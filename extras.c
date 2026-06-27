/*
  Crimelife 3 Extras v0.8.6
  Companion for Crimelife3.WidescreenFix.
  Freestanding 32-bit Windows DLL: no CRT imports.

  Fixes in this build:
  - Inline hooks the real GameMaker action functions instead of patching the
    already-executed registration table.
  - Correct GameMaker ABI / argument order for globals and cheats.
  - One parked vehicle creation per spatial parking slot per process.
  - Stretches/removes the night overlay.
  - Typed cheats are polled directly; no WM_CHAR dependency and no command
    contains the G key.
  - NPC density falls back to the original cap while wanted, so the density
    multiplier does not multiply police/FBI/army spawns.
*/

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef unsigned long  DWORD;
typedef long           LONG;
typedef unsigned long  ULONG_PTR;
typedef unsigned int   UINT;
typedef int            BOOL;
typedef short          SHORT;
typedef void*          PVOID;
typedef void*          HANDLE;
typedef void*          HMODULE;
typedef void*          HINSTANCE;
typedef void*          HWND;
typedef const char*    LPCSTR;
typedef char*          LPSTR;
typedef DWORD (__attribute__((stdcall)) *THREADPROC)(PVOID);
int _fltused=0;

#define WINAPI __attribute__((stdcall))
#define DLL_PROCESS_ATTACH 1
#define PAGE_EXECUTE_READWRITE 0x40
#define GENERIC_WRITE 0x40000000u
#define FILE_SHARE_READ 1u
#define CREATE_ALWAYS 2u
#define FILE_ATTRIBUTE_NORMAL 0x80u
#define INVALID_HANDLE_VALUE ((HANDLE)(ULONG_PTR)-1)

/* Exact RVAs for the supplied Crimelife3.exe runner. */
#define RVA_ACTION_CREATE_OBJECT        0x14b560u
#define RVA_ACTION_CREATE_OBJECT_RANDOM 0x14b7ccu
#define RVA_ACTION_IF_NUMBER            0x14c7e0u
#define RVA_ACTION_SET_HEALTH           0x14d460u
#define RVA_ACTION_DRAW_RECTANGLE        0x14e57cu
#define RVA_VARIABLE_GLOBAL_GET          0x16a7e8u
#define RVA_VARIABLE_GLOBAL_SET          0x16aa5cu

/* Kernel32 */
static BOOL   (WINAPI *pVirtualProtect)(PVOID,u32,DWORD,DWORD*);
static BOOL   (WINAPI *pFlushInstructionCache)(HANDLE,const void*,u32);
static HANDLE (WINAPI *pGetCurrentProcess)(void);
static DWORD  (WINAPI *pGetCurrentProcessId)(void);
static HANDLE (WINAPI *pCreateThread)(PVOID,u32,THREADPROC,PVOID,DWORD,DWORD*);
static void   (WINAPI *pSleep)(DWORD);
static DWORD  (WINAPI *pGetTickCount)(void);
static DWORD  (WINAPI *pGetPrivateProfileIntA)(LPCSTR,LPCSTR,i32,LPCSTR);
static HANDLE (WINAPI *pCreateFileA)(LPCSTR,DWORD,DWORD,PVOID,DWORD,DWORD,HANDLE);
static BOOL   (WINAPI *pWriteFile)(HANDLE,const void*,DWORD,DWORD*,PVOID);
static BOOL   (WINAPI *pCloseHandle)(HANDLE);
/* User32 */
static HWND   (WINAPI *pGetForegroundWindow)(void);
static DWORD  (WINAPI *pGetWindowThreadProcessId)(HWND,DWORD*);
static SHORT  (WINAPI *pGetAsyncKeyState)(i32);

static u8* g_exe;
static u8* g_mainFix;
static HANDLE g_log = INVALID_HANDLE_VALUE;

static i32 g_cheatsEnabled=1;
static i32 g_nightOverlayMode=1;
static i32 g_stabilizeTraffic=1;
static i32 g_fixParked=1;
static i32 g_stableParked=1;
static i32 g_excludePoliceDensity=1;
static i32 g_resX=3440, g_resY=1440;
static i32 g_mergeRadius=192;
static u32 g_trafficCooldownMs=120000;

static volatile u32 g_pendingCheats;
static volatile i32 g_superman;
static volatile i32 g_blindCops;

/* Real function continuation pointers for inline detours. */
void* g_retCreateObject;
void* g_retCreateRandom;
void* g_retIfNumber;
void* g_retSetHealth;
void* g_retDrawRectangle;

