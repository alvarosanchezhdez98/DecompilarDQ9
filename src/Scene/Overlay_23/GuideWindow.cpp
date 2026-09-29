// The window of the guides of the game: pages of titled texts that overlays 0, 2, 3 and 8 show over their screens
#pragma ipa file
#include "Scene/Overlay_23/GuideWindow.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "GameState/PartyMember.h"
#include "GameState/PlayRecords.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/Cache.h"
#include "System/ColorEffects.h"
#include "System/LoadToVRAM.h"
#include "System/TouchScreen.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define REG_DISPCNT (*(volatile unsigned int*)0x04000000)
#define REG_BG0CNT (*(volatile unsigned short*)0x04000008)
#define REG_BG1CNT (*(volatile unsigned short*)0x0400000a)
#define REG_BG2CNT (*(volatile unsigned short*)0x0400000c)
#define REG_BG3CNT (*(volatile unsigned short*)0x0400000e)
#define REG_DISPCNT_SUB (*(volatile unsigned int*)0x04001000)
#define REG_BG0CNT_SUB (*(volatile unsigned short*)0x04001008)
#define REG_BG1CNT_SUB (*(volatile unsigned short*)0x0400100a)
#define REG_BG2CNT_SUB (*(volatile unsigned short*)0x0400100c)
#define REG_BG3CNT_SUB (*(volatile unsigned short*)0x0400100e)
#define REG_BLDCNT 0x04000050
#define REG_BLDCNT_SUB 0x04001050

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    // The sound player, the pad and the touch screen
    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];
    extern TouchState data_02114e54;

    GameResources* func_0200fb8c(GameState* gameState);
    PartyMember* func_0200ff1c(GameState* gameState, int member);
    int func_020100a8(GameState* gameState);
    int func_02012444(void* pad, int buttons);
    void func_02041a90(char* text, int x, int y);
    void func_02041bac(char* text, int, int, int, int, int);
    void func_02042058(char* text, const char* append);
    int func_020420e8(const char* text, int large);
    MessageSystem* func_020421a0();
    void func_02043204(MessageSystem* messages);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    void func_02046380(MessageSystem* messages);
    void func_02046574(MessageSystem* messages, int index, const char* text);
    void func_02046608(MessageSystem* messages, int, const char* format, char* output, int size, int, int);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    int func_02046900(void* archive);
    void func_0204af38(BackgroundGraphics* background, unsigned char, SafeAllocator* allocator);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204afb4(BackgroundGraphics* background);
    void func_0204b010(BackgroundGraphics* background, int);
    void func_0204b04c(BackgroundGraphics* background, int);
    void func_0204b088(BackgroundGraphics* background, int);
    void func_0204b0e8(BackgroundGraphics* background, int);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b12c(BackgroundGraphics* background, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* background, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* background, int);
    void func_0204b5e8(BackgroundGraphics* background, int, int);
    void func_0204b8d0(BackgroundGraphics* background, int, int, int, short x, short y, short width, short height,
                       int);
    void func_0204bc74(BackgroundGraphics* background, int, int, int, int, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, int size);
    int func_0204c7e0(Canvas* canvas);
    void func_0205a198(Sprite* sprite);
    void func_0205a234(SpriteAnimationList* animations);
    void func_0205a330(SpriteAnimationList* animations, int ticks);
    void func_0205a370(SpriteAnimationList* animations, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* animations, int);
    void func_0205a42c(SpriteAnimationList* animations, int, int);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ae8c(SpriteRenderer* renderer);
    void func_0205cf78(TextWindow* window, Canvas* canvases, int count);
    void func_0205cfd4(TextWindow* window);
    int func_0205d0e0(TextWindow* window, int);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d304(TextWindow* window, char* text, int, int, int, int, int, int);
    void func_0205d5d0(TextWindow* window, int item, char* text, int, int);
    void func_0205d6a0(TextWindow* window, int);
    Canvas* func_0205d81c(TextWindow* window, int item);
    void func_0205de24(TextWindow* window, int, int);
    void func_0205deb4(TextWindow* window, unsigned char item, int);
    void func_0205eaa0(void* sound, int effect, int);
    void func_0205ebc0(void* sound, int, int);
    void func_0205ebec(void* sound);
    void func_0205ebfc(void* sound, int, int);
    void* func_0205ec34();
    int func_0206dfb0(void*, void*, int flag);
    void func_02074af4(void*);
    void func_02074b64(void*);
    void func_02074bd0(void*);
    void func_02074bf4(void*);
    void* func_02094a00();
    void func_02094b34(void* music, int, int, int, int);
    void func_02094b40(void* music);
    int func_02094b4c(void* music);
    void func_0209c830(void*, int);
    int func_0209ca2c(void*);
    void func_020a03c4(PlayRecords* records, int count);
    void func_020ac3c8(GameFlags* flags, const short* ids, int count);
    void* func_020d6c00();
    void func_020dc2bc();
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, short id);
    void func_020e4bf4(char* name, short);
}

// The NitroSDK's functions that set the backgrounds' control registers, which the compiler didn't inline
static inline void G2_SetBG2ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    REG_BG2CNT = (REG_BG2CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}

static inline void G2_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    REG_BG1CNT = (REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) |
                 (bgExtPltt << 13);
}

