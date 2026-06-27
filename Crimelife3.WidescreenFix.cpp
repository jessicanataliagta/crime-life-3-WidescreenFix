// Crimelife 3 Widescreen Fix v0.8.4
// Exact-target build for Crimelife3.exe SHA-256:
// 6dc6a6bcc7785c169dec35ab6e61370be98978631970417f23663d63cdfdcd9e
// 32-bit ASI plugin for the GameMaker 8 / Direct3D 8 runner.

extern "C" {
int _fltused = 0;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* HINSTANCE;
typedef void* HWND;
typedef void* LPVOID;
typedef const void* LPCVOID;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long SIZE_T;
typedef long LONG;
typedef unsigned int UINT;
typedef int BOOL;
typedef long HRESULT;
typedef unsigned long ULONG;

#define WINAPI __stdcall
#define TRUE 1
#define FALSE 0
#define DLL_PROCESS_ATTACH 1
#define PAGE_NOACCESS 0x01
#define PAGE_GUARD 0x100
#define PAGE_EXECUTE_READWRITE 0x40
#define MEM_COMMIT 0x1000
#define INVALID_HANDLE_VALUE ((HANDLE)(LONG)-1)
#define GENERIC_WRITE 0x40000000UL
#define FILE_SHARE_READ 0x00000001UL
#define CREATE_ALWAYS 2UL
#define FILE_ATTRIBUTE_NORMAL 0x00000080UL
#define GWL_STYLE (-16)
#define GWL_EXSTYLE (-20)
#define WS_VISIBLE 0x10000000UL
#define WS_POPUP 0x80000000UL
#define WS_OVERLAPPEDWINDOW 0x00CF0000UL
#define SWP_FRAMECHANGED 0x0020UL
#define SWP_SHOWWINDOW 0x0040UL
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define FILE_END 2

__declspec(dllimport) HMODULE WINAPI GetModuleHandleA(LPCSTR);
__declspec(dllimport) DWORD WINAPI GetModuleFileNameA(HMODULE, LPSTR, DWORD);
__declspec(dllimport) BOOL WINAPI VirtualProtect(LPVOID, DWORD, DWORD, DWORD*);
__declspec(dllimport) SIZE_T WINAPI VirtualQuery(LPCVOID, LPVOID, SIZE_T);
__declspec(dllimport) int WINAPI GetPrivateProfileIntA(LPCSTR, LPCSTR, int, LPCSTR);
__declspec(dllimport) DWORD WINAPI GetPrivateProfileStringA(LPCSTR, LPCSTR, LPCSTR, LPSTR, DWORD, LPCSTR);
__declspec(dllimport) HANDLE WINAPI CreateFileA(LPCSTR, DWORD, DWORD, LPVOID, DWORD, DWORD, HANDLE);
__declspec(dllimport) BOOL WINAPI WriteFile(HANDLE, const void*, DWORD, DWORD*, LPVOID);
__declspec(dllimport) BOOL WINAPI CloseHandle(HANDLE);
__declspec(dllimport) DWORD WINAPI SetFilePointer(HANDLE, LONG, LONG*, DWORD);
__declspec(dllimport) BOOL WINAPI DisableThreadLibraryCalls(HMODULE);
__declspec(dllimport) BOOL WINAPI FlushInstructionCache(HANDLE, const void*, unsigned long);
__declspec(dllimport) HANDLE WINAPI GetCurrentProcess(void);
__declspec(dllimport) void WINAPI OutputDebugStringA(LPCSTR);

__declspec(dllimport) int WINAPI GetSystemMetrics(int);
__declspec(dllimport) LONG WINAPI GetWindowLongA(HWND, int);
__declspec(dllimport) LONG WINAPI SetWindowLongA(HWND, int, LONG);
__declspec(dllimport) BOOL WINAPI SetWindowPos(HWND, HWND, int, int, int, int, UINT);
__declspec(dllimport) BOOL WINAPI GetClientRect(HWND, LPVOID);
__declspec(dllimport) BOOL WINAPI GetWindowRect(HWND, LPVOID);
}

struct RECTI { LONG left, top, right, bottom; };
extern "C" __declspec(dllimport) BOOL WINAPI AdjustWindowRectEx(RECTI*, DWORD, BOOL, DWORD);

struct MEMORY_BASIC_INFORMATION32 {
    LPVOID BaseAddress;
    LPVOID AllocationBase;
    DWORD AllocationProtect;
    SIZE_T RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
};

struct D3DPRESENT_PARAMETERS8 {
    UINT BackBufferWidth;
    UINT BackBufferHeight;
    UINT BackBufferFormat;
    UINT BackBufferCount;
    UINT MultiSampleType;
    UINT SwapEffect;
    HWND hDeviceWindow;
    BOOL Windowed;
    BOOL EnableAutoDepthStencil;
    UINT AutoDepthStencilFormat;
    DWORD Flags;
    UINT FullScreen_RefreshRateInHz;
    UINT FullScreen_PresentationInterval;
};

struct D3DVIEWPORT8 {
    DWORD X, Y, Width, Height;
    float MinZ, MaxZ;
};

struct D3DMATRIX8 {
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
};

struct D3DLOCKED_RECT8 {
    int Pitch;
    void* pBits;
};

struct D3DSURFACE_DESC8 {
    UINT Format;
    UINT Type;
    DWORD Usage;
    UINT Pool;
    UINT Size;
    UINT MultiSampleType;
    UINT Width;
    UINT Height;
};

struct IMAGE_IMPORT_DESCRIPTOR_MIN {
    DWORD OriginalFirstThunk;
    DWORD TimeDateStamp;
    DWORD ForwarderChain;
    DWORD Name;
    DWORD FirstThunk;
};

struct Config {
    int enabled;
    int resX;
    int resY;
    int fullscreen;
    int borderless;
    int windowPosX;
    int windowPosY;
    int patchRunnerRegion;
    int patchRunnerViews;
    int correctGameProjection;
    int correctPerspective;
    int correctHUD;
    int vignetteMode;
    int letterboxMode;
    int alphaEdgeFix;
    int dualPassAlpha;
    int dualPassAlphaRef;
    int forceMipmaps;
    int mipmapsAlphaTextures;
    int mipmapsAlphaTest;
    int mipmapsAlphaBlend;
    int textureSmoothing;
    int alphaCoveragePreservation;
    int regenerateMipmapsOnUpload;
    int worldTextureUpscale;
    int upscaleMaxDimension;
    int upscaleOpaqueOnly;
    int upscaleTransparentDraws;
    int anisotropicFiltering;
    int maxAnisotropy;
    float mipLODBias;
    int depthPrecisionFix;
    float nearClip;
    float farClip;
    int force24BitDepth;
    int coplanarZBias;
    int coplanarZBiasLayers;
    int mapModelZBias;
    int mapModelZBiasLayers;
    int disableBackfaceCulling;
    int fixDistantBackfaces;
    float mapScaleThreshold;
    int fixDistantObjects;
    int disableInstanceDeactivation;
    float streamingRegionScale;
    int fixParkedVehicleFlicker;
    int stableParkedVehicleModels;
    float parkedVehicleDespawnDistance;
    float parkedSpawnerResetDistance;
    float parkedSpawnMergeRadius;
    int parkedLockUntilRestart;
    float vehicleDensity;
    float npcDensity;
    float vehicleSpawnDistanceScale;
    float npcSpawnDistanceScale;
    int msaaSamples;
    int msaaFallback;
    int logEnabled;
    int logRunnerState;
    float referenceAspect;
    float horizontalFOVScale;
};

struct ViewPatchState {
    BYTE* entry;
    int valid;
    int originalXPort;
    int originalYPort;
    int originalWPort;
    int originalHPort;
    int patchedXPort;
    int patchedYPort;
    int patchedWPort;
    int patchedHPort;
    int originalWView;
    int originalHView;
    int patchedWView;
    int logged;
};

struct TextureInfo {
    void* texture;
    UINT width;
    UINT height;
    UINT format;
    UINT levels;
    BOOL generated;
    BOOL generationFailed;
    BOOL alphaClassified;
    UINT alphaClass; // 1 opaque, 2 cutout, 3 blended
    BOOL skippedAlpha;
    BOOL contentReady;
    BOOL uploadSeen;
    void* replacementTexture;
    BOOL replacementReady;
    BOOL replacementFailed;
    UINT replacementScale;
    void* edgeFixedTexture;
    BOOL edgeFixedReady;
    BOOL edgeFixedFailed;
};

struct SurfaceInfo {
    void* surface;
    void* texture;
    UINT level;
};

static HMODULE g_asiModule = 0;
static BYTE* g_mainBase = 0;
static Config g_cfg;
static ViewPatchState g_views[8];
static char g_iniPath[520];
static char g_logPath[520];
static UINT g_backBufferWidth = 0;
static UINT g_backBufferHeight = 0;
static UINT g_originalBackBufferWidth = 0;
static UINT g_originalBackBufferHeight = 0;
static UINT g_originalRegionWidth = 0;
static UINT g_originalRegionHeight = 0;
static HWND g_gameWindow = 0;
static BOOL g_windowApplied = FALSE;
static BOOL g_runnerCompatible = FALSE;
static BOOL g_regionLogged = FALSE;
static int g_visibleViewCount = 0;
static BOOL g_projectionLogged = FALSE;
static BOOL g_windowSizeLogged = FALSE;
static UINT g_windowRepairCount = 0;
static int g_projectionMode = 0; // 0 unknown, 1 perspective, 2 orthographic
static BOOL g_perspectiveLogged = FALSE;
static BOOL g_orthoLogged = FALSE;
static D3DVIEWPORT8 g_lastRunnerViewport = {0,0,0,0,0.0f,1.0f};
static D3DVIEWPORT8 g_lastFourThreeViewport = {0,0,0,0,0.0f,1.0f};
static BOOL g_haveFourThreeViewport = FALSE;
static BOOL g_rawViewportLogged = FALSE;
static void* g_device = 0;
static void* g_d3dObject = 0;
static BOOL g_vignetteLogged = FALSE;
static BOOL g_letterboxLogged = FALSE;
static BOOL g_textureHooksInstalled = FALSE;
static BOOL g_generatingMipmaps = FALSE;
static UINT g_mipTextureCount = 0;
static UINT g_mipFallbackCount = 0;
static UINT g_generatedMipChains = 0;
static UINT g_mipGenerationFailures = 0;
static BOOL g_mipGenerationLogged = FALSE;
static BOOL g_mipLazyLogged = FALSE;
static BOOL g_mipFailureLogged = FALSE;
static BOOL g_mipCreationLogged = FALSE;
static BOOL g_mipFallbackLogged = FALSE;
static BOOL g_alphaMipSkipLogged = FALSE;
static BOOL g_alphaMipSafeLogged = FALSE;
static BOOL g_surfaceTrackingLogged = FALSE;
static BOOL g_filterStateVerified = FALSE;
static BOOL g_filterStateDirty = TRUE;
static BOOL g_alphaCoverageLogged = FALSE;
static BOOL g_uploadRegenerationLogged = FALSE;
static BOOL g_upscaleLogged = FALSE;
static BOOL g_upscaleFailureLogged = FALSE;
static UINT g_upscaledTextureCount = 0;
static UINT g_stateBlockReapplyCount = 0;
static TextureInfo g_textures[8192];
static int g_textureCount = 0;
static SurfaceInfo g_surfaces[16384];
static int g_surfaceCount = 0;
static void* g_boundTextures[8] = {0,0,0,0,0,0,0,0};
static void* g_requestedTextures[8] = {0,0,0,0,0,0,0,0};
static BOOL g_alphaBlendEnabled = FALSE;
static BOOL g_alphaTestEnabled = FALSE;
static BOOL g_zWriteEnabled = TRUE;
static DWORD g_alphaRef = 128;
static DWORD g_alphaFunc = 7;
static DWORD g_srcBlend = 5;
static DWORD g_destBlend = 6;
static DWORD g_zFunc = 4;
static DWORD g_zBias = 0;
static BOOL g_loggedOpaqueMipDraw = FALSE;
static BOOL g_loggedTransparentSafeDraw = FALSE;
static BOOL g_loggedOpaqueUpscaleDraw = FALSE;
static DWORD g_requestedCullMode = 3;
static UINT g_activeMSAA = 0;
static UINT g_selectedDepthFormat = 0;
static BOOL g_msaaLogged = FALSE;
static BOOL g_depthSurfaceLogged = FALSE;
static BOOL g_depthPrecisionLogged = FALSE;
static BOOL g_twoSidedLogged = FALSE;
static BOOL g_alphaEdgeLogged = FALSE;
static BOOL g_alphaEdgeFailureLogged = FALSE;
static BOOL g_cutoutDetectedLogged = FALSE;
static BOOL g_dualPassLogged = FALSE;
static BOOL g_streamingHookLogged = FALSE;
static BOOL g_streamingAdjustedLogged = FALSE;
static BOOL g_coplanarBiasLogged = FALSE;
static float g_worldMaxElement = 1.0f;
static BOOL g_largeMapTransform = FALSE;
static UINT g_mapDrawSerial = 0;
static BOOL g_mapCullLogged = FALSE;
static BOOL g_mapModelBiasLogged = FALSE;
static BOOL g_backfaceCompletionLogged = FALSE;
static BOOL g_boundTextureSyncLogged = FALSE;
static BOOL g_parkedVehicleHookLogged = FALSE;
static BOOL g_parkedVehicleDestroySuppressedLogged = FALSE;
static BOOL g_parkedVehicleStableModelLogged = FALSE;
static BOOL g_parkedVehicleSingleOccupantLogged = FALSE;
static BOOL g_parkedSpatialAcceptedLogged = FALSE;
static BOOL g_parkedSpatialBlockedLogged = FALSE;
static BOOL g_parkedSpatialKillBackupLogged = FALSE;
static BOOL g_densityHookLogged = FALSE;
static BOOL g_vehicleDensityLogged = FALSE;
static BOOL g_npcDensityLogged = FALSE;
static BOOL g_spawnDistanceLogged = FALSE;
static BOOL g_parkedDistanceProtectedLogged = FALSE;
static BOOL g_distanceHookInstalled = FALSE;
static DWORD g_worldBiasHash = 0;
static UINT g_deviceAdapter = 0;
static UINT g_deviceType = 0;
static UINT g_deviceBackBufferFormat = 22;
static BOOL g_deviceWindowed = FALSE;

// Exact RVAs recovered from the supplied GM8 runner.
static const DWORD RVA_REGION_WIDTH = 0x18D320;
static const DWORD RVA_REGION_HEIGHT = 0x18D324;
static const DWORD RVA_VIEW_MANAGER_HOLDER = 0x18FAC4;
// d3d_set_projection_ext wrapper and the immediate used while registering it.
static const DWORD RVA_GML_PROJECTION_EXT = 0x181704;
static const DWORD RVA_GML_PROJECTION_EXT_REGISTER_MOV = 0x182367;
static const DWORD RVA_GML_DRAW_SPRITE_EXT = 0x154BAC;
static const DWORD RVA_GML_DRAW_SPRITE_EXT_REGISTER_MOV = 0x158129;
static const DWORD RVA_ACTION_DRAW_RECTANGLE = 0x14E57C;
static const DWORD RVA_ACTION_DRAW_RECTANGLE_REGISTER_MOV = 0x14F583;
// instance_deactivate_region registration recovered from the exact runner.
static const DWORD RVA_GML_INSTANCE_DEACTIVATE_REGION = 0x15CB5C;
static const DWORD RVA_GML_INSTANCE_DEACTIVATE_REGION_REGISTER_MOV = 0x15D700;
// d3d_draw_wall / d3d_draw_floor registrations used for optional coplanar Z bias.
static const DWORD RVA_GML_D3D_DRAW_WALL = 0x1815E4;
static const DWORD RVA_GML_D3D_DRAW_WALL_REGISTER_MOV = 0x182325;
static const DWORD RVA_GML_D3D_DRAW_FLOOR = 0x181644;
static const DWORD RVA_GML_D3D_DRAW_FLOOR_REGISTER_MOV = 0x18233B;
// DnD actions used by the parked-vehicle generators and their far-distance cleanup.
static const DWORD RVA_ACTION_KILL_OBJECT = 0x14B91C;
static const DWORD RVA_ACTION_KILL_OBJECT_REGISTER_MOV = 0x14EDA5;
static const DWORD RVA_ACTION_CREATE_OBJECT_RANDOM = 0x14B7CC;
static const DWORD RVA_ACTION_CREATE_OBJECT_RANDOM_REGISTER_MOV = 0x14EDE4;
static const DWORD RVA_ACTION_IF_NUMBER = 0x14C7E0;
static const DWORD RVA_ACTION_IF_NUMBER_REGISTER_MOV = 0x14F168;
static const DWORD RVA_GML_DISTANCE_TO_OBJECT = 0x15B538;
static const DWORD RVA_GML_DISTANCE_TO_OBJECT_REGISTER_MOV = 0x15D328;
static const DWORD EXPECTED_IMAGE_SIZE = 0x364000;
static const int VIGNETTE_SPRITE_INDEX = 6532;

// Direct3D 8 method types.
typedef void* (WINAPI* Direct3DCreate8Fn)(UINT);
typedef HRESULT (WINAPI* CreateDeviceFn)(void*, UINT, UINT, HWND, DWORD, D3DPRESENT_PARAMETERS8*, void**);
typedef HRESULT (WINAPI* CheckDeviceFormatFn)(void*, UINT, UINT, UINT, DWORD, UINT, UINT);
typedef HRESULT (WINAPI* CheckDeviceMultiSampleTypeFn)(void*, UINT, UINT, UINT, BOOL, UINT);
typedef HRESULT (WINAPI* CheckDepthStencilMatchFn)(void*, UINT, UINT, UINT, UINT, UINT);
typedef HRESULT (WINAPI* ResetFn)(void*, D3DPRESENT_PARAMETERS8*);
typedef HRESULT (WINAPI* PresentFn)(void*, const RECTI*, const RECTI*, HWND, const void*);
typedef HRESULT (WINAPI* BeginSceneFn)(void*);
typedef HRESULT (WINAPI* SetTransformFn)(void*, UINT, const D3DMATRIX8*);
typedef HRESULT (WINAPI* SetViewportFn)(void*, const D3DVIEWPORT8*);
typedef HRESULT (WINAPI* GetViewportFn)(void*, D3DVIEWPORT8*);
typedef HRESULT (WINAPI* CreateTextureFn)(void*, UINT, UINT, UINT, DWORD, UINT, UINT, void**);
typedef HRESULT (WINAPI* CreateDepthStencilSurfaceFn)(void*, UINT, UINT, UINT, UINT, void**);
typedef HRESULT (WINAPI* GetTextureFn)(void*, DWORD, void**);
typedef HRESULT (WINAPI* SetTextureFn)(void*, DWORD, void*);
typedef HRESULT (WINAPI* SetTextureStageStateFn)(void*, DWORD, UINT, DWORD);
typedef HRESULT (WINAPI* SetRenderStateFn)(void*, UINT, DWORD);
typedef HRESULT (WINAPI* GetRenderStateFn)(void*, UINT, DWORD*);
typedef HRESULT (WINAPI* DrawPrimitiveFn)(void*, UINT, UINT, UINT);
typedef HRESULT (WINAPI* DrawIndexedPrimitiveFn)(void*, UINT, UINT, UINT, UINT, UINT);
typedef HRESULT (WINAPI* DrawPrimitiveUPFn)(void*, UINT, UINT, const void*, UINT);
typedef HRESULT (WINAPI* DrawIndexedPrimitiveUPFn)(void*, UINT, UINT, UINT, UINT, const void*, UINT, const void*, UINT);
typedef ULONG (WINAPI* ComReleaseFn)(void*);
typedef HRESULT (WINAPI* GetTextureStageStateFn)(void*, DWORD, UINT, DWORD*);
typedef HRESULT (WINAPI* ApplyStateBlockFn)(void*, DWORD);
typedef HRESULT (WINAPI* TextureGetSurfaceLevelFn)(void*, UINT, void**);
typedef void (WINAPI* TexturePreLoadFn)(void*);
typedef HRESULT (WINAPI* SurfaceUnlockRectFn)(void*);
typedef UINT (WINAPI* TextureGetLevelCountFn)(void*);
typedef HRESULT (WINAPI* TextureGetLevelDescFn)(void*, UINT, D3DSURFACE_DESC8*);
typedef HRESULT (WINAPI* TextureLockRectFn)(void*, UINT, D3DLOCKED_RECT8*, const RECTI*, DWORD);
typedef HRESULT (WINAPI* TextureUnlockRectFn)(void*, UINT);
typedef void* GmlFunctionFn;

static Direct3DCreate8Fn g_originalDirect3DCreate8 = 0;
static CreateDeviceFn g_originalCreateDevice = 0;
static CheckDeviceFormatFn g_checkDeviceFormat = 0;
static CheckDeviceMultiSampleTypeFn g_checkDeviceMultiSampleType = 0;
static CheckDepthStencilMatchFn g_checkDepthStencilMatch = 0;
static ResetFn g_originalReset = 0;
static PresentFn g_originalPresent = 0;
static BeginSceneFn g_originalBeginScene = 0;
static SetTransformFn g_originalSetTransform = 0;
static SetViewportFn g_originalSetViewport = 0;
static GetViewportFn g_originalGetViewport = 0;
static CreateTextureFn g_originalCreateTexture = 0;
static CreateDepthStencilSurfaceFn g_originalCreateDepthStencilSurface = 0;
static GetTextureFn g_originalGetTexture = 0;
static SetTextureFn g_originalSetTexture = 0;
static SetTextureStageStateFn g_originalSetTextureStageState = 0;
static GetTextureStageStateFn g_originalGetTextureStageState = 0;
static ApplyStateBlockFn g_originalApplyStateBlock = 0;
static SetRenderStateFn g_originalSetRenderState = 0;
static GetRenderStateFn g_originalGetRenderState = 0;
static DrawPrimitiveFn g_originalDrawPrimitive = 0;
static DrawIndexedPrimitiveFn g_originalDrawIndexedPrimitive = 0;
static DrawPrimitiveUPFn g_originalDrawPrimitiveUP = 0;
static DrawIndexedPrimitiveUPFn g_originalDrawIndexedPrimitiveUP = 0;
static TextureGetLevelCountFn g_textureGetLevelCount = 0;
static TextureGetLevelDescFn g_textureGetLevelDesc = 0;
static TextureLockRectFn g_textureLockRect = 0;
static TextureUnlockRectFn g_originalTextureUnlockRect = 0;
static TextureGetSurfaceLevelFn g_originalTextureGetSurfaceLevel = 0;
static TexturePreLoadFn g_texturePreLoad = 0;
static SurfaceUnlockRectFn g_originalSurfaceUnlockRect = 0;
static GmlFunctionFn g_originalGmlProjectionExt = 0;
static GmlFunctionFn g_originalDrawSpriteExt = 0;
static GmlFunctionFn g_originalActionDrawRectangle = 0;
static GmlFunctionFn g_originalInstanceDeactivateRegion = 0;
static GmlFunctionFn g_originalD3DDrawWall = 0;
static GmlFunctionFn g_originalD3DDrawFloor = 0;
static GmlFunctionFn g_originalActionKillObject = 0;
static GmlFunctionFn g_originalActionCreateObjectRandom = 0;
static GmlFunctionFn g_originalActionIfNumber = 0;
static GmlFunctionFn g_originalDistanceToObject = 0;
static GmlFunctionFn g_distanceToObject = 0;

static BOOL CurrentDrawAllowsMipmaps();
static BOOL CurrentDrawAllowsUpscale();
static void RefreshTransparencyRenderStates(void* device);

static int StrLen(const char* s) {
    int n = 0;
    if (!s) return 0;
    while (s[n]) ++n;
    return n;
}

static char LowerAscii(char c) {
    if (c >= 'A' && c <= 'Z') return (char)(c + ('a' - 'A'));
    return c;
}