/* GameMaker RValue is 24 bytes in this runner. */
typedef struct {
    u32 a0, a4;
    double real;
    char* str;
    u32 tail;
} RValue;

#define DSTR(sym, literal) \
    static struct { i32 refcount; i32 length; char data[sizeof(literal)]; } sym = { -1, (i32)sizeof(literal)-1, literal }
DSTR(ds_hours,"hours");
DSTR(ds_night,"night");
DSTR(ds_armor,"armor");
DSTR(ds_wanted,"wanted");
DSTR(ds_copnerves,"copnerves");
DSTR(ds_cgammo,"cgammo");
DSTR(ds_mk23ammo,"mk23ammo");
DSTR(ds_psgammo,"psgammo");
DSTR(ds_uziammo,"uziammo");
DSTR(ds_mp9ammo,"mp9ammo");
DSTR(ds_shotgunammo,"shotgunammo");
DSTR(ds_grenades,"grenades");
DSTR(ds_molotovs,"molotovs");
DSTR(ds_ak47ammo,"ak47ammo");
DSTR(ds_rpgammo,"rpgammo");
DSTR(ds_sniperammo,"sniperammo");
DSTR(ds_flameammo,"flameammo");
DSTR(ds_grappler,"grappler");
DSTR(ds_weapon,"weapon");

#define CHEAT_DARK      0x01u
#define CHEAT_DAY       0x02u
#define CHEAT_ARSENAL   0x04u
#define CHEAT_SUPERMAN  0x08u
#define CHEAT_BLINDCOPS 0x10u

static u32 cstrlen(const char* s){u32 n=0;if(!s)return 0;while(s[n])n++;return n;}
static i32 lowerc(i32 c){return(c>='A'&&c<='Z')?c+32:c;}
static i32 streqi_w(const u16* w,u16 bytes,const char* s){u32 n=(u32)bytes/2,i=0;while(i<n&&w[i])i++;if(i!=cstrlen(s))return 0;for(i=0;i<n&&w[i];i++)if(lowerc((i32)w[i])!=lowerc((i32)(u8)s[i]))return 0;return 1;}
static i32 streq(const char*a,const char*b){u32 i=0;if(!a||!b)return 0;while(a[i]&&b[i]&&a[i]==b[i])i++;return a[i]==0&&b[i]==0;}
static i32 endswith(const char*buf,u32 len,const char*suf){u32 n=cstrlen(suf),i;if(n>len)return 0;for(i=0;i<n;i++)if(buf[len-n+i]!=suf[i])return 0;return 1;}
static void memzero(void*p,u32 n){u8*d=(u8*)p;while(n--)*d++=0;}
static void logline(const char*s){DWORD out=0;u32 n=cstrlen(s);if(g_log!=INVALID_HANDLE_VALUE&&pWriteFile){pWriteFile(g_log,s,n,&out,0);pWriteFile(g_log,"\r\n",2,&out,0);}}

