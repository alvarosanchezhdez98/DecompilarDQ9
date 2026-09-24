// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file

#include "Scene/Overlay_20/StartupScene.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "Graphics/VRAMStaging.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include "System/VRAM.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>
#include <std_library_functions.h>

#define REG_MASTER_BRIGHT ((volatile unsigned short*)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((volatile unsigned short*)0x0400106c)
#define BLDCNT (*(volatile unsigned short*)0x04000050)
#define BLDCNTSUB (*(volatile unsigned short*)0x04001050)
#define VIEWPORT (*(volatile unsigned int*)0x04000580)

#define PAD_BUTTON_A 1
#define PAD_BUTTON_B 2
#define PAD_BUTTON_X 0x400
#define PAD_BUTTON_Y 0x800
#define PAD_BUTTONS 0xf0b
#define TOUCHING (data_02114e54[0x55])

struct Unknown_0203bd08;

extern "C"
{
    // The game's heap
    extern AllocatorUnion data_02114e20;
    // The pad
    extern char data_02114e30[];
    // The touch screen
    extern unsigned char data_02114e54[];
    // The sound player
    extern char data_02108760[];
    extern char data_02109bf4[];

    // Sets the next mode of main()
    void func_0200fb94(GameState* gameState, unsigned char mode);
    // The current mode of main(): 6 is the title
    int func_0200fb9c(GameState* gameState);
    void func_0200f3a4(GameState* gameState);
    void func_02012010(GameState* gameState, int);
    int func_0201201c(GameState* gameState);
    void func_02012028(GameState* gameState, int);
    // Returns whether the buttons were just pressed
    bool func_02012444(void* pad, int buttons);
    void* func_02012d88(AllocatorUnion* allocator, unsigned int size);
    void func_02012da4(AllocatorUnion* allocator, void* data);
    void func_02012efc();
    void func_0202ae18();
    Unknown_0203bd08* func_0203bd08();
    void func_0203bd24();
    void func_0203bd88(Unknown_0203bd08*);
    void func_0203bdb0(Unknown_0203bd08*);
    void func_02041a90(void* text, int x, int y);
    void func_02042058(void* text, const char* string);
    void func_02042084(void* text, const char* string, int, int);
    MessageSystem* func_020421a0();
    void func_02042c68();
    void func_02043000(MessageSystem* messages);
    void func_02043124(MessageSystem* messages);
    void func_020432c4(MessageSystem* messages);
    void func_02043368(MessageSystem* messages);
    void func_0204359c(MessageSystem* messages, int);
    void func_020439b0(MessageSystem* messages, int);
    void func_020440a4(MessageSystem* messages);
    void func_02045cac(MessageSystem* messages);
    // Returns a file of a .pac file
    void* func_020467f0(void* pac, int index, void** outName, unsigned int* outSize);
    // Returns the number of files in a .pac file
    int func_02046900(void* pac);
    void func_0204af38(BackgroundGraphics* graphics, int, SafeAllocator* allocator);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204afb4(BackgroundGraphics* graphics);
    void func_0204b0e8(BackgroundGraphics* graphics, int);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b12c(BackgroundGraphics* graphics, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* graphics, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b2e0(BackgroundGraphics* graphics, void* file);
    void func_0204b3a0(BackgroundGraphics* graphics, void* file);
    void func_0204b5b4(BackgroundGraphics* graphics, int);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204b8d0(BackgroundGraphics* graphics, int, int, int, int, int, int, int, int);
    void func_0204bc74(BackgroundGraphics* graphics, int, int, int, int, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* buffer, int);
    void func_0205a330(void*, int);
    void func_0205ba68(void*, int columns, int rows, int);
    void func_0205bacc(void*, int count);
    void func_0205bb04(void*, int);
    void func_0205bcdc(void*, int);
    void func_0205c77c(void*);
    void func_0205c790(TextMenu* menu);
    void func_0205c904(TextMenu* menu, int);
    void func_0205c96c(TextMenu* menu, int);
    // Returns the chosen item
    int func_0205cb64(TextMenu* menu);
    void func_0205cb74(TextMenu* menu, const char* item);
    void func_0205cc50(TextMenu* menu, int, int);
    void func_0205cd28(TextMenu* menu);
    bool func_0205cde8(TextMenu* menu);
    int func_0205cecc(TextMenu* menu);
    void func_0205cf78(TextWindow* window, Canvas* canvas);
    void func_0205cfd4(TextWindow* window);
    void func_0205d0e0(TextWindow* window, int);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d304(TextWindow* window, void* text, int, int, int, int, int, int);
    void func_0205e8ec(void*);
    void func_0207de48(void*, int, int);
    void func_0207df50(void*);
    void func_0207df90(void*);
    void func_0207dfac(void*);
    void func_0209c20c(void*);
    void func_0209c3b4(void*, int);
    void func_0209c678(void*, int);
    int func_020ab9c0(int);
    void func_020bb48c(int, int);
    void func_020bb780(int, int);
    void func_020bbcb4();
    // NNS_SndMain
    void func_020bbd9c();
    // GX_DispOn
    void func_020c38d4();
    // GX_SetGraphicsMode
    void func_020c391c(int mode, int bgMode, int bg0Is3D);
    // GXS_SetGraphicsMode
    void func_020c3984(int bgMode);
    // GXx_SetMasterBrightness_
    void func_020c39a0(volatile unsigned short* reg, int brightness);
    // GXx_GetMasterBrightness_
    int func_020c39c8(volatile unsigned short* reg);
    // G3X_Reset
    void func_020c52e8();
    // G3X_ResetMtxStack
    void func_020c5414();
    // G3X_SetClearColor
    void func_020c5588(int color, int alpha, int depth, int polygonID, int fog);
    void func_020c5770(int, int, int, int, int, int, int, int, int);
    // OS_WaitVBlankIntr
    void func_020c9820();
    void func_020d86d0(int, int);
}

// Level-5's version control keyword, and a pointer to the revision's number in it. Nothing reads it
static struct
{
    const char* number;
    const char* keyword;
} sRevision = {sRevision.keyword + 11, "$Revision: 17659 $"};

// The modes that the debug menu's items choose, with "On the way" when func_020ab9c0 returns 4
static const int sModes[] = {4, 0, 2, 100, 6, 1, 3};
static const int sModesWithOnTheWay[] = {4, 0, 5, 2, 100, 6, 1, 3};

// The strings of the functions, which the compiler pools in this order. Run() is in assembly for now (NONMATCHING),
// which can't reference the compiler's pool, so they're in an array for it
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] __attribute__((aligned(4))) =
    "data/ani/bg_tm.pac\0%s %s\0ver035\0Apr 14 2010\0NITRO SDK %d.%d.%d\0NITRO SYSTEM %d\0NITRO WiFi %d.%d.%d\0"
    "NITRO CRYPTO %d.%d.%d\0DWC-DL %d.%d.%d\0SWC %d.%d.%d\0DRAGON QUEST IX\0XENLON project\0LEVEL5 INC.\0"
    "data/ani/bg_title.pac\0data/menu/nintendo.pac\0data/menu/bg_mobi_2.pac\0data/menu/bg_sqen.pac\0"
    "data/menu/bg_lv5.pac";
#define STRING(offset, text) (sStrings + (offset))
#endif

// The debug menu's items, which are defined after the strings to get the original's layout (see
// tools/data_order.py)
static const char sItems[][0x20] = {"Debug", "Start", "Create", "Delete", "Title", "Chara Viewer", "Movie"};
static const char sItemsWithOnTheWay[][0x20] = {"Debug", "Start", "On the way", "Create", "Delete", "Title",
                                                "Chara Viewer", "Movie"};

// The NitroSDK's G2_SetBG1Control and G2S_SetBG0Control, which the compiler didn't inline
static inline void G2_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    BG1CNT = (BG1CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (screenSize << 14) | (colorMode << 7) |
             (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13);
}

static inline void G2S_SetBG0Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    BG0CNTSUB = (BG0CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (screenSize << 14) | (colorMode << 7) |
                (screenBase << 8) | (charBase << 2) | (bgExtPltt << 13);
}

void StartupScene::Initialize()
{
    GameState* gameState = GameState::GetInstance();
    func_0202ae18();
    func_0200f3a4(gameState);
    MapVRAMBanksToMainBG(4);
    DISPCNT &= ~DISPCNT_MASK_CHARACTER_BASE_64K;
    DISPCNT &= ~DISPCNT_MASK_SCREEN_BASE_64K;
    func_020c391c(1, 0, 1);
    func_020c3984(0);
    BG0CNT = BG0CNT & ~BGCNT_MASK_PRIORITY;
    BG1CNT = (BG1CNT & ~BGCNT_MASK_PRIORITY) | 1;
    func_020c5588(0, 0, 0x7fff, 0x3f, 0);
    if (func_0200fb9c(gameState) == 6)
        func_020c5588(0, 0x1f, 0x7fff, 0, 0);
    func_020c5770(0, 0xc0000, 0, 0x100000, -0x400000, 0x400000, 0x400000, 1, 0);
    GXFIFO_MATRIX_STORE = 0;
    POWCNT &= ~0x8000;
    VIEWPORT = 0xbfff0000;
    allocator_.ResetAllocatorPointer();
    unk_484.ResetAllocatorPointer();
    unk_8 = 0;
    unk_500 = 0;
    mainBrightnessTimeRemaining_ = 0;
    mainBrightnessTarget_ = 0;
    subBrightnessTimeRemaining_ = 0;
    subBrightness_ = 0;
}