static bool StrEqualI(const char* a, const char* b) {
    if (!a || !b) return false;
    while (*a && *b) {
        if (LowerAscii(*a) != LowerAscii(*b)) return false;
        ++a; ++b;
    }
    return *a == 0 && *b == 0;
}

static void StrCopy(char* dst, int cap, const char* src) {
    if (!dst || cap <= 0) return;
    int i = 0;
    if (src) {
        while (src[i] && i < cap - 1) { dst[i] = src[i]; ++i; }
    }
    dst[i] = 0;
}

static void ReplaceFileName(char* path, int cap, const char* fileName) {
    int len = StrLen(path);
    int pos = len;
    while (pos > 0 && path[pos - 1] != '\\' && path[pos - 1] != '/') --pos;
    int j = 0;
    while (fileName[j] && pos < cap - 1) path[pos++] = fileName[j++];
    path[pos] = 0;
}

static float AbsF(float v) { return v < 0.0f ? -v : v; }
static int AbsI(int v) { return v < 0 ? -v : v; }
static int RoundToInt(float v) { return v >= 0.0f ? (int)(v + 0.5f) : (int)(v - 0.5f); }
static int FloorToInt(float v) { int i = (int)v; return ((float)i > v) ? i - 1 : i; }
static int ClampI(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }
static float ClampF(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }
static BYTE ClampByteF(float v) { int i = RoundToInt(v); return (BYTE)ClampI(i, 0, 255); }
static float CubicWeight(float x) {
    x = AbsF(x);
    if (x <= 1.0f) return (1.5f * x - 2.5f) * x * x + 1.0f;
    if (x < 2.0f) return ((-0.5f * x + 2.5f) * x - 4.0f) * x + 2.0f;
    return 0.0f;
}

static bool PlausibleDimension(int v) { return v >= 64 && v <= 16384; }

static float ParseFloat(const char* s, float fallback) {
    if (!s) return fallback;
    while (*s == ' ' || *s == '\t') ++s;
    float sign = 1.0f;
    if (*s == '-') { sign = -1.0f; ++s; }
    else if (*s == '+') { ++s; }
    float value = 0.0f;
    bool any = false;
    while (*s >= '0' && *s <= '9') {
        any = true;
        value = value * 10.0f + (float)(*s - '0');
        ++s;
    }
    if (*s == '.' || *s == ',') {
        ++s;
        float place = 0.1f;
        while (*s >= '0' && *s <= '9') {
            any = true;
            value += (float)(*s - '0') * place;
            place *= 0.1f;
            ++s;
        }
    }
    return any ? value * sign : fallback;
}

static void UIntToText(UINT v, char* out, int cap) {
    if (cap <= 0) return;
    char tmp[16];
    int n = 0;
    do { tmp[n++] = (char)('0' + (v % 10)); v /= 10; } while (v && n < 15);
    int p = 0;
    while (n > 0 && p < cap - 1) out[p++] = tmp[--n];
    out[p] = 0;
}

static void IntToText(int v, char* out, int cap) {
    if (cap <= 0) return;
    if (v < 0) {
        out[0] = '-';
        UINT magnitude = (UINT)(-(v + 1)) + 1;
        UIntToText(magnitude, out + 1, cap - 1);
    } else {
        UIntToText((UINT)v, out, cap);
    }
}

static void AppendText(char* dst, int cap, int* pos, const char* src) {
    if (!dst || !pos || !src) return;
    while (*src && *pos < cap - 1) dst[(*pos)++] = *src++;
    dst[*pos] = 0;
}

static void LogRaw(const char* text) {
    OutputDebugStringA(text);
    if (!g_cfg.logEnabled || !g_logPath[0]) return;
    HANDLE f = CreateFileA(g_logPath, GENERIC_WRITE, FILE_SHARE_READ, 0, 4, FILE_ATTRIBUTE_NORMAL, 0);
    if (f == INVALID_HANDLE_VALUE) return;
    SetFilePointer(f, 0, 0, FILE_END);
    DWORD written = 0;
    WriteFile(f, text, (DWORD)StrLen(text), &written, 0);
    CloseHandle(f);
}

static void CreateInitialLog(const char* text) {
    OutputDebugStringA(text);
    if (!g_cfg.logEnabled || !g_logPath[0]) return;
    HANDLE f = CreateFileA(g_logPath, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (f == INVALID_HANDLE_VALUE) return;
    DWORD written = 0;
    WriteFile(f, text, (DWORD)StrLen(text), &written, 0);
    CloseHandle(f);
}

static void LogResolution(const char* prefix, UINT w, UINT h) {
    char a[16], b[16], buf[192];
    UIntToText(w, a, 16); UIntToText(h, b, 16);
    int p = 0; buf[0] = 0;
    AppendText(buf, 192, &p, prefix);
    AppendText(buf, 192, &p, a);
    AppendText(buf, 192, &p, "x");
    AppendText(buf, 192, &p, b);
    AppendText(buf, 192, &p, "\r\n");
    LogRaw(buf);
}

static void LogView(int index, int wView, int hView, int wPort, int hPort, int newWView, int newWPort, int newHPort) {
    char i[12], a[16], b[16], c[16], d[16], e[16], f[16], g[16], buf[320];
    IntToText(index, i, 12);
    IntToText(wView, a, 16); IntToText(hView, b, 16);
    IntToText(wPort, c, 16); IntToText(hPort, d, 16);
    IntToText(newWView, e, 16); IntToText(newWPort, f, 16); IntToText(newHPort, g, 16);
    int p = 0; buf[0] = 0;
    AppendText(buf, 320, &p, "[Runner] View "); AppendText(buf, 320, &p, i);
    AppendText(buf, 320, &p, ": world "); AppendText(buf, 320, &p, a); AppendText(buf, 320, &p, "x"); AppendText(buf, 320, &p, b);
    AppendText(buf, 320, &p, ", port "); AppendText(buf, 320, &p, c); AppendText(buf, 320, &p, "x"); AppendText(buf, 320, &p, d);
    AppendText(buf, 320, &p, " -> world "); AppendText(buf, 320, &p, e);
    AppendText(buf, 320, &p, "x"); AppendText(buf, 320, &p, b);
    AppendText(buf, 320, &p, ", port "); AppendText(buf, 320, &p, f); AppendText(buf, 320, &p, "x"); AppendText(buf, 320, &p, g);
    AppendText(buf, 320, &p, "\r\n");
    LogRaw(buf);
}

static float ReadFloat(const char* section, const char* key, float fallback) {
    char buf[64];
    GetPrivateProfileStringA(section, key, "", buf, 64, g_iniPath);
    return ParseFloat(buf, fallback);
}

static void LoadConfig() {
    StrCopy(g_iniPath, 520, "");
    GetModuleFileNameA(g_asiModule, g_iniPath, 519);
    ReplaceFileName(g_iniPath, 520, "Crimelife3.WidescreenFix.ini");
    StrCopy(g_logPath, 520, g_iniPath);
    ReplaceFileName(g_logPath, 520, "Crimelife3.WidescreenFix.log");

    g_cfg.enabled = GetPrivateProfileIntA("MAIN", "Enabled", 1, g_iniPath);
    g_cfg.resX = GetPrivateProfileIntA("DISPLAY", "ResX", 0, g_iniPath);
    g_cfg.resY = GetPrivateProfileIntA("DISPLAY", "ResY", 0, g_iniPath);
    g_cfg.fullscreen = GetPrivateProfileIntA("DISPLAY", "Fullscreen", -1, g_iniPath);
    g_cfg.borderless = GetPrivateProfileIntA("DISPLAY", "Borderless", 1, g_iniPath);
    g_cfg.windowPosX = GetPrivateProfileIntA("DISPLAY", "WindowPosX", -1, g_iniPath);
    g_cfg.windowPosY = GetPrivateProfileIntA("DISPLAY", "WindowPosY", -1, g_iniPath);
    g_cfg.patchRunnerRegion = GetPrivateProfileIntA("WIDESCREEN", "PatchRunnerRegion", 0, g_iniPath);
    g_cfg.patchRunnerViews = GetPrivateProfileIntA("WIDESCREEN", "PatchRunnerViews", 0, g_iniPath);
    g_cfg.correctGameProjection = GetPrivateProfileIntA("WIDESCREEN", "CorrectGameProjection", 0, g_iniPath);
    g_cfg.correctPerspective = GetPrivateProfileIntA("WIDESCREEN", "CorrectPerspective", 1, g_iniPath);
    g_cfg.correctHUD = GetPrivateProfileIntA("WIDESCREEN", "CorrectHUD", 1, g_iniPath);
    g_cfg.vignetteMode = GetPrivateProfileIntA("OVERLAYS", "VignetteMode", 1, g_iniPath);
    g_cfg.letterboxMode = GetPrivateProfileIntA("OVERLAYS", "LetterboxMode", 1, g_iniPath);
    g_cfg.alphaEdgeFix = GetPrivateProfileIntA("ALPHA", "EdgeColorFix", 1, g_iniPath);
    g_cfg.dualPassAlpha = GetPrivateProfileIntA("ALPHA", "DualPass", 1, g_iniPath);
    g_cfg.dualPassAlphaRef = GetPrivateProfileIntA("ALPHA", "DualPassAlphaRef", 128, g_iniPath);
    g_cfg.forceMipmaps = GetPrivateProfileIntA("GRAPHICS", "ForceMipmaps", 1, g_iniPath);
    g_cfg.mipmapsAlphaTextures = GetPrivateProfileIntA("GRAPHICS", "MipmapsAlphaTextures", 1, g_iniPath);
    g_cfg.mipmapsAlphaTest = GetPrivateProfileIntA("GRAPHICS", "MipmapsAlphaTest", 0, g_iniPath);
    g_cfg.mipmapsAlphaBlend = GetPrivateProfileIntA("GRAPHICS", "MipmapsAlphaBlend", 0, g_iniPath);
    g_cfg.textureSmoothing = GetPrivateProfileIntA("GRAPHICS", "TextureSmoothing", 1, g_iniPath);
    g_cfg.alphaCoveragePreservation = GetPrivateProfileIntA("GRAPHICS", "AlphaCoveragePreservation", 1, g_iniPath);
    g_cfg.regenerateMipmapsOnUpload = GetPrivateProfileIntA("GRAPHICS", "RegenerateMipmapsOnUpload", 1, g_iniPath);
    g_cfg.worldTextureUpscale = GetPrivateProfileIntA("GRAPHICS", "WorldTextureUpscale", 2, g_iniPath);
    g_cfg.upscaleMaxDimension = GetPrivateProfileIntA("GRAPHICS", "UpscaleMaxDimension", 256, g_iniPath);
    g_cfg.upscaleOpaqueOnly = GetPrivateProfileIntA("GRAPHICS", "UpscaleOpaqueOnly", 0, g_iniPath);
    g_cfg.upscaleTransparentDraws = GetPrivateProfileIntA("GRAPHICS", "UpscaleTransparentDraws", 0, g_iniPath);
    g_cfg.anisotropicFiltering = GetPrivateProfileIntA("GRAPHICS", "AnisotropicFiltering", 1, g_iniPath);
    g_cfg.maxAnisotropy = GetPrivateProfileIntA("GRAPHICS", "MaxAnisotropy", 16, g_iniPath);
    g_cfg.mipLODBias = ReadFloat("GRAPHICS", "MipLODBias", 0.0f);
    g_cfg.depthPrecisionFix = GetPrivateProfileIntA("DEPTH", "DepthPrecisionFix", 1, g_iniPath);
    g_cfg.nearClip = ReadFloat("DEPTH", "NearClip", 3.0f);
    g_cfg.farClip = ReadFloat("DEPTH", "FarClip", 0.0f);
    g_cfg.force24BitDepth = GetPrivateProfileIntA("DEPTH", "Force24BitDepth", 1, g_iniPath);
    g_cfg.coplanarZBias = GetPrivateProfileIntA("DEPTH", "CoplanarZBias", 0, g_iniPath);
    g_cfg.coplanarZBiasLayers = GetPrivateProfileIntA("DEPTH", "CoplanarZBiasLayers", 4, g_iniPath);
    g_cfg.mapModelZBias = GetPrivateProfileIntA("DEPTH", "MapModelZBias", 1, g_iniPath);
    g_cfg.mapModelZBiasLayers = GetPrivateProfileIntA("DEPTH", "MapModelZBiasLayers", 8, g_iniPath);
    g_cfg.disableBackfaceCulling = GetPrivateProfileIntA("GEOMETRY", "DisableBackfaceCulling", 0, g_iniPath);
    g_cfg.fixDistantBackfaces = GetPrivateProfileIntA("GEOMETRY", "FixDistantBackfaces", 1, g_iniPath);
    g_cfg.mapScaleThreshold = ReadFloat("GEOMETRY", "MapScaleThreshold", 100.0f);
    g_cfg.fixDistantObjects = GetPrivateProfileIntA("STREAMING", "FixDistantObjects", 0, g_iniPath);
    g_cfg.disableInstanceDeactivation = GetPrivateProfileIntA("STREAMING", "DisableInstanceDeactivation", 0, g_iniPath);
    g_cfg.streamingRegionScale = ReadFloat("STREAMING", "RegionScale", 0.0f);
    g_cfg.fixParkedVehicleFlicker = GetPrivateProfileIntA("VEHICLE_SPAWNING", "FixParkedVehicleFlicker", 1, g_iniPath);
    g_cfg.stableParkedVehicleModels = GetPrivateProfileIntA("VEHICLE_SPAWNING", "StableParkedVehicleModels", 1, g_iniPath);
    g_cfg.parkedVehicleDespawnDistance = ReadFloat("VEHICLE_SPAWNING", "ParkedVehicleDespawnDistance", 20000.0f);
    g_cfg.parkedSpawnerResetDistance = ReadFloat("VEHICLE_SPAWNING", "ParkedSpawnerResetDistance", 0.0f);
    g_cfg.parkedSpawnMergeRadius = ReadFloat("VEHICLE_SPAWNING", "ParkedSpawnMergeRadius", 24.0f);
    g_cfg.parkedLockUntilRestart = GetPrivateProfileIntA("VEHICLE_SPAWNING", "ParkedLockUntilRestart", 1, g_iniPath);
    g_cfg.vehicleDensity = ReadFloat("DENSITY", "VehicleDensity", 1.0f);
    g_cfg.npcDensity = ReadFloat("DENSITY", "NPCDensity", 1.0f);
    g_cfg.vehicleSpawnDistanceScale = ReadFloat("SPAWN_DISTANCE", "VehicleSpawnDistanceScale", 2.0f);
    g_cfg.npcSpawnDistanceScale = ReadFloat("SPAWN_DISTANCE", "NPCSpawnDistanceScale", 2.0f);
    g_cfg.msaaSamples = GetPrivateProfileIntA("ANTIALIASING", "MSAA", 4, g_iniPath);
    g_cfg.msaaFallback = GetPrivateProfileIntA("ANTIALIASING", "Fallback", 1, g_iniPath);
    g_cfg.referenceAspect = ReadFloat("WIDESCREEN", "ReferenceAspect", 1.3333333f);
    g_cfg.horizontalFOVScale = ReadFloat("WIDESCREEN", "HorizontalFOVScale", 1.0f);
    g_cfg.logEnabled = GetPrivateProfileIntA("DEBUG", "Log", 1, g_iniPath);
    g_cfg.logRunnerState = GetPrivateProfileIntA("DEBUG", "LogRunnerState", 1, g_iniPath);

    if (g_cfg.resX <= 0) g_cfg.resX = GetSystemMetrics(SM_CXSCREEN);
    if (g_cfg.resY <= 0) g_cfg.resY = GetSystemMetrics(SM_CYSCREEN);
    if (g_cfg.resX < 320) g_cfg.resX = 320;
    if (g_cfg.resY < 200) g_cfg.resY = 200;
    if (g_cfg.referenceAspect < 0.5f) g_cfg.referenceAspect = 1.3333333f;
    if (g_cfg.horizontalFOVScale < 0.25f) g_cfg.horizontalFOVScale = 0.25f;
    if (g_cfg.horizontalFOVScale > 4.0f) g_cfg.horizontalFOVScale = 4.0f;
    if (g_cfg.vignetteMode < 0 || g_cfg.vignetteMode > 2) g_cfg.vignetteMode = 1;
    if (g_cfg.letterboxMode < 0 || g_cfg.letterboxMode > 2) g_cfg.letterboxMode = 1;
    if (g_cfg.dualPassAlphaRef < 1) g_cfg.dualPassAlphaRef = 1;
    if (g_cfg.dualPassAlphaRef > 254) g_cfg.dualPassAlphaRef = 254;
    if (g_cfg.coplanarZBiasLayers < 1) g_cfg.coplanarZBiasLayers = 1;
    if (g_cfg.coplanarZBiasLayers > 16) g_cfg.coplanarZBiasLayers = 16;
    if (g_cfg.mapModelZBiasLayers < 1) g_cfg.mapModelZBiasLayers = 1;
    if (g_cfg.mapModelZBiasLayers > 16) g_cfg.mapModelZBiasLayers = 16;
    if (g_cfg.mapScaleThreshold < 10.0f) g_cfg.mapScaleThreshold = 10.0f;
    if (g_cfg.mapScaleThreshold > 1000.0f) g_cfg.mapScaleThreshold = 1000.0f;
    if (g_cfg.streamingRegionScale < 0.0f) g_cfg.streamingRegionScale = 0.0f;
    if (g_cfg.streamingRegionScale > 8.0f) g_cfg.streamingRegionScale = 8.0f;
    if (g_cfg.parkedVehicleDespawnDistance < 1100.0f) g_cfg.parkedVehicleDespawnDistance = 1100.0f;
    if (g_cfg.parkedVehicleDespawnDistance > 20000.0f) g_cfg.parkedVehicleDespawnDistance = 20000.0f;
    if (g_cfg.parkedSpawnerResetDistance < 0.0f) g_cfg.parkedSpawnerResetDistance = 0.0f;
    if (g_cfg.parkedSpawnerResetDistance > 690.0f) g_cfg.parkedSpawnerResetDistance = 690.0f;
    if (g_cfg.parkedSpawnMergeRadius < 2.0f) g_cfg.parkedSpawnMergeRadius = 2.0f;
    if (g_cfg.parkedSpawnMergeRadius > 128.0f) g_cfg.parkedSpawnMergeRadius = 128.0f;
    g_cfg.parkedLockUntilRestart = g_cfg.parkedLockUntilRestart ? 1 : 0;
    if (g_cfg.vehicleDensity < 0.25f) g_cfg.vehicleDensity = 0.25f;
    if (g_cfg.vehicleDensity > 16.0f) g_cfg.vehicleDensity = 16.0f;
    if (g_cfg.npcDensity < 0.25f) g_cfg.npcDensity = 0.25f;
    if (g_cfg.npcDensity > 16.0f) g_cfg.npcDensity = 16.0f;
    if (g_cfg.vehicleSpawnDistanceScale < 1.0f) g_cfg.vehicleSpawnDistanceScale = 1.0f;
    if (g_cfg.vehicleSpawnDistanceScale > 16.0f) g_cfg.vehicleSpawnDistanceScale = 16.0f;
    if (g_cfg.npcSpawnDistanceScale < 1.0f) g_cfg.npcSpawnDistanceScale = 1.0f;
    if (g_cfg.npcSpawnDistanceScale > 16.0f) g_cfg.npcSpawnDistanceScale = 16.0f;
    if (g_cfg.worldTextureUpscale != 1 && g_cfg.worldTextureUpscale != 2 && g_cfg.worldTextureUpscale != 4) g_cfg.worldTextureUpscale = 2;
    if (g_cfg.upscaleMaxDimension < 16) g_cfg.upscaleMaxDimension = 16;
    if (g_cfg.upscaleMaxDimension > 1024) g_cfg.upscaleMaxDimension = 1024;
    if (g_cfg.maxAnisotropy < 1) g_cfg.maxAnisotropy = 1;
    if (g_cfg.maxAnisotropy > 16) g_cfg.maxAnisotropy = 16;
    if (g_cfg.mipLODBias < -4.0f) g_cfg.mipLODBias = -4.0f;
    if (g_cfg.mipLODBias > 4.0f) g_cfg.mipLODBias = 4.0f;
    if (g_cfg.nearClip < 0.05f) g_cfg.nearClip = 0.05f;
    if (g_cfg.nearClip > 100.0f) g_cfg.nearClip = 100.0f;
    if (g_cfg.farClip < 0.0f) g_cfg.farClip = 0.0f;
    if (g_cfg.farClip > 100000.0f) g_cfg.farClip = 100000.0f;
    if (g_cfg.msaaSamples != 0 && g_cfg.msaaSamples != 2 && g_cfg.msaaSamples != 4 && g_cfg.msaaSamples != 8) g_cfg.msaaSamples = 4;
}

static bool IsReadable(const void* address, DWORD bytes) {
    if (!address || bytes == 0) return false;
    MEMORY_BASIC_INFORMATION32 mbi;
    SIZE_T got = VirtualQuery(address, &mbi, sizeof(mbi));
    if (got < sizeof(mbi)) return false;
    if (mbi.State != MEM_COMMIT) return false;
    if ((mbi.Protect & PAGE_NOACCESS) || (mbi.Protect & PAGE_GUARD)) return false;
    const BYTE* start = (const BYTE*)address;
    const BYTE* regionStart = (const BYTE*)mbi.BaseAddress;
    const BYTE* regionEnd = regionStart + mbi.RegionSize;
    return start >= regionStart && start + bytes <= regionEnd;
}

static bool MatchBytes(const BYTE* address, const BYTE* signature, int count) {
    if (!IsReadable(address, (DWORD)count)) return false;
    for (int i = 0; i < count; ++i) if (address[i] != signature[i]) return false;
    return true;
}

static void InitRunnerCompatibility() {
    g_mainBase = (BYTE*)GetModuleHandleA(0);
    if (!g_mainBase || !IsReadable(g_mainBase, 0x1000)) return;
    if (g_mainBase[0] != 'M' || g_mainBase[1] != 'Z') return;
    DWORD peOffset = *(DWORD*)(g_mainBase + 0x3C);
    BYTE* nt = g_mainBase + peOffset;
    if (!IsReadable(nt, 0x100) || nt[0] != 'P' || nt[1] != 'E') return;
    BYTE* optional = nt + 24;
    DWORD imageSize = *(DWORD*)(optional + 56);
    static const BYTE regionFunctionSignature[6] = {0x53, 0x56, 0x8B, 0xD9, 0x85, 0xC0};
    if (imageSize == EXPECTED_IMAGE_SIZE && MatchBytes(g_mainBase + 0x9B3F8, regionFunctionSignature, 6)) {
        g_runnerCompatible = TRUE;
        LogRaw("Exact Crimelife 3 GameMaker runner detected.\r\n");
    } else {
        LogRaw("WARNING: executable signature differs; internal runner patch disabled.\r\n");
    }
}

static bool PatchPointer(void** slot, void* replacement, void** original) {
    if (!slot || !replacement) return false;
    if (*slot == replacement) return true;
    DWORD oldProtect = 0;
    if (!VirtualProtect(slot, 4, PAGE_EXECUTE_READWRITE, &oldProtect)) return false;
    if (original && !*original) *original = *slot;
    *slot = replacement;
    FlushInstructionCache(GetCurrentProcess(), slot, 4);
    DWORD ignored = 0;
    VirtualProtect(slot, 4, oldProtect, &ignored);
    return true;
}

static bool PatchVTable(void* object, int index, void* replacement, void** original) {
    if (!object) return false;
    void*** asObject = (void***)object;
    if (!*asObject) return false;
    return PatchPointer(&((*asObject)[index]), replacement, original);
}


static void LogMSAASelection(UINT requested, UINT active, UINT depthFormat) {
    if (!g_cfg.logRunnerState || g_msaaLogged) return;
    char a[16], b[16], c[16], buf[256];
    IntToText((int)requested, a, 16);
    IntToText((int)active, b, 16);
    IntToText((int)depthFormat, c, 16);
    int p = 0; buf[0] = 0;
    AppendText(buf, 256, &p, "[MSAA] requested="); AppendText(buf, 256, &p, a);
    AppendText(buf, 256, &p, " active="); AppendText(buf, 256, &p, b);
    AppendText(buf, 256, &p, " depthFormat="); AppendText(buf, 256, &p, c);
    AppendText(buf, 256, &p, "\r\n");
    LogRaw(buf);
    g_msaaLogged = TRUE;
}

static bool CheckDepthFormatForMode(void* d3d, UINT adapter, UINT deviceType, UINT adapterFormat,
                                    UINT renderFormat, UINT depthFormat, BOOL windowed, UINT multisample) {
    if (!d3d || !g_checkDeviceFormat || !g_checkDepthStencilMatch) return false;
    const DWORD D3DUSAGE_DEPTHSTENCIL_VALUE = 0x00000002UL;
    const UINT D3DRTYPE_SURFACE_VALUE = 1;
    if (g_checkDeviceFormat(d3d, adapter, deviceType, adapterFormat,
                            D3DUSAGE_DEPTHSTENCIL_VALUE, D3DRTYPE_SURFACE_VALUE, depthFormat) < 0) return false;
    if (g_checkDepthStencilMatch(d3d, adapter, deviceType, adapterFormat, renderFormat, depthFormat) < 0) return false;
    if (multisample && g_checkDeviceMultiSampleType &&
        g_checkDeviceMultiSampleType(d3d, adapter, deviceType, depthFormat, windowed, multisample) < 0) return false;
    return true;
}

static UINT SelectDepthFormat(void* d3d, UINT adapter, UINT deviceType, D3DPRESENT_PARAMETERS8* pp, UINT multisample) {
    if (!pp) return 0;
    UINT adapterFormat = pp->BackBufferFormat ? pp->BackBufferFormat : 22;
    UINT renderFormat = pp->BackBufferFormat ? pp->BackBufferFormat : 22;
    const UINT D3DFMT_D24S8_VALUE = 75;
    const UINT D3DFMT_D24X8_VALUE = 77;
    const UINT D3DFMT_D16_VALUE = 80;

    if (g_cfg.force24BitDepth) {
        if (CheckDepthFormatForMode(d3d, adapter, deviceType, adapterFormat, renderFormat,
                                    D3DFMT_D24S8_VALUE, pp->Windowed, multisample)) return D3DFMT_D24S8_VALUE;
        if (CheckDepthFormatForMode(d3d, adapter, deviceType, adapterFormat, renderFormat,
                                    D3DFMT_D24X8_VALUE, pp->Windowed, multisample)) return D3DFMT_D24X8_VALUE;
    }
    if (CheckDepthFormatForMode(d3d, adapter, deviceType, adapterFormat, renderFormat,
                                D3DFMT_D16_VALUE, pp->Windowed, multisample)) return D3DFMT_D16_VALUE;
    return 0;
}

static UINT SelectSupportedMSAA(void* d3d, UINT adapter, UINT deviceType, D3DPRESENT_PARAMETERS8* pp) {
    if (!pp || g_cfg.msaaSamples <= 1 || !g_checkDeviceMultiSampleType) return 0;
    UINT candidates[3] = {0, 0, 0};
    int count = 0;
    candidates[count++] = (UINT)g_cfg.msaaSamples;
    if (g_cfg.msaaFallback) {
        if (g_cfg.msaaSamples > 4) candidates[count++] = 4;
        if (g_cfg.msaaSamples > 2) candidates[count++] = 2;
    }
    for (int i = 0; i < count; ++i) {
        UINT samples = candidates[i];
        if (!samples) continue;
        if (g_checkDeviceMultiSampleType(d3d, adapter, deviceType,
                                         pp->BackBufferFormat ? pp->BackBufferFormat : 22,
                                         pp->Windowed, samples) < 0) continue;
        UINT depthFormat = SelectDepthFormat(d3d, adapter, deviceType, pp, samples);
        if (!depthFormat) continue;
        g_selectedDepthFormat = depthFormat;
        return samples;
    }
    g_selectedDepthFormat = SelectDepthFormat(d3d, adapter, deviceType, pp, 0);
    return 0;
}

static void ConfigureDepthAndMSAA(void* d3d, UINT adapter, UINT deviceType, D3DPRESENT_PARAMETERS8* pp) {
    if (!pp) return;
    g_selectedDepthFormat = 0;
    g_activeMSAA = SelectSupportedMSAA(d3d, adapter, deviceType, pp);
    if (!g_selectedDepthFormat) g_selectedDepthFormat = SelectDepthFormat(d3d, adapter, deviceType, pp, g_activeMSAA);
    if (g_activeMSAA) {
        // D3D8 requires DISCARD swap effect for multisampled swap chains.
        pp->MultiSampleType = g_activeMSAA;
        pp->SwapEffect = 1;
        pp->BackBufferCount = 1;
    } else {
        pp->MultiSampleType = 0;
    }
    if (pp->EnableAutoDepthStencil && g_selectedDepthFormat) pp->AutoDepthStencilFormat = g_selectedDepthFormat;
    LogMSAASelection((UINT)g_cfg.msaaSamples, g_activeMSAA, g_selectedDepthFormat);
}

static void ApplyConfiguredPresentParameters(D3DPRESENT_PARAMETERS8* pp) {
    if (!pp) return;
    if (g_originalBackBufferWidth == 0) g_originalBackBufferWidth = pp->BackBufferWidth;
    if (g_originalBackBufferHeight == 0) g_originalBackBufferHeight = pp->BackBufferHeight;

    pp->BackBufferWidth = (UINT)g_cfg.resX;
    pp->BackBufferHeight = (UINT)g_cfg.resY;

    if (g_cfg.fullscreen == 0) {
        pp->Windowed = TRUE;
        pp->FullScreen_RefreshRateInHz = 0;
    } else if (g_cfg.fullscreen == 1) {
        pp->Windowed = FALSE;
        pp->FullScreen_RefreshRateInHz = 0;
        if (pp->BackBufferFormat == 0) pp->BackBufferFormat = 22;
    }

    g_backBufferWidth = pp->BackBufferWidth;
    g_backBufferHeight = pp->BackBufferHeight;
    if (pp->hDeviceWindow) g_gameWindow = pp->hDeviceWindow;
}

static bool ClientMatchesTarget() {
    if (!g_gameWindow || !g_backBufferWidth || !g_backBufferHeight) return false;
    RECTI client = {0, 0, 0, 0};
    if (!GetClientRect(g_gameWindow, &client)) return false;
    int width = (int)(client.right - client.left);
    int height = (int)(client.bottom - client.top);
    return width == (int)g_backBufferWidth && height == (int)g_backBufferHeight;
}

static void LogWindowClient(const char* prefix) {
    if (!g_gameWindow || !g_cfg.logRunnerState) return;
    RECTI client = {0, 0, 0, 0};
    if (!GetClientRect(g_gameWindow, &client)) return;
    LogResolution(prefix, (UINT)(client.right - client.left), (UINT)(client.bottom - client.top));
}

static void ApplyWindowMode() {
    if (!g_gameWindow || !g_backBufferWidth || !g_backBufferHeight) return;

    DWORD desiredStyle;
    int x = g_cfg.windowPosX;
    int y = g_cfg.windowPosY;
    int width = (int)g_backBufferWidth;
    int height = (int)g_backBufferHeight;

    if (g_cfg.fullscreen == 1 || g_cfg.borderless) {
        desiredStyle = WS_POPUP | WS_VISIBLE;
        if (x < 0) x = 0;
        if (y < 0) y = 0;
    } else {
        desiredStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
        RECTI r = {0, 0, width, height};
        DWORD exStyle = (DWORD)GetWindowLongA(g_gameWindow, GWL_EXSTYLE);
        AdjustWindowRectEx(&r, desiredStyle, FALSE, exStyle);
        width = (int)(r.right - r.left);
        height = (int)(r.bottom - r.top);
        if (x < 0) x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
        if (y < 0) y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    }

    DWORD currentStyle = (DWORD)GetWindowLongA(g_gameWindow, GWL_STYLE);
    bool styleWrong = (currentStyle & (WS_POPUP | WS_OVERLAPPEDWINDOW)) !=
                      (desiredStyle & (WS_POPUP | WS_OVERLAPPEDWINDOW));
    bool sizeWrong = !ClientMatchesTarget();

    // GameMaker 8 can resize the game window again after CreateDevice when a
    // room is entered. v0.3 only resized once, so the 3440x1440 backbuffer was
    // clipped by the restored 1024x768 client. Re-check on every Present and
    // repair only when the runner changed it.
    if (styleWrong) SetWindowLongA(g_gameWindow, GWL_STYLE, (LONG)desiredStyle);
    if (styleWrong || sizeWrong || !g_windowApplied) {
        SetWindowPos(g_gameWindow, 0, x, y, width, height, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
        ++g_windowRepairCount;
        if (!g_windowSizeLogged || g_windowRepairCount <= 3) {
            LogWindowClient("[Window] Client after repair: ");
            g_windowSizeLogged = TRUE;
        }
    }
    g_windowApplied = TRUE;
}

static void PatchRunnerRegion() {
    if (!g_runnerCompatible || !g_cfg.patchRunnerRegion || !g_mainBase) return;
    int* regionWidth = (int*)(g_mainBase + RVA_REGION_WIDTH);
    int* regionHeight = (int*)(g_mainBase + RVA_REGION_HEIGHT);
    if (!IsReadable(regionWidth, 8)) return;

    int currentW = *regionWidth;
    int currentH = *regionHeight;
    if (PlausibleDimension(currentW) && PlausibleDimension(currentH) &&
        (currentW != g_cfg.resX || currentH != g_cfg.resY)) {
        g_originalRegionWidth = (UINT)currentW;
        g_originalRegionHeight = (UINT)currentH;
    }

    if (!g_originalRegionWidth && PlausibleDimension((int)g_originalBackBufferWidth) && PlausibleDimension((int)g_originalBackBufferHeight)) {
        g_originalRegionWidth = g_originalBackBufferWidth;
        g_originalRegionHeight = g_originalBackBufferHeight;
    }

    *regionWidth = g_cfg.resX;
    *regionHeight = g_cfg.resY;

    if (!g_regionLogged && g_cfg.logRunnerState && g_originalRegionWidth && g_originalRegionHeight) {
        LogResolution("[Runner] Original drawing region: ", g_originalRegionWidth, g_originalRegionHeight);
        LogResolution("[Runner] Patched drawing region: ", (UINT)g_cfg.resX, (UINT)g_cfg.resY);
        g_regionLogged = TRUE;
    }
}

static BYTE* GetViewEntry(BYTE* room, int index) {
    if (!room || index < 0 || index >= 8) return 0;
    BYTE** slot = (BYTE**)(room + 0x44 + index * 4);
    if (!IsReadable(slot, 4)) return 0;
    BYTE* entry = *slot;
    if (!IsReadable(entry, 0x40)) return 0;
    return entry;
}

static void ResetViewState(ViewPatchState* state, BYTE* entry) {
    state->entry = entry;
    state->valid = 0;
    state->originalXPort = state->originalYPort = 0;
    state->originalWPort = state->originalHPort = 0;
    state->patchedXPort = state->patchedYPort = 0;
    state->patchedWPort = state->patchedHPort = 0;
    state->originalWView = state->originalHView = 0;
    state->patchedWView = 0;
    state->logged = 0;
}

static void PatchRunnerViews() {
    g_visibleViewCount = 0;
    if (!g_runnerCompatible || !g_cfg.patchRunnerViews || !g_mainBase) return;
    BYTE** holderSlot = (BYTE**)(g_mainBase + RVA_VIEW_MANAGER_HOLDER);
    if (!IsReadable(holderSlot, 4)) return;
    BYTE* holder = *holderSlot;
    if (!IsReadable(holder, 4)) return;
    BYTE* room = *(BYTE**)holder;
    if (!IsReadable(room, 0x68)) return;
    if (*(BYTE*)(room + 0x40) == 0) return;

    BYTE* entries[8];
    int visible[8];
    for (int i = 0; i < 8; ++i) {
        entries[i] = GetViewEntry(room, i);
        visible[i] = entries[i] && *(BYTE*)(entries[i] + 0x04) != 0;
        if (visible[i]) ++g_visibleViewCount;
    }
    if (g_visibleViewCount <= 0) return;

    const float targetAspect = (float)g_cfg.resX / (float)g_cfg.resY;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    if (g_originalRegionWidth && g_originalRegionHeight) {
        scaleX = (float)g_cfg.resX / (float)g_originalRegionWidth;
        scaleY = (float)g_cfg.resY / (float)g_originalRegionHeight;
    }

    for (int i = 0; i < 8; ++i) {
        if (!visible[i]) continue;
        BYTE* entry = entries[i];
        ViewPatchState* state = &g_views[i];
        if (state->entry != entry) ResetViewState(state, entry);

        int* xView = (int*)(entry + 0x08);
        int* yView = (int*)(entry + 0x0C);
        int* wView = (int*)(entry + 0x10);
        int* hView = (int*)(entry + 0x14);
        int* xPort = (int*)(entry + 0x18);
        int* yPort = (int*)(entry + 0x1C);
        int* wPort = (int*)(entry + 0x20);
        int* hPort = (int*)(entry + 0x24);

        if (!PlausibleDimension(*wView) || !PlausibleDimension(*hView) ||
            !PlausibleDimension(*wPort) || !PlausibleDimension(*hPort)) continue;

        bool portsAlreadyPatched = state->valid &&
            *xPort == state->patchedXPort && *yPort == state->patchedYPort &&
            *wPort == state->patchedWPort && *hPort == state->patchedHPort;

        if (!portsAlreadyPatched) {
            state->originalXPort = *xPort;
            state->originalYPort = *yPort;
            state->originalWPort = *wPort;
            state->originalHPort = *hPort;
        }

        if (g_visibleViewCount == 1) {
            state->patchedXPort = 0;
            state->patchedYPort = 0;
            state->patchedWPort = g_cfg.resX;
            state->patchedHPort = g_cfg.resY;
        } else {
            state->patchedXPort = RoundToInt((float)state->originalXPort * scaleX);
            state->patchedYPort = RoundToInt((float)state->originalYPort * scaleY);
            state->patchedWPort = RoundToInt((float)state->originalWPort * scaleX);
            state->patchedHPort = RoundToInt((float)state->originalHPort * scaleY);
        }

        if (state->patchedWPort < 1) state->patchedWPort = 1;
        if (state->patchedHPort < 1) state->patchedHPort = 1;

        // Crimelife 3 is a custom 3D game. Its real camera is created by
        // d3d_set_projection_ext, not by view_wview. Keep the 640x480 world
        // coordinates intact and only expand the output port.
        int currentWView = *wView;
        int currentHView = *hView;
        int targetWView = currentWView;
        if (!state->originalWView) {
            state->originalWView = currentWView;
            state->originalHView = currentHView;
        }
        state->patchedWView = targetWView;

        *xPort = state->patchedXPort;
        *yPort = state->patchedYPort;
        *wPort = state->patchedWPort;
        *hPort = state->patchedHPort;
        state->valid = 1;

        if (!state->logged && g_cfg.logRunnerState) {
            LogView(i, state->originalWView, state->originalHView,
                    state->originalWPort, state->originalHPort,
                    targetWView, state->patchedWPort, state->patchedHPort);
            state->logged = 1;
        }
    }
}


static void LogProjectionAspect(double originalAspect, double forcedAspect) {
    int old1000 = (int)(originalAspect * 1000.0 + 0.5);
    int new1000 = (int)(forcedAspect * 1000.0 + 0.5);
    char a[16], b[16], buf[256];
    IntToText(old1000, a, 16);
    IntToText(new1000, b, 16);
    int p = 0; buf[0] = 0;
    AppendText(buf, 256, &p, "[GML projection] aspect x1000: ");
    AppendText(buf, 256, &p, a);
    AppendText(buf, 256, &p, " -> ");
    AppendText(buf, 256, &p, b);
    AppendText(buf, 256, &p, "\r\n");
    LogRaw(buf);
}

// GameMaker 8 registered functions receive three stack arguments, while EAX
// carries an additional runner context. A normal C function pointer call loses
// that EAX value, so exact GML/action hooks use small x86 entry thunks.
extern "C" __declspec(naked) void WINAPI CallGmlRaw(GmlFunctionFn fn, void* eaxContext, void* argA, void* argB, void* values) {
    __asm {
        mov edx, dword ptr [esp + 4]
        mov eax, dword ptr [esp + 8]
        push dword ptr [esp + 20]
        push dword ptr [esp + 20]
        push dword ptr [esp + 20]
        call edx
        ret 20
    }
}

// Some runner functions, notably distance_to_object, use both EAX and EDX
// as instance contexts. Preserve both registers when calling them from a hook.
extern "C" __declspec(naked) void WINAPI CallGmlRawEaxEdx(GmlFunctionFn fn, void* eaxContext, void* edxContext, void* argA, void* argB, void* values) {
    __asm {
        mov ecx, dword ptr [esp + 4]
        mov eax, dword ptr [esp + 8]
        mov edx, dword ptr [esp + 12]
        push dword ptr [esp + 24]
        push dword ptr [esp + 24]
        push dword ptr [esp + 24]
        call ecx
        ret 24
    }
}

static void WINAPI HandleGmlProjectionExt(void* eaxContext, void* argA, void* argB, void* values) {
    if (values && g_cfg.correctGameProjection) {
        BYTE* args = (BYTE*)values;
        double* aspect = (double*)(args + 0xF8);
        if (IsReadable(aspect, 8)) {
            double originalAspect = *aspect;
            double forcedAspect = (double)g_cfg.resX / (double)g_cfg.resY;
            *aspect = forcedAspect;
            if (!g_projectionLogged) {
                LogProjectionAspect(originalAspect, forcedAspect);
                g_projectionLogged = TRUE;
            }
        }
    }
    if (g_originalGmlProjectionExt) CallGmlRaw(g_originalGmlProjectionExt, eaxContext, argA, argB, values);
}

extern "C" __declspec(naked) void HookGmlProjectionExtEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleGmlProjectionExt
        ret 12
    }
}