/* ---------------- PEB / exports ---------------- */
static void* get_peb(void){void*p;__asm__ volatile("movl %%fs:0x30,%0":"=r"(p));return p;}
static void* module_by_name(const char*wanted){u8*peb=(u8*)get_peb();u8*ldr=*(u8**)(peb+0x0c);u8*head=ldr+0x0c;u8*link=*(u8**)head;while(link&&link!=head){u8*ent=link;void*base=*(void**)(ent+0x18);u16 len=*(u16*)(ent+0x2c);u16*name=*(u16**)(ent+0x30);if(name&&streqi_w(name,len,wanted))return base;link=*(u8**)link;}return 0;}
static void* main_exe_base(void){u8*peb=(u8*)get_peb();u8*ldr=*(u8**)(peb+0x0c);u8*head=ldr+0x0c;u8*link=*(u8**)head;if(!link||link==head)return 0;return *(void**)(link+0x18);}
static void* resolve_export_raw(void*module,const char*name){u8*b=(u8*)module;u32 nt=*(u32*)(b+0x3c);u8*pe=b+nt;u32 er=*(u32*)(pe+0x78),es=*(u32*)(pe+0x7c);if(!er)return 0;u8*ex=b+er;u32 nn=*(u32*)(ex+0x18);u32*funcs=(u32*)(b+*(u32*)(ex+0x1c));u32*names=(u32*)(b+*(u32*)(ex+0x20));u16*ords=(u16*)(b+*(u32*)(ex+0x24));u32 i;for(i=0;i<nn;i++){char*nm=(char*)(b+names[i]);if(streq(nm,name)){u32 r=funcs[ords[i]];if(r>=er&&r<er+es){char*fwd=(char*)(b+r),mod[64],fn[96],dll[68];u32 j=0,k=0,z=0;while(fwd[j]&&fwd[j]!='.'&&j<58){mod[j]=lowerc(fwd[j]);j++;}mod[j]=0;if(fwd[j]=='.')j++;while(fwd[j]&&k<94)fn[k++]=fwd[j++];fn[k]=0;while(mod[z]&&z<60){dll[z]=mod[z];z++;}dll[z++]='.';dll[z++]='d';dll[z++]='l';dll[z++]='l';dll[z]=0;{void*m=module_by_name(dll);if(m)return resolve_export_raw(m,fn);}return 0;}return b+r;}}return 0;}
static void* resolve_any(const char*name){void*kb=module_by_name("kernelbase.dll"),*k32=module_by_name("kernel32.dll"),*p=0;if(kb)p=resolve_export_raw(kb,name);if(!p&&k32)p=resolve_export_raw(k32,name);return p;}
static i32 resolve_apis(void){void*u=module_by_name("user32.dll");pVirtualProtect=(void*)resolve_any("VirtualProtect");pFlushInstructionCache=(void*)resolve_any("FlushInstructionCache");pGetCurrentProcess=(void*)resolve_any("GetCurrentProcess");pGetCurrentProcessId=(void*)resolve_any("GetCurrentProcessId");pCreateThread=(void*)resolve_any("CreateThread");pSleep=(void*)resolve_any("Sleep");pGetTickCount=(void*)resolve_any("GetTickCount");pGetPrivateProfileIntA=(void*)resolve_any("GetPrivateProfileIntA");pCreateFileA=(void*)resolve_any("CreateFileA");pWriteFile=(void*)resolve_any("WriteFile");pCloseHandle=(void*)resolve_any("CloseHandle");if(u){pGetForegroundWindow=(void*)resolve_export_raw(u,"GetForegroundWindow");pGetWindowThreadProcessId=(void*)resolve_export_raw(u,"GetWindowThreadProcessId");pGetAsyncKeyState=(void*)resolve_export_raw(u,"GetAsyncKeyState");}return pVirtualProtect&&pCreateThread&&pSleep&&pGetTickCount&&pGetPrivateProfileIntA&&pGetForegroundWindow&&pGetWindowThreadProcessId&&pGetAsyncKeyState;}

static void patch_jmp(void*target,void*hook,u32 len){DWORD old=0,tmp=0;u8*p=(u8*)target;u32 i;if(len<5||!pVirtualProtect)return;if(pVirtualProtect(target,len,PAGE_EXECUTE_READWRITE,&old)){p[0]=0xe9;*(i32*)(p+1)=(i32)((u8*)hook-(p+5));for(i=5;i<len;i++)p[i]=0x90;if(pFlushInstructionCache)pFlushInstructionCache(pGetCurrentProcess(),target,len);pVirtualProtect(target,len,old,&tmp);}}

/* ---------------- GameMaker ABI helpers ---------------- */
void call_gml_raw(void*fn,void*self,void*other,RValue*result,RValue*args) __attribute__((naked));
void call_gml_raw(void*fn,void*self,void*other,RValue*result,RValue*args){__asm__ volatile(
    "push %ebp\n\t"
    "mov %esp,%ebp\n\t"
    /* Callee expects result at [ebp+8], unused at +12, args at +16. */
    "push 24(%ebp)\n\t"
    "push $0\n\t"
    "push 20(%ebp)\n\t"
    "mov 16(%ebp),%edx\n\t"
    "mov 12(%ebp),%eax\n\t"
    "call *8(%ebp)\n\t"
    "leave\n\t"
    "ret\n\t");}
static void set_global(void*self,char*name,double value){RValue a[2],r;memzero(a,sizeof(a));memzero(&r,sizeof(r));a[0].str=name;a[1].real=value;call_gml_raw((void*)(g_exe+RVA_VARIABLE_GLOBAL_SET),self,self,&r,a);}
static double get_global(void*self,char*name){RValue a[1],r;memzero(a,sizeof(a));memzero(&r,sizeof(r));a[0].str=name;call_gml_raw((void*)(g_exe+RVA_VARIABLE_GLOBAL_GET),self,self,&r,a);return r.real;}
static void set_health_100(void){double*p=*(double**)(g_exe+0x18f5fcu);if(p&&(u32)(ULONG_PTR)p>0x10000u)*p=100.0;}

