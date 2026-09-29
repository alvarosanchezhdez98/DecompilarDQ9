// The card of the player's profile that tag mode shows on the sub screen, with its pages of records, profile and
// message. Overlay 12's profile editor and overlay 2 run it
// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_23/ProfileCard.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "GameState/PartyMember.h"
#include "GameState/Profile.h"
#include "System/Cache.h"
#include "System/LoadToVRAM.h"
#include "System/VRAM.h"
#include "Text/ForbiddenWordChecker.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define REG_DISPCNT_SUB (*(volatile unsigned int*)0x04001000)
#define REG_BG0CNT_SUB (*(volatile unsigned short*)0x04001008)
#define REG_BG1CNT_SUB (*(volatile unsigned short*)0x0400100a)
#define REG_BG0OFS_SUB (*(volatile unsigned int*)0x04001010)
#define REG_BG1OFS_SUB (*(volatile unsigned int*)0x04001014)
#define REG_BLDCNT_SUB (*(volatile unsigned short*)0x04001050)

// The screen data of a background, which func_0204af14 returns
struct ScreenData
{
    char unk_0[8];
    unsigned int size_;
    void* data_;
};

// What func_02010828 returns
struct Unknown_02010828
{
    char unk_0[0xf68];
    int unk_f68;
    int unk_f6c;
    int unk_f70;
    int unk_f74;
};

// What func_0202ae18 returns (tag mode's state?)
struct Unknown_0202ae18
{
    char unk_0[4];
};

// How a window of the card is laid out
struct CardWindowLayout
{
    unsigned char id_;
    unsigned char unk_1;
    unsigned char unk_2;
    signed char width_;
    signed char height_;
    unsigned char unk_5;
    unsigned char unk_6;
};

// A function that copies pixels to VRAM
typedef void (*CopyFunction)(const void* pixels, int offset, unsigned int size);

// A method that draws a part of a page
typedef void (ProfileCard::*PageFunction)();

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    int func_0200fb08(GameState* gameState);
    PartyMember* func_0200ff1c(GameState* gameState, int member);
    int func_020100a8(GameState* gameState);
    // The time played since the game was saved
    void func_020103f0(GameState* gameState, unsigned short* hours, unsigned char* minutes, unsigned char* seconds);
    Unknown_02010828* func_02010828(GameState* gameState);
    Unknown_0202ae18* func_0202ae18();
    int func_0202b7d8(Unknown_0202ae18*);
    int func_0202c1a4(Unknown_0202ae18*);
    // The functions that write the control codes of a text
    void func_02041a28(char* text, int x);
    void func_02041a5c(char* text, int y);
    void func_02041a90(char* text, int x, int y);
    void func_02041b70(char* text, int item, const char* itemText);
    void func_02041cc0(char* text, int);
    void func_02041fac(char* text, const char* line, int);
    void func_02042058(char* text, const char* append);
    // Returns the width of a text
    int func_020420e8(const char* text, int large);
    MessageSystem* func_020421a0();
    signed char func_020424e4(const char* character, int);
    CharacterInfo* func_0204254c(const char* character, int);
    CharacterInfo* func_020425b4(int code, int);
    int func_020426bc(const char* text, unsigned char* codes, int);
    void func_02042764(const unsigned char* codes, char* text, int);
    void func_02046380(MessageSystem* messages);
    void func_020465c0(MessageSystem* messages, int index, int value);
    void func_020465d8(MessageSystem* messages, int index, int);
    void func_020465f0(MessageSystem* messages, int index, unsigned char digits);
    void func_02046608(MessageSystem* messages, int, const char* format, char* output, int size, int, int);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    int func_02046900(void* archive);
    CopyFunction func_0204a5e4(int, int);
    void func_0204ae44(ScreenData* screen, unsigned short);
    ScreenData* func_0204af14(BackgroundGraphics* background, unsigned char index);
    void func_0204af38(BackgroundGraphics* background, unsigned char, SafeAllocator* allocator);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204b0e8(BackgroundGraphics* background, int);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b12c(BackgroundGraphics* background, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* background, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* background, int);
    void func_0204b5e8(BackgroundGraphics* background, int, int);
    void func_0204bc74(BackgroundGraphics* background, int, int, int, int, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, int size);
    void func_0204f41c(Canvas* canvas, short x, short y, const char* text, unsigned char size, unsigned char color,
                       short* outX, short* outY, int large);
    void func_0204f914(Canvas* canvas, int color, short left, short top, short right, short bottom);
    void* func_02050064();
    PartyMemberData* func_02053c6c(PartyMember* member);
    void func_0205ac40(SpriteRenderer* renderer);
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
    void func_0205deb4(TextWindow* window, unsigned char item, int);
    const char* func_02072a68(BinTextTable* table, short id);
    void func_02074b64(void*);
    void func_02074bf4(void*);
    int func_020d2ff0(const char* text);
    void func_020dc7e8(int, int);
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, short id);
    char* strstr(const char* text, const char* search);
}