static bool InstallExactProjectionHook() {
    if (!g_runnerCompatible || !g_mainBase || !g_cfg.correctGameProjection) return false;
    BYTE* movInstruction = g_mainBase + RVA_GML_PROJECTION_EXT_REGISTER_MOV;
    static const BYTE expected[5] = {0xBA, 0x04, 0x17, 0x58, 0x00};
    if (!MatchBytes(movInstruction, expected, 5)) {
        LogRaw("ERROR: d3d_set_projection_ext registration signature differs.\r\n");
        return false;
    }
    g_originalGmlProjectionExt = (GmlFunctionFn)(g_mainBase + RVA_GML_PROJECTION_EXT);
    void** operand = (void**)(movInstruction + 1);
    if (!PatchPointer(operand, (void*)&HookGmlProjectionExtEntry, 0)) {
        LogRaw("ERROR: exact GML projection hook could not be installed.\r\n");
        return false;
    }
    LogRaw("Exact d3d_set_projection_ext hook installed.\r\n");
    return true;
}


static double ReadGmlReal(void* values, int index);
static bool WriteGmlReal(void* values, int index, double value);


static int ReadInstanceInt(void* instance, DWORD offset, int fallback);
static double ReadInstanceReal(void* instance, DWORD offset, double fallback);

struct ParkedSpawnSlot {
    BOOL used;
    BOOL reserved;
    double x;
    double y;
    int chosenModel;
    DWORD firstSpawnerKey;
    UINT blockedCreates;
};

static ParkedSpawnSlot g_parkedSpawnSlots[2048];

static DWORD ParkedSpawnerKey(void* instance) {
    DWORD key = (DWORD)instance;
    return key ? key : 1UL;
}

static ParkedSpawnSlot* FindParkedSpatialSlot(void* instance, BOOL create, BOOL* created) {
    if (created) *created = FALSE;
    if (!instance) return 0;
    double x = ReadInstanceReal(instance, 0x50, 0.0);
    double y = ReadInstanceReal(instance, 0x58, 0.0);
    double radius = (double)g_cfg.parkedSpawnMergeRadius;
    double radiusSq = radius * radius;
    ParkedSpawnSlot* freeSlot = 0;
    for (UINT i = 0; i < 2048U; ++i) {
        ParkedSpawnSlot* slot = &g_parkedSpawnSlots[i];
        if (!slot->used) {
            if (!freeSlot) freeSlot = slot;
            continue;
        }
        double dx = slot->x - x;
        double dy = slot->y - y;
        if (dx * dx + dy * dy <= radiusSq) return slot;
    }
    if (!create || !freeSlot) return 0;
    freeSlot->used = TRUE;
    freeSlot->reserved = FALSE;
    freeSlot->x = x;
    freeSlot->y = y;
    freeSlot->chosenModel = -1;
    freeSlot->firstSpawnerKey = ParkedSpawnerKey(instance);
    freeSlot->blockedCreates = 0;
    if (created) *created = TRUE;
    return freeSlot;
}

static bool IsNearReservedParkedSlot(void* instance, double extraRadius) {
    if (!instance) return false;
    double x = ReadInstanceReal(instance, 0x50, 0.0);
    double y = ReadInstanceReal(instance, 0x58, 0.0);
    double radius = (double)g_cfg.parkedSpawnMergeRadius + extraRadius;
    double radiusSq = radius * radius;
    for (UINT i = 0; i < 2048U; ++i) {
        ParkedSpawnSlot* slot = &g_parkedSpawnSlots[i];
        if (!slot->used || !slot->reserved) continue;
        double dx = slot->x - x;
        double dy = slot->y - y;
        if (dx * dx + dy * dy <= radiusSq) return true;
    }
    return false;
}

static bool IsTrafficDensitySpawner(int objectIndex) {
    return objectIndex == 2844 || objectIndex == 2846 || objectIndex == 2847 || objectIndex == 2848;
}

static bool IsNpcPopulationObject(int objectIndex) {
    static const int ids[] = {2241, 7486, 2786, 7479, 7182, 2782, 7498};
    for (UINT i = 0; i < sizeof(ids) / sizeof(ids[0]); ++i) {
        if (objectIndex == ids[i]) return true;
    }
    return false;
}

static bool IsMovingTrafficVehicleObject(int objectIndex) {
    static const int ids[] = {7478, 2843, 7292, 7484, 5582, 7214, 5583, 5610, 7351, 7358, 7298, 7217};
    for (UINT i = 0; i < sizeof(ids) / sizeof(ids[0]); ++i) {
        if (objectIndex == ids[i]) return true;
    }
    return false;
}

static void AdjustPopulationLimit(void* instance, void* values) {
    if (!instance || !values) return;
    int objectIndex = ReadInstanceInt(instance, 0xCC, -1);
    int targetObject = RoundToInt((float)ReadGmlReal(values, 0));

    if (objectIndex == 2781 && targetObject == 2744) {
        int limit = RoundToInt(6.0f * g_cfg.npcDensity);
        if (limit < 1) limit = 1;
        if (limit > 256) limit = 256;
        WriteGmlReal(values, 1, (double)limit);
        if (!g_npcDensityLogged) {
            LogRaw("[Density] NPC population cap adjusted from 6 by NPCDensity.\r\n");
            g_npcDensityLogged = TRUE;
        }
    } else if (IsTrafficDensitySpawner(objectIndex) && targetObject == 2845) {
        int limit = RoundToInt(7.0f * g_cfg.vehicleDensity);
        if (limit < 1) limit = 1;
        if (limit > 256) limit = 256;
        WriteGmlReal(values, 1, (double)limit);
        if (!g_vehicleDensityLogged) {
            LogRaw("[Density] moving-traffic population cap adjusted from 7 by VehicleDensity.\r\n");
            g_vehicleDensityLogged = TRUE;
        }
    }
}