static i32 obj_id(void*self){return self?*(i32*)((u8*)self+0xcc):-1;}
static double obj_x(void*self){return self?*(double*)((u8*)self+0x50):0.0;}
static double obj_y(void*self){return self?*(double*)((u8*)self+0x58):0.0;}
static i32 rv_int(void*args,i32 n){return(i32)(*(double*)((u8*)args+n*24+8));}
static void rv_set(void*args,i32 n,i32 v){*(double*)((u8*)args+n*24+8)=(double)v;}
static u32 ihash(i32 a,i32 b,i32 c){u32 x=(u32)a*0x9e3779b1u^(u32)b*0x85ebca6bu^(u32)c*0xc2b2ae35u;x^=x>>16;x*=0x7feb352du;x^=x>>15;return x;}

/* ---------------- Cheats ---------------- */
static void activate_cheat(u32 bit){g_pendingCheats|=bit;}
static void process_cheats(void*self){static DWORD lastMaintain=0;u32 pending=g_pendingCheats;DWORD now=pGetTickCount?pGetTickCount():0;if(pending){g_pendingCheats=0;
    if(pending&CHEAT_DARK){set_global(self,ds_hours.data,23);set_global(self,ds_night.data,1);logline("[Cheat] DARK activated: time set to night.");}
    if(pending&CHEAT_DAY){set_global(self,ds_hours.data,12);set_global(self,ds_night.data,0);logline("[Cheat] DAY activated: time set to day.");}
    if(pending&CHEAT_ARSENAL){set_global(self,ds_cgammo.data,999);set_global(self,ds_mk23ammo.data,999);set_global(self,ds_psgammo.data,999);set_global(self,ds_uziammo.data,999);set_global(self,ds_mp9ammo.data,999);set_global(self,ds_shotgunammo.data,999);set_global(self,ds_grenades.data,999);set_global(self,ds_molotovs.data,999);set_global(self,ds_ak47ammo.data,999);set_global(self,ds_rpgammo.data,999);set_global(self,ds_sniperammo.data,999);set_global(self,ds_flameammo.data,999);set_global(self,ds_grappler.data,999);set_global(self,ds_weapon.data,1);logline("[Cheat] ARSENAL activated: all ammunition granted.");}
    if(pending&CHEAT_SUPERMAN){g_superman=!g_superman;if(g_superman){set_health_100();set_global(self,ds_armor.data,100);logline("[Cheat] SUPERMAN enabled.");}else logline("[Cheat] SUPERMAN disabled.");}
    if(pending&CHEAT_BLINDCOPS){g_blindCops=!g_blindCops;if(g_blindCops){set_global(self,ds_wanted.data,0);set_global(self,ds_copnerves.data,0);logline("[Cheat] BLINDCOPS enabled.");}else logline("[Cheat] BLINDCOPS disabled.");}
  }
  if((g_superman||g_blindCops)&&(DWORD)(now-lastMaintain)>=75){lastMaintain=now;if(g_superman){set_health_100();set_global(self,ds_armor.data,100);}if(g_blindCops){set_global(self,ds_wanted.data,0);set_global(self,ds_copnerves.data,0);}}
}

/* ---------------- Stable vehicle spawning ---------------- */
typedef struct {i32 used,group,model,created;i32 x,y;DWORD lastSpawn;} SpawnSlot;
static SpawnSlot g_slots[2048];
static void* g_lastCreatorSelf;
static DWORD g_lastCreatorTick;
static i32 g_loggedParkReserve,g_loggedParkBlock,g_loggedTrafficModel,g_loggedTrafficBlock,g_loggedCooldown;

static SpawnSlot* find_slot(double x,double y,i32 group,i32 create){i32 i,freeIdx=-1;double r=(double)g_mergeRadius,r2=r*r;for(i=0;i<2048;i++){SpawnSlot*s=&g_slots[i];if(!s->used){if(freeIdx<0)freeIdx=i;continue;}if(s->group==group){double dx=x-(double)s->x,dy=y-(double)s->y;if(dx*dx+dy*dy<=r2)return s;}}if(!create)return 0;if(freeIdx<0)freeIdx=(i32)(ihash((i32)x,(i32)y,group)&2047u);{SpawnSlot*s=&g_slots[freeIdx];memzero(s,sizeof(*s));s->used=1;s->group=group;s->x=(i32)x;s->y=(i32)y;return s;}}
static i32 choose_candidate(void*args,u32 seed,i32 count){i32 valid[8],n=0,i;for(i=0;i<count&&i<8;i++){i32 c=rv_int(args,i);if(c>=0)valid[n++]=c;}return n?valid[seed%(u32)n]:-1;}
static i32 is_parking_spawner(i32 id){return id>=7458&&id<=7462;}

