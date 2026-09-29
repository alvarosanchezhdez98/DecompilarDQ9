// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_12/ProfileEditor.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "GameState/PartyMemberData.h"
#include "Resource/Brightness.h"
#include "System/Cache.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include "System/LoadToVRAM.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>
#include <std_library_functions.h>

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    int memcmp(const void* a, const void* b, unsigned long size);
    // Methods of overlay 23, for the assembly
    void _ZN13ProfileEditor18ResetAccoladeTextsEv();
    void _ZN13ProfileEditor11IsConfirmedEv();
    void _ZN13ProfileEditor11IsCancelledEv();
    void _ZN13ProfileEditor11SetItemGridEv();

    // The file of the forbidden words
    extern const char* data_020f285c;
    extern char data_02108760[];
    extern char data_02114e30[];

    int func_02012444(void* pad, int buttons);
    void func_0202ae18();
    // The code of a character of a text, and the character of a code
    signed char func_020424e4(const char* character, int);
    void* func_020425b4(signed char code, int);
    void func_020426bc(const char* text, char* codes, int);
    MessageSystem* func_020421a0();
    void func_02043204(MessageSystem* messages);
    void func_02050400(Canvas* canvas, int);
    void func_0205042c(Canvas* canvas, unsigned char);
    void func_02050440(Canvas* canvas, unsigned char);
    PartyMemberData* func_02053c6c(GameObject* object);
    void func_02074af4(void*);
    void func_02074bd0(void*);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204c684(Canvas* canvas);
    void func_0205cfd4(TextWindow* window);
    void func_0205d048(TextWindow* window);
    int func_0205d0e0(TextWindow* window, int);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d5d0(TextWindow* window, int, char* text, int, int);
    void func_0205d6a0(TextWindow* window, int);
    Canvas* func_0205d81c(TextWindow* window, int canvas);
    void func_0205da88(TextWindow* window, int, int, int);
    void func_0205def8(TextWindow* window, int, int);
    Canvas* func_0205e00c(TextWindow* window, int canvas);
    void func_0204b0e8(BackgroundGraphics* background, int);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b12c(BackgroundGraphics* background, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* background, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* background, int);
    void func_0204b5e8(BackgroundGraphics* background, int, int);
    void func_0204bc74(BackgroundGraphics* background, int, int, int, int, int, int);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, int);
    // The count of the files of an archive, and a file of it
    int func_02046900(void* archive);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    void func_0205a198(Sprite* sprite);
    void func_0205a234(void*);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205cf78(TextWindow* window, Canvas* canvases, int count);
    void func_020728ac(BinTextTable* table, SafeAllocator* allocator, void* file, unsigned int size, int, int, int);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    void func_020727d8(BinTextTable* table);
    const char* func_02072a68(BinTextTable* table, short id);
    void func_02094ab0();
    int func_02098f20(int year, int month, int day);
    void func_020ac460(void*);
    void func_020dfc40(TextTable* texts);
    const char* func_020e0434(TextTable* texts, short id);

    void func_ov003_0215e6d8(void*);
    void func_ov003_0215efb8(void*);
    int func_ov017_021959b4();
    GameResources* func_0200fb8c(GameState* gameState);
    int func_020100a8(GameState* gameState);
    int func_0201079c(GameState* gameState);
    int func_0201248c(void* pad, int buttons);
    void func_0203b4a0(GameResources* resources, int);
    void func_0203b4b0(GameResources* resources, int);
    // The functions that write the control codes of a text
    void func_02041a28(char* text, int x);
    void func_02041a90(char* text, int x, int y);
    void func_02041b00(char* text, int);
    void func_02041b34(char* text, int, int);
    void func_02041b70(char* text, int item, const char* itemText);
    void func_02041c08(char* text, int, int, int, int, int);
    void func_02041cf4(char* text, int, int, int, int);
    void func_02041d48(char* text, int, int, int, int);
    void func_02041d9c(char* text, int);
    void func_02041dd0(char* text, int);
    void func_02041e70(char* text, int color);
    void func_02041ea4(char* text, int);
    void func_02041fac(char* text, const char* line, int);
    void func_02042058(char* text, const char* append);
    // Returns the width of a text
    int func_020420e8(const char* text, int large);
    void func_02042764(const void* codes, char* text, int);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    int func_020457e0(MessageSystem* messages);
    void func_020465c0(MessageSystem* messages, int, int);
    void func_020465d8(MessageSystem* messages, int, int);
    void func_020465f0(MessageSystem* messages, int, int);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    int func_02046b08(void*);
    void func_0204ecb4(Canvas* canvas, int, int, int, int, int);
    void func_0204f160(Canvas* canvas, int, int);
    void func_0204f3bc(Canvas* canvas, int);
    void func_0204f41c(Canvas* canvas, short x, short y, const char* text, unsigned char size, unsigned char color,
                       short* outX, short* outY, int large);
    void func_0204f914(Canvas* canvas, int color, short left, short top, short right, short bottom);
    void func_0204fbf8(Canvas* canvas);
    void func_0205c508(WindowCursor* cursor, int* first, int* last);
    void func_0205d304(TextWindow* window, char* text, int, int, int, int, int, int);
    int func_0205d794(TextWindow* window);
    Canvas* func_0205d888(TextWindow* window);
    int func_0205d97c(TextWindow* window);
    void func_0205de24(TextWindow* window, int, int);
    void func_0205deb4(TextWindow* window, int, int);
    int func_0205df38(TextWindow* window, int item);
    void func_0205eaa0(void* sound, int effect, int);
    void* func_0205ec34();
    void func_0206819c(const char* text, char* output, int);
    int func_0206dfb0(void*, void*, int);
    void* func_02094a00();
    void func_02094b34(void* music, int, int, int, int);
    int func_02094b4c();
    void func_02099304(ProfileData* profile, const char* name, void* sentences, unsigned int size, char* text,
                       int length, int, const char* title, const char* accolade);
    void* func_020d6c00();
    void func_020dc2bc();
    int func_020d2ff0(const char* text);
    char* strstr(const char* text, const char* search);

    void func_ov003_0215e6f8(void* layout, SafeAllocator* allocator, void* file, unsigned int size);
    void func_ov003_0215ec68(int size, short* width, short* height);
    int func_ov003_0215f000(void* keyboard, int input);
    void func_ov003_0215f41c(void* keyboard, const char*);
    void func_ov023_021e71b4(Unknown_021e7220* windows, SafeAllocator* allocator);
    void func_ov023_021e7340(Unknown_021e7220* windows);
    int func_ov023_021e76c4(Unknown_021e7220* windows);
    void func_ov023_021e7b34(Unknown_021e7220* windows, int);
    void func_ov023_021e7bc4(Unknown_021e7220* windows, int, int);
    void func_ov023_021e7c58(Unknown_021e7220* windows, int, int);
    void func_ov023_021e8270(Unknown_021e7220* windows);
    void func_ov023_021e7220(Unknown_021e7220* windows, int);
    void func_ov023_021e7404(Unknown_021e7220* windows, int input);
    void func_ov023_021e761c(Unknown_021e7220* windows);
    void func_ov023_021e76a8(Unknown_021e7220* windows);
}



// Most of the file's variables, defined here (and the backgrounds' before LoadBackgrounds()) for the original's layout:
// the compiler sorts them by size, and the order of the ones with the same size depends on where they're defined (see
// Decompiling.md). The original aligns sSymbols and sItemWindows to 4, which none of their declarations tried does
// (an attribute on sItemWindows itself changes SetItemWindow()'s code, so it's on a structure)








// The ranges of the titles of each category
struct TitleRange
{
    short start_;
    short end_;
};

// The windows of the items: their item, and their width, height and more in tiles
struct ItemWindow
{
    unsigned char item_;
    unsigned char unk_1;
    unsigned char unk_2;
    signed char width_;
    signed char height_;
    unsigned char unk_5;
    unsigned char unk_6;
};

// The items of the menu that can't be selected again after they're changed
static const unsigned char sMenuItems[5][2] = {{3, 2}, {4, 2}, {5, 2}, {11, 10}, {12, 10}};

// The symbols of the patterns of the forbidden words
static const char sSymbols[15][5] __attribute__((aligned(4))) = {
    ":", "[", "]", "{", "}", "^", "-", ".", "$", "/", "@", "&", ",", "<c/>", "'"};

// What Check() writes for a tag (in .data, before the pool of the strings)
static char sTagCharacter[] = "C";

// The texts of the menu's items after the first
static const short sMenuTexts[] = {3, 4, 5, 6, 12, -1};

// The windows of the items
struct ItemWindowTable
{
    ItemWindow windows_[18];
} __attribute__((aligned(4)));

static const ItemWindowTable sItemWindows = {{
    {1, 12, 11, 28, 15, 10, 16},  {2, 12, 8, 11, 10, 10, 18},   {3, 12, 8, 17, 18, 10, 16},
    {4, 12, 10, 15, 10, 10, 16},  {5, 12, 6, 15, 19, 10, 16},   {6, 12, 8, 6, 5, 10, 16},
    {7, 30, 16, 12, 6, 1, 1},     {8, 30, 16, 9, 6, 1, 1},      {9, 30, 16, 9, 6, 1, 1},
    {10, 12, 8, 10, 6, 10, 18},   {11, 12, 6, 16, 20, 10, 14},  {12, 12, 8, 32, 17, 10, 16},
    {13, 12, 12, 15, 18, 10, 16}, {14, 0, 0, 30, 18, 16, 16},   {16, 16, 2, 8, 2, 10, 16},
    {17, 20, 2, 8, 2, 10, 16},    {18, 1, 1, 32, 9, 1, 1},      {0xff, 1, 1, 1, 1, 1, 1},
}};

// The ranges of the titles of each category
static const TitleRange sTitleRanges[] = {{0x136, 0x200}, {0xc8, 0x12c}, {0, 0x64}, {0x12c, 0x12d}};

// The cursor of a window's items (like GetProfile(), the original computes its address apart from its fields')
static inline WindowCursor* GetCursor(TextWindow* window)
{
    return (WindowCursor*)((char*)window + 0x54);
}

// The frame of a window (see GetCursor())
static inline WindowFrame* GetFrame(TextWindow* window)
{
    return (WindowFrame*)((char*)window + 4);
}

// The editor's window (see GetCursor())
static inline TextWindow* GetWindow(ProfileEditor* editor)
{
    return (TextWindow*)((char*)editor + 0xac);
}

// Shows or hides a canvas of the window
void ProfileEditor::SetCanvasColors(int canvas, int color, int shadow)
{
    Canvas* found = func_0205d81c(&window_, canvas);
    if (found == 0)
    {
        found = func_0205e00c(&window_, canvas);
        if (found == 0)
            return;
    }
    if (shadow != 0)
    {
        func_02050400(found, 1);
        func_0205042c(found, color);
        func_02050440(found, shadow);
    }
    else
    {
        func_02050400(found, 0);
        func_0205042c(found, 0);
        func_02050440(found, 0);
    }
}


// The index of the profile's title in a category, or 0
static int GetTitleIndex(int category)
{
    int title = GetProfile(GameState::GetInstance())->title_;
    if (sTitleRanges[category].start_ <= title && title < sTitleRanges[category].end_)
        return title - sTitleRanges[category].start_;
    return 0;
}

// The index of the profile's accolade in a list, or -1
static int FindAccolade(const unsigned short* accolades, int count)
{
    int accolade = GetProfile(GameState::GetInstance())->accolade_;
    for (int i = 0; i < count; i++)
    {
        if (accolade == accolades[i])
            return i;
    }
    return -1;
}

void ProfileEditor::Initialize()
{
    unk_0 = 0;
    unk_4 = 0;
    unk_18 = 0;
    unk_19 = 0;
    func_02074af4(unk_8);
    planes_ = (DISPCNT & 0x1f00) >> 8;
    DISPCNT = (DISPCNT & ~0x1f00) | 0x100;
    finished_ = 0;
    allocators_[0].ResetAllocatorPointer();
    allocators_[1].ResetAllocatorPointer();
    allocators_[2].ResetAllocatorPointer();
    allocators_[3].ResetAllocatorPointer();
    allocators_[5].ResetAllocatorPointer();
    allocators_[6].ResetAllocatorPointer();
    func_ov023_021e7220(&windows_, 2);
    func_020727d8(&strings_);
    func_020dfc40(&texts_);
    renderer_ = 0;
    sprites_ = 0;
    unk_1360 = 0;
    renderer2_ = 0;
    sprites2_ = 0;
    func_0205cfd4(&window_);
    for (int i = 0; i < 3; i++)
        func_0204af64(&backgrounds_[i]);
    for (int i = 0; i < 13; i++)
        func_0204c684(&canvases_[i]);
    step_ = 0;
    state_ = 0;
    text_ = 0;
    pixels_ = 0;
    unk_1378 = 0;
    result_ = 0;
    unk_13a0 = 0;
    unk_1398 = 0;
    for (int i = 0; i < 6; i++)
        tasks_[i] = -1;
    unk_13a8 = -1;
    unk_13a9 = 0;
    unk_13aa = 0;
    unk_13ab = 0;
    unk_13ac = 0;
    name_ = 0;
    unk_13b4 = 0;
    unk_13b8 = 0;
    unk_13bc = 0;
    unk_13c0 = 0;
    unk_13c4_0 = 0;
    unk_13c4_5 = 0;
    unk_13c8 = 0;
    unk_13cc = 0;
    message_ = 0;
    selection_ = 0;
    design_ = 0;
    unk_13f8 = 0;
    year_ = 0;
    month_ = 0;
    day_ = 0;
    selections_[0] = -1;
    selections_[1] = -1;
    selections_[2] = -1;
    selections_[3] = -1;
    selections_[4] = -1;
    selections_[5] = -1;
    memset(accoladeText_, 0, sizeof(accoladeText_));
    memset(titleText_, 0, sizeof(titleText_));
    checker_.Initialize();
    unk_14bd = 0;
}


void ForbiddenWordChecker::Initialize()
{
    memset(&file_, 0, sizeof(file_));
    unk_24 = 0;
    unk_28 = 0;
    unsigned char* symbol = symbols_;
    for (int i = 0; i < 15; i++)
        *symbol++ = func_020424e4(sSymbols[i], 1);
}

// Initializes the profile the first time, and gets the texts of its title and accolade
// NONMATCHING: The original reads the sex of the protagonist through a pointer to its details, add r0, r4, #0x88 and
// [r0, #0x414], and the compiler folds it into [r4, #0x49c] with every accessor tried (88.6 %)
#ifdef NONMATCHING
void ProfileEditor::LoadProfile()
{
    GameState* gameState = GameState::GetInstance();
    ProfileData* profile = GetProfile(gameState);
    func_0202ae18();
    PartyMemberData* data = 0;
    GameObject* protagonist = gameState->GetProtagonist();
    if (protagonist != 0)
        data = func_02053c6c(protagonist);
    if (data == 0)
        return;

    name_ = data->name_;
    if (!profile->initialized_)
    {
        profile->year_ = 2000;
        profile->month_ = 1;
        profile->day_ = 1;
        profile->showBirthday_ = 1;
        profile->female_ = data->details_.appearance_.female_;
        profile->unk_0_21 = data->details_.appearance_.female_;
        profile->title_ = 300;
        int accolade = 0x50dc;
        if (protagonist->partyData_->details_.appearance_.female_ == 1)
            accolade += 0x32;
        profile->accolade_ = accolade + protagonist->partyData_->vocation_ - 0x4e20;
        memset(profile->unk_8, 0, sizeof(profile->unk_8));
        profile->initialized_ = 1;
    }
    profile->unk_4_0 = func_02098f20(profile->year_, profile->month_, profile->day_);
    const char* title = func_02072a68(&strings_, profile->title_ + 10000);
    memcpy(titleText_, title, strlen(title));
    int accolade = profile->accolade_;
    const char* text;
    if (accolade < 700)
        text = func_020e0434(&texts_, accolade);
    else
        text = func_02072a68(&strings_, accolade + 20000);
    memcpy(accoladeText_, text, strlen(text));
    ResetAccoladeTexts();
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState14GetProtagonistEv(); // GameState::GetProtagonist
}

asm void ProfileEditor::LoadProfile()
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r7, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    add r0, r4, #0x29c
    add r6, r0, #0x5400
    bl func_0202ae18
    mov r0, r4
    mov r4, #0x0
    bl _ZN9GameState14GetProtagonistEv
    movs r5, r0
    beq @L0218468c
    bl func_02053c6c
    mov r4, r0