static bool IsParkedVehicleObject(int objectIndex) {
    // Exact objects used by object7458..object7461 parked-vehicle generators.
    static const int ids[] = {
        21, 7356, 7293, 7290,
        2739, 2758, 5572, 7190,
        7349, 2752, 2810, 5608
    };
    for (UINT i = 0; i < sizeof(ids) / sizeof(ids[0]); ++i) {
        if (objectIndex == ids[i]) return true;
    }
    return false;
}

static bool IsParkedVehicleSpawner(int objectIndex) {
    return objectIndex == 7458 || objectIndex == 7459 || objectIndex == 7460 || objectIndex == 7461;
}

static int ReadInstanceInt(void* instance, DWORD offset, int fallback) {
    BYTE* p = (BYTE*)instance + offset;
    if (!IsReadable(p, 4)) return fallback;
    return *(int*)p;
}

static double ReadInstanceReal(void* instance, DWORD offset, double fallback) {
    BYTE* p = (BYTE*)instance + offset;
    if (!IsReadable(p, 8)) return fallback;
    return *(double*)p;
}

static double DistanceToCameraParent(void* instance) {
    if (!instance || !g_distanceToObject) return 1000000000.0;
    BYTE result[24];
    BYTE argument[24];
    for (int i = 0; i < 24; ++i) { result[i] = 0; argument[i] = 0; }
    *(double*)(argument + 8) = 2.0; // cam_par, including its child camera objects.
    CallGmlRawEaxEdx(g_distanceToObject, instance, instance, result, 0, argument);
    if (!IsReadable(result + 8, 8)) return 1000000000.0;
    return *(double*)(result + 8);
}

static bool ShouldSuppressParkedVehicleDestroy(void* instance) {
    if (!g_cfg.fixParkedVehicleFlicker || !instance) return false;
    if (!IsReadable((BYTE*)instance + 0x108, 1)) return false;
    int objectIndex = ReadInstanceInt(instance, 0xCC, -1);
    if (!IsParkedVehicleObject(objectIndex)) return false;

    // Only protect vehicles that actually occupy a reserved parked-spawn slot.
    // This prevents the same car classes used by normal traffic from being kept
    // alive globally while still catching cleanup paths other than >1000.
    if (!IsNearReservedParkedSlot(instance, 96.0)) return false;

    double distance = DistanceToCameraParent(instance);
    if (distance <= 650.0 || distance >= (double)g_cfg.parkedVehicleDespawnDistance) return false;

    if (!g_parkedSpatialKillBackupLogged) {
        LogRaw("[VehicleSpawn] parked vehicle kill action suppressed by spatial ownership backup.\r\n");
        g_parkedSpatialKillBackupLogged = TRUE;
    }
    return true;
}

static DWORD ParkedSpatialHash(const ParkedSpawnSlot* slot, void* values) {
    DWORD hash = 2166136261UL;
    int px = slot ? RoundToInt((float)slot->x) : 0;
    int py = slot ? RoundToInt((float)slot->y) : 0;
    hash = (hash ^ (DWORD)px) * 16777619UL;
    hash = (hash ^ (DWORD)py) * 16777619UL;
    for (int i = 0; i < 4; ++i) {
        int id = RoundToInt((float)ReadGmlReal(values, i));
        hash = (hash ^ (DWORD)id) * 16777619UL;
    }
    return hash;
}

static void StabilizeParkedVehicleRandomChoice(void* instance, void* values, ParkedSpawnSlot* slot) {
    if (!g_cfg.stableParkedVehicleModels || !instance || !values || !slot) return;

    int candidates[4];
    int validCount = 0;
    for (int i = 0; i < 4; ++i) {
        candidates[i] = RoundToInt((float)ReadGmlReal(values, i));
        if (candidates[i] >= 0) ++validCount;
    }
    if (!validCount) return;

    int chosen = slot->chosenModel;
    bool chosenStillValid = false;
    for (int i = 0; i < 4; ++i) if (candidates[i] == chosen) chosenStillValid = true;
    if (!chosenStillValid) {
        DWORD hash = ParkedSpatialHash(slot, values);
        int pick = (int)(hash % 4UL);
        for (int n = 0; n < 4 && candidates[pick] < 0; ++n) pick = (pick + 1) & 3;
        chosen = candidates[pick];
        if (chosen < 0) return;
        slot->chosenModel = chosen;
    }
    for (int i = 0; i < 4; ++i) WriteGmlReal(values, i, (double)chosen);

    if (!g_parkedVehicleStableModelLogged) {
        LogRaw("[VehicleSpawn] parked-vehicle model stabilized by world position, not by transient instance pointer.\r\n");
        g_parkedVehicleStableModelLogged = TRUE;
    }
}

static void WINAPI HandleActionKillObject(void* eaxContext, void* argA, void* argB, void* values) {
    if (ShouldSuppressParkedVehicleDestroy(eaxContext)) return;
    if (g_originalActionKillObject) CallGmlRaw(g_originalActionKillObject, eaxContext, argA, argB, values);
}

extern "C" __declspec(naked) void HookActionKillObjectEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleActionKillObject
        ret 12
    }
}

static bool AllowParkedSpawnerCreate(void* instance, ParkedSpawnSlot** outSlot) {
    if (outSlot) *outSlot = 0;
    if (!g_cfg.fixParkedVehicleFlicker || !instance) return true;
    int objectIndex = ReadInstanceInt(instance, 0xCC, -1);
    if (!IsParkedVehicleSpawner(objectIndex)) return true;

    BOOL created = FALSE;
    ParkedSpawnSlot* slot = FindParkedSpatialSlot(instance, TRUE, &created);
    if (outSlot) *outSlot = slot;
    if (!slot) return true;
    if (slot->reserved) {
        ++slot->blockedCreates;
        if (!g_parkedSpatialBlockedLogged) {
            LogRaw("[VehicleSpawn] duplicate parked creation blocked by spatial position lock.\r\n");
            g_parkedSpatialBlockedLogged = TRUE;
        }
        return false;
    }

    slot->reserved = TRUE;
    slot->firstSpawnerKey = ParkedSpawnerKey(instance);
    if (!g_parkedSpatialAcceptedLogged) {
        LogRaw("[VehicleSpawn] spatial parking slot reserved: only one vehicle may occupy overlapping spawners at that world position.\r\n");
        g_parkedSpatialAcceptedLogged = TRUE;
    }
    if (!g_parkedVehicleSingleOccupantLogged) {
        LogRaw("[VehicleSpawn] one parked vehicle is now allowed per spatial parking slot.\r\n");
        g_parkedVehicleSingleOccupantLogged = TRUE;
    }
    return true;
}

static void UpdateParkedSpawnerVisit(void* instance, void* values, void* resultValue) {
    if (!g_cfg.fixParkedVehicleFlicker || g_cfg.parkedLockUntilRestart) return;
    if (g_cfg.parkedSpawnerResetDistance <= 0.0f || !instance || !values || !resultValue) return;
    int objectIndex = ReadInstanceInt(instance, 0xCC, -1);
    if (!IsParkedVehicleSpawner(objectIndex)) return;
    int targetObject = RoundToInt((float)ReadGmlReal(values, 0));
    if (targetObject != 2) return;

    double distance = ReadGmlReal(resultValue, 0);
    if (distance <= (double)g_cfg.parkedSpawnerResetDistance) {
        ParkedSpawnSlot* slot = FindParkedSpatialSlot(instance, FALSE, 0);
        if (slot) {
            slot->reserved = FALSE;
            slot->chosenModel = -1;
        }
    }
}

static void AdjustDistanceToObjectResult(void* instance, void* values, void* resultValue) {
    if (!instance || !values || !resultValue) return;
    int targetObject = RoundToInt((float)ReadGmlReal(values, 0));
    if (targetObject != 2) return; // cam_par / player camera parent used by population logic.

    int objectIndex = ReadInstanceInt(instance, 0xCC, -1);
    double originalDistance = ReadGmlReal(resultValue, 0);
    if (originalDistance < 0.0) return;
    double adjustedDistance = originalDistance;

    // Placed parked vehicles use a >1000 cleanup check. Scaling only the far
    // range preserves all close interaction/collision checks (150/256 units).
    if (g_cfg.fixParkedVehicleFlicker && IsParkedVehicleObject(objectIndex) && originalDistance > 750.0) {
        double parkedScale = (double)g_cfg.parkedVehicleDespawnDistance / 1000.0;
        if (parkedScale < 1.0) parkedScale = 1.0;
        adjustedDistance = originalDistance / parkedScale;
        if (!g_parkedDistanceProtectedLogged) {
            LogRaw("[VehicleSpawn] exact parked-vehicle >1000 distance cleanup extended through distance_to_object; distant model cycling is suppressed.\r\n");
            g_parkedDistanceProtectedLogged = TRUE;
        }
    }

    // Spawn generators compare against the original 600/700-unit bands. Divide
    // the measured distance so those same script constants represent a farther
    // physical radius without editing the embedded game data.
    if (objectIndex == 2781 && g_cfg.npcSpawnDistanceScale > 1.0f) {
        adjustedDistance = originalDistance / (double)g_cfg.npcSpawnDistanceScale;
    } else if (IsTrafficDensitySpawner(objectIndex) && g_cfg.vehicleSpawnDistanceScale > 1.0f) {
        adjustedDistance = originalDistance / (double)g_cfg.vehicleSpawnDistanceScale;
    }

    // Population objects have far cleanup checks at 700 (NPC) and 900 (traffic).
    // Only scale distances above the gameplay/AI ranges so combat and interaction
    // thresholds such as 20/90/200/400 units remain unchanged.
    if (IsNpcPopulationObject(objectIndex) && originalDistance > 500.0 && g_cfg.npcSpawnDistanceScale > 1.0f) {
        adjustedDistance = originalDistance / (double)g_cfg.npcSpawnDistanceScale;
    } else if (IsMovingTrafficVehicleObject(objectIndex) && originalDistance > 650.0 && g_cfg.vehicleSpawnDistanceScale > 1.0f) {
        adjustedDistance = originalDistance / (double)g_cfg.vehicleSpawnDistanceScale;
    }

    if (adjustedDistance != originalDistance) {
        WriteGmlReal(resultValue, 0, adjustedDistance);
        if (!g_spawnDistanceLogged && (objectIndex == 2781 || IsTrafficDensitySpawner(objectIndex))) {
            LogRaw("[SpawnDistance] vehicle/NPC spawn and matching far-cleanup radii scaled from their original 600/700/900-unit rules.\r\n");
            g_spawnDistanceLogged = TRUE;
        }
    }
}

static void WINAPI HandleDistanceToObject(void* eaxContext, void* edxContext, void* argA, void* argB, void* values) {
    if (g_originalDistanceToObject) {
        CallGmlRawEaxEdx(g_originalDistanceToObject, eaxContext, edxContext, argA, argB, values);
    }
    AdjustDistanceToObjectResult(eaxContext, values, argA);
    UpdateParkedSpawnerVisit(eaxContext, values, argA);
}

extern "C" __declspec(naked) void HookDistanceToObjectEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push edx
        push eax
        call HandleDistanceToObject
        ret 12
    }
}

static void WINAPI HandleActionCreateObjectRandom(void* eaxContext, void* argA, void* argB, void* values) {
    int objectIndex = ReadInstanceInt(eaxContext, 0xCC, -1);
    if (IsParkedVehicleSpawner(objectIndex)) {
        ParkedSpawnSlot* slot = 0;
        if (!AllowParkedSpawnerCreate(eaxContext, &slot)) return;
        StabilizeParkedVehicleRandomChoice(eaxContext, values, slot);
    }
    if (g_originalActionCreateObjectRandom) CallGmlRaw(g_originalActionCreateObjectRandom, eaxContext, argA, argB, values);
}

extern "C" __declspec(naked) void HookActionCreateObjectRandomEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleActionCreateObjectRandom
        ret 12
    }
}

static void WINAPI HandleActionIfNumber(void* eaxContext, void* argA, void* argB, void* values) {
    AdjustPopulationLimit(eaxContext, values);
    if (g_originalActionIfNumber) CallGmlRaw(g_originalActionIfNumber, eaxContext, argA, argB, values);
}

extern "C" __declspec(naked) void HookActionIfNumberEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleActionIfNumber
        ret 12
    }
}

static bool InstallVehicleSpawnFixHooks() {
    bool wantsParked = g_cfg.fixParkedVehicleFlicker || g_cfg.stableParkedVehicleModels;
    bool wantsDensity = g_cfg.vehicleDensity != 1.0f || g_cfg.npcDensity != 1.0f;
    bool wantsDistance = wantsParked || g_cfg.vehicleSpawnDistanceScale != 1.0f || g_cfg.npcSpawnDistanceScale != 1.0f;
    if (!g_runnerCompatible || !g_mainBase || (!wantsParked && !wantsDensity && !wantsDistance)) return false;

    bool any = false;
    g_originalDistanceToObject = (GmlFunctionFn)(g_mainBase + RVA_GML_DISTANCE_TO_OBJECT);
    g_distanceToObject = g_originalDistanceToObject;

    if (wantsDistance) {
        BYTE* distanceMov = g_mainBase + RVA_GML_DISTANCE_TO_OBJECT_REGISTER_MOV;
        static const BYTE expectedDistance[5] = {0xBA, 0x38, 0xB5, 0x55, 0x00};
        if (MatchBytes(distanceMov, expectedDistance, 5)) {
            if (PatchPointer((void**)(distanceMov + 1), (void*)&HookDistanceToObjectEntry, 0)) {
                any = true;
                g_distanceHookInstalled = TRUE;
                LogRaw("Exact distance_to_object population/spawn hook installed.\r\n");
            }
        } else {
            LogRaw("ERROR: distance_to_object registration signature differs.\r\n");
        }

        BYTE* killMov = g_mainBase + RVA_ACTION_KILL_OBJECT_REGISTER_MOV;
        static const BYTE expectedKill[5] = {0xBA, 0x1C, 0xB9, 0x54, 0x00};
        if (MatchBytes(killMov, expectedKill, 5)) {
            g_originalActionKillObject = (GmlFunctionFn)(g_mainBase + RVA_ACTION_KILL_OBJECT);
            if (PatchPointer((void**)(killMov + 1), (void*)&HookActionKillObjectEntry, 0)) any = true;
        } else {
            LogRaw("ERROR: action_kill_object registration signature differs.\r\n");
        }
    }

    if (wantsParked) {
        BYTE* createMov = g_mainBase + RVA_ACTION_CREATE_OBJECT_RANDOM_REGISTER_MOV;
        static const BYTE expectedCreate[5] = {0xBA, 0xCC, 0xB7, 0x54, 0x00};
        if (MatchBytes(createMov, expectedCreate, 5)) {
            g_originalActionCreateObjectRandom = (GmlFunctionFn)(g_mainBase + RVA_ACTION_CREATE_OBJECT_RANDOM);
            if (PatchPointer((void**)(createMov + 1), (void*)&HookActionCreateObjectRandomEntry, 0)) any = true;
        } else {
            LogRaw("ERROR: action_create_object_random registration signature differs.\r\n");
        }
    }

    if (wantsDensity) {
        BYTE* numberMov = g_mainBase + RVA_ACTION_IF_NUMBER_REGISTER_MOV;
        static const BYTE expectedNumber[5] = {0xBA, 0xE0, 0xC7, 0x54, 0x00};
        if (MatchBytes(numberMov, expectedNumber, 5)) {
            g_originalActionIfNumber = (GmlFunctionFn)(g_mainBase + RVA_ACTION_IF_NUMBER);
            if (PatchPointer((void**)(numberMov + 1), (void*)&HookActionIfNumberEntry, 0)) {
                any = true;
                if (!g_densityHookLogged) {
                    LogRaw("Exact traffic/NPC density limit hook installed.\r\n");
                    g_densityHookLogged = TRUE;
                }
            }
        } else {
            LogRaw("ERROR: action_if_number registration signature differs.\r\n");
        }
    }

    if (wantsParked && any && !g_parkedVehicleHookLogged) {
        LogRaw("Exact parked-vehicle stabilization hooks installed.\r\n");
        g_parkedVehicleHookLogged = TRUE;
    }
    return any;
}


static void ComputeFitViewport(D3DVIEWPORT8* out);
static void ComputeFullViewport(D3DVIEWPORT8* out);

static double ReadGmlReal(void* values, int index) {
    if (!values || index < 0) return 0.0;
    BYTE* address = (BYTE*)values + index * 24 + 8;
    if (!IsReadable(address, 8)) return 0.0;
    return *(double*)address;
}

static bool MatchGmlReal(double value, int expected, double tolerance) {
    double delta = value - (double)expected;
    if (delta < 0.0) delta = -delta;
    return delta <= tolerance;
}

static bool WriteGmlReal(void* values, int index, double value) {
    if (!values || index < 0) return false;
    BYTE* address = (BYTE*)values + index * 24 + 8;
    if (!IsReadable(address, 8)) return false;
    *(double*)address = value;
    return true;
}

static float EffectiveStreamingScale() {
    float scale = g_cfg.streamingRegionScale;
    if (scale <= 0.0f) {
        float targetAspect = (float)g_cfg.resX / (float)g_cfg.resY;
        scale = targetAspect / g_cfg.referenceAspect;
    }
    if (scale < 1.0f) scale = 1.0f;
    return scale;
}

static void WINAPI HandleInstanceDeactivateRegion(void* eaxContext, void* argA, void* argB, void* values) {
    if (g_cfg.fixDistantObjects && values) {
        if (g_cfg.disableInstanceDeactivation) {
            if (!g_streamingAdjustedLogged) {
                LogRaw("[Streaming] instance_deactivate_region bypassed; all map instances remain active.\r\n");
                g_streamingAdjustedLogged = TRUE;
            }
            return;
        }

        double x = ReadGmlReal(values, 0);
        double y = ReadGmlReal(values, 1);
        double w = ReadGmlReal(values, 2);
        double h = ReadGmlReal(values, 3);
        float scale = EffectiveStreamingScale();
        if (w > 0.0 && h > 0.0 && scale > 1.001f) {
            double cx = x + w * 0.5;
            double cy = y + h * 0.5;
            double newW = w * (double)scale;
            double newH = h * (double)scale;
            WriteGmlReal(values, 0, cx - newW * 0.5);
            WriteGmlReal(values, 1, cy - newH * 0.5);
            WriteGmlReal(values, 2, newW);
            WriteGmlReal(values, 3, newH);
            if (!g_streamingAdjustedLogged) {
                char a[16], buf[224];
                IntToText(RoundToInt(scale * 1000.0f), a, 16);
                int q = 0; buf[0] = 0;
                AppendText(buf, 224, &q, "[Streaming] activation region expanded; scale x1000=");
                AppendText(buf, 224, &q, a);
                AppendText(buf, 224, &q, ".\r\n");
                LogRaw(buf);
                g_streamingAdjustedLogged = TRUE;
            }
        }
    }
    if (g_originalInstanceDeactivateRegion) {
        CallGmlRaw(g_originalInstanceDeactivateRegion, eaxContext, argA, argB, values);
    }
}

extern "C" __declspec(naked) void HookInstanceDeactivateRegionEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleInstanceDeactivateRegion
        ret 12
    }
}

static DWORD ComputeCoplanarBias(void* values) {
    if (!values || g_cfg.coplanarZBiasLayers <= 0) return 0;
    int textureId = RoundToInt(ReadGmlReal(values, 6));
    DWORD hash = (DWORD)textureId * 2654435761UL;
    return 1 + ((hash >> 28) % (DWORD)g_cfg.coplanarZBiasLayers);
}

static void CallGmlWithCoplanarBias(GmlFunctionFn fn, void* eaxContext, void* argA, void* argB, void* values) {
    if (!fn) return;
    DWORD oldBias = 0;
    BOOL changed = FALSE;
    if (g_cfg.coplanarZBias && g_projectionMode == 1 && g_device &&
        g_originalSetRenderState && g_originalGetRenderState) {
        if (g_originalGetRenderState(g_device, 47, &oldBias) >= 0) {
            DWORD bias = ComputeCoplanarBias(values);
            if (g_originalSetRenderState(g_device, 47, bias) >= 0) {
                changed = TRUE;
                if (!g_coplanarBiasLogged) {
                    LogRaw("[Depth] stable texture-layer Z bias enabled for d3d_draw_floor/wall.\r\n");
                    g_coplanarBiasLogged = TRUE;
                }
            }
        }
    }
    CallGmlRaw(fn, eaxContext, argA, argB, values);
    if (changed) g_originalSetRenderState(g_device, 47, oldBias);
}

static void WINAPI HandleD3DDrawWall(void* eaxContext, void* argA, void* argB, void* values) {
    CallGmlWithCoplanarBias(g_originalD3DDrawWall, eaxContext, argA, argB, values);
}

static void WINAPI HandleD3DDrawFloor(void* eaxContext, void* argA, void* argB, void* values) {
    CallGmlWithCoplanarBias(g_originalD3DDrawFloor, eaxContext, argA, argB, values);
}

extern "C" __declspec(naked) void HookD3DDrawWallEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleD3DDrawWall
        ret 12
    }
}

extern "C" __declspec(naked) void HookD3DDrawFloorEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleD3DDrawFloor
        ret 12
    }
}

static bool InstallWorldFixHooks() {
    if (!g_runnerCompatible || !g_mainBase) return false;
    bool any = false;

    if (g_cfg.fixDistantObjects) {
        BYTE* movInstruction = g_mainBase + RVA_GML_INSTANCE_DEACTIVATE_REGION_REGISTER_MOV;
        static const BYTE expectedDeactivate[5] = {0xBA, 0x5C, 0xCB, 0x55, 0x00};
        if (MatchBytes(movInstruction, expectedDeactivate, 5)) {
            g_originalInstanceDeactivateRegion = (GmlFunctionFn)(g_mainBase + RVA_GML_INSTANCE_DEACTIVATE_REGION);
            if (PatchPointer((void**)(movInstruction + 1), (void*)&HookInstanceDeactivateRegionEntry, 0)) {
                any = true;
                if (!g_streamingHookLogged) {
                    LogRaw("Exact instance_deactivate_region hook installed.\r\n");
                    g_streamingHookLogged = TRUE;
                }
            }
        } else {
            LogRaw("ERROR: instance_deactivate_region registration signature differs.\r\n");
        }
    }

    if (g_cfg.coplanarZBias) {
        BYTE* wallMov = g_mainBase + RVA_GML_D3D_DRAW_WALL_REGISTER_MOV;
        BYTE* floorMov = g_mainBase + RVA_GML_D3D_DRAW_FLOOR_REGISTER_MOV;
        static const BYTE expectedWall[5] = {0xBA, 0xE4, 0x15, 0x58, 0x00};
        static const BYTE expectedFloor[5] = {0xBA, 0x44, 0x16, 0x58, 0x00};
        bool wallOk = false, floorOk = false;
        if (MatchBytes(wallMov, expectedWall, 5)) {
            g_originalD3DDrawWall = (GmlFunctionFn)(g_mainBase + RVA_GML_D3D_DRAW_WALL);
            wallOk = PatchPointer((void**)(wallMov + 1), (void*)&HookD3DDrawWallEntry, 0);
        }
        if (MatchBytes(floorMov, expectedFloor, 5)) {
            g_originalD3DDrawFloor = (GmlFunctionFn)(g_mainBase + RVA_GML_D3D_DRAW_FLOOR);
            floorOk = PatchPointer((void**)(floorMov + 1), (void*)&HookD3DDrawFloorEntry, 0);
        }
        if (wallOk || floorOk) {
            any = true;
            LogRaw("Exact d3d_draw_wall/floor depth-bias hooks installed.\r\n");
        } else {
            LogRaw("ERROR: d3d_draw_wall/floor registration signatures differ.\r\n");
        }
    }
    return any;
}