static inline void G2_SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    REG_BG3CNT = (REG_BG3CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}

static inline void G2S_SetBG3ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    REG_BG3CNT_SUB = (REG_BG3CNT_SUB & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                     (charBase << 2);
}

static inline void G2S_SetBG2ControlText(int screenSize, int colorMode, int screenBase, int charBase)
{
    REG_BG2CNT_SUB = (REG_BG2CNT_SUB & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                     (charBase << 2);
}

static inline void G2S_SetBG1Control(int screenSize, int colorMode, int screenBase, int charBase, int bgExtPltt)
{
    REG_BG1CNT_SUB = (REG_BG1CNT_SUB & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                     (charBase << 2) | (bgExtPltt << 13);
}

// The priorities of the backgrounds and the visible layers (the NitroSDK's inline functions)
#define SET_PRIORITY(reg, priority) ((reg) = ((reg) & ~3) | (priority))
#define SET_VISIBLE_PLANE(reg, planes) ((reg) = ((reg) & ~0x1f00) | ((planes) << 8))

void GuideWindow::CreateAllocators(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;
    unsigned int sizes[4] = {0x2000, 0x4800, 0x400, 0x800};
    allocators_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator) * 4);
    for (int i = 0; i < 4; i++)
    {
        SafeAllocator* allocators = allocators_;
        allocators[i].ResetAllocatorPointer();
        unsigned int size = sizes[i];
        allocators[i].CreateTypeA(allocator->Allocate(size), size);
    }
    renderer_ = (SpriteRenderer*)allocator->Allocate(0x54);
    sprites_ = (Sprite*)allocator->Allocate(sizeof(Sprite) * 4);
    animations_ = (SpriteAnimationList*)allocator->Allocate(sizeof(SpriteAnimationList));
}

void GuideWindow::Initialize(unsigned char type)
{
    type_ = type;
    unk_3a = 0;
    unk_3b = 0;
    func_02074af4(unk_2a);
    func_02074b64(unk_2a);
    mainLayers_ = (REG_DISPCNT & 0x1f00) >> 8;
    subLayers_ = (REG_DISPCNT_SUB & 0x1f00) >> 8;
    allocators_ = NULL;
    func_020dfc40(&texts_);
    for (int i = 0; i < 2; i++)
        func_0204af64(&backgrounds_[i]);
    for (int i = 0; i < 2; i++)
        func_0204af64(&subBackgrounds_[i]);
    for (int i = 0; i < 3; i++)
        func_0204c684(&canvases_[i]);
    func_0205cfd4(&window_);
    pixels_ = NULL;
    renderer_ = NULL;
    sprites_ = NULL;
    animations_ = NULL;
    pages_ = NULL;
    count_ = 0;
    page_ = 0;
    state_ = 0;
    step_ = 0;
    titleStep_ = 0;
    task_ = -1;
    flags_ = 0;
    titleY_ = 0;
    ticks_ = 0;
    titleBackground_ = 0;
    titleScroll_ = 0;
    titleX_ = 0;
    titleTop_ = 0;
    titleWidth_ = 0;
    titleHeight_ = 0;
    arrowX_ = 0;
    closing_ = 0;
}

void GuideWindow::Finish()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (mainLayers_ << 8);
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | (subLayers_ << 8);
    func_02074bd0(unk_2a);
    func_02074bf4(unk_2a);
    if (type_ == 2 || (type_ == 7 && (flags_ & GUIDE_WINDOW_MAIN_SCREEN)))
    {
        func_0204b010(&backgrounds_[0], 0);
        func_0204b04c(&backgrounds_[0], 0);
        func_0204b088(&backgrounds_[0], 0);
        func_0204afb4(&backgrounds_[0]);
        memset(pixels_, 0, 0x20);
        CleanInvalidateCacheRange(pixels_, 0x20);
        LoadToMainBG1CharacterData(pixels_, 0, 0x20);
    }
    pages_ = NULL;
    count_ = 0;
    type_ = 0xff;
    state_ = 0;
    step_ = 0;
    titleStep_ = 0;
    task_ = -1;
    flags_ = 0;
    titleY_ = 0;
    ticks_ = 0;
    titleBackground_ = 0;
    titleScroll_ = 0;
    titleX_ = 0;
    titleTop_ = 0;
    titleWidth_ = 0;
    titleHeight_ = 0;
    arrowX_ = 0;
    SafeAllocator* allocators[5] = {};
    allocators[0] = &allocators_[0];
    allocators[1] = &allocators_[1];
    allocators[2] = &allocators_[2];
    allocators[3] = &allocators_[3];
    for (int i = 0; allocators[i] != NULL; i++)
    {
        if (allocators[i]->GetSignedAllocator())
            allocators[i]->Destroy();
    }
}

void GuideWindow::Close()
{
    if (closing_ != 0)
        return;
    closing_ = 1;
    state_ = 2;
    step_ = 0;
}

// The states, for Update(). Defined here, the compiler lays out the file's data like the original
static void (GuideWindow::*sStates[3])() = {&GuideWindow::State_Load, &GuideWindow::State_Main,
                                           &GuideWindow::State_Close};