// Draws a character of the message on the canvas of the message page (the message has 3 lines of 19 characters)
static void DrawCharacter(Canvas* canvas, const unsigned char* codes, int index)
{
    if (index >= 0 && index < 57)
    {
        unsigned char code = codes[index];
        int x = index % 19 * 12 + 15;
        int y = index / 19 * 19 + 8;
        func_0204f914(canvas, 1, x, y, x + 12, y + 12);
        if (code != 0xff)
        {
            CharacterInfo* character = func_020425b4(code, 1);
            if (code == 0)
                character = func_0204254c("*", 1);
            short width;
            short height;
            func_0204f41c(canvas, x, y, character->text_, 12, 15, &width, &height, 1);
        }
    }
}

static void ClearTime(PlayTime* time)
{
    time->hours_ = 0;
    time->minutes_ = 0;
    time->seconds_ = 0;
}

void ProfileCard::CreateAllocators(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;
    allocators_[0].CreateTypeA(allocator->Allocate(0x5000), 0x5000);
    allocators_[1].CreateTypeA(allocator->Allocate(0x3400), 0x3400);
    allocators_[2].CreateTypeA(allocator->Allocate(0xccc), 0xccc);
}

void ProfileCard::Initialize(int mode)
{
    allocators_[0].ResetAllocatorPointer();
    allocators_[1].ResetAllocatorPointer();
    allocators_[2].ResetAllocatorPointer();
    GameState* gameState = GameState::GetInstance();
    mode_ = mode;
    subBGBanks_ = GetSubBGVRAMBanks();
    subObjBanks_ = GetSubObjVRAMBanks();
    subLayers_ = (REG_DISPCNT_SUB & 0x1f00) >> 8;
    unk_74 = 0;
    unk_75 = 0;
    func_02074b64(unk_64);
    func_0205cfd4(&window_);
    func_020dfc40(&cardTexts_);
    for (int i = 0; i < 2; i++)
        func_0204af64(&backgrounds_[i]);
    for (int i = 0; i < 5; i++)
        func_0204c684(&canvases_[i]);
    pixels_ = NULL;
    text_ = NULL;
    loaded_ = 0;
    step_ = 0;
    task_ = -1;
    scrollY_ = 0;
    scrollX_ = 0;
    design_ = func_020100a8(gameState);
    strings_ = NULL;
    texts_ = NULL;
    unk_5fc = NULL;
    message_ = NULL;
    renderer_ = NULL;
    sprites_ = NULL;
    unk_60c = 0;
    unk_60d = 0;
    ClearTime(&playTime_);
}

void ProfileCard::Finish()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    REG_BG0OFS_SUB = 0;
    REG_BG1OFS_SUB = 0;
    func_02074bf4(unk_64);
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | (subLayers_ << 8);
    DisableSubBGVRAMBanks();
    MapVRAMBanksToSubBG(subBGBanks_);
    MapVRAMBanksToSubObj(subObjBanks_);
    SafeAllocator* allocators[3] = {&allocators_[0], &allocators_[1], &allocators_[2]};
    for (int i = 0; i < 3; i++)
    {
        SafeAllocator* allocator = allocators[i];
        if (allocator->GetSignedAllocator())
            allocator->Destroy();
    }
}

// The flags and the records of the game in the save data (GameState + 0x104 + 0x7400)
struct SavedRecords
{
    GameFlags flags_;
    PlayRecords records_;
};

// The data of the save file in GameState
static inline char* GetSaveData(GameState* gameState)
{
    return (char*)gameState + 0x104;
}