static bool PushFullViewport(D3DVIEWPORT8* previous) {
    if (!g_device || !g_originalSetViewport || !previous) return false;
    bool havePrevious = false;
    if (g_originalGetViewport && g_originalGetViewport(g_device, previous) >= 0) havePrevious = true;
    if (!havePrevious) {
        if (g_projectionMode == 2) ComputeFitViewport(previous);
        else ComputeFullViewport(previous);
    }
    D3DVIEWPORT8 full;
    ComputeFullViewport(&full);
    return g_originalSetViewport(g_device, &full) >= 0;
}

static void PopViewport(const D3DVIEWPORT8* previous) {
    if (g_device && g_originalSetViewport && previous) g_originalSetViewport(g_device, previous);
}

static void WINAPI HandleDrawSpriteExt(void* eaxContext, void* argA, void* argB, void* values) {
    int spriteIndex = RoundToInt((float)ReadGmlReal(values, 0));
    if (spriteIndex == VIGNETTE_SPRITE_INDEX) {
        if (g_cfg.vignetteMode == 2) {
            if (!g_vignetteLogged) {
                LogRaw("[Overlay] Vignette sprite6532 disabled.\r\n");
                g_vignetteLogged = TRUE;
            }
            return;
        }
        if (g_cfg.vignetteMode == 1) {
            D3DVIEWPORT8 previous;
            bool changed = PushFullViewport(&previous);
            if (g_originalDrawSpriteExt) CallGmlRaw(g_originalDrawSpriteExt, eaxContext, argA, argB, values);
            if (changed) PopViewport(&previous);
            if (!g_vignetteLogged) {
                LogRaw("[Overlay] Vignette sprite6532 stretched to full ultrawide viewport.\r\n");
                g_vignetteLogged = TRUE;
            }
            return;
        }
    }
    if (g_originalDrawSpriteExt) CallGmlRaw(g_originalDrawSpriteExt, eaxContext, argA, argB, values);
}

extern "C" __declspec(naked) void HookDrawSpriteExtEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleDrawSpriteExt
        ret 12
    }
}

static bool IsLetterboxRectangle(void* values) {
    if (!values) return false;
    double x1 = ReadGmlReal(values, 0);
    double y1 = ReadGmlReal(values, 1);
    double x2 = ReadGmlReal(values, 2);
    double y2 = ReadGmlReal(values, 3);
    double outline = ReadGmlReal(values, 4);
    if (!MatchGmlReal(x1, -1, 1.1) || !MatchGmlReal(x2, 640, 1.1) || !MatchGmlReal(outline, 0, 0.1)) return false;
    bool top = MatchGmlReal(y1, -1, 1.1) && MatchGmlReal(y2, 60, 1.1);
    bool bottom = MatchGmlReal(y1, 420, 1.1) && MatchGmlReal(y2, 480, 1.1);
    return top || bottom;
}

static void WINAPI HandleActionDrawRectangle(void* eaxContext, void* argA, void* argB, void* values) {
    if (IsLetterboxRectangle(values)) {
        if (g_cfg.letterboxMode == 2) {
            if (!g_letterboxLogged) {
                LogRaw("[Overlay] Cutscene letterbox rectangles disabled.\r\n");
                g_letterboxLogged = TRUE;
            }
            return;
        }
        if (g_cfg.letterboxMode == 1) {
            D3DVIEWPORT8 previous;
            bool changed = PushFullViewport(&previous);
            if (g_originalActionDrawRectangle) CallGmlRaw(g_originalActionDrawRectangle, eaxContext, argA, argB, values);
            if (changed) PopViewport(&previous);
            if (!g_letterboxLogged) {
                LogRaw("[Overlay] Cutscene letterbox rectangles stretched to full ultrawide viewport.\r\n");
                g_letterboxLogged = TRUE;
            }
            return;
        }
    }
    if (g_originalActionDrawRectangle) CallGmlRaw(g_originalActionDrawRectangle, eaxContext, argA, argB, values);
}

extern "C" __declspec(naked) void HookActionDrawRectangleEntry() {
    __asm {
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push dword ptr [esp + 12]
        push eax
        call HandleActionDrawRectangle
        ret 12
    }
}

static bool InstallOverlayHooks() {
    if (!g_runnerCompatible || !g_mainBase) return false;
    bool ok = true;
    BYTE* spriteMov = g_mainBase + RVA_GML_DRAW_SPRITE_EXT_REGISTER_MOV;
    static const BYTE expectedSprite[5] = {0xBA, 0xAC, 0x4B, 0x55, 0x00};
    if (MatchBytes(spriteMov, expectedSprite, 5)) {
        g_originalDrawSpriteExt = (GmlFunctionFn)(g_mainBase + RVA_GML_DRAW_SPRITE_EXT);
        if (!PatchPointer((void**)(spriteMov + 1), (void*)&HookDrawSpriteExtEntry, 0)) ok = false;
    } else {
        LogRaw("ERROR: draw_sprite_ext registration signature differs.\r\n");
        ok = false;
    }

    BYTE* rectangleMov = g_mainBase + RVA_ACTION_DRAW_RECTANGLE_REGISTER_MOV;
    static const BYTE expectedRectangle[5] = {0xBA, 0x7C, 0xE5, 0x54, 0x00};
    if (MatchBytes(rectangleMov, expectedRectangle, 5)) {
        g_originalActionDrawRectangle = (GmlFunctionFn)(g_mainBase + RVA_ACTION_DRAW_RECTANGLE);
        if (!PatchPointer((void**)(rectangleMov + 1), (void*)&HookActionDrawRectangleEntry, 0)) ok = false;
    } else {
        LogRaw("ERROR: action_draw_rectangle registration signature differs.\r\n");
        ok = false;
    }

    if (ok) LogRaw("Exact vignette and cutscene-letterbox hooks installed.\r\n");
    return ok;
}

static DWORD FloatBits(float v) {
    union { float f; DWORD d; } u;
    u.f = v;
    return u.d;
}

static float BitsFloat(DWORD v) {
    union { float f; DWORD d; } u;
    u.d = v;
    return u.f;
}

static SurfaceInfo* FindSurfaceInfo(void* surface) {
    for (int i = 0; i < g_surfaceCount; ++i) if (g_surfaces[i].surface == surface) return &g_surfaces[i];
    return 0;
}

static void TrackSurface(void* surface, void* texture, UINT level) {
    if (!surface || !texture) return;
    SurfaceInfo* existing = FindSurfaceInfo(surface);
    if (existing) {
        existing->texture = texture;
        existing->level = level;
        return;
    }
    if (g_surfaceCount >= 16384) return;
    g_surfaces[g_surfaceCount].surface = surface;
    g_surfaces[g_surfaceCount].texture = texture;
    g_surfaces[g_surfaceCount].level = level;
    ++g_surfaceCount;
}

static TextureInfo* FindTextureInfo(void* texture) {
    for (int i = 0; i < g_textureCount; ++i) if (g_textures[i].texture == texture) return &g_textures[i];
    return 0;
}

static UINT ComputeMipLevelCount(UINT width, UINT height) {
    UINT levels = 1;
    while (width > 1 || height > 1) {
        if (width > 1) width >>= 1;
        if (height > 1) height >>= 1;
        ++levels;
    }
    return levels;
}

static void TrackMipTexture(void* texture, UINT width, UINT height, UINT format, UINT levels) {
    if (!texture || levels <= 1) return;
    TextureInfo* info = FindTextureInfo(texture);
    if (!info) {
        if (g_textureCount >= 8192) return;
        info = &g_textures[g_textureCount++];
        ++g_mipTextureCount;
    }
    // A released COM texture can later reuse the same address. Always refresh
    // the metadata instead of retaining stale dimensions/classification.
    info->texture = texture;
    info->width = width;
    info->height = height;
    info->format = format;
    info->levels = levels;
    info->generated = FALSE;
    info->generationFailed = FALSE;
    info->alphaClassified = FALSE;
    info->alphaClass = 0;
    info->skippedAlpha = FALSE;
    info->contentReady = FALSE;
    info->uploadSeen = FALSE;
    info->replacementTexture = 0;
    info->replacementReady = FALSE;
    info->replacementFailed = FALSE;
    info->replacementScale = 1;
    info->edgeFixedTexture = 0;
    info->edgeFixedReady = FALSE;
    info->edgeFixedFailed = FALSE;
    if (!g_mipCreationLogged) {
        LogRaw("[Graphics] Full mip-chain textures are being created.\r\n");
        g_mipCreationLogged = TRUE;
    }
}

static UINT ClassifyTextureAlpha(void* texture, TextureInfo* info) {
    if (!texture || !info) return 0;
    if (info->format == 22) {
        info->alphaClassified = TRUE;
        info->alphaClass = 1;
        return 1;
    }
    if (info->format != 21 || !g_textureGetLevelDesc || !g_textureLockRect || !g_originalTextureUnlockRect) return 0;
    D3DSURFACE_DESC8 desc;
    D3DLOCKED_RECT8 lock;
    if (g_textureGetLevelDesc(texture, 0, &desc) < 0 || g_textureLockRect(texture, 0, &lock, 0, 0x10) < 0) return 0;
    UINT total = desc.Width * desc.Height;
    UINT nonOpaque = 0;
    UINT intermediate = 0;
    BYTE* bits = (BYTE*)lock.pBits;
    for (UINT y = 0; y < desc.Height; ++y) {
        BYTE* row = bits + y * lock.Pitch;
        for (UINT x = 0; x < desc.Width; ++x) {
            BYTE a = row[x * 4 + 3];
            if (a != 255) {
                ++nonOpaque;
                if (a != 0) ++intermediate;
            }
        }
    }
    g_originalTextureUnlockRect(texture, 0);
    UINT cls = 1;
    if (nonOpaque) {
        // GameMaker assets commonly contain binary cutout alpha, but the runtime
        // can introduce a sizeable ring of intermediate values while uploading or
        // filtering them. Classify by the alpha distribution, not by a strict 5%
        // intermediate-pixel limit. Water/effects have broad continuous alpha,
        // whereas foliage/fences contain large transparent AND opaque populations.
        UINT transparent = 0;
        UINT opaque = 0;
        for (UINT y = 0; y < desc.Height; ++y) {
            BYTE* row = bits + y * lock.Pitch;
            for (UINT x = 0; x < desc.Width; ++x) {
                BYTE a = row[x * 4 + 3];
                if (a <= 16) ++transparent;
                else if (a >= 239) ++opaque;
            }
        }
        UINT tolerance = total / 20;
        if (tolerance < 8) tolerance = 8;
        BOOL hasTransparentBody = transparent >= (total / 100);
        BOOL hasOpaqueBody = opaque >= (total / 100);
        BOOL edgeDominated = intermediate <= (total / 3);
        cls = ((intermediate <= tolerance) || (hasTransparentBody && hasOpaqueBody && edgeDominated)) ? 2 : 3;
    }
    info->alphaClassified = TRUE;
    info->alphaClass = cls;
    return cls;
}

static void PreserveCutoutCoverage(const D3DLOCKED_RECT8& srcLock, const D3DSURFACE_DESC8& srcDesc,
                                   D3DLOCKED_RECT8& dstLock, const D3DSURFACE_DESC8& dstDesc) {
    if (!g_cfg.alphaCoveragePreservation) return;
    UINT srcPixels = srcDesc.Width * srcDesc.Height;
    UINT dstPixels = dstDesc.Width * dstDesc.Height;
    if (!srcPixels || !dstPixels) return;

    UINT srcCoverage = 0;
    BYTE* srcBits = (BYTE*)srcLock.pBits;
    for (UINT y = 0; y < srcDesc.Height; ++y) {
        BYTE* row = srcBits + y * srcLock.Pitch;
        for (UINT x = 0; x < srcDesc.Width; ++x) if (row[x * 4 + 3] >= 128) ++srcCoverage;
    }
    UINT targetCoverage = (UINT)RoundToInt(((float)srcCoverage * (float)dstPixels) / (float)srcPixels);
    if (targetCoverage == 0) return;

    int lo = 128;
    int hi = 8192;
    for (int iteration = 0; iteration < 14; ++iteration) {
        int mid = (lo + hi) / 2;
        UINT coverage = 0;
        BYTE* dstBits = (BYTE*)dstLock.pBits;
        for (UINT y = 0; y < dstDesc.Height; ++y) {
            BYTE* row = dstBits + y * dstLock.Pitch;
            for (UINT x = 0; x < dstDesc.Width; ++x) {
                UINT a = row[x * 4 + 3];
                UINT scaled = (a * (UINT)mid + 512) / 1024;
                if (scaled >= 128) ++coverage;
            }
        }
        if (coverage < targetCoverage) lo = mid + 1;
        else hi = mid;
    }

    BYTE* dstBits = (BYTE*)dstLock.pBits;
    for (UINT y = 0; y < dstDesc.Height; ++y) {
        BYTE* row = dstBits + y * dstLock.Pitch;
        for (UINT x = 0; x < dstDesc.Width; ++x) {
            UINT a = row[x * 4 + 3];
            UINT scaled = (a * (UINT)hi + 512) / 1024;
            row[x * 4 + 3] = (BYTE)(scaled > 255 ? 255 : scaled);
        }
    }
    if (!g_alphaCoverageLogged) {
        LogRaw("[Graphics] Alpha-test coverage preservation enabled for cutout mipmaps.\r\n");
        g_alphaCoverageLogged = TRUE;
    }
}

static bool GenerateMipChain(void* texture, bool forceRegenerate) {
    TextureInfo* info = FindTextureInfo(texture);
    if (!info || info->levels <= 1 || !g_textureGetLevelDesc || !g_textureLockRect || !g_originalTextureUnlockRect) return false;
    if (info->format != 21 && info->format != 22) return false;
    if (info->generated && !forceRegenerate) return true;
    if (info->skippedAlpha && !g_cfg.mipmapsAlphaTextures) return false;
    if (g_generatingMipmaps) return false;

    UINT alphaClass = info->alphaClassified ? info->alphaClass : ClassifyTextureAlpha(texture, info);
    if (!alphaClass) return false;
    if (alphaClass != 1 && !g_cfg.mipmapsAlphaTextures) {
        info->skippedAlpha = TRUE;
        info->generated = FALSE;
        info->generationFailed = FALSE;
        if (!g_alphaMipSkipLogged) {
            LogRaw("[Graphics] Alpha-texture mipmaps skipped by configuration.\r\n");
            g_alphaMipSkipLogged = TRUE;
        }
        return false;
    }
    if (alphaClass != 1 && !g_alphaMipSafeLogged) {
        LogRaw("[Graphics] Safe premultiplied-alpha mip generation enabled for transparent textures.\r\n");
        g_alphaMipSafeLogged = TRUE;
    }

    g_generatingMipmaps = TRUE;
    bool success = true;
    bool generatedAny = false;
    for (UINT level = 1; level < info->levels; ++level) {
        D3DSURFACE_DESC8 srcDesc, dstDesc;
        if (g_textureGetLevelDesc(texture, level - 1, &srcDesc) < 0 ||
            g_textureGetLevelDesc(texture, level, &dstDesc) < 0 ||
            (srcDesc.Format != 21 && srcDesc.Format != 22) || srcDesc.Format != dstDesc.Format) {
            success = false;
            break;
        }

        D3DLOCKED_RECT8 srcLock = {0,0}, dstLock = {0,0};
        if (g_textureLockRect(texture, level - 1, &srcLock, 0, 0x10) < 0) {
            success = false;
            break;
        }
        if (g_textureLockRect(texture, level, &dstLock, 0, 0) < 0) {
            g_originalTextureUnlockRect(texture, level - 1);
            success = false;
            break;
        }

        BYTE* srcBits = (BYTE*)srcLock.pBits;
        BYTE* dstBits = (BYTE*)dstLock.pBits;
        for (UINT y = 0; y < dstDesc.Height; ++y) {
            for (UINT x = 0; x < dstDesc.Width; ++x) {
                UINT sx0 = x * 2;
                UINT sy0 = y * 2;
                UINT sx1 = sx0 + 1 < srcDesc.Width ? sx0 + 1 : sx0;
                UINT sy1 = sy0 + 1 < srcDesc.Height ? sy0 + 1 : sy0;
                BYTE* px[4];
                px[0] = srcBits + sy0 * srcLock.Pitch + sx0 * 4;
                px[1] = srcBits + sy0 * srcLock.Pitch + sx1 * 4;
                px[2] = srcBits + sy1 * srcLock.Pitch + sx0 * 4;
                px[3] = srcBits + sy1 * srcLock.Pitch + sx1 * 4;
                BYTE* d = dstBits + y * dstLock.Pitch + x * 4;

                if (srcDesc.Format == 22 || alphaClass == 1) {
                    d[0] = (BYTE)(((UINT)px[0][0] + px[1][0] + px[2][0] + px[3][0] + 2) / 4);
                    d[1] = (BYTE)(((UINT)px[0][1] + px[1][1] + px[2][1] + px[3][1] + 2) / 4);
                    d[2] = (BYTE)(((UINT)px[0][2] + px[1][2] + px[2][2] + px[3][2] + 2) / 4);
                    d[3] = 255;
                } else {
                    UINT alphaSum = 0;
                    UINT c0 = 0, c1 = 0, c2 = 0;
                    for (int i = 0; i < 4; ++i) {
                        UINT a = px[i][3];
                        alphaSum += a;
                        c0 += (UINT)px[i][0] * a;
                        c1 += (UINT)px[i][1] * a;
                        c2 += (UINT)px[i][2] * a;
                    }
                    if (!alphaSum) {
                        // Dilate nearby visible colour into transparent texels.
                        // This prevents black/foreign atlas colours bleeding at lower mips.
                        int minX = ClampI((int)sx0 - 2, 0, (int)srcDesc.Width - 1);
                        int maxX = ClampI((int)sx1 + 2, 0, (int)srcDesc.Width - 1);
                        int minY = ClampI((int)sy0 - 2, 0, (int)srcDesc.Height - 1);
                        int maxY = ClampI((int)sy1 + 2, 0, (int)srcDesc.Height - 1);
                        for (int ny = minY; ny <= maxY; ++ny) {
                            BYTE* row = srcBits + ny * srcLock.Pitch;
                            for (int nx = minX; nx <= maxX; ++nx) {
                                BYTE* q = row + nx * 4;
                                UINT a = q[3];
                                if (a) {
                                    alphaSum += a;
                                    c0 += (UINT)q[0] * a;
                                    c1 += (UINT)q[1] * a;
                                    c2 += (UINT)q[2] * a;
                                }
                            }
                        }
                    }
                    if (alphaSum) {
                        d[0] = (BYTE)((c0 + alphaSum / 2) / alphaSum);
                        d[1] = (BYTE)((c1 + alphaSum / 2) / alphaSum);
                        d[2] = (BYTE)((c2 + alphaSum / 2) / alphaSum);
                    } else {
                        d[0] = (BYTE)(((UINT)px[0][0] + px[1][0] + px[2][0] + px[3][0] + 2) / 4);
                        d[1] = (BYTE)(((UINT)px[0][1] + px[1][1] + px[2][1] + px[3][1] + 2) / 4);
                        d[2] = (BYTE)(((UINT)px[0][2] + px[1][2] + px[2][2] + px[3][2] + 2) / 4);
                    }
                    UINT originalAlphaSum = (UINT)px[0][3] + px[1][3] + px[2][3] + px[3][3];
                    d[3] = (BYTE)((originalAlphaSum + 2) / 4);
                }
            }
        }

        if (alphaClass == 2 && srcDesc.Format == 21) PreserveCutoutCoverage(srcLock, srcDesc, dstLock, dstDesc);
        g_originalTextureUnlockRect(texture, level);
        g_originalTextureUnlockRect(texture, level - 1);
        generatedAny = true;
    }

    g_generatingMipmaps = FALSE;
    if (success && generatedAny) {
        if (!info->generated) ++g_generatedMipChains;
        info->generated = TRUE;
        info->skippedAlpha = FALSE;
        info->generationFailed = FALSE;
        if (g_texturePreLoad) g_texturePreLoad(texture);
        if (!g_mipGenerationLogged) {
            LogRaw("[Graphics] Automatic mipmap chain generated successfully.\r\n");
            g_mipGenerationLogged = TRUE;
        }
        return true;
    }

    if (!info->generationFailed) ++g_mipGenerationFailures;
    info->generationFailed = TRUE;
    if (!g_mipFailureLogged) {
        LogRaw("[Graphics] WARNING: a created mip chain could not be populated; that texture will use its base level.\r\n");
        g_mipFailureLogged = TRUE;
    }
    return false;
}

static void HandleBaseTextureUpload(void* texture) {
    TextureInfo* info = FindTextureInfo(texture);
    if (!info) return;
    info->contentReady = TRUE;
    info->uploadSeen = TRUE;
    info->generated = FALSE;
    info->generationFailed = FALSE;
    info->skippedAlpha = FALSE;
    info->alphaClassified = FALSE;
    info->alphaClass = 0;
    if (info->replacementReady) {
        // The source changed. Build a fresh smoothed replacement on the next 3D bind.
        info->replacementReady = FALSE;
        info->replacementFailed = FALSE;
        info->replacementTexture = 0;
    }
    if (info->edgeFixedReady) {
        info->edgeFixedReady = FALSE;
        info->edgeFixedFailed = FALSE;
        info->edgeFixedTexture = 0;
    }
    if (g_cfg.forceMipmaps && g_cfg.regenerateMipmapsOnUpload && !g_generatingMipmaps) {
        bool generated = GenerateMipChain(texture, true);
        if (generated && !g_uploadRegenerationLogged) {
            LogRaw("[Graphics] Mipmaps regenerated immediately after the real level-0 upload.\r\n");
            g_uploadRegenerationLogged = TRUE;
        }
        if (g_originalSetTextureStageState) {
            for (DWORD stage = 0; stage < 8; ++stage) {
                if (g_boundTextures[stage] == texture) {
                    g_originalSetTextureStageState(g_device, stage, 18, generated ? 2 : 0);
                }
            }
        }
    }
}

static HRESULT WINAPI HookSurfaceUnlockRect(void* surface) {
    if (!g_originalSurfaceUnlockRect) return (HRESULT)0x80004005L;
    HRESULT hr = g_originalSurfaceUnlockRect(surface);
    if (hr >= 0 && !g_generatingMipmaps) {
        SurfaceInfo* surfaceInfo = FindSurfaceInfo(surface);
        if (surfaceInfo && surfaceInfo->level == 0) HandleBaseTextureUpload(surfaceInfo->texture);
    }
    return hr;
}

static void HookSurfaceObject(void* surface) {
    if (!surface) return;
    void** table = *(void***)surface;
    if (!table) return;
    if (!g_originalSurfaceUnlockRect) {
        if (PatchPointer(&table[14], (void*)&HookSurfaceUnlockRect, (void**)&g_originalSurfaceUnlockRect)) {
            if (!g_surfaceTrackingLogged) {
                LogRaw("[Graphics] Surface-level texture upload tracking installed.\r\n");
                g_surfaceTrackingLogged = TRUE;
            }
        }
    }
}

static HRESULT WINAPI HookTextureGetSurfaceLevel(void* texture, UINT level, void** returnedSurface) {
    if (!g_originalTextureGetSurfaceLevel) return (HRESULT)0x80004005L;
    HRESULT hr = g_originalTextureGetSurfaceLevel(texture, level, returnedSurface);
    if (hr >= 0 && returnedSurface && *returnedSurface) {
        TrackSurface(*returnedSurface, texture, level);
        HookSurfaceObject(*returnedSurface);
    }
    return hr;
}

static HRESULT WINAPI HookTextureUnlockRect(void* texture, UINT level) {
    if (!g_originalTextureUnlockRect) return (HRESULT)0x80004005L;
    HRESULT hr = g_originalTextureUnlockRect(texture, level);
    if (hr >= 0 && level == 0 && !g_generatingMipmaps) HandleBaseTextureUpload(texture);
    return hr;
}