void GuideWindow::Update()
{
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    if (state_ != 0)
        func_0205d0e0(&window_, ticks);
    if (sStates[state_] == NULL)
        return;
    (this->*sStates[state_])();
    UpdateTitle();
    UpdateArrow();
}

void GuideWindow::Draw1()
{
    if (state_ == 0)
        return;
    DrawTitleBackground();
    func_0205d1e0(&window_);
    func_0205d228(&window_);
    func_0205d274(&window_);
    DrawArrow();
}

void GuideWindow::Draw2()
{
    if (state_ == 0)
        return;
    func_0205d2bc(&window_);
    if ((flags_ & GUIDE_WINDOW_OPENING) || (flags_ & GUIDE_WINDOW_SKIPPED))
    {
        func_0204b5e8(&backgrounds_[1], 0, titleY_);
        func_0204b088(&backgrounds_[1], 0);
        flags_ &= ~GUIDE_WINDOW_SKIPPED;
    }
    RefreshTitle();
}

void GuideWindow::SetPages(GuidePage* pages, int count)
{
    if (pages != NULL && count != 0)
    {
        pages_ = pages;
        count_ = count;
    }
}

void GuideWindow::State_Load()
{
    unsigned char screens[2];
    unsigned char layers[2];
    unsigned char priorities[2];
    unsigned char subLayers[2];
    SafeAllocator* allocators;
    void* music;
    GameResources* resources;
    BackgroundLoader* loader;
    unsigned char step;
    resources = func_0200fb8c(GameState::GetInstance());
    music = func_02094a00();
    loader = BackgroundLoader::GetInstance();
    step = step_;
    if (step == 0)
    {
        unsigned char type = type_;
        if (type == 0 || type == 1 || type == 6 || (type == 7 && !(flags_ & GUIDE_WINDOW_MAIN_SCREEN)))
            SetSubBrightness(resources, -16, 15);
        else if (type == 2 || (type == 7 && (flags_ & GUIDE_WINDOW_MAIN_SCREEN)))
            SetMainBrightness(resources, -16, 15);
        func_02094b40(music);
        func_02094b34(music, 0x71, 0x201, 0, 0);
        step_++;
    }
    if (step == 1)
    {
        if (IsBrightnessTransitionActive(resources) || !func_02094b4c(music))
            return;
        if (flags_ & GUIDE_WINDOW_PAUSE_MUSIC)
        {
            func_020466e4(func_020d6c00(), 1);
            func_020dc2bc();
        }
        task_ = loader->QueueLoadFileInGP2("data/bin/menu/str_tg.gp2", "str_tg_<LG>.nat", NULL);
        step_++;
    }
    if (step == 2)
    {
        void* file;
        unsigned int size;
        if (!loader->GetTaskStatus(task_))
            return;
        loader->GetLoadedFileByID(task_, &file, &size);
        allocators = allocators_;
        allocators[2].Reset();
        func_020dfec0(&texts_, &allocators[2], file, size);
        loader->RemoveTask(task_);
        task_ = -1;
        text_ = (char*)func_020421a0()->unk_5c;
        if (type_ == 0 || type_ == 1)
        {
            G2S_SetBG1Control(0, 0, 0x1a, 4, 0);
            G2S_SetBG2ControlText(0, 0, 0x1b, 4);
            G2S_SetBG3ControlText(0, 0, 0x1c, 6);
            G2_SetBG3ControlText(0, 0, 0x1d, 2);
            screens[0] = 1;
            screens[1] = 0;
        }
        else if (type_ == 7)
        {
            if (!(flags_ & GUIDE_WINDOW_MAIN_SCREEN))
            {
                G2S_SetBG1Control(0, 0, 0xe, 0, 0);
                G2S_SetBG2ControlText(0, 0, 0xf, 0);
                G2S_SetBG3ControlText(0, 0, 7, 1);
                G2_SetBG3ControlText(0, 0, 0x1e, 2);
                screens[0] = 1;
                screens[1] = 0;
            }
            else
            {
                G2_SetBG1Control(0, 0, 0, 1, 0);
                G2_SetBG2ControlText(0, 0, 0x1f, 1);
                G2_SetBG3ControlText(0, 0, 0x17, 3);
                G2S_SetBG3ControlText(0, 0, 0x17, 2);
                screens[0] = 0;
                screens[1] = 1;
            }
        }
        else if (type_ == 2)
        {
            G2_SetBG1Control(0, 0, 0, 1, 0);
            G2_SetBG2ControlText(0, 0, 0x1f, 1);
            G2_SetBG3ControlText(0, 0, 0x17, 3);
            G2S_SetBG3ControlText(0, 0, 0x17, 2);
            screens[0] = 0;
            screens[1] = 1;
        }
        else if (type_ == 6)
        {
            G2S_SetBG1Control(0, 0, 0xe, 0, 0);
            G2S_SetBG2ControlText(0, 0, 0xf, 0);
            G2S_SetBG3ControlText(0, 0, 7, 1);
            G2_SetBG3ControlText(0, 0, 0x1d, 2);
            screens[0] = 1;
            screens[1] = 0;
        }
        for (int i = 0; i < 2; i++)
        {
            BackgroundGraphics* background = &subBackgrounds_[i];
            func_0204b11c(background, 0);
            background->unk_1c_0_ = screens[i];
            background->unk_1c_4_ = 3;
            func_0204b5b4(background, 0);
            func_0204b5e8(background, 0, 0);
            func_0204b12c(background, &allocators_[1]);
        }
        task_ = loader->QueueLoadFile("data/ani/bg_tm.pac", NULL);
        step_++;
    }
    if (step == 3)
    {
        char name[4];
        void* archive;
        unsigned int archiveSize;
        unsigned int size;
        unsigned char canvases[3];
        if (!loader->GetTaskStatus(task_))
            return;
        allocators = allocators_;
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        for (int i = 0; i < count; i++)
        {
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL && i != 1)
            {
                func_0204b174(&subBackgrounds_[0], file, &allocators[1], size);
                func_0204b174(&subBackgrounds_[1], file, &allocators[1], size);
            }
        }
        loader->RemoveTask(task_);
        task_ = -1;
        for (int i = 0; i < 2; i++)
        {
            BackgroundGraphics* background = &subBackgrounds_[i];
            func_0204bc74(background, 0, 0, 0, 0x20, 0x19, 0);
            func_0204b0e8(background, 0);
        }
        pixels_ = allocators[1].Allocate(0x2a00);
        canvases[0] = 0;
        canvases[1] = 0;
        canvases[2] = 1;
        for (int i = 0; i < 3; i++)
        {
            Canvas* canvas = &canvases_[i];
            func_0204c7a8(canvas, &allocators[1], pixels_, 0x400);
            canvas->background_ = &subBackgrounds_[canvases[i]];
        }
        window_.background_ = &subBackgrounds_[0];
        window_.unk_b2 = 2;
        func_0205cf78(&window_, canvases_, 3);
        task_ = loader->QueueLoadFile(func_020e0434(&texts_, 3), NULL);
        step_++;
    }
    if (step == 4)
    {
        char name[4];
        void* archive;
        unsigned int archiveSize;
        unsigned int size;
        if (!loader->GetTaskStatus(task_))
            return;
        allocators = allocators_;
        allocators->Reset();
        unsigned char type = type_;
        int screen = 0;
        if (type == 0 || type == 1 || type == 6 || (type == 7 && !(flags_ & GUIDE_WINDOW_MAIN_SCREEN)))
            screen = 1;
        else if (type == 2 || (type == 7 && (flags_ & GUIDE_WINDOW_MAIN_SCREEN)))
            screen = 0;
        unsigned char layerTemplate[2] = {1, 2};
        signed char priorityTemplate[2] = {2, 1};
        unsigned char subLayerTemplate[2] = {1, 3};
        for (int i = 0; i < 2; i++)
        {
            BackgroundGraphics* background = &backgrounds_[i];
            func_0204af64(background);
            background->unk_1c_0_ = screen;
            background->unk_1c_4_ = layerTemplate[i];
            func_0204b5b4(background, priorityTemplate[i]);
            func_0204b5e8(background, 0, 0);
            func_0204b12c(background, allocators);
            func_0204af38(background, subLayerTemplate[i], allocators);
        }
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        for (int i = 0; i < count; i++)
        {
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL)
            {
                if (i < 3)
                    func_0204b174(&backgrounds_[0], file, allocators, size);
                else
                    func_0204b174(&backgrounds_[1], file, allocators, size);
            }
        }
        loader->RemoveTask(task_);
        task_ = -1;
        func_0204b8d0(&backgrounds_[0], 0, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
        func_0204b0e8(&backgrounds_[0], 0);
        func_0204bc74(&backgrounds_[1], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(&backgrounds_[1], 0);
        type = type_;
        if ((int)type == 0 || (int)type == 1)
        {
            SET_PRIORITY(REG_BG0CNT, 1);
            SET_PRIORITY(REG_BG1CNT, 2);
            SET_PRIORITY(REG_BG2CNT, 3);
            SET_PRIORITY(REG_BG3CNT, 0);
            SET_VISIBLE_PLANE(REG_DISPCNT, 0x1b);
            SET_PRIORITY(REG_BG0CNT_SUB, 3);
            SET_PRIORITY(REG_BG1CNT_SUB, 2);
            SET_PRIORITY(REG_BG2CNT_SUB, 1);
            SET_PRIORITY(REG_BG3CNT_SUB, 0);
            SET_VISIBLE_PLANE(REG_DISPCNT_SUB, 0x1e);
        }
        else if (type == 7)
        {
            if (!(flags_ & GUIDE_WINDOW_MAIN_SCREEN))
            {
                SET_PRIORITY(REG_BG0CNT, 1);
                SET_PRIORITY(REG_BG1CNT, 2);
                SET_PRIORITY(REG_BG2CNT, 3);
                SET_PRIORITY(REG_BG3CNT, 0);
                SET_VISIBLE_PLANE(REG_DISPCNT, 0x1b);
                SET_PRIORITY(REG_BG0CNT_SUB, 3);
                SET_PRIORITY(REG_BG1CNT_SUB, 2);
                SET_PRIORITY(REG_BG2CNT_SUB, 1);
                SET_PRIORITY(REG_BG3CNT_SUB, 0);
                SET_VISIBLE_PLANE(REG_DISPCNT_SUB, 0x1e);
            }
            else
            {
                SET_PRIORITY(REG_BG0CNT, 3);
                SET_PRIORITY(REG_BG1CNT, 2);
                SET_PRIORITY(REG_BG2CNT, 1);
                SET_PRIORITY(REG_BG3CNT, 0);
                SET_VISIBLE_PLANE(REG_DISPCNT, 0x1e);
                SET_PRIORITY(REG_BG0CNT_SUB, 2);
                SET_PRIORITY(REG_BG1CNT_SUB, 3);
                SET_PRIORITY(REG_BG2CNT_SUB, 1);
                SET_PRIORITY(REG_BG3CNT_SUB, 0);
                SET_VISIBLE_PLANE(REG_DISPCNT_SUB, 0x1f);
            }
        }
        else if (type == 2)
        {
            SET_PRIORITY(REG_BG0CNT, 3);
            SET_PRIORITY(REG_BG1CNT, 2);
            SET_PRIORITY(REG_BG2CNT, 1);
            SET_PRIORITY(REG_BG3CNT, 0);
            SET_VISIBLE_PLANE(REG_DISPCNT, 0x1e);
            SET_PRIORITY(REG_BG0CNT_SUB, 2);
            SET_PRIORITY(REG_BG1CNT_SUB, 3);
            SET_PRIORITY(REG_BG2CNT_SUB, 1);
            SET_PRIORITY(REG_BG3CNT_SUB, 0);
            SET_VISIBLE_PLANE(REG_DISPCNT_SUB, 0x1f);
        }
        else if (type == 6)
        {
            SET_PRIORITY(REG_BG0CNT, 3);
            SET_PRIORITY(REG_BG1CNT, 1);
            SET_PRIORITY(REG_BG2CNT, 2);
            SET_PRIORITY(REG_BG3CNT, 0);
            SET_VISIBLE_PLANE(REG_DISPCNT, 0x19);
            SET_PRIORITY(REG_BG0CNT_SUB, 3);
            SET_PRIORITY(REG_BG1CNT_SUB, 2);
            SET_PRIORITY(REG_BG2CNT_SUB, 1);
            SET_PRIORITY(REG_BG3CNT_SUB, 0);
            SET_VISIBLE_PLANE(REG_DISPCNT_SUB, 0x1e);
        }
        task_ = loader->QueueLoadFile(func_020e0434(&texts_, 4), NULL);
        step_++;
    }
    if (step == 5)
    {
        char name[4];
        void* archive;
        unsigned int archiveSize;
        unsigned int size;
        if (!loader->GetTaskStatus(task_))
            return;
        allocators = allocators_;
        unsigned int screen = backgrounds_[0].unk_1c_0_;
        func_0205a444(renderer_);
        renderer_->unk_50 = screen;
        renderer_->SetSprites(sprites_, 4);
        renderer_->animations_ = animations_;
        for (int i = 0; i < 4; i++)
            func_0205a198(&sprites_[i]);
        func_0205a234(animations_);
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        allocators[3].Reset();
        for (int i = 0; i < count; i++)
        {
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL)
                func_0205a528(renderer_, file, size, &allocators[3]);
        }
        loader->RemoveTask(task_);
        task_ = -1;
        step_++;
    }
    if (step == 6)
    {
        if (backgrounds_[0].unk_1c_0_ == 0)
            SetMainBrightness(resources, 0, 15);
        else
            SetSubBrightness(resources, 0, 15);
        if (pages_ == NULL || count_ == 0)
        {
            state_ = 2;
            step_ = 0;
        }
        else
        {
            state_ = 1;
            step_ = 0;
        }
    }
}