void ProfileCard::Update(int ticks)
{
    if (ticks == 0)
        ticks = 1;
    if (loaded_ == 0)
        return;
    func_0205d0e0(&window_, ticks);
    REG_BG0OFS_SUB = 0;
    if (mode_ == 0)
    {
        SavedRecords* saved;
        int reset;
        unsigned char minutes;
        GameState* gameState = GameState::GetInstance();
        minutes = playTime_.minutes_;
        reset = 0;
        saved = (SavedRecords*)(GetSaveData(gameState) + 0x7400);
        unsigned short addedHours;
        unsigned char addedSeconds;
        unsigned char addedMinutes;
        addedHours = 0;
        addedMinutes = 0;
        addedSeconds = 0;
        if (playTime_.hours_ == 0 && playTime_.minutes_ == 0)
            reset = 1;
        func_020103f0(GameState::GetInstance(), &addedHours, &addedMinutes, &addedSeconds);
        ClearTime(&playTime_);
        func_020ac614(&playTime_, saved->records_.playTime_.hours_ + addedHours);
        func_020ac644(&playTime_, saved->records_.playTime_.minutes_ + addedMinutes);
        playTime_.seconds_ += (unsigned char)(saved->records_.playTime_.seconds_ + addedSeconds);
        if (playTime_.seconds_ > 59)
        {
            unsigned char added = playTime_.seconds_ / 60;
            if (playTime_.hours_ == 9999 && playTime_.minutes_ + added > 59)
            {
                playTime_.hours_ = 9999;
                playTime_.minutes_ = 59;
                playTime_.seconds_ = 59;
            }
            else
            {
                func_020ac644(&playTime_, added);
                playTime_.seconds_ %= 60;
            }
        }
        int refresh = reset ? 1 : minutes != playTime_.minutes_;
        if (refresh)
            RefreshPage(0, 0);
    }
    scrollX_ -= ticks << 11;
    scrollY_ += ticks << 11;
    if (scrollX_ < -0x100000)
        scrollX_ += 0x100000;
    if (scrollY_ > 0x100000)
        scrollY_ -= 0x100000;
    REG_BG1OFS_SUB = (0x1ff & (scrollX_ >> 12)) | ((0x1ff << 16) & ((scrollY_ >> 12) << 16));
}