/* kind: 0=action_create_object, 1=action_create_object_random */
__attribute__((noinline)) i32 on_create(void*self,void*result,void*arg2,void*args,i32 kind){i32 id,model,i;double x,y;DWORD now;SpawnSlot*s;(void)result;(void)arg2;if(!self||!args)return 1;id=obj_id(self);x=obj_x(self);y=obj_y(self);now=pGetTickCount?pGetTickCount():0;
  if(g_fixParked&&is_parking_spawner(id)){
    s=find_slot(x,y,1,1);
    if(s->created){if(!g_loggedParkBlock){logline("[VehicleSpawn] duplicate parked creation blocked by the real action function; only one vehicle is allowed per spatial parking slot.");g_loggedParkBlock=1;}return 0;}
    if(kind==1&&g_stableParked){if(s->model<=0)s->model=choose_candidate(args,ihash(s->x,s->y,1),4);model=s->model;if(model>=0)for(i=0;i<4;i++)rv_set(args,i,model);}
    s->created=1;s->lastSpawn=now;if(!g_loggedParkReserve){logline("[VehicleSpawn] parked slot reserved before the first actual create; subsequent random-create actions in the same event are suppressed.");g_loggedParkReserve=1;}return 1;
  }
  if(kind==1&&g_stabilizeTraffic&&(id==7215||id==7216)){
    if(g_lastCreatorSelf==self&&(DWORD)(now-g_lastCreatorTick)<1500){if(!g_loggedTrafficBlock){logline("[VehicleSpawn] extra random vehicle creates from the same traffic-creator event are blocked.");g_loggedTrafficBlock=1;}return 0;}
    g_lastCreatorSelf=self;g_lastCreatorTick=now;s=find_slot(x,y,3,1);if(s->model<=0)s->model=choose_candidate(args,ihash(s->x,s->y,3),4);model=s->model;if(model>=0)for(i=0;i<4;i++)rv_set(args,i,model);if(!g_loggedTrafficModel){logline("[VehicleSpawn] distant traffic model stabilized by world position.");g_loggedTrafficModel=1;}return 1;
  }
  if(kind==1&&g_stabilizeTraffic&&(id==2844||id==2846||id==2847||id==2848)){
    s=find_slot(x,y,2,1);if(s->lastSpawn&&(DWORD)(now-s->lastSpawn)<g_trafficCooldownMs){if(!g_loggedCooldown){logline("[VehicleSpawn] rapid distant traffic-spawner loop suppressed with a long respawn cooldown.");g_loggedCooldown=1;}return 0;}s->lastSpawn=now;return 1;
  }
  return 1;
}

/* ---------------- Civilian density without multiplying police ---------------- */
static i32 g_loggedPoliceCap;
__attribute__((noinline)) void on_if_number(void*self,void*args){if(!g_excludePoliceDensity||!self||!args)return;if(obj_id(self)==2781&&rv_int(args,0)==2744&&rv_int(args,1)>6){double wanted=get_global(self,ds_wanted.data);if(wanted>0.5){rv_set(args,1,6);if(!g_loggedPoliceCap){logline("[Density] wanted level active: NPC cap restored to the original 6 so NPCDensity does not multiply police/FBI/army.");g_loggedPoliceCap=1;}}}}