void GuideWindow::State_Main()
{
    GameResources* resources = func_ov017_0218b5b0();
    MessageSystem* messages = func_020421a0();
    if (step_ >= 1 && step_ <= 3 && Skip())
    {
        step_ = 4;
        return;
    }
    unsigned char step = step_;
    if (step == 0)
    {
        if (IsBrightnessTransitionActive(resources))
            return;
        if (!(flags_ & GUIDE_WINDOW_NO_DIMMING))
        {
            if (subBackgrounds_[1].unk_1c_0_ == 0)
                ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT, 0x17, -8);
            else
                ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 0x17, -8);
        }
        int volume = 0x8c;
        if (type_ == 2 || (type_ == 7 && (flags_ & GUIDE_WINDOW_MAIN_SCREEN)))
            volume = 0x1b4;
        func_0205ebc0(data_02108760, volume, volume);
        StartTitle();
        step_++;
    }
    if (step == 1)
    {
        if (flags_ & GUIDE_WINDOW_OPENING)
            return;
        OpenTitle();
        flags_ |= GUIDE_WINDOW_TITLE_SCROLLING;
        func_0205ebfc(data_02108760, 0, 0);
        step_++;
    }
    if (step == 2)
    {
        if (flags_ & GUIDE_WINDOW_TITLE_SCROLLING)
            return;
        OpenText();
        OpenName();
        unsigned char items[2] = {0, 1};
        for (int i = 0; i < 2; i++)
            func_0205deb4(&window_, items[i], 0);
        func_0209c830(data_02109bf4, 0x40);
        step_++;
    }
    if (step == 3)
    {
        flags_ |= GUIDE_WINDOW_SHOWN;
        step++;
        step_++;
    }
    if (step == 4)
    {
        if (!(flags_ & GUIDE_WINDOW_SHOWN))
            return;
        if (flags_ & GUIDE_WINDOW_UNK_400)
        {
            void* unknown = func_0205ec34();
            if (page_ == count_ - 1 && func_0206dfb0(unknown, (char*)unknown + 0x8c, 0x119a) &&
                func_0209ca2c(data_02109bf4))
                return;
        }
        if (WasButtonPressed())
            step_++;
    }
    if (step == 5)
    {
        int next = page_ + 1;
        if (next < count_)
        {
            func_0205d6a0(&window_, 1);
            page_ = next;
            step_ = 1;
            StartTitle();
            return;
        }
        step_++;
    }
    if (step == 6)
    {
        func_0205d6a0(&window_, 0);
        func_0205ebec(data_02108760);
        if (!(flags_ & GUIDE_WINDOW_NO_DIMMING))
        {
            if (subBackgrounds_[1].unk_1c_0_ == 0)
                ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT, 0x17, 0);
            else
                ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 0x17, 0);
        }
        if (type_ == 0 || type_ == 1)
            ColorEffect_ConfigureAlphaBlend(REG_BLDCNT, 1, 2, 0xf, 0x1f);
        if (flags_ & GUIDE_WINDOW_UNK_400)
        {
            void* unknown = func_0205ec34();
            if (func_0206dfb0(unknown, (char*)unknown + 0x8c, 0x119a))
            {
                step_++;
                return;
            }
        }
        else if (flags_ & GUIDE_WINDOW_UNK_800)
        {
            step_ = 10;
            return;
        }
        state_ = 2;
        step_ = 0;
    }
    if (step == 7)
    {
        if (subBackgrounds_[1].unk_1c_0_ == 0)
        {
            memset(text_, 0, 0x960);
            func_02042058(text_, func_020e0434(&texts_, 1000));
            func_02042058(text_, func_020e0434(&texts_, 1002));
            messages->busy_ = 1;
            func_0204500c(messages, text_, 0, 0xe3);
            messages->unk_19b2 = 0;
            messages->unk_19c8 = 0;
            messages->unk_19ae = 0;
        }
        else
        {
            OpenEnd();
            unsigned char items2[2] = {0, 1};
            for (int i = 0; i < 2; i++)
                func_0205deb4(&window_, items2[i], 0);
        }
        func_0209c830(data_02109bf4, 0x40);
        step_++;
    }
    if (step == 8)
    {
        messages->unk_19ae = 0;
        if (func_0209ca2c(data_02109bf4))
            return;
        step_++;
        step++;
    }
    if (step == 9)
    {
        if (flags_ & GUIDE_WINDOW_UNK_800)
        {
            if (WasButtonPressed())
            {
                step_++;
                step++;
            }
        }
        else
        {
            step = 11;
            step_ = 11;
        }
    }
    if (step == 10)
    {
        memset(text_, 0, 0x960);
        func_02042058(text_, func_020e0434(&texts_, 1001));
        func_02042058(text_, func_020e0434(&texts_, 1002));
        messages->busy_ = 1;
        func_0204500c(messages, text_, 0, 0xe3);
        messages->unk_19b2 = 0;
        messages->unk_19c8 = 0;
        messages->unk_19ae = 0;
        func_0209c830(data_02109bf4, 0x40);
        step_++;
    }
    if (step == 11)
    {
        messages->unk_19ae = 0;
        if (func_0209ca2c(data_02109bf4))
            return;
        if (!WasButtonPressed())
            return;
        if (subBackgrounds_[1].unk_1c_0_ == 0)
        {
            func_02043204(messages);
            state_ = 2;
            step_ = 0;
            return;
        }
        func_0205d6a0(&window_, 0);
        state_ = 2;
        step_ = 0;
    }
}