@L0218468c:
    cmp r4, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
    add r1, r4, #0x3c
    add r0, r7, #0x1000
    str r1, [r0, #0x3b0]
    ldr r1, [r6, #0x0]
    mov r0, r1, lsl #0x5
    movs r0, r0, lsr #0x1f
    bne @L0218478c
    mov r0, #0x1000
    rsb r0, r0, #0x0
    and r0, r1, r0
    orr r3, r0, #0x7d0
    bic r0, r3, #0xf000
    orr r2, r0, #0x1000
    bic r0, r2, #0x1f0000
    orr r1, r0, #0x10000
    bic r0, r1, #0x80000000
    orr r2, r0, #0x80000000
    str r2, [r6, #0x0]
    add r0, r4, #0x88
    ldrb r1, [r0, #0x414]
    bic r2, r2, #0x2000000
    mov r1, r1, lsl #0x1f
    mov r1, r1, lsr #0x1f
    mov r1, r1, lsl #0x1f
    orr r1, r2, r1, lsr #0x6
    str r1, [r6, #0x0]
    ldrb r0, [r0, #0x414]
    bic r1, r1, #0x1e00000
    ldr r2, =0x50dc
    mov r0, r0, lsl #0x1f
    mov r0, r0, lsr #0x1f
    mov r0, r0, lsl #0x1c
    orr r0, r1, r0, lsr #0x7
    str r0, [r6, #0x0]
    ldr r1, [r6, #0x4]
    ldr r0, =0xfff801ff
    and r0, r1, r0
    orr r0, r0, #0x25800
    str r0, [r6, #0x4]
    ldr r1, [r5, #0x150]
    ldrb r0, [r1, #0x49c]
    ldr r1, [r1, #0x950]
    mov r0, r0, lsl #0x1f
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    addeq r2, r2, #0x32
    add r1, r2, r1
    ldr r0, =0xffffb1e0
    ldr r2, [r6, #0x4]
    add r1, r1, r0
    ldr r0, =0xc007ffff
    mov r1, r1, lsl #0x15
    and r0, r2, r0
    orr r0, r0, r1, lsr #0x2
    str r0, [r6, #0x4]
    add r0, r6, #0x8
    mov r1, #0x0
    mov r2, #0x74
    bl memset
    ldr r0, [r6, #0x0]
    orr r0, r0, #0x4000000
    str r0, [r6, #0x0]
@L0218478c:
    ldr r0, [r6, #0x0]
    mov r1, r0, lsl #0x10
    mov r2, r0, lsl #0xb
    mov r3, r0, lsl #0x14
    mov r0, r3, lsr #0x14
    mov r1, r1, lsr #0x1c
    mov r2, r2, lsr #0x1b
    bl func_02098f20
    mov r1, #0x200
    rsb r1, r1, #0x0
    ldr r2, [r6, #0x4]
    and r0, r0, r1, lsr #0x17
    and r1, r2, r1
    orr r2, r1, r0
    mov r0, r2, lsl #0xd
    mov r0, r0, asr #0x16
    add r0, r0, #0x710
    add r1, r0, #0x2000
    add r0, r7, #0x33c
    mov r1, r1, lsl #0x10
    add r0, r0, #0x1000
    mov r1, r1, asr #0x10
    str r2, [r6, #0x4]
    bl func_02072a68
    mov r4, r0
    bl strlen
    mov r2, r0
    mov r1, r4
    add r0, r7, #0x1440
    bl memcpy
    ldr r0, [r6, #0x4]
    mov r0, r0, lsl #0x2
    mov r1, r0, asr #0x15
    cmp r1, #0x2bc
    bge @L02184830
    add r0, r7, #0x344
    mov r1, r1, lsl #0x10
    add r0, r0, #0x1000
    mov r1, r1, asr #0x10
    bl func_020e0434
    b @L0218484c
@L02184830:
    add r0, r1, #0xe20
    add r1, r0, #0x4000
    add r0, r7, #0x33c
    mov r1, r1, lsl #0x10
    add r0, r0, #0x1000
    mov r1, r1, asr #0x10
    bl func_02072a68
@L0218484c:
    mov r4, r0
    mov r0, r4
    bl strlen
    mov r2, r0
    mov r1, r4
    add r0, r7, #0x1400
    bl memcpy
    mov r0, r7
    bl _ZN13ProfileEditor18ResetAccoladeTextsEv
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

void ProfileEditor::Load(SafeAllocator* allocator)
{
    if (allocator == 0)
        return;

    unk_0 = allocator->Allocate(0x28);
    if (unk_0 != 0)
        func_ov003_0215efb8(unk_0);
    unk_4 = allocator->Allocate(0x10);
    if (unk_4 != 0)
        func_ov003_0215e6d8(unk_4);
    allocators_[0].CreateTypeA(allocator->Allocate(0x14c00), 0x14c00);
    allocators_[1].CreateTypeA(allocator->Allocate(0x2400), 0x2400);
    allocators_[2].CreateTypeA(allocator->Allocate(0x9400), 0x9400);
    allocators_[3].CreateTypeA(allocator->Allocate(0x800), 0x800);
    allocators_[4].CreateTypeA(allocator->Allocate(0x1800), 0x1800);
    allocators_[5].CreateTypeA(allocator->Allocate(0x5400), 0x5400);
    allocators_[6].CreateTypeA(allocator->Allocate(0x400), 0x400);
    sprites_ = (Sprite*)allocator->Allocate(0x2f8);
    renderer_ = (SpriteRenderer*)allocator->Allocate(0x54);
    unk_1360 = allocator->Allocate(8);
    sprites2_ = (Sprite*)allocator->Allocate(0x78);
    renderer2_ = (SpriteRenderer*)allocator->Allocate(0x54);
    unk_13ac = allocator->Allocate(0x72);
    unk_13b4 = allocator->Allocate(0x3c00);
    unk_13bc = allocator->Allocate(0xf2);
    memset(unk_13bc, 0, 0xf2);
    unk_13c0 = (signed char*)allocator->Allocate(0x12);
    memset(unk_13c0, 0, 0x12);
    unk_13c8 = (unsigned short*)allocator->Allocate(0x38c);
    memset(unk_13c8, 0, 0x38c);
    unk_13cc = (unsigned int*)allocator->Allocate(0x3c);
    memset(unk_13cc, 0, 0x3c);
    func_020ac460(unk_13cc);
    message_ = (char*)allocator->Allocate(0x400);
    memset(message_, 0, 0x400);
}
int ProfileEditor::Update(int input)
{
    unk_13a4 = input;
    func_ov023_021e7404(&windows_, input);
    unk_1398 = func_0205d0e0(&window_, input);
    void (ProfileEditor::*states[])() = {
        &ProfileEditor::State_Load,     &ProfileEditor::State_Menu,      &ProfileEditor::State_TitleCategory,
        &ProfileEditor::State_Title0,   &ProfileEditor::State_Title1,    &ProfileEditor::State_Title2,
        &ProfileEditor::State_06,       &ProfileEditor::State_07,        &ProfileEditor::State_08,
        &ProfileEditor::State_09,       &ProfileEditor::State_0a,        &ProfileEditor::State_0b,
        &ProfileEditor::State_0c,       &ProfileEditor::State_0d,        &ProfileEditor::State_0e,
        &ProfileEditor::State_Finish,   0,
    };
    if (states[state_] != 0)
        (this->*states[state_])();
    UpdateText();

    MessageSystem* messages = func_020421a0();
    GameState* gameState = GameState::GetInstance();
    if ((state_ != 0 && state_ < 15) || (state_ == 0 && messages->busy_ != 0))
    {
        if (messages->busy_ == 0 && func_02012444(data_02114e30, 0x800))
        {
            unk_14bd = ++unk_14bd & 1;
            windows_.unk_60c = unk_14bd;
            if (state_ == 13 && step_ == 3)
                RefreshCard(0, GetProfile(gameState)->female_ + design_ * 2, 1);
            else
                RefreshCard(0, -1, 1);
        }

        if (func_ov017_021959b4())
        {
            if (state_ == 14 && step_ == 4 && *message_ != 0)
            {
                GameState::GetInstance();
                BackgroundLoader::AddLockGlobal();
                BackgroundLoader::FreeAllocationsGlobal();
                checker_.Initialize();
                int forbidden = checker_.Check(message_);
                BackgroundLoader::RemoveLockGlobal();
                if (forbidden)
                {
                    func_0205def8(&window_, 0, 14);
                    step_ = 10;
                    return 0;
                }
            }

            finished_ = 1;
            unk_13a0 = 0;
            selection_ = 0;
            func_0205d6a0(&window_, 1);
            state_ = 15;
            step_ = 0;
            if (messages->busy_ != 0)
                func_02043204(messages);

            BackgroundLoader* loader = BackgroundLoader::GetInstance();
            for (int i = 0; i < 6; i++)
            {
                if (tasks_[i] > -1)
                {
                    loader->RemoveTask(tasks_[i]);
                    tasks_[i] = -1;
                }
            }
        }
    }
    return result_;
}

static int ResolvePattern(ForbiddenWordFile* file, ForbiddenWordPattern* pattern);


// Reads the loaded file of the patterns, and prepares them the first time
inline void ForbiddenWordChecker::LoadFile(void* data, int extra,
                                           int (*prepare)(ForbiddenWordFile* file, ForbiddenWordPattern* pattern))
{
    memset(&file_, 0, sizeof(file_));
    if (data != 0)
    {
        memcpy(&file_.header_, data, 4);
        file_.patterns_ = (ForbiddenWordPattern*)((char*)data + ((3 + 4) & ~3));
        file_.texts_ = (char*)data + ((3 + 4) & ~3) + (file_.header_ & 0xfff) * ((3 + 0x20) & ~3) + 0;
        if (!(file_.header_ >> 31))
        {
            ForbiddenWordPattern* pattern = file_.patterns_;
            unsigned int count;
            if (pattern != 0 && (count = file_.header_ & 0xfff) != 0 && prepare != 0)
            {
                for (int i = 0; i < count; i++)
                {
                    prepare(&file_, pattern);
                    pattern++;
                }
            }
            file_.header_ = (file_.header_ & ~0x80000000) | 0x80000000;
            *(unsigned int*)data = (*(unsigned int*)data & ~0x80000000) | 0x80000000;
        }
    }
    unk_24 = 0;
    unk_28 = 0;
    if (extra != 0)
    {
        unk_24 = (char*)data + extra;
        unk_28 = extra;
    }
}

// Whether a text has a forbidden word: 1 if it has
// NONMATCHING: The compiler inlines the loading of the file and assigns the registers and the stack in another way, and
// compiles the loop over the characters in another order (objdiff counts 0 %, the sizes differ)
#ifdef NONMATCHING
#pragma always_inline on
int ForbiddenWordChecker::Check(const char* text)
{
    unsigned int size = 0;
    LoadFileIntoMemory(data_020f285c, data_0211e33c, &size);
    LoadFile(data_0211e33c, 0, ResolvePattern);

    ForbiddenWordRange words[30];
    char converted[0x200];
    char codes[0x80];
    __clear(words, sizeof(words));
    __clear(converted, sizeof(converted));
    __clear(codes, sizeof(codes));
    char* output = converted;
    int dollar = symbols_[8];
    int slash = symbols_[9];
    int at = symbols_[10];
    int ampersand = symbols_[11];
    unsigned char quote = symbols_[14];
    unsigned char tag = symbols_[13];
    while (*text != 0)
    {
        signed char code = func_020424e4(text, 1);
        CharacterInfo* info = (CharacterInfo*)func_020425b4(code, 1);
        if (info != 0 &&
            ((code >= 8 && code <= 0x45) || code == 0x4d || code == 0x53 || (code >= 0x78 && code <= 0xa9) ||
             (code == dollar || code == at || code == ampersand || code == 0x6b || code == quote)))
        {
            int length = info->length_;
            if (code == 0x6b)
                info = (CharacterInfo*)func_020425b4(slash, 1);
            char buffer[0xc];
            __clear(buffer, sizeof(buffer));
            const char* characters = info->text_;
            int size = info->length_;
            if (info->uppercase_)
            {
                ToUpper(characters, buffer);
                characters = buffer;
            }
            if (code >= 0x78 && code <= 0xa9)
            {
                signed char second = characters[1];
                if (!(second >= 'A' && second <= 'Z' || second >= 'a' && second <= 'z') || second == 's')
                {
                    signed char third = characters[2];
                    if (third >= 'a' && third <= 'z')
                        third -= 0x20;
                    memset(buffer, 0, sizeof(buffer));
                    buffer[0] = third;
                    characters = buffer;
                    size = 1;
                }
            }
            memcpy(output, characters, size);
            text += length;
            output += size;
        }
        else if (code == tag)
        {
            int length = info->length_;
            memcpy(output, sTagCharacter, 1);
            text += length;
            output++;
        }
        else
        {
            int length = 1;
            char character;
            if (info != 0)
            {
                length = info->length_;
                character = ',';
            }
            else
            {
                character = ' ';
            }
            *output = character;
            text += length;
            output++;
        }
    }

    func_020426bc(converted, codes, 1);
    ForbiddenWordRange* word = words;
    unsigned char separator = symbols_[12];
    const unsigned char* code = (const unsigned char*)codes;
    int column = 0;
    short position = 0;
    int count = 0;
    while (true)
    {
        unsigned int current = *code;
        if (word->active_)
        {
            if (current == 0 || current == 0xff || current == separator)
            {
                count++;
                word->length_ = position - word->start_;
                word->lineEnd_ = current == 0xff ? 1 : 0;
                word->active_ = 0;
                word++;
            }
        }
        else
        {
            if (current != 0 && current < 0xff && current != separator)
            {
                word->start_ = position;
                word->active_ = 1;
            }
            if (current == separator && count != 0)
                words[count - 1].lineEnd_ = 0;
        }
        if (word->active_ && column == 0x12)
        {
            count++;
            word->length_ = position - word->start_ + 1;
            word->lineEnd_ = 1;
            word++;
        }
        if (current == 0)
            break;
        column++;
        code++;
        position++;
        if (column == 0x13)
            column = 0;
    }

    word = words;
    for (int i = 0; i < count - 1; i++, word++)
    {
        int j = word->start_ + word->length_;
        word->lineEnd_ = 1;
        const unsigned char* character = (const unsigned char*)&codes[j];
        for (; j < word[1].start_; j++, character++)
        {
            if (symbols_[12] == *character)
            {
                word->lineEnd_ = 0;
                break;
            }
        }
    }

    for (int i = 0; i < 0x80; i++)
    {
        if ((signed char)symbols_[12] == codes[i])
            codes[i] = -1;
    }

    unsigned int patternCount = file_.header_ & 0xfff;
    for (int i = 0; i < patternCount; i = (short)(i + 1))
    {
        ForbiddenWordPattern* pattern = file_.patterns_ + i;
        ForbiddenWordRange* first = words;
        char patternCodes[5][0x40];
        __clear(patternCodes, sizeof(patternCodes));
        for (int j = 0; j < pattern->count_; j++)
        {
            func_020426bc(pattern->words_[j], patternCodes[j], 1);
            pattern->words_[j] = patternCodes[j];
        }

        int positions = count - pattern->count_ + 1;
        for (int j = 0; j < positions; j++, first++)
        {
            int found;
            ForbiddenWordRange* range = first;
            int k = 0;
            int wordCount = pattern->count_;
            int last = pattern->count_ - 1;
            while (true)
            {
                if (k >= wordCount)
                {
                    found = 1;
                    break;
                }
                if (k < last && !range->lineEnd_)
                {
                    found = 0;
                    break;
                }

                signed char length = pattern->lengths_[k];
                short rangeLength = range->length_;
                const char* patternWord = pattern->words_[k];
                int positions2 = rangeLength - length + 1;
                int matched;
                switch (pattern->types_[k])
                {
                    case 0:
                        matched = length == rangeLength && FindText(patternWord, &codes[range->start_], length, 1);
                        break;
                    case 3:
                        matched = rangeLength >= length && FindText(patternWord, &codes[range->start_], length, 1);
                        break;
                    case 2:
                        matched = rangeLength >= length &&
                                  FindText(patternWord, &codes[range->start_ + range->length_ - length], length, 1);
                        break;
                    case 1:
                        matched = rangeLength >= length && FindText(patternWord, &codes[range->start_], length, positions2);
                        break;
                    case 4:
                        matched = length == rangeLength && Match(patternWord, &codes[range->start_], length, 1);
                        break;
                    case 7:
                        matched = rangeLength >= length && Match(patternWord, &codes[range->start_], length, 1);
                        break;
                    case 6:
                        matched = rangeLength >= length &&
                                  Match(patternWord, &codes[range->start_ + range->length_ - length], length, 1);
                        break;
                    case 5:
                        matched = rangeLength >= length && Match(patternWord, &codes[range->start_], length, positions2);
                        break;
                    default:
                        matched = 1;
                        break;
                }
                if (!matched)
                {
                    found = 0;
                    break;
                }
                k++;
                range++;
            }
            if (found)
                return 1;
        }
    }
    return 0;
}

#pragma always_inline reset
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN20ForbiddenWordChecker5MatchEPKcS1_ii(); // ForbiddenWordChecker::Match
    void _ZN20ForbiddenWordChecker7ToUpperEPKcPc(); // ForbiddenWordChecker::ToUpper
    void _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii(); // ForbiddenWordChecker::FindText
}

asm int ForbiddenWordChecker::Check(const char* text)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xf8
    sub sp, sp, #0x400
    ldr r2, =data_020f285c
    mov r9, r0
    mov r5, r1
    ldr r0, [r2, #0x0]
    mov r4, #0x0
    ldr r1, =data_0211e33c
    add r2, sp, #0x28
    str r4, [sp, #0x28]
    bl LoadFileIntoMemory
    add r0, r9, #0x18
    mov r1, r4
    mov r2, #0xc
    bl memset
    ldr r1, =data_0211e33c
    cmp r1, #0x0
    beq @L02184e94
    add r0, r9, #0x18
    mov r2, #0x4
    bl memcpy
    mov r0, #0x3
    add r1, r0, #0x4
    mvn r6, #0x3
    add r2, r0, #0x20
    ldr r0, =data_0211e33c
    and r1, r6, r1
    add r3, r0, r1
    str r3, [r9, #0x1c]
    ldr r3, [r9, #0x18]
    and r2, r6, r2
    mov r3, r3, lsl #0x14
    mov r3, r3, lsr #0x14
    mul r2, r3, r2
    add r2, r2, #0x0
    add r1, r1, r2
    add r0, r0, r1
    str r0, [r9, #0x20]
    ldr r0, [r9, #0x18]
    movs r0, r0, lsr #0x1f
    bne @L02184e94
    ldr r6, [r9, #0x1c]
    cmp r6, #0x0
    beq @L02184e70
    ldr r0, [r9, #0x18]
    mov r0, r0, lsl #0x14
    movs r7, r0, lsr #0x14
    ldrne r0, =ResolvePattern
    cmpne r0, #0x0
    beq @L02184e70
    mov r8, r4
    b @L02184e68
@L02184e54:
    mov r1, r6
    add r0, r9, #0x18
    bl ResolvePattern
    add r8, r8, #0x1
    add r6, r6, #0x20
@L02184e68:
    cmp r8, r7
    blt @L02184e54
@L02184e70:
    ldr r0, [r9, #0x18]
    ldr r1, =data_0211e33c
    bic r0, r0, #0x80000000
    orr r0, r0, #0x80000000
    str r0, [r9, #0x18]
    ldr r0, [r1, #0x0]
    bic r0, r0, #0x80000000
    orr r0, r0, #0x80000000
    str r0, [r1, #0x0]
@L02184e94:
    mov r0, #0x0
    str r0, [r9, #0x24]
    strh r0, [r9, #0x28]
    cmp r4, #0x0
    ldrne r0, =data_0211e33c
    mov r1, #0xb4
    addne r0, r0, r4
    strne r0, [r9, #0x24]
    add r0, sp, #0x84
    strneh r4, [r9, #0x28]
    bl __clear
    add r0, sp, #0x138
    mov r1, #0x200
    bl __clear
    add r0, sp, #0x338
    mov r1, #0x80
    bl __clear
    ldrb r0, [r9, #0x32]
    add r4, sp, #0x138
    str r0, [sp, #0x1c]
    ldrb r0, [r9, #0x33]
    str r0, [sp, #0x18]
    ldrb r0, [r9, #0x34]
    str r0, [sp, #0x14]
    ldrb r0, [r9, #0x35]
    str r0, [sp, #0x10]
    ldrb r10, [r9, #0x38]
    ldrb r6, [r9, #0x37]
@L02184f04:
    ldrsb r0, [r5, #0x0]
    cmp r0, #0x0
    beq @L021850bc
    mov r0, r5
    mov r1, #0x1
    bl func_020424e4
    mov r1, #0x1
    mov r8, r0
    bl func_020425b4
    movs r7, r0
    beq @L02185090
    cmp r8, #0x8
    blt @L02184f40
    cmp r8, #0x45
    ble @L02184f80
@L02184f40:
    cmp r8, #0x4d
    cmpne r8, #0x53
    beq @L02184f80
    cmp r8, #0x78
    blt @L02184f5c
    cmp r8, #0xa9
    ble @L02184f80
@L02184f5c:
    ldr r0, [sp, #0x1c]
    cmp r8, r0
    ldrne r0, [sp, #0x14]
    cmpne r8, r0
    ldrne r0, [sp, #0x10]
    cmpne r8, r0
    cmpne r8, #0x6b
    cmpne r8, r10
    bne @L02185064
@L02184f80:
    cmp r8, #0x6b
    ldrsb r0, [r7, #0x5]
    mov r11, r0, lsl #0x1a
    bne @L02184fa0
    ldr r0, [sp, #0x18]
    mov r1, #0x1
    bl func_020425b4
    mov r7, r0
@L02184fa0:
    add r0, sp, #0x78
    mov r1, #0xc
    bl __clear
    ldrsb r0, [r7, #0x5]
    ldr r1, [r7, #0x0]
    mov r2, r0, lsl #0x1a
    mov r0, r0, lsl #0x18
    mov r7, r2, asr #0x1a
    movs r0, r0, asr #0x1f
    beq @L02184fd8
    mov r0, r9
    add r2, sp, #0x78
    bl _ZN20ForbiddenWordChecker7ToUpperEPKcPc
    add r1, sp, #0x78
@L02184fd8:
    cmp r8, #0x78
    blt @L0218504c
    cmp r8, #0xa9
    bgt @L0218504c
    ldrsb r8, [r1, #0x1]
    cmp r8, #0x41
    blt @L02184ffc
    cmp r8, #0x5a
    ble @L0218500c
@L02184ffc:
    cmp r8, #0x61
    blt @L02185014
    cmp r8, #0x7a
    bgt @L02185014
@L0218500c:
    cmp r8, #0x73
    bne @L0218504c
@L02185014:
    ldrsb r8, [r1, #0x2]
    cmp r8, #0x61
    blt @L02185030
    cmp r8, #0x7a
    suble r0, r8, #0x20
    movle r0, r0, lsl #0x18
    movle r8, r0, asr #0x18
@L02185030:
    add r0, sp, #0x78
    mov r1, #0x0
    mov r2, #0xc
    bl memset
    strb r8, [sp, #0x78]
    add r1, sp, #0x78
    mov r7, #0x1
@L0218504c:
    mov r0, r4
    mov r2, r7
    bl memcpy
    add r5, r5, r11, asr #0x1a
    add r4, r4, r7
    b @L02184f04
@L02185064:
    cmp r8, r6
    bne @L02185090
    ldrsb r2, [r7, #0x5]
    ldr r1, =sTagCharacter
    mov r0, r4
    mov r7, r2, lsl #0x1a
    mov r2, #0x1
    bl memcpy
    add r5, r5, r7, asr #0x1a
    add r4, r4, #0x1
    b @L02184f04
@L02185090:
    cmp r7, #0x0
    ldrnesb r0, [r7, #0x5]
    mov r1, #0x1
    movne r0, r0, lsl #0x1a
    movne r1, r0, asr #0x1a
    movne r0, #0x2c
    moveq r0, #0x20
    strb r0, [r4, #0x0]
    add r5, r5, r1
    add r4, r4, #0x1
    b @L02184f04
@L021850bc:
    add r0, sp, #0x138
    add r1, sp, #0x338
    mov r2, #0x1
    bl func_020426bc
    mov r4, #0x0
    add r7, sp, #0x84
    ldrb r3, [r9, #0x36]
    add r6, sp, #0x338
    mov r5, r4
    mov r8, r4
    mov r0, r7
    mov r12, #0x1
    mov lr, r4
    mov r2, r4
@L021850f4:
    ldrb r10, [r6, #0x0]
    ldrb r1, [r7, #0x5]
    cmp r1, #0x0
    beq @L02185140
    cmp r10, #0x0
    cmpne r10, #0xff
    cmpne r10, r3
    bne @L02185178
    ldrsh r1, [r7, #0x0]
    cmp r10, #0xff
    add r8, r8, #0x1
    sub r1, r5, r1
    strh r1, [r7, #0x2]
    moveq r1, #0x1
    movne r1, #0x0
    strb r1, [r7, #0x4]
    strb r2, [r7, #0x5]
    add r7, r7, #0x6
    b @L02185178
@L02185140:
    cmp r10, #0x0
    beq @L0218515c
    cmp r10, #0xff
    bhs @L0218515c
    cmp r10, r3
    strneh r5, [r7, #0x0]
    strneb r12, [r7, #0x5]
@L0218515c:
    cmp r10, r3
    bne @L02185178
    cmp r8, #0x0
    subne r1, r8, #0x1
    movne r11, #0x6
    mlane r11, r1, r11, r0
    strneb lr, [r11, #0x4]
@L02185178:
    ldrb r1, [r7, #0x5]
    cmp r1, #0x0
    beq @L021851ac
    cmp r4, #0x12
    bne @L021851ac
    ldrsh r1, [r7, #0x0]
    add r8, r8, #0x1
    sub r1, r5, r1
    add r1, r1, #0x1
    strh r1, [r7, #0x2]
    mov r1, #0x1
    strb r1, [r7, #0x4]
    add r7, r7, #0x6
@L021851ac:
    cmp r10, #0x0
    beq @L021851cc
    add r4, r4, #0x1
    cmp r4, #0x13
    add r6, r6, #0x1
    add r5, r5, #0x1
    moveq r4, #0x0
    b @L021850f4
@L021851cc:
    mov r7, #0x0
    ldrb r11, [r9, #0x36]
    add r10, sp, #0x84
    sub r0, r8, #0x1
    mov r3, #0x1
    add r2, sp, #0x338
    mov r12, r7
    b @L02185230
@L021851ec:
    ldrsh r4, [r10, #0x0]
    ldrsh r1, [r10, #0x2]
    ldrsh r6, [r10, #0x6]
    add r4, r4, r1
    strb r3, [r10, #0x4]
    add r5, r2, r4
    b @L02185220
@L02185208:
    ldrb r1, [r5, #0x0]
    cmp r11, r1
    streqb r12, [r10, #0x4]
    beq @L02185228
    add r4, r4, #0x1
    add r5, r5, #0x1
@L02185220:
    cmp r4, r6
    blt @L02185208
@L02185228:
    add r7, r7, #0x1
    add r10, r10, #0x6
@L02185230:
    cmp r7, r0
    blt @L021851ec
    ldrsb r4, [r9, #0x36]
    mov r3, #0x0
    mvn r0, #0x0
    add r2, sp, #0x338
    b @L0218525c
@L0218524c:
    ldrsb r1, [r2, r3]
    cmp r4, r1
    streqb r0, [r2, r3]
    add r3, r3, #0x1
@L0218525c:
    cmp r3, #0x80
    blt @L0218524c
    ldr r0, [r9, #0x18]
    mov r7, #0x0
    mov r0, r0, lsl #0x14
    mov r0, r0, lsr #0x14
    str r0, [sp, #0x4]
    b @L02185560
@L0218527c:
    ldr r2, [r9, #0x1c]
    add r0, sp, #0x3b8
    add r6, r2, r7, lsl #0x5
    add r2, sp, #0x84
    mov r1, #0x140
    str r2, [sp, #0x8]
    bl __clear
    mov r5, #0x0
    add r4, sp, #0x3b8
    mov r10, #0x1
    b @L021852c4
@L021852a8:
    ldr r0, [r6, r5, lsl #0x2]
    mov r2, r10
    add r1, r4, r5, lsl #0x6
    bl func_020426bc
    add r0, r4, r5, lsl #0x6
    str r0, [r6, r5, lsl #0x2]
    add r5, r5, #0x1
@L021852c4:
    ldrb r0, [r6, #0x1e]
    cmp r5, r0
    blt @L021852a8
    sub r0, r8, r0
    add r0, r0, #0x1
    str r0, [sp, #0xc]
    mov r11, #0x0
    add r10, sp, #0x338
    b @L02185548
@L021852e8:
    ldrb r0, [r6, #0x1e]
    ldr r5, [sp, #0x8]
    mov r4, #0x0
    str r0, [sp, #0x20]
    sub r0, r0, #0x1
    str r0, [sp, #0x24]
    b @L0218551c
@L02185304:
    ldr r0, [sp, #0x24]
    cmp r4, r0
    bge @L02185320
    ldrb r0, [r5, #0x4]
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L0218552c
@L02185320:
    add r0, r6, r4
    ldrb r12, [r0, #0x19]
    ldrsb r3, [r0, #0x14]
    ldrsh r0, [r5, #0x2]
    ldr r1, [r6, r4, lsl #0x2]
    cmp r12, #0x7
    sub r2, r0, r3
    add r2, r2, #0x1
    addls pc, pc, r12, lsl #0x2
    b @L02185514
@L02185348:
    b @L02185368
    b @L02185410
    b @L021853d0
    b @L0218539c
    b @L02185440
    b @L021854e8
    b @L021854a8
    b @L02185474
@L02185368:
    cmp r3, r0
    movne r0, #0x0
    bne @L0218552c
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r5, #0x0]
    mov r0, r9
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L02185514
    mov r0, #0x0
    b @L0218552c
@L0218539c:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218552c
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r5, #0x0]
    mov r0, r9
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L02185514
    mov r0, #0x0
    b @L0218552c
@L021853d0:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218552c
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r12, [r5, #0x0]
    ldrsh r2, [r5, #0x2]
    mov r0, r9
    add r2, r12, r2
    sub r2, r2, r3
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L02185514
    mov r0, #0x0
    b @L0218552c
@L02185410:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218552c
    str r2, [sp, #0x0]
    mov r0, r9
    ldrsh r2, [r5, #0x0]
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker8FindTextEPKcS1_ii
    cmp r0, #0x0
    bne @L02185514
    mov r0, #0x0
    b @L0218552c
@L02185440:
    cmp r3, r0
    movne r0, #0x0
    bne @L0218552c
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r5, #0x0]
    mov r0, r9
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    bne @L02185514
    mov r0, #0x0
    b @L0218552c
@L02185474:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218552c
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r2, [r5, #0x0]
    mov r0, r9
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    bne @L02185514
    mov r0, #0x0
    b @L0218552c
@L021854a8:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218552c
    mov r0, #0x1
    str r0, [sp, #0x0]
    ldrsh r12, [r5, #0x0]
    ldrsh r2, [r5, #0x2]
    mov r0, r9
    add r2, r12, r2
    sub r2, r2, r3
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    bne @L02185514
    mov r0, #0x0
    b @L0218552c
@L021854e8:
    cmp r0, r3
    movlt r0, #0x0
    blt @L0218552c
    str r2, [sp, #0x0]
    ldrsh r2, [r5, #0x0]
    mov r0, r9
    add r2, r10, r2
    bl _ZN20ForbiddenWordChecker5MatchEPKcS1_ii
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L0218552c
@L02185514:
    add r4, r4, #0x1
    add r5, r5, #0x6
@L0218551c:
    ldr r0, [sp, #0x20]
    cmp r4, r0
    blt @L02185304
    mov r0, #0x1
@L0218552c:
    cmp r0, #0x0
    movne r0, #0x1
    bne @L02185570
    ldr r0, [sp, #0x8]
    add r11, r11, #0x1
    add r0, r0, #0x6
    str r0, [sp, #0x8]
@L02185548:
    ldr r0, [sp, #0xc]
    cmp r11, r0
    blt @L021852e8
    add r0, r7, #0x1
    mov r0, r0, lsl #0x10
    mov r7, r0, asr #0x10
@L02185560:
    ldr r0, [sp, #0x4]
    cmp r7, r0
    blt @L0218527c
    mov r0, #0x0
@L02185570:
    add sp, sp, #0xf8
    add sp, sp, #0x400
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Replaces the offsets of the pattern's words with their addresses
static int ResolvePattern(ForbiddenWordFile* file, ForbiddenWordPattern* pattern)
{
    for (int i = 0; i < pattern->count_; i++)
    {
        bool none = true;
        int offset = pattern->words_[i] - (const char*)0;
        if (offset != -1 && file->texts_ != 0)
            none = false;
        pattern->words_[i] = none ? 0 : file->texts_ + offset;
    }
    return 1;
}

void ForbiddenWordChecker::ToUpper(const char* text, char* output)
{
    while (*text != 0)
    {
        if (((*text >= 'a' && *text <= 'z') ? (*output = *text - 0x20) : (*output = *text)) != 0)
            text++;
        output++;
    }
}

// Whether a word is at one of the first positions of a text
int ForbiddenWordChecker::FindText(const char* word, const char* text, int length, int positions)
{
    for (int i = 0; i < positions; i++, text++)
    {
        if (memcmp(word, text, length) == 0)
            return 1;
    }
    return 0;
}

// Whether a pattern (with classes [...], repetitions {n,m}, digits : and the wildcard .{0,60}) matches the text at one
// of its first positions
// NONMATCHING: The loops over the pattern and the text are compiled in another form, with other registers (30.5 %)
#ifdef NONMATCHING
int ForbiddenWordChecker::Match(const char* pattern, const char* text, int length, int positions)
{
    int digit = symbols_[0];
    int classStart = symbols_[1];
    int classEnd = symbols_[2];
    int countStart = symbols_[3];
    int countEnd = symbols_[4];
    int wildcard = symbols_[7];
    for (int i = 0; i < positions; i++, text++)
    {
        const unsigned char* p = (const unsigned char*)pattern;
        const unsigned char* t = (const unsigned char*)text;
        while (true)
        {
            unsigned int symbol = *p;
            if (symbol == 0)
                return 1;

            int min = 1;
            unsigned char character = *t;
            int max = 1;
            const unsigned char* next = p;
            if (symbol == classStart)
            {
                while (*next != classEnd)
                    next++;
                next++;
            }
            else
            {
                next = p + 1;
            }
            if (*next == countStart)
            {
                min = next[1] - 8;
                max = next[3] - 8;
                if (next[4] - 8 == 0)
                    max *= 10;
            }

            int matches = 1;
            if (symbol == wildcard)
            {
                if (min == 0 && max == 60)
                {
                    while (true)
                    {
                        unsigned char current = *t;
                        if (current == 0 || current == 0xff)
                            return 0;
                        if (p[7] == current)
                            break;
                        t++;
                    }
                    p += 8;
                    t++;
                    continue;
                }
            }
            else if (symbol == digit)
            {
                if (character < 0x12 || character > 0x2b)
                    matches = 0;
            }
            else if (symbol == classStart)
            {
                char characters[8];
                __clear(characters, sizeof(characters));
                int negated = 0;
                char* output = characters;
                const unsigned char* current = p + 1;
                int range = 0;
                while (*current != symbols_[2])
                {
                    *output = *current;
                    if (*current == symbols_[5])
                        range = 2;
                    if (*current == symbols_[6])
                        negated = 1;
                    current++;
                    output++;
                }
                int length = strlen(characters);
                switch (negated + range)
                {
                    case 0:
                        matches = Contains((unsigned char*)characters, length, character);
                        break;
                    case 1:
                        matches = (unsigned char)characters[0] <= character &&
                                  character <= (unsigned char)characters[length - 1];
                        break;
                    case 2:
                        matches = Contains((unsigned char*)&characters[1], length - 1, character) == 0;
                        break;
                    case 3:
                        matches = !((unsigned char)characters[1] <= character &&
                                    character <= (unsigned char)characters[length - 2]);
                        break;
                }
                p += length + 1;
            }
            else if (symbol != character)
            {
                matches = 0;
            }

            if (matches)
            {
                for (int k = 0; k < min; k++)
                {
                    if (character != *t)
                    {
                        matches = 0;
                        break;
                    }
                    t++;
                }
                if (!matches)
                    break;
                while (min < max && character == *t)
                {
                    min++;
                    t++;
                }
            }
            else if (min != 0)
            {
                break;
            }

            p++;
            if (*p == countStart)
            {
                while (*p != countEnd)
                    p++;
                p++;
            }
        }
    }
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN20ForbiddenWordChecker8ContainsEPKhih(); // ForbiddenWordChecker::Contains
}

asm int ForbiddenWordChecker::Match(const char* pattern, const char* text, int length, int positions)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x30
    mov r10, r0
    ldr r0, [sp, #0x58]
    str r1, [sp, #0x0]
    str r0, [sp, #0x58]
    ldrb r0, [r10, #0x2a]
    str r2, [sp, #0x4]
    str r0, [sp, #0x24]
    ldrb r0, [r10, #0x2b]
    str r0, [sp, #0x20]
    ldrb r0, [r10, #0x2c]
    str r0, [sp, #0x1c]
    ldrb r0, [r10, #0x2d]
    str r0, [sp, #0x18]
    ldrb r0, [r10, #0x2e]
    str r0, [sp, #0x14]
    ldrb r0, [r10, #0x31]
    str r0, [sp, #0x10]
    mov r0, #0x0
    str r0, [sp, #0xc]
    b @L021859d8
@L021856dc:
    ldr r4, [sp, #0x0]
    ldr r5, [sp, #0x4]
@L021856e4:
    ldrb r1, [r4, #0x0]
    cmp r1, #0x0
    moveq r0, #0x1
    beq @L021859ec
    ldr r0, [sp, #0x20]
    mov r8, #0x1
    cmp r1, r0
    ldrb r6, [r5, #0x0]
    mov r11, r8
    mov r0, r4
    bne @L0218572c
@L02185710:
    ldrb r3, [r0, #0x0]
    ldr r2, [sp, #0x1c]
    cmp r3, r2
    addeq r0, r0, #0x1
    beq @L02185730
    add r0, r0, #0x1
    b @L02185710
@L0218572c:
    add r0, r4, #0x1
@L02185730:
    ldrb r3, [r0, #0x0]
    ldr r2, [sp, #0x18]
    cmp r3, r2
    bne @L02185764
    ldrb r3, [r0, #0x1]
    ldrb r2, [r0, #0x3]
    ldrb r0, [r0, #0x4]
    sub r8, r3, #0x8
    sub r11, r2, #0x8
    subs r0, r0, #0x8
    moveq r0, #0xa
    muleq r0, r11, r0
    moveq r11, r0
@L02185764:
    ldr r0, [sp, #0x10]
    cmp r1, r0
    mov r0, #0x1
    str r0, [sp, #0x8]
    bne @L021857b4
    cmp r8, #0x0
    cmpeq r11, #0x3c
    bne @L02185920
    ldrb r1, [r4, #0x7]
@L02185788:
    ldrb r0, [r5, #0x0]
    cmp r0, #0x0
    cmpne r0, #0xff
    moveq r0, #0x0
    beq @L021859ec
    cmp r1, r0
    addne r5, r5, #0x1
    bne @L02185788
    add r4, r4, #0x8
    add r5, r5, #0x1
    b @L021856e4
@L021857b4:
    ldr r0, [sp, #0x24]
    cmp r1, r0
    bne @L021857dc
    cmp r6, #0x12
    blo @L021857d0
    cmp r6, #0x2b
    bls @L02185920
@L021857d0:
    mov r0, #0x0
    str r0, [sp, #0x8]
    b @L02185920
@L021857dc:
    ldr r0, [sp, #0x20]
    cmp r1, r0
    bne @L02185914
    add r0, sp, #0x28
    mov r1, #0x8
    bl __clear
    mov r9, #0x0
    add r1, sp, #0x28
    add r0, r4, #0x1
    mov r7, r9
    ldrb r3, [r10, #0x2c]
    ldrb r2, [r10, #0x2f]
    ldrb lr, [r10, #0x30]
    b @L02185830
@L02185814:
    strb r12, [r1, #0x0]
    cmp r12, r2
    moveq r7, #0x2
    cmp r12, lr
    moveq r9, #0x1
    add r0, r0, #0x1
    add r1, r1, #0x1
@L02185830:
    ldrb r12, [r0, #0x0]
    cmp r12, r3
    bne @L02185814
    add r9, r9, r7
    add r0, sp, #0x28
    bl strlen
    mov r7, r0
    cmp r9, #0x0
    bne @L02185870
    mov r0, r10
    add r1, sp, #0x28
    mov r2, r7
    mov r3, r6
    bl _ZN20ForbiddenWordChecker8ContainsEPKhih
    str r0, [sp, #0x8]
    b @L02185908
@L02185870:
    cmp r9, #0x1
    bne @L021858a4
    sub r1, r7, #0x1
    add r0, sp, #0x28
    ldrb r1, [r0, r1]
    ldrb r0, [sp, #0x28]
    cmp r0, r6
    cmpls r6, r1
    movls r0, #0x1
    strls r0, [sp, #0x8]
    movhi r0, #0x0
    strhi r0, [sp, #0x8]
    b @L02185908
@L021858a4:
    cmp r9, #0x2
    bne @L021858d8
    mov r0, r10
    add r1, sp, #0x29
    sub r2, r7, #0x1
    mov r3, r6
    bl _ZN20ForbiddenWordChecker8ContainsEPKhih
    cmp r0, #0x0
    moveq r0, #0x1
    streq r0, [sp, #0x8]
    movne r0, #0x0
    strne r0, [sp, #0x8]
    b @L02185908
@L021858d8:
    cmp r9, #0x3
    bne @L02185908
    sub r1, r7, #0x2
    add r0, sp, #0x29
    ldrb r1, [r0, r1]
    ldrb r0, [sp, #0x29]
    cmp r0, r6
    cmpls r6, r1
    movhi r0, #0x1
    strhi r0, [sp, #0x8]
    movls r0, #0x0
    strls r0, [sp, #0x8]
@L02185908:
    add r0, r7, #0x1
    add r4, r4, r0
    b @L02185920
@L02185914:
    cmp r1, r6
    movne r0, #0x0
    strne r0, [sp, #0x8]
@L02185920:
    ldr r0, [sp, #0x8]
    cmp r0, #0x0
    beq @L02185988
    mov r1, #0x0
    b @L02185950
@L02185934:
    ldrb r0, [r5, #0x0]
    cmp r6, r0
    movne r0, #0x0
    strne r0, [sp, #0x8]
    bne @L02185958
    add r1, r1, #0x1
    add r5, r5, #0x1
@L02185950:
    cmp r1, r8
    blt @L02185934
@L02185958:
    ldr r0, [sp, #0x8]
    cmp r0, #0x0
    beq @L021859c0
    b @L0218597c
@L02185968:
    ldrb r0, [r5, #0x0]
    cmp r6, r0
    bne @L02185994
    add r8, r8, #0x1
    add r5, r5, #0x1
@L0218597c:
    cmp r8, r11
    blt @L02185968
    b @L02185994
@L02185988:
    bne @L02185994
    cmp r8, #0x0
    bne @L021859c0
@L02185994:
    ldrb r1, [r4, #0x1]!
    ldr r0, [sp, #0x18]
    cmp r1, r0
    bne @L021856e4
@L021859a4:
    ldrb r1, [r4, #0x0]
    ldr r0, [sp, #0x14]
    cmp r1, r0
    addne r4, r4, #0x1
    bne @L021859a4
    add r4, r4, #0x1
    b @L021856e4
@L021859c0:
    ldr r0, [sp, #0xc]
    add r0, r0, #0x1
    str r0, [sp, #0xc]
    ldr r0, [sp, #0x4]
    add r0, r0, #0x1
    str r0, [sp, #0x4]
@L021859d8:
    ldr r1, [sp, #0xc]
    ldr r0, [sp, #0x58]
    cmp r1, r0
    blt @L021856dc
    mov r0, #0x0
@L021859ec:
    add sp, sp, #0x30
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Whether a character is in a text
int ForbiddenWordChecker::Contains(const unsigned char* text, int length, unsigned char character)
{
    for (int i = 0; i < length; i++, text++)
    {
        if (*text == character)
            return 1;
    }
    return 0;
}

void ProfileEditor::Draw1()
{
    func_ov023_021e761c(&windows_);
    func_0205d1e0(&window_);
    func_0205d228(&window_);
    func_0205da88(&window_, 1, 2, 1);
    func_0205da88(&window_, 1, 3, 1);
    func_0205da88(&window_, 2, 3, 0);
    func_0205d274(&window_);
    DrawCursorAnimation();
    DrawDateArrows();
    DrawDateMarker();
    DrawMarker();
    DrawKey();
}

void ProfileEditor::Draw2()
{
    func_ov023_021e76a8(&windows_);
    if (state_ != 0)
        func_0205d2bc(&window_);
    DrawKeyText();
}

void ProfileEditor::Finish()
{
    func_02094a00();
    func_02094ab0();
    DISPCNT = (DISPCNT & ~0x1f00) | 0x100;
    // BLDCNT
    *(volatile unsigned short*)0x04000050 = 0;
    func_02074bd0(unk_8);
    func_0205d1e0(&window_);
    func_0205d274(&window_);
    func_0205d2bc(&window_);
    func_0205d048(&window_);
    memset(pixels_, 0, 0x20);
    CleanInvalidateCacheRange(pixels_, 0x20);
    LoadToMainBG1CharacterData(pixels_, 0, 0x20);
    text_ = 0;
    pixels_ = 0;
    SafeAllocator* allocators[] = {&allocators_[0], &allocators_[1], &allocators_[2], &allocators_[3],
                                   &allocators_[4]};
    for (int i = 0; i < 5; i++)
    {
        SafeAllocator* allocator = allocators[i];
        if (allocator->GetSignedAllocator() != 0)
            allocator->Destroy();
    }
}


// The touch screen
struct TouchPanel
{
    char unk_0[0x24];
    unsigned short unk_24;
    char unk_26[0x5f - 0x26];
    unsigned char unk_5f;
};

extern "C" TouchPanel data_02114e54;

// Writes the text of an item of the window, and draws it
void ProfileEditor::DrawItemText(unsigned char item, int selected)
{
    Canvas* canvas = func_0205d81c(&window_, item);
    if (canvas == 0)
        return;

    if (selected)
        canvas->flags_ |= 0x40;
    else
        canvas->flags_ &= ~0x40;
    int hidden = 0;
    if (canvas->flags_ & 2)
        hidden = 1;
    memset(text_, 0, 0x960);
    void (ProfileEditor::*functions[])(char* text, int hidden) = {
        0,
        &ProfileEditor::Text_01,
        &ProfileEditor::Text_02,
        &ProfileEditor::Text_03,
        &ProfileEditor::Text_04,
        &ProfileEditor::Text_05,
        &ProfileEditor::Text_06,
        &ProfileEditor::Text_07,
        &ProfileEditor::Text_08,
        &ProfileEditor::Text_09,
        &ProfileEditor::Text_0a,
        &ProfileEditor::Text_0b,
        &ProfileEditor::Text_0c,
        &ProfileEditor::Text_0d,
        &ProfileEditor::Text_0e,
        0,
    };
    if (functions[item] != 0)
        (this->*functions[item])(text_, hidden);
    func_0205d5d0(&window_, item, text_, 0, 0);
}

// Writes the text of the state's item, and draws it
void ProfileEditor::UpdateText()
{
    if (unk_1398 == 0)
        return;

    int hidden = 0;
    if (unk_1398 == 2)
    {
        if (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0 && GetFrame(GetWindow(this))->unk_30 < 0)
            return;
        hidden = 1;
    }
    memset(text_, 0, 0x960);
    void (ProfileEditor::*functions[])(char* text, int hidden) = {
        0,
        &ProfileEditor::Text_01,
        &ProfileEditor::Text_02,
        &ProfileEditor::Text_03,
        &ProfileEditor::Text_04,
        &ProfileEditor::Text_05,
        &ProfileEditor::Text_06,
        &ProfileEditor::Text_07,
        &ProfileEditor::Text_08,
        &ProfileEditor::Text_09,
        &ProfileEditor::Text_0a,
        &ProfileEditor::Text_0b,
        &ProfileEditor::Text_0c,
        &ProfileEditor::Text_0d,
        &ProfileEditor::Text_0e,
        0,
    };
    if (functions[state_] != 0)
        (this->*functions[state_])(text_, hidden);
    func_0205d5d0(&window_, state_, text_, 0, 0);
}

void ProfileEditor::LoadStrings()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    void* file;
    unsigned int size;
    loader->GetLoadedFileByID(tasks_[0], &file, &size);
    allocators_[1].Reset();
    func_020728ac(&strings_, &allocators_[1], file, size, 0, 0, 0);
    unk_1378 = func_02072a68(&strings_, 0);
    loader->RemoveTask(tasks_[0]);
    tasks_[0] = -1;
}

void ProfileEditor::LoadSentences()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    void* file;
    loader->GetLoadedFileByID(tasks_[1], &file, &unk_13b8);
    memcpy(unk_13b4, file, unk_13b8);
    loader->RemoveTask(tasks_[1]);
    tasks_[1] = -1;
}

void ProfileEditor::LoadTexts()
{
    GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    void* file;
    unsigned int size;
    loader->GetLoadedFileByID(tasks_[2], &file, &size);
    allocators_[5].Reset();
    func_020dfec0(&texts_, &allocators_[5], file, size);
    loader->RemoveTask(tasks_[2]);
    tasks_[2] = -1;
}



// The priorities of the backgrounds, and *likely* their layers
static const unsigned char sBackgroundPriorities[3] = {1, 2, 3};
static const unsigned char sBackgroundUnk[3] = {2, 1, 0};

void ProfileEditor::LoadBackgrounds()
{
    BackgroundGraphics* background;
    int count;
    BackgroundLoader* loader;
    Canvas* canvas;
    char name[4];
    void* file;
    unsigned int size;
    unsigned int fileSize;
    loader = BackgroundLoader::GetInstance();
    allocators_[0].Reset();
    for (int i = 0; i < 3; i++)
    {
        background = &backgrounds_[i];
        func_0204b11c(background, 0);
        background->unk_1c_0_ = 0;
        background->unk_1c_4_ = sBackgroundPriorities[i];
        func_0204b5b4(background, sBackgroundUnk[i]);
        func_0204b12c(background, &allocators_[0]);
        func_0204b5e8(background, 0, 0);
    }
    BG1CNT = (BG1CNT & 0x43) | 0x1d00;
    BG2CNT = (BG2CNT & 0x43) | 0x1e00;
    BG3CNT = (BG3CNT & 0x43) | 0x1f08;
    ColorEffect_ConfigureAlphaBlend(0x4000050, 2, 1, 10, 6);

    loader->GetLoadedFileByID(tasks_[3], &file, &size);
    count = func_02046900(file);
    for (int i = 0; i < count; i++)
    {
        void* data = func_020467f0(file, i, name, &fileSize);
        if (data != 0)
        {
            func_0204b174(&backgrounds_[1], data, &allocators_[0], fileSize);
            func_0204b174(&backgrounds_[2], data, &allocators_[0], fileSize);
        }
    }
    for (int i = 0; i < 3; i++)
    {
        background = &backgrounds_[i];
        func_0204bc74(background, 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(background, 0);
    }
    pixels_ = allocators_[0].Allocate(0x7800);
    for (int i = 0; i < 13; i++)
    {
        canvas = &canvases_[i];
        func_0204c7a8(canvas, &allocators_[0], pixels_, 0x800);
        canvas->background_ = &backgrounds_[1];
    }
    window_.background_ = backgrounds_;
    window_.unk_b2 = 3;
    func_0205cf78(&window_, canvases_, 13);
    loader->RemoveTask(tasks_[3]);
    tasks_[3] = -1;
}

void ProfileEditor::LoadSprites()
{
    char name[4];
    void* file;
    unsigned int size;
    unsigned int fileSize;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    for (unsigned int i = 0; i < 19; i = (unsigned char)(i + 1))
        func_0205a198(&sprites_[i]);
    func_0205a234(unk_1360);
    func_0205a444(renderer_);
    renderer_->unk_50 = 0;
    SpriteRenderer* renderer = renderer_;
    renderer->SetSprites(sprites_, 19);
    renderer_->animations_ = (SpriteAnimationList*)unk_1360;

    loader->GetLoadedFileByID(tasks_[4], &file, &size);
    int count = func_02046900(file);
    allocators_[3].Reset();
    for (int i = 0; i < count; i++)
    {
        func_0205a528(renderer_, func_020467f0(file, i, name, &fileSize), fileSize, &allocators_[3]);
    }
    loader->RemoveTask(tasks_[4]);
    tasks_[4] = -1;
}

void ProfileEditor::LoadSprites2()
{
    char name[4];
    void* file;
    unsigned int size;
    unsigned int fileSize;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    for (int i = 0; i < 3; i++)
        func_0205a198(&sprites2_[i]);
    func_0205a444(renderer2_);
    renderer2_->unk_50 = 1;
    SpriteRenderer* renderer = renderer2_;
    renderer->SetSprites(sprites2_, 3);

    loader->GetLoadedFileByID(tasks_[5], &file, &size);
    int count = func_02046900(file);
    allocators_[6].Reset();
    for (int i = 0; i < count; i++)
    {
        func_0205a528(renderer2_, func_020467f0(file, i, name, &fileSize), fileSize, &allocators_[6]);
    }
    loader->RemoveTask(tasks_[5]);
    tasks_[5] = -1;
}

void ProfileEditor::State_Load()
{
    // Constants of one of the file's functions that .rodata has among the variables (the compiler sorts a function's
    // static variables with them, emitting them even when nothing reads them). The code uses such values as
    // immediates, so which function had them, and what for, is unknown (0x800 is *likely* the Y button, which turns the
    // card in Update(), and 0x12 the number of titles that the loop below checks)
    static const unsigned char sConstant0 = 4;
    static const int sConstant1 = 0x800;
    static const int sConstant2 = 0x12;
    static const int sConstant3 = 5;
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_02094a00();
    if (step_ == 0)
    {
        if (func_02046b08(resources->unknown_ptr_3700))
        {
            func_0203b4a0(resources, 0x10);
            func_020466e4(func_020d6c00(), 0xf);
            text_ = (char*)func_020421a0()->unk_5c;
            unsigned int female = 0;
            GameObject* protagonist = gameState->GetProtagonist();
            if (protagonist != 0)
                female = protagonist->partyData_->details_.appearance_.female_;
            char archive[0x40];
            char file[0x20];
            sprintf(archive, "data/bin/ttlname%d.gp2", female);
            sprintf(file, "ttlname%d_<LG>.nat", female);
            tasks_[0] = loader->QueueLoadFileInGP2("data/bin/profstr.gp2", "profstr_<LG>.bin", 0);
            tasks_[1] = loader->QueueLoadFileInGP2("data/bin/profsen.gp2", "profsen_<LG>.bin", 0);
            tasks_[2] = loader->QueueLoadFileInGP2(archive, file, 0);
            tasks_[3] = loader->QueueLoadFile("data/ani/bg_tm.pac", 0);
            tasks_[4] = loader->QueueLoadFileInGP2("data/ani/obj_pro.gp2", "obj_pro_<LG>.pac", 0);
            tasks_[5] = loader->QueueLoadFile("data/ani/obj_pro_y.pac", 0);
            func_020dc2bc();
            step_++;
        }
        return;
    }
    else if (step_ == 1)
    {
        int i;
        int done = 0;
        for (i = 0; i < 6; i++)
        {
            if (tasks_[i] == -1)
            {
                done++;
            }
            else if (loader->GetTaskStatus(tasks_[i]))
            {
                switch (i)
                {
                    case 0:
                        LoadStrings();
                        break;
                    case 1:
                        LoadSentences();
                        break;
                    case 2:
                        LoadTexts();
                        break;
                    case 3:
                        LoadBackgrounds();
                        break;
                    case 4:
                        LoadSprites();
                        break;
                    case 5:
                        LoadSprites2();
                        break;
                }
                break;
            }
        }
        if (done == 6)
            step_++;
        return;
    }
    else if (step_ == 2)
    {
        LoadProfile();
        BG0CNT = (BG0CNT & ~3) | 3;
        BG1CNT = (BG1CNT & ~3) | 2;
        BG2CNT = (BG2CNT & ~3) | 1;
        BG3CNT = (BG3CNT & ~3) | 0;
        DISPCNT = (DISPCNT & ~0x1f00) | 0x1f00;
        void* music = func_02094a00();
        func_02094ab0();
        func_02094b34(music, 0x6e, 0x1ff, 0, 0);
        SetSubBrightness(resources, -16, 15);
        step_++;
        return;
    }
    else if (step_ == 3)
    {
        func_02094a00();
        if (func_02094b4c() && !IsSubBrightnessTransitionActive(resources))
        {
            func_020dc2bc();
            allocators_[2].Reset();
            func_ov023_021e7220(&windows_, 2);
            func_ov023_021e71b4(&windows_, &allocators_[2]);
            windows_.strings_ = &strings_;
            windows_.texts_ = &texts_;
            windows_.unk_5fc = unk_13bc;
            windows_.renderer_ = renderer2_;
            windows_.sprites_ = sprites2_;
            step_++;
            return;
        }
    }
    else if (step_ == 4)
    {
        if (func_ov023_021e76c4(&windows_))
        {
            func_ov023_021e7b34(&windows_, func_020100a8(gameState));
            RefreshCard(1, -1, 0);
            SetSubBrightness(resources, 0, 15);
            void* unk = func_0205ec34();
            for (int i = 0; i < 0x12; i++)
            {
                if (func_0206dfb0(unk, (char*)unk + 0x8c, i + 0x200))
                {
                    unk_13c0[unk_13c4_0] = i;
                    unk_13c4_0++;
                }
            }
            for (int i = 0; i < 0x1e0; i++)
            {
                if (unk_13cc[i / 32] & (1 << (i % 32)))
                {
                    unk_13c8[unk_13c4_5] = i;
                    unk_13c4_5++;
                }
            }
            ProfileData* profile = GetProfile(gameState);
            if (profile->edited_ == 0)
            {
                step_++;
            }
            else
            {
                state_ = 1;
                step_ = 0;
            }
            unsigned short color = 0x294a;
            void* pixels = pixels_;
            memcpy(pixels, &color, sizeof(color));
            CleanInvalidateCacheRange(pixels, sizeof(color));
            LoadToMainBGStandardPalette(pixels, 4, sizeof(color));
            CleanCacheRange(pixels, sizeof(color));
            unsigned short color2 = 0x1ce7;
            void* pixels2 = pixels_;
            memcpy(pixels2, &color2, sizeof(color2));
            CleanInvalidateCacheRange(pixels2, sizeof(color2));
            LoadToMainBGStandardPalette(pixels2, 8, sizeof(color2));
            CleanCacheRange(pixels2, sizeof(color2));
            return;
        }
    }
    else if (step_ == 5)
    {
        MessageSystem* messages = func_020421a0();
        func_0204500c(messages, func_02072a68(&strings_, 500), 0, 0xe3);
        messages->busy_ = 1;
        step_++;
        return;
    }
    else if (step_ == 6)
    {
        if (func_020421a0()->busy_ == 0)
        {
            GetProfile(gameState)->edited_ = 1;
            state_ = 1;
            step_ = 0;
        }
    }
}

void ProfileEditor::State_Menu()
{
    GameState* gameState = GameState::GetInstance();
    func_0200fb8c(gameState);
    BackgroundLoader::GetInstance();
    func_02094a00();
    if (step_ == 0)
    {
        unk_13a0 = 0;
        selection_ = 0;
        func_0205de24(&window_, 0, 2);
        SetItemGrid();
        OpenMenu();
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        selection_ = func_0205d794(&window_);
        int close = 0;
        if (IsConfirmed())
        {
            window_.unk_b8 = state_;
            unk_13a0 = 0;
            func_0205eaa0(data_02108760, 1, 0);
            switch (selection_)
            {
                case 0:
                    state_ = 2;
                    step_ = 0;
                    break;
                case 1:
                    state_ = 9;
                    step_ = 0;
                    break;
                case 2:
                    state_ = 10;
                    step_ = 0;
                    break;
                case 3:
                    state_ = 13;
                    step_ = 0;
                    break;
                case 4:
                    state_ = 14;
                    step_ = 0;
                    break;
                case 5:
                    close = 1;
                    break;
            }
        }
        else if (IsCancelled())
        {
            close = 1;
        }
        if (!close)
            return;

        unk_13a0 = 0;
        selection_ = 0;
        func_0205d6a0(&window_, 1);
        state_ = 15;
        step_ = 0;
        return;
    }
}

// NONMATCHING: The original compares the title with 0x136 at the end of the chain without using the result, and
// assigns the category without a condition (97.8 %)
#ifdef NONMATCHING
void ProfileEditor::State_TitleCategory()
{
    if (step_ == 0)
    {
        unk_13a0 = 0;
        int title = GetProfile(GameState::GetInstance())->title_;
        unsigned int category;
        if (title < 100)
            category = 2;
        else if (title < 200)
            category = 0;
        else if (title == 300)
            category = 3;
        else if (title < 300)
            category = 1;
        else if (title >= 0x136)
            category = 0;
        selections_[0] = category;
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenTitleCategories();
        step_++;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        selections_[0] = func_0205d794(&window_);
        if (IsConfirmed())
        {
            int sound = 1;
            switch (selections_[0])
            {
                case 0:
                    state_ = 3;
                    step_ = 0;
                    break;
                case 1:
                    state_ = 4;
                    step_ = 0;
                    break;
                case 2:
                    if (unk_13c4_0 != 0)
                    {
                        state_ = 5;
                        step_ = 0;
                    }
                    else
                    {
                        sound = 0;
                    }
                    break;
                case 3:
                {
                    GameState* gameState = GameState::GetInstance();
                    const char* title = func_02072a68(&strings_, 0x6d);
                    ProfileData* profile = GetProfile(gameState);
                    profile->title_ = 300;
                    memset(titleText_, 0, sizeof(titleText_));
                    memcpy(titleText_, title, strlen(title));
                    RefreshCard(0, -1, 0);
                    SelectItem(1);
                    break;
                }
            }
            if (sound)
                func_0205eaa0(data_02108760, 1, 0);
        }
        else if (IsCancelled())
        {
            SelectItem(1);
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13ProfileEditor10SelectItemEi(); // ProfileEditor::SelectItem
    void _ZN13ProfileEditor11RefreshCardEiii(); // ProfileEditor::RefreshCard
    void _ZN13ProfileEditor19OpenTitleCategoriesEv(); // ProfileEditor::OpenTitleCategories
}

asm void ProfileEditor::State_TitleCategory()
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r6, r0
    add r1, r6, #0x1000
    ldrb r0, [r1, #0x370]
    cmp r0, #0x0
    bne @L02186cc8
    mov r0, #0x0
    strb r0, [r1, #0x3a0]
    bl _ZN9GameState11GetInstanceEv
    add r0, r0, #0x29c
    add r0, r0, #0x5400
    ldr r0, [r0, #0x4]
    mov r0, r0, lsl #0xd
    mov r1, r0, asr #0x16
    cmp r1, #0x64
    movlt r4, #0x2
    blt @L02186c8c
    cmp r1, #0xc8
    movlt r4, #0x0
    blt @L02186c8c
    cmp r1, #0x12c
    moveq r4, #0x3
    beq @L02186c8c
    movlt r4, #0x1
    blt @L02186c8c
    ldr r0, =0x136
    mov r4, #0x0
    cmp r1, r0
@L02186c8c:
    add r3, r6, #0x1000
    add r0, r6, #0xac
    mov r1, #0x0
    mov r2, #0x3
    str r4, [r3, #0x3d8]
    bl func_0205de24
    mov r0, r6
    bl _ZN13ProfileEditor11SetItemGridEv
    mov r0, r6
    bl _ZN13ProfileEditor19OpenTitleCategoriesEv
    add r0, r6, #0x1000
    ldrb r1, [r0, #0x370]
    add r1, r1, #0x1
    strb r1, [r0, #0x370]
    ldmia sp!, {r4, r5, r6, pc}
@L02186cc8:
    cmp r0, #0x1
    ldmneia sp!, {r4, r5, r6, pc}
    mov r2, #0x1
    add r0, r6, #0xac
    strb r2, [r1, #0x3a0]
    bl func_0205d794
    add r1, r6, #0x1000
    str r0, [r1, #0x3d8]
    mov r0, r6
    bl _ZN13ProfileEditor11IsConfirmedEv
    cmp r0, #0x0
    beq @L02186e0c
    add r1, r6, #0x1000
    ldr r0, [r1, #0x3d8]
    mov r5, #0x1
    cmp r0, #0x3
    addls pc, pc, r0, lsl #0x2
    b @L02186df0
@L02186d10:
    b @L02186d20
    b @L02186d34
    b @L02186d48
    b @L02186d70
@L02186d20:
    mov r0, #0x3
    strb r0, [r1, #0x371]
    mov r0, #0x0
    strb r0, [r1, #0x370]
    b @L02186df0
@L02186d34:
    mov r0, #0x4
    strb r0, [r1, #0x371]
    mov r0, #0x0
    strb r0, [r1, #0x370]
    b @L02186df0
@L02186d48:
    add r0, r6, #0x1300
    ldrh r0, [r0, #0xc4]
    mov r0, r0, lsl #0x1b
    movs r0, r0, lsr #0x1b
    movne r0, #0x5
    strneb r0, [r1, #0x371]
    movne r0, #0x0
    strneb r0, [r1, #0x370]
    moveq r5, #0x0
    b @L02186df0
@L02186d70:
    bl _ZN9GameState11GetInstanceEv
    add r1, r6, #0x33c
    mov r4, r0
    add r0, r1, #0x1000
    mov r1, #0x6d
    bl func_02072a68
    add r1, r4, #0x29c
    add r3, r1, #0x5400
    mov r4, r0
    ldr r2, [r3, #0x4]
    ldr r1, =0xfff801ff
    add r0, r6, #0x1440
    and r1, r2, r1
    orr r1, r1, #0x25800
    str r1, [r3, #0x4]
    mov r1, #0x0
    mov r2, #0x40
    bl memset
    mov r0, r4
    bl strlen
    mov r2, r0
    mov r1, r4
    add r0, r6, #0x1440
    bl memcpy
    mov r1, #0x0
    mov r0, r6
    sub r2, r1, #0x1
    mov r3, r1
    bl _ZN13ProfileEditor11RefreshCardEiii
    mov r0, r6
    mov r1, r5
    bl _ZN13ProfileEditor10SelectItemEi
@L02186df0:
    cmp r5, #0x0
    ldmeqia sp!, {r4, r5, r6, pc}
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    ldmia sp!, {r4, r5, r6, pc}
@L02186e0c:
    mov r0, r6
    bl _ZN13ProfileEditor11IsCancelledEv
    cmp r0, #0x0
    ldmeqia sp!, {r4, r5, r6, pc}
    mov r0, r6
    mov r1, #0x1
    bl _ZN13ProfileEditor10SelectItemEi
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void ProfileEditor::State_Title0()
{
    if (step_ == 0)
    {
        unk_13a0 = 0;
        selections_[1] = GetTitleIndex(0);
        if (selections_[1] < 0)
            selections_[1] = 0;
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenTitles0();
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        selections_[1] = func_0205d794(&window_);
        if (UpdateTouchedPage())
            selections_[1] = func_0205d794(&window_);
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            GameState* gameState = GameState::GetInstance();
            const char* title = func_02072a68(&strings_, selections_[1] + 0x2846);
            ProfileData* profile = GetProfile(gameState);
            memset(titleText_, 0, sizeof(titleText_));
            memcpy(titleText_, title, strlen(title));
            profile->title_ = selections_[1] + 0x136;
            RefreshCard(0, -1, 0);
            SelectItem(0);
            return;
        }
        if (IsCancelled())
            SelectItem(1);
        return;
    }
}

void ProfileEditor::State_Title1()
{
    if (step_ == 0)
    {
        unk_13a0 = 0;
        selections_[2] = GetTitleIndex(1);
        if (selections_[2] < 0)
            selections_[2] = 0;
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenTitles1();
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        selections_[2] = func_0205d794(&window_);
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            GameState* gameState = GameState::GetInstance();
            const char* title = func_02072a68(&strings_, selections_[2] + 0x27d8);
            ProfileData* profile = GetProfile(gameState);
            memset(titleText_, 0, sizeof(titleText_));
            memcpy(titleText_, title, strlen(title));
            profile->title_ = selections_[2] + 0xc8;
            RefreshCard(0, -1, 0);
            SelectItem(0);
            return;
        }
        if (IsCancelled())
            SelectItem(1);
        return;
    }
}

void ProfileEditor::State_Title2()
{
    if (step_ == 0)
    {
        unk_13a0 = 0;
        selections_[3] = 0;
        int title = GetTitleIndex(2);
        for (int i = 0; i < unk_13c4_0; i++)
        {
            if (title == unk_13c0[i])
            {
                selections_[3] = i;
                break;
            }
        }
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenTitles2();
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        selections_[3] = func_0205d794(&window_);
        if (UpdateTouchedPage())
            selections_[3] = func_0205d794(&window_);
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            int index;
            GameState* gameState = GameState::GetInstance();
            index = unk_13c0[selections_[3]];
            const char* title = func_02072a68(&strings_, index + 10000);
            ProfileData* profile = GetProfile(gameState);
            memset(titleText_, 0, sizeof(titleText_));
            memcpy(titleText_, title, strlen(title));
            profile->title_ = index;
            RefreshCard(0, -1, 0);
            SelectItem(0);
            return;
        }
        if (IsCancelled())
            SelectItem(1);
        return;
    }
}

// Whether the birthday is shown on the card (a question)
void ProfileEditor::State_06()
{
    MessageSystem* messages = func_020421a0();
    int windowState = messages->unk_9a0;
    if (windowState == 3)
        messages->unk_19ae = 0;
    if (step_ == 0)
    {
        func_0204500c(messages, func_02072a68(&strings_, 0xf), 0, 0xe3);
        messages->busy_ = 1;
        func_0205d6a0(&window_, 1);
        step_ = 10;
        return;
    }
    else if (step_ == 1)
    {
        if (windowState == 0 || windowState == 3)
            step_++;
        return;
    }
    else if (step_ == 2)
    {
        unk_13a0 = 0;
        unk_13f8 = 0;
        func_0205de24(&window_, 0, 2);
        SetItemGrid();
        OpenQuestion();
        func_0205eaa0(data_02108760, 5, 0);
        step_++;
        return;
    }
    else if (step_ == 3)
    {
        unk_13a0 = 1;
        unk_13f8 = func_0205d794(&window_);
        int done = 0;
        if (IsConfirmed() || IsCancelled())
        {
            DrawItemText(state_, 1);
            func_0205eaa0(data_02108760, 1, 0);
            ProfileData* profile = GetProfile(GameState::GetInstance());
            switch (unk_13f8)
            {
                case 1:
                    profile->showBirthday_ = 1;
                    break;
                case 0:
                    profile->showBirthday_ = 0;
                    break;
            }
            if (IsCancelled())
                profile->showBirthday_ = 1;
            RefreshCard(0, -1, 0);
            done = 1;
        }
        if (!done)
            return;
        MessageSystem* system = func_020421a0();
        int busy = system->busy_ == 0 ? 1 : 0;
        if (!busy)
            func_02043204(system);
        func_0205d6a0(&window_, 1);
        step_++;
        return;
    }
    else if (step_ == 4)
    {
        step_++;
        return;
    }
    else if (step_ == 5)
    {
        step_++;
        return;
    }
    else if (step_ == 6)
    {
        state_ = 1;
        SetItemGrid();
        OpenMenu();
        unk_13a0 = 1;
        unk_13a8 = -1;
        unk_13a9 = 0;
        step_ = 1;
        return;
    }
    else if (step_ == 10 && messages->busy_ == 0)
    {
        ProfileData* profile = GetProfile(GameState::GetInstance());
        if (func_020457e0(messages) == 0)
            profile->showBirthday_ = 0;
        else
            profile->showBirthday_ = 1;
        RefreshCard(0, -1, 0);
        func_0205d6a0(&window_, 1);
        step_ = 5;
    }
}

// Edits the year of the birthday
void ProfileEditor::State_07()
{
    if (step_ == 4)
    {
        int changed = 0;
        int canCancel = 1;
        int scroll = GetTouchedDateArrow();
        if (func_0201248c(data_02114e30, 0x80) || scroll < 0)
        {
            if (unk_13aa != 0)
                unk_13a8 = 1;
            if (unk_13a9 > -3)
                unk_13a9--;
        }
        else if (func_0201248c(data_02114e30, 0x40) || scroll > 0)
        {
            if (unk_13aa != 0)
                unk_13a8 = 0;
            if (unk_13a9 < 3)
                unk_13a9++;
        }
        else
        {
            unk_13a9 = 0;
        }
        UpdateDateArrows();
        if (func_02012444(data_02114e30, 0x80) || unk_13a9 <= -3)
        {
            if (unk_13ab & 2)
            {
                changed = 1;
                year_--;
                unk_13a8 = 1;
                unk_13aa = 1;
                if (year_ % 4 != 0 && month_ == 2 && day_ == 29)
                {
                    day_ = 28;
                    DrawItemText(9, 1);
                }
            }
            else
            {
                unk_13aa = 0;
            }
            unk_13a9 = 0;
        }
        else if (func_02012444(data_02114e30, 0x40) || unk_13a9 >= 3)
        {
            if (unk_13ab & 1)
            {
                changed = 1;
                year_++;
                unk_13a8 = 0;
                unk_13aa = 1;
                if (year_ % 4 != 0 && month_ == 2 && day_ == 29)
                {
                    day_ = 28;
                    DrawItemText(9, 1);
                }
            }
            else
            {
                unk_13aa = 0;
            }
            unk_13a9 = 0;
        }
        else if (func_02012444(data_02114e30, 0x20) || func_0205df38(&window_, 8))
        {
            ShowDateItems(8, 1, 0, 1);
            changed = 1;
            canCancel = 0;
            DrawItemText(7, 1);
        }
        else if (func_0205df38(&window_, 9))
        {
            ShowDateItems(9, 1, 1, 0);
            changed = 1;
            canCancel = 0;
            DrawItemText(7, 1);
        }
        else if (func_0205df38(&window_, 7))
        {
            canCancel = 0;
        }
        if (changed)
        {
            DrawItemText(state_, 1);
            func_0205eaa0(data_02108760, 2, 0);
        }

        int close = 0;
        if (IsConfirmed() || func_0205df38(&window_, 0x10))
        {
            GameState* gameState = GameState::GetInstance();
            ProfileData* profile = GetProfile(gameState);
            DrawItemText(state_, 1);
            func_0205eaa0(data_02108760, 1, 0);
            profile->year_ = year_;
            profile->month_ = month_;
            profile->day_ = day_;
            profile->birthdayChosen_ = 1;
            profile->unk_4_0 = func_02098f20(year_, month_, day_);
            RefreshCard(0, -1, 0);
            state_ = 6;
            step_ = 0;
        }
        else if (IsCancelled() && canCancel)
        {
            close = 1;
        }
        if (!close)
            return;
        func_0205d6a0(&window_, 1);
        step_++;
        return;
    }
    else if (step_ == 5)
    {
        step_++;
        return;
    }
    else if (step_ == 6)
    {
        step_++;
        return;
    }
    else if (step_ == 7)
    {
        state_ = 1;
        SetItemGrid();
        OpenMenu();
        unk_13a0 = 1;
        unk_13a8 = -1;
        unk_13a9 = 0;
        unk_13aa = 0;
        step_ = 1;
        return;
    }
}

// Edits the month of the birthday
void ProfileEditor::State_08()
{
    if (step_ == 4)
    {
        int changed = 0;
        int canCancel = 1;
        int scroll = GetTouchedDateArrow();
        if (func_0201248c(data_02114e30, 0x80) || scroll < 0)
        {
            if (unk_13aa != 0)
                unk_13a8 = 3;
            if (unk_13a9 > -3)
                unk_13a9--;
        }
        else if (func_0201248c(data_02114e30, 0x40) || scroll > 0)
        {
            if (unk_13aa != 0)
                unk_13a8 = 2;
            if (unk_13a9 < 3)
                unk_13a9++;
        }
        else
        {
            unk_13a9 = 0;
        }
        UpdateDateArrows();
        // The days of each month
        unsigned char days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (year_ % 4 == 0)
            days[1] = 29;
        if (func_02012444(data_02114e30, 0x80) || unk_13a9 <= -3)
        {
            if (unk_13ab & 8)
            {
                changed = 1;
                month_--;
                unk_13a8 = 3;
                unk_13aa = 1;
                signed char maximum = days[month_ - 1];
                if (day_ > maximum)
                {
                    day_ = maximum;
                    DrawItemText(9, 1);
                }
            }
            else
            {
                unk_13aa = 0;
            }
            unk_13a9 = 0;
        }
        else if (func_02012444(data_02114e30, 0x40) || unk_13a9 >= 3)
        {
            if (unk_13ab & 4)
            {
                changed = 1;
                month_++;
                unk_13a8 = 2;
                unk_13aa = 1;
                signed char maximum = days[month_ - 1];
                if (day_ > maximum)
                {
                    day_ = maximum;
                    DrawItemText(9, 1);
                }
            }
            else
            {
                unk_13aa = 0;
            }
            unk_13a9 = 0;
        }
        else if (func_02012444(data_02114e30, 0x20) || func_0205df38(&window_, 9))
        {
            ShowDateItems(9, 1, 1, 0);
            changed = 1;
            canCancel = 0;
            DrawItemText(8, 1);
        }
        else if (func_02012444(data_02114e30, 0x10) || func_0205df38(&window_, 7))
        {
            GameState::GetInstance();
            ShowDateItems(7, 0, 1, 1);
            changed = 1;
            canCancel = 0;
            DrawItemText(8, 1);
        }
        else if (func_0205df38(&window_, 8))
        {
            canCancel = 0;
        }
        if (changed)
        {
            DrawItemText(state_, 1);
            func_0205eaa0(data_02108760, 2, 0);
        }

        int close = 0;
        if (IsConfirmed() || func_0205df38(&window_, 0x10))
        {
            GameState* gameState = GameState::GetInstance();
            ProfileData* profile = GetProfile(gameState);
            DrawItemText(state_, 1);
            func_0205eaa0(data_02108760, 1, 0);
            profile->year_ = year_;
            profile->month_ = month_;
            profile->day_ = day_;
            profile->birthdayChosen_ = 1;
            profile->unk_4_0 = func_02098f20(year_, month_, day_);
            RefreshCard(0, -1, 0);
            state_ = 6;
            step_ = 0;
        }
        else if (IsCancelled() && canCancel)
        {
            close = 1;
        }
        if (close)
        {
            func_0205d6a0(&window_, 1);
            step_++;
            return;
        }
        return;
    }
    else if (step_ == 5)
    {
        step_++;
        return;
    }
    else if (step_ == 6)
    {
        step_++;
        return;
    }
    else if (step_ == 7)
    {
        state_ = 1;
        SetItemGrid();
        OpenMenu();
        unk_13a0 = 1;
        unk_13a8 = -1;
        unk_13a9 = 0;
        step_ = 1;
    }
}

// Edits the day of the birthday (and opens the birthday's windows)
void ProfileEditor::State_09()
{
    if (step_ == 0)
    {
        func_0205d6a0(&window_, 1);
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        step_++;
        return;
    }
    else if (step_ == 2)
    {
        step_++;
        return;
    }
    else if (step_ == 3)
    {
        GameState* gameState = GameState::GetInstance();
        year_ = GetProfile(gameState)->year_;
        month_ = GetProfile(gameState)->month_;
        day_ = GetProfile(gameState)->day_;
        func_0205de24(&window_, 0, 2);
        SetItemGrid();
        OpenBirthday();
        unk_13a0 = 0;
        step_++;
        return;
    }
    else if (step_ == 4)
    {
        int changed = 0;
        int canCancel = 1;
        int scroll = GetTouchedDateArrow();
        if (func_0201248c(data_02114e30, 0x80) || scroll < 0)
        {
            if (unk_13aa != 0)
                unk_13a8 = 5;
            if (unk_13a9 > -3)
                unk_13a9--;
        }
        else if (func_0201248c(data_02114e30, 0x40) || scroll > 0)
        {
            if (unk_13aa != 0)
                unk_13a8 = 4;
            if (unk_13a9 < 3)
                unk_13a9++;
        }
        else
        {
            unk_13a9 = 0;
        }
        UpdateDateArrows();
        if (func_02012444(data_02114e30, 0x80) || unk_13a9 <= -3)
        {
            if (!(unk_13ab & 0x20))
            {
                unk_13aa = 0;
            }
            else
            {
                changed = 1;
                day_--;
                unk_13a8 = 5;
                unk_13aa = 1;
            }
            unk_13a9 = 0;
        }
        else if (func_02012444(data_02114e30, 0x40) || unk_13a9 >= 3)
        {
            if (!(unk_13ab & 0x10))
            {
                unk_13aa = 0;
            }
            else
            {
                changed = 1;
                day_++;
                unk_13a8 = 4;
                unk_13aa = 1;
            }
            unk_13a9 = 0;
        }
        else if (func_02012444(data_02114e30, 0x10) || func_0205df38(&window_, 8))
        {
            ShowDateItems(8, 1, 0, 1);
            changed = 1;
            canCancel = 0;
            DrawItemText(9, 1);
        }
        else if (func_0205df38(&window_, 7))
        {
            GameState::GetInstance();
            ShowDateItems(7, 0, 1, 1);
            changed = 1;
            canCancel = 0;
            DrawItemText(9, 1);
        }
        else if (func_0205df38(&window_, 9))
        {
            canCancel = 0;
        }
        if (changed)
        {
            DrawItemText(state_, 1);
            func_0205eaa0(data_02108760, 2, 0);
        }

        int close = 0;
        if (IsConfirmed() || func_0205df38(&window_, 0x10))
        {
            GameState* gameState = GameState::GetInstance();
            ProfileData* profile = GetProfile(gameState);
            DrawItemText(state_, 1);
            func_0205eaa0(data_02108760, 1, 0);
            profile->year_ = year_;
            profile->month_ = month_;
            profile->day_ = day_;
            profile->birthdayChosen_ = 1;
            profile->unk_4_0 = func_02098f20(year_, month_, day_);
            RefreshCard(0, -1, 0);
            state_ = 6;
            step_ = 0;
        }
        else if (IsCancelled() && canCancel)
        {
            close = 1;
        }
        if (!close)
            return;
        func_0205d6a0(&window_, 1);
        step_++;
        return;
    }
    else if (step_ == 5)
    {
        step_++;
        return;
    }
    else if (step_ == 6)
    {
        step_++;
        return;
    }
    else if (step_ == 7)
    {
        state_ = 1;
        SetItemGrid();
        OpenMenu();
        unk_13a0 = 1;
        unk_13a8 = -1;
        unk_13a9 = 0;
        step_ = 1;
        return;
    }
}

// Chooses the kind of accolade: the vocation's or one of the ones that the party has
void ProfileEditor::State_0a()
{
    if (step_ == 0)
    {
        unk_13a0 = 0;
        selections_[4] = 1;
        if (FindAccolade(unk_13c8, unk_13c4_5) < 0)
            selections_[4] = 0;
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenAccoladeKinds();
        step_++;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        selections_[4] = func_0205d794(&window_);
        if (IsConfirmed())
        {
            int sound = 1;
            switch (selections_[4])
            {
                case 0:
                    state_ = 11;
                    step_ = 0;
                    break;
                case 1:
                    if (unk_13c4_5 != 0)
                    {
                        state_ = 12;
                        step_ = 0;
                    }
                    else
                    {
                        sound = 0;
                    }
                    break;
            }
            if (sound)
                func_0205eaa0(data_02108760, 1, 0);
        }
        else if (IsCancelled())
        {
            SelectItem(1);
        }
    }
}

// Chooses an accolade of the vocations
void ProfileEditor::State_0b()
{
    if (step_ == 0)
    {
        unk_13a0 = 0;
        GameState* gameState = GameState::GetInstance();
        unsigned int index;
        if (!GetProfile(gameState)->vocationAccolade_)
        {
            int accolade = GetProfile(gameState)->accolade_;
            if (accolade >= 800 && accolade < 900)
            {
                index = accolade - 799;
                goto found;
            }
            if (accolade >= 900 && accolade < 1000)
            {
                index = accolade - 899;
                goto found;
            }
        }
        index = 0;
    found:
        selections_[5] = index;
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenAccolades0();
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        selections_[5] = func_0205d794(&window_);
        if (UpdateTouchedPage())
            selections_[5] = func_0205d794(&window_);
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            ProfileData* profile = GetProfile(GameState::GetInstance());
            GameState* gameState = GameState::GetInstance();
            func_0202ae18();
            GameObject* protagonist = gameState->GetProtagonist();
            if (selections_[5] == 0)
            {
                PartyMemberData* data = protagonist->partyData_;
                int accolade = 0x50dc;
                if (data->details_.appearance_.female_ == 1)
                    accolade = 0x510e;
                int vocation = data->vocation_;
                profile->vocationAccolade_ = 1;
                profile->accolade_ = accolade + vocation - 0x4e20;
                if (func_0201079c(gameState) == 1)
                    profile->accolade_ = accolade + 13 - 0x4e20;
            }
            else
            {
                int accolade = 0x5140;
                if (protagonist->partyData_->details_.appearance_.female_ == 1)
                    accolade = 0x51a4;
                profile->accolade_ = accolade + selections_[5] - 0x4e21;
                profile->vocationAccolade_ = 0;
            }
            const char* text = func_02072a68(&strings_, profile->accolade_ + 20000);
            memset(accoladeText_, 0, sizeof(accoladeText_));
            memcpy(accoladeText_, text, strlen(text));
            profile->accoladeChosen_ = 1;
            RefreshCard(0, -1, 0);
            SelectItem(0);
            return;
        }
        if (IsCancelled())
            SelectItem(1);
        return;
    }
}

// Chooses one of the accolades that the party has
void ProfileEditor::State_0c()
{
    if (step_ == 0)
    {
        unk_13a0 = 0;
        unk_13f0 = FindAccolade(unk_13c8, unk_13c4_5);
        if (unk_13f0 < 0)
            unk_13f0 = 0;
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenAccolades1();
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        unk_13a0 = 1;
        unk_13f0 = func_0205d794(&window_);
        if (UpdateTouchedPage())
            unk_13f0 = func_0205d794(&window_);
        if (IsConfirmed())
        {
            const char* text = func_020e0434(&texts_, unk_13c8[unk_13f0]);
            if (text == 0)
                return;
            func_0205eaa0(data_02108760, 1, 0);
            memset(accoladeText_, 0, sizeof(accoladeText_));
            memcpy(accoladeText_, text, strlen(text));
            GameState* gameState = GameState::GetInstance();
            ProfileData* profile = GetProfile(gameState);
            profile->accolade_ = unk_13c8[unk_13f0];
            GetProfile(gameState)->vocationAccolade_ = 0;
            GetProfile(gameState)->accoladeChosen_ = 1;
            RefreshCard(0, -1, 0);
            SelectItem(0);
            return;
        }
        if (IsCancelled())
            SelectItem(1);
        return;
    }
}

// Chooses the design of the card
// NONMATCHING: The original reads the design again after storing it, and adds the protagonist's sex first and the
// design shifted, female + (design << 1), while the compiler shifts the design first (81.8 %)
#ifdef NONMATCHING
void ProfileEditor::State_0d()
{
    ProfileData* profile = GetProfile(GameState::GetInstance());
    if (step_ == 0)
    {
        step_++;
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        step_++;
        return;
    }
    else if (step_ == 2)
    {
        unk_13a0 = 0;
        design_ = (profile->unk_0_21 - profile->female_) >> 1;
        func_0205de24(&window_, 0, 3);
        SetItemGrid();
        OpenDesigns();
        step_++;
        return;
    }
    else if (step_ == 3)
    {
        unk_13a0 = 1;
        unsigned int selected = func_0205d794(&window_);
        if (design_ != selected)
        {
            design_ = selected;
            RefreshCard(0, profile->female_ + design_ * 2, 0);
        }
        int done = 0;
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            ProfileData* profile2 = GetProfile(GameState::GetInstance());
            profile2->unk_0_21 = profile2->female_ + design_ * 2;
            profile2->designChosen_ = 1;
            done = 1;
        }
        else if (IsCancelled())
        {
            design_ = (profile->unk_0_21 - profile->female_) >> 1;
            done = 1;
            RefreshCard(0, -1, 0);
        }
        if (done)
            step_++;
        return;
    }
    else if (step_ == 4)
    {
        step_++;
        return;
    }
    else if (step_ == 5)
    {
        state_ = 1;
        step_ = 1;
        SelectItem(1);
        return;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13ProfileEditor11OpenDesignsEv(); // ProfileEditor::OpenDesigns
}

asm void ProfileEditor::State_0d()
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    add r3, r5, #0x1000
    ldrb r1, [r3, #0x370]
    add r0, r0, #0x29c
    add r4, r0, #0x5400
    cmp r1, #0x0
    addeq r1, r1, #0x1
    andeq r0, r1, #0xff
    addeq r0, r0, #0x1
    streqb r0, [r3, #0x370]
    ldmeqia sp!, {r4, r5, r6, pc}
    cmp r1, #0x1
    addeq r0, r1, #0x1
    streqb r0, [r3, #0x370]
    ldmeqia sp!, {r4, r5, r6, pc}
    cmp r1, #0x2
    bne @L02188b8c
    mov r1, #0x0
    strb r1, [r3, #0x3a0]
    ldr r4, [r4, #0x0]
    add r0, r5, #0xac
    mov r2, r4, lsl #0x6
    mov r4, r4, lsl #0x7
    mov r2, r2, lsr #0x1f
    rsb r2, r2, r4, lsr #0x1c
    mov r4, r2, lsr #0x1
    mov r2, #0x3
    str r4, [r3, #0x3f4]
    bl func_0205de24
    mov r0, r5
    bl _ZN13ProfileEditor11SetItemGridEv
    mov r0, r5
    bl _ZN13ProfileEditor11OpenDesignsEv
    add r0, r5, #0x1000
    ldrb r1, [r0, #0x370]
    add r1, r1, #0x1
    strb r1, [r0, #0x370]
    ldmia sp!, {r4, r5, r6, pc}
@L02188b8c:
    cmp r1, #0x3
    bne @L02188c9c
    mov r1, #0x1
    add r0, r5, #0xac
    strb r1, [r3, #0x3a0]
    bl func_0205d794
    add r2, r5, #0x1000
    ldr r1, [r2, #0x3f4]
    cmp r1, r0
    beq @L02188bdc
    str r0, [r2, #0x3f4]
    ldr r0, [r4, #0x0]
    mov r1, #0x0
    mov r0, r0, lsl #0x6
    ldr r12, [r2, #0x3f4]
    mov r2, r0, lsr #0x1f
    mov r0, r5
    mov r3, r1
    add r2, r2, r12, lsl #0x1
    bl _ZN13ProfileEditor11RefreshCardEiii
@L02188bdc:
    mov r0, r5
    mov r6, #0x0
    bl _ZN13ProfileEditor11IsConfirmedEv
    cmp r0, #0x0
    beq @L02188c3c
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, r6
    bl func_0205eaa0
    bl _ZN9GameState11GetInstanceEv
    add r1, r0, #0x5000
    ldr r4, [r1, #0x69c]
    add r0, r5, #0x1000
    mov r2, r4, lsl #0x6
    ldr r3, [r0, #0x3f4]
    mov r0, r2, lsr #0x1f
    add r0, r0, r3, lsl #0x1
    bic r2, r4, #0x1e00000
    mov r0, r0, lsl #0x1c
    orr r0, r2, r0, lsr #0x7
    orr r0, r0, #0x8000000
    str r0, [r1, #0x69c]
    mov r6, #0x1
    b @L02188c84
@L02188c3c:
    mov r0, r5
    bl _ZN13ProfileEditor11IsCancelledEv
    cmp r0, #0x0
    beq @L02188c84
    ldr r2, [r4, #0x0]
    mov r1, r6
    mov r0, r2, lsl #0x6
    mov r2, r2, lsl #0x7
    mov r0, r0, lsr #0x1f
    rsb r2, r0, r2, lsr #0x1c
    mov r12, r2, lsr #0x1
    add r4, r5, #0x1000
    mov r0, r5
    mov r3, r1
    sub r2, r1, #0x1
    str r12, [r4, #0x3f4]
    mov r6, #0x1
    bl _ZN13ProfileEditor11RefreshCardEiii
@L02188c84:
    cmp r6, #0x0
    addne r0, r5, #0x1000
    ldrneb r1, [r0, #0x370]
    addne r1, r1, #0x1
    strneb r1, [r0, #0x370]
    ldmia sp!, {r4, r5, r6, pc}
@L02188c9c:
    cmp r1, #0x4
    addeq r0, r1, #0x1
    streqb r0, [r3, #0x370]
    ldmeqia sp!, {r4, r5, r6, pc}
    cmp r1, #0x5
    ldmneia sp!, {r4, r5, r6, pc}
    mov r1, #0x1
    strb r1, [r3, #0x371]
    mov r0, r5
    strb r1, [r3, #0x370]
    bl _ZN13ProfileEditor10SelectItemEi
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

// Edits the message of the card with the keyboard
void ProfileEditor::State_0e()
{
    if (step_ == 0)
    {
        func_0205d6a0(&window_, 1);
        ProfileData* profile = GetProfile(GameState::GetInstance());
        memset(message_, 0, 0x400);
        windows_.message_ = message_;
        func_02042764(profile->unk_8, message_, 1);
        tasks_[0] = BackgroundLoader::GetInstance()->QueueLoadFile("data/bin/keyboard_pr.bin", 0);
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        if (loader->GetTaskStatus(tasks_[0]))
        {
            if (loader->GetDetailedTaskStatus(tasks_[0]) != 2)
            {
                loader->RemoveTask(tasks_[0]);
                tasks_[0] = -1;
            }
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(tasks_[0], &file, &size);
            if (file != 0 && size != 0)
            {
                allocators_[4].Reset();
                func_ov003_0215e6d8(unk_4);
                func_ov003_0215e6f8(unk_4, &allocators_[4], file, size);
                func_ov003_0215efb8(unk_0);
                ((Keyboard*)unk_0)->layout_ = (KeyboardLayout*)unk_4;
                ((Keyboard*)unk_0)->key_ = 0;
            }
            loader->RemoveTask(tasks_[0]);
            tasks_[0] = -1;
            step_++;
            return;
        }
        return;
    }
    else if (step_ == 2)
    {
        FormatCard(GetProfile(GameState::GetInstance()));
        step_++;
        return;
    }
    else if (step_ == 3)
    {
        unk_13a0 = 0;
        func_0205de24(&window_, 0, 2);
        SetItemGrid();
        OpenMessage();
        memcpy(unk_13ac, GetProfile(GameState::GetInstance())->unk_8, 0x72);
        Keyboard* keyboard = (Keyboard*)unk_0;
        keyboard->text_ = message_;
        keyboard->size_ = 0x400;
        ((Keyboard*)unk_0)->unk_14 = 0x39;
        ((Keyboard*)unk_0)->unk_1f = 1;
        ((Keyboard*)unk_0)->unk_21 = 1;
        ((Keyboard*)unk_0)->unk_24 = 1;
        func_ov003_0215f41c(unk_0, "1");
        ((Keyboard*)unk_0)->unk_22 = 1;
        ((Keyboard*)unk_0)->unk_23 = 0;
        Text_0e(0, 0);
        step_++;
        return;
    }
    else if (step_ == 4)
    {
        if ((func_02012444(data_02114e30, 2) || func_0205d97c(&window_) == 2) && *message_ == 0)
        {
            func_0205d6a0(&window_, 1);
            step_++;
        }
        Keyboard* keyboard = (Keyboard*)unk_0;
        unsigned char page = keyboard->unk_20;
        switch (func_ov003_0215f000(keyboard, unk_13a4))
        {
            case 1:
                func_0205eaa0(data_02108760, 2, 0);
                return;

            case 2:
            case 3:
            case 8:
                func_0205eaa0(data_02108760, 1, 0);
                if (page != ((Keyboard*)unk_0)->unk_20)
                    Text_0e(0, 0);
                func_ov023_021e8270(&windows_);
                return;

            case 4:
            case 5:
            case 6:
            case 7:
            case 11:
                func_0205eaa0(data_02108760, 1, 0);
                Text_0e(0, 0);
                return;

            case 9:
                func_0205eaa0(data_02108760, 1, 0);
                return;

            case 10:
                func_0205eaa0(data_02108760, 1, 0);
                if (*message_ != 0)
                {
                    GameState::GetInstance();
                    BackgroundLoader::AddLockGlobal();
                    BackgroundLoader::FreeAllocationsGlobal();
                    checker_.Initialize();
                    int forbidden = checker_.Check(message_);
                    BackgroundLoader::RemoveLockGlobal();
                    if (forbidden)
                    {
                        func_0205def8(&window_, 0, 14);
                        step_ = 10;
                        return;
                    }
                }
                func_0205d6a0(&window_, 1);
                step_++;
                return;
        }
    }
    else if (step_ == 5)
    {
        func_020426bc(message_, (char*)GetProfile(GameState::GetInstance())->unk_8, 1);
        windows_.message_ = 0;
        memset(message_, 0, 0x400);
        step_++;
        return;
    }
    else if (step_ == 6)
    {
        step_++;
        return;
    }
    else if (step_ == 7)
    {
        state_ = 1;
        SetItemGrid();
        OpenMenu();
        unk_13a0 = 1;
        step_ = 1;
        return;
    }
    else if (step_ == 10)
    {
        MessageSystem* messages = func_020421a0();
        func_0204500c(messages, func_02072a68(&strings_, 501), 0, 0xe3);
        messages->busy_ = 1;
        step_++;
        return;
    }
    else if (step_ == 11)
    {
        if (func_020421a0()->busy_ == 0)
        {
            func_0205def8(&window_, 1, 14);
            step_ = 4;
            ((Keyboard*)unk_0)->unk_18 = 0;
            ((Keyboard*)unk_0)->unk_1c = 0;
        }
    }
}

void ProfileEditor::State_Finish()
{
    GameResources* resources = func_ov017_0218b5b0();
    if (step_ == 0)
    {
        SetSubBrightness(resources, -16, 15);
        step_++;
        return;
    }
    else if (step_ == 1)
    {
        if (IsSubBrightnessTransitionActive(resources))
            return;
        windows_.strings_ = 0;
        windows_.unk_5fc = 0;
        func_ov023_021e7340(&windows_);
        RefreshAccoladeTexts();
        func_020466f4(func_020d6c00(), 0xf);
        func_0203b4b0(resources, 0x10);
        result_ = 1;
        step_ = 0;
        return;
    }
}


// Selects the item of the window under the cursor (after a choice, or when cancelling)
void ProfileEditor::SelectItem(int cancel)
{
    Canvas* canvas = func_0205d888(&window_);
    if (canvas != 0 && !cancel)
    {
        for (int i = 0; i < 5; i++)
        {
            unsigned char item = sMenuItems[i][0];
            if (item == canvas->unk_c4)
            {
                func_0205d6a0(&window_, 0);
                break;
            }
        }
    }
    func_0205d6a0(&window_, 0);
    Canvas* selected = func_0205d888(&window_);
    if (selected == 0)
        return;
    state_ = selected->unk_c4;
    SetItemGrid();
    DrawItemText(state_, 0);
}



// Places the window of an item
void ProfileEditor::SetItemWindow(unsigned char item, short x, short y)
{
    TextWindow* window = &window_;
    for (int i = 0; sItemWindows.windows_[i].item_ != 0xff; i++)
    {
        const ItemWindow* found = &sItemWindows.windows_[i];
        if (found->item_ == item)
        {
            window->unk_b1 = found->item_;
            window->unk_a4 = x;
            window->unk_a6 = y;
            window->SetUnkA8(found->unk_1, found->unk_2);
            window->SetSize(found->width_, found->height_);
            window->SetUnkAc(found->unk_5, found->unk_6);
            window->unk_b5 = 1;
            return;
        }
    }
}

void ProfileEditor::OpenMenu()
{
    SetItemWindow(state_, 2, 1);
    memset(text_, 0, 0x960);
    Text_01(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 0, 0, 0);
}

// The menu: the card's title, accolade, birthday and message, and the items
void ProfileEditor::Text_01(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = selection_;
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    const char* title = func_02072a68(&strings_, 1);
    func_02041a28(text, (0xe0 - func_020420e8(title, 0)) >> 1);
    func_02041fac(text, title, 0x10);
    func_02041b00(text, 3);
    func_02041b70(text, 0, func_02072a68(&strings_, 2));
    int item;
    const short* texts = sMenuTexts;
    for (item = 1;; item++, texts++)
    {
        short id = *texts;
        if (id < 0)
            break;
        func_02042058(text, unk_1378);
        if (item == 5)
            func_02041b34(text, 3, 3);
        func_02041b70(text, item, func_02072a68(&strings_, id));
    }
    func_02041cf4(text, 0x7fff, 2, 0xdd, 0x66);
    func_02041d48(text, 0x7fff, 0x58, 0x10, 0x66);

    GameState* gameState = GameState::GetInstance();
    ProfileData* profile = GetProfile(gameState);
    func_020421a0();
    char unused[0x20];
    __clear(unused, sizeof(unused));
    func_02041a90(text, ((0x88 - func_020420e8(titleText_, 0)) >> 1) + 0x58, 0x16);
    func_02042058(text, titleText_);

    char birthday[0x100];
    __clear(birthday, sizeof(birthday));
    const char* month = func_02072a68(&strings_, GetProfile(gameState)->month_ + 0x13);
    int width;
    if (GetProfile(gameState)->showBirthday_)
    {
        sprintf(birthday, "%d  %s  %d", profile->day_, month, GetProfile(gameState)->year_);
        width = func_020420e8(birthday, 0);
    }
    else
    {
        const char* hiddenBirthday = func_02072a68(&strings_, 0x78);
        int length = func_020d2ff0(hiddenBirthday);
        char shown[0x40];
        __clear(shown, sizeof(shown));
        memcpy(shown, hiddenBirthday + 8, length - 0x11);
        width = func_020420e8(shown, 0);
        sprintf(birthday, hiddenBirthday);
    }
    func_02041a90(text, ((0x88 - width) >> 1) + 0x58, 0x26);
    func_02042058(text, birthday);

    char accolade[0x80];
    __clear(accolade, sizeof(accolade));
    func_0206819c(accoladeText_, accolade, 0);
    func_02041a90(text, ((0x88 - func_020420e8(accolade, 0)) >> 1) + 0x58, 0x36);
    func_02042058(text, accolade);

    short design = 0x6d;
    unsigned int chosen = profile->designChosen_;
    if (chosen)
        design = profile->unk_0_21 + 30000;
    const char* designText = func_02072a68(&strings_, design);
    func_02041a90(text, ((0x88 - func_020420e8(designText, 0)) >> 1) + 0x58, 0x46);
    func_02042058(text, designText);

    char* message = (char*)profile->unk_8;
    int empty = 0;
    if (state_ == 14 && step_ >= 1 && step_ <= 4)
        message = message_;
    const char* messageText;
    if (*message == 0)
    {
        messageText = func_02072a68(&strings_, 0x12);
        empty = 1;
    }
    else
    {
        messageText = func_02072a68(&strings_, 0x13);
    }
    func_02041a90(text, ((0x88 - func_020420e8(messageText, 0)) >> 1) + 0x58, 0x56);
    if (empty)
        func_02041e70(text, 3);
    func_02042058(text, messageText);
}

void ProfileEditor::OpenTitleCategories()
{
    SetItemWindow(state_, 0x14, 1);
    memset(text_, 0, 0x960);
    Text_02(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
}

// The categories of titles
void ProfileEditor::Text_02(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = selections_[0];
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    func_02041b70(text, 0, func_02072a68(&strings_, 7));
    func_02042058(text, unk_1378);
    func_02041b70(text, 1, func_02072a68(&strings_, 8));
    func_02042058(text, unk_1378);
    if (unk_13c4_0 == 0)
        func_02041e70(text, 3);
    func_02041b70(text, 2, func_02072a68(&strings_, 9));
    func_02042058(text, unk_1378);
    if (unk_13c4_0 == 0)
        func_02041e70(text, 0xf);
    func_02041b70(text, 3, func_02072a68(&strings_, 0x6d));
}

void ProfileEditor::OpenTitles0()
{
    SetItemWindow(state_, 0xe, 1);
    memset(text_, 0, 0x960);
    Text_03(text_, 0);
    func_0205d304(&window_, text_, 0, 0, 1, 1, 0, 0);
}

// The titles of the first category, in two columns
void ProfileEditor::Text_03(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = selections_[1] & 0xf;
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    func_020421a0();
    WindowCursor* cursor = GetCursor(&window_);
    int shadow = cursor->words_[5];
    int color = cursor->unk_4;
    int first;
    int last;
    func_0205c508(cursor, &first, &last);
    int end = first + (last + 1 - first) / 2;
    for (int i = first; i < end; i++)
    {
        if (i != first)
            func_02042058(text, unk_1378);
        func_02041b70(text, i & 0xf, func_02072a68(&strings_, i + 0x2846));
        int right = i + (last + 1 - first) / 2;
        if (right < 0xc0)
        {
            func_02041a28(text, 0x56);
            func_02041b70(text, right & 0xf, func_02072a68(&strings_, right + 0x2846));
        }
    }
    SetCanvasColors(3, shadow, color);
}

void ProfileEditor::OpenTitles1()
{
    SetItemWindow(state_, 0x10, 1);
    memset(text_, 0, 0x960);
    Text_04(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
}

// The titles of the second category
void ProfileEditor::Text_04(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = selections_[2];
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    for (int i = 0; i < 8; i++)
    {
        if (i != 0)
            func_02042058(text, unk_1378);
        func_02041b70(text, i, func_02072a68(&strings_, i + 0x27d8));
    }
}

void ProfileEditor::OpenTitles2()
{
    SetItemWindow(state_, 0x10, 1);
    memset(text_, 0, 0x960);
    Text_05(text_, 0);
    int scroll = 0;
    if (unk_13c4_0 > 9)
        scroll = 1;
    func_0205d304(&window_, text_, 0, 0, scroll, 1, 0, 0);
}

// The titles of the third category that the party has
void ProfileEditor::Text_05(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = selections_[3] % 9;
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    func_020421a0();
    int i;
    WindowCursor* cursor = GetCursor(&window_);
    int shadow = cursor->words_[5];
    int color = cursor->unk_4;
    int first;
    int last;
    func_0205c508(cursor, &first, &last);
    for (i = first; i < last; i++)
    {
        if (i != first)
            func_02042058(text, unk_1378);
        func_02041b70(text, i % 9, func_02072a68(&strings_, unk_13c0[i] + 10000));
    }
    if (unk_13c4_0 > 9)
    {
        SetCanvasColors(5, shadow, color);
        func_02041a90(text, 0x2a, 0x94);
        func_02042058(text, " ");
    }
}

void ProfileEditor::OpenQuestion()
{
    SetItemWindow(state_, 0x19, 0xa);
    memset(text_, 0, 0x960);
    Text_06(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
}

// Yes and no
void ProfileEditor::Text_06(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = unk_13f8;
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    func_02041b70(text, 0, func_02072a68(&strings_, 0x10));
    func_02042058(text, unk_1378);
    func_02041b70(text, 1, func_02072a68(&strings_, 0x11));
}

void ProfileEditor::OpenBirthday()
{
    SetItemWindow(16, 0x17, 0x15);
    memset(text_, 0, 0x960);
    func_0205d304(&window_, text_, 0, 0, 0, 1, 0, 0);
    SetItemWindow(8, 0xa, 8);
    memset(text_, 0, 0x960);
    Text_08(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
    SetItemWindow(7, 0x13, 8);
    memset(text_, 0, 0x960);
    Text_07(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
    SetItemWindow(state_, 1, 8);
    memset(text_, 0, 0x960);
    Text_09(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
    func_0205deb4(&window_, 0x10, 0);
}

// The year
void ProfileEditor::Text_07(char* text, int hidden)
{
    if (text == 0)
        return;

    MessageSystem* messages = func_020421a0();
    func_020465c0(messages, 0, year_);
    func_020465f0(messages, 0, 4);
    func_020465d8(messages, 0, 1);
    func_02041d9c(text, 0xc);
    short id = 0x64;
    if (state_ == 7)
        id = 0x67;
    func_02041b70(text, 0, func_02072a68(&strings_, id));
    const char* label = func_02072a68(&strings_, 0x2a);
    func_02041a90(text, (0x60 - func_020420e8(label, 0)) >> 1, 1);
    func_02042058(text, label);
}

// The month
void ProfileEditor::Text_08(char* text, int hidden)
{
    if (text == 0)
        return;

    func_020421a0();
    if (state_ == 8)
        func_02041dd0(text, 4);
    func_02041b70(text, 0, func_02072a68(&strings_, month_ + 0x13));
    if (state_ == 8)
        func_02041dd0(text, 0);
    const char* label = func_02072a68(&strings_, 0x29);
    func_02041a90(text, (0x48 - func_020420e8(label, 0)) >> 1, 1);
    func_02042058(text, label);
}

// The day
void ProfileEditor::Text_09(char* text, int hidden)
{
    if (text == 0)
        return;

    MessageSystem* messages = func_020421a0();
    func_020465c0(messages, 0, day_);
    func_020465f0(messages, 0, 2);
    func_020465d8(messages, 0, 1);
    func_02041d9c(text, 0xc);
    short id = 0x66;
    if (state_ == 9)
        id = 0x69;
    func_02041b70(text, 0, func_02072a68(&strings_, id));
    const char* label = func_02072a68(&strings_, 0x28);
    func_02041a90(text, (0x48 - func_020420e8(label, 0)) >> 1, 1);
    func_02042058(text, label);
}

void ProfileEditor::OpenAccoladeKinds()
{
    SetItemWindow(state_, 0x15, 1);
    memset(text_, 0, 0x960);
    Text_0a(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
}

// The kinds of accolades
void ProfileEditor::Text_0a(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = selections_[4];
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    func_02041b70(text, 0, func_02072a68(&strings_, 0xa));
    func_02042058(text, unk_1378);
    if (unk_13c4_5 == 0)
        func_02041e70(text, 3);
    func_02041b70(text, 1, func_02072a68(&strings_, 0xb));
}

void ProfileEditor::OpenAccolades0()
{
    SetItemWindow(state_, 0xf, 1);
    memset(text_, 0, 0x960);
    Text_0b(text_, 0);
    func_0205d304(&window_, text_, 0, 0, 1, 1, 0, 0);
}

// The accolades of the vocations
void ProfileEditor::Text_0b(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = selections_[5] % 10;
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    func_020421a0();
    GameObject* protagonist;
    int i;
    WindowCursor* cursor = GetCursor(&window_);
    int shadow = cursor->words_[5];
    int color = cursor->unk_4;
    int first;
    int last;
    func_0205c508(cursor, &first, &last);
    func_0202ae18();
    protagonist = GameState::GetInstance()->GetProtagonist();
    int base = 0x50dc;
    for (i = first; i < last; i++)
    {
        if (i != first)
            func_02042058(text, unk_1378);
        if (i == 0)
        {
            int id = base;
            if (protagonist->partyData_->details_.appearance_.female_ == 1)
                id = 0x510e;
            const char* name = func_02072a68(&strings_, id);
            func_02041b70(text, i % 10, name);
        }
        else
        {
            int id = 0x5140;
            if (protagonist->partyData_->details_.appearance_.female_ == 1)
                id = 0x51a4;
            const char* name = func_02072a68(&strings_, id + i - 1);
            char converted[0x80];
            __clear(converted, sizeof(converted));
            func_0206819c(name, converted, 0);
            func_02041b70(text, i % 10, converted);
        }
    }
    SetCanvasColors(11, shadow, color);
}

void ProfileEditor::OpenAccolades1()
{
    SetItemWindow(state_, 0, 1);
    memset(text_, 0, 0x960);
    Text_0c(text_, 0);
    int scroll;
    if ((unk_13c4_5 - 1) / 16 > 0)
        scroll = 1;
    else
        scroll = 0;
    func_0205d304(&window_, text_, 0, 0, scroll, 1, 0, 0);
}

// The accolades that the party has, in two columns
void ProfileEditor::Text_0c(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = unk_13f0 & 0xf;
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    func_020421a0();
    int i;
    WindowCursor* cursor = GetCursor(&window_);
    int shadow = cursor->words_[5];
    int color = cursor->unk_4;
    int first;
    int last;
    func_0205c508(cursor, &first, &last);
    for (i = first; i < last; i++)
    {
        if (i % 2 == 0)
        {
            if (i != first)
                func_02042058(text, unk_1378);
        }
        else
        {
            func_02041a28(text, 0x88);
        }
        func_02041b70(text, i & 0xf, func_020e0434(&texts_, unk_13c8[i]));
    }
    if (color > 1)
    {
        SetCanvasColors(12, shadow, color);
        func_02041a90(text, 0x56, 0x94);
        func_02042058(text, " ");
    }
}

void ProfileEditor::OpenDesigns()
{
    SetItemWindow(state_, 0x10, 1);
    memset(text_, 0, 0x960);
    Text_0d(text_, 0);
    func_0205d304(&window_, text_, 0, 1, 0, 1, 0, 0);
}

// The designs of the card
// NONMATCHING: The original adds the protagonist's sex first and the index shifted, female + (i << 1), while the
// compiler shifts the index first (94.2 %)
#ifdef NONMATCHING
void ProfileEditor::Text_0d(char* text, int hidden)
{
    if (text == 0)
        return;

    int selection = design_ & 7;
    ProfileData* profile = GetProfile(GameState::GetInstance());
    if (hidden)
        func_02041c08(text, selection, 8, 5, 5, 5);
    func_02041ea4(text, selection);
    for (int i = 0; i < 8; i++)
    {
        if (i != 0)
            func_02042058(text, unk_1378);
        func_02041b70(text, i, func_02072a68(&strings_, profile->female_ + 30000 + i * 2));
    }
}
#else
asm void ProfileEditor::Text_0d(char* text, int hidden)
{
    stmdb sp!, {r4, r5, r6, r7, r8, lr}
    sub sp, sp, #0x8
    movs r7, r1
    mov r8, r0
    mov r5, r2
    beq @L0218aab4
    add r0, r8, #0x1000
    ldr r0, [r0, #0x3f4]
    and r4, r0, #0x7
    bl _ZN9GameState11GetInstanceEv
    add r0, r0, #0x29c
    cmp r5, #0x0
    add r5, r0, #0x5400
    beq @L0218aa40
    mov r3, #0x5
    str r3, [sp, #0x0]
    mov r0, r7
    mov r1, r4
    mov r2, #0x8
    str r3, [sp, #0x4]
    bl func_02041c08
@L0218aa40:
    mov r0, r7
    mov r1, r4
    bl func_02041ea4
    add r4, r8, #0x33c
    mov r6, #0x0
    add r8, r8, #0x1000
    b @L0218aaac
@L0218aa5c:
    cmp r6, #0x0
    beq @L0218aa70
    ldr r1, [r8, #0x378]
    mov r0, r7
    bl func_02042058
@L0218aa70:
    ldr r1, [r5, #0x0]
    add r0, r4, #0x1000
    mov r1, r1, lsl #0x6
    mov r1, r1, lsr #0x1f
    add r1, r1, r6, lsl #0x1
    add r1, r1, #0x530
    add r1, r1, #0x7000
    mov r1, r1, lsl #0x10
    mov r1, r1, asr #0x10
    bl func_02072a68
    mov r2, r0
    mov r0, r7
    mov r1, r6
    bl func_02041b70
    add r6, r6, #0x1
@L0218aaac:
    cmp r6, #0x8
    blt @L0218aa5c
@L0218aab4:
    add sp, sp, #0x8
    ldmia sp!, {r4, r5, r6, r7, r8, pc}
}
#endif

void ProfileEditor::OpenMessage()
{
    SetItemWindow(state_, 1, 3);
    memset(text_, 0, 0x960);
    Text_0e(text_, 0);
    func_0205d304(&window_, text_, 0, 0, 0, 1, 0, 0);
}

// The keyboard of the message (without a text: it draws its keys on the window's canvas)
// NONMATCHING: The compiler assigns the registers of two variables and the stack slots of three the other way around
// (89.9 %, with the variables declared in every order)
#ifdef NONMATCHING
void ProfileEditor::Text_0e(char* text, int hidden)
{
    if (text != 0)
        return;

    short outX;
    short outY;
    short w;
    short h;
    const char* title;
    Canvas* canvas;
    int mask;
    KeyboardKey* key;
    int x;
    unsigned char large;
    int left;
    int top;
    int keyWidth;
    int shifted;
    int page;
    int count;
    canvas = func_0205d81c(&window_, 14);
    if (canvas == 0)
        return;

    left = canvas->x_ << 19;
    top = canvas->y_ << 19;
    title = func_02072a68(&strings_, 0xe);
    x = (0xf0 - func_020420e8(title, 1)) >> 1;
    Keyboard* keyboard = (Keyboard*)unk_0;
    KeyboardLayout* layout = (KeyboardLayout*)unk_4;
    void* pixels = canvas->pixels_;
    large = keyboard->unk_1f;
    mask = keyboard->unk_1e;
    page = keyboard->unk_20;
    count = layout->count_;
    key = layout->keys_;
    if (pixels != 0)
        memset(pixels, 0, 0x7800);
    func_0204f160(canvas, canvas->unk_a0, 0xe);
    func_0204ecb4(canvas, 0, 0, 0x1e, 0x12, 0);
    func_0204f41c(canvas, x, 6, title, 0xc, 0xf, &outX, &outY, large);
    func_0204f3bc(canvas, 0x18);
    shifted = mask & 2;
    for (int i = 0; i < count; i++, key++)
    {
        if (key->flags_ & mask)
        {
            const char* keyText = key->text_;
            if (page != 0 || shifted != 0)
                keyText = key->shiftedText_;
            if (key->unk_d != 0)
                keyText = key->text_;
            keyWidth = func_020420e8(keyText, 1);
            func_ov003_0215ec68(key->size_, &w, &h);
            short keyX = key->x_ - (left >> 16);
            short keyY = key->y_ - (top >> 16);
            func_0204f914(canvas, 4, keyX + 1, keyY + 1, (short)(w + keyX - 1), (short)(h + keyY - 1));
            w = (w - keyWidth) >> 1;
            func_0204f41c(canvas, w + keyX, keyY + 2, keyText, 0xc, 0xf, &outX, &outY, large);
        }
    }
    func_0204fbf8(canvas);
}
#else
asm void ProfileEditor::Text_0e(char* text, int hidden)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x34
    mov r6, r0
    cmp r1, #0x0
    bne @L0218ada4
    add r0, r6, #0xac
    mov r1, #0xe
    bl func_0205d81c
    movs r5, r0
    beq @L0218ada4
    ldrsh r2, [r5, #0xac]
    ldrsh r3, [r5, #0xae]
    add r0, r6, #0x33c
    mov r2, r2, lsl #0x13
    str r2, [sp, #0x28]
    mov r2, r3, lsl #0x13
    add r0, r0, #0x1000
    mov r1, #0xe
    str r2, [sp, #0x24]
    bl func_02072a68
    mov r1, #0x1
    mov r4, r0
    bl func_020420e8
    ldmia r6, {r1, r2}
    rsb r3, r0, #0xf0
    ldr r0, [r5, #0x8]
    ldrb r9, [r1, #0x1f]
    ldrb r6, [r1, #0x1e]
    ldrb r1, [r1, #0x20]
    mov r8, r3, asr #0x1
    cmp r0, #0x0
    str r1, [sp, #0x18]
    ldrsh r1, [r2, #0x6]
    ldr r7, [r2, #0x0]
    str r1, [sp, #0x14]
    beq @L0218abd0
    mov r1, #0x0
    mov r2, #0x7800
    bl memset
@L0218abd0:
    ldr r1, [r5, #0xa0]
    mov r0, r5
    mov r2, #0xe
    bl func_0204f160
    mov r0, #0x12
    mov r1, #0x0
    str r0, [sp, #0x0]
    mov r0, r5
    mov r2, r1
    mov r3, #0x1e
    str r1, [sp, #0x4]
    bl func_0204ecb4
    mov r0, r8, lsl #0x10
    mov r1, r0, asr #0x10
    mov r0, #0xc
    str r0, [sp, #0x0]
    mov r0, #0xf
    str r0, [sp, #0x4]
    add r2, sp, #0x32
    str r2, [sp, #0x8]
    add r0, sp, #0x30
    str r0, [sp, #0xc]
    mov r3, r4
    mov r0, r5
    mov r2, #0x6
    str r9, [sp, #0x10]
    bl func_0204f41c
    mov r0, r5
    mov r1, #0x18
    bl func_0204f3bc
    and r0, r6, #0x2
    mov r8, #0x0
    str r0, [sp, #0x1c]
    b @L0218ad90
@L0218ac58:
    ldrb r0, [r7, #0xc]
    tst r0, r6
    beq @L0218ad88
    ldr r0, [sp, #0x18]
    ldr r1, [r7, #0x4]
    cmp r0, #0x0
    ldreq r0, [sp, #0x1c]
    mov r11, r1
    cmpeq r0, #0x0
    ldrb r0, [r7, #0xd]
    ldrne r11, [r7, #0x8]
    cmp r0, #0x0
    movne r11, r1
    mov r0, r11
    mov r1, #0x1
    bl func_020420e8
    str r0, [sp, #0x20]
    ldrb r0, [r7, #0xe]
    add r1, sp, #0x2e
    add r2, sp, #0x2c
    bl func_ov003_0215ec68
    ldrsh r3, [r7, #0x0]
    ldr r0, [sp, #0x28]
    ldrsh r2, [r7, #0x2]
    sub r0, r3, r0, asr #0x10
    mov r4, r0, lsl #0x10
    ldr r0, [sp, #0x24]
    ldrsh r1, [sp, #0x2e]
    sub r0, r2, r0, asr #0x10
    mov r3, r0, lsl #0x10
    add r0, r1, r4, asr #0x10
    sub r0, r0, #0x1
    mov r0, r0, lsl #0x10
    mov r0, r0, asr #0x10
    str r0, [sp, #0x0]
    mov r0, r4, asr #0x10
    add r0, r0, #0x1
    mov r0, r0, lsl #0x10
    mov r2, r0, asr #0x10
    ldrsh r12, [sp, #0x2c]
    mov r10, r3, asr #0x10
    mov r0, r5
    add r3, r12, r3, asr #0x10
    sub r3, r3, #0x1
    mov r3, r3, lsl #0x10
    mov r3, r3, asr #0x10
    str r3, [sp, #0x4]
    add r3, r10, #0x1
    mov r3, r3, lsl #0x10
    mov r1, #0x4
    mov r3, r3, asr #0x10
    bl func_0204f914
    add r0, r10, #0x2
    mov r0, r0, lsl #0x10
    mov r2, r0, asr #0x10
    ldrsh r10, [sp, #0x2e]
    ldr r1, [sp, #0x20]
    mov r3, r11
    sub r1, r10, r1
    mov r1, r1, asr #0x1
    strh r1, [sp, #0x2e]
    mov r1, #0xc
    str r1, [sp, #0x0]
    mov r1, #0xf
    str r1, [sp, #0x4]
    add r1, sp, #0x32
    str r1, [sp, #0x8]
    add r1, sp, #0x30
    str r1, [sp, #0xc]
    str r9, [sp, #0x10]
    ldrsh r1, [sp, #0x2e]
    mov r0, r5
    add r1, r1, r4, asr #0x10
    mov r1, r1, lsl #0x10
    mov r1, r1, asr #0x10
    bl func_0204f41c
@L0218ad88:
    add r8, r8, #0x1
    add r7, r7, #0x14
@L0218ad90:
    ldr r0, [sp, #0x14]
    cmp r8, r0
    blt @L0218ac58
    mov r0, r5
    bl func_0204fbf8
@L0218ada4:
    add sp, sp, #0x34
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Draws the card of the profile, with a design (or its own), and keeps the page of the card or not
void ProfileEditor::RefreshCard(int animate, int design, int keepPage)
{
    GameState* gameState = GameState::GetInstance();
    RefreshAccoladeTexts();
    ProfileData* profile;
    ProfileData copy;
    if (design == -1)
    {
        profile = GetProfile(gameState);
    }
    else
    {
        memcpy(&copy, GetProfile(gameState), sizeof(copy));
        copy.unk_0_21 = design;
        profile = &copy;
    }
    if (!keepPage)
    {
        unk_14bd = 0;
        windows_.unk_60c = 0;
    }
    if (FormatCard(profile) || !keepPage)
    {
        if (animate)
            func_ov023_021e7bc4(&windows_, 2, 0);
        else
            func_ov023_021e7c58(&windows_, 2, 0);
    }
    ResetAccoladeTexts();
}

// Writes the text of the card, and returns whether it has two pages
int ProfileEditor::FormatCard(ProfileData* profile)
{
    int twoPages = 1;
    windows_.unk_60d = 1;
    memset(text_, 0, 0x960);
    func_02099304(profile, name_, unk_13b4, unk_13b8, text_, 0x960, 0, titleText_, accoladeText_);
    char* shown = text_;
    char* page = strstr(shown, "<PAGE>");
    if (page == 0)
    {
        twoPages = 0;
        unk_14bd = 0;
        windows_.unk_60c = 0;
        windows_.unk_60d = 0;
    }
    else if (unk_14bd == 0)
    {
        *page = 0;
    }
    else
    {
        shown = page + strlen(name_) + 0xb;
    }
    memset(unk_13bc, 0, 0xf2);
    memcpy(unk_13bc, shown, strlen(shown));
    return twoPages;
}