static void HookTextureObject(void* texture) {
    if (!texture) return;
    void** table = *(void***)texture;
    if (!table) return;
    if (!g_texturePreLoad) g_texturePreLoad = (TexturePreLoadFn)table[9];
    if (!g_textureGetLevelCount) g_textureGetLevelCount = (TextureGetLevelCountFn)table[13];
    if (!g_textureGetLevelDesc) g_textureGetLevelDesc = (TextureGetLevelDescFn)table[14];
    if (!g_originalTextureGetSurfaceLevel) {
        PatchPointer(&table[15], (void*)&HookTextureGetSurfaceLevel, (void**)&g_originalTextureGetSurfaceLevel);
    }
    if (!g_textureLockRect) g_textureLockRect = (TextureLockRectFn)table[16];
    if (!g_textureHooksInstalled) {
        if (PatchPointer(&table[17], (void*)&HookTextureUnlockRect, (void**)&g_originalTextureUnlockRect)) {
            g_textureHooksInstalled = TRUE;
            LogRaw("Texture mip-generation hook installed.\r\n");
        }
    }
}

static HRESULT WINAPI HookCreateTexture(void* device, UINT width, UINT height, UINT levels, DWORD usage, UINT format, UINT pool, void** returnedTexture) {
    if (!g_originalCreateTexture) return (HRESULT)0x80004005L;
    bool candidate = g_cfg.forceMipmaps && levels == 1 && usage == 0 && pool == 1 && width > 1 && height > 1 && (format == 21 || format == 22);
    HRESULT hr;
    if (candidate) {
        UINT requestedLevels = ComputeMipLevelCount(width, height);
        hr = g_originalCreateTexture(device, width, height, requestedLevels, usage, format, pool, returnedTexture);
        if (hr < 0) {
            ++g_mipFallbackCount;
            if (!g_mipFallbackLogged) {
                LogRaw("[Graphics] A texture rejected a mip chain; original one-level creation used for incompatible textures.\r\n");
                g_mipFallbackLogged = TRUE;
            }
            hr = g_originalCreateTexture(device, width, height, levels, usage, format, pool, returnedTexture);
        }
    } else {
        hr = g_originalCreateTexture(device, width, height, levels, usage, format, pool, returnedTexture);
    }
    if (hr >= 0 && returnedTexture && *returnedTexture) {
        HookTextureObject(*returnedTexture);
        if (candidate && g_textureGetLevelCount) {
            UINT createdLevels = g_textureGetLevelCount(*returnedTexture);
            TrackMipTexture(*returnedTexture, width, height, format, createdLevels);
        }
    }
    return hr;
}

static bool TextureUsesMipmaps(void* texture) {
    TextureInfo* info = FindTextureInfo(texture);
    return info && info->generated && !info->skippedAlpha && !info->generationFailed;
}

static void* RecoverRequestedTexture(void* actualTexture) {
    if (!actualTexture) return 0;
    for (int i = 0; i < g_textureCount; ++i) {
        if (g_textures[i].replacementTexture == actualTexture && g_textures[i].texture) return g_textures[i].texture;
        if (g_textures[i].edgeFixedTexture == actualTexture && g_textures[i].texture) return g_textures[i].texture;
    }
    return actualTexture;
}

static void RefreshBoundTexture(void* device, DWORD stage) {
    if (!device || stage > 7 || !g_originalGetTexture) return;
    void* texture = 0;
    if (g_originalGetTexture(device, stage, &texture) >= 0) {
        g_boundTextures[stage] = texture;
        g_requestedTextures[stage] = RecoverRequestedTexture(texture);
        if (texture) {
            void** table = *(void***)texture;
            if (table && table[2]) ((ComReleaseFn)table[2])(texture);
        }
    }
}

static void VerifyForcedFiltering(void* device, DWORD stage) {
    if (g_filterStateVerified || !g_originalGetTextureStageState || !g_cfg.logEnabled) return;
    if (g_projectionMode != 1 || !CurrentDrawAllowsMipmaps()) return;
    DWORD magFilter = 0, minFilter = 0, mipFilter = 0, maxMip = 0, maxAniso = 0, lodBits = 0;
    if (g_originalGetTextureStageState(device, stage, 16, &magFilter) < 0) return;
    g_originalGetTextureStageState(device, stage, 17, &minFilter);
    g_originalGetTextureStageState(device, stage, 18, &mipFilter);
    g_originalGetTextureStageState(device, stage, 20, &maxMip);
    g_originalGetTextureStageState(device, stage, 21, &maxAniso);
    g_originalGetTextureStageState(device, stage, 19, &lodBits);
    char m[16], a[16], b[16], c[16], d[16], e[16], buf[352];
    UIntToText(magFilter, m, 16);
    UIntToText(minFilter, a, 16);
    UIntToText(mipFilter, b, 16);
    UIntToText(maxMip, c, 16);
    UIntToText(maxAniso, d, 16);
    IntToText(RoundToInt(BitsFloat(lodBits) * 1000.0f), e, 16);
    int p = 0; buf[0] = 0;
    AppendText(buf, 352, &p, "[Graphics] Verified stage state: mag="); AppendText(buf, 352, &p, m);
    AppendText(buf, 352, &p, " min="); AppendText(buf, 352, &p, a);
    AppendText(buf, 352, &p, " mip="); AppendText(buf, 352, &p, b);
    AppendText(buf, 352, &p, " maxMip="); AppendText(buf, 352, &p, c);
    AppendText(buf, 352, &p, " maxAniso="); AppendText(buf, 352, &p, d);
    AppendText(buf, 352, &p, " lodBiasX1000="); AppendText(buf, 352, &p, e);
    AppendText(buf, 352, &p, "\r\n");
    LogRaw(buf);
    g_filterStateVerified = TRUE;
}

static void ApplyForcedFiltering(void* device, DWORD stage, void* texture, BOOL allowMipmaps) {
    if (!g_originalSetTextureStageState || stage > 7) return;
    if (g_cfg.anisotropicFiltering) {
        g_originalSetTextureStageState(device, stage, 16, 2); // MAGFILTER = LINEAR
        g_originalSetTextureStageState(device, stage, 17, 3); // MINFILTER = ANISOTROPIC
        g_originalSetTextureStageState(device, stage, 21, (DWORD)g_cfg.maxAnisotropy);
    } else if (g_cfg.textureSmoothing) {
        g_originalSetTextureStageState(device, stage, 16, 2); // MAGFILTER = LINEAR
        g_originalSetTextureStageState(device, stage, 17, 2); // MINFILTER = LINEAR
    }
    if (g_cfg.forceMipmaps) {
        g_originalSetTextureStageState(device, stage, 18, (allowMipmaps && TextureUsesMipmaps(texture)) ? 2 : 0);
        g_originalSetTextureStageState(device, stage, 20, 0);
        g_originalSetTextureStageState(device, stage, 19, FloatBits(g_cfg.mipLODBias));
    }
    VerifyForcedFiltering(device, stage);
}

static void ApplyForcedFilteringAllStages(void* device) {
    if (!device) return;
    for (DWORD stage = 0; stage < 8; ++stage) {
        RefreshBoundTexture(device, stage);
        ApplyForcedFiltering(device, stage, g_boundTextures[stage], CurrentDrawAllowsMipmaps());
    }
    g_filterStateDirty = FALSE;
}

static bool BuildUpscaledReplacement(TextureInfo* sourceInfo) {
    if (!sourceInfo || !sourceInfo->texture || sourceInfo->replacementReady) return sourceInfo && sourceInfo->replacementReady;
    if (sourceInfo->replacementFailed || g_cfg.worldTextureUpscale <= 1) return false;
    if (!sourceInfo->contentReady || !g_originalCreateTexture || !g_textureLockRect || !g_originalTextureUnlockRect) return false;
    if (sourceInfo->width < 4 || sourceInfo->height < 4) return false;
    if (sourceInfo->width > (UINT)g_cfg.upscaleMaxDimension || sourceInfo->height > (UINT)g_cfg.upscaleMaxDimension) return false;

    UINT alphaClass = sourceInfo->alphaClassified ? sourceInfo->alphaClass : ClassifyTextureAlpha(sourceInfo->texture, sourceInfo);
    if (!alphaClass) return false;
    // Runtime draw-state gating prevents replacements from being bound for alpha-blended
    // and alpha-tested geometry. UpscaleOpaqueOnly remains available as an extra guard.
    if (g_cfg.upscaleOpaqueOnly && alphaClass != 1) return false;

    UINT scale = (UINT)g_cfg.worldTextureUpscale;
    UINT outW = sourceInfo->width * scale;
    UINT outH = sourceInfo->height * scale;
    if (outW > 2048 || outH > 2048) return false;
    UINT outLevels = g_cfg.forceMipmaps ? ComputeMipLevelCount(outW, outH) : 1;
    void* replacement = 0;
    HRESULT hr = g_originalCreateTexture(g_device, outW, outH, outLevels, 0, sourceInfo->format, 1, &replacement);
    if (hr < 0 || !replacement) {
        sourceInfo->replacementFailed = TRUE;
        if (!g_upscaleFailureLogged) {
            LogRaw("[Graphics] WARNING: a smoothed world-texture replacement could not be created.\r\n");
            g_upscaleFailureLogged = TRUE;
        }
        return false;
    }

    HookTextureObject(replacement);
    UINT actualLevels = g_textureGetLevelCount ? g_textureGetLevelCount(replacement) : outLevels;
    TrackMipTexture(replacement, outW, outH, sourceInfo->format, actualLevels);
    TextureInfo* replacementInfo = FindTextureInfo(replacement);

    D3DSURFACE_DESC8 srcDesc, dstDesc;
    D3DLOCKED_RECT8 srcLock, dstLock;
    if (g_textureGetLevelDesc(sourceInfo->texture, 0, &srcDesc) < 0 ||
        g_textureGetLevelDesc(replacement, 0, &dstDesc) < 0 ||
        g_textureLockRect(sourceInfo->texture, 0, &srcLock, 0, 0x10) < 0) {
        sourceInfo->replacementFailed = TRUE;
        return false;
    }
    if (g_textureLockRect(replacement, 0, &dstLock, 0, 0) < 0) {
        g_originalTextureUnlockRect(sourceInfo->texture, 0);
        sourceInfo->replacementFailed = TRUE;
        return false;
    }

    BYTE* srcBits = (BYTE*)srcLock.pBits;
    BYTE* dstBits = (BYTE*)dstLock.pBits;
    for (UINT y = 0; y < outH; ++y) {
        float sy = ((float)y + 0.5f) / (float)scale - 0.5f;
        int iy = FloorToInt(sy);
        for (UINT x = 0; x < outW; ++x) {
            float sx = ((float)x + 0.5f) / (float)scale - 0.5f;
            int ix = FloorToInt(sx);
            float sumW = 0.0f;
            float c0 = 0.0f, c1 = 0.0f, c2 = 0.0f, ca = 0.0f;
            for (int j = -1; j <= 2; ++j) {
                int py = ClampI(iy + j, 0, (int)srcDesc.Height - 1);
                float wy = CubicWeight(sy - (float)(iy + j));
                BYTE* row = srcBits + py * srcLock.Pitch;
                for (int i = -1; i <= 2; ++i) {
                    int px = ClampI(ix + i, 0, (int)srcDesc.Width - 1);
                    float wx = CubicWeight(sx - (float)(ix + i));
                    float w = wx * wy;
                    BYTE* q = row + px * 4;
                    c0 += (float)q[0] * w;
                    c1 += (float)q[1] * w;
                    c2 += (float)q[2] * w;
                    ca += (float)(sourceInfo->format == 21 ? q[3] : 255) * w;
                    sumW += w;
                }
            }
            if (AbsF(sumW) < 0.00001f) sumW = 1.0f;
            BYTE* d = dstBits + y * dstLock.Pitch + x * 4;
            d[0] = ClampByteF(c0 / sumW);
            d[1] = ClampByteF(c1 / sumW);
            d[2] = ClampByteF(c2 / sumW);
            d[3] = sourceInfo->format == 21 ? ClampByteF(ca / sumW) : 255;
        }
    }

    g_originalTextureUnlockRect(replacement, 0);
    g_originalTextureUnlockRect(sourceInfo->texture, 0);

    if (replacementInfo) {
        replacementInfo->contentReady = TRUE;
        replacementInfo->uploadSeen = TRUE;
        replacementInfo->alphaClassified = TRUE;
        replacementInfo->alphaClass = alphaClass;
        replacementInfo->generated = FALSE;
        if (g_cfg.forceMipmaps) GenerateMipChain(replacement, true);
    }

    sourceInfo->replacementTexture = replacement;
    sourceInfo->replacementReady = TRUE;
    sourceInfo->replacementScale = scale;
    ++g_upscaledTextureCount;
    if (!g_upscaleLogged) {
        LogRaw("[Graphics] Perspective-only cubic texture upscaling enabled for low-resolution world textures.\r\n");
        g_upscaleLogged = TRUE;
    }
    return true;
}

static void LogAlphaEdgeFailureOnce(const char* reason) {
    if (g_alphaEdgeFailureLogged) return;
    LogRaw(reason);
    g_alphaEdgeFailureLogged = TRUE;
}

static bool BuildAlphaEdgeReplacement(TextureInfo* info) {
    if (!info || !info->texture || !g_cfg.alphaEdgeFix) return false;
    if (info->edgeFixedReady) return true;
    if (info->edgeFixedFailed || info->format != 21 || !g_device ||
        !g_originalCreateTexture || !g_textureGetLevelDesc ||
        !g_textureLockRect || !g_originalTextureUnlockRect) {
        LogAlphaEdgeFailureOnce("[Alpha] edge-colour replacement unavailable for the active cutout texture (format/hook mismatch).\r\n");
        return false;
    }

    UINT alphaClass = info->alphaClassified ? info->alphaClass : ClassifyTextureAlpha(info->texture, info);
    if (alphaClass != 2) {
        info->edgeFixedFailed = TRUE;
        return false;
    }

    D3DSURFACE_DESC8 desc;
    if (g_textureGetLevelDesc(info->texture, 0, &desc) < 0 || !desc.Width || !desc.Height) {
        info->edgeFixedFailed = TRUE;
        LogAlphaEdgeFailureOnce("[Alpha] edge-colour replacement failed while reading the source texture description.\r\n");
        return false;
    }

    void* replacement = 0;
    if (g_originalCreateTexture(g_device, desc.Width, desc.Height, 1, 0, 21, 1, &replacement) < 0 || !replacement) {
        info->edgeFixedFailed = TRUE;
        LogAlphaEdgeFailureOnce("[Alpha] edge-colour replacement texture creation failed.\r\n");
        return false;
    }
    HookTextureObject(replacement);

    D3DLOCKED_RECT8 srcLock, dstLock;
    if (g_textureLockRect(info->texture, 0, &srcLock, 0, 0x10) < 0 ||
        g_textureLockRect(replacement, 0, &dstLock, 0, 0) < 0) {
        if (srcLock.pBits) g_originalTextureUnlockRect(info->texture, 0);
        info->edgeFixedFailed = TRUE;
        LogAlphaEdgeFailureOnce("[Alpha] edge-colour replacement failed because the texture could not be locked.\r\n");
        return false;
    }

    BYTE* srcBits = (BYTE*)srcLock.pBits;
    BYTE* dstBits = (BYTE*)dstLock.pBits;
    const int radius = 4;
    for (UINT y = 0; y < desc.Height; ++y) {
        BYTE* srcRow = srcBits + y * srcLock.Pitch;
        BYTE* dstRow = dstBits + y * dstLock.Pitch;
        for (UINT x = 0; x < desc.Width; ++x) {
            BYTE* q = srcRow + x * 4;
            BYTE* d = dstRow + x * 4;
            d[0] = q[0]; d[1] = q[1]; d[2] = q[2]; d[3] = q[3];
            if (q[3] > 32) continue;

            bool found = false;
            for (int r = 1; r <= radius && !found; ++r) {
                int minX = ClampI((int)x - r, 0, (int)desc.Width - 1);
                int maxX = ClampI((int)x + r, 0, (int)desc.Width - 1);
                int minY = ClampI((int)y - r, 0, (int)desc.Height - 1);
                int maxY = ClampI((int)y + r, 0, (int)desc.Height - 1);
                UINT c0 = 0, c1 = 0, c2 = 0, weight = 0;
                for (int ny = minY; ny <= maxY; ++ny) {
                    BYTE* row = srcBits + ny * srcLock.Pitch;
                    for (int nx = minX; nx <= maxX; ++nx) {
                        if (nx != minX && nx != maxX && ny != minY && ny != maxY) continue;
                        BYTE* n = row + nx * 4;
                        if (n[3] >= 128) {
                            UINT w = n[3];
                            c0 += (UINT)n[0] * w;
                            c1 += (UINT)n[1] * w;
                            c2 += (UINT)n[2] * w;
                            weight += w;
                        }
                    }
                }
                if (weight) {
                    d[0] = (BYTE)((c0 + weight / 2) / weight);
                    d[1] = (BYTE)((c1 + weight / 2) / weight);
                    d[2] = (BYTE)((c2 + weight / 2) / weight);
                    found = true;
                }
            }
        }
    }

    g_originalTextureUnlockRect(replacement, 0);
    g_originalTextureUnlockRect(info->texture, 0);
    if (g_texturePreLoad) g_texturePreLoad(replacement);

    info->edgeFixedTexture = replacement;
    info->edgeFixedReady = TRUE;
    info->edgeFixedFailed = FALSE;
    if (!g_alphaEdgeLogged) {
        LogRaw("[Alpha] transparent RGB dilation enabled; blue/black texture fringes are replaced with nearby visible colour.\r\n");
        g_alphaEdgeLogged = TRUE;
    }
    return true;
}

static void* SelectAlphaSafeTexture(void* texture) {
    // The map foliage in this game is often rendered with ordinary alpha blend,
    // not with ALPHATESTENABLE. Restricting the edge fix to alpha-test draws
    // meant the replacement was never selected. Apply it to every confirmed
    // binary/cutout alpha texture in perspective rendering.
    if (!texture || !g_cfg.alphaEdgeFix || g_projectionMode != 1) return texture;
    TextureInfo* info = FindTextureInfo(texture);
    if (!info) return texture;
    UINT alphaClass = info->alphaClassified ? info->alphaClass : ClassifyTextureAlpha(texture, info);
    if (alphaClass != 2) return texture;
    if (!info->edgeFixedReady) BuildAlphaEdgeReplacement(info);
    return info->edgeFixedReady && info->edgeFixedTexture ? info->edgeFixedTexture : texture;
}

static BOOL CurrentDrawAllowsMipmaps() {
    if (g_projectionMode != 1) return FALSE;
    // Water/effects in this runner may also signal transparency by disabling
    // Z writes, even before alpha blending is toggled.
    if (!g_zWriteEnabled) return FALSE;
    if (g_alphaBlendEnabled && !g_cfg.mipmapsAlphaBlend) return FALSE;
    if (g_alphaTestEnabled && !g_cfg.mipmapsAlphaTest) return FALSE;
    return TRUE;
}

static BOOL CurrentDrawAllowsUpscale() {
    if (g_projectionMode != 1 || g_cfg.worldTextureUpscale <= 1) return FALSE;
    if (!g_cfg.upscaleTransparentDraws && (!g_zWriteEnabled || g_alphaBlendEnabled || g_alphaTestEnabled)) return FALSE;
    return TRUE;
}

static void* SelectTextureForBinding(void* texture, BOOL allowUpscale) {
    if (!texture) return texture;
    void* alphaSafe = SelectAlphaSafeTexture(texture);
    if (!allowUpscale) return alphaSafe;
    TextureInfo* info = FindTextureInfo(texture);
    if (!info) return alphaSafe;
    if (!info->contentReady) info->contentReady = TRUE;
    if (!info->replacementReady) BuildUpscaledReplacement(info);
    return info->replacementReady && info->replacementTexture ? info->replacementTexture : alphaSafe;
}

static HRESULT WINAPI HookSetTexture(void* device, DWORD stage, void* texture) {
    if (!g_originalSetTexture) return (HRESULT)0x80004005L;
    if (stage < 8) g_requestedTextures[stage] = texture;
    TextureInfo* originalInfo = FindTextureInfo(texture);
    if (originalInfo && !originalInfo->contentReady) originalInfo->contentReady = TRUE;
    if (texture && g_cfg.forceMipmaps && originalInfo && !originalInfo->generated && !originalInfo->skippedAlpha) {
        if (!g_mipLazyLogged) {
            LogRaw("[Graphics] Lazy mipmap generation triggered after texture upload/bind.\r\n");
            g_mipLazyLogged = TRUE;
        }
        GenerateMipChain(texture, false);
    }

    BOOL allowMipmaps = CurrentDrawAllowsMipmaps();
    BOOL allowUpscale = CurrentDrawAllowsUpscale();
    void* actualTexture = SelectTextureForBinding(texture, allowUpscale);
    HRESULT hr = g_originalSetTexture(device, stage, actualTexture);
    if (hr >= 0 && stage < 8) g_boundTextures[stage] = actualTexture;
    if (hr >= 0 && actualTexture) ApplyForcedFiltering(device, stage, actualTexture, allowMipmaps);
    return hr;
}

static void RefreshTransparencyRenderStates(void* device) {
    if (!g_originalGetRenderState || !device) return;
    DWORD value = 0;
    if (g_originalGetRenderState(device, 15, &value) >= 0) g_alphaTestEnabled = value ? TRUE : FALSE;
    if (g_originalGetRenderState(device, 27, &value) >= 0) g_alphaBlendEnabled = value ? TRUE : FALSE;
    if (g_originalGetRenderState(device, 14, &value) >= 0) g_zWriteEnabled = value ? TRUE : FALSE;
    if (g_originalGetRenderState(device, 24, &value) >= 0) g_alphaRef = value;
    if (g_originalGetRenderState(device, 25, &value) >= 0) g_alphaFunc = value;
    if (g_originalGetRenderState(device, 19, &value) >= 0) g_srcBlend = value;
    if (g_originalGetRenderState(device, 20, &value) >= 0) g_destBlend = value;
    if (g_originalGetRenderState(device, 23, &value) >= 0) g_zFunc = value;
    if (g_originalGetRenderState(device, 22, &value) >= 0) g_requestedCullMode = value;
    if (g_originalGetRenderState(device, 47, &value) >= 0) g_zBias = value;
}

static HRESULT WINAPI HookSetRenderState(void* device, UINT state, DWORD value) {
    if (!g_originalSetRenderState) return (HRESULT)0x80004005L;
    if (state == 161 && g_activeMSAA) value = 1;
    // Keep the game's requested cull mode. Distant missing faces are repaired
    // with a second reverse-cull pass at draw time instead of globally forcing
    // D3DCULL_NONE, which could make coincident front/back polygons z-fight.
    if (state == 22 && g_projectionMode == 1 && g_cfg.disableBackfaceCulling) {
        value = 1; // explicit user override only
    }
    HRESULT hr = g_originalSetRenderState(device, state, value);
    if (hr >= 0) {
        if (state == 15) g_alphaTestEnabled = value ? TRUE : FALSE;
        else if (state == 27) g_alphaBlendEnabled = value ? TRUE : FALSE;
        else if (state == 14) g_zWriteEnabled = value ? TRUE : FALSE;
        else if (state == 22) g_requestedCullMode = value;
        else if (state == 24) g_alphaRef = value;
        else if (state == 25) g_alphaFunc = value;
        else if (state == 19) g_srcBlend = value;
        else if (state == 20) g_destBlend = value;
        else if (state == 23) g_zFunc = value;
        else if (state == 47) g_zBias = value;
    }
    return hr;
}