void GuideWindow::State_Close()
{
    GameResources* resources = func_ov017_0218b5b0();
    unsigned char step = step_;
    if (step == 0)
    {
        if (backgrounds_[0].unk_1c_0_ == 0)
            SetMainBrightness(resources, -16, 15);
        else
            SetSubBrightness(resources, -16, 15);
        step_++;
    }
    if (step != 1)
        return;
    if (IsBrightnessTransitionActive(resources))
        return;
    if (closing_ != 0)
    {
        if (!(type_ == 0 || type_ == 1) && func_0209ca2c(data_02109bf4))
            return;
        if (!(flags_ & GUIDE_WINDOW_NO_DIMMING))
        {
            if (subBackgrounds_[1].unk_1c_0_ == 0)
                ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT, 0x17, 0);
            else
                ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT_SUB, 0x17, 0);
        }
    }
    func_0205d6a0(&window_, 1);
    flags_ |= GUIDE_WINDOW_MESSAGE_WINDOW;
    if (flags_ & GUIDE_WINDOW_PAUSE_MUSIC)
        func_020466f4(func_020d6c00(), 1);
    step_++;
}

void GuideWindow::StartTitle()
{
    flags_ &= ~GUIDE_WINDOW_SHOWN;
    flags_ |= GUIDE_WINDOW_OPENING;
    ticks_ = 0;
    titleStep_ = 0;
}