/* ---------------- Night overlay ---------------- */
typedef struct{DWORD X,Y,Width,Height;float MinZ,MaxZ;}D3DVIEWPORT8;
typedef LONG(WINAPI*D3DGetViewportFn)(void*,D3DVIEWPORT8*);
typedef LONG(WINAPI*D3DSetViewportFn)(void*,const D3DVIEWPORT8*);
static D3DVIEWPORT8 g_savedViewport;static i32 g_viewportSaved;
static i32 nearv(double a,double b){double d=a-b;if(d<0)d=-d;return d<0.01;}
__attribute__((noinline)) i32 on_draw_before(void*self,void*result,void*arg2,void*args){static i32 logged=0;i32 id;double x1,y1,x2,y2;(void)result;(void)arg2;g_viewportSaved=0;if(self)process_cheats(self);if(!self||!args||g_nightOverlayMode==0)return 0;id=obj_id(self);if(id!=10)return 0;x1=*(double*)((u8*)args+8);y1=*(double*)((u8*)args+32);x2=*(double*)((u8*)args+56);y2=*(double*)((u8*)args+80);if(!(nearv(x1,-1)&&nearv(y1,-1)&&nearv(x2,800)&&nearv(y2,600)))return 0;if(g_nightOverlayMode==2){if(!logged){logline("[Overlay] night darkness rectangle disabled.");logged=1;}return 2;}if(g_mainFix){void*dev=*(void**)(g_mainFix+0x26170);D3DSetViewportFn setv=*(D3DSetViewportFn*)(g_mainFix+0x2618c);D3DGetViewportFn getv=*(D3DGetViewportFn*)(g_mainFix+0x26190);if(dev&&setv&&getv&&getv(dev,&g_savedViewport)>=0){D3DVIEWPORT8 full;full.X=0;full.Y=0;full.Width=(DWORD)g_resX;full.Height=(DWORD)g_resY;full.MinZ=g_savedViewport.MinZ;full.MaxZ=g_savedViewport.MaxZ;if(setv(dev,&full)>=0){g_viewportSaved=1;if(!logged){logline("[Overlay] night darkness stretched across the full ultrawide viewport.");logged=1;}return 1;}}}return 0;}
__attribute__((noinline)) void on_draw_after(void){if(g_viewportSaved&&g_mainFix){void*dev=*(void**)(g_mainFix+0x26170);D3DSetViewportFn setv=*(D3DSetViewportFn*)(g_mainFix+0x2618c);if(dev&&setv)setv(dev,&g_savedViewport);}g_viewportSaved=0;}
__attribute__((noinline)) i32 on_health(void*self,void*args){double amount;if(!g_superman||!self||!args)return 1;amount=*(double*)((u8*)args+8);if(obj_id(self)==0&&amount<0.0)return 0;return 1;}

/* ---------------- Original prologue trampolines ---------------- */
void create_object_trampoline(void)__attribute__((naked));
void create_object_trampoline(void){__asm__ volatile("push %ebp\n\tmov %esp,%ebp\n\tpush $0\n\tpush $0\n\tjmp *_g_retCreateObject\n\t");}
void create_random_trampoline(void)__attribute__((naked));
void create_random_trampoline(void){__asm__ volatile("push %ebp\n\tmov %esp,%ebp\n\tpush %ecx\n\tpush %ebx\n\tjmp *_g_retCreateRandom\n\t");}
void if_number_trampoline(void)__attribute__((naked));
void if_number_trampoline(void){__asm__ volatile("push %ebp\n\tmov %esp,%ebp\n\tsub $8,%esp\n\tjmp *_g_retIfNumber\n\t");}
void health_trampoline(void)__attribute__((naked));
void health_trampoline(void){__asm__ volatile("push %ebp\n\tmov %esp,%ebp\n\tsub $8,%esp\n\tjmp *_g_retSetHealth\n\t");}
void draw_trampoline(void)__attribute__((naked));
void draw_trampoline(void){__asm__ volatile("push %ebp\n\tmov %esp,%ebp\n\tmov %eax,%ecx\n\tjmp *_g_retDrawRectangle\n\t");}

/* ---------------- Inline hook entry wrappers ---------------- */
void create_object_hook(void)__attribute__((naked));
void create_object_hook(void){__asm__ volatile(
  "pushal\n\t"
  "mov 28(%esp),%eax\n\t" "mov 36(%esp),%ecx\n\t" "mov 40(%esp),%edx\n\t" "mov 44(%esp),%ebx\n\t"
  "push $0\n\t" "push %ebx\n\t" "push %edx\n\t" "push %ecx\n\t" "push %eax\n\t"
  "call _on_create\n\t" "add $20,%esp\n\t" "test %eax,%eax\n\t" "popal\n\t" "jz 1f\n\t" "jmp _create_object_trampoline\n\t" "1: ret $12\n\t");}
void create_random_hook(void)__attribute__((naked));
void create_random_hook(void){__asm__ volatile(
  "pushal\n\t"
  "mov 28(%esp),%eax\n\t" "mov 36(%esp),%ecx\n\t" "mov 40(%esp),%edx\n\t" "mov 44(%esp),%ebx\n\t"
  "push $1\n\t" "push %ebx\n\t" "push %edx\n\t" "push %ecx\n\t" "push %eax\n\t"
  "call _on_create\n\t" "add $20,%esp\n\t" "test %eax,%eax\n\t" "popal\n\t" "jz 1f\n\t" "jmp _create_random_trampoline\n\t" "1: ret $12\n\t");}