static void PrepareTexturesForDraw(void* device) {
    // State blocks can bind textures and transparency states without passing
    // through SetTexture/SetRenderState. Synchronize from the real device right
    // before every draw so alpha classification and replacement selection use
    // the texture that is actually active.
    RefreshTransparencyRenderStates(device);
    RefreshBoundTexture(device, 0);
    if (!g_boundTextureSyncLogged && g_projectionMode == 1 && g_requestedTextures[0]) {
        LogRaw("[Alpha] active stage-0 texture synchronized from the device at draw time.\r\n");
        g_boundTextureSyncLogged = TRUE;
    }
    if (g_cfg.disableBackfaceCulling && g_projectionMode == 1 && g_originalSetRenderState) {
        g_originalSetRenderState(device, 22, 1);
        if (!g_twoSidedLogged) {
            LogRaw("[Geometry] Backface culling disabled for perspective draws.\r\n");
            g_twoSidedLogged = TRUE;
        }
    }
    BOOL allowMipmaps = CurrentDrawAllowsMipmaps();
    BOOL allowUpscale = CurrentDrawAllowsUpscale();
    for (DWORD stage = 0; stage < 8; ++stage) {
        void* requested = g_requestedTextures[stage];
        if (!requested) continue;
        void* actual = SelectTextureForBinding(requested, allowUpscale);
        if (actual != g_boundTextures[stage] && g_originalSetTexture) {
            if (g_originalSetTexture(device, stage, actual) >= 0) g_boundTextures[stage] = actual;
        }
        ApplyForcedFiltering(device, stage, actual, allowMipmaps);
    }
    if (allowMipmaps && !g_loggedOpaqueMipDraw) {
        LogRaw("[Graphics] Opaque perspective draw: mipmaps enabled.\r\n");
        g_loggedOpaqueMipDraw = TRUE;
    }
    if (!allowMipmaps && g_projectionMode == 1 && (!g_zWriteEnabled || g_alphaBlendEnabled || g_alphaTestEnabled) && !g_loggedTransparentSafeDraw) {
        LogRaw("[Graphics] Transparent/alpha-tested draw: original base texture restored and mip sampling disabled.\r\n");
        g_loggedTransparentSafeDraw = TRUE;
    }
    if (allowUpscale && !g_loggedOpaqueUpscaleDraw) {
        LogRaw("[Graphics] Opaque perspective draw: cubic texture smoothing/upscale allowed.\r\n");
        g_loggedOpaqueUpscaleDraw = TRUE;
    }
}

struct DrawOverrideState {
    DWORD oldCull;
    DWORD oldBias;
    BOOL cullChanged;
    BOOL biasChanged;
};

static DWORD MixBiasHash(DWORD x) {
    x ^= x >> 16;
    x *= 0x7FEB352DUL;
    x ^= x >> 15;
    x *= 0x846CA68BUL;
    x ^= x >> 16;
    return x;
}

static DWORD ComputeStableMapBias(UINT drawKey) {
    UINT layers = (UINT)(g_cfg.mapModelZBiasLayers > 0 ? g_cfg.mapModelZBiasLayers : 1);
    if (layers > 16) layers = 16;
    void* texture = g_requestedTextures[0];
    if (!texture && g_boundTextures[0]) texture = RecoverRequestedTexture(g_boundTextures[0]);
    DWORD h = g_worldBiasHash ^ (DWORD)texture ^ (drawKey * 0x9E3779B9UL);
    h = MixBiasHash(h);
    // Never return zero: zero is the game's original plane and cannot separate
    // two coincident draws. D3D8 accepts integer ZBIAS values 0..16.
    return 1 + (h % layers);
}

static void BeginDrawOverrides(void* device, DrawOverrideState* state, UINT drawKey) {
    if (!state) return;
    state->oldCull = g_requestedCullMode;
    state->oldBias = g_zBias;
    state->cullChanged = FALSE;
    state->biasChanged = FALSE;
    if (!device || g_projectionMode != 1 || !g_originalSetRenderState) return;

    if (g_cfg.disableBackfaceCulling) {
        if (g_originalGetRenderState) g_originalGetRenderState(device, 22, &state->oldCull);
        if (g_originalSetRenderState(device, 22, 1) >= 0) state->cullChanged = TRUE;
    }

    if (g_cfg.mapModelZBias && g_largeMapTransform) {
        // Use a deterministic per-draw/per-texture/per-transform bias. The old
        // serial reset on every world matrix made the first subset always get
        // bias zero, so many independently transformed coplanar surfaces were
        // never separated at all.
        void* requested0 = g_requestedTextures[0];
        if (!requested0 && g_boundTextures[0]) requested0 = RecoverRequestedTexture(g_boundTextures[0]);
        TextureInfo* ti = FindTextureInfo(requested0);
        UINT alphaClass = ti ? (ti->alphaClassified ? ti->alphaClass : ClassifyTextureAlpha(requested0, ti)) : 1;
        if (alphaClass == 1 && g_zWriteEnabled && !g_alphaBlendEnabled) {
            if (g_originalGetRenderState) g_originalGetRenderState(device, 47, &state->oldBias);
            DWORD bias = ComputeStableMapBias(drawKey);
            if (g_originalSetRenderState(device, 47, bias) >= 0) {
                state->biasChanged = TRUE;
                if (!g_mapModelBiasLogged) {
                    LogRaw("[Depth] stable hashed ZBIAS active for opaque map draws; texture, transform and draw range select the layer.\r\n");
                    g_mapModelBiasLogged = TRUE;
                }
            }
        }
    }
}

static void EndDrawOverrides(void* device, const DrawOverrideState* state) {
    if (!device || !state || !g_originalSetRenderState) return;
    if (state->biasChanged) g_originalSetRenderState(device, 47, state->oldBias);
    if (state->cullChanged) g_originalSetRenderState(device, 22, state->oldCull);
}

struct AlphaPassState {
    DWORD alphaTest;
    DWORD alphaBlend;
    DWORD alphaRef;
    DWORD alphaFunc;
    DWORD srcBlend;
    DWORD destBlend;
    DWORD zWrite;
    DWORD zFunc;
};

static BOOL ShouldUseDualPass(void* device) {
    if (!g_cfg.dualPassAlpha || g_projectionMode != 1) return FALSE;
    RefreshBoundTexture(device, 0);
    void* texture = g_requestedTextures[0];
    if (!texture && g_boundTextures[0]) texture = RecoverRequestedTexture(g_boundTextures[0]);
    TextureInfo* info = FindTextureInfo(texture);
    if (!info) return FALSE;
    UINT alphaClass = info->alphaClassified ? info->alphaClass : ClassifyTextureAlpha(texture, info);
    BOOL transparencyDraw = g_alphaBlendEnabled || g_alphaTestEnabled || !g_zWriteEnabled || g_largeMapTransform;
    if (alphaClass == 2 && transparencyDraw && !g_cutoutDetectedLogged) {
        LogRaw("[Alpha] binary/almost-binary cutout texture detected from the actual stage-0 binding.\r\n");
        g_cutoutDetectedLogged = TRUE;
    }
    return (alphaClass == 2 && transparencyDraw) ? TRUE : FALSE;
}

static void SaveAlphaPassState(void* device, AlphaPassState* state) {
    if (!state) return;
    state->alphaTest = g_alphaTestEnabled ? 1 : 0;
    state->alphaBlend = g_alphaBlendEnabled ? 1 : 0;
    state->alphaRef = g_alphaRef;
    state->alphaFunc = g_alphaFunc;
    state->srcBlend = g_srcBlend;
    state->destBlend = g_destBlend;
    state->zWrite = g_zWriteEnabled ? 1 : 0;
    state->zFunc = g_zFunc;
    if (!g_originalGetRenderState) return;
    g_originalGetRenderState(device, 15, &state->alphaTest);
    g_originalGetRenderState(device, 27, &state->alphaBlend);
    g_originalGetRenderState(device, 24, &state->alphaRef);
    g_originalGetRenderState(device, 25, &state->alphaFunc);
    g_originalGetRenderState(device, 19, &state->srcBlend);
    g_originalGetRenderState(device, 20, &state->destBlend);
    g_originalGetRenderState(device, 14, &state->zWrite);
    g_originalGetRenderState(device, 23, &state->zFunc);
}

static void SetDualPassOpaqueState(void* device, DWORD zFunc) {
    if (!g_originalSetRenderState) return;
    g_originalSetRenderState(device, 15, 1); // ALPHATESTENABLE
    g_originalSetRenderState(device, 24, (DWORD)g_cfg.dualPassAlphaRef);
    g_originalSetRenderState(device, 25, 7); // GREATEREQUAL
    g_originalSetRenderState(device, 27, 0); // ALPHABLENDENABLE
    g_originalSetRenderState(device, 14, 1); // ZWRITEENABLE
    g_originalSetRenderState(device, 23, zFunc);
}

static void SetDualPassEdgeState(void* device, DWORD zFunc) {
    if (!g_originalSetRenderState) return;
    g_originalSetRenderState(device, 15, 1);
    g_originalSetRenderState(device, 24, (DWORD)g_cfg.dualPassAlphaRef);
    g_originalSetRenderState(device, 25, 2); // LESS: only soft edge below first-pass threshold
    g_originalSetRenderState(device, 27, 1);
    g_originalSetRenderState(device, 19, 5); // SRCALPHA
    g_originalSetRenderState(device, 20, 6); // INVSRCALPHA
    g_originalSetRenderState(device, 14, 0);
    g_originalSetRenderState(device, 23, zFunc);
}

static void RestoreAlphaPassState(void* device, const AlphaPassState* state) {
    if (!state || !g_originalSetRenderState) return;
    g_originalSetRenderState(device, 15, state->alphaTest);
    g_originalSetRenderState(device, 27, state->alphaBlend);
    g_originalSetRenderState(device, 24, state->alphaRef);
    g_originalSetRenderState(device, 25, state->alphaFunc);
    g_originalSetRenderState(device, 19, state->srcBlend);
    g_originalSetRenderState(device, 20, state->destBlend);
    g_originalSetRenderState(device, 14, state->zWrite);
    g_originalSetRenderState(device, 23, state->zFunc);
}

struct BackfacePassState {
    DWORD oldCull;
    DWORD oldZFunc;
    BOOL active;
};

static BOOL BeginBackfaceCompletion(void* device, BackfacePassState* state) {
    if (!state) return FALSE;
    state->active = FALSE;
    state->oldCull = g_requestedCullMode;
    state->oldZFunc = g_zFunc;
    if (!device || !g_cfg.fixDistantBackfaces || g_projectionMode != 1 || !g_originalSetRenderState) return FALSE;
    if (g_cfg.disableBackfaceCulling || g_requestedCullMode == 1 || g_requestedCullMode == 0) return FALSE;
    if (g_originalGetRenderState) {
        g_originalGetRenderState(device, 22, &state->oldCull);
        g_originalGetRenderState(device, 23, &state->oldZFunc);
    }
    DWORD opposite = state->oldCull == 2 ? 3 : 2;
    if (g_originalSetRenderState(device, 22, opposite) < 0) return FALSE;
    // Strict LESS prevents the completion pass from redrawing equal-depth
    // front faces, while still admitting the opposite-winding wall that the
    // original pass culled.
    g_originalSetRenderState(device, 23, 2);
    state->active = TRUE;
    if (!g_backfaceCompletionLogged) {
        LogRaw("[Geometry] reverse-cull completion pass active; distant back walls are added without globally disabling culling.\r\n");
        g_backfaceCompletionLogged = TRUE;
    }
    return TRUE;
}

static void EndBackfaceCompletion(void* device, const BackfacePassState* state) {
    if (!state || !state->active || !g_originalSetRenderState) return;
    g_originalSetRenderState(device, 22, state->oldCull);
    g_originalSetRenderState(device, 23, state->oldZFunc);
}

static HRESULT DrawPrimitivePasses(void* device, UINT type, UINT startVertex, UINT primitiveCount, BOOL dual, DWORD baseZFunc) {
    if (!dual) return g_originalDrawPrimitive(device, type, startVertex, primitiveCount);
    SetDualPassOpaqueState(device, baseZFunc);
    HRESULT hr = g_originalDrawPrimitive(device, type, startVertex, primitiveCount);
    SetDualPassEdgeState(device, 4);
    HRESULT hr2 = g_originalDrawPrimitive(device, type, startVertex, primitiveCount);
    return hr < 0 ? hr : hr2;
}

static HRESULT WINAPI HookDrawPrimitive(void* device, UINT type, UINT startVertex, UINT primitiveCount) {
    PrepareTexturesForDraw(device);
    if (!g_originalDrawPrimitive) return (HRESULT)0x80004005L;
    UINT drawKey = type ^ (startVertex * 131U) ^ (primitiveCount * 65537U);
    DrawOverrideState drawState;
    BeginDrawOverrides(device, &drawState, drawKey);
    BOOL dual = ShouldUseDualPass(device);
    AlphaPassState saved;
    if (dual) SaveAlphaPassState(device, &saved);
    HRESULT result = DrawPrimitivePasses(device, type, startVertex, primitiveCount, dual, dual ? saved.zFunc : g_zFunc);
    if (dual) {
        RestoreAlphaPassState(device, &saved);
        if (!g_dualPassLogged) { LogRaw("[Alpha] cutout dual-pass executed: opaque depth pass plus blended edge pass.\r\n"); g_dualPassLogged = TRUE; }
    }
    BackfacePassState back;
    if (BeginBackfaceCompletion(device, &back)) {
        if (dual) {
            SetDualPassOpaqueState(device, 2);
            g_originalDrawPrimitive(device, type, startVertex, primitiveCount);
            SetDualPassEdgeState(device, 4);
            g_originalDrawPrimitive(device, type, startVertex, primitiveCount);
            RestoreAlphaPassState(device, &saved);
        } else {
            g_originalDrawPrimitive(device, type, startVertex, primitiveCount);
        }
        EndBackfaceCompletion(device, &back);
    }
    EndDrawOverrides(device, &drawState);
    return result;
}

static HRESULT WINAPI HookDrawIndexedPrimitive(void* device, UINT type, UINT minIndex, UINT numVertices, UINT startIndex, UINT primitiveCount) {
    PrepareTexturesForDraw(device);
    if (!g_originalDrawIndexedPrimitive) return (HRESULT)0x80004005L;
    UINT drawKey = type ^ (minIndex * 31U) ^ (numVertices * 131U) ^ (startIndex * 8191U) ^ (primitiveCount * 65537U);
    DrawOverrideState drawState;
    BeginDrawOverrides(device, &drawState, drawKey);
    BOOL dual = ShouldUseDualPass(device);
    AlphaPassState saved;
    if (dual) SaveAlphaPassState(device, &saved);
    HRESULT result;
    if (!dual) result = g_originalDrawIndexedPrimitive(device, type, minIndex, numVertices, startIndex, primitiveCount);
    else {
        SetDualPassOpaqueState(device, saved.zFunc);
        HRESULT hr = g_originalDrawIndexedPrimitive(device, type, minIndex, numVertices, startIndex, primitiveCount);
        SetDualPassEdgeState(device, 4);
        HRESULT hr2 = g_originalDrawIndexedPrimitive(device, type, minIndex, numVertices, startIndex, primitiveCount);
        RestoreAlphaPassState(device, &saved);
        result = hr < 0 ? hr : hr2;
        if (!g_dualPassLogged) { LogRaw("[Alpha] cutout dual-pass executed: opaque depth pass plus blended edge pass.\r\n"); g_dualPassLogged = TRUE; }
    }
    BackfacePassState back;
    if (BeginBackfaceCompletion(device, &back)) {
        if (dual) {
            SetDualPassOpaqueState(device, 2);
            g_originalDrawIndexedPrimitive(device, type, minIndex, numVertices, startIndex, primitiveCount);
            SetDualPassEdgeState(device, 4);
            g_originalDrawIndexedPrimitive(device, type, minIndex, numVertices, startIndex, primitiveCount);
            RestoreAlphaPassState(device, &saved);
        } else {
            g_originalDrawIndexedPrimitive(device, type, minIndex, numVertices, startIndex, primitiveCount);
        }
        EndBackfaceCompletion(device, &back);
    }
    EndDrawOverrides(device, &drawState);
    return result;
}

static HRESULT WINAPI HookDrawPrimitiveUP(void* device, UINT type, UINT primitiveCount, const void* data, UINT stride) {
    PrepareTexturesForDraw(device);
    if (!g_originalDrawPrimitiveUP) return (HRESULT)0x80004005L;
    UINT drawKey = type ^ (primitiveCount * 65537U) ^ (stride * 257U);
    DrawOverrideState drawState;
    BeginDrawOverrides(device, &drawState, drawKey);
    BOOL dual = ShouldUseDualPass(device);
    AlphaPassState saved;
    if (dual) SaveAlphaPassState(device, &saved);
    HRESULT result;
    if (!dual) result = g_originalDrawPrimitiveUP(device, type, primitiveCount, data, stride);
    else {
        SetDualPassOpaqueState(device, saved.zFunc);
        HRESULT hr = g_originalDrawPrimitiveUP(device, type, primitiveCount, data, stride);
        SetDualPassEdgeState(device, 4);
        HRESULT hr2 = g_originalDrawPrimitiveUP(device, type, primitiveCount, data, stride);
        RestoreAlphaPassState(device, &saved);
        result = hr < 0 ? hr : hr2;
        if (!g_dualPassLogged) { LogRaw("[Alpha] cutout dual-pass executed: opaque depth pass plus blended edge pass.\r\n"); g_dualPassLogged = TRUE; }
    }
    BackfacePassState back;
    if (BeginBackfaceCompletion(device, &back)) {
        if (dual) {
            SetDualPassOpaqueState(device, 2);
            g_originalDrawPrimitiveUP(device, type, primitiveCount, data, stride);
            SetDualPassEdgeState(device, 4);
            g_originalDrawPrimitiveUP(device, type, primitiveCount, data, stride);
            RestoreAlphaPassState(device, &saved);
        } else {
            g_originalDrawPrimitiveUP(device, type, primitiveCount, data, stride);
        }
        EndBackfaceCompletion(device, &back);
    }
    EndDrawOverrides(device, &drawState);
    return result;
}

static HRESULT WINAPI HookDrawIndexedPrimitiveUP(void* device, UINT type, UINT minVertexIndex, UINT numVertices, UINT primitiveCount, const void* indexData, UINT indexFormat, const void* vertexData, UINT stride) {
    PrepareTexturesForDraw(device);
    if (!g_originalDrawIndexedPrimitiveUP) return (HRESULT)0x80004005L;
    UINT drawKey = type ^ (minVertexIndex * 31U) ^ (numVertices * 131U) ^ (primitiveCount * 65537U) ^ (stride * 257U);
    DrawOverrideState drawState;
    BeginDrawOverrides(device, &drawState, drawKey);
    BOOL dual = ShouldUseDualPass(device);
    AlphaPassState saved;
    if (dual) SaveAlphaPassState(device, &saved);
    HRESULT result;
    if (!dual) result = g_originalDrawIndexedPrimitiveUP(device, type, minVertexIndex, numVertices, primitiveCount, indexData, indexFormat, vertexData, stride);
    else {
        SetDualPassOpaqueState(device, saved.zFunc);
        HRESULT hr = g_originalDrawIndexedPrimitiveUP(device, type, minVertexIndex, numVertices, primitiveCount, indexData, indexFormat, vertexData, stride);
        SetDualPassEdgeState(device, 4);
        HRESULT hr2 = g_originalDrawIndexedPrimitiveUP(device, type, minVertexIndex, numVertices, primitiveCount, indexData, indexFormat, vertexData, stride);
        RestoreAlphaPassState(device, &saved);
        result = hr < 0 ? hr : hr2;
        if (!g_dualPassLogged) { LogRaw("[Alpha] cutout dual-pass executed: opaque depth pass plus blended edge pass.\r\n"); g_dualPassLogged = TRUE; }
    }
    BackfacePassState back;
    if (BeginBackfaceCompletion(device, &back)) {
        if (dual) {
            SetDualPassOpaqueState(device, 2);
            g_originalDrawIndexedPrimitiveUP(device, type, minVertexIndex, numVertices, primitiveCount, indexData, indexFormat, vertexData, stride);
            SetDualPassEdgeState(device, 4);
            g_originalDrawIndexedPrimitiveUP(device, type, minVertexIndex, numVertices, primitiveCount, indexData, indexFormat, vertexData, stride);
            RestoreAlphaPassState(device, &saved);
        } else {
            g_originalDrawIndexedPrimitiveUP(device, type, minVertexIndex, numVertices, primitiveCount, indexData, indexFormat, vertexData, stride);
        }
        EndBackfaceCompletion(device, &back);
    }
    EndDrawOverrides(device, &drawState);
    return result;
}

static HRESULT WINAPI HookSetTextureStageState(void* device, DWORD stage, UINT type, DWORD value) {
    if (!g_originalSetTextureStageState) return (HRESULT)0x80004005L;
    void* texture = stage < 8 ? g_boundTextures[stage] : 0;
    if (g_cfg.anisotropicFiltering) {
        if (type == 16) value = 2;
        else if (type == 17) value = 3;
        else if (type == 21) value = (DWORD)g_cfg.maxAnisotropy;
    } else if (g_cfg.textureSmoothing) {
        if (type == 16 || type == 17) value = 2;
    }
    if (g_cfg.forceMipmaps) {
        if (type == 18) value = (CurrentDrawAllowsMipmaps() && TextureUsesMipmaps(texture)) ? 2 : 0;
        else if (type == 20) value = 0;
        else if (type == 19) value = FloatBits(g_cfg.mipLODBias);
    }
    return g_originalSetTextureStageState(device, stage, type, value);
}

static HRESULT WINAPI HookApplyStateBlock(void* device, DWORD token) {
    if (!g_originalApplyStateBlock) return (HRESULT)0x80004005L;
    HRESULT hr = g_originalApplyStateBlock(device, token);
    if (hr >= 0) RefreshTransparencyRenderStates(device);
    if (hr >= 0 && (g_cfg.forceMipmaps || g_cfg.anisotropicFiltering || g_cfg.textureSmoothing)) {
        ++g_stateBlockReapplyCount;
        ApplyForcedFilteringAllStages(device);
        if (g_stateBlockReapplyCount == 1) {
            LogRaw("[Graphics] Texture filtering restored after a Direct3D state block.\r\n");
        }
    }
    return hr;
}

static void ApplyRunnerFix() {
    // v0.5 deliberately leaves GameMaker's 1024x768 logical drawing region
    // and room view structures untouched. The previous builds changed those
    // values and caused the 4:3 scene to be magnified/cropped.
}

static bool IsPerspective(const D3DMATRIX8& m) {
    return AbsF(m._34) > 0.25f && AbsF(m._44) < 0.01f && AbsF(m._11) > 0.000001f && AbsF(m._22) > 0.000001f;
}

static bool IsOrthographic2D(const D3DMATRIX8& m) {
    if (AbsF(m._34) > 0.01f || AbsF(m._44 - 1.0f) > 0.01f) return false;
    if (AbsF(m._11) < 0.000001f || AbsF(m._22) < 0.000001f) return false;
    float aspect = AbsF(m._22 / m._11);
    return aspect > 0.5f && aspect < 4.0f;
}

static void ComputeFitViewport(D3DVIEWPORT8* out) {
    if (!out) return;
    float refAspect = g_cfg.referenceAspect;
    if (refAspect < 0.5f) refAspect = 1.3333333f;
    UINT w = g_backBufferWidth;
    UINT h = (UINT)((float)w / refAspect + 0.5f);
    if (h > g_backBufferHeight) {
        h = g_backBufferHeight;
        w = (UINT)((float)h * refAspect + 0.5f);
    }
    if (w < 1) w = 1;
    if (h < 1) h = 1;
    out->X = (g_backBufferWidth - w) / 2;
    out->Y = (g_backBufferHeight - h) / 2;
    out->Width = w;
    out->Height = h;
    out->MinZ = 0.0f;
    out->MaxZ = 1.0f;
}