void GuideWindow::UpdateTitle()
{
    if (!(flags_ & GUIDE_WINDOW_OPENING))
        return;
    unsigned char step = titleStep_;
    if (step == 0)
    {
        switch (pages_[page_].layout_)
        {
        case 0:
            titleBackground_ = 0;
            titleX_ = 3;
            titleTop_ = 3;
            titleWidth_ = 0x1a;
            titleHeight_ = 7;
            break;
        case 1:
            titleBackground_ = 1;
            titleX_ = 3;
            titleTop_ = 3;
            titleWidth_ = 0x1a;
            titleHeight_ = 7;
            break;
        case 2:
            titleBackground_ = 2;
            titleX_ = 0;
            titleTop_ = 1;
            titleWidth_ = 0x20;
            titleHeight_ = 0xb;
            break;
        }
        titleY_ = 0x60;
        titleScroll_ = (titleY_ - titleTop_ * 8 - 0x41) / 8 + 2;
        if (titleScroll_ <= 0)
            titleScroll_ = 0;
        titleStep_++;
    }
    if (step == 1)
    {
        ticks_ += GameState::GetInstance()->GetTickCount();
        float time = ticks_ / 60.0f;
        float one = 1.0f;
        titleY_ = titleY_ * (time - one) * (time - one);
        titleScroll_ = (titleY_ - titleTop_ * 8 - 0x41) / 8 + 2;
        if (titleScroll_ <= 0)
            titleScroll_ = 0;
        if (titleY_ < 1)
        {
            titleY_ = 0;
            titleStep_++;
        }
    }
    if (step != 2)
        return;
    flags_ &= ~GUIDE_WINDOW_OPENING;
    titleStep_ = 0;
}