void StartupScene::Finish()
{
    func_02043000(func_020421a0());
}

// NONMATCHING: the C matches 92.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler keeps 30003 in a register for the arguments of the versions' sprintf() (and computes 30006 and 30001
// from it), where the original loads each one from the literal pool, and it gives another register to the 1 stored
// before func_0205cf78(). Without bg_tm.pac's loading loop, or with other forms of it, it doesn't keep the constant
// either, but the loop's code doesn't match then.
#ifdef NONMATCHING
void StartupScene::Run()
{
    GameState* gameState = GameState::GetInstance();
    func_020c9820();
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    if (func_0201201c(gameState) == 1)
    {
        func_020c39a0(REG_MASTER_BRIGHT, 16);
        func_020c39a0(REG_MASTER_BRIGHT_SUB, 16);
    }
    func_020c38d4();
    DISPCNTSUB |= 0x10000;
    if (func_0201201c(gameState) == 1)
    {
        SetMainBrightness(-16, 2000);
        SetSubBrightness(-16, 2000);
        // The original checks the conditions of its waiting loops before their bodies, which the compiler does with a
        // `break` (it checks a `while` loop's condition after the body)
        while (true)
        {
            if (!IsBrightnessTransitionActive())
                break;
            UpdateBrightness();
            func_020c9820();
            func_020d86d0(0, 1);
        }
    }
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    BG0CNT = BG0CNT & ~BGCNT_MASK_PRIORITY;
    BG1CNT = (BG1CNT & ~BGCNT_MASK_PRIORITY) | 1;
    func_020c9820();
    func_020c38d4();
    DISPCNTSUB |= 0x10000;
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);

    if (func_0200fb9c(gameState) != 6)
    {
        // The versions of the game and its libraries
        allocator_.CreateTypeA(func_02012d88(&data_02114e20, 0x10000), 0x10000);
        allocator_.Reset();
        func_0205cfd4(&window_);
        func_0204af64(&windowBackground_);
        func_0204c684(&canvas_);
        MapVRAMBanksToMainBG(4);
        G2_SetBG1Control(0, 0, 1, 1, 0);
        func_0204b11c(&windowBackground_, 0);
        windowBackground_.unk_1c_0_ = 0;
        windowBackground_.unk_1c_4_ = 1;
        func_0204b5b4(&windowBackground_, 0);
        func_0204b12c(&windowBackground_, &allocator_);
        func_0204b5e8(&windowBackground_, 0, 0);
        int taskID;
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->MaybeReset();
        taskID = loader->QueueLoadFile(STRING(0x0, "data/ani/bg_tm.pac"), NULL);
        while (true)
        {
            if (loader->GetTaskStatus(taskID))
            {
                void* name;
                void* file;
                unsigned int size;
                unsigned int dataSize;
                loader->GetLoadedFileByID(taskID, &file, &size);
                int numFiles = func_02046900(file);
                for (int i = 0; i < numFiles; i++)
                {
                    void* data = func_020467f0(file, i, &name, &dataSize);
                    if (data != NULL)
                        func_0204b174(&windowBackground_, data, &allocator_, dataSize);
                }
                loader->RemoveTask(taskID);
                func_0204bc74(&windowBackground_, 0, 0, 0, 0x20, 0x19, 0);
                func_0204b0e8(&windowBackground_, 0);
                canvasBuffer_ = allocator_.Allocate(0x8000);
                func_0204c7a8(&canvas_, &allocator_, canvasBuffer_, 0x800);
                canvas_.background_ = &windowBackground_;
                window_.background_ = &windowBackground_;
                window_.unk_b2 = 1;
                func_0205cf78(&window_, &canvas_);
                break;
            }
            loader->RemoveAllLocks();
        }
        window_.unk_b1 = 1;
        window_.unk_a4 = 0;
        window_.unk_a6 = 0;
        window_.unk_a8 = 0;
        window_.unk_aa = 0;
        window_.width_ = 0x20;
        window_.height_ = 0x18;
        window_.unk_ac = 10;
        window_.unk_ae = 13;
        window_.unk_b5 = 0;
        window_.unk_b6 = 1;

        void* text = func_020421a0()->unk_5c;
        memset(text, 0, 0x960);
        char buffer[0x80] = {0};
        func_02041a90(text, 4, 0x68);
        sprintf(buffer, STRING(0x13, "%s %s"), STRING(0x19, "ver035"), STRING(0x20, "Apr 14 2010"));
        func_02042058(text, buffer);
        func_02041a90(text, 4, 0x74);
        sprintf(buffer, STRING(0x2c, "NITRO SDK %d.%d.%d"), 4, 2, 30009);
        func_02042058(text, buffer);
        func_02041a90(text, 4, 0x80);
        sprintf(buffer, STRING(0x3f, "NITRO SYSTEM %d"), 20071126);
        func_02042058(text, buffer);
        func_02041a90(text, 4, 0x8c);
        sprintf(buffer, STRING(0x4f, "NITRO WiFi %d.%d.%d"), 2, 1, 30003);
        func_02042058(text, buffer);
        func_02041a90(text, 4, 0x98);
        sprintf(buffer, STRING(0x63, "NITRO CRYPTO %d.%d.%d"), 2, 1, 30003);
        func_02042058(text, buffer);
        func_02041a90(text, 4, 0xa4);
        sprintf(buffer, STRING(0x79, "DWC-DL %d.%d.%d"), 3, 1, 30006);
        func_02042058(text, buffer);
        func_02041a90(text, 4, 0xb0);
        sprintf(buffer, STRING(0x89, "SWC %d.%d.%d"), 3, 0, 30001);
        func_02042058(text, buffer);
        func_02041a90(text, 0, 0x28);
        func_02042084(text, STRING(0x96, "DRAGON QUEST IX"), 0x100, 0);
        func_02041a90(text, 0, 0x36);
        func_02042084(text, STRING(0xa6, "XENLON project"), 0x100, 0);
        func_02041a90(text, 0, 0x50);
        func_02042084(text, STRING(0xb5, "LEVEL5 INC."), 0x100, 0);
        func_0205d304(&window_, text, 0, 0, 0, 1, 0, 0);
        func_0205d0e0(&window_, 1);
        func_0205d0e0(&window_, 1);
        func_0205d228(&window_);
        func_0205d274(&window_);
        func_0205d2bc(&window_);
        func_020d86d0(0, 1);
        func_020c9820();
        func_020c38d4();
        DISPCNT = (DISPCNT & ~0x1f00) | 0x200;
        func_020bbcb4();
        func_020d86d0(0, 1);
        while (state_ != State_End)
        {
            func_02012efc();
            if (func_02012444(data_02114e30, PAD_BUTTON_A) || func_02012444(data_02114e30, PAD_BUTTON_B) ||
                func_02012444(data_02114e30, PAD_BUTTON_X) || func_02012444(data_02114e30, PAD_BUTTON_Y) || TOUCHING)
                break;
            func_020c9820();
            func_020c39a0(REG_MASTER_BRIGHT, 0);
            func_020d86d0(0, 1);
        }
        SignedAllocatorHeader* buffer2 = allocator_.GetSignedAllocator();
        allocator_.Destroy();
        func_02012da4(&data_02114e20, buffer2);
    }

    func_020c9820();
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    BG0CNT = (BG0CNT & ~BGCNT_MASK_PRIORITY) | 1;
    BG1CNT = BG1CNT & ~BGCNT_MASK_PRIORITY;
    BG2CNT = (BG2CNT & ~BGCNT_MASK_PRIORITY) | 2;
    BG3CNT = (BG3CNT & ~BGCNT_MASK_PRIORITY) | 3;
    BG0CNTSUB = BG0CNTSUB & ~BGCNT_MASK_PRIORITY;
    BG1CNTSUB = (BG1CNTSUB & ~BGCNT_MASK_PRIORITY) | 1;
    BG2CNTSUB = (BG2CNTSUB & ~BGCNT_MASK_PRIORITY) | 2;
    BG3CNTSUB = (BG3CNTSUB & ~BGCNT_MASK_PRIORITY) | 3;
    LockStagedTextureVRAMCopying();
    MapVRAMBanksToTextureImage(1);
    func_020bb48c(1, 1);
    MapVRAMBanksToTexturePalette(0x60);
    func_020bb780(0x8000, 1);
    UpdateVRAMStagingVRAMBanks();
    UnlockStagedTextureVRAMCopying();
    allocator_.CreateTypeA(func_02012d88(&data_02114e20, 0x10000), 0x10000);
    func_0207de48(unk_244, 0x4000, 0x400);
    MessageSystem* messages = func_020421a0();
    func_02042c68();
    func_02043124(messages);
    func_020440a4(messages);
    messages->unk_1e28 = unk_244;
    func_0207df50(unk_244);
    func_0207df90(unk_244);
    func_020432c4(messages);
    func_0207dfac(unk_244);
    state_ = State_Menu;
    frame_ = -1;

    if (func_0200fb9c(gameState) == 6)
    {
        // The logos
        if (func_0201201c(gameState) == 0)
        {
            func_020c5588(0x7fff, 0x1f, 0x7fff, 0, 0);
            LoadNintendoLogo();
            func_020c38d4();
            DISPCNTSUB |= 0x10000;
            timer_ = 2000;
            while (true)
            {
                if (!IsTimerActive())
                    break;
                UpdateTimer();
                func_020c9820();
                func_02012efc();
                func_020d86d0(0, 1);
            }
            SetMainBrightness(0, 500);
            SetSubBrightness(0, 500);
            timer_ = 3000;
            while (true)
            {
                if (IsSubBrightnessTransitionActive())
                {
                }
                else if (IsTimerActive())
                {
                    UpdateTimer();
                    func_02012efc();
                }
                else
                    break;
                UpdateBrightness();
                func_020c9820();
                func_020d86d0(0, 1);
            }
            SetMainBrightness(-16, 500);
            SetSubBrightness(-16, 500);
            while (true)
            {
                if (!IsSubBrightnessTransitionActive())
                    break;
                UpdateBrightness();
                func_020c9820();
                func_02012efc();
                func_020d86d0(0, 1);
            }
            timer_ = 1000;
            while (true)
            {
                if (!IsTimerActive())
                    break;
                UpdateTimer();
                func_020c9820();
                func_02012efc();
                func_020d86d0(0, 1);
            }

            LoadMobiLogo();
            func_020c38d4();
            DISPCNTSUB |= 0x10000;
            SetMainBrightness(0, 1500);
            SetSubBrightness(0, 1500);
            timer_ = 7000;
            while (true)
            {
                if (IsBrightnessTransitionActive())
                {
                }
                else if (IsTimerActive())
                {
                    UpdateTimer();
                    func_02012efc();
                    if (timer_ <= 2500 && (func_02012444(data_02114e30, PAD_BUTTONS) || TOUCHING))
                        break;
                }
                else
                    break;
                UpdateBrightness();
                func_020c9820();
                func_020d86d0(0, 1);
            }
            SetMainBrightness(-16, 1000);
            SetSubBrightness(-16, 1000);
            while (true)
            {
                if (!IsSubBrightnessTransitionActive())
                    break;
                UpdateBrightness();
                func_020c9820();
                func_02012efc();
                func_020d86d0(0, 1);
            }
            timer_ = 1000;
            while (true)
            {
                if (!IsTimerActive())
                    break;
                UpdateTimer();
                func_020c9820();
                func_02012efc();
                func_020d86d0(0, 1);
            }

            LoadCompanyLogo(0);
            func_020c38d4();
            DISPCNTSUB |= 0x10000;
            SetMainBrightness(0, 1500);
            SetSubBrightness(0, 1500);
            timer_ = 6000;
            while (true)
            {
                if (IsSubBrightnessTransitionActive())
                {
                }
                else if (IsTimerActive())
                {
                    UpdateTimer();
                    func_02012efc();
                    if (func_02012444(data_02114e30, PAD_BUTTONS) || TOUCHING)
                        break;
                }
                else
                    break;
                UpdateBrightness();
                func_020c9820();
                func_020d86d0(0, 1);
            }
            SetMainBrightness(-16, 1000);
            SetSubBrightness(-16, 1000);
            while (true)
            {
                if (!IsSubBrightnessTransitionActive())
                    break;
                UpdateBrightness();
                func_020c9820();
                func_02012efc();
                func_020d86d0(0, 1);
            }
            timer_ = 1000;
            while (true)
            {
                if (!IsTimerActive())
                    break;
                UpdateTimer();
                func_020c9820();
                func_02012efc();
                func_020d86d0(0, 1);
            }
            func_020c5588(0, 0x1f, 0x7fff, 0, 0);
        }
        func_02012010(gameState, 5);
        func_0200fb94(gameState, 0);
        func_02012028(gameState, 1);
    }
    else
    {
        // The debug menu
        func_02012010(gameState, 0);
        LoadMenuBackgrounds();
        func_020c38d4();
        DISPCNTSUB |= 0x10000;
        func_02045cac(messages);
        func_0205c790(&menu_);
        menu_.unk_b1 = 1;
        menu_.unk_b0 = 1;
        if (func_020ab9c0(1) == 4)
        {
            for (int i = 0; i < 8; i++)
            {
                func_0205cb74(&menu_, sItemsWithOnTheWay[i]);
                func_0204359c(messages, 0x10);
                func_020439b0(messages, 0);
            }
            menu_.SetGrid(1, 8);
        }
        else
        {
            for (int i = 0; i < 7; i++)
            {
                func_0205cb74(&menu_, sItems[i]);
                func_0204359c(messages, 0x10);
                func_020439b0(messages, 0);
            }
            menu_.SetGrid(1, 7);
        }
        func_0205cc50(&menu_, 0, -4);
        menu_.SetPosition((0x100 - menu_.width_) >> 1, (0xc0 - menu_.height_) >> 2);
        func_0205cc50(&menu_, 0, -4);
        func_0205bcdc(menu_.unk_20, 0);
        func_0205bb04(menu_.unk_70, 0);
        MapVRAMBanksToMainObj(2);
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        MessageSystem* messages2 = func_020421a0();
        while (true)
        {
            func_02043368(messages2);
            if (messages2->unk_2e7 == 2)
                break;
            loader->RemoveAllLocks();
        }
        Unknown_0203bd08* unknown = func_0203bd08();
        func_0203bd24();
        func_0205e8ec(data_02108760);
        func_0209c3b4(data_02109bf4, 2);
        while (state_ != State_End)
        {
            func_02012efc();
            if (++frame_ >= 0xffffff)
                frame_ = 1;
            func_020c52e8();
            func_020c5414();
            DISP3DCNT &= 0xcfdf;
            switch (state_)
            {
            case State_Menu:
                UpdateMenu();
                break;
            default:
                state_ = State_End;
                break;
            }
            func_020d86d0(0, 1);
            func_0203bd88(unknown);
            func_020c9820();
            func_0203bdb0(unknown);
            func_020bbcb4();
            func_020bbd9c();
            func_020c39a0(REG_MASTER_BRIGHT, 0);
            func_020c39a0(REG_MASTER_BRIGHT_SUB, 0);
        }
        if (func_0200fb9c(gameState) == 0)
            func_02012010(gameState, 6);
        else if (func_0200fb9c(gameState) == 5)
            func_02012010(gameState, 6);
    }
    Cleanup();
    func_0207df50(unk_244);
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12StartupScene10UpdateMenuEv(); // StartupScene::UpdateMenu
    void _ZN12StartupScene11UpdateTimerEv(); // StartupScene::UpdateTimer
    void _ZN12StartupScene12LoadMobiLogoEv(); // StartupScene::LoadMobiLogo
    void _ZN12StartupScene15LoadCompanyLogoEi(); // StartupScene::LoadCompanyLogo
    void _ZN12StartupScene16LoadNintendoLogoEv(); // StartupScene::LoadNintendoLogo
    void _ZN12StartupScene16SetSubBrightnessEii(); // StartupScene::SetSubBrightness
    void _ZN12StartupScene16UpdateBrightnessEv(); // StartupScene::UpdateBrightness
    void _ZN12StartupScene17SetMainBrightnessEii(); // StartupScene::SetMainBrightness
    void _ZN12StartupScene19LoadMenuBackgroundsEv(); // StartupScene::LoadMenuBackgrounds
    void _ZN12StartupScene28IsBrightnessTransitionActiveEv(); // StartupScene::IsBrightnessTransitionActive
    void _ZN12StartupScene7CleanupEv(); // StartupScene::Cleanup
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator7DestroyEv(); // SafeAllocator::Destroy
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader10MaybeResetEv(); // BackgroundLoader::MaybeReset
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader14RemoveAllLocksEv(); // BackgroundLoader::RemoveAllLocks
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN8TextMenu7SetGridEii(); // TextMenu::SetGrid
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK13SafeAllocator18GetSignedAllocatorEv(); // SafeAllocator::GetSignedAllocator
    void __clear(); // Zeroes the buffer of Run()
}