void if_number_hook(void)__attribute__((naked));
void if_number_hook(void){__asm__ volatile(
  "pushal\n\t" "mov 28(%esp),%eax\n\t" "mov 44(%esp),%ebx\n\t" "push %ebx\n\t" "push %eax\n\t" "call _on_if_number\n\t" "add $8,%esp\n\t" "popal\n\t" "jmp _if_number_trampoline\n\t");}
void health_hook(void)__attribute__((naked));
void health_hook(void){__asm__ volatile(
  "pushal\n\t" "mov 28(%esp),%eax\n\t" "mov 44(%esp),%ebx\n\t" "push %ebx\n\t" "push %eax\n\t" "call _on_health\n\t" "add $8,%esp\n\t" "test %eax,%eax\n\t" "popal\n\t" "jz 1f\n\t" "jmp _health_trampoline\n\t" "1: ret $12\n\t");}
void draw_hook(void)__attribute__((naked));
void draw_hook(void){__asm__ volatile(
  "pushal\n\t"
  "mov 28(%esp),%eax\n\t" "mov 36(%esp),%ecx\n\t" "mov 40(%esp),%edx\n\t" "mov 44(%esp),%ebx\n\t"
  "push %ebx\n\t" "push %edx\n\t" "push %ecx\n\t" "push %eax\n\t" "call _on_draw_before\n\t" "add $16,%esp\n\t"
  "cmp $2,%eax\n\t" "je 2f\n\t" "cmp $1,%eax\n\t" "je 1f\n\t" "popal\n\t" "jmp _draw_trampoline\n\t"
  "1: popal\n\t" "push 12(%esp)\n\t" "push 12(%esp)\n\t" "push 12(%esp)\n\t" "call _draw_trampoline\n\t" "pushal\n\t" "call _on_draw_after\n\t" "popal\n\t" "ret $12\n\t"
  "2: popal\n\t" "ret $12\n\t");}

/* ---------------- Keyboard polling ---------------- */
static char g_typebuf[48];static u32 g_typelen;static DWORD g_lastCharTick;
static void feed_char(i32 ch){DWORD now=pGetTickCount?pGetTickCount():0;u32 i;ch=lowerc(ch);if(ch<'a'||ch>'z')return;if((DWORD)(now-g_lastCharTick)>4000)g_typelen=0;g_lastCharTick=now;if(g_typelen>=sizeof(g_typebuf)-1){for(i=1;i<g_typelen;i++)g_typebuf[i-1]=g_typebuf[i];g_typelen--;}g_typebuf[g_typelen++]=(char)ch;g_typebuf[g_typelen]=0;
  if(endswith(g_typebuf,g_typelen,"blindcops")){activate_cheat(CHEAT_BLINDCOPS);g_typelen=0;logline("[Cheat] BLINDCOPS sequence accepted.");}
  else if(endswith(g_typebuf,g_typelen,"superman")){activate_cheat(CHEAT_SUPERMAN);g_typelen=0;logline("[Cheat] SUPERMAN sequence accepted.");}
  else if(endswith(g_typebuf,g_typelen,"arsenal")){activate_cheat(CHEAT_ARSENAL);g_typelen=0;logline("[Cheat] ARSENAL sequence accepted.");}
  else if(endswith(g_typebuf,g_typelen,"dark")){activate_cheat(CHEAT_DARK);g_typelen=0;logline("[Cheat] DARK sequence accepted.");}
  else if(endswith(g_typebuf,g_typelen,"day")){activate_cheat(CHEAT_DAY);g_typelen=0;logline("[Cheat] DAY sequence accepted.");}
}

static void load_config(void){const char*ini="Crimelife3.WidescreenFix.ini";i32 sec;if(!pGetPrivateProfileIntA)return;g_resX=(i32)pGetPrivateProfileIntA("DISPLAY","ResX",3440,ini);g_resY=(i32)pGetPrivateProfileIntA("DISPLAY","ResY",1440,ini);g_nightOverlayMode=(i32)pGetPrivateProfileIntA("OVERLAYS","NightOverlayMode",1,ini);g_cheatsEnabled=(i32)pGetPrivateProfileIntA("CHEATS","Enabled",1,ini);g_fixParked=(i32)pGetPrivateProfileIntA("VEHICLE_SPAWNING","FixParkedVehicleFlicker",1,ini);g_stableParked=(i32)pGetPrivateProfileIntA("VEHICLE_SPAWNING","StableParkedVehicleModels",1,ini);g_stabilizeTraffic=(i32)pGetPrivateProfileIntA("VEHICLE_SPAWNING","StabilizeDistantTraffic",1,ini);g_mergeRadius=(i32)pGetPrivateProfileIntA("VEHICLE_SPAWNING","ParkedSpawnMergeRadius",192,ini);if(g_mergeRadius<16)g_mergeRadius=16;if(g_mergeRadius>1024)g_mergeRadius=1024;sec=(i32)pGetPrivateProfileIntA("VEHICLE_SPAWNING","DistantTrafficRespawnSeconds",120,ini);if(sec<5)sec=5;if(sec>3600)sec=3600;g_trafficCooldownMs=(u32)sec*1000u;g_excludePoliceDensity=(i32)pGetPrivateProfileIntA("DENSITY","ExcludePoliceFromNPCDensity",1,ini);}