void GuideWindow::DrawTitleBackground()
{
    if ((flags_ & GUIDE_WINDOW_OPENING) || (flags_ & GUIDE_WINDOW_SKIPPED))
    {
        func_0204b010(&backgrounds_[1], 0);
        short scroll = titleScroll_;
        func_0204b8d0(&backgrounds_[1], titleBackground_, 0, scroll, titleX_, titleTop_ + scroll, titleWidth_,
                      titleHeight_ - scroll, 0xffff);
        func_0204b04c(&backgrounds_[1], 0);
    }
}

void GuideWindow::UpdateArrow()
{
    if (!(flags_ & GUIDE_WINDOW_TITLE_SCROLLING))
        return;
    unsigned char step = titleStep_;
    if (step == 0)
    {
        arrowX_ = -0x24;
        ticks_ = 0;
        titleStep_++;
    }
    if (step != 1)
        return;
    flags_ |= GUIDE_WINDOW_REDRAW_TITLE;
    ticks_ += GameState::GetInstance()->GetTickCount();
    arrowX_ = (int)(292.0f * (ticks_ / 60.0f)) - 0x24;
    if (arrowX_ <= 0x100)
        return;
    flags_ &= ~GUIDE_WINDOW_TITLE_SCROLLING;
    arrowX_ = -0x24;
    ticks_ = 0;
    flags_ |= GUIDE_WINDOW_TITLE_CHANGED;
    titleStep_ = 0;
}

void GuideWindow::DrawArrow()
{
    if (!(flags_ & GUIDE_WINDOW_TITLE_SCROLLING))
        return;
    GameState* gameState = GameState::GetInstance();
    func_0205a42c(animations_, 0, 0x40);
    func_0205a370(animations_, 0);
    SpriteAnimation* animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
        animation->flags_ |= 8;
    func_0205a330(animations_, gameState->GetTickCount());
    short x = arrowX_;
    animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
    {
        animation->x_ = x;
        animation->y_ = 0x24;
    }
    func_0205ae8c(renderer_);
}

int GuideWindow::WasButtonPressed()
{
    if (!func_02012444(data_02114e30, 0xf03) && data_02114e54.touching_ == 0)
        return 0;
    func_0205eaa0(data_02108760, 1, 0);
    return 1;
}

int GuideWindow::Skip()
{
    if (!WasButtonPressed())
        return 0;
    titleScroll_ = 0;
    titleY_ = 0;
    titleStep_ = 0;
    arrowX_ = -0x24;
    ticks_ = 0;
    flags_ &= ~GUIDE_WINDOW_OPENING;
    flags_ &= ~GUIDE_WINDOW_TITLE_SCROLLING;
    flags_ |= GUIDE_WINDOW_SKIPPED;
    flags_ |= GUIDE_WINDOW_TITLE_CHANGED;
    Canvas* canvas = func_0205d81c(&window_, 0);
    if (canvas != NULL && func_0204c7e0(canvas))
        flags_ |= GUIDE_WINDOW_REDRAW_TITLE;
    else
        OpenTitle();
    if (func_0205d81c(&window_, 1) == NULL)
        OpenText();
    if (func_0205d81c(&window_, 2) == NULL)
        OpenName();
    unsigned char items[2] = {0, 1};
    for (int i = 0; i < 2; i++)
        func_0205deb4(&window_, items[i], 0);
    flags_ |= GUIDE_WINDOW_SHOWN;
    return 1;
}