// NONMATCHING: the C matches 74.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Only the registers of sprites_ and unk_60c are swapped (r1/r2); tried locals, conditions and pointer forms
#ifdef NONMATCHING
void ProfileCard::Draw1()
{
    if (loaded_ == 0)
        return;
    func_0205d1e0(&window_);
    func_0205d228(&window_);
    func_0205d274(&window_);
    if (mode_ != 2)
        return;
    if (renderer_ == NULL || sprites_ == NULL)
        return;
    Sprite* sprite;
    if (unk_60d != 0)
    {
        sprite = &sprites_[unk_60c];
        sprite->unk_22 = unk_60c + 3;
    }
    else
    {
        sprite = &sprites_[2];
        sprite->unk_22 = 5;
    }
    sprite->x_ = 0xd0000;
    sprite->y_ = 0x10000;
    func_0205ac40(renderer_);
}
#else
asm void ProfileCard::Draw1()
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    ldr r0, [r4, #0x5dc]
    cmp r0, #0x0
    ldmeqia sp!, {r4, pc}
    add r0, r4, #0x78
    bl func_0205d1e0
    add r0, r4, #0x78
    bl func_0205d228
    add r0, r4, #0x78
    bl func_0205d274
    ldr r0, [r4, #0x3c]
    cmp r0, #0x2
    ldmneia sp!, {r4, pc}
    ldr r0, [r4, #0x604]
    cmp r0, #0x0
    ldrne r1, [r4, #0x608]
    cmpne r1, #0x0
    ldmeqia sp!, {r4, pc}
    ldrb r0, [r4, #0x60d]
    cmp r0, #0x0
    ldrneb r2, [r4, #0x60c]
    movne r0, #0x28
    mlane r1, r2, r0, r1
    addne r0, r2, #0x3
    addeq r1, r1, #0x50
    moveq r0, #0x5
    strb r0, [r1, #0x22]
    mov r0, #0xd0000
    str r0, [r1, #0x14]
    mov r0, #0x10000
    str r0, [r1, #0x18]
    ldr r0, [r4, #0x604]
    bl func_0205ac40
    ldmia sp!, {r4, pc}
}
#endif

void ProfileCard::Draw2()
{
    if (loaded_ == 0)
        return;
    func_0205d2bc(&window_);
}

// The color of the texts
static const unsigned short sTextColor = 0x18c6;

int ProfileCard::Load()
{
    void* files[4];
    unsigned int sizes[4];
    void* file;
    unsigned int size;
    int screens[2];
    char name[4];
    void* archive;
    unsigned int archiveSize;
    if (loaded_ != 0)
        return 1;
    int result = 1;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (step_ == 0)
    {
        REG_BG0OFS_SUB = 0;
        REG_BG1OFS_SUB = 0;
        task_ = loader->QueueLoadFileInGP2("data/bin/menu/str_sli.gp2", "str_sli_<LG>.nat", NULL);
        result = 0;
        step_++;
    }
    else if (step_ == 1)
    {
        if (loader->GetTaskStatus(task_))
        {
            loader->GetLoadedFileByID(task_, &file, &size);
            allocators_[2].Reset();
            func_020dfec0(&cardTexts_, &allocators_[2], file, size);
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
        result = 0;
    }
    else if (step_ == 2)
    {
        allocators_[0].Reset();
        text_ = (char*)func_020421a0()->unk_5c;
        __clear(screens, sizeof(screens));
        BackgroundGraphics* background;
        int i;
        for (i = 0; i < 2; i++)
        {
            background = &backgrounds_[i];
            func_0204b11c(background, screens[i]);
            background->unk_1c_0_ = 1;
            background->unk_1c_4_ = i;
            func_0204b5b4(background, i);
            func_0204b12c(background, &allocators_[1]);
            func_0204b5e8(background, 0, 0);
        }
        func_0204af38(&backgrounds_[1], 1, &allocators_[1]);
        DisableSubBGVRAMBanks();
        MapVRAMBanksToSubBG(0x80);
        REG_BG0CNT_SUB = (REG_BG0CNT_SUB & 0x43) | 0xe00;
        REG_BG1CNT_SUB = (REG_BG1CNT_SUB & 0x43) | 0xf00;
        REG_BLDCNT_SUB = 0;
        loader->MaybeFreeAllocations();
        task_ = loader->QueueLoadFile("data/ani/bg_slime3.pac", NULL);
        result = 0;
        step_++;
    }
    else if (step_ == 3)
    {
        if (loader->GetTaskStatus(task_))
        {
            loader->GetLoadedFileByID(task_, &archive, &archiveSize);
            int count = func_02046900(archive);
            for (int i = 0; i < count; i++)
                files[i] = func_020467f0(archive, i, name, &sizes[i]);
            BackgroundGraphics* background = &backgrounds_[0];
            for (int i = 0; i < count; i++)
            {
                if (files[i] != NULL)
                    func_0204b174(background, files[i], &allocators_[1], sizes[i]);
                background = &backgrounds_[1];
            }
            loader->RemoveTask(task_);
            task_ = -1;
            func_0204bc74(&backgrounds_[0], 0, 0, 0, 0x20, 0x19, 0);
            func_0204b0e8(&backgrounds_[0], 0);
            ScreenData* screen = func_0204af14(&backgrounds_[1], 0);
            if (screen != NULL)
            {
                void* data;
                unsigned int screenSize;
                screenSize = screen->size_;
                data = screen->data_;
                CleanInvalidateCacheRange(data, screenSize);
                LoadToSubBG1ScreenData(data, 0, screenSize);
            }
            pixels_ = allocators_[0].Allocate(0x4e00);
            Canvas* canvas;
            int j;
            for (j = 0; j < 4; j++)
            {
                canvas = &canvases_[j];
                func_0204c7a8(canvas, &allocators_[1], pixels_, 0x600);
                canvas->background_ = &backgrounds_[0];
            }
            canvas = &canvases_[4];
            func_0204c7a8(canvas, &allocators_[1], pixels_, 0x40);
            canvas->background_ = &backgrounds_[0];
            window_.background_ = &backgrounds_[0];
            window_.unk_b2 = 1;
            func_0205cf78(&window_, canvases_, 5);
            step_++;
        }
        result = 0;
    }
    else if (step_ == 4)
    {
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1300;
        loaded_ = result;
        step_ = 0;
        func_020dc7e8(2, -1);
        CleanInvalidateCacheRange(&sTextColor, 2);
        LoadToSubBGStandardPalette(&sTextColor, 2, 2);
        CleanCacheRange(&sTextColor, 2);
        CleanInvalidateCacheRange(&sTextColor, 2);
        LoadToSubBGStandardPalette(&sTextColor, 0x22, 2);
        CleanCacheRange(&sTextColor, 2);
    }
    return result;
}

int ProfileCard::SetDesign(int design)
{
    if (loaded_ == 0)
        return 1;
    if (!(design >= 0 && design <= 3 ? 1 : 0))
        return 1;
    ScreenData* screen = func_0204af14(&backgrounds_[1], 0);
    if (screen == NULL)
        return 1;
    func_0204ae44(screen, design + 12);
    void* data = screen->data_;
    unsigned int size = screen->size_;
    CleanInvalidateCacheRange(data, size);
    LoadToSubBG1ScreenData(data, 0, size);
    return 0;
}

void ProfileCard::OpenPage(int page, int design)
{
    if (pixels_ != NULL && loaded_ != 0)
    {
        if (design >= 0 && design <= 3 ? 1 : 0)
        {
            design_ = design;
            unsigned char unused1[1] = {1};
            int unused2[1] = {8};
            short unused3[3] = {2, 5, 11};
            int unused4[1] = {12};
            unsigned char unused5[1] = {1};
            int unused6[1] = {8};
            unsigned char unused7[1] = {1};
            int unused8[1] = {19};
            int unused9[1] = {19};
            int unused10[1] = {0x100000};
            PageFunction functions[3] = {&ProfileCard::OpenRecords, &ProfileCard::OpenProfile,
                                         &ProfileCard::OpenMessage};
            (this->*functions[page])();
        }
    }
}

void ProfileCard::RefreshPage(int page, int design)
{
    if (pixels_ != NULL && loaded_ != 0)
    {
        if (design >= 0 && design <= 3 ? 1 : 0)
        {
            design_ = design;
            PageFunction functions[3] = {&ProfileCard::RefreshRecords, &ProfileCard::RefreshProfile,
                                         &ProfileCard::RefreshMessage};
            (this->*functions[page])();
        }
    }
}

// The layouts of the card's windows
static const CardWindowLayout sWindowLayouts[] = {
    {0, 4, 7, 0x1c, 3, 10, 13},    {1, 4, 7, 0x1c, 6, 10, 13},    {2, 4, 7, 0x1c, 3, 10, 13},
    {11, 6, 10, 0x1a, 14, 10, 21}, {12, 15, 8, 0x20, 8, 12, 19},  {13, 8, 8, 0x20, 8, 12, 19},
    {14, 6, 6, 1, 3, 10, 1},       {15, 6, 6, 1, 3, 10, 1},       {16, 2, 2, 2, 2, 1, 1},
    {0xff, 1, 1, 1, 1, 1, 1},
};

void ProfileCard::SetWindow(int id, short x, short y)
{
    for (int i = 0; sWindowLayouts[i].id_ != 0xff; i++)
    {
        const CardWindowLayout* layout = &sWindowLayouts[i];
        if (layout->id_ == id)
        {
            window_.unk_b1 = layout->id_;
            window_.unk_a4 = x;
            window_.unk_a6 = y;
            window_.SetUnkA8(layout->unk_1, layout->unk_2);
            window_.SetSize(layout->width_, layout->height_);
            window_.SetUnkAc(layout->unk_5, layout->unk_6);
            window_.unk_b5 = 0;
            window_.unk_b6 = 0;
            if (layout->id_ == 16)
            {
                window_.unk_b5 = 1;
                window_.unk_b6 = 1;
            }
            return;
        }
    }
}

void ProfileCard::OpenRecords()
{
    MessageSystem* messages = func_020421a0();
    PageFunction functions[3] = {&ProfileCard::DrawPlayTime, &ProfileCard::DrawRecords, &ProfileCard::DrawUnkF74};
    short y[3] = {2, 5, 11};
    for (unsigned char i = 0; i < 3; i++)
    {
        func_02046380(messages);
        SetWindow(i, 2, y[i]);
        memset(text_, 0, 0x960);
        (this->*functions[i])();
        func_0205d304(&window_, text_, 0, 0, 0, 1, 0, 0);
    }
    for (int i = 0; i < 3; i++)
        func_0205deb4(&window_, i, 0);
}

void ProfileCard::RefreshRecords()
{
    PageFunction functions[3] = {&ProfileCard::DrawPlayTime, &ProfileCard::DrawRecords, &ProfileCard::DrawUnkF74};
    MessageSystem* messages = func_020421a0();
    for (unsigned char i = 0; i < 3; i++)
    {
        func_02046380(messages);
        memset(text_, 0, 0x960);
        (this->*functions[i])();
        func_0205d5d0(&window_, i, text_, 1, 0);
    }
}

void ProfileCard::OpenProfile()
{
    func_0205d6a0(&window_, 1);
    SetWindow(11, 3, 5);
    memset(text_, 0, 0x960);
    if (strings_ != NULL)
        DrawProfile();
    func_0205d304(&window_, text_, 0, 0, 0, 1, 0, 0);
}

void ProfileCard::RefreshProfile()
{
    memset(text_, 0, 0x960);
    DrawProfile();
    func_0205d5d0(&window_, 11, text_, 1, 0);
}

void ProfileCard::OpenMessage()
{
    func_0205d6a0(&window_, 1);
    SetWindow(12, 0, 5);
    memset(text_, 0, 0x960);
    DrawUnk5fc();
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 1);
    SetWindow(13, 0, 16);
    memset(text_, 0, 0x960);
    DrawMessage();
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 1);
    SetWindow(14, 0, 2);
    memset(text_, 0, 0x960);
    DrawName();
    func_0205d304(&window_, text_, 1, 0, 0, 1, 0, 0);
    SetWindow(15, 0, 13);
    func_0205d304(&window_, text_, 1, 0, 0, 1, 0, 0);
    SetWindow(16, 15, 13);
    memset(text_, 0, 0x960);
    DrawLabel();
    func_0205d304(&window_, text_, 1, 1, 0, 1, 0, 1);
    for (int i = 0; i < 5; i++)
        func_0205deb4(&window_, i + 12, 0);
}

void ProfileCard::RefreshMessage()
{
    memset(text_, 0, 0x960);
    DrawUnk5fc();
    func_0205d5d0(&window_, 12, text_, 0, 1);
    memset(text_, 0, 0x960);
    DrawMessage();
    func_0205d5d0(&window_, 13, text_, 0, 1);
}

// Draws the characters of the message around the cursor again
void ProfileCard::RedrawMessage()
{
    char* message = message_;
    Canvas* canvas = func_0205d81c(&window_, 13);
    if (canvas == NULL)
        return;
    void* pixels = canvas->pixels_;
    unsigned int offset = canvas->unk_a0;
    unsigned int size = canvas->unk_a4;
    char* saved = (char*)func_02050064();
    BackgroundGraphics* background = canvas->background_;
    memcpy(pixels, saved + offset, size);
    ProfileData* profile = GetProfile(GameState::GetInstance());
    unsigned char codes[0x3a] = {};
    char text[0x400] = {};
    int length;
    if (message != NULL)
    {
        length = func_020426bc(message, codes, 1);
    }
    else
    {
        length = func_020d2ff0(profile->unk_8);
        memcpy(codes, profile->unk_8, length);
    }
    DrawCharacter(canvas, codes, length - 1);
    DrawCharacter(canvas, codes, length);
    DrawCharacter(canvas, codes, length + 1);
    static CopyFunction copy = func_0204a5e4(background->unk_1c_0_, background->unk_1c_4_);
    int unused1[1] = {15};
    int unused2[1] = {12};
    int unused3[1] = {15};
    CleanInvalidateCacheRange(pixels, size);
    copy(pixels, offset, size);
    CleanCacheRange(pixels, size);
}

void ProfileCard::DrawPlayTime()
{
    MessageSystem* messages = func_020421a0();
    int values[2] = {playTime_.hours_, playTime_.minutes_};
    int digits[2] = {4, 2};
    for (int i = 0; i < 2; i++)
    {
        func_020465c0(messages, i, values[i]);
        func_020465d8(messages, i, 1);
        func_020465f0(messages, i, digits[i]);
    }
    func_02046608(messages, 10, func_020e0434(&cardTexts_, 0), text_, 0x100, 0, 0);
    int x1;
    int x2;
    char* first = strstr(text_, "<X=");
    char* second = strstr(first + 1, "<X=");
    x1 = 0x82;
    x2 = 0xb4;
    switch (func_0200fb08(GameState::GetInstance()))
    {
    case 2:
    case 5:
        x1 = 0xa5;
        x2 = 0xc1;
        break;
    case 3:
        x1 = 0x92;
        x2 = 0xb6;
        break;
    }
    char number1[4];
    char number2[4];
    sprintf(number1, "%d", x1);
    sprintf(number2, "%d", x2);
    memcpy(first + 3, number1, 3);
    memcpy(second + 3, number2, 3);
}

void ProfileCard::DrawRecords()
{
    Unknown_02010828* unknown = func_02010828(GameState::GetInstance());
    MessageSystem* messages = func_020421a0();
    func_02041cc0(text_, 0x18);
    int values[2] = {unknown->unk_f6c, unknown->unk_f68};
    for (int i = 0; i < 2; i++)
    {
        func_020465c0(messages, i, values[i]);
        func_020465d8(messages, i, 1);
        func_020465f0(messages, i, 10);
    }
    func_02046608(messages, 10, func_020e0434(&cardTexts_, 1), text_, 0x100, 0, 0);
}

void ProfileCard::DrawUnkF74()
{
    Unknown_02010828* unknown = func_02010828(GameState::GetInstance());
    MessageSystem* messages = func_020421a0();
    func_020465c0(messages, 0, unknown->unk_f74);
    func_020465d8(messages, 0, 1);
    func_020465f0(messages, 0, 10);
    func_02046608(messages, 10, func_020e0434(&cardTexts_, 2), text_, 0x100, 0, 0);
}

void ProfileCard::DrawProfile()
{
    GameState* gameState = GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    Unknown_0202ae18* unknown = func_0202ae18();
    PartyMemberData* data = NULL;
    if (func_0202b7d8(unknown) == 0)
    {
        PartyMember* member = func_0200ff1c(gameState, 0);
        if (member != NULL)
            data = func_02053c6c(member);
    }
    else
    {
        PartyMember* member = func_0200ff1c(gameState, func_0202c1a4(unknown));
        if (member != NULL)
            data = func_02053c6c(member);
    }
    if (data == NULL)
        return;
    ProfileData* profile = GetProfile(gameState);
    char* text = text_;
    char buffer[0x20] = {};
    func_02041a28(text, (0xd0 - func_020420e8(data->name_, 0)) >> 1);
    func_02041fac(text, data->name_, 0x10);
    const char* title = func_02072a68(strings_, profile->title_ + 10000);
    func_02041b70(text, 0, func_02072a68(strings_, 2));
    func_02042058(text, func_02072a68(strings_, 0x6c));
    func_02041a28(text, ((0x6e - func_020420e8(title, 0)) >> 1) + 0x56);
    func_02042058(text, title);
    func_02042058(text, func_02072a68(strings_, 0));
    func_02041b70(text, 1, func_02072a68(strings_, 3));
    func_02041a28(text, 0x4c);
    func_02042058(text, func_02072a68(strings_, 0x6c));
    if (profile->showBirthday_)
    {
        func_02041a28(text, 0x5a);
    }
    else
    {
        func_02041a90(text, 0x6e, 0x34);
        func_02046608(messages, 10, func_02072a68(strings_, 0x78), buffer, 0x100, 0, 0);
        func_02042058(text, buffer);
        func_02041a90(text, 0x5a, 0x28);
    }
    if (profile->birthdayChosen_)
    {
        func_020465c0(messages, 0, profile->year_);
        func_020465d8(messages, 0, 1);
        func_020465f0(messages, 0, 4);
        func_02046608(messages, 10, func_02072a68(strings_, 0x64), buffer, 0x100, 0, 0);
        func_02042058(text, buffer);
        memset(buffer, 0, sizeof(buffer));
        func_020465c0(messages, 0, profile->month_);
        func_020465d8(messages, 0, 1);
        func_020465f0(messages, 0, 2);
        func_02046608(messages, 10, func_02072a68(strings_, 0x65), buffer, 0x100, 0, 0);
        func_02042058(text, buffer);
        memset(buffer, 0, sizeof(buffer));
        func_020465c0(messages, 0, profile->day_);
        func_020465d8(messages, 0, 1);
        func_020465f0(messages, 0, 2);
        func_02046608(messages, 10, func_02072a68(strings_, 0x66), buffer, 0x100, 0, 0);
        func_02042058(text, buffer);
        func_02042058(text, func_02072a68(strings_, 0));
    }
    else
    {
        func_02046608(messages, 10, func_02072a68(strings_, 0x6e), buffer, 0x100, 0, 0);
        func_02042058(text, buffer);
        memset(buffer, 0, sizeof(buffer));
        func_02046608(messages, 10, func_02072a68(strings_, 0x6f), buffer, 0x100, 0, 0);
        func_02042058(text, buffer);
        memset(buffer, 0, sizeof(buffer));
        func_02046608(messages, 10, func_02072a68(strings_, 0x70), buffer, 0x100, 0, 0);
        func_02042058(text, buffer);
        func_02042058(text, func_02072a68(strings_, 0));
    }
    int accolade = profile->accolade_;
    short accoladeId = accolade + 20000;
    if (accolade < 700)
        accoladeId = accolade;
    const char* accoladeText = func_02072a68(strings_, accoladeId);
    func_02041a5c(text, 0x42);
    func_02041b70(text, 2, func_02072a68(strings_, 4));
    func_02041a28(text, 0x4c);
    func_02042058(text, func_02072a68(strings_, 0x6c));
    func_02041a28(text, ((0x6e - func_020420e8(accoladeText, 0)) >> 1) + 0x56);
    func_02042058(text, accoladeText);
    func_02042058(text, func_02072a68(strings_, 0));
    short id = 0x6d;
    if (profile->designChosen_)
        id = profile->unk_0_21 + 30000;
    const char* vocation = func_02072a68(strings_, id);
    func_02041b70(text, 3, func_02072a68(strings_, 5));
    func_02041a28(text, 0x4c);
    func_02042058(text, func_02072a68(strings_, 0x6c));
    func_02041a28(text, ((0x6e - func_020420e8(vocation, 0)) >> 1) + 0x56);
    func_02042058(text, vocation);
}

void ProfileCard::DrawUnk5fc()
{
    if (unk_5fc == NULL)
        return;
    func_02042058(text_, unk_5fc);
}

void ProfileCard::DrawMessage()
{
    if (strings_ == NULL)
        return;
    char* text = text_;
    ProfileData* profile = GetProfile(GameState::GetInstance());
    char codes[0x3a] = {};
    char characters[0x400] = {};
    int length;
    if (message_ != NULL)
    {
        length = func_020426bc(message_, (unsigned char*)codes, 1);
    }
    else
    {
        length = func_020d2ff0(profile->unk_8);
        memcpy(codes, profile->unk_8, length);
    }
    int space = func_020424e4("*", 1);
    for (; length < 57; length++)
        codes[length] = space;
    func_02042764((unsigned char*)codes, characters, 1);
    const char* character;
    int x;
    x = 15;
    character = characters;
    int y = 8;
    int column = 0;
    while (true)
    {
        if (*character == 0)
            break;
        int size = 1;
        CharacterInfo* info = func_0204254c(character, 1);
        if (info != NULL)
        {
            func_02041a28(text, x);
            func_02042058(text, info->text_);
            size = info->length_;
        }
        column++;
        character += size;
        x += 12;
        if (column == 19)
        {
            y += 19;
            x = 15;
            column = 0;
            func_02041a5c(text, y);
        }
    }
}

void ProfileCard::DrawName()
{
    if (strings_ == NULL)
        return;
    char* text = text_;
    GameState* gameState = GameState::GetInstance();
    Unknown_0202ae18* unknown = func_0202ae18();
    PartyMemberData* data = NULL;
    if (func_0202b7d8(unknown) == 0)
    {
        PartyMember* member = func_0200ff1c(gameState, 0);
        if (member != NULL)
            data = func_02053c6c(member);
    }
    else
    {
        PartyMember* member = func_0200ff1c(gameState, func_0202c1a4(unknown));
        if (member != NULL)
            data = func_02053c6c(member);
    }
    if (data == NULL)
        return;
    int width = strlen(data->name_) * 5;
    func_02041a28(text, (((width + 6) / 8 + 1) * 8 - width) / 2);
    func_02042058(text, data->name_);
}

void ProfileCard::DrawLabel()
{
    if (strings_ == NULL)
        return;
    char* text = text_;
    func_02042058(text, func_02072a68(strings_, 0x77));
}