static i32 g_hooksInstalled;
static void install_hooks(void){if(g_hooksInstalled||!g_exe)return;g_retCreateObject=g_exe+RVA_ACTION_CREATE_OBJECT+7;g_retCreateRandom=g_exe+RVA_ACTION_CREATE_OBJECT_RANDOM+5;g_retIfNumber=g_exe+RVA_ACTION_IF_NUMBER+6;g_retSetHealth=g_exe+RVA_ACTION_SET_HEALTH+6;g_retDrawRectangle=g_exe+RVA_ACTION_DRAW_RECTANGLE+5;patch_jmp(g_exe+RVA_ACTION_CREATE_OBJECT,(void*)create_object_hook,7);patch_jmp(g_exe+RVA_ACTION_CREATE_OBJECT_RANDOM,(void*)create_random_hook,5);patch_jmp(g_exe+RVA_ACTION_IF_NUMBER,(void*)if_number_hook,6);patch_jmp(g_exe+RVA_ACTION_SET_HEALTH,(void*)health_hook,6);patch_jmp(g_exe+RVA_ACTION_DRAW_RECTANGLE,(void*)draw_hook,5);g_hooksInstalled=1;logline("[Hooks] real GameMaker action functions inline-hooked (registration timing no longer matters).");}

static DWORD WINAPI worker(PVOID unused){DWORD pid=pGetCurrentProcessId?pGetCurrentProcessId():0;u8 prev[256];i32 i;(void)unused;memzero(prev,sizeof(prev));for(i=0;i<600;i++){u8*mf=(u8*)module_by_name("Crimelife3.WidescreenFix.asi");if(mf){g_mainFix=mf;break;}pSleep(10);}install_hooks();logline("Crimelife 3 Extras v0.8.6 active. Cheats: DARK, DAY, ARSENAL, SUPERMAN, BLINDCOPS (no command uses G).");for(;;){HWND h=pGetForegroundWindow?pGetForegroundWindow():0;DWORD wpid=0;i32 vk;if(h&&pGetWindowThreadProcessId){pGetWindowThreadProcessId(h,&wpid);if(wpid==pid&&g_cheatsEnabled){for(vk='A';vk<='Z';vk++){SHORT s=pGetAsyncKeyState(vk);u8 down=(s&0x8000)?1:0;if(down&&!prev[vk])feed_char(vk);prev[vk]=down;}/* Function-key fallbacks. */for(vk=0x74;vk<=0x78;vk++){SHORT s=pGetAsyncKeyState(vk);u8 down=(s&0x8000)?1:0;if(down&&!prev[vk]){if(vk==0x74)activate_cheat(CHEAT_DARK);else if(vk==0x75)activate_cheat(CHEAT_DAY);else if(vk==0x76)activate_cheat(CHEAT_ARSENAL);else if(vk==0x77)activate_cheat(CHEAT_SUPERMAN);else activate_cheat(CHEAT_BLINDCOPS);}prev[vk]=down;}}}pSleep(10);}return 0;}

BOOL WINAPI DllMain(HINSTANCE inst,DWORD reason,PVOID reserved){DWORD tid=0;(void)inst;(void)reserved;if(reason!=DLL_PROCESS_ATTACH)return 1;g_exe=(u8*)main_exe_base();if(!resolve_apis())return 1;if(pCreateFileA)g_log=pCreateFileA("Crimelife3.Extras.log",GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);logline("Crimelife 3 Extras v0.8.6 loaded.");load_config();g_mainFix=(u8*)module_by_name("Crimelife3.WidescreenFix.asi");install_hooks();if(pCreateThread){HANDLE t=pCreateThread(0,0,worker,0,0,&tid);if(t&&pCloseHandle)pCloseHandle(t);}return 1;}