void GuideWindow::OpenTitle()
{
    func_0205de24(&window_, subBackgrounds_[0].unk_1c_0_, 3);
    window_.SetSize(0x14, 3);
    window_.unk_a4 = 6;
    window_.unk_a6 = 5;
    window_.SetUnkA8(0, 6);
    window_.SetUnkAc(0xc, 0xe);
    window_.unk_b7 = 0xc;
    window_.unk_b1 = 0;
    window_.unk_b5 = 1;
    window_.unk_b6 = 1;
    memset(text_, 0, 0x960);
    WriteTitle(text_);
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 1);
}

void GuideWindow::WriteTitle(char* text)
{
    if (text == NULL)
        return;
    const char* title = pages_[page_].title_;
    int x = (0xa0 - func_020420e8(title, 1)) / 2;
    if (x < 0)
        x = 0;
    func_02041a90(text, x, 6);
    if (title != NULL)
        func_02042058(text, title);
    if (!(flags_ & GUIDE_WINDOW_TITLE_CHANGED))
    {
        short left = arrowX_ - 0xc;
        short width = 0xa0 - left;
        if (left > 0 && width > 0)
            func_02041bac(text, 1, left, 1, width, 0x16);
        else if (left <= 0)
            func_02041bac(text, 1, 1, 1, 0x9e, 0x16);
    }
    flags_ &= ~GUIDE_WINDOW_TITLE_CHANGED;
}

void GuideWindow::OpenText()
{
    func_0205de24(&window_, subBackgrounds_[0].unk_1c_0_, 3);
    window_.SetSize(0x1e, 0xa);
    window_.unk_a4 = 1;
    window_.unk_a6 = 0xd;
    window_.SetUnkA8(7, 8);
    window_.SetUnkAc(0xc, 0xc);
    window_.unk_b7 = 0xc;
    window_.unk_b1 = 1;
    window_.unk_b5 = 0;
    window_.unk_b6 = 0;
    MessageSystem* messages = func_020421a0();
    memset(text_, 0, 0x960);
    func_02046608(messages, 1, pages_[page_].text_, text_, 0xe3, 0, 1);
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 1);
}

void GuideWindow::RefreshTitle()
{
    if (flags_ & GUIDE_WINDOW_REDRAW_TITLE)
    {
        memset(text_, 0, 0x960);
        WriteTitle(text_);
        func_0205d5d0(&window_, 0, text_, 0, 1);
        flags_ &= ~GUIDE_WINDOW_REDRAW_TITLE;
    }
}

void GuideWindow::OpenName()
{
    char name[12];
    func_0205de24(&window_, subBackgrounds_[1].unk_1c_0_, 3);
    window_.SetSize(0x1e, 7);
    window_.unk_a4 = 1;
    window_.unk_a6 = 9;
    window_.SetUnkA8(7, 0xa);
    window_.SetUnkAc(0xc, 0xc);
    window_.unk_b7 = 0xc;
    window_.unk_b1 = 2;
    window_.unk_b5 = 0;
    window_.unk_b6 = 0;
    GuidePage* page = &pages_[page_];
    memset(text_, 0, 0x960);
    GameState* gameState = GameState::GetInstance();
    PartyMember* member = func_0200ff1c(gameState, func_020100a8(gameState));
    if (member != NULL)
    {
        MessageSystem* messages = func_020421a0();
        func_02046380(messages);
        func_020e4bf4(name, *(short*)((char*)member + 4));
        messages->arguments_ = name;
        func_02046574(messages, 1, page->title_);
        func_02046608(messages, 1, func_020e0434(&texts_, 100), text_, 0xe3, 0, 1);
        func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 1);
    }
}

void GuideWindow::OpenEnd()
{
    func_0205de24(&window_, subBackgrounds_[1].unk_1c_0_, 3);
    window_.SetSize(0x20, 9);
    window_.unk_a4 = 0;
    window_.unk_a6 = 0xf;
    window_.SetUnkA8(0xa, 0xa);
    window_.SetUnkAc(0xc, 0x14);
    window_.unk_b7 = 0xc;
    window_.unk_b1 = 2;
    window_.unk_b5 = 0;
    window_.unk_b6 = 0;
    memset(text_, 0, 0x960);
    func_02042058(text_, func_020e0434(&texts_, 1000));
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 1);
}

int GuideWindow::IsFlagSet(int flag)
{
    GameFlags flags;
    func_020ac460(&flags);
    int set = 0;
    if (flags.flags_[flag / 32] & (1 << (flag % 32)))
        set = 1;
    return set ? 1 : 0;
}

// Sets the flags of the guides of the ids and counts them in the records: returns whether it's the first time
int GuideWindow::SetShown(const short* ids, int count)
{
    if (this == NULL)
        return 0;
    if (ids == NULL)
        return 0;
    if (count == 0)
        return 0;
    short copy[50];
    PlayRecords records;
    GameFlags flags;
    int first = 0;
    func_020ac460(&flags);
    memset(copy, 0, sizeof(copy));
    for (int i = 0; i < count; i++)
        copy[i] = ids[i];
    func_020ac3c8(&flags, copy, count);
    func_020ac4c0(&records);
    if (records.unk_10_0 == 0)
        first |= 1;
    func_020a03c4(&records, count);
    func_020ac494(&records);
    return first;
}