asm void StartupScene::Run()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xa0
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    mov r8, r0
    bl func_020c9820
    ldr r0, =0x400006c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    mov r0, r8
    bl func_0201201c
    cmp r0, #0x1
    bne @L0218b768
    ldr r0, =0x400006c
    mov r1, #0x10
    bl func_020c39a0
    ldr r0, =0x400106c
    mov r1, #0x10
    bl func_020c39a0
@L0218b768:
    bl func_020c38d4
    ldr r2, =0x4001000
    mov r0, r8
    ldr r1, [r2, #0x0]
    orr r1, r1, #0x10000
    str r1, [r2, #0x0]
    bl func_0201201c
    cmp r0, #0x1
    bne @L0218b7e0
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x7d0
    bl _ZN12StartupScene17SetMainBrightnessEii
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x7d0
    bl _ZN12StartupScene16SetSubBrightnessEii
    mov r5, #0x0
    mov r4, #0x1
@L0218b7b4:
    mov r0, r10
    bl _ZN12StartupScene28IsBrightnessTransitionActiveEv
    cmp r0, #0x0
    beq @L0218b7e0
    mov r0, r10
    bl _ZN12StartupScene16UpdateBrightnessEv
    bl func_020c9820
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218b7b4
@L0218b7e0:
    ldr r0, =0x400006c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r1, =0x4000008
    ldrh r0, [r1, #0x0]
    bic r0, r0, #0x3
    strh r0, [r1, #0x0]
    ldrh r0, [r1, #0x2]
    bic r0, r0, #0x3
    orr r0, r0, #0x1
    strh r0, [r1, #0x2]
    bl func_020c9820
    bl func_020c38d4
    ldr r3, =0x4001000
    ldr r0, =0x400006c
    ldr r2, [r3, #0x0]
    mvn r1, #0xf
    orr r2, r2, #0x10000
    str r2, [r3, #0x0]
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    mov r0, r8
    bl func_0200fb9c
    cmp r0, #0x6
    beq @L0218bdcc
    ldr r0, =data_02114e20
    mov r1, #0x10000
    bl func_02012d88
    mov r1, r0
    add r0, r10, #0x470
    mov r2, #0x10000
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, r10, #0x470
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x2b4
    bl func_0205cfd4
    add r0, r10, #0x370
    bl func_0204af64
    add r0, r10, #0x390
    bl func_0204c684
    mov r0, #0x4
    bl MapVRAMBanksToMainBG
    mov r0, #0x0
    mov r2, #0x1
    mov r1, r0
    mov r3, r2
    str r0, [sp, #0x0]
    bl G2_SetBG1Control
    add r0, r10, #0x370
    mov r1, #0x0
    bl func_0204b11c
    ldrb r2, [r10, #0x38c]
    add r0, r10, #0x370
    mov r1, #0x0
    bic r2, r2, #0xf
    strb r2, [r10, #0x38c]
    and r2, r2, #0xff
    bic r2, r2, #0xf0
    orr r2, r2, #0x10
    strb r2, [r10, #0x38c]
    bl func_0204b5b4
    add r0, r10, #0x370
    add r1, r10, #0x470
    bl func_0204b12c
    mov r1, #0x0
    add r0, r10, #0x370
    mov r2, r1
    bl func_0204b5e8
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r6, r0
    bl _ZN16BackgroundLoader10MaybeResetEv
    ldr r1, =sStrings
    mov r0, r6
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    mov r5, r0
@L0218b924:
    mov r0, r6
    mov r1, r5
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0218ba28
    add r2, sp, #0x18
    add r3, sp, #0x14
    mov r0, r6
    mov r1, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x18]
    bl func_02046900
    mov r7, r0
    mov r9, #0x0
    add r4, sp, #0x1c
    add r11, sp, #0x10
    b @L0218b998
@L0218b968:
    ldr r0, [sp, #0x18]
    mov r1, r9
    mov r2, r4
    mov r3, r11
    bl func_020467f0
    movs r1, r0
    beq @L0218b994
    ldr r3, [sp, #0x10]
    add r0, r10, #0x370
    add r2, r10, #0x470
    bl func_0204b174
@L0218b994:
    add r9, r9, #0x1
@L0218b998:
    cmp r9, r7
    blt @L0218b968
    mov r0, r6
    mov r1, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    mov r2, r1
    mov r3, r1
    add r0, r10, #0x370
    str r1, [sp, #0x8]
    bl func_0204bc74
    add r0, r10, #0x370
    mov r1, #0x0
    bl func_0204b0e8
    add r0, r10, #0x470
    mov r1, #0x8000
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x498]
    add r0, r10, #0x390
    add r1, r10, #0x470
    ldr r2, [r10, #0x498]
    mov r3, #0x800
    bl func_0204c7a8
    add r0, r10, #0x370
    str r0, [r10, #0x394]
    str r0, [r10, #0x34c]
    mov r2, #0x1
    strb r2, [r10, #0x366]
    add r0, r10, #0x2b4
    add r1, r10, #0x390
    bl func_0205cf78
    b @L0218ba34
@L0218ba28:
    mov r0, r6
    bl _ZN16BackgroundLoader14RemoveAllLocksEv
    b @L0218b924
@L0218ba34:
    mov r3, #0x1
    strb r3, [r10, #0x365]
    add r0, r10, #0x300
    mov r2, #0x0
    strh r2, [r0, #0x58]
    strh r2, [r0, #0x5a]
    strh r2, [r0, #0x5c]
    strh r2, [r0, #0x5e]
    mov r1, #0x20
    strh r1, [r0, #0x54]
    mov r1, #0x18
    strh r1, [r0, #0x56]
    mov r1, #0xa
    strh r1, [r0, #0x60]
    mov r1, #0xd
    strh r1, [r0, #0x62]
    strb r2, [r10, #0x369]
    strb r3, [r10, #0x36a]
    bl func_020421a0
    ldr r4, [r0, #0x5c]
    mov r1, #0x0
    mov r0, r4
    mov r2, #0x960
    bl memset
    add r0, sp, #0x20
    mov r1, #0x80
    bl __clear
    mov r0, r4
    mov r1, #0x4
    mov r2, #0x68
    bl func_02041a90
    ldr r1, =sStrings+0x13
    ldr r2, =sStrings+0x19
    ldr r3, =sStrings+0x20
    add r0, sp, #0x20
    bl sprintf
    mov r0, r4
    add r1, sp, #0x20
    bl func_02042058
    mov r0, r4
    mov r1, #0x4
    mov r2, #0x74
    bl func_02041a90
    ldr r1, =0x7539
    add r0, sp, #0x20
    str r1, [sp, #0x0]
    ldr r1, =sStrings+0x2c
    mov r2, #0x4
    mov r3, #0x2
    bl sprintf
    mov r0, r4
    add r1, sp, #0x20
    bl func_02042058
    mov r0, r4
    mov r1, #0x4
    mov r2, #0x80
    bl func_02041a90
    ldr r1, =sStrings+0x3f
    ldr r2, =0x13242d6
    add r0, sp, #0x20
    bl sprintf
    add r1, sp, #0x20
    mov r0, r4
    bl func_02042058
    mov r0, r4
    mov r1, #0x4
    mov r2, #0x8c
    bl func_02041a90
    ldr r2, =0x7533
    ldr r1, =sStrings+0x4f
    str r2, [sp, #0x0]
    add r0, sp, #0x20
    mov r2, #0x2
    mov r3, #0x1
    bl sprintf
    mov r0, r4
    add r1, sp, #0x20
    bl func_02042058
    mov r0, r4
    mov r1, #0x4
    mov r2, #0x98
    bl func_02041a90
    ldr r1, =0x7533
    add r0, sp, #0x20
    str r1, [sp, #0x0]
    ldr r1, =sStrings+0x63
    mov r2, #0x2
    mov r3, #0x1
    bl sprintf
    mov r0, r4
    add r1, sp, #0x20
    bl func_02042058
    mov r0, r4
    mov r1, #0x4
    mov r2, #0xa4
    bl func_02041a90
    ldr r1, =0x7536
    add r0, sp, #0x20
    str r1, [sp, #0x0]
    ldr r1, =sStrings+0x79
    mov r2, #0x3
    mov r3, #0x1
    bl sprintf
    mov r0, r4
    add r1, sp, #0x20
    bl func_02042058
    mov r0, r4
    mov r1, #0x4
    mov r2, #0xb0
    bl func_02041a90
    ldr r1, =0x7531
    add r0, sp, #0x20
    str r1, [sp, #0x0]
    ldr r1, =sStrings+0x89
    mov r2, #0x3
    mov r3, #0x0
    bl sprintf
    mov r0, r4
    add r1, sp, #0x20
    bl func_02042058
    mov r0, r4
    mov r1, #0x0
    mov r2, #0x28
    bl func_02041a90
    ldr r1, =sStrings+0x96
    mov r0, r4
    mov r2, #0x100
    mov r3, #0x0
    bl func_02042084
    mov r0, r4
    mov r1, #0x0
    mov r2, #0x36
    bl func_02041a90
    ldr r1, =sStrings+0xa6
    mov r0, r4
    mov r2, #0x100
    mov r3, #0x0
    bl func_02042084
    mov r0, r4
    mov r1, #0x0
    mov r2, #0x50
    bl func_02041a90
    ldr r1, =sStrings+0xb5
    mov r0, r4
    mov r2, #0x100
    mov r3, #0x0
    bl func_02042084
    mov r2, #0x0
    str r2, [sp, #0x0]
    mov r0, #0x1
    stmib sp, {r0, r2}
    mov r1, r4
    add r0, r10, #0x2b4
    mov r3, r2
    str r2, [sp, #0xc]
    bl func_0205d304
    add r0, r10, #0x2b4
    mov r1, #0x1
    bl func_0205d0e0
    add r0, r10, #0x2b4
    mov r1, #0x1
    bl func_0205d0e0
    add r0, r10, #0x2b4
    bl func_0205d228
    add r0, r10, #0x2b4
    bl func_0205d274
    add r0, r10, #0x2b4
    bl func_0205d2bc
    mov r0, #0x0
    mov r1, #0x1
    bl func_020d86d0
    bl func_020c9820
    bl func_020c38d4
    mov r1, #0x4000000
    ldr r0, [r1, #0x0]
    bic r0, r0, #0x1f00
    orr r0, r0, #0x200
    str r0, [r1, #0x0]
    bl func_020bbcb4
    mov r0, #0x0
    mov r1, #0x1
    bl func_020d86d0
    ldr r9, =data_02114e30
    mov r7, #0x1
    mov r6, #0x2
    mov r11, #0x400
    ldr r5, =data_02114e54
    mvn r4, #0x0
    b @L0218bda0
@L0218bd28:
    bl func_02012efc
    mov r0, r9
    mov r1, r7
    bl func_02012444
    cmp r0, #0x0
    bne @L0218bdac
    mov r0, r9
    mov r1, r6
    bl func_02012444
    cmp r0, #0x0
    bne @L0218bdac
    mov r0, r9
    mov r1, r11
    bl func_02012444
    cmp r0, #0x0
    bne @L0218bdac
    mov r0, r9
    mov r1, #0x800
    bl func_02012444
    cmp r0, #0x0
    ldreqb r0, [r5, #0x55]
    cmpeq r0, #0x0
    bne @L0218bdac
    bl func_020c9820
    ldr r0, =0x400006c
    mov r1, #0x0
    bl func_020c39a0
    mov r0, #0x0
    mov r1, #0x1
    bl func_020d86d0
@L0218bda0:
    ldr r0, [r10, #0x0]
    cmp r0, r4
    bne @L0218bd28
@L0218bdac:
    add r0, r10, #0x470
    bl _ZNK13SafeAllocator18GetSignedAllocatorEv
    mov r4, r0
    add r0, r10, #0x470
    bl _ZN13SafeAllocator7DestroyEv
    ldr r0, =data_02114e20
    mov r1, r4
    bl func_02012da4
@L0218bdcc:
    bl func_020c9820
    ldr r0, =0x400006c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x4000008
    ldr r1, =0x400100a
    ldrh r3, [r0, #0x0]
    add r2, r0, #0x1000
    bic r3, r3, #0x3
    orr r3, r3, #0x1
    strh r3, [r0, #0x0]
    ldrh r3, [r0, #0x2]
    bic r3, r3, #0x3
    strh r3, [r0, #0x2]
    ldrh r3, [r0, #0x4]
    bic r3, r3, #0x3
    orr r3, r3, #0x2
    strh r3, [r0, #0x4]
    ldrh r3, [r0, #0x6]
    bic r3, r3, #0x3
    orr r3, r3, #0x3
    strh r3, [r0, #0x6]
    ldrh r0, [r2, #0x0]
    bic r0, r0, #0x3
    strh r0, [r2, #0x0]
    ldrh r0, [r1, #0x0]
    bic r0, r0, #0x3
    orr r0, r0, #0x1
    strh r0, [r1, #0x0]
    ldrh r0, [r1, #0x2]
    bic r0, r0, #0x3
    orr r0, r0, #0x2
    strh r0, [r1, #0x2]
    ldrh r0, [r1, #0x4]
    bic r0, r0, #0x3
    orr r0, r0, #0x3
    strh r0, [r1, #0x4]
    bl LockStagedTextureVRAMCopying
    mov r0, #0x1
    bl MapVRAMBanksToTextureImage
    mov r0, #0x1
    mov r1, r0
    bl func_020bb48c
    mov r0, #0x60
    bl MapVRAMBanksToTexturePalette
    mov r0, #0x8000
    mov r1, #0x1
    bl func_020bb780
    bl UpdateVRAMStagingVRAMBanks
    bl UnlockStagedTextureVRAMCopying
    ldr r0, =data_02114e20
    mov r1, #0x10000
    bl func_02012d88
    mov r1, r0
    add r0, r10, #0x470
    mov r2, #0x10000
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, r10, #0x244
    mov r1, #0x4000
    mov r2, #0x400
    bl func_0207de48
    bl func_020421a0
    mov r4, r0
    bl func_02042c68
    mov r0, r4
    bl func_02043124
    mov r0, r4
    bl func_020440a4
    add r0, r10, #0x244
    add r1, r4, #0x1000
    str r0, [r1, #0xe28]
    bl func_0207df50
    add r0, r10, #0x244
    bl func_0207df90
    mov r0, r4
    bl func_020432c4
    add r0, r10, #0x244
    bl func_0207dfac
    mov r1, #0x64
    str r1, [r10, #0x0]
    sub r1, r1, #0x65
    mov r0, r8
    str r1, [r10, #0x4]
    bl func_0200fb9c
    cmp r0, #0x6
    mov r0, r8
    bne @L0218c46c
    bl func_0201201c
    cmp r0, #0x0
    bne @L0218c444
    ldr r0, =0x7fff
    mov r3, #0x0
    mov r2, r0
    mov r1, #0x1f
    str r3, [sp, #0x0]
    bl func_020c5588
    mov r0, r10
    bl _ZN12StartupScene16LoadNintendoLogoEv
    bl func_020c38d4
    ldr r2, =0x4001000
    mov r6, #0x0
    ldr r1, [r2, #0x0]
    mov r7, #0x1
    orr r1, r1, #0x10000
    mov r0, #0x7d0
    str r1, [r2, #0x0]
    str r0, [r10, #0x4e4]
    mov r5, r6
    mov r4, r7
@L0218bf8c:
    ldr r0, [r10, #0x4e4]
    cmp r0, #0x0
    movgt r0, r7
    movle r0, r6
    cmp r0, #0x0
    beq @L0218bfc4
    mov r0, r10
    bl _ZN12StartupScene11UpdateTimerEv
    bl func_020c9820
    bl func_02012efc
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218bf8c
@L0218bfc4:
    mov r0, r10
    mov r1, #0x0
    mov r2, #0x1f4
    bl _ZN12StartupScene17SetMainBrightnessEii
    mov r0, r10
    mov r1, #0x0
    mov r2, #0x1f4
    bl _ZN12StartupScene16SetSubBrightnessEii
    mov r7, #0x0
    mov r9, #0x1
    ldr r0, =0xbb8
    mov r5, r7
    str r0, [r10, #0x4e4]
    mov r6, r9
    mov r4, r7
    mov r11, r9
@L0218c004:
    ldr r0, [r10, #0x4fc]
    cmp r0, #0x0
    movgt r0, r9
    movle r0, r7
    cmp r0, #0x0
    bne @L0218c040
    ldr r0, [r10, #0x4e4]
    cmp r0, #0x0
    movgt r0, r6
    movle r0, r5
    cmp r0, #0x0
    beq @L0218c05c
    mov r0, r10
    bl _ZN12StartupScene11UpdateTimerEv
    bl func_02012efc
@L0218c040:
    mov r0, r10
    bl _ZN12StartupScene16UpdateBrightnessEv
    bl func_020c9820
    mov r0, r4
    mov r1, r11
    bl func_020d86d0
    b @L0218c004
@L0218c05c:
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x1f4
    bl _ZN12StartupScene17SetMainBrightnessEii
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x1f4
    bl _ZN12StartupScene16SetSubBrightnessEii
    mov r6, #0x0
    mov r7, #0x1
    mov r5, r6
    mov r4, r7
@L0218c08c:
    ldr r0, [r10, #0x4fc]
    cmp r0, #0x0
    movgt r0, r7
    movle r0, r6
    cmp r0, #0x0
    beq @L0218c0c4
    mov r0, r10
    bl _ZN12StartupScene16UpdateBrightnessEv
    bl func_020c9820
    bl func_02012efc
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218c08c
@L0218c0c4:
    mov r0, #0x3e8
    mov r6, #0x0
    mov r7, #0x1
    str r0, [r10, #0x4e4]
    mov r5, r6
    mov r4, r7
@L0218c0dc:
    ldr r0, [r10, #0x4e4]
    cmp r0, #0x0
    movgt r0, r7
    movle r0, r6
    cmp r0, #0x0
    beq @L0218c114
    mov r0, r10
    bl _ZN12StartupScene11UpdateTimerEv
    bl func_020c9820
    bl func_02012efc
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218c0dc
@L0218c114:
    mov r0, r10
    bl _ZN12StartupScene12LoadMobiLogoEv
    bl func_020c38d4
    ldr r4, =0x4001000
    ldr r2, =0x5dc
    ldr r1, [r4, #0x0]
    mov r0, r10
    orr r3, r1, #0x10000
    mov r1, #0x0
    str r3, [r4, #0x0]
    bl _ZN12StartupScene17SetMainBrightnessEii
    ldr r2, =0x5dc
    mov r0, r10
    mov r1, #0x0
    bl _ZN12StartupScene16SetSubBrightnessEii
    ldr r0, =0x1b58
    ldr r6, =data_02114e30
    ldr r11, =0xf0b
    ldr r5, =data_02114e54
    ldr r4, =0x9c4
    str r0, [r10, #0x4e4]
    mov r7, #0x0
    mov r9, #0x1
@L0218c170:
    mov r0, r10
    bl _ZN12StartupScene28IsBrightnessTransitionActiveEv
    cmp r0, #0x0
    bne @L0218c1cc
    ldr r0, [r10, #0x4e4]
    cmp r0, #0x0
    movgt r0, r9
    movle r0, r7
    cmp r0, #0x0
    beq @L0218c1e8
    mov r0, r10
    bl _ZN12StartupScene11UpdateTimerEv
    bl func_02012efc
    ldr r0, [r10, #0x4e4]
    cmp r0, r4
    bgt @L0218c1cc
    mov r0, r6
    mov r1, r11
    bl func_02012444
    cmp r0, #0x0
    ldreqb r0, [r5, #0x55]
    cmpeq r0, #0x0
    bne @L0218c1e8
@L0218c1cc:
    mov r0, r10
    bl _ZN12StartupScene16UpdateBrightnessEv
    bl func_020c9820
    mov r0, #0x0
    mov r1, #0x1
    bl func_020d86d0
    b @L0218c170
@L0218c1e8:
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x3e8
    bl _ZN12StartupScene17SetMainBrightnessEii
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x3e8
    bl _ZN12StartupScene16SetSubBrightnessEii
    mov r6, #0x0
    mov r7, #0x1
    mov r5, r6
    mov r4, r7
@L0218c218:
    ldr r0, [r10, #0x4fc]
    cmp r0, #0x0
    movgt r0, r7
    movle r0, r6
    cmp r0, #0x0
    beq @L0218c250
    mov r0, r10
    bl _ZN12StartupScene16UpdateBrightnessEv
    bl func_020c9820
    bl func_02012efc
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218c218
@L0218c250:
    mov r0, #0x3e8
    mov r6, #0x0
    mov r7, #0x1
    str r0, [r10, #0x4e4]
    mov r5, r6
    mov r4, r7
@L0218c268:
    ldr r0, [r10, #0x4e4]
    cmp r0, #0x0
    movgt r0, r7
    movle r0, r6
    cmp r0, #0x0
    beq @L0218c2a0
    mov r0, r10
    bl _ZN12StartupScene11UpdateTimerEv
    bl func_020c9820
    bl func_02012efc
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218c268
@L0218c2a0:
    mov r0, r10
    mov r1, #0x0
    bl _ZN12StartupScene15LoadCompanyLogoEi
    bl func_020c38d4
    ldr r4, =0x4001000
    ldr r2, =0x5dc
    ldr r1, [r4, #0x0]
    mov r0, r10
    orr r3, r1, #0x10000
    mov r1, #0x0
    str r3, [r4, #0x0]
    bl _ZN12StartupScene17SetMainBrightnessEii
    ldr r2, =0x5dc
    mov r0, r10
    mov r1, #0x0
    bl _ZN12StartupScene16SetSubBrightnessEii
    ldr r0, =0x1770
    mov r7, #0x0
    mov r9, #0x1
    ldr r11, =data_02114e30
    ldr r4, =data_02114e54
    str r0, [r10, #0x4e4]
    mov r5, r7
    mov r6, r9
@L0218c300:
    ldr r0, [r10, #0x4fc]
    cmp r0, #0x0
    movgt r0, r9
    movle r0, r7
    cmp r0, #0x0
    bne @L0218c358
    ldr r0, [r10, #0x4e4]
    cmp r0, #0x0
    movgt r0, r6
    movle r0, r5
    cmp r0, #0x0
    beq @L0218c374
    mov r0, r10
    bl _ZN12StartupScene11UpdateTimerEv
    bl func_02012efc
    ldr r1, =0xf0b
    mov r0, r11
    bl func_02012444
    cmp r0, #0x0
    ldreqb r0, [r4, #0x55]
    cmpeq r0, #0x0
    bne @L0218c374
@L0218c358:
    mov r0, r10
    bl _ZN12StartupScene16UpdateBrightnessEv
    bl func_020c9820
    mov r0, #0x0
    mov r1, #0x1
    bl func_020d86d0
    b @L0218c300
@L0218c374:
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x3e8
    bl _ZN12StartupScene17SetMainBrightnessEii
    mov r0, r10
    mvn r1, #0xf
    mov r2, #0x3e8
    bl _ZN12StartupScene16SetSubBrightnessEii
    mov r6, #0x0
    mov r7, #0x1
    mov r5, r6
    mov r4, r7
@L0218c3a4:
    ldr r0, [r10, #0x4fc]
    cmp r0, #0x0
    movgt r0, r7
    movle r0, r6
    cmp r0, #0x0
    beq @L0218c3dc
    mov r0, r10
    bl _ZN12StartupScene16UpdateBrightnessEv
    bl func_020c9820
    bl func_02012efc
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218c3a4
@L0218c3dc:
    mov r0, #0x3e8
    mov r6, #0x0
    mov r7, #0x1
    str r0, [r10, #0x4e4]
    mov r5, r6
    mov r4, r7
@L0218c3f4:
    ldr r0, [r10, #0x4e4]
    cmp r0, #0x0
    movgt r0, r7
    movle r0, r6
    cmp r0, #0x0
    beq @L0218c42c
    mov r0, r10
    bl _ZN12StartupScene11UpdateTimerEv
    bl func_020c9820
    bl func_02012efc
    mov r0, r5
    mov r1, r4
    bl func_020d86d0
    b @L0218c3f4
@L0218c42c:
    mov r0, #0x0
    ldr r2, =0x7fff
    mov r3, r0
    mov r1, #0x1f
    str r0, [sp, #0x0]
    bl func_020c5588
@L0218c444:
    mov r0, r8
    mov r1, #0x5
    bl func_02012010
    mov r0, r8
    mov r1, #0x0
    bl func_0200fb94
    mov r0, r8
    mov r1, #0x1
    bl func_02012028
    b @L0218c78c
@L0218c46c:
    mov r1, #0x0
    bl func_02012010
    mov r0, r10
    bl _ZN12StartupScene19LoadMenuBackgroundsEv
    bl func_020c38d4
    ldr r2, =0x4001000
    mov r0, r4
    ldr r1, [r2, #0x0]
    orr r1, r1, #0x10000
    str r1, [r2, #0x0]
    bl func_02045cac
    add r0, r10, #0xc
    bl func_0205c790
    mov r0, #0x1
    strb r0, [r10, #0xbd]
    strb r0, [r10, #0xbc]
    bl func_020ab9c0
    cmp r0, #0x4
    mov r9, #0x0
    mov r6, #0x10
    bne @L0218c510
    ldr r7, =sItemsWithOnTheWay
    mov r5, r9
    b @L0218c4f4
@L0218c4cc:
    add r0, r10, #0xc
    add r1, r7, r9, lsl #0x5
    bl func_0205cb74
    mov r0, r4
    mov r1, r6
    bl func_0204359c
    mov r0, r4
    mov r1, r5
    bl func_020439b0
    add r9, r9, #0x1
@L0218c4f4:
    cmp r9, #0x8
    blt @L0218c4cc
    add r0, r10, #0xc
    mov r1, #0x1
    mov r2, #0x8
    bl _ZN8TextMenu7SetGridEii
    b @L0218c55c
@L0218c510:
    ldr r7, =sItems
    mov r5, r9
    b @L0218c544
@L0218c51c:
    add r0, r10, #0xc
    add r1, r7, r9, lsl #0x5
    bl func_0205cb74
    mov r0, r4
    mov r1, r6
    bl func_0204359c
    mov r0, r4
    mov r1, r5
    bl func_020439b0
    add r9, r9, #0x1
@L0218c544:
    cmp r9, #0x7
    blt @L0218c51c
    add r0, r10, #0xc
    mov r1, #0x1
    mov r2, #0x7
    bl _ZN8TextMenu7SetGridEii
@L0218c55c:
    mov r1, #0x0
    add r0, r10, #0xc
    sub r2, r1, #0x4
    bl func_0205cc50
    ldrsh r0, [r10, #0xc4]
    ldrsh r2, [r10, #0xc6]
    mov r1, #0x0
    rsb r0, r0, #0x100
    rsb r2, r2, #0xc0
    mov r0, r0, asr #0x1
    strh r0, [r10, #0xc0]
    mov r3, r2, asr #0x2
    add r0, r10, #0xc
    sub r2, r1, #0x4
    strh r3, [r10, #0xc2]
    bl func_0205cc50
    add r0, r10, #0x2c
    mov r1, #0x0
    bl func_0205bcdc
    add r0, r10, #0x7c
    mov r1, #0x0
    bl func_0205bb04
    mov r0, #0x2
    bl MapVRAMBanksToMainObj
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r4, r0
    bl func_020421a0
    mov r5, r0
@L0218c5cc:
    mov r0, r5
    bl func_02043368
    ldrb r0, [r5, #0x2e7]
    cmp r0, #0x2
    beq @L0218c5ec
    mov r0, r4
    bl _ZN16BackgroundLoader14RemoveAllLocksEv
    b @L0218c5cc
@L0218c5ec:
    bl func_0203bd08
    mov r9, r0
    bl func_0203bd24
    ldr r0, =data_02108760
    bl func_0205e8ec
    ldr r0, =data_02109bf4
    mov r1, #0x2
    bl func_0209c3b4
    mvn r5, #0x0
    sub r4, r5, #0xff000000
    mov r7, #0x1
    ldr r6, =0x4000060
    ldr r11, =0xcfdf
    b @L0218c748
@L0218c624:
    bl func_02012efc
    ldr r0, [r10, #0x4]
    add r0, r0, #0x1
    str r0, [r10, #0x4]
    cmp r0, r4
    strge r7, [r10, #0x4]
    bl func_020c52e8
    bl func_020c5414
    ldrh r0, [r6, #0x0]
    and r0, r0, r11
    strh r0, [r6, #0x0]
    ldr r0, [r10, #0x0]
    cmp r0, #0x64
    bne @L0218c704
    mov r0, r10
    bl _ZN12StartupScene10UpdateMenuEv
    b @L0218c708
@L0218c704:
    str r5, [r10, #0x0]
@L0218c708:
    mov r0, #0x0
    mov r1, #0x1
    bl func_020d86d0
    mov r0, r9
    bl func_0203bd88
    bl func_020c9820
    mov r0, r9
    bl func_0203bdb0
    bl func_020bbcb4
    bl func_020bbd9c
    add r0, r6, #0xc
    mov r1, #0x0
    bl func_020c39a0
    ldr r0, =0x400106c
    mov r1, #0x0
    bl func_020c39a0
@L0218c748:
    ldr r0, [r10, #0x0]
    cmp r0, r5
    bne @L0218c624
    mov r0, r8
    bl func_0200fb9c
    cmp r0, #0x0
    mov r0, r8
    bne @L0218c774
    mov r1, #0x6
    bl func_02012010
    b @L0218c78c
@L0218c774:
    bl func_0200fb9c
    cmp r0, #0x5
    bne @L0218c78c
    mov r0, r8
    mov r1, #0x6
    bl func_02012010
@L0218c78c:
    mov r0, r10
    bl _ZN12StartupScene7CleanupEv
    add r0, r10, #0x244
    bl func_0207df50
    ldr r0, =0x400006c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    add sp, sp, #0xa0
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void TextMenu::SetGrid(int columns, int rows)
{
    func_0205ba68(unk_20, columns, rows, 0);
    func_0205ba68(unk_70, columns, rows, 0);
    int count = columns * rows;
    func_0205bacc(unk_20, count);
    func_0205bacc(unk_70, count);
}

void StartupScene::UpdateMenu()
{
    GameState* gameState = GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    if (frame_ == 0)
    {
        menu_.unk_233 = 1;
        menu_.unk_234 = 1;
        func_0205c77c(menu_.unk_4);
        func_0205cd28(&menu_);
    }
    func_0205c904(&menu_, 1);
    if (messages->unk_2e0 != NULL)
        func_0205a330(messages->unk_2e0, 1);
    if (func_0205cde8(&menu_))
    {
        if (frame_ > 5)
            DISPCNT = (DISPCNT & ~0x1f00) | 0x1300;
        if (func_02012444(data_02114e30, PAD_BUTTON_A | PAD_BUTTON_X) | (func_0205cecc(&menu_) >= 0))
        {
            int item = func_0205cb64(&menu_);
            if (func_0200fb9c(gameState) == 6)
                return;
            if (func_020ab9c0(1) == 4)
            {
                func_0200fb94(gameState, sModesWithOnTheWay[item]);
                state_ = State_End;
                frame_ = -1;
                return;
            }
            func_0200fb94(gameState, sModes[item]);
            state_ = State_End;
            frame_ = -1;
            return;
        }
    }
    func_0205c96c(&menu_, 0);
}

void StartupScene::LoadMenuBackgrounds()
{
    allocator_.Reset();
    MapVRAMBanksToMainBG(8);
    G2_SetBG1Control(0, 1, 1, 1, 0);
    func_0204af64(&mainBackground_);
    func_0204b11c(&mainBackground_, 0);
    mainBackground_.unk_1c_0_ = 0;
    mainBackground_.unk_1c_4_ = 1;
    func_0204b5b4(&mainBackground_, 1);
    func_0204b12c(&mainBackground_, &allocator_);
    func_0204af38(&mainBackground_, 1, &allocator_);
    func_0204b5e8(&mainBackground_, 0, 0);
    MapVRAMBanksToSubBG(4);
    G2S_SetBG0Control(0, 1, 1, 1, 0);
    func_0204af64(&subBackground_);
    func_0204b11c(&subBackground_, 0);
    subBackground_.unk_1c_0_ = 1;
    subBackground_.unk_1c_4_ = 0;
    func_0204b5b4(&subBackground_, 0);
    func_0204b12c(&subBackground_, &allocator_);
    func_0204af38(&subBackground_, 1, &allocator_);
    func_0204b5e8(&subBackground_, 0, 0);
    // Declared first, so that the compiler gives it and the loader the original's registers
    int taskID;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    loader->MaybeReset();
    taskID = loader->QueueLoadFile(STRING(0xc1, "data/ani/bg_title.pac"), NULL);
    while (true)
    {
        if (loader->GetTaskStatus(taskID))
        {
            void* files[5];
            unsigned int sizes[5];
            void* name;
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(taskID, &file, &size);
            int numFiles = func_02046900(file);
            for (int i = 0; i < numFiles; i++)
                files[i] = func_020467f0(file, i, &name, &sizes[i]);
            int mainFiles[3] = {0, 2, 3};
            int subFiles[3] = {1, 2, 4};
            int main = 0;
            int sub = 0;
            for (int i = 0; i < numFiles; i++)
            {
                if (i == mainFiles[main])
                {
                    func_0204b174(&mainBackground_, files[i], &allocator_, sizes[i]);
                    main++;
                }
                if (i == subFiles[sub])
                {
                    func_0204b174(&subBackground_, files[i], &allocator_, sizes[i]);
                    sub++;
                }
            }
            loader->RemoveTask(taskID);
            func_0204b8d0(&mainBackground_, 0, 0, 0, 0, 0, 0x20, 0x19, 0);
            func_0204b8d0(&subBackground_, 0, 0, 0, 0, 0, 0x20, 0x19, 0);
            func_0204b0e8(&mainBackground_, 0);
            func_0204b0e8(&subBackground_, 0);
            break;
        }
        loader->RemoveAllLocks();
    }
    BLDCNT = 0;
    BLDCNTSUB = 0;
    ColorEffect_ConfigureAlphaBlend(0x04000050, 1, 2, 0xf, 0x1f);
    ColorEffect_ConfigureAlphaBlend(0x04001050, 1, 2, 0x1f, 0);
    DISPCNT = (DISPCNT & ~0x1f00) | 0x300;
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x100;
    func_020c39a0(REG_MASTER_BRIGHT, 0);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, 0);
}

void StartupScene::LoadNintendoLogo()
{
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    allocator_.Reset();
    MapVRAMBanksToSubBG(4);
    G2S_SetBG0Control(0, 1, 1, 1, 0);
    func_0204af64(&subBackground_);
    func_0204b11c(&subBackground_, 0);
    // Through a pointer, the compiler computes the address of the bitfields like the original
    BackgroundGraphics* background = &subBackground_;
    background->unk_1c_0_ = 1;
    background->unk_1c_4_ = 0;
    func_0204b5b4(background, 0);
    func_0204b12c(&subBackground_, &allocator_);
    func_0204af38(&subBackground_, 1, &allocator_);
    func_0204b5e8(&subBackground_, 0, 0);
    BackgroundLoader::AddLockGlobal();
    unsigned int size = 0;
    LoadFileIntoMemory(STRING(0xd7, "data/menu/nintendo.pac"), data_0211e33c, &size);
    int numFiles = func_02046900(data_0211e33c);
    for (int i = 0; i < numFiles; i++)
    {
        unsigned int dataSize;
        void* name;
        void* data = func_020467f0(data_0211e33c, i, &name, &dataSize);
        if (data != NULL)
            func_0204b174(&subBackground_, data, &allocator_, dataSize);
    }
    func_0204b8d0(&subBackground_, 0, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
    func_0204b0e8(&subBackground_, 0);
    BackgroundLoader::RemoveLockGlobal();
    BLDCNT = 0;
    BLDCNTSUB = 0;
    DISPCNT = (DISPCNT & ~0x1f00) | 0x1300;
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x100;
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
}

void StartupScene::LoadMobiLogo()
{
    allocator_.Reset();
    MapVRAMBanksToMainBG(8);
    G2_SetBG1Control(0, 0, 0x1f, 2, 0);
    func_0204af64(&mainBackground_);
    func_0204b11c(&mainBackground_, 0);
    mainBackground_.unk_1c_0_ = 0;
    mainBackground_.unk_1c_4_ = 1;
    func_0204b5b4(&mainBackground_, 0);
    func_0204b12c(&mainBackground_, &allocator_);
    func_0204af38(&mainBackground_, 1, &allocator_);
    func_0204b5e8(&mainBackground_, 0, 0);
    MapVRAMBanksToSubBG(4);
    G2S_SetBG0Control(0, 0, 1, 1, 0);
    func_0204af64(&subBackground_);
    func_0204b11c(&subBackground_, 0);
    subBackground_.unk_1c_0_ = 1;
    subBackground_.unk_1c_4_ = 0;
    func_0204b5b4(&subBackground_, 0);
    func_0204b12c(&subBackground_, &allocator_);
    func_0204af38(&subBackground_, 1, &allocator_);
    func_0204b5e8(&subBackground_, 0, 0);
    int taskID;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    loader->MaybeReset();
    taskID = loader->QueueLoadFile(STRING(0xee, "data/menu/bg_mobi_2.pac"), NULL);
    while (true)
    {
        if (loader->GetTaskStatus(taskID))
        {
            void* files[6];
            unsigned int sizes[6];
            void* name;
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(taskID, &file, &size);
            int numFiles = func_02046900(file);
            for (int i = 0; i < numFiles; i++)
                files[i] = func_020467f0(file, i, &name, &sizes[i]);
            int mainFiles[3] = {0, 2, 4};
            int subFiles[3] = {1, 3, 5};
            int main = 0;
            int sub = 0;
            for (int i = 0; i < numFiles; i++)
            {
                if (i == mainFiles[main])
                {
                    func_0204b174(&mainBackground_, files[i], &allocator_, sizes[i]);
                    main++;
                }
                if (i == subFiles[sub])
                {
                    func_0204b174(&subBackground_, files[i], &allocator_, sizes[i]);
                    sub++;
                }
            }
            loader->RemoveTask(taskID);
            func_0204b8d0(&mainBackground_, 0, 0, 0, 0, 0, 0x20, 0x19, 0);
            func_0204b8d0(&subBackground_, 0, 0, 0, 0, 0, 0x20, 0x19, 0);
            func_0204b0e8(&mainBackground_, 0);
            func_0204b0e8(&subBackground_, 0);
            break;
        }
        loader->RemoveAllLocks();
    }
    BLDCNT = 0;
    BLDCNTSUB = 0;
    DISPCNT = (DISPCNT & ~0x1f00) | 0x200;
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x100;
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
}

void StartupScene::LoadCompanyLogo(int company)
{
    allocator_.Reset();
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    MapVRAMBanksToMainBG(8);
    G2_SetBG1Control(0, 1, 1, 1, 0);
    func_0204af64(&mainBackground_);
    func_0204b11c(&mainBackground_, 0);
    BackgroundGraphics* background = &mainBackground_;
    background->unk_1c_0_ = 0;
    background->unk_1c_4_ = 1;
    func_0204b5b4(background, 1);
    func_0204b12c(&mainBackground_, &allocator_);
    func_0204af38(&mainBackground_, 1, &allocator_);
    func_0204b5e8(&mainBackground_, 0, 0);
    DisableSubObjVRAMBanks();
    DisableSubBGVRAMBanks();
    func_020c3984(0);
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x100;
    MapVRAMBanksToSubObj(0x100);
    DISPCNTSUB = (DISPCNTSUB & ~0x300010) | 0x10;
    MapVRAMBanksToSubBG(0x80);
    G2S_SetBG0Control(0, 0, 0xe, 0, 0);
    G2S_SetBG0Control(0, 0, 0xf, 0, 0);
    BG0CNTSUB = (BG0CNTSUB & ~BGCNT_MASK_PRIORITY) | 1;
    BG1CNTSUB = (BG1CNTSUB & ~BGCNT_MASK_PRIORITY) | 2;
    BG2CNTSUB = BG2CNTSUB & ~BGCNT_MASK_PRIORITY;
    BG3CNTSUB = (BG3CNTSUB & ~BGCNT_MASK_PRIORITY) | 3;
    BackgroundLoader::AddLockGlobal();
    unsigned int size;
    if (company == 1)
        LoadFileIntoMemory(STRING(0x106, "data/menu/bg_sqen.pac"), data_0211e33c, &size);
    else
        LoadFileIntoMemory(STRING(0x11c, "data/menu/bg_lv5.pac"), data_0211e33c, &size);
    void* name;
    // The original reads each file again for the second call of the loop below
    void* volatile files[3];
    unsigned int sizes[3];
    int numFiles = func_02046900(data_0211e33c);
    for (int i = 0; i < numFiles; i++)
        files[i] = func_020467f0(data_0211e33c, i, &name, &sizes[i]);
    BackgroundGraphics graphics;
    func_0204af64(&graphics);
    graphics.unk_1c_0_ = 1;
    graphics.unk_1c_4_ = 0;
    func_0204b5b4(&graphics, 3);
    func_0204b11c(&graphics, 0);
    func_0204b5e8(&graphics, 0, 0);
    for (int i = 0; i < 3; i++)
    {
        func_0204b2e0(&graphics, files[i]);
        func_0204b3a0(&graphics, files[i]);
    }
    func_0204b0e8(&graphics, 0);
    func_0204afb4(&graphics);
    BackgroundLoader::RemoveLockGlobal();
    BLDCNT = 0;
    BLDCNTSUB = 0;
    ColorEffect_ConfigureAlphaBlend(0x04000050, 1, 2, 0xf, 0x1f);
    DISPCNT = (DISPCNT & ~0x1f00) | 0x1300;
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
}

void StartupScene::UpdateBrightness()
{
    int delta = GameState::GetInstance()->GetEffectiveDeltaTime();
    if (IsMainBrightnessTransitionActive())
    {
        mainBrightness_ += (float)delta * (((float)mainBrightnessTarget_ - mainBrightness_) /
                                           (float)mainBrightnessTimeRemaining_);
        mainBrightnessTimeRemaining_ -= delta;
        if (mainBrightnessTimeRemaining_ <= 0)
        {
            mainBrightness_ = (float)mainBrightnessTarget_;
            mainBrightnessTimeRemaining_ = 0;
        }
        func_020c39a0(REG_MASTER_BRIGHT, (int)mainBrightness_);
    }
    if (IsSubBrightnessTransitionActive())
    {
        subBrightness_ += (float)delta * (((float)subBrightnessTarget_ - subBrightness_) /
                                          (float)subBrightnessTimeRemaining_);
        subBrightnessTimeRemaining_ -= delta;
        if (subBrightnessTimeRemaining_ <= 0)
        {
            subBrightness_ = (float)subBrightnessTarget_;
            subBrightnessTimeRemaining_ = 0;
        }
        func_020c39a0(REG_MASTER_BRIGHT_SUB, (int)subBrightness_);
    }
}

void StartupScene::SetMainBrightness(int brightness, int duration)
{
    if (duration == 0)
    {
        func_020c39a0(REG_MASTER_BRIGHT, brightness);
        mainBrightness_ = (float)brightness;
        mainBrightnessTarget_ = brightness;
        mainBrightnessTimeRemaining_ = 0;
    }
    else
    {
        mainBrightness_ = (float)func_020c39c8(REG_MASTER_BRIGHT);
        mainBrightnessTarget_ = brightness;
        mainBrightnessTimeRemaining_ = duration;
    }
}

void StartupScene::SetSubBrightness(int brightness, int duration)
{
    if (duration == 0)
    {
        func_020c39a0(REG_MASTER_BRIGHT_SUB, brightness);
        subBrightness_ = (float)brightness;
        subBrightnessTarget_ = brightness;
        subBrightnessTimeRemaining_ = 0;
    }
    else
    {
        subBrightness_ = (float)func_020c39c8(REG_MASTER_BRIGHT_SUB);
        subBrightnessTarget_ = brightness;
        subBrightnessTimeRemaining_ = duration;
    }
}

void StartupScene::UpdateTimer()
{
    int delta = GameState::GetInstance()->GetEffectiveDeltaTime();
    if (IsTimerActive())
    {
        timer_ -= delta;
        if (timer_ <= 0)
            timer_ = 0;
    }
}

bool StartupScene::IsBrightnessTransitionActive()
{
    if (IsMainBrightnessTransitionActive() || IsSubBrightnessTransitionActive())
        return true;
    return false;
}

void StartupScene::Cleanup()
{
    GameState* gameState = GameState::GetInstance();
    SignedAllocatorHeader* buffer = allocator_.GetSignedAllocator();
    allocator_.Destroy();
    func_02012da4(&data_02114e20, buffer);
    if (func_0200fb9c(gameState) != 2)
    {
        func_0209c678(data_02109bf4, 0);
        func_0209c20c(data_02109bf4);
        func_0205e8ec(data_02108760);
    }
}