static void ComputeFullViewport(D3DVIEWPORT8* out) {
    if (!out) return;
    out->X = 0;
    out->Y = 0;
    out->Width = g_backBufferWidth;
    out->Height = g_backBufferHeight;
    out->MinZ = 0.0f;
    out->MaxZ = 1.0f;
}

static void MapLogicalViewportToFit(const D3DVIEWPORT8* in, D3DVIEWPORT8* out) {
    if (!in || !out) return;
    D3DVIEWPORT8 fit;
    ComputeFitViewport(&fit);
    *out = *in;
    UINT logicalW = g_originalBackBufferWidth ? g_originalBackBufferWidth : 1024;
    UINT logicalH = g_originalBackBufferHeight ? g_originalBackBufferHeight : 768;

    // The GameMaker runner normally supplies viewport coordinates in its
    // original 1024x768 output space. Convert only those logical coordinates;
    // if the runner already produced a target-sized viewport, preserve it.
    if (in->Width <= logicalW + 2 && in->Height <= logicalH + 2 &&
        in->X <= logicalW && in->Y <= logicalH) {
        out->X = fit.X + (DWORD)((in->X * fit.Width) / logicalW);
        out->Y = fit.Y + (DWORD)((in->Y * fit.Height) / logicalH);
        out->Width = (DWORD)((in->Width * fit.Width) / logicalW);
        out->Height = (DWORD)((in->Height * fit.Height) / logicalH);
        if (out->Width < 1) out->Width = 1;
        if (out->Height < 1) out->Height = 1;
    }
}

static void LogMatrixMode(const char* label, const D3DMATRIX8& m, const D3DVIEWPORT8& vp) {
    if (!g_cfg.logRunnerState) return;
    int aspect1000 = 0;
    if (AbsF(m._11) > 0.000001f) aspect1000 = RoundToInt(AbsF(m._22 / m._11) * 1000.0f);
    char a[16], x[16], y[16], w[16], h[16], buf[320];
    IntToText(aspect1000, a, 16);
    IntToText((int)vp.X, x, 16); IntToText((int)vp.Y, y, 16);
    IntToText((int)vp.Width, w, 16); IntToText((int)vp.Height, h, 16);
    int p=0; buf[0]=0;
    AppendText(buf,320,&p,label);
    AppendText(buf,320,&p," aspect x1000="); AppendText(buf,320,&p,a);
    AppendText(buf,320,&p," viewport="); AppendText(buf,320,&p,x); AppendText(buf,320,&p,",");
    AppendText(buf,320,&p,y); AppendText(buf,320,&p," "); AppendText(buf,320,&p,w);
    AppendText(buf,320,&p,"x"); AppendText(buf,320,&p,h); AppendText(buf,320,&p,"\r\n");
    LogRaw(buf);
}

static bool IsReferenceViewport(const D3DVIEWPORT8& vp) {
    if (vp.Width == 0 || vp.Height == 0) return false;
    float aspect = (float)vp.Width / (float)vp.Height;
    float delta = aspect - g_cfg.referenceAspect;
    if (delta < 0.0f) delta = -delta;
    return delta < 0.04f;
}

static void LogRawViewportOnce(const D3DVIEWPORT8& vp) {
    if (g_rawViewportLogged || !g_cfg.logRunnerState) return;
    D3DMATRIX8 dummy = {};
    dummy._11 = 1.0f;
    dummy._22 = (float)vp.Width / (float)(vp.Height ? vp.Height : 1);
    LogMatrixMode("[Viewport] Runner", dummy, vp);
    g_rawViewportLogged = TRUE;
}


static bool AdjustPerspectiveDepth(D3DMATRIX8* matrix) {
    if (!matrix || !g_cfg.depthPrecisionFix) return false;
    float originalNear = 0.0f;
    float originalFar = 0.0f;
    bool leftHanded = matrix->_34 > 0.0f;

    if (leftHanded) {
        if (AbsF(matrix->_33) < 0.000001f || AbsF(1.0f - matrix->_33) < 0.000001f) return false;
        originalNear = -matrix->_43 / matrix->_33;
        originalFar = matrix->_43 / (1.0f - matrix->_33);
    } else {
        if (AbsF(matrix->_33) < 0.000001f || AbsF(matrix->_33 + 1.0f) < 0.000001f) return false;
        originalNear = matrix->_43 / matrix->_33;
        originalFar = matrix->_43 / (matrix->_33 + 1.0f);
    }

    if (originalNear < 0.0f) originalNear = -originalNear;
    if (originalFar < 0.0f) originalFar = -originalFar;
    if (originalNear < 0.001f || originalFar <= originalNear + 0.01f || originalFar > 1000000.0f) return false;

    float newNear = originalNear;
    if (g_cfg.nearClip > newNear) newNear = g_cfg.nearClip;
    float newFar = originalFar;
    if (g_cfg.farClip > newNear + 0.01f) newFar = g_cfg.farClip;
    if (newFar <= newNear + 0.01f) return false;

    if (leftHanded) {
        matrix->_33 = newFar / (newFar - newNear);
        matrix->_43 = -(newNear * newFar) / (newFar - newNear);
    } else {
        matrix->_33 = newFar / (newNear - newFar);
        matrix->_43 = (newNear * newFar) / (newNear - newFar);
    }

    if (!g_depthPrecisionLogged && g_cfg.logRunnerState) {
        char a[16], b[16], c[16], d[16], buf[320];
        IntToText(RoundToInt(originalNear * 1000.0f), a, 16);
        IntToText(RoundToInt(originalFar * 1000.0f), b, 16);
        IntToText(RoundToInt(newNear * 1000.0f), c, 16);
        IntToText(RoundToInt(newFar * 1000.0f), d, 16);
        int p = 0; buf[0] = 0;
        AppendText(buf, 320, &p, "[Depth] projection near/far x1000: ");
        AppendText(buf, 320, &p, a); AppendText(buf, 320, &p, "/"); AppendText(buf, 320, &p, b);
        AppendText(buf, 320, &p, " -> "); AppendText(buf, 320, &p, c); AppendText(buf, 320, &p, "/"); AppendText(buf, 320, &p, d);
        AppendText(buf, 320, &p, "\r\n");
        LogRaw(buf);
        g_depthPrecisionLogged = TRUE;
    }
    return true;
}


static HRESULT WINAPI HookCreateDepthStencilSurface(void* device, UINT width, UINT height, UINT format,
                                                     UINT multisample, void** returnedSurface) {
    if (!g_originalCreateDepthStencilSurface) return (HRESULT)0x80004005L;
    UINT desiredFormat = g_selectedDepthFormat ? g_selectedDepthFormat : format;
    UINT desiredMSAA = g_activeMSAA ? g_activeMSAA : multisample;
    HRESULT hr = g_originalCreateDepthStencilSurface(device, width, height, desiredFormat, desiredMSAA, returnedSurface);
    if (hr < 0 && (desiredFormat != format || desiredMSAA != multisample)) {
        hr = g_originalCreateDepthStencilSurface(device, width, height, format, desiredMSAA, returnedSurface);
    }
    if (hr < 0 && desiredMSAA != multisample) {
        hr = g_originalCreateDepthStencilSurface(device, width, height, format, multisample, returnedSurface);
    }
    if (hr >= 0 && !g_depthSurfaceLogged && g_cfg.logRunnerState) {
        char a[16], b[16], c[16], d[16], buf[280];
        IntToText((int)format, a, 16); IntToText((int)desiredFormat, b, 16);
        IntToText((int)multisample, c, 16); IntToText((int)desiredMSAA, d, 16);
        int p = 0; buf[0] = 0;
        AppendText(buf, 280, &p, "[Depth] surface format/MSAA requested ");
        AppendText(buf, 280, &p, a); AppendText(buf, 280, &p, "/"); AppendText(buf, 280, &p, c);
        AppendText(buf, 280, &p, " -> "); AppendText(buf, 280, &p, b); AppendText(buf, 280, &p, "/"); AppendText(buf, 280, &p, d);
        AppendText(buf, 280, &p, "\r\n");
        LogRaw(buf);
        g_depthSurfaceLogged = TRUE;
    }
    return hr;
}

static HRESULT WINAPI HookSetTransform(void* device, UINT state, const D3DMATRIX8* matrix) {
    if (!g_originalSetTransform || !matrix) {
        return g_originalSetTransform ? g_originalSetTransform(device, state, matrix) : (HRESULT)0x80004005L;
    }

    // D3DTS_WORLD and its indexed variants start at 256. The city partitions
    // are drawn with a scale around 580, while characters/vehicles are roughly
    // 6-11. This provides a precise map-only discriminator without altering
    // gameplay objects.
    if (state >= 256 && state <= 259) {
        float maxElement = AbsF(matrix->_11);
        float values[8] = {matrix->_12, matrix->_13, matrix->_21, matrix->_22, matrix->_23, matrix->_31, matrix->_32, matrix->_33};
        for (int i = 0; i < 8; ++i) { float v = AbsF(values[i]); if (v > maxElement) maxElement = v; }
        g_worldMaxElement = maxElement;
        g_largeMapTransform = maxElement >= g_cfg.mapScaleThreshold ? TRUE : FALSE;
        DWORD h = 2166136261UL;
        const float* mf = (const float*)matrix;
        for (int i = 0; i < 16; ++i) { h ^= FloatBits(mf[i]); h *= 16777619UL; }
        g_worldBiasHash = h;
        return g_originalSetTransform(device, state, matrix);
    }

    if (state != 3 || !g_backBufferWidth || !g_backBufferHeight) {
        return g_originalSetTransform(device, state, matrix);
    }

    if (g_cfg.correctPerspective && IsPerspective(*matrix)) {
        D3DMATRIX8 fixed = *matrix;
        AdjustPerspectiveDepth(&fixed);
        const float targetAspect = (float)g_backBufferWidth / (float)g_backBufferHeight;
        float sign = fixed._11 < 0.0f ? -1.0f : 1.0f;
        fixed._11 = sign * (AbsF(fixed._22) / (targetAspect * g_cfg.horizontalFOVScale));
        HRESULT hr = g_originalSetTransform(device, state, &fixed);
        g_projectionMode = 1;

        // The runner's 4:3 viewport is correct for menus/HUD but would keep
        // the 3D scene pillarboxed. Perspective rendering alone uses the
        // complete target backbuffer.
        D3DVIEWPORT8 full;
        ComputeFullViewport(&full);
        if (g_originalSetViewport) g_originalSetViewport(device, &full);
        if (!g_perspectiveLogged) {
            LogMatrixMode("[Projection] Perspective Hor+", fixed, full);
            g_perspectiveLogged = TRUE;
        }
        return hr;
    }

    if (g_cfg.correctHUD && IsOrthographic2D(*matrix)) {
        HRESULT hr = g_originalSetTransform(device, state, matrix);
        g_projectionMode = 2;

        // The trace proved that GameMaker renders menus in a logical 640x480
        // viewport and then asks Present to stretch that source to 1024x768.
        // Once the backbuffer is ultrawide, keeping a raw 640x480 viewport and
        // the old Present source rectangle exposes only a corner of the image.
        // Render the 4:3 layer into a centered, height-fitted viewport instead.
        D3DVIEWPORT8 fit;
        ComputeFitViewport(&fit);
        if (g_originalSetViewport) g_originalSetViewport(device, &fit);
        if (!g_orthoLogged) {
            LogMatrixMode("[Projection] Orthographic centered 4:3", *matrix, fit);
            g_orthoLogged = TRUE;
        }
        return hr;
    }

    return g_originalSetTransform(device, state, matrix);
}

static HRESULT WINAPI HookSetViewport(void* device, const D3DVIEWPORT8* viewport) {
    if (!g_originalSetViewport || !viewport) {
        return g_originalSetViewport ? g_originalSetViewport(device, viewport) : (HRESULT)0x80004005L;
    }

    // Preserve the raw value for diagnostics, but map the active layer to the
    // target backbuffer. The original runner alternates between a 640x480 menu
    // viewport and a 1024x768 3D viewport.
    g_lastRunnerViewport = *viewport;
    LogRawViewportOnce(*viewport);
    if (IsReferenceViewport(*viewport)) {
        g_lastFourThreeViewport = *viewport;
        g_haveFourThreeViewport = TRUE;
    }

    if (g_projectionMode == 1) {
        D3DVIEWPORT8 full;
        ComputeFullViewport(&full);
        return g_originalSetViewport(device, &full);
    }
    if (g_projectionMode == 2) {
        D3DVIEWPORT8 fit;
        ComputeFitViewport(&fit);
        return g_originalSetViewport(device, &fit);
    }

    // Before the first projection of a frame, pass the runner value through.
    // The following SetTransform call will immediately select full-screen 3D
    // or centered 4:3 rendering before any geometry is drawn.
    return g_originalSetViewport(device, viewport);
}

static HRESULT WINAPI HookBeginScene(void* device) {
    HRESULT hr = g_originalBeginScene ? g_originalBeginScene(device) : (HRESULT)0x80004005L;
    if (hr >= 0) {
        // Do not touch the viewport here. The GameMaker runner owns the 2D
        // aspect-fit viewport; we only replace it temporarily for perspective.
        g_projectionMode = 0;
        g_mapDrawSerial = 0;
        RefreshTransparencyRenderStates(device);
        if (g_activeMSAA && g_originalSetRenderState) g_originalSetRenderState(device, 161, 1);
        if (g_cfg.forceMipmaps || g_cfg.anisotropicFiltering || g_cfg.textureSmoothing) ApplyForcedFilteringAllStages(device);
    }
    return hr;
}

static HRESULT WINAPI HookReset(void* device, D3DPRESENT_PARAMETERS8* pp) {
    if (!g_originalReset) return (HRESULT)0x80004005L;
    UINT originalSwapEffect = pp ? pp->SwapEffect : 3;
    UINT originalBackBufferCount = pp ? pp->BackBufferCount : 1;
    ApplyConfiguredPresentParameters(pp);
    ConfigureDepthAndMSAA(g_d3dObject, g_deviceAdapter, g_deviceType, pp);
    HRESULT hr = g_originalReset(device, pp);
    if (hr < 0 && g_activeMSAA && pp) {
        LogRaw("[MSAA] Reset failed with multisampling; retrying without MSAA.\r\n");
        g_activeMSAA = 0;
        pp->MultiSampleType = 0;
        pp->SwapEffect = originalSwapEffect;
        pp->BackBufferCount = originalBackBufferCount;
        g_selectedDepthFormat = SelectDepthFormat(g_d3dObject, g_deviceAdapter, g_deviceType, pp, 0);
        if (pp->EnableAutoDepthStencil && g_selectedDepthFormat) pp->AutoDepthStencilFormat = g_selectedDepthFormat;
        hr = g_originalReset(device, pp);
    }
    if (hr >= 0) {
        g_windowApplied = FALSE;
        g_projectionMode = 0;
        g_haveFourThreeViewport = FALSE;
        g_filterStateDirty = TRUE;
        g_filterStateVerified = FALSE;
        g_depthSurfaceLogged = FALSE;
        g_depthPrecisionLogged = FALSE;
        for (int i = 0; i < 8; ++i) { g_boundTextures[i] = 0; g_requestedTextures[i] = 0; }
        g_alphaBlendEnabled = FALSE;
        g_alphaTestEnabled = FALSE;
        g_zWriteEnabled = TRUE;
        g_worldMaxElement = 1.0f;
        g_largeMapTransform = FALSE;
        g_mapDrawSerial = 0;
        ApplyWindowMode();
        ApplyRunnerFix();
    }
    return hr;
}

static HRESULT WINAPI HookPresent(void* device, const RECTI* src, const RECTI* dst, HWND overrideWindow, const void* dirty) {
    ApplyRunnerFix();
    ApplyWindowMode();

    // Critical fix from the trace: in menu mode the runner presents only the
    // original [0,0 -> 640,480] source rectangle. On a 3440x1440 backbuffer
    // that crops away the centered 4:3 viewport. Present the complete target
    // backbuffer; the 2D layer is already pillarboxed by ComputeFitViewport.
    return g_originalPresent ? g_originalPresent(device, 0, 0, overrideWindow, dirty) : (HRESULT)0x80004005L;
}

static void HookDevice(void* device) {
    g_device = device;
    void** table = device ? *(void***)device : 0;
    if (table && !g_originalGetViewport) g_originalGetViewport = (GetViewportFn)table[41];
    if (table && !g_originalGetTexture) g_originalGetTexture = (GetTextureFn)table[60];
    if (table && !g_originalGetTextureStageState) g_originalGetTextureStageState = (GetTextureStageStateFn)table[62];
    if (table && !g_originalGetRenderState) g_originalGetRenderState = (GetRenderStateFn)table[51];
    PatchVTable(device, 14, (void*)&HookReset, (void**)&g_originalReset);
    PatchVTable(device, 15, (void*)&HookPresent, (void**)&g_originalPresent);
    PatchVTable(device, 20, (void*)&HookCreateTexture, (void**)&g_originalCreateTexture);
    PatchVTable(device, 26, (void*)&HookCreateDepthStencilSurface, (void**)&g_originalCreateDepthStencilSurface);
    PatchVTable(device, 34, (void*)&HookBeginScene, (void**)&g_originalBeginScene);
    PatchVTable(device, 37, (void*)&HookSetTransform, (void**)&g_originalSetTransform);
    PatchVTable(device, 40, (void*)&HookSetViewport, (void**)&g_originalSetViewport);
    PatchVTable(device, 50, (void*)&HookSetRenderState, (void**)&g_originalSetRenderState);
    PatchVTable(device, 54, (void*)&HookApplyStateBlock, (void**)&g_originalApplyStateBlock);
    PatchVTable(device, 61, (void*)&HookSetTexture, (void**)&g_originalSetTexture);
    PatchVTable(device, 63, (void*)&HookSetTextureStageState, (void**)&g_originalSetTextureStageState);
    PatchVTable(device, 70, (void*)&HookDrawPrimitive, (void**)&g_originalDrawPrimitive);
    PatchVTable(device, 71, (void*)&HookDrawIndexedPrimitive, (void**)&g_originalDrawIndexedPrimitive);
    PatchVTable(device, 72, (void*)&HookDrawPrimitiveUP, (void**)&g_originalDrawPrimitiveUP);
    PatchVTable(device, 73, (void*)&HookDrawIndexedPrimitiveUP, (void**)&g_originalDrawIndexedPrimitiveUP);
    RefreshTransparencyRenderStates(device);
}

static HRESULT WINAPI HookCreateDevice(void* d3d, UINT adapter, UINT deviceType, HWND focusWindow, DWORD behaviorFlags, D3DPRESENT_PARAMETERS8* pp, void** returnedDevice) {
    if (!g_originalCreateDevice) return (HRESULT)0x80004005L;
    UINT originalSwapEffect = pp ? pp->SwapEffect : 3;
    UINT originalBackBufferCount = pp ? pp->BackBufferCount : 1;
    g_gameWindow = pp && pp->hDeviceWindow ? pp->hDeviceWindow : focusWindow;
    ApplyConfiguredPresentParameters(pp);
    g_deviceAdapter = adapter;
    g_deviceType = deviceType;
    g_deviceBackBufferFormat = pp && pp->BackBufferFormat ? pp->BackBufferFormat : 22;
    g_deviceWindowed = pp ? pp->Windowed : FALSE;
    ConfigureDepthAndMSAA(d3d, adapter, deviceType, pp);
    LogResolution("[Crimelife3.WidescreenFix] Original backbuffer: ", g_originalBackBufferWidth, g_originalBackBufferHeight);
    LogResolution("[Crimelife3.WidescreenFix] Requested backbuffer: ", g_backBufferWidth, g_backBufferHeight);

    HRESULT hr = g_originalCreateDevice(d3d, adapter, deviceType, focusWindow, behaviorFlags, pp, returnedDevice);
    if (hr < 0 && g_activeMSAA && pp) {
        LogRaw("[MSAA] CreateDevice failed with multisampling; retrying without MSAA.\r\n");
        g_activeMSAA = 0;
        pp->MultiSampleType = 0;
        pp->SwapEffect = originalSwapEffect;
        pp->BackBufferCount = originalBackBufferCount;
        g_selectedDepthFormat = SelectDepthFormat(d3d, adapter, deviceType, pp, 0);
        if (pp->EnableAutoDepthStencil && g_selectedDepthFormat) pp->AutoDepthStencilFormat = g_selectedDepthFormat;
        hr = g_originalCreateDevice(d3d, adapter, deviceType, focusWindow, behaviorFlags, pp, returnedDevice);
    }
    if (hr >= 0 && returnedDevice && *returnedDevice) {
        HookDevice(*returnedDevice);
        ApplyWindowMode();
        ApplyRunnerFix();
    }
    return hr;
}

static void* WINAPI HookDirect3DCreate8(UINT sdkVersion) {
    if (!g_originalDirect3DCreate8) return 0;
    void* d3d = g_originalDirect3DCreate8(sdkVersion);
    if (d3d) {
        g_d3dObject = d3d;
        void** table = *(void***)d3d;
        if (table) {
            g_checkDeviceFormat = (CheckDeviceFormatFn)table[10];
            g_checkDeviceMultiSampleType = (CheckDeviceMultiSampleTypeFn)table[11];
            g_checkDepthStencilMatch = (CheckDepthStencilMatchFn)table[12];
        }
        PatchVTable(d3d, 15, (void*)&HookCreateDevice, (void**)&g_originalCreateDevice);
    }
    return d3d;
}

static bool HookMainExecutableImport(const char* dllName, const char* functionName, void* replacement, void** original) {
    BYTE* base = (BYTE*)GetModuleHandleA(0);
    if (!base || base[0] != 'M' || base[1] != 'Z') return false;
    DWORD peOffset = *(DWORD*)(base + 0x3C);
    BYTE* nt = base + peOffset;
    if (nt[0] != 'P' || nt[1] != 'E' || nt[2] != 0 || nt[3] != 0) return false;
    BYTE* optional = nt + 24;
    WORD magic = *(WORD*)optional;
    if (magic != 0x10B) return false;
    DWORD importRva = *(DWORD*)(optional + 104);
    if (!importRva) return false;

    IMAGE_IMPORT_DESCRIPTOR_MIN* desc = (IMAGE_IMPORT_DESCRIPTOR_MIN*)(base + importRva);
    while (desc->Name) {
        const char* importedDll = (const char*)(base + desc->Name);
        if (StrEqualI(importedDll, dllName)) {
            DWORD lookupRva = desc->OriginalFirstThunk ? desc->OriginalFirstThunk : desc->FirstThunk;
            DWORD* lookup = (DWORD*)(base + lookupRva);
            void** iat = (void**)(base + desc->FirstThunk);
            for (UINT i = 0; lookup[i]; ++i) {
                if (lookup[i] & 0x80000000UL) continue;
                BYTE* byName = base + lookup[i];
                const char* name = (const char*)(byName + 2);
                if (StrEqualI(name, functionName)) return PatchPointer(&iat[i], replacement, original);
            }
        }
        ++desc;
    }
    return false;
}

extern "C" __declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_asiModule = module;
        DisableThreadLibraryCalls(module);
        LoadConfig();
        CreateInitialLog("Crimelife 3 Widescreen Fix v0.8.4 loaded.\r\n");
        if (!g_cfg.enabled) return TRUE;
        InitRunnerCompatibility();
        InstallOverlayHooks();
        InstallWorldFixHooks();
        InstallVehicleSpawnFixHooks();
        InstallExactProjectionHook();
        bool ok = HookMainExecutableImport("d3d8.dll", "Direct3DCreate8", (void*)&HookDirect3DCreate8, (void**)&g_originalDirect3DCreate8);
        if (ok) LogRaw("Direct3DCreate8 import hook installed.\r\n");
        else LogRaw("ERROR: Direct3DCreate8 import hook was not installed.\r\n");
    }
    return TRUE;
}
