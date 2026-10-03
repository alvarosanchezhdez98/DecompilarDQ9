// The alchemy menu of overlay 6, which overlay 17 runs: the choice of the ingredients (up to three items of the
// player's categories, and how many of each), alchemy with its success rate and great successes, the recipe book
// with its categories, filters and orders, and making a recipe of the book

#include "Scene/Overlay_6/AlchemyMenu.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "GameState/Party.h"
#include "GameState/PartyMemberData.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/BGBases.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include "System/TouchScreen.h"
#include "Util/Random.h"
#include <std_library_functions.h>

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    // The runtime's float and division functions, for the assembly
    void _fdiv();
    void _ffix();
    void _ffltu();
    void _fmul();
    void _s32_div_f();

    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];
    extern TouchState data_02114e54;
    extern const char* data_020f2a30;
    extern const char* data_020f2a38;

    GameResources* func_0200fb8c(GameState* gameState);
    int func_0200fb08(GameState* gameState);
    void* func_0200ff1c(GameState* gameState, unsigned char member);
    int func_020100a8(GameState* gameState);
    Party* func_02010828(GameState* gameState);
    int func_02012444(void* pad, int buttons);
    void func_02012a84(TouchState* touch, int* x, int* y);
    void func_0202ae18();
    int func_0202c540();
    void* func_0203bd08();
    unsigned int func_0203be4c(void* vram);
    char* func_020421a0();
    char* func_0204254c(const char* text, int);
    void func_02046380(char* messages);
    void func_020465c0(char* messages, int, int);
    void func_02046608(char* messages, int, const char* format, char* output, int size, int, int);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    void* func_020467f0(void* pac, int index, void** name, unsigned int* size);
    int func_02046900(void* pac);
    void* func_0204af14(BackgroundGraphics* graphics, int layer);
    void func_0204af38(BackgroundGraphics* graphics, int, SafeAllocator* allocator);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204b010(BackgroundGraphics* graphics, int);
    void func_0204b04c(BackgroundGraphics* graphics, int);
    void func_0204b088(BackgroundGraphics* graphics, int);
    void func_0204b0e8(BackgroundGraphics* graphics, int);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b12c(BackgroundGraphics* graphics, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* graphics, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* graphics, int);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204b8d0(BackgroundGraphics* graphics, unsigned char, int, int, int, int, int, int, unsigned short);
    void func_0204b938(BackgroundGraphics* graphics, void* layer, short x, short y, unsigned short);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* buffer, unsigned int size);
    int func_0204c7e0(Canvas* canvas);
    void func_0205a198(Sprite* sprite);
    void func_0205a330(SpriteAnimationList* list, int ticks);
    void func_0205a370(SpriteAnimationList* list, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* list, int index);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205ae8c(SpriteRenderer* renderer);
    unsigned char func_0205eaa0(void* sound, int effect, int);
    char* func_0205ec34();
    void func_0206df6c(void* flags, void* flags2, int flag, int);
    int func_0206dfb0(void* flags, void* flags2, int flag);
    void func_02071be8(RecipeTable* table);
    void func_02071c00(RecipeTable* table, SafeAllocator* allocator, void* file, unsigned int size);
    Recipe* func_02071da4(RecipeTable* table, short* items, unsigned char* counts, unsigned char* times);
    void func_02071ffc(RecipeTable* table, signed char category, signed char kind, unsigned char sort, int,
                       short* count);
    void func_02075cdc(Unknown_02075cdc* graphics);
    void func_02075db0(Unknown_02075cdc* graphics, int x, int y);
    void func_02076080(Unknown_02075cdc* graphics, SafeAllocator* allocator, void* file, unsigned int size);
    void func_02076988(Unknown_02075cdc* graphics, int width, int height);
    short* func_0207c5f8(void* lists, int list);
    unsigned char* func_0207c60c(void* lists, int list);
    short func_0207c620(void* lists, int list);
    void func_0207cbe8(SafeAllocator* allocator);
    void func_0207cc0c(SafeAllocator* allocator);
    void func_0207d300(SafeAllocator* allocator, short item, signed char count, int);
    void func_0207f7f0(Menu* menu, Canvas* canvases, int numCanvases);
    void func_0207f84c(Menu* menu);
    void func_0207f914(Menu* menu, SafeAllocator* allocator, const char* archive, const char* file);
    int func_0207f9f4(Menu* menu);
    void func_0207fc6c(Menu* menu, int ticks);
    void func_0207fcb8(Menu* menu);
    void func_0207fd00(Menu* menu);
    void func_0207fd44(Menu* menu);
    void func_0207fd88(Menu* menu);
    void func_0207fdcc(Menu* menu, short group);
    void func_0207fe44(Menu* menu);
    void func_0207fe80(Menu* menu, int, int, int);
    int func_020800fc(Menu* menu, short* cursor, short prevCursor, unsigned short buttons, unsigned char, int);
    short func_02080468(Menu* menu, short group);
    void func_020804fc(Menu* menu, short group);
    void func_020805f4(Menu* menu, short item);
    void func_02080608(Menu* menu, short group);
    void func_0208065c(Menu* menu, short group);
    void func_020806b0(Menu* menu, short item);
    void func_020806c4(Menu* menu, short item);
    void func_020806d8(Menu* menu, int, int, int, int);
    void func_02080798(Menu* menu, short item, int);
    void func_020807c4(Menu* menu, short item, short* x, short* y);
    void func_020809c4(Menu* menu, short group, short item, short* x, short* y);
    void func_02080b2c(Menu* menu, short item);
    void func_02080b40(Menu* menu, short item);
    void func_02080b54(Menu* menu, short group);
    void func_02080bac(Menu* menu, short group);
    void func_02080c04(Menu* menu, short group);
    void func_02080c20(Menu* menu, short group);
    int func_02080c3c(Menu* menu, short group);
    void func_02080c68(Menu* menu, short group, int);
    void func_02080cc0(Menu* menu, short item, int);
    int func_02080d54(Menu* menu, short group, short x, short y);
    int func_02080dd4(Menu* menu, short group, short x, short y, unsigned char* confirmed, int);
    void func_02080f8c(Menu* menu, short item, const char* text);
    void func_02080fa8(Menu* menu, short item, int value);
    void func_0208103c(Menu* menu, short item, short text);
    void func_0208108c(Menu* menu, short item);
    void func_020810a0(Menu* menu, int);
    void func_02081130(Menu* menu, short group, int);
    void func_02081164(Menu* menu, short group, int);
    void func_020813ec(Menu* menu, short group);
    Canvas* func_02081da8(Menu* menu, short group);
    void func_02081ea4(Menu* menu, short group, int);
    void func_02081ee4(KeyRepeat* repeat, unsigned short* buttons);
    unsigned short func_02081f20(KeyRepeat* repeat, int ticks);
    void func_0208203c(KeyRepeat* repeat);
    void func_020836e4(PartEntry* destination, PartEntry* source);
    void func_02086d88(Party* party, short item);
    void* func_02094a00();
    void func_02094b34(void* music, int, int, int, int);
    void func_02094b40();
    int func_02094b4c();
    void func_0209c3b4(void* sound, int);
    void func_0209c678(void* sound, int);
    void func_0209c830(void* sound, int);
    int func_0209ca2c(void* sound);
    void func_020a9ea4(void* save);
    int func_020aad1c(void* save, void* buffer, int, int);
    void func_020ac234(RecipeRecord* records);
    void func_020c54a4(int, int, int, int);
    void func_020c5588(int, int, int, int, int);
    void* func_020d6c00();
    int func_020dd4c4(signed char member, PotIngredient* item);
    void func_020de1d4(PotIngredient* item);
    int func_020de234(PotIngredient* item);
    void func_020de824(void* data);
    void func_020deef4(PartEntry* items, void* file, unsigned int size, short* ids, int count);
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, short id);
    void func_020e2490(void* choice, int, int, SpriteAnimationList* animations, SafeAllocator* allocator, int, int);
    void func_020e25e8(void* choice);
    void func_020e263c(void* choice, int ticks);
    void func_020e2794(void* choice, SpriteRenderer* renderer);
    void func_020e280c(void* choice, int);
    void func_020e2834(void* choice);
    int func_020e28dc(void* choice);
    void func_020e28f0(void* choice, short x, short y);
    int func_020e2918(void* choice);
    int func_020e2984(void* choice);
    void func_020e2cc4(void*, int);
    void func_020e2d24(void*, int, int);
    void func_020e4864(const char* input, char* output, int, int, int, int);
    void func_020e4bf4(void* name, int member);
    void func_020e526c(void* reader);
    const char** func_020e5294(void* reader, short id);
    void func_020e5604(void* reader, SafeAllocator* allocator, void* file, unsigned int size);
    int func_ov017_021959b4();
}

// The sprites and the palettes of the arrows of the count
static const short sCountArrowSprites[4] = {0xb, 0xc, 6, 7};
static const unsigned char sCountArrowPalettes[4] = {8, 0xa, 0xc, 0xe};
// The capacities of the 9 categories of items
static const unsigned short sCategorySizes[9] = {0x110, 0x30, 0x90, 0xc0, 0x50, 0x60, 0x70, 0x40, 0x98};
// Two sizes that nothing uses
extern const unsigned int data_ov006_0215ffbc = 0x800;
extern const unsigned int data_ov006_0215ffb8 = 0x800;
// The elements of the arrows of the count
static const short sCountArrows[5] = {0x1c, 0x1d, 0x1a, 0x1b, -1};
// The sizes of the allocators of the menu's files
static const unsigned int sAllocatorSizes[10] = {0x8800, 0x1800, 0x10400, 0x3400, 0x2c00, 0x1c00, 0x800, 0x610, 0x80, 0x12c};
// The lists of the party's bag that are the categories 0 to 7 of the ingredients
static const int sItemLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};
// The elements of the recipe book's buttons, their sprites and their palettes
static const short sBookButtons[4] = {0x41, 0x42, 0x26, -1};
static const short sBookButtonSprites[3] = {8, 9, 0xd};
static const unsigned char sBookButtonPalettes[3] = {0x10, 0x12, 0x14};
// The messages that show the name of the chosen ingredient, and the ones without the sound of the text
static const short sItemMessages[4] = {0x39, 0x3a, 0x3b, -1};
static const short sSilentMessages[5] = {0xc, 0x36, 0x37, 0x38, -1};
// The items of the 4 results before they're known
static const struct ResultItems
{
    short items_[4];
} sNoResultItems = {{-1, -1, -1, -1}};
// The sprite of the pot for each category of the ingredients
static const struct CategorySprites
{
    int sprites_[9];
} sCategorySprites = {{0, 1, 4, 2, 5, 3, 6, 7, 8}};

// Shows the layout of the recipe book's lists
static void SetLayoutBook(Layout* layout);
static LayoutElement* GetLayoutElement(Layout* layout, short id);

#define SHOW_ELEMENT(layout, id)                                \
    {                                                           \
        LayoutElement* element = GetLayoutElement(layout, id); \
        if (element != 0)                                       \
            element->flags_ |= LAYOUT_ELEMENT_FLAG_VISIBLE;     \
    }

#define HIDE_ELEMENT(layout, id)                                \
    {                                                           \
        LayoutElement* element = GetLayoutElement(layout, id); \
        if (element != 0)                                       \
            element->flags_ &= ~LAYOUT_ELEMENT_FLAG_VISIBLE;    \
    }

static void SetLayoutBook(Layout* layout)
{
    HIDE_ELEMENT(layout, 0x50);
    SHOW_ELEMENT(layout, 0x4f);
    HIDE_ELEMENT(layout, 0xe);
    SHOW_ELEMENT(layout, 0xf);
    HIDE_ELEMENT(layout, 0x15);
    HIDE_ELEMENT(layout, 0x41);
    HIDE_ELEMENT(layout, 0x42);
}

static LayoutElement* GetLayoutElement(Layout* layout, short id)
{
    LayoutElement* elements = layout->elements_;
    if (elements == 0)
        return 0;
    unsigned short count = layout->numElements_;
    if (count == 0)
        return 0;
    for (unsigned short i = 0; i < count; i++)
    {
        LayoutElement* element = &elements[i];
        if (element->id_ == id)
            return element;
    }
    return 0;
}

// Shows the layout of the choice of the ingredients
static void SetLayoutIngredients(Layout* layout)
{
    HIDE_ELEMENT(layout, 0x50);
    HIDE_ELEMENT(layout, 0x4f);
    HIDE_ELEMENT(layout, 0xe);
    HIDE_ELEMENT(layout, 0xf);
    SHOW_ELEMENT(layout, 0x15);
}

// The filter of the recipe book's buttons: a category of the recipes, or a kind of items
static void GetFilter(short id, signed char* category, signed char* kind)
{
    *kind = -1;
    switch (id)
    {
    case 0x48:
        *kind = 0;
        break;
    case 0x49:
        *kind = 1;
        break;
    case 0x4a:
        *kind = 2;
        break;
    case 0x4b:
        *kind = 3;
        break;
    case 0x4c:
        *kind = 4;
        break;
    case 0x4d:
        *kind = 5;
        break;
    case 0x4e:
        *kind = 6;
        break;
    case 0x4f:
        *kind = 7;
        break;
    case 0x50:
        *kind = 8;
        break;
    case 0x51:
        *kind = 9;
        break;
    case 0x52:
        *kind = 0xa;
        break;
    case 0x53:
        *kind = 0xb;
        break;
    case 0x40:
        *kind = 0xc;
        break;
    case 0x41:
        *category = 4;
        break;
    case 0x42:
        *category = 2;
        break;
    case 0x43:
        *category = 5;
        break;
    case 0x44:
        *category = 3;
        break;
    case 0x45:
        *category = 6;
        break;
    }
}

// Gives the item that alchemy made, and takes its ingredients
static void GiveResult(PotIngredient* result, Recipe* recipe, unsigned int times)
{
    Party* party = func_02010828(GameState::GetInstance());
    char data[0x24];
    SafeAllocator allocator;
    func_020de824(data);
    func_0207cbe8(&allocator);
    func_0207cbe8(&allocator);
    func_0207d300(&allocator, result->entry_.unk_18, (signed char)times, 0);
    func_0207cc0c(&allocator);
    for (unsigned char i = 0; i < times; i++)
    {
        for (unsigned char a = 0; a < recipe->amount0_; a++)
            func_02086d88(party, recipe->ingredients_[0]);
        for (unsigned char b = 0; b < recipe->amount1_; b++)
            func_02086d88(party, recipe->ingredients_[1]);
        for (unsigned char c = 0; c < recipe->amount2_; c++)
            func_02086d88(party, recipe->ingredients_[2]);
    }
}

// NONMATCHING: the C matches 97.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::Allocate(SafeAllocator* allocator, void* buffer)
{
    unsigned short sizes[9];
    memcpy(sizes, sCategorySizes, sizeof(sizes));

    items_ = (short**)allocator->Allocate(sizeof(short*) * 9);
    counts_ = (unsigned char**)allocator->Allocate(sizeof(unsigned char*) * 9);
    sizes_ = (unsigned short*)allocator->Allocate(sizeof(unsigned short) * 9);
    for (unsigned char i = 0; i < 9; i++)
    {
        unsigned short size = sizes[i];
        items_[i] = (short*)allocator->Allocate(size * 2);
        counts_[i] = (unsigned char*)allocator->Allocate(size);
        memset(items_[i], -1, size * 2);
        memset(counts_[i], 0, size);
        sizes_[i] = 0;
    }
    canvasBuffer_ = allocator->Allocate(0x4000);
    allocators_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator) * 10);
    menu_ = (Menu*)allocator->Allocate(sizeof(Menu));
    backgrounds_ = (BackgroundGraphics*)allocator->Allocate(sizeof(BackgroundGraphics) * 2);
    canvases_ = (Canvas*)allocator->Allocate(sizeof(Canvas) * 7);
    sprites_ = (Sprite*)allocator->Allocate(sizeof(Sprite) * 29);
    animations_ = (SpriteAnimationList*)allocator->Allocate(sizeof(SpriteAnimationList));
    pot_ = (AlchemyPot*)allocator->Allocate(sizeof(AlchemyPot));
    records_ = (RecipeRecord*)allocator->Allocate(sizeof(RecipeRecord) * 0x1d7);
    choice_ = allocator->Allocate(0x24);
    func_020e2490(choice_, 1, 1, animations_, allocator, 4, 0x40);
    (*(char**)((char*)choice_ + 0xc))[0x3e] = 1;
    for (unsigned char j = 0; j < 10; j++)
    {
        allocators_[j].ResetAllocatorPointer();
        unsigned int size = sAllocatorSizes[j];
        allocators_[j].CreateTypeA(allocator->Allocate(size), size);
        allocators_[j].Reset();
    }
    func_0207f84c(menu_);
    for (unsigned char k = 0; k < 2; k++)
        func_0204af64(&backgrounds_[k]);
    for (unsigned char l = 0; l < 7; l++)
        func_0204c684(&canvases_[l]);
    for (unsigned char m = 0; m < 29; m++)
        func_0205a198(&sprites_[m]);
    for (unsigned short n = 0; n < 0x1d7; n++)
    {
        RecipeRecord* record = &records_[n];
        record->id_ = -1;
        record->known_ = 0;
        record->made_ = 0;
        record->unk_2_2 = 0;
    }
    pot_->Initialize();
    pot_->Allocate(allocator, buffer);
    pot_->canvasBuffer_ = canvasBuffer_;
    pot_->itemNames_ = itemNames_;
    pot_->texts_ = &menuTexts_;
    if (flags_ & ALCHEMY_MENU_NO_SCENE)
        pot_->SetNo3D();
    func_020ac234(records_);
    texts_ = (char**)allocator->Allocate(sizeof(char*) * 16);
    for (int o = 0; o < 16; o++)
    {
        texts_[o] = (char*)allocator->Allocate(0x80);
        memset(texts_[o], 0, 0x80);
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10AlchemyPot10InitializeEv(); // AlchemyPot::Initialize
    void _ZN10AlchemyPot7SetNo3DEv(); // AlchemyPot::SetNo3D
    void _ZN10AlchemyPot8AllocateEP13SafeAllocatorPv(); // AlchemyPot::Allocate
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
}

asm void AlchemyMenu::Allocate(SafeAllocator* allocator, void* buffer)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x20
    mov r9, r1
    mov r10, r0
    mov r8, r2
    ldr r1, =sCategorySizes
    add r0, sp, #0xc
    mov r2, #0x12
    bl memcpy
    mov r0, r9
    mov r1, #0x24
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x48]
    mov r0, r9
    mov r1, #0x24
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x4c]
    mov r0, r9
    mov r1, #0x12
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x50]
    mov r5, #0x0
    add r11, sp, #0xc
    mvn r4, #0x0
    b @L02157778
@L02157704:
    mov r0, r5, lsl #0x1
    ldrh r6, [r11, r0]
    mov r0, r9
    mov r7, r6, lsl #0x1
    mov r1, r7
    bl _ZN13SafeAllocator8AllocateEj
    ldr r2, [r10, #0x48]
    mov r1, r6
    str r0, [r2, r5, lsl #0x2]
    mov r0, r9
    bl _ZN13SafeAllocator8AllocateEj
    ldr r3, [r10, #0x4c]
    mov r2, r7
    str r0, [r3, r5, lsl #0x2]
    ldr r0, [r10, #0x48]
    mov r1, r4
    ldr r0, [r0, r5, lsl #0x2]
    bl memset
    ldr r0, [r10, #0x4c]
    mov r2, r6
    ldr r0, [r0, r5, lsl #0x2]
    mov r1, #0x0
    bl memset
    ldr r2, [r10, #0x50]
    mov r1, r5, lsl #0x1
    mov r0, #0x0
    strh r0, [r2, r1]
    add r0, r5, #0x1
    and r5, r0, #0xff
@L02157778:
    cmp r5, #0x9
    blo @L02157704
    mov r0, r9
    mov r1, #0x4000
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x8]
    mov r0, r9
    mov r1, #0xc8
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0xc]
    mov r0, r9
    mov r1, #0x40
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x14]
    mov r0, r9
    mov r1, #0x40
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x1c]
    mov r0, r9
    mov r1, #0x620
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x20]
    ldr r1, =0x488
    mov r0, r9
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x24]
    mov r0, r9
    mov r1, #0x8
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x28]
    mov r0, r9
    mov r1, #0x12c0
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x10]
    ldr r1, =0x75c
    mov r0, r9
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x38]
    mov r0, r9
    mov r1, #0x24
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x18]
    mov r1, #0x1
    str r9, [sp, #0x0]
    mov r0, #0x4
    str r0, [sp, #0x4]
    mov r0, #0x40
    str r0, [sp, #0x8]
    ldr r0, [r10, #0x18]
    ldr r3, [r10, #0x28]
    mov r2, r1
    bl func_020e2490
    ldr r1, [r10, #0x18]
    mov r0, #0x1
    ldr r1, [r1, #0xc]
    mov r5, #0x0
    strb r0, [r1, #0x3e]
    ldr r4, =sAllocatorSizes
    mov r11, #0x14
    b @L021578b0
@L02157868:
    mul r7, r5, r11
    ldr r0, [r10, #0xc]
    add r0, r0, r7
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r6, [r4, r5, lsl #0x2]
    mov r0, r9
    mov r1, r6
    bl _ZN13SafeAllocator8AllocateEj
    mov r2, r6
    mov r1, r0
    ldr r0, [r10, #0xc]
    add r0, r0, r7
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    ldr r0, [r10, #0xc]
    add r0, r0, r7
    bl _ZN13SafeAllocator5ResetEv
    add r0, r5, #0x1
    and r5, r0, #0xff
@L021578b0:
    cmp r5, #0xa
    blo @L02157868
    ldr r0, [r10, #0x14]
    bl func_0207f84c
    mov r4, #0x0
    b @L021578dc
@L021578c8:
    ldr r0, [r10, #0x1c]
    add r0, r0, r4, lsl #0x5
    bl func_0204af64
    add r0, r4, #0x1
    and r4, r0, #0xff
@L021578dc:
    cmp r4, #0x2
    blo @L021578c8
    mov r5, #0x0
    mov r4, #0xe0
    b @L02157904
@L021578f0:
    ldr r0, [r10, #0x20]
    mla r0, r5, r4, r0
    bl func_0204c684
    add r0, r5, #0x1
    and r5, r0, #0xff
@L02157904:
    cmp r5, #0x7
    blo @L021578f0
    mov r5, #0x0
    mov r4, #0x28
    b @L0215792c
@L02157918:
    ldr r0, [r10, #0x24]
    mla r0, r5, r4, r0
    bl func_0205a198
    add r0, r5, #0x1
    and r5, r0, #0xff
@L0215792c:
    cmp r5, #0x1d
    blo @L02157918
    mvn r0, #0x0
    mov r2, #0x0
    add r3, r0, #0x1d8
    ldr r4, =0xffff0003
    b @L02157988
@L02157948:
    ldr r5, [r10, #0x38]
    mov r1, r2, lsl #0x2
    strh r0, [r5, r1]
    add r1, r5, r2, lsl #0x2
    ldrh r5, [r1, #0x2]
    add r2, r2, #0x1
    mov r2, r2, lsl #0x10
    bic r5, r5, #0x1
    strh r5, [r1, #0x2]
    ldrh r5, [r1, #0x2]
    mov r2, r2, lsr #0x10
    bic r5, r5, #0x2
    strh r5, [r1, #0x2]
    ldrh r5, [r1, #0x2]
    and r5, r5, r4
    strh r5, [r1, #0x2]
@L02157988:
    cmp r2, r3
    blo @L02157948
    ldr r0, [r10, #0x10]
    bl _ZN10AlchemyPot10InitializeEv
    ldr r0, [r10, #0x10]
    mov r1, r9
    mov r2, r8
    bl _ZN10AlchemyPot8AllocateEP13SafeAllocatorPv
    ldr r2, [r10, #0x8]
    ldr r0, [r10, #0x10]
    add r1, r10, #0x170
    str r2, [r0, #0x1a4]
    ldr r0, [r10, #0x10]
    add r2, r10, #0x158
    str r1, [r0, #0x1ac]
    ldr r1, [r10, #0x10]
    add r0, r10, #0x300
    str r2, [r1, #0x1b0]
    ldrh r0, [r0, #0x94]
    tst r0, #0x2
    beq @L021579e4
    ldr r0, [r10, #0x10]
    bl _ZN10AlchemyPot7SetNo3DEv
@L021579e4:
    ldr r0, [r10, #0x38]
    bl func_020ac234
    mov r0, r9
    mov r1, #0x40
    bl _ZN13SafeAllocator8AllocateEj
    mov r5, #0x0
    mov r4, #0x80
    str r0, [r10, #0x4]
    mov r7, r5
    mov r6, r4
    b @L02157a3c
@L02157a10:
    mov r0, r9
    mov r1, r4
    bl _ZN13SafeAllocator8AllocateEj
    ldr r2, [r10, #0x4]
    mov r1, r7
    str r0, [r2, r5, lsl #0x2]
    ldr r0, [r10, #0x4]
    mov r2, r6
    ldr r0, [r0, r5, lsl #0x2]
    bl memset
    add r5, r5, #0x1
@L02157a3c:
    cmp r5, #0x10
    blt @L02157a10
    add sp, sp, #0x20
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void AlchemyMenu::Initialize()
{
    char* flags = func_0205ec34();
    if (!func_0206dfb0(flags, flags + 0x8c, 0x777))
        func_0206df6c(flags, flags + 0x8c, 0x777, 1);
    textPosition_ = 0;
    showResult_ = 0;
    resultTask_ = -1;
    fadeTimer_ = 0;
    nextStep_ = 0;
    canvasBuffer_ = 0;
    allocators_ = 0;
    pot_ = 0;
    menu_ = 0;
    choice_ = 0;
    backgrounds_ = 0;
    canvases_ = 0;
    sprites_ = 0;
    animations_ = 0;
    recipes_ = 0;
    pageStart_ = 0;
    recipe_ = 0;
    records_ = 0;
    cursor_ = 0;
    items_ = 0;
    counts_ = 0;
    sizes_ = 0;
    func_0204af64(&subBackground_);
    ingredients_.Initialize();
    func_02081ee4(&repeat_, &buttons_);
    func_0205a444(&renderer_);
    layout_.Initialize();
    func_02071be8(&table_);
    func_020dfc40(&menuTexts_);
    for (unsigned char i = 0; i < 4; i++)
        results_[i].Initialize();
    menuResult_ = 0;
    task_ = -1;
    unk_358 = -1;
    unk_35c = 0;
    previousCursor_ = -1;
    mainCursor_ = -1;
    categoryCursor_ = -1;
    itemCursor_ = -1;
    bookCursor_ = -1;
    filterCursor_ = -1;
    recipeCursor_ = -1;
    choiceCursor_ = -1;
    group_ = -1;
    item_ = -1;
    categories_[2] = 0;
    categories_[1] = 0;
    categories_[0] = 0;
    chosenItems_[2] = -1;
    chosenItems_[1] = chosenItems_[2];
    chosenItems_[0] = chosenItems_[1];
    message_ = -1;
    messageLength_ = 0;
    successRate_ = 0;
    filterCategory_ = -1;
    filterKind_ = -1;
    sort_ = 0;
    times_ = 0;
    page_ = 0;
    pages_ = 0;
    category_ = 0;
    count_ = 0;
    chosenCounts_[2] = 0;
    chosenCounts_[1] = 0;
    chosenCounts_[0] = 0;
    state_ = 0;
    step_ = 0;
    unk_391 = 0;
    messageStep_ = 0;
    repeatDelay_ = 0;
    flags_ = 0;
    female_ = 0;
    background_ = 0;
    female_ = GameState::GetInstance()->GetProtagonist()->partyData_->appearance_.female_;
    textSound_ = 0;
    textSoundOn_ = 1;
    textSoundTimer_ = 0;
    textSoundPlaying_ = 0;
    textSoundState_ = -1;
    saved_ = 0;
    arrowUp_ = arrowDown_ = 0;
    resetBlend_ = 0;
    closing_ = 0;
    closeRequested_ = 0;
    arrowTimer_ = 0;
}

void PotIngredient::Initialize()
{
    func_020de1d4(this);
    memset(model_, 0, sizeof(model_));
    memset(unk_40, 0, sizeof(unk_40));
    entry_.model_ = (PartModelInfo*)model_;
    *(void**)&entry_.unk_4 = unk_40;
    item_ = -1;
}

void AlchemyMenu::Finish()
{
    if (pot_ != 0)
    {
        pot_->Finish();
        pot_ = 0;
    }
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    if (unk_358 >= 0)
    {
        loader->RemoveTask(unk_358);
        unk_358 = -1;
    }
    ingredients_.Finish();
    *(int*)(func_020421a0() + 0x2d8) = 0;
    if (allocators_ == 0)
        return;
    for (unsigned char i = 0; i < 10; i++)
    {
        if (allocators_[i].GetSignedAllocator() != 0)
            allocators_[i].Destroy();
    }
}

#ifndef NONMATCHING
// The table of states of Update() and its guard, for its assembly, which can't name a function's static variable: its
// pointers to member functions are their functions and the adjustments of `this`, and the last one is null, which
// Update() copies from __ptmf_null the first time
extern "C"
{
    extern const int __ptmf_null[3];
    void _ZN11AlchemyMenu10State_LoadEv();
    void _ZN11AlchemyMenu12State_FadeInEv();
    void _ZN11AlchemyMenu10State_BookEv();
    void _ZN11AlchemyMenu14State_BookListEv();
    void _ZN11AlchemyMenu10State_MainEv();
    void _ZN11AlchemyMenu17State_Ingredient1Ev();
    void _ZN11AlchemyMenu17State_Ingredient2Ev();
    void _ZN11AlchemyMenu17State_Ingredient3Ev();
    void _ZN11AlchemyMenu10State_MakeEv();
    void _ZN11AlchemyMenu13State_RecipesEv();
    void _ZN11AlchemyMenu16State_RecipeListEv();
    void _ZN11AlchemyMenu16State_MakeRecipeEv();
    void _ZN11AlchemyMenu13State_FadeOutEv();
}

static struct StateEntry
{
    void (*function_)();
    int adjustment_;
} sStates[14] = {
    {_ZN11AlchemyMenu10State_LoadEv, 0},
    {_ZN11AlchemyMenu12State_FadeInEv, 0},
    {_ZN11AlchemyMenu10State_BookEv, 0},
    {_ZN11AlchemyMenu14State_BookListEv, 0},
    {_ZN11AlchemyMenu10State_MainEv, 0},
    {_ZN11AlchemyMenu17State_Ingredient1Ev, 0},
    {_ZN11AlchemyMenu17State_Ingredient2Ev, 0},
    {_ZN11AlchemyMenu17State_Ingredient3Ev, 0},
    {_ZN11AlchemyMenu10State_MakeEv, 0},
    {_ZN11AlchemyMenu13State_RecipesEv, 0},
    {_ZN11AlchemyMenu16State_RecipeListEv, 0},
    {_ZN11AlchemyMenu16State_MakeRecipeEv, 0},
    {_ZN11AlchemyMenu13State_FadeOutEv, 0},
    {0, 0},
};
static int sStatesGuard;
#endif

// The strings of the file, which the compiler pools in this order. A function is in assembly for now
// (NONMATCHING), which can't reference the compiler's pool, so they're in an array for it
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] =
    "data/bin/menu/str_ren.gp2\0"
    "str_ren_<LG>.nat\0"
    "data/bin/recipe.gp2\0"
    "recipe_<LG>.bin\0"
    "data/ani/bg_kamael.pac\0"
    "data/ani/lay_rrb.gp2\0"
    "lay_rrb_<LG>.lia\0"
    "data/ani/orrb.gp2\0"
    "orrb_<LG>.pac\0"
    "data/prm/itemname.gp2\0"
    "itemname_<LG>.nat\0"
    "data/bin/menu/bm_rrb.gp2\0"
    "bm_rrb\0"
    "data/ani/d_%c%03d.spr";
#define STRING(offset, text) (sStrings + (offset))
#endif

// NONMATCHING: the C matches 96.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original references the table of states by its symbol when it initializes it, and the C by its section, with one
// more word in the pool
#ifdef NONMATCHING
int AlchemyMenu::Update(int ticks)
{
    ticks_ = ticks;
    if (func_ov017_021959b4())
        RequestClose();
    if (!(flags_ & ALCHEMY_MENU_SAVING) && closing_ != 0)
    {
        if (cursor_ != 0)
            *cursor_ = -1;
        cursor_ = 0;
        state_ = AlchemyMenuState_FadeOut;
        step_ = 0;
        closing_ = 0;
    }
    unsigned char state = state_;
    if ((unsigned int)(state <= 4 ? 1 : 0) <= state)
    {
        arrowTimer_ += ticks;
        arrowTimer_ &= 0x3f;
    }
    if (!func_0209ca2c(data_02109bf4))
        saved_ = 0;
    pot_->Update(ticks);
    Menu* menu = menu_;
    if (menu != 0)
        func_0207fc6c(menu, ticks);
    if (message_ >= 0)
    {
        arrowTimer_ = 0;
        UpdateMessage();
        return 0;
    }
    if (flags_ & ALCHEMY_MENU_100)
    {
        if (IsMessageAdvanced())
        {
            func_0207fdcc(menu, 0);
            func_0207fdcc(menu, 1);
            flags_ &= ~ALCHEMY_MENU_100;
        }
        return 0;
    }
    if (pot_->flags_ & (ALCHEMY_POT_ANIMATION_IN | ALCHEMY_POT_ANIMATION_WORK | ALCHEMY_POT_ANIMATION_OUT))
    {
        arrowTimer_ = 0;
        return 0;
    }
    if (cursor_ != 0)
    {
        func_02081f20(&repeat_, ticks);
        previousCursor_ = *cursor_;
        menuResult_ = func_020800fc(menu, cursor_, previousCursor_, buttons_, unk_aa, (flags_ & ALCHEMY_MENU_PAGES) ? 1 : 0);
        menu->cursor_ = *cursor_;
        if (menuResult_ != 0)
            func_020804fc(menu, group_);
        if (previousCursor_ != *cursor_)
            func_020813ec(menu, group_);
    }
    if (choice_ != 0 && func_020e28dc(choice_))
        func_020e263c(choice_, ticks_);
    static void (AlchemyMenu::*states[14])() = {
        &AlchemyMenu::State_Load,        &AlchemyMenu::State_FadeIn,      &AlchemyMenu::State_Book,
        &AlchemyMenu::State_BookList,    &AlchemyMenu::State_Main,        &AlchemyMenu::State_Ingredient1,
        &AlchemyMenu::State_Ingredient2, &AlchemyMenu::State_Ingredient3, &AlchemyMenu::State_Make,
        &AlchemyMenu::State_Recipes,     &AlchemyMenu::State_RecipeList,  &AlchemyMenu::State_MakeRecipe,
        &AlchemyMenu::State_FadeOut,     0,
    };
    if (states[state_] == 0)
        return 1;
    (this->*states[state_])();
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10AlchemyPot6UpdateEi(); // AlchemyPot::Update
    void _ZN11AlchemyMenu12RequestCloseEv(); // AlchemyMenu::RequestClose
    void _ZN11AlchemyMenu13UpdateMessageEv(); // AlchemyMenu::UpdateMessage
    void _ZN11AlchemyMenu17IsMessageAdvancedEv(); // AlchemyMenu::IsMessageAdvanced
}

asm int AlchemyMenu::Update(int ticks)
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x8
    mov r6, r0
    mov r5, r1
    str r5, [r6, #0x34c]
    bl func_ov017_021959b4
    cmp r0, #0x0
    beq @L02157da4
    mov r0, r6
    bl _ZN11AlchemyMenu12RequestCloseEv
@L02157da4:
    add r0, r6, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x200
    bne @L02157de8
    ldrb r0, [r6, #0x433]
    cmp r0, #0x0
    beq @L02157de8
    ldr r1, [r6, #0x44]
    cmp r1, #0x0
    mvnne r0, #0x0
    strneh r0, [r1, #0x0]
    mov r1, #0x0
    str r1, [r6, #0x44]
    mov r0, #0xc
    strb r0, [r6, #0x38f]
    strb r1, [r6, #0x390]
    strb r1, [r6, #0x433]
@L02157de8:
    ldrb r0, [r6, #0x38f]
    cmp r0, #0x4
    movls r1, #0x1
    movhi r1, #0x0
    cmp r1, r0
    bhi @L02157e1c
    add r0, r6, #0x400
    ldrsb r1, [r0, #0x2c]
    add r1, r1, r5
    strb r1, [r6, #0x42c]
    ldrsb r0, [r0, #0x2c]
    and r0, r0, #0x3f
    strb r0, [r6, #0x42c]
@L02157e1c:
    ldr r0, =data_02109bf4
    bl func_0209ca2c
    cmp r0, #0x0
    moveq r0, #0x0
    streqb r0, [r6, #0x42f]
    ldr r0, [r6, #0x10]
    mov r1, r5
    bl _ZN10AlchemyPot6UpdateEi
    ldr r4, [r6, #0x14]
    cmp r4, #0x0
    beq @L02157e54
    mov r0, r4
    mov r1, r5
    bl func_0207fc6c
@L02157e54:
    add r0, r6, #0x300
    ldrsh r1, [r0, #0x7e]
    cmp r1, #0x0
    blt @L02157e7c
    mov r1, #0x0
    mov r0, r6
    strb r1, [r6, #0x42c]
    bl _ZN11AlchemyMenu13UpdateMessageEv
    mov r0, #0x0
    b @L02158020
@L02157e7c:
    ldrh r0, [r0, #0x94]
    tst r0, #0x100
    beq @L02157ec8
    mov r0, r6
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L02157ec0
    mov r0, r4
    mov r1, #0x0
    bl func_0207fdcc
    mov r0, r4
    mov r1, #0x1
    bl func_0207fdcc
    add r0, r6, #0x300
    ldrh r1, [r0, #0x94]
    bic r1, r1, #0x100
    strh r1, [r0, #0x94]
@L02157ec0:
    mov r0, #0x0
    b @L02158020
@L02157ec8:
    ldr r0, [r6, #0x10]
    add r0, r0, #0xa00
    ldrh r0, [r0, #0xe2]
    tst r0, #0x380
    movne r0, #0x0
    strneb r0, [r6, #0x42c]
    bne @L02158020
    ldr r0, [r6, #0x44]
    cmp r0, #0x0
    beq @L02157f8c
    mov r1, r5
    add r0, r6, #0x9c
    bl func_02081f20
    ldr r1, [r6, #0x44]
    add r0, r6, #0x300
    ldrsh r1, [r1, #0x0]
    strh r1, [r0, #0x5e]
    ldrh r0, [r0, #0x94]
    ldrb r2, [r6, #0xaa]
    add r1, r6, #0x300
    tst r0, #0x4
    movne r3, #0x1
    moveq r3, #0x0
    stmia sp, {r2, r3}
    ldrsh r2, [r1, #0x5e]
    ldrh r3, [r6, #0xa8]
    ldr r1, [r6, #0x44]
    mov r0, r4
    bl func_020800fc
    str r0, [r6, #0x350]
    ldr r0, [r6, #0x44]
    ldrsh r0, [r0, #0x0]
    strh r0, [r4, #0x36]
    ldr r0, [r6, #0x350]
    cmp r0, #0x0
    beq @L02157f68
    add r0, r6, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_020804fc
@L02157f68:
    ldr r1, [r6, #0x44]
    add r0, r6, #0x300
    ldrsh r2, [r0, #0x5e]
    ldrsh r1, [r1, #0x0]
    cmp r2, r1
    beq @L02157f8c
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_020813ec
@L02157f8c:
    ldr r0, [r6, #0x18]
    cmp r0, #0x0
    beq @L02157fb0
    bl func_020e28dc
    cmp r0, #0x0
    beq @L02157fb0
    ldr r0, [r6, #0x18]
    ldr r1, [r6, #0x34c]
    bl func_020e263c
@L02157fb0:
    ldr r2, =sStatesGuard
    ldr r5, [r2, #0x0]
    tst r5, #0x1
    bne @L02157fe0
    ldr r1, =__ptmf_null
    ldr r0, =sStates
    ldr r4, [r1, #0x0]
    ldr r3, [r1, #0x4]
    orr r1, r5, #0x1
    str r4, [r0, #0x68]
    str r3, [r0, #0x6c]
    str r1, [r2, #0x0]
@L02157fe0:
    ldrb r2, [r6, #0x38f]
    ldr r1, =sStates
    ldr r0, [r1, r2, lsl #0x3]
    cmp r0, #0x0
    moveq r0, #0x1
    beq @L02158020
    add r1, r1, r2, lsl #0x3
    ldr r0, [r1, #0x4]
    tst r0, #0x1
    add r0, r6, r0, asr #0x1
    ldrne r2, [r0, #0x0]
    ldrne r1, [r1, #0x0]
    ldrne r1, [r2, r1]
    ldreq r1, [r1, #0x0]
    blx r1
    mov r0, #0x0
@L02158020:
    add sp, sp, #0x8
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void AlchemyMenu::Draw3D()
{
    if (state_ == AlchemyMenuState_Load)
        return;
    pot_->Draw3D();
}

// Places a sprite and draws it
static void DrawSprite(SpriteRenderer* renderer, Sprite* sprite, int x, int y, unsigned char unk22,
                       unsigned char unk26)
{
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = unk22;
    sprite->unk_26 = unk26;
    func_0205ac40(renderer, sprite);
}

// Whether a group of the menu is shown
static int IsGroupShown(Menu* menu, short group)
{
    if (func_02081da8(menu, group) != 0 && func_02080c3c(menu, group))
        return 1;
    return 0;
}

void AlchemyMenu::Draw()
{
    if (state_ != AlchemyMenuState_Load)
    {
        if (IsGroupShown(menu_, 0))
            DrawSprite(&renderer_, &sprites_[26], 2, 0x61, 0x64, 1);
        if (IsGroupShown(menu_, 1))
        {
            DrawSprite(&renderer_, &sprites_[27], 2, 0x74, 0x66, 1);
            if (arrowTimer_ > 0x1f)
                DrawSprite(&renderer_, &sprites_[28], 0x78, 0xb6, 0x63, 1);
        }
        else
        {
            arrowTimer_ = 0;
        }
        pot_->Draw();
        func_0204b010(&subBackground_, 0);
        void* layer = func_0204af14(&subBackground_, background_);
        if (layer != 0)
            func_0204b938(&subBackground_, layer, 0, 0, 0xffff);
        if (background_ == 1)
        {
            unsigned int kind = func_0200fb08(GameState::GetInstance());
            unsigned char tiles = 1;
            switch (kind)
            {
            case 2:
                tiles = 3;
                break;
            case 4:
                tiles = 4;
                break;
            case 3:
                tiles = 5;
                break;
            case 5:
                tiles = 6;
                break;
            }
            if (tiles > 1)
                func_0204b8d0(&subBackground_, tiles, 0, 0, 0x16, 2, 9, 2, 0xffff);
        }
        Menu* menu = menu_;
        func_0207fcb8(menu);
        func_0207fd00(menu);
        func_0207fe80(menu, 2, 1, 1);
        func_0204b04c(&subBackground_, 0);
        func_0207fd44(menu);
        if (flags_ & ALCHEMY_MENU_SAVING)
        {
            arrowTimer_ = 0;
            func_0205a370(animations_, 1);
            SpriteAnimation* animation = func_0205a3d0(animations_, 0);
            if (animation != 0)
                animation->flags_ &= ~8;
            animation = func_0205a3d0(animations_, 1);
            if (animation != 0)
                animation->flags_ |= 8;
            func_0205a330(animations_, ticks_);
            animation = func_0205a3d0(animations_, 1);
            if (animation != 0)
            {
                animation->x_ = 0xd7;
                animation->y_ = 0x96;
            }
            func_0205ae8c(&renderer_);
        }
        else
        {
            SpriteAnimation* animation = func_0205a3d0(animations_, 1);
            if (animation != 0)
                animation->flags_ &= ~8;
        }
        if (message_ < 0)
        {
            if (choice_ != 0 && func_020e28dc(choice_))
                func_020e2794(choice_, &renderer_);
            else
                DrawChoice();
        }
        DrawButtons();
        DrawCountArrows();
        DrawBookButtons();
        arrowDown_ = 0;
        arrowUp_ = 0;
    }
    if (showResult_ != 0)
    {
        unsigned char state = state_;
        if (state != AlchemyMenuState_Make && state != AlchemyMenuState_MakeRecipe)
            return;
        short x;
        short y;
        func_020807c4(menu_, 0x12, &x, &y);
        Sprite* sprite = &sprites_[17];
        if (sprite != 0)
        {
            sprite->x_ = (x + 4) << 12;
            sprite->y_ = (y + 4) << 12;
            sprite->unk_22 = 0x32;
            sprite->unk_26 = 1;
            func_0205ac40(&renderer_, sprite);
        }
        unsigned int vram = func_0203be4c(func_0203bd08());
        resultSprite_.unk_4c = 0;
        resultSprite_.unk_14 = vram + 0x1b8;
        resultSprite_.unk_44 = 0x37;
        func_02076988(&resultSprite_, 0x1000, 0x1000);
        func_02075db0(&resultSprite_, x + 8, y + 8);
    }
}

void AlchemyMenu::DrawSub()
{
    if (state_ == AlchemyMenuState_Load)
        return;
    unsigned short* screen = (unsigned short*)GetSubBG0ScreenBase();
    memset(screen, 0, 0x800);
    if (IsGroupShown(menu_, 1))
    {
        Canvas* canvas = func_02081da8(menu_, 1);
        if (canvas == 0)
            return;
        short x;
        short y;
        void* layer = (char*)canvas + 0xc8;
        if (layer == 0)
            return;
        x = canvas->x_;
        y = canvas->y_;
        BackgroundGraphics background;
        func_0204af64(&background);
        background.unk_1c_0_ = 1;
        background.unk_1c_4_ = 0;
        *(unsigned short**)&background.unk_0[0x14] = screen;
        func_0204b5e8(&background, 0, 0);
        func_0204b938(&background, layer, x, y, 0xffff);
    }
    pot_->DrawSub();
    if (resetBlend_ != 0)
    {
        pot_->OpenWindow();
        pot_->ShowNames(1);
        resetBlend_ = 0;
    }
    func_0204b088(&subBackground_, 0);
    if (choice_ != 0)
    {
        void* window = *(void**)((char*)choice_ + 0x10);
        func_020e2cc4((char*)window + 0x28, func_020e28dc(choice_));
        func_020e2834(choice_);
    }
    if (menu_ != 0)
        func_0207fd88(menu_);
}

void AlchemyMenu::RequestClose()
{
    if (closeRequested_ == 0)
    {
        closeRequested_ = 1;
        closing_ = 1;
    }
}

void AlchemyMenu::DrawChoice()
{
    if (state_ == AlchemyMenuState_Load || cursor_ == 0)
        return;
    if (group_ < 0)
        return;
    Canvas* canvas = func_02081da8(menu_, group_);
    if (canvas == 0)
        return;
    if (!func_0204c7e0(canvas) || choice_ == 0)
        return;
    if (func_020e28dc(choice_))
        return;
    short x;
    short y;
    func_020809c4(menu_, group_, *cursor_, &x, &y);
    func_020e263c(choice_, ticks_);
    x -= 0x10;
    y -= 3;
    func_020e28f0(choice_, x, y);
    func_0205ae8c(&renderer_);
}

void AlchemyMenu::DrawButtons()
{
    if (!(flags_ & ALCHEMY_MENU_ITEMS))
        return;
    short x;
    short y;
    layout_.GetPosition(0x78, &x, &y);
    Sprite* sprite = &sprites_[10];
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0xc;
    sprite->unk_25 = 9;
    sprite->unk_26 = 2;
    if (chosenCounts_[0] > 1 || chosenCounts_[1] >= 1)
        sprite->unk_25 = 8;
    func_0205ac40(&renderer_, sprite);
    layout_.GetPosition(0x10, &x, &y);
    sprite = &sprites_[9];
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0xe;
    sprite->unk_26 = 2;
    func_0205ac40(&renderer_, sprite);
    layout_.GetPosition(0x25, &x, &y);
    sprite = &sprites_[15];
    if (!(pot_->window_.flags_ & ITEM_INFO_WINDOW_NAMES))
        sprite = &sprites_[16];
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x10;
    sprite->unk_26 = 2;
    func_0205ac40(&renderer_, sprite);
}

void AlchemyMenu::DrawCountArrows()
{
    if (!(flags_ & ALCHEMY_MENU_COUNT))
        return;
    short ids[5];
    memcpy(ids, sCountArrows, sizeof(ids));
    if (state_ == AlchemyMenuState_RecipeList)
    {
        ids[0] = 0x1f;
        ids[1] = 0x20;
        ids[2] = 0x21;
        ids[3] = 0x22;
    }
    for (unsigned char i = 0; ids[i] >= 0; i++)
    {
        short x;
        short y;
        layout_.GetPosition(ids[i], &x, &y);
        short index = sCountArrowSprites[i];
        Sprite* sprite = &sprites_[index];
        if (index == 0xb && arrowUp_ != 0)
        {
            x++;
            y++;
        }
        if (index == 0xc && arrowDown_ != 0)
        {
            x++;
            y++;
        }
        sprite->x_ = x << 12;
        sprite->y_ = y << 12;
        sprite->unk_22 = sCountArrowPalettes[i];
        func_0205ac40(&renderer_, sprite);
    }
}

void AlchemyMenu::DrawBookButtons()
{
    if (!(flags_ & ALCHEMY_MENU_BOOK))
        return;
    if (func_02081da8(menu_, 1) != 0)
        return;
    for (unsigned char i = 0; sBookButtons[i] >= 0; i++)
    {
        short id = sBookButtons[i];
        if (layout_.IsVisible(id))
        {
            short x;
            short y;
            layout_.GetPosition(id, &x, &y);
            short index = sBookButtonSprites[i];
            Sprite* sprite = &sprites_[index];
            if (i == 2 && !(pot_->window_.flags_ & ITEM_INFO_WINDOW_NAMES))
                sprite = &sprites_[index + 1];
            sprite->x_ = x << 12;
            sprite->y_ = y << 12;
            sprite->unk_22 = sBookButtonPalettes[i];
            sprite->unk_26 = 2;
            if (index == 8)
                sprite->unk_25 = 0xb;
            else if (index == 9)
                sprite->unk_25 = 1;
            func_0205ac40(&renderer_, sprite);
        }
    }
}

unsigned char AlchemyMenu::IsConfirmed()
{
    unsigned char confirmed = 0;
    if (func_02012444(data_02114e30, 1))
        confirmed = 1;
    if ((flags_ & ALCHEMY_MENU_NO_SCENE) && func_02012444(data_02114e30, 0x400))
        confirmed = 1;
    if (choice_ != 0 && func_020e28dc(choice_))
    {
        int choice = func_020e2918(choice_);
        if (choice >= 0)
        {
            confirmed = 1;
            *cursor_ = choice + 0x22;
        }
    }
    else if (data_02114e54.touching_ && cursor_ != 0)
    {
        int x;
        int y;
        func_02012a84(&data_02114e54, &x, &y);
        previousCursor_ = *cursor_;
        int item = func_02080dd4(menu_, group_, x, y, &confirmed, 1);
        if (item < 0)
            return 0;
        *cursor_ = item;
        short cursor = *cursor_;
        if (previousCursor_ != cursor)
        {
            menu_->cursor_ = cursor;
            func_020813ec(menu_, group_);
        }
    }
    return confirmed;
}

unsigned char AlchemyMenu::IsCancelled()
{
    unsigned char cancelled = 0;
    if (func_02012444(data_02114e30, 2))
        cancelled = 1;
    if (choice_ != 0 && func_020e28dc(choice_))
    {
        if (func_020e2984(choice_))
            cancelled = 1;
    }
    else if (data_02114e54.touching_)
    {
        int x;
        int y;
        func_02012a84(&data_02114e54, &x, &y);
        if (!func_02080d54(menu_, group_, x, y))
            cancelled = 1;
    }
    return cancelled;
}

void AlchemyMenu::CheckClose()
{
    if (!func_02012444(data_02114e30, 0x800))
        return;
    if (cursor_ != 0)
        *cursor_ = -1;
    cursor_ = 0;
    state_ = AlchemyMenuState_FadeOut;
    step_ = 0;
}

unsigned char AlchemyMenu::IsMessageAdvanced()
{
    unsigned char advanced;
    unsigned char touching = data_02114e54.touching_;
    advanced = 0;
    if (func_02012444(data_02114e30, 0x7f3) || touching)
        advanced = 1;
    return advanced;
}

void AlchemyMenu::CountPages()
{
    Recipe* recipe = recipes_;
    unsigned short count = 0;
    while (recipe != 0)
    {
        recipe = recipe->next_;
        count++;
    }
    pages_ = (count + 15) / 16;
    if (pages_ == 0)
        pages_ = 1;
    page_ = 0;
}

void AlchemyMenu::SetPage(Recipe* recipe)
{
    Recipe* entry = recipes_;
    Recipe* start = entry;
    signed char i = 0;
    while (entry != 0)
    {
        if (i % 16 == 0)
        {
            start = entry;
            i = 0;
        }
        if (entry == recipe)
            break;
        entry = entry->next_;
        i++;
    }
    pageStart_ = start;
}

Recipe* AlchemyMenu::GetPageStart(unsigned char page)
{
    Recipe* recipe = recipes_;
    Recipe* result = recipe;
    short target = page * 16;
    for (short i = 0; recipe != 0; i++)
    {
        if (i == target)
        {
            result = recipe;
            break;
        }
        recipe = recipe->next_;
    }
    return result;
}

Recipe* AlchemyMenu::GetRecipe(short index)
{
    Recipe* recipe = pageStart_;
    short i = 0;
    while (recipe != 0 && index != 0)
    {
        if (recipe->next_ == 0)
        {
            recipeCursor_ = i + 0x29;
            break;
        }
        recipe = recipe->next_;
        index--;
        i++;
    }
    return recipe;
}

void AlchemyMenu::LoadInventory()
{
    unsigned short sizes[9];
    memcpy(sizes, sCategorySizes, sizeof(sizes));

    for (unsigned char i = 0; i < 9; i++)
    {
        unsigned short size = sizes[i];
        memset(items_[i], -1, size * 2);
        memset(counts_[i], 0, size);
        sizes_[i] = 0;
    }
    GameState* gameState = GameState::GetInstance();
    Party* party = func_02010828(gameState);
    for (unsigned short j = 0; j < 0x98; j++)
        AddItem(8, *(short*)((char*)party + 0xc + j * 2), *((char*)party + 0x13c + j));
    for (unsigned char k = 0; k < party->count_; k++)
    {
        GameObject* member = (GameObject*)func_0200ff1c(gameState, party->members_[k]);
        if (member != 0)
        {
            unsigned short* items = member->partyData_->unk_454;
            for (unsigned char l = 0; l < 8; l++)
                AddItem(8, items[l], 1);
        }
    }
    for (unsigned char m = 0; m < 8; m++)
    {
        int list = sItemLists[m];
        short count = func_0207c620((char*)party + 0x1d4, list);
        short* listItems = func_0207c5f8((char*)party + 0x1d4, list);
        unsigned char* listCounts = func_0207c60c((char*)party + 0x1d4, list);
        for (short n = 0; n < count; n++)
            AddItem(m, listItems[n], listCounts[n]);
    }
    ingredients_.SetTable(&table_);
    ingredients_.SetItems(items_, counts_, sizes_);
}

void AlchemyMenu::AddItem(unsigned int category, short item, unsigned char count)
{
    if (item <= 0 || count == 0)
        return;
    short* items = items_[category];
    unsigned char* counts = counts_[category];
    unsigned short* size = &sizes_[category];
    unsigned short sizes[9];
    memcpy(sizes, sCategorySizes, sizeof(sizes));
    unsigned short capacity = sizes[category];
    for (unsigned short i = 0; i < capacity; i++)
    {
        short entry = items[i];
        if (entry <= 0)
        {
            items[i] = item;
            counts[i] = count;
            (*size)++;
            return;
        }
        if (entry == item)
        {
            counts[i] += count;
            return;
        }
    }
}

void AlchemyMenu::ReturnIngredient()
{
    for (signed char i = 2; i >= 0; i--)
    {
        short item = chosenItems_[i];
        if (item > 0)
        {
            AddItem((unsigned char)categories_[i], item, chosenCounts_[i]);
            categories_[i] = 0;
            chosenItems_[i] = -1;
            chosenCounts_[i] = 0;
            return;
        }
    }
}

void AlchemyMenu::TakeIngredient(short category, short item, unsigned char count)
{
    short* items = items_[category];
    unsigned char* counts = counts_[category];
    unsigned short size = sizes_[category];
    for (unsigned short i = 0; i < size; i++)
    {
        if (item == items[i])
            counts[i] -= count;
    }
    for (unsigned char j = 0; j < 3; j++)
    {
        if (chosenItems_[j] <= 0)
        {
            categories_[j] = category;
            chosenItems_[j] = item;
            chosenCounts_[j] = count;
            return;
        }
    }
}

short* AlchemyMenu::GetCategoryItems()
{
    short* items = 0;
    short category = categoryCursor_ - 0x5b;
    if (category >= 0)
        items = items_[category];
    return items;
}

unsigned char* AlchemyMenu::GetCategoryCounts()
{
    unsigned char* counts = 0;
    short category = categoryCursor_ - 0x5b;
    if (category >= 0)
        counts = counts_[category];
    return counts;
}

unsigned short AlchemyMenu::GetCategorySize()
{
    unsigned short size = 0;
    short category = categoryCursor_ - 0x5b;
    if (category >= 0)
        size = sizes_[category];
    return size;
}

int AlchemyMenu::HasCategoryItems()
{
    short* items = GetCategoryItems();
    unsigned short size = GetCategorySize();
    int found = 0;
    if (items != 0)
    {
        for (unsigned short i = 0; i < size; i++)
        {
            if (items[i] > 0)
            {
                found = 1;
                break;
            }
        }
    }
    return found;
}

void AlchemyMenu::GetSelectedItem(unsigned char* category, short* item, unsigned char* count)
{
    *category = 0;
    *item = -1;
    *count = 0;
    if (itemCursor_ < 0)
        return;
    short index = categoryCursor_ - 0x5b;
    short* items = GetCategoryItems();
    unsigned char* counts = GetCategoryCounts();
    unsigned short size = GetCategorySize();
    if (items != 0 && counts != 0 && size != 0)
    {
        unsigned short position = (unsigned short)(page_ * 8);
        position += itemCursor_ - 0x64;
        *category = index;
        *item = items[position];
        *count = counts[position];
    }
}

void AlchemyMenu::IncreaseCount()
{
    unsigned char category;
    short item;
    unsigned char count;
    GetSelectedItem(&category, &item, &count);
    if (count > 9)
        count = 9;
    if (count != 0)
    {
        unsigned char previous = count_;
        count_ = previous + 1;
        if (count < count_)
            count_ = count;
        if (previous != count_)
            arrowUp_ = 1;
    }
    DrawItems();
    func_02080fa8(menu_, 0x1f, count_);
    func_020813ec(menu_, 6);
}

void AlchemyMenu::DecreaseCount()
{
    unsigned char category;
    short item;
    unsigned char count;
    GetSelectedItem(&category, &item, &count);
    if (count > 9)
        count = 9;
    if (count != 0)
    {
        unsigned char previous = count_;
        count_ = previous - 1;
        if (count_ == 0)
            count_ = 1;
        if (previous != count_)
            arrowDown_ = 1;
    }
    DrawItems();
    func_02080fa8(menu_, 0x1f, count_);
    func_020813ec(menu_, 6);
}

void AlchemyMenu::OpenItems()
{
    func_02080c20(menu_, 0);
    flags_ |= ALCHEMY_MENU_ITEMS;
    item_ = -1;
    count_ = 0;
    SetLayoutIngredients(&layout_);
    unsigned short size = GetCategorySize();
    flags_ &= ~ALCHEMY_MENU_PAGES;
    if (size > 8)
        flags_ |= ALCHEMY_MENU_PAGES;
    group_ = 0x11;
    itemCursor_ = -1;
    if (itemCursor_ < 0)
        itemCursor_ = func_02080468(menu_, group_);
    menu_->cursor_ = itemCursor_;
    DrawItems();
    ShowSelectedItem();
    func_0208203c(&repeat_);
    cursor_ = 0;
    func_02081ea4(menu_, group_, 0);
}

void AlchemyMenu::CountItemPages()
{
    page_ = 0;
    pages_ = (sizes_[(short)(categoryCursor_ - 0x5b)] + 7) / 8;
    if (pages_ == 0)
        pages_ = 1;
}

int AlchemyMenu::UpdateItems()
{
    cursor_ = &itemCursor_;
    UpdateItemPage();
    if (previousCursor_ != *cursor_)
    {
        ShowSelectedItem();
        return 0;
    }
    if (UpdateItemButtons())
        return 1;
    return 0;
}

int AlchemyMenu::UpdateItemButtons()
{
    short element = layout_.GetTouchedElement();
    int names = element == 0x78 ? 1 : 0;
    int window = element == 0x25 ? 1 : 0;
    if (chosenCounts_[0] > 1 || chosenCounts_[1] >= 1)
    {
        names = (names | func_02012444(data_02114e30, 0x400)) ? 1 : 0;
        if (names)
        {
            cursor_ = 0;
            state_ = AlchemyMenuState_Ingredient3;
            step_ = 6;
            DrawItems();
            func_02081ea4(menu_, 0x10, 1);
            flags_ &= ~ALCHEMY_MENU_ITEMS;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0xa;
            messageStep_ = 0;
            return 1;
        }
    }
    if (names)
        return 1;
    if (flags_ & ALCHEMY_MENU_ITEMS)
    {
        if (func_02012444(data_02114e30, 0x300) || window)
        {
            AlchemyPot* pot = pot_;
            pot->ShowNames((pot->window_.flags_ & ITEM_INFO_WINDOW_NAMES) ? 0 : 1);
            func_0205eaa0(data_02108760, 1, 0);
            return 1;
        }
    }
    return 0;
}

static unsigned short GetButtons(KeyRepeat* repeat);

void AlchemyMenu::OpenCount()
{
    SHOW_ELEMENT(&layout_, 0x50);
    HIDE_ELEMENT(&layout_, 0x4f);
    HIDE_ELEMENT(&layout_, 0xe);
    HIDE_ELEMENT(&layout_, 0xf);
    HIDE_ELEMENT(&layout_, 0x15);
    HIDE_ELEMENT(&layout_, 0x1f);
    HIDE_ELEMENT(&layout_, 0x20);
    HIDE_ELEMENT(&layout_, 0x21);
    HIDE_ELEMENT(&layout_, 0x22);
    DrawItems();
    flags_ |= ALCHEMY_MENU_COUNT;
    group_ = 6;
    func_02080fa8(menu_, 0x1f, count_);
    func_020813ec(menu_, 6);
}

int AlchemyMenu::UpdateCount()
{
    int confirm = 0;
    int cancel = 0;
    int change = 0;
    if (repeatDelay_ < 5)
    {
        repeatDelay_++;
    }
    else
    {
        short button = layout_.GetTouchedButton();
        if (button == 0x76)
            change = 1;
        if (button == 0x77)
            change = -1;
        if (change != 0)
            repeatDelay_ = 0;
    }
    unsigned char count = 0;
    short element = layout_.GetTouchedElement();
    if (element >= 0)
    {
        if (element == 0x76)
            change = 1;
        if (element == 0x77)
            change = -1;
        confirm = element == 0x11 ? 1 : 0;
        cancel = element == 0x12 ? 1 : 0;
    }
    if ((unsigned short)(func_02081f20(&repeat_, GameState::GetInstance()->GetTickCount()) + 0xffff) <= 1)
    {
        unsigned short buttons = GetButtons(&repeat_);
        if (buttons == 0x40)
            change = 1;
        if (buttons == 0x80)
            change = -1;
        if (buttons == 0x20)
            count = 9;
        if (buttons == 0x10)
            count = 1;
    }
    if (count != 0)
    {
        int previous = count_;
        count_ = count;
        if (count == 9)
            IncreaseCount();
        else
            DecreaseCount();
        arrowUp_ = previous < count_ ? 1 : 0;
        arrowDown_ = count_ < previous ? 1 : 0;
        return 1;
    }
    if (change != 0)
    {
        if (change > 0)
            IncreaseCount();
        else
            DecreaseCount();
        return 1;
    }
    if (confirm)
        return 2;
    if (cancel)
        return 3;
    return 0;
}


#pragma dont_inline on
// The buttons that a KeyRepeat repeats
static unsigned short GetButtons(KeyRepeat* repeat)
{
    if (repeat->buttons_ != 0)
        return *repeat->buttons_;
    return 0;
}
#pragma dont_inline reset

unsigned char AlchemyMenu::UpdateTimes()
{
    int confirm = 0;
    int cancel = 0;
    int change = 0;
    if (repeatDelay_ < 5)
    {
        repeatDelay_++;
    }
    else
    {
        short button = layout_.GetTouchedButton();
        if (button == 0x49)
            change = 1;
        if (button == 0x4a)
            change = -1;
        if (change != 0)
            repeatDelay_ = 0;
    }
    unsigned char count = 0;
    short element = layout_.GetTouchedElement();
    if (element >= 0)
    {
        if (element == 0x49)
            change = 1;
        if (element == 0x4a)
            change = -1;
        confirm = element == 0x4e ? 1 : 0;
        cancel = element == 0x14 ? 1 : 0;
    }
    if ((unsigned short)(func_02081f20(&repeat_, GameState::GetInstance()->GetTickCount()) + 0xffff) <= 1)
    {
        unsigned short buttons = GetButtons(&repeat_);
        if (buttons == 0x40)
            change = 1;
        if (buttons == 0x80)
            change = -1;
        if (buttons == 0x20)
            count = 9;
        if (buttons == 0x10)
            count = 1;
    }
    if (count != 0)
    {
        int previous = count_;
        count_ = count;
        while (!ingredients_.HasIngredients(count_))
            count_--;
        if (previous < count_)
            arrowUp_ = 1;
        if (count_ < previous)
            arrowDown_ = 1;
        DrawTimes();
        UpdateMultiplier();
        return 1;
    }
    if (change != 0)
    {
        int previous = count_;
        count_ = previous + change;
        if (!ingredients_.HasIngredients(count_))
            count_--;
        if (count_ == 0)
            count_ = 1;
        if (count_ > 9)
            count_ = 9;
        if (previous < count_)
            arrowUp_ = 1;
        if (count_ < previous)
            arrowDown_ = 1;
        DrawTimes();
        UpdateMultiplier();
        return 1;
    }
    if (confirm)
        return 2;
    if (cancel)
        return 3;
    return 0;
}

unsigned char AlchemyMenu::GetRecipeButton()
{
    int filter1 = 0;
    int filter2 = 0;
    int sort = 0;
    int names = 0;
    short element = layout_.GetTouchedElement();
    if (element >= 0)
    {
        if (element == 0x41)
            filter1 = 1;
        filter2 = element == 0x42 ? 1 : 0;
        sort = element == 0x13 ? 1 : 0;
        names = element == 0x26 ? 1 : 0;
    }
    else
    {
        if (func_02012444(data_02114e30, 4))
            sort = 1;
        if (func_02012444(data_02114e30, 0x300))
            names = 1;
    }
    if (sort)
        return 1;
    if (filter1)
        return 2;
    if (filter2)
        return 3;
    if (names)
        return 4;
    return 0;
}

// NONMATCHING: the C matches 48.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::ChangeSort()
{
    Recipe* recipe = GetRecipe(recipeCursor_ - 0x29);
    if (recipe == 0)
        return;
    if (!recipe->known_)
    {
        recipeCursor_ = -1;
        previousCursor_ = -1;
        recipe = 0;
    }
    sort_ = sort_ == 0 ? 1 : 0;
    short count = 0;
    func_02071ffc(&table_, filterCategory_, filterKind_, sort_, 0x10, &count);
    Recipe* recipes = table_.unk_0;
    recipes_ = recipes;
    pageStart_ = recipes;
    if (recipe == 0)
        recipe = pageStart_;
    CountPages();
    func_0205eaa0(data_02108760, 1, 0);
    Recipe* entry = pageStart_;
    short index = 0;
    while (entry != 0)
    {
        if (entry == recipe)
            break;
        entry = entry->next_;
        index++;
    }
    short column = index % 16;
    page_ = index / 16;
    SetPage(recipe);
    recipeCursor_ = column + 0x29;
    func_020804fc(menu_, 9);
    DrawRecipes();
    DrawSort();
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11AlchemyMenu10CountPagesEv(); // AlchemyMenu::CountPages
    void _ZN11AlchemyMenu11DrawRecipesEv(); // AlchemyMenu::DrawRecipes
    void _ZN11AlchemyMenu7SetPageEP6Recipe(); // AlchemyMenu::SetPage
    void _ZN11AlchemyMenu8DrawSortEv(); // AlchemyMenu::DrawSort
    void _ZN11AlchemyMenu9GetRecipeEs(); // AlchemyMenu::GetRecipe
}

asm void AlchemyMenu::ChangeSort()
{
    stmdb sp!, {r4, r5, lr}
    sub sp, sp, #0xc
    mov r5, r0
    add r1, r5, #0x300
    ldrsh r1, [r1, #0x6a]
    sub r1, r1, #0x29
    mov r1, r1, lsl #0x10
    mov r1, r1, asr #0x10
    bl _ZN11AlchemyMenu9GetRecipeEs
    movs r4, r0
    beq @L02159da4
    ldr r0, [r4, #0x10]
    mov r0, r0, lsl #0x9
    movs r0, r0, lsr #0x1f
    addeq r0, r5, #0x300
    mvneq r1, #0x0
    streqh r1, [r0, #0x6a]
    streqh r1, [r0, #0x5e]
    ldrb r0, [r5, #0x386]
    moveq r4, #0x0
    mov r1, #0x10
    cmp r0, #0x0
    moveq r0, #0x1
    movne r0, #0x0
    strb r0, [r5, #0x386]
    mov r0, #0x0
    strh r0, [sp, #0x8]
    add r0, sp, #0x8
    str r1, [sp, #0x0]
    str r0, [sp, #0x4]
    add r0, r5, #0x300
    ldrsb r1, [r0, #0x84]
    ldrsb r2, [r0, #0x85]
    ldrb r3, [r5, #0x386]
    add r0, r5, #0x14c
    bl func_02071ffc
    ldr r0, [r5, #0x14c]
    cmp r4, #0x0
    str r0, [r5, #0x2c]
    str r0, [r5, #0x30]
    mov r0, r5
    ldreq r4, [r5, #0x30]
    bl _ZN11AlchemyMenu10CountPagesEv
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    ldr r1, [r5, #0x30]
    mov r3, #0x0
    b @L02159d44
@L02159d2c:
    cmp r1, r4
    beq @L02159d4c
    add r0, r3, #0x1
    mov r0, r0, lsl #0x10
    ldr r1, [r1, #0x1c]
    mov r3, r0, asr #0x10
@L02159d44:
    cmp r1, #0x0
    bne @L02159d2c
@L02159d4c:
    mov r1, r3, lsr #0x1f
    rsb r0, r1, r3, lsl #0x1c
    add r1, r1, r0, ror #0x1c
    mov r0, r3, asr #0x3
    mov r2, r1, lsl #0x10
    add r0, r3, r0, lsr #0x1c
    mov r3, r0, asr #0x4
    mov r0, r5
    mov r1, r4
    mov r4, r2, asr #0x10
    strb r3, [r5, #0x388]
    bl _ZN11AlchemyMenu7SetPageEP6Recipe
    add r1, r4, #0x29
    add r0, r5, #0x300
    strh r1, [r0, #0x6a]
    ldr r0, [r5, #0x14]
    mov r1, #0x9
    bl func_020804fc
    mov r0, r5
    bl _ZN11AlchemyMenu11DrawRecipesEv
    mov r0, r5
    bl _ZN11AlchemyMenu8DrawSortEv
@L02159da4:
    add sp, sp, #0xc
    ldmia sp!, {r4, r5, pc}
}
#endif

void AlchemyMenu::OpenChoice()
{
    func_0205eaa0(data_02108760, 5, 0);
    group_ = 7;
    previousCursor_ = choiceCursor_ = 0x22;
    menu_->cursor_ = choiceCursor_;
    func_020813ec(menu_, group_);
    func_0208203c(&repeat_);
    cursor_ = 0;
    if (choice_ == 0)
        return;
    func_02080c04(menu_, group_);
    func_020e280c(choice_, -1);
    func_020e2d24(*(char**)((char*)choice_ + 0x10) + 0x28, 0x18, 1);
}

signed char AlchemyMenu::UpdateChoice()
{
    signed char result = 0;
    arrowTimer_ = 0;
    cursor_ = &choiceCursor_;
    if (IsConfirmed() || func_02012444(data_02114e30, 0x200))
    {
        func_0205eaa0(data_02108760, 1, 0);
        result = -1;
        if (choiceCursor_ == 0x22)
            result = 1;
    }
    else if (IsCancelled())
    {
        result = -1;
    }
    if (result != 0)
    {
        func_0207fdcc(menu_, group_);
        func_0208203c(&repeat_);
        cursor_ = 0;
    }
    if (choice_ != 0 && result != 0)
        func_020e25e8(choice_);
    return result;
}

void AlchemyMenu::PlayTextSound()
{
    if (textSoundPlaying_ != 0)
        return;
    if (textSoundOn_ == 0)
        return;
    switch (textSound_)
    {
    case 0:
        func_0205eaa0(data_02108760, 0xa, 0);
        break;
    case 1:
        func_0205eaa0(data_02108760, 0xc, 0);
        break;
    case 2:
        func_0205eaa0(data_02108760, 0xb, 0);
        break;
    }
    textSoundPlaying_ = 1;
}

void AlchemyMenu::StopTextSound()
{
    if (textSoundPlaying_ != 0 && textSoundOn_ != 0)
        textSoundPlaying_ = 0;
}

void AlchemyMenu::UpdateTextSound()
{
    if (textSoundState_ < 0)
    {
        textSoundTimer_ = 0;
        StopTextSound();
        return;
    }
    if (textSoundTimer_ > 0x3c)
    {
        textSoundTimer_ = 0;
        StopTextSound();
        PlayTextSound();
    }
    textSoundTimer_ += GameState::GetInstance()->GetEffectiveDeltaTime();
}

// NONMATCHING: the C matches 92.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::UpdateMessage()
{
    if (messageStep_ == 0)
    {
        if (flags_ & ALCHEMY_MENU_MESSAGE)
        {
            func_02080c20(menu_, 0);
            func_020813ec(menu_, 0);
        }
        flags_ &= ~ALCHEMY_MENU_MESSAGE;
        messageLength_ = 0;
        if (func_020e0434(&menuTexts_, message_) == 0)
            message_ = -1;
        textSoundState_ = -1;
        messageStep_++;
    }
    else if (messageStep_ == 1)
    {
        char* text;
        char* messages = func_020421a0();
        text = *(char**)(messages + 0x5c);
        memset(text, 0, 0x960);
        func_02046380(messages);
        unsigned short rate = 0;
        if (recipe_ != 0)
        {
            const char** name = func_020e5294(itemNames_, results_[0].item_);
            if (name != 0)
                *(const char***)(messages + 0x18) = name;
            rate = (successRate_ / 10) * 10;
        }
        func_020465c0(messages, 0, times_);
        func_020465c0(messages, 1, rate);
        GameObject* object = (GameObject*)GameState::GetInstance()->GetUnknownGameObject();
        char name[0xc];
        if (object != 0)
        {
            func_020e4bf4(name, *(short*)((char*)object + 4));
            *(char**)messages = name;
        }
        int i = 0;
        const short* messagesWithItems = sItemMessages;
        while (true)
        {
            short withItem = *messagesWithItems;
            if (withItem < 0)
                break;
            if (withItem == message_)
            {
                const char** itemName = func_020e5294(itemNames_, chosenItems_[i]);
                if (itemName != 0)
                    *(const char***)(messages + 0x18) = itemName;
                break;
            }
            messagesWithItems++;
            i++;
        }
        func_02046608(messages, 0xc, func_020e0434(&menuTexts_, message_), text, 0xe3, 0, 1);
        char* character;
        unsigned short length = messageLength_;
        int previous = textPosition_;
        int position = previous + ticks_ * 16;
        textPosition_ = position;
        int count = (position >> 4) - (previous >> 4);
        if (position >= 0xffffff)
            textPosition_ = 0;
        character = text + length;
        for (int j = 0; j < count; j++)
        {
            if (*character == 0)
                break;
            int size = 1;
            if (*character == '\\' && character[1] == 'n')
            {
                character += 2;
                length += 2;
            }
            else
            {
                char* glyph = func_0204254c(character, 1);
                if (glyph != 0)
                    size = (signed char)(glyph[5] << 2) >> 2;
                character += size;
                length += size;
            }
        }
        if (messageLength_ >= length)
            message_ = -1;
        messageLength_ = length;
        char buffer[0x400] = {0};
        memcpy(buffer, text, length);
        func_02080f8c(menu_, 1, buffer);
        func_020813ec(menu_, 1);
        func_02080c20(menu_, 1);
        textSoundState_ = 1;
        const short* silentMessages = sSilentMessages;
        while (true)
        {
            short silent = *silentMessages;
            if (silent < 0)
                break;
            if (silent == message_)
            {
                textSoundState_ = -1;
                break;
            }
            silentMessages++;
        }
        UpdateTextSound();
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11AlchemyMenu15UpdateTextSoundEv(); // AlchemyMenu::UpdateTextSound
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState20GetUnknownGameObjectEv(); // GameState::GetUnknownGameObject
    void _s32_div_f();
}

asm void AlchemyMenu::UpdateMessage()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x18
    sub sp, sp, #0x400
    mov r10, r0
    ldrb r0, [r10, #0x392]
    cmp r0, #0x0
    bne @L0215a09c
    add r0, r10, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x20
    beq @L0215a050
    ldr r0, [r10, #0x14]
    mov r1, #0x0
    bl func_02080c20
    ldr r0, [r10, #0x14]
    mov r1, #0x0
    bl func_020813ec
@L0215a050:
    add r1, r10, #0x300
    ldrh r3, [r1, #0x94]
    mov r2, #0x0
    add r0, r10, #0x158
    bic r3, r3, #0x20
    strh r3, [r1, #0x94]
    strh r2, [r1, #0x80]
    ldrsh r1, [r1, #0x7e]
    bl func_020e0434
    cmp r0, #0x0
    addeq r0, r10, #0x300
    mvneq r1, #0x0
    streqh r1, [r0, #0x7e]
    mvn r0, #0x0
    str r0, [r10, #0x3b0]
    ldrb r0, [r10, #0x392]
    add r0, r0, #0x1
    strb r0, [r10, #0x392]
    b @L0215a328
@L0215a09c:
    cmp r0, #0x1
    bne @L0215a328
    bl func_020421a0
    mov r5, r0
    ldr r4, [r5, #0x5c]
    mov r1, #0x0
    mov r0, r4
    mov r2, #0x960
    bl memset
    mov r0, r5
    bl func_02046380
    ldr r0, [r10, #0x34]
    mov r6, #0x0
    cmp r0, #0x0
    beq @L0215a110
    add r0, r10, #0x100
    ldrsh r1, [r0, #0xec]
    add r0, r10, #0x170
    bl func_020e5294
    cmp r0, #0x0
    strne r0, [r5, #0x18]
    add r0, r10, #0x300
    ldrsh r0, [r0, #0x82]
    mov r1, #0xa
    bl _s32_div_f
    mov r1, #0xa
    mul r1, r0, r1
    mov r0, r1, lsl #0x10
    mov r6, r0, lsr #0x10
@L0215a110:
    ldrb r2, [r10, #0x387]
    mov r0, r5
    mov r1, #0x0
    bl func_020465c0
    mov r0, r5
    mov r2, r6
    mov r1, #0x1
    bl func_020465c0
    bl _ZN9GameState11GetInstanceEv
    bl _ZN9GameState20GetUnknownGameObjectEv
    cmp r0, #0x0
    beq @L0215a154
    ldrsh r1, [r0, #0x4]
    add r0, sp, #0xc
    bl func_020e4bf4
    add r0, sp, #0xc
    str r0, [r5, #0x0]
@L0215a154:
    ldr r6, =sItemMessages
    mov r3, #0x0
    add r0, r10, #0x300
@L0215a160:
    ldrsh r2, [r6, #0x0]
    cmp r2, #0x0
    blt @L0215a1a4
    ldrsh r1, [r0, #0x7e]
    cmp r2, r1
    bne @L0215a198
    add r0, r10, r3, lsl #0x1
    add r0, r0, #0x300
    ldrsh r1, [r0, #0x78]
    add r0, r10, #0x170
    bl func_020e5294
    cmp r0, #0x0
    strne r0, [r5, #0x18]
    b @L0215a1a4
@L0215a198:
    add r6, r6, #0x2
    add r3, r3, #0x1
    b @L0215a160
@L0215a1a4:
    add r0, r10, #0x300
    ldrsh r1, [r0, #0x7e]
    add r0, r10, #0x158
    bl func_020e0434
    mov r1, #0xe3
    mov r2, r0
    str r1, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    mov r1, #0x1
    str r1, [sp, #0x8]
    mov r0, r5
    mov r3, r4
    mov r1, #0xc
    bl func_02046608
    add r0, r10, #0x300
    ldrh r6, [r0, #0x80]
    ldr r3, [r10, #0x0]
    ldr r1, [r10, #0x34c]
    mvn r0, #0xff000000
    add r2, r3, r1, lsl #0x4
    mov r1, r2, asr #0x4
    cmp r2, r0
    str r2, [r10, #0x0]
    movge r0, #0x0
    add r5, r4, r6
    sub r7, r1, r3, asr #0x4
    strge r0, [r10, #0x0]
    mov r8, #0x0
    mov r11, #0x1
    b @L0215a280
@L0215a220:
    ldrsb r0, [r5, #0x0]
    cmp r0, #0x0
    beq @L0215a288
    cmp r0, #0x5c
    ldreqsb r0, [r5, #0x1]
    mov r9, r11
    cmpeq r0, #0x6e
    addeq r0, r6, #0x2
    moveq r0, r0, lsl #0x10
    addeq r5, r5, #0x2
    moveq r6, r0, lsr #0x10
    beq @L0215a27c
    mov r0, r5
    mov r1, #0x1
    bl func_0204254c
    cmp r0, #0x0
    ldrnesb r0, [r0, #0x5]
    movne r0, r0, lsl #0x1a
    movne r9, r0, asr #0x1a
    add r0, r6, r9
    mov r0, r0, lsl #0x10
    add r5, r5, r9
    mov r6, r0, lsr #0x10
@L0215a27c:
    add r8, r8, #0x1
@L0215a280:
    cmp r8, r7
    blt @L0215a220
@L0215a288:
    add r0, r10, #0x300
    ldrh r1, [r0, #0x80]
    add r2, r10, #0x300
    cmp r1, r6
    mvnhs r1, #0x0
    strhsh r1, [r0, #0x7e]
    add r0, sp, #0x18
    mov r1, #0x400
    strh r6, [r2, #0x80]
    bl __clear
    add r0, sp, #0x18
    mov r1, r4
    mov r2, r6
    bl memcpy
    ldr r0, [r10, #0x14]
    add r2, sp, #0x18
    mov r1, #0x1
    bl func_02080f8c
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    bl func_020813ec
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    bl func_02080c20
    mov r0, #0x1
    str r0, [r10, #0x3b0]
    ldr r3, =sSilentMessages
    add r0, r10, #0x300
@L0215a2f8:
    ldrsh r2, [r3, #0x0]
    cmp r2, #0x0
    blt @L0215a320
    ldrsh r1, [r0, #0x7e]
    cmp r2, r1
    mvneq r0, #0x0
    streq r0, [r10, #0x3b0]
    beq @L0215a320
    add r3, r3, #0x2
    b @L0215a2f8
@L0215a320:
    mov r0, r10
    bl _ZN11AlchemyMenu15UpdateTextSoundEv
@L0215a328:
    add sp, sp, #0x18
    add sp, sp, #0x400
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void AlchemyMenu::LoadResult(int great)
{
    pot_->ResetIngredients();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    loader->AddFence();
    task_ = loader->QueueLoadFileInGP2(data_020f2a38, data_020f2a30, 0);
}

unsigned char AlchemyMenu::UpdateResult(int great)
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loader->GetTaskStatus(task_))
    {
        void* data;
        unsigned int size;
        loader->GetLoadedFileByID(task_, &data, &size);
        if (data != 0)
        {
            allocators_[8].Reset();
            ResultItems ids = sNoResultItems;
            PartEntry copies[4];
            unsigned char i;
            for (i = 0; i < 4; i++)
            {
                results_[i].Initialize();
                func_020836e4(&copies[i], &results_[i].entry_);
            }
            Recipe* recipe = recipe_;
            if (recipe != 0)
            {
                if (great)
                    recipe = func_02071d60(&table_, recipe->greatRecipe_);
                short item = recipe->item_;
                results_[0].item_ = item;
                ids.items_[0] = item;
            }
            short item1 = chosenItems_[0];
            results_[1].item_ = item1;
            ids.items_[1] = item1;
            short item2 = chosenItems_[1];
            results_[2].item_ = item2;
            ids.items_[2] = item2;
            short item3 = chosenItems_[2];
            results_[3].item_ = item3;
            ids.items_[3] = item3;
            if (recipe_ != 0)
            {
                if (ids.items_[1] < 0)
                {
                    short ingredient = recipe_->ingredients_[0];
                    results_[1].item_ = ingredient;
                    ids.items_[1] = ingredient;
                }
                if (ids.items_[2] < 0)
                {
                    short ingredient = recipe_->ingredients_[1];
                    results_[2].item_ = ingredient;
                    ids.items_[2] = ingredient;
                }
                if (ids.items_[3] < 0)
                {
                    short ingredient = recipe_->ingredients_[2];
                    results_[3].item_ = ingredient;
                    ids.items_[3] = ingredient;
                }
            }
            func_020deef4(copies, data, size, ids.items_, 4);
            if (ids.items_[1] == ids.items_[2] && ids.items_[2] > 0)
                func_020836e4(&copies[2], &copies[1]);
            if (ids.items_[1] == ids.items_[3] && ids.items_[3] > 0)
                func_020836e4(&copies[3], &copies[1]);
            if (ids.items_[2] == ids.items_[3] && ids.items_[3] > 0)
                func_020836e4(&copies[3], &copies[2]);
            for (i = 0; i < 4; i++)
                func_020836e4(&results_[i].entry_, &copies[i]);
            pot_->LoadIngredients(results_);
        }
        loader->RemoveTask(task_);
        task_ = -1;
    }
    if (task_ == -1)
        return 1;
    return 0;
}

void AlchemyMenu::UpdateMultiplier()
{
    pot_->SetMultiplier(count_);
    pot_->DrawNames();
}

// NONMATCHING: the C matches 98.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::State_Load()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (step_ == 0)
    {
        if (!(flags_ & ALCHEMY_MENU_NO_SCENE))
            func_0209c3b4(data_02109bf4, 8);
        func_020c54a4(0, 0, 0, 0);
        func_020c5588(0, 0, 0x7fff, 0, 0);
        void* music = func_02094a00();
        func_02094b40();
        func_02094b34(music, 0x6c, 0x1fd, 0, 0);
        step_++;
    }
    else if (step_ == 1)
    {
        func_02094a00();
        if (func_02094b4c())
            step_++;
    }
    else if (step_ == 2)
    {
        task_ = loader->QueueLoadFileInGP2(STRING(0x0, "data/bin/menu/str_ren.gp2"), STRING(0x1a, "str_ren_<LG>.nat"), 0);
        step_++;
    }
    else if (step_ == 3)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                SafeAllocator* allocators = allocators_;
                allocators[1].Reset();
                func_020dfc40(&menuTexts_);
                func_020dfec0(&menuTexts_, &allocators[1], data, size);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step_ == 4)
    {
        task_ = loader->QueueLoadFileInGP2(STRING(0x2b, "data/bin/recipe.gp2"), STRING(0x3f, "recipe_<LG>.bin"), 0);
        step_++;
    }
    else if (step_ == 5)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                SafeAllocator* allocator = allocators_;
                allocator->Reset();
                func_02071be8(&table_);
                func_02071c00(&table_, allocator, data, size);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step_ == 6)
    {
        BG0CNTSUB = (BG0CNTSUB & 0x43) | 0x1010;
        BG1CNTSUB = (BG1CNTSUB & 0x43) | 0x1110;
        BG2CNTSUB = (BG2CNTSUB & 0x43) | 0x1210;
        BG3CNTSUB = (BG3CNTSUB & 0x43) | 0x1300;
        memset((void*)GetSubBG0ScreenBase(), 0, 0x800);
        *(volatile unsigned int*)0x04001010 = 0;
        allocators_[3].Reset();
        func_0204af64(&subBackground_);
        func_0204b11c(&subBackground_, 0);
        subBackground_.unk_1c_0_ = 1;
        subBackground_.unk_1c_4_ = 3;
        func_0204b5b4(&subBackground_, 3);
        func_0204b5e8(&subBackground_, 0, 0);
        func_0204b12c(&subBackground_, &allocators_[3]);
        func_0204af38(&subBackground_, 7, &allocators_[3]);
        task_ = loader->QueueLoadFile(STRING(0x4f, "data/ani/bg_kamael.pac"), 0);
        step_++;
    }
    else if (step_ == 7)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* name;
            void* pac;
            unsigned int pacSize;
            loader->GetLoadedFileByID(task_, &pac, &pacSize);
            int count = func_02046900(pac);
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(pac, i, &name, &size);
                if (file != 0)
                {
                    if (i == 0)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            BackgroundGraphics* background = &backgrounds_[j];
                            func_0204af64(background);
                            func_0204b11c(background, 0);
                            background->unk_1c_0_ = 1;
                            background->unk_1c_4_ = j + 1;
                            func_0204b5e8(background, 0, 0);
                            func_0204b5b4(background, j + 1);
                            func_0204b12c(background, &allocators_[3]);
                            func_0204b174(background, file, &allocators_[3], size);
                        }
                    }
                    else
                    {
                        func_0204b174(&subBackground_, file, &allocators_[3], size);
                    }
                }
            }
            func_0204b0e8(&subBackground_, 0);
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step_ == 8)
    {
        SafeAllocator* allocators = allocators_;
        allocators[4].Reset();
        for (unsigned char i = 0; i < 7; i++)
        {
            Canvas* canvas = &canvases_[i];
            func_0204c684(canvas);
            func_0204c7a8(canvas, &allocators[4], canvasBuffer_, 0x600);
            canvas->background_ = backgrounds_;
        }
        task_ = loader->QueueLoadFileInGP2(STRING(0x66, "data/ani/lay_rrb.gp2"), STRING(0x7b, "lay_rrb_<LG>.lia"), 0);
        step_++;
    }
    else if (step_ == 9)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                SafeAllocator* allocators = allocators_;
                allocators[6].Reset();
                layout_.Initialize();
                layout_.Load(&allocators[6], data, size);
                HIDE_ELEMENT(&layout_, 1);
                HIDE_ELEMENT(&layout_, 0x23);
                HIDE_ELEMENT(&layout_, 0x24);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step_ == 10)
    {
        func_0205a444(&renderer_);
        renderer_.unk_50 = 1;
        renderer_.SetSprites(sprites_, 29);
        renderer_.animations_ = *(SpriteAnimationList**)((char*)choice_ + 0x20);
        task_ = loader->QueueLoadFileInGP2(STRING(0x8c, "data/ani/orrb.gp2"), STRING(0x9e, "orrb_<LG>.pac"), 0);
        step_++;
    }
    else if (step_ == 11)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* name;
            void* pac;
            unsigned int pacSize;
            loader->GetLoadedFileByID(task_, &pac, &pacSize);
            int count = func_02046900(pac);
            SafeAllocator* allocators = allocators_;
            allocators[7].Reset();
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(pac, i, &name, &size);
                if (file != 0)
                    func_0205a528(&renderer_, file, size, &allocators[7]);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
            for (int j = 0; j < 8; j++)
                sprites_[j + 0x12].unk_22 = 0x18;
        }
    }
    else if (step_ == 12)
    {
        task_ = loader->QueueLoadFileInGP2(STRING(0xac, "data/prm/itemname.gp2"), STRING(0xc2, "itemname_<LG>.nat"), 0);
        step_++;
    }
    else if (step_ == 13)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                SafeAllocator* allocators = allocators_;
                allocators[2].Reset();
                func_020e526c(itemNames_);
                func_020e5604(itemNames_, &allocators[2], data, size);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step_ == 14)
    {
        SafeAllocator* allocators = allocators_;
        allocators[5].Reset();
        func_0207f84c(menu_);
        func_0207f914(menu_, &allocators[5], STRING(0xd4, "data/bin/menu/bm_rrb.gp2"), STRING(0xed, "bm_rrb"));
        step_++;
    }
    else if (step_ == 15)
    {
        int result = func_0207f9f4(menu_);
        if (result == 0)
            step_++;
        if (result < 0)
            state_ = AlchemyMenuState_FadeOut;
    }
    else if (step_ == 16)
    {
        func_020810a0(menu_, 1);
        menu_->SetBackgrounds(backgrounds_);
        func_0207f7f0(menu_, canvases_, 7);
        menu_->unk_3a = 1;
        func_0208108c(menu_, 0x20);
        func_0208108c(menu_, 0x3e);
        BG0CNTSUB = BG0CNTSUB & ~3;
        BG1CNTSUB = (BG1CNTSUB & ~3) | 1;
        BG2CNTSUB = (BG2CNTSUB & ~3) | 2;
        BG3CNTSUB = (BG3CNTSUB & ~3) | 3;
        DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x1f00;
        ColorEffect_ConfigureAlphaBlend(0x04001050, 4, 0x18, 10, 6);
        LoadInventory();
        state_ = AlchemyMenuState_FadeIn;
        step_ = 0;
        ingredients_.MarkKnownRecipes(&table_, records_, 0x1d7);
        func_02071ffc(&table_, -1, -1, 0, 0, &unk_35c);
        short count = 0;
        func_02071ffc(&table_, filterCategory_, filterKind_, sort_, 0x10, &count);
        Recipe* recipes = table_.unk_0;
        recipes_ = recipes;
        pageStart_ = recipes;
        CountPages();
        ingredients_.SetRecords(records_, 0x1d7);
        ingredients_.SetTable(&table_);
        if (!(flags_ & ALCHEMY_MENU_NO_SCENE))
        {
            func_02081164(menu_, 0, 1);
            func_02081164(menu_, 1, 1);
            func_020813ec(menu_, 0);
            func_020813ec(menu_, 1);
            Canvas* canvas = func_02081da8(menu_, 1);
            if (canvas != 0)
            {
                canvas->unk_b8 = 0xc;
                canvas->unk_ba = 0x10;
            }
            char text[0x400] = {0};
            char* messages = func_020421a0();
            func_02046608(messages, 0xc, func_020e0434(&menuTexts_, 0), text, 0xe3, 0, 1);
            func_02080f8c(menu_, 1, text);
            func_020813ec(menu_, 1);
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11AlchemyMenu13LoadInventoryEv(); // AlchemyMenu::LoadInventory
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
    void _ZN18AlchemyIngredients10SetRecordsEP12RecipeRecordt(); // AlchemyIngredients::SetRecords
    void _ZN18AlchemyIngredients16MarkKnownRecipesEP11RecipeTableP12RecipeRecordi(); // AlchemyIngredients::MarkKnownRecipes
    void _ZN18AlchemyIngredients8SetTableEP11RecipeTable(); // AlchemyIngredients::SetTable
    void _ZN6Layout10InitializeEv(); // Layout::Initialize
    void _ZN6Layout4LoadEP13SafeAllocatorPvj(); // Layout::Load
}

asm void AlchemyMenu::State_Load()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x450
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    bl func_0200fb8c
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r1, [r10, #0x390]
    mov r4, r0
    cmp r1, #0x0
    bne @L0215a6a0
    add r0, r10, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x2
    bne @L0215a640
    ldr r0, =data_02109bf4
    mov r1, #0x8
    bl func_0209c3b4
@L0215a640:
    mov r0, #0x0
    mov r1, r0
    mov r2, r0
    mov r3, r0
    bl func_020c54a4
    mov r0, #0x0
    ldr r2, =0x7fff
    mov r1, r0
    mov r3, r0
    str r0, [sp, #0x0]
    bl func_020c5588
    bl func_02094a00
    mov r4, r0
    bl func_02094b40
    mov r0, r4
    mov r3, #0x0
    str r3, [sp, #0x0]
    mov r1, #0x6c
    ldr r2, =0x1fd
    bl func_02094b34
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215a6a0:
    cmp r1, #0x1
    bne @L0215a6c4
    bl func_02094a00
    bl func_02094b4c
    cmp r0, #0x0
    ldrneb r0, [r10, #0x390]
    addne r0, r0, #0x1
    strneb r0, [r10, #0x390]
    b @L0215b0a4
@L0215a6c4:
    cmp r1, #0x2
    bne @L0215a6f0
    ldr r1, =sStrings
    ldr r2, =sStrings+0x1a
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215a6f0:
    cmp r1, #0x3
    bne @L0215a774
    ldr r1, [r10, #0x354]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0215b0a4
    ldr r1, [r10, #0x354]
    add r2, sp, #0x4c
    add r3, sp, #0x48
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x4c]
    cmp r0, #0x0
    beq @L0215a750
    ldr r5, [r10, #0xc]
    add r0, r5, #0x14
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x158
    bl func_020dfc40
    ldr r2, [sp, #0x4c]
    ldr r3, [sp, #0x48]
    add r0, r10, #0x158
    add r1, r5, #0x14
    bl func_020dfec0
@L0215a750:
    ldr r1, [r10, #0x354]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215a774:
    cmp r1, #0x4
    bne @L0215a7a0
    ldr r1, =sStrings+0x2b
    ldr r2, =sStrings+0x3f
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215a7a0:
    cmp r1, #0x5
    bne @L0215a824
    ldr r1, [r10, #0x354]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0215b0a4
    ldr r1, [r10, #0x354]
    add r2, sp, #0x44
    add r3, sp, #0x40
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x44]
    cmp r0, #0x0
    beq @L0215a800
    ldr r5, [r10, #0xc]
    mov r0, r5
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x14c
    bl func_02071be8
    ldr r2, [sp, #0x44]
    ldr r3, [sp, #0x40]
    mov r1, r5
    add r0, r10, #0x14c
    bl func_02071c00
@L0215a800:
    ldr r1, [r10, #0x354]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215a824:
    cmp r1, #0x6
    bne @L0215a944
    ldr r0, =0x4001008
    ldr r1, =0x1010
    ldrh r5, [r0, #0x0]
    add r2, r1, #0x100
    add r3, r1, #0x200
    and r5, r5, #0x43
    orr r5, r5, #0x10
    orr r5, r5, #0x1000
    strh r5, [r0, #0x0]
    ldrh r5, [r0, #0x2]
    sub r1, r1, #0xfc000002
    and r5, r5, #0x43
    orr r2, r5, r2
    strh r2, [r0, #0x2]
    ldrh r2, [r0, #0x4]
    and r2, r2, #0x43
    orr r2, r2, r3
    strh r2, [r0, #0x4]
    ldrh r0, [r1, #0x0]
    and r0, r0, #0x43
    orr r0, r0, #0x1300
    strh r0, [r1, #0x0]
    bl GetSubBG0ScreenBase
    mov r1, #0x0
    mov r2, #0x800
    bl memset
    ldr r0, =0x4001010
    mov r1, #0x0
    str r1, [r0, #0x0]
    ldr r0, [r10, #0xc]
    add r0, r0, #0x3c
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x54
    bl func_0204af64
    add r0, r10, #0x54
    mov r1, #0x0
    bl func_0204b11c
    ldrb r2, [r10, #0x70]
    add r0, r10, #0x54
    mov r1, #0x3
    bic r2, r2, #0xf
    orr r2, r2, #0x1
    strb r2, [r10, #0x70]
    and r2, r2, #0xff
    bic r2, r2, #0xf0
    orr r2, r2, #0x30
    strb r2, [r10, #0x70]
    bl func_0204b5b4
    add r0, r10, #0x54
    mov r1, #0x0
    mov r2, r1
    bl func_0204b5e8
    add r0, r10, #0x54
    ldr r1, [r10, #0xc]
    add r1, r1, #0x3c
    bl func_0204b12c
    add r0, r10, #0x54
    mov r1, #0x7
    ldr r2, [r10, #0xc]
    add r2, r2, #0x3c
    bl func_0204af38
    mov r0, r4
    ldr r1, =sStrings+0x4f
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215a944:
    cmp r1, #0x7
    bne @L0215aaa4
    ldr r1, [r10, #0x354]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0215b0a4
    ldr r1, [r10, #0x354]
    add r2, sp, #0x38
    add r3, sp, #0x34
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x38]
    bl func_02046900
    mov r6, r0
    mov r7, #0x0
    b @L0215aa6c
@L0215a984:
    ldr r0, [sp, #0x38]
    add r2, sp, #0x3c
    add r3, sp, #0x30
    mov r1, r7
    bl func_020467f0
    movs r5, r0
    beq @L0215aa68
    cmp r7, #0x0
    bne @L0215aa50
    mov r8, #0x0
    mov r11, r8
    b @L0215aa44
@L0215a9b4:
    ldr r0, [r10, #0x1c]
    add r9, r0, r8, lsl #0x5
    mov r0, r9
    bl func_0204af64
    mov r0, r9
    mov r1, r11
    bl func_0204b11c
    ldrb r1, [r9, #0x1c]
    add r0, r8, #0x1
    and r0, r0, #0xff
    bic r1, r1, #0xf
    orr r1, r1, #0x1
    strb r1, [r9, #0x1c]
    and r1, r1, #0xff
    mov r0, r0, lsl #0x1c
    bic r1, r1, #0xf0
    orr r0, r1, r0, lsr #0x18
    mov r1, #0x0
    strb r0, [r9, #0x1c]
    mov r0, r9
    mov r2, r1
    bl func_0204b5e8
    mov r0, r9
    add r1, r8, #0x1
    bl func_0204b5b4
    ldr r1, [r10, #0xc]
    mov r0, r9
    add r1, r1, #0x3c
    bl func_0204b12c
    ldr r2, [r10, #0xc]
    ldr r3, [sp, #0x30]
    mov r0, r9
    mov r1, r5
    add r2, r2, #0x3c
    bl func_0204b174
    add r8, r8, #0x1
@L0215aa44:
    cmp r8, #0x2
    blt @L0215a9b4
    b @L0215aa68
@L0215aa50:
    ldr r2, [r10, #0xc]
    ldr r3, [sp, #0x30]
    mov r1, r5
    add r0, r10, #0x54
    add r2, r2, #0x3c
    bl func_0204b174
@L0215aa68:
    add r7, r7, #0x1
@L0215aa6c:
    cmp r7, r6
    blt @L0215a984
    add r0, r10, #0x54
    mov r1, #0x0
    bl func_0204b0e8
    ldr r1, [r10, #0x354]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215aaa4:
    cmp r1, #0x8
    bne @L0215ab2c
    ldr r6, [r10, #0xc]
    add r0, r6, #0x50
    bl _ZN13SafeAllocator5ResetEv
    mov r7, #0x0
    mov r5, #0x600
    mov r9, #0xe0
    b @L0215aafc
@L0215aac8:
    ldr r0, [r10, #0x20]
    mla r8, r7, r9, r0
    mov r0, r8
    bl func_0204c684
    ldr r2, [r10, #0x8]
    mov r0, r8
    mov r3, r5
    add r1, r6, #0x50
    bl func_0204c7a8
    ldr r1, [r10, #0x1c]
    add r0, r7, #0x1
    str r1, [r8, #0x4]
    and r7, r0, #0xff
@L0215aafc:
    cmp r7, #0x7
    blo @L0215aac8
    ldr r1, =sStrings+0x66
    ldr r2, =sStrings+0x7b
    mov r0, r4
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215ab2c:
    cmp r1, #0x9
    bne @L0215ac04
    ldr r1, [r10, #0x354]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0215b0a4
    ldr r1, [r10, #0x354]
    add r2, sp, #0x2c
    add r3, sp, #0x28
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x2c]
    cmp r0, #0x0
    beq @L0215abe0
    ldr r5, [r10, #0xc]
    add r0, r5, #0x78
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x100
    bl _ZN6Layout10InitializeEv
    ldr r2, [sp, #0x2c]
    ldr r3, [sp, #0x28]
    add r0, r10, #0x100
    add r1, r5, #0x78
    bl _ZN6Layout4LoadEP13SafeAllocatorPvj
    add r0, r10, #0x100
    mov r1, #0x1
    bl GetLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r10, #0x100
    mov r1, #0x23
    bl GetLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r10, #0x100
    mov r1, #0x24
    bl GetLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L0215abe0:
    ldr r1, [r10, #0x354]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215ac04:
    cmp r1, #0xa
    bne @L0215ac60
    add r0, r10, #0xac
    bl func_0205a444
    mov r0, #0x1
    strb r0, [r10, #0xfc]
    ldr r1, [r10, #0x24]
    mov r0, #0x1d
    str r1, [r10, #0xec]
    strh r0, [r10, #0xf8]
    ldr r0, [r10, #0x18]
    ldr r1, =sStrings+0x8c
    ldr r3, [r0, #0x20]
    ldr r2, =sStrings+0x9e
    mov r0, r4
    str r3, [r10, #0xe8]
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215ac60:
    cmp r1, #0xb
    bne @L0215ad3c
    ldr r1, [r10, #0x354]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0215b0a4
    ldr r1, [r10, #0x354]
    add r2, sp, #0x20
    add r3, sp, #0x1c
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x20]
    bl func_02046900
    ldr r7, [r10, #0xc]
    mov r8, r0
    add r0, r7, #0x8c
    bl _ZN13SafeAllocator5ResetEv
    mov r9, #0x0
    add r6, sp, #0x24
    add r5, sp, #0x18
    b @L0215ace4
@L0215acb4:
    ldr r0, [sp, #0x20]
    mov r1, r9
    mov r2, r6
    mov r3, r5
    bl func_020467f0
    movs r1, r0
    beq @L0215ace0
    ldr r2, [sp, #0x18]
    add r0, r10, #0xac
    add r3, r7, #0x8c
    bl func_0205a528
@L0215ace0:
    add r9, r9, #0x1
@L0215ace4:
    cmp r9, r8
    blt @L0215acb4
    ldr r1, [r10, #0x354]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    mov r4, #0x0
    mov r3, #0x18
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    mov r0, #0x28
    b @L0215ad30
@L0215ad1c:
    ldr r1, [r10, #0x24]
    add r2, r4, #0x12
    mla r1, r2, r0, r1
    strb r3, [r1, #0x22]
    add r4, r4, #0x1
@L0215ad30:
    cmp r4, #0x8
    blt @L0215ad1c
    b @L0215b0a4
@L0215ad3c:
    cmp r1, #0xc
    bne @L0215ad68
    ldr r1, =sStrings+0xac
    ldr r2, =sStrings+0xc2
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215ad68:
    cmp r1, #0xd
    bne @L0215adec
    ldr r1, [r10, #0x354]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0215b0a4
    ldr r1, [r10, #0x354]
    add r2, sp, #0x14
    add r3, sp, #0x10
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x14]
    cmp r0, #0x0
    beq @L0215adc8
    ldr r5, [r10, #0xc]
    add r0, r5, #0x28
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x170
    bl func_020e526c
    ldr r2, [sp, #0x14]
    ldr r3, [sp, #0x10]
    add r0, r10, #0x170
    add r1, r5, #0x28
    bl func_020e5604
@L0215adc8:
    ldr r1, [r10, #0x354]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x354]
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215adec:
    cmp r1, #0xe
    bne @L0215ae2c
    ldr r4, [r10, #0xc]
    add r0, r4, #0x64
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r10, #0x14]
    bl func_0207f84c
    ldr r0, [r10, #0x14]
    ldr r2, =sStrings+0xd4
    ldr r3, =sStrings+0xed
    add r1, r4, #0x64
    bl func_0207f914
    ldrb r0, [r10, #0x390]
    add r0, r0, #0x1
    strb r0, [r10, #0x390]
    b @L0215b0a4
@L0215ae2c:
    cmp r1, #0xf
    bne @L0215ae5c
    ldr r0, [r10, #0x14]
    bl func_0207f9f4
    cmp r0, #0x0
    ldreqb r1, [r10, #0x390]
    addeq r1, r1, #0x1
    streqb r1, [r10, #0x390]
    cmp r0, #0x0
    movlt r0, #0xc
    strltb r0, [r10, #0x38f]
    b @L0215b0a4
@L0215ae5c:
    cmp r1, #0x10
    bne @L0215b0a4
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    bl func_020810a0
    ldr r2, [r10, #0x14]
    ldr r1, [r10, #0x1c]
    mov r0, #0x2
    str r1, [r2, #0x2c]
    strb r0, [r2, #0x38]
    ldr r0, [r10, #0x14]
    ldr r1, [r10, #0x20]
    mov r2, #0x7
    bl func_0207f7f0
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    strb r1, [r0, #0x3a]
    ldr r0, [r10, #0x14]
    mov r1, #0x20
    bl func_0208108c
    ldr r0, [r10, #0x14]
    mov r1, #0x3e
    bl func_0208108c
    ldr r4, =0x4001008
    mov r5, #0x6
    ldrh r1, [r4, #0x0]
    sub r6, r4, #0x8
    add r0, r4, #0x48
    bic r1, r1, #0x3
    strh r1, [r4, #0x0]
    ldrh r3, [r4, #0x2]
    mov r1, #0x4
    mov r2, #0x18
    bic r3, r3, #0x3
    orr r3, r3, #0x1
    strh r3, [r4, #0x2]
    ldrh r7, [r4, #0x4]
    mov r3, #0xa
    bic r7, r7, #0x3
    orr r7, r7, #0x2
    strh r7, [r4, #0x4]
    ldrh r7, [r4, #0x6]
    bic r7, r7, #0x3
    orr r7, r7, #0x3
    strh r7, [r4, #0x6]
    ldr r4, [r6, #0x0]
    bic r4, r4, #0x1f00
    orr r4, r4, #0x1f00
    str r4, [r6, #0x0]
    str r5, [sp, #0x0]
    bl ColorEffect_ConfigureAlphaBlend
    mov r0, r10
    bl _ZN11AlchemyMenu13LoadInventoryEv
    mov r0, #0x1
    strb r0, [r10, #0x38f]
    rsb r3, r0, #0x1d8
    mov r0, #0x0
    strb r0, [r10, #0x390]
    add r0, r10, #0x74
    add r1, r10, #0x14c
    ldr r2, [r10, #0x38]
    bl _ZN18AlchemyIngredients16MarkKnownRecipesEP11RecipeTableP12RecipeRecordi
    mov r3, #0x0
    str r3, [sp, #0x0]
    add r0, r10, #0x35c
    str r0, [sp, #0x4]
    add r0, r10, #0x14c
    sub r1, r3, #0x1
    mov r2, r1
    bl func_02071ffc
    mov r0, #0x0
    strh r0, [sp, #0xc]
    mov r1, #0x10
    add r0, sp, #0xc
    str r1, [sp, #0x0]
    str r0, [sp, #0x4]
    add r0, r10, #0x300
    ldrsb r1, [r0, #0x84]
    ldrsb r2, [r0, #0x85]
    ldrb r3, [r10, #0x386]
    add r0, r10, #0x14c
    bl func_02071ffc
    ldr r1, [r10, #0x14c]
    mov r0, r10
    str r1, [r10, #0x2c]
    str r1, [r10, #0x30]
    bl _ZN11AlchemyMenu10CountPagesEv
    ldr r1, [r10, #0x38]
    ldr r2, =0x1d7
    add r0, r10, #0x74
    bl _ZN18AlchemyIngredients10SetRecordsEP12RecipeRecordt
    add r0, r10, #0x74
    add r1, r10, #0x14c
    bl _ZN18AlchemyIngredients8SetTableEP11RecipeTable
    add r0, r10, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x2
    bne @L0215b0a4
    ldr r0, [r10, #0x14]
    mov r1, #0x0
    mov r2, #0x1
    bl func_02081164
    mov r1, #0x1
    ldr r0, [r10, #0x14]
    mov r2, r1
    bl func_02081164
    ldr r0, [r10, #0x14]
    mov r1, #0x0
    bl func_020813ec
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    bl func_020813ec
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    bl func_02081da8
    cmp r0, #0x0
    movne r1, #0xc
    strneh r1, [r0, #0xb8]
    movne r1, #0x10
    strneh r1, [r0, #0xba]
    add r0, sp, #0x50
    mov r1, #0x400
    bl __clear
    bl func_020421a0
    mov r4, r0
    add r0, r10, #0x158
    mov r1, #0x0
    bl func_020e0434
    mov r1, #0xe3
    str r1, [sp, #0x0]
    mov r1, #0x0
    str r1, [sp, #0x4]
    mov r1, #0x1
    mov r2, r0
    str r1, [sp, #0x8]
    mov r0, r4
    mov r1, #0xc
    add r3, sp, #0x50
    bl func_02046608
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    add r2, sp, #0x50
    bl func_02080f8c
    ldr r0, [r10, #0x14]
    mov r1, #0x1
    bl func_020813ec
@L0215b0a4:
    add sp, sp, #0x450
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void AlchemyMenu::State_FadeIn()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    unsigned char step = step_;
    if (step == 0)
    {
        if (pot_->flags_ & (ALCHEMY_POT_LOADED | ALCHEMY_POT_NO_3D))
            step_ = step + 1;
    }
    else if (step == 1)
    {
        SetBrightness(resources, 0, 8);
        step_++;
    }
    else if (step == 2)
    {
        if (IsBrightnessTransitionActive(resources))
            return;
        state_ = AlchemyMenuState_Main;
        step_ = 0;
        if (flags_ & ALCHEMY_MENU_NO_SCENE)
        {
            background_ = 2;
            state_ = AlchemyMenuState_Book;
        }
    }
}

void AlchemyMenu::State_Book()
{
    if (step_ == 0)
    {
        background_ = 2;
        DrawBookTitle(1);
        group_ = 8;
        if (bookCursor_ < 0)
            bookCursor_ = 0x24;
        menu_->cursor_ = bookCursor_;
        func_020813ec(menu_, group_);
        func_0208203c(&repeat_);
        cursor_ = 0;
        step_++;
    }
    else if (step_ == 1)
    {
        cursor_ = &bookCursor_;
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            int open = 0;
            cursor_ = 0;
            filterCursor_ = -1;
            recipeCursor_ = -1;
            filterCategory_ = -1;
            filterKind_ = -1;
            switch (bookCursor_)
            {
            case 0x24:
                open = 1;
                break;
            case 0x25:
                filterCategory_ = 0;
                step_++;
                break;
            case 0x26:
                step_++;
                break;
            case 0x27:
                filterCategory_ = 7;
                open = 1;
                break;
            case 0x28:
                filterCategory_ = 8;
                open = 1;
                break;
            }
            if (open)
            {
                state_ = AlchemyMenuState_BookList;
                step_ = 0;
                SetLayoutBook(&layout_);
                flags_ |= ALCHEMY_MENU_BOOK;
            }
            short count = 0;
            func_02071ffc(&table_, filterCategory_, filterKind_, sort_, 0x10, &count);
            Recipe* recipes = table_.unk_0;
            recipes_ = recipes;
            pageStart_ = recipes;
            CountPages();
            func_0207fdcc(menu_, 8);
            return;
        }
        if (IsCancelled() || func_02012444(data_02114e30, 0x800))
        {
            *cursor_ = -1;
            cursor_ = 0;
            state_ = AlchemyMenuState_FadeOut;
            step_ = 0;
        }
    }
    else if (step_ == 2)
    {
        background_ = 2;
        DrawBookTitle(0);
        short book = bookCursor_;
        if (book == 0x25)
        {
            group_ = 0xc;
            if (filterCursor_ < 0)
                filterCursor_ = 0x48;
        }
        else if (book == 0x26)
        {
            group_ = 0xb;
            if (filterCursor_ < 0)
                filterCursor_ = 0x40;
        }
        menu_->cursor_ = filterCursor_;
        func_020813ec(menu_, group_);
        func_0208203c(&repeat_);
        cursor_ = 0;
        step_++;
    }
    else if (step_ == 3)
    {
        cursor_ = &filterCursor_;
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            state_ = AlchemyMenuState_BookList;
            step_ = 0;
            cursor_ = 0;
            recipeCursor_ = -1;
            GetFilter(filterCursor_, &filterCategory_, &filterKind_);
            short count = 0;
            func_02071ffc(&table_, filterCategory_, filterKind_, sort_, 0x10, &count);
            Recipe* recipes = table_.unk_0;
            recipes_ = recipes;
            pageStart_ = recipes;
            CountPages();
            func_0207fdcc(menu_, group_);
            state_ = AlchemyMenuState_BookList;
            step_ = 0;
            SetLayoutBook(&layout_);
            flags_ |= ALCHEMY_MENU_BOOK;
            return;
        }
        if (IsCancelled())
        {
            filterCursor_ = -1;
            func_0207fdcc(menu_, group_);
            step_ = 0;
        }
        CheckClose();
    }
}

void AlchemyMenu::State_BookList()
{
    AlchemyPot* pot = pot_;
    if (step_ == 0)
    {
        background_ = 1;
        DrawBookTitle(0);
        DrawFilter();
        DrawSort();
        group_ = 9;
        if (recipeCursor_ < 0)
            recipeCursor_ = 0x29;
        menu_->cursor_ = recipeCursor_;
        DrawRecipes();
        func_0208203c(&repeat_);
        cursor_ = 0;
        step_++;
    }
    else if (step_ == 1)
    {
        cursor_ = &recipeCursor_;
        int result = menuResult_;
        int pageChanged = 0;
        if (result & 0x10)
        {
            pageChanged = 1;
            page_++;
        }
        else if (result & 0x20)
        {
            pageChanged = 1;
            page_--;
        }
        if (page_ == 0xff)
            page_ = pages_ - 1;
        if (pages_ <= page_)
            page_ = 0;
        Recipe* recipe = GetRecipe(recipeCursor_ - 0x29);
        RecipeRecord* record = 0;
        if (recipe != 0)
        {
            record = ingredients_.FindRecord(recipe->id_);
            ingredients_.GetAmounts(recipe->id_, amounts_);
        }
        else
        {
            pot->CloseWindow();
        }
        pot->ShowRecipe(recipe, record, amounts_);
        if (pageChanged)
        {
            DrawRecipes();
            return;
        }
        unsigned char button = GetRecipeButton();
        if (button == 1)
        {
            ChangeSort();
            return;
        }
        if (button == 4)
        {
            if (recipe != 0 && record != 0)
            {
                pot->ShowNames((pot->window_.flags_ & ITEM_INFO_WINDOW_NAMES) ? 0 : 1);
                func_0205eaa0(data_02108760, 1, 0);
            }
            return;
        }
        if (!IsConfirmed() && IsCancelled())
        {
            flags_ &= ~ALCHEMY_MENU_BOOK;
            func_0207fdcc(menu_, group_);
            func_0207fdcc(menu_, 0xe);
            func_0207fdcc(menu_, 0xf);
            state_ = AlchemyMenuState_Book;
            step_ = 0;
            background_ = 2;
            pot->CloseWindow();
            if (bookCursor_ == 0x25 || bookCursor_ == 0x26)
                step_ = 2;
        }
        CheckClose();
    }
}

void AlchemyMenu::State_Main()
{
    Menu* menu = menu_;
    if (step_ == 0)
    {
        pot_->ShowNames(1);
        background_ = 0;
        group_ = 2;
        if (mainCursor_ < 0)
            mainCursor_ = func_02080468(menu, group_);
        menu->cursor_ = mainCursor_;
        func_020813ec(menu, group_);
        DrawMainTexts();
        func_02081ea4(menu, group_, 0);
        func_0208203c(&repeat_);
        cursor_ = 0;
        step_++;
        if (mainCursor_ == 4)
            func_02080c04(menu, 3);
        else
            func_02080c20(menu, 3);
    }
    else if (step_ == 1)
    {
        cursor_ = &mainCursor_;
        if (previousCursor_ != *cursor_)
        {
            if (mainCursor_ == 4)
                func_02080c04(menu, 3);
            else
                func_02080c20(menu, 3);
            DrawMainTexts();
        }
        arrowTimer_ = 0;
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            switch (mainCursor_)
            {
            case 2:
                bookCursor_ = -1;
                func_0207fe44(menu);
                state_ = AlchemyMenuState_Recipes;
                step_ = 0;
                HIDE_ELEMENT(&layout_, 0x50);
                SHOW_ELEMENT(&layout_, 0x4f);
                HIDE_ELEMENT(&layout_, 0xe);
                SHOW_ELEMENT(&layout_, 0xf);
                HIDE_ELEMENT(&layout_, 0x15);
                break;
            case 3:
            {
                LoadInventory();
                unsigned short* sizes = sizes_;
                unsigned char i;
                int found = 0;
                if (sizes != 0)
                {
                    for (i = 0; i < 9; i++)
                    {
                        if (sizes[i] != 0)
                        {
                            found = 1;
                            break;
                        }
                    }
                    if (sizes[8] != 0)
                        found = 1;
                }
                if (found)
                {
                    categoryCursor_ = -1;
                    itemCursor_ = -1;
                    func_0207fe44(menu);
                    state_ = AlchemyMenuState_Ingredient1;
                    step_ = 0;
                    pot_->ShowNames(1);
                    message_ = 0x24;
                    messageStep_ = 0;
                    flags_ |= ALCHEMY_MENU_MESSAGE | ALCHEMY_MENU_100;
                    break;
                }
                flags_ |= ALCHEMY_MENU_MESSAGE;
                message_ = 0x35;
                messageStep_ = 0;
                func_02081ea4(menu, group_, 1);
                step_ = 0;
                func_0208203c(&repeat_);
                cursor_ = 0;
                return;
            }
            case 4:
                state_ = AlchemyMenuState_FadeOut;
                step_ = 0;
                break;
            }
            func_0207fdcc(menu, 3);
            func_0207fdcc(menu, group_);
            return;
        }
        if (IsCancelled() || func_02012444(data_02114e30, 0x800))
        {
            func_0207fe44(menu);
            state_ = AlchemyMenuState_FadeOut;
            step_ = 0;
        }
    }
}

// NONMATCHING: the C matches 99.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::State_Ingredient1()
{
    Menu* menu = menu_;
    if (step_ == 0)
    {
        func_02080c20(menu, 0x10);
        func_02080c20(menu, 0x11);
        func_02080c68(menu, 0x11, 1);
        pot_->flags_ &= ~ALCHEMY_POT_MAKING;
        func_0207fdcc(menu, 0);
        func_0207fdcc(menu, 1);
        group_ = 0x10;
        if (categoryCursor_ < 0)
            categoryCursor_ = func_02080468(menu, group_);
        func_02081ea4(menu, group_, 0);
        func_020813ec(menu, group_);
        func_02080c68(menu, group_, 0);
        item_ = -1;
        count_ = 0;
        for (unsigned char i = 0; i < 3; i++)
        {
            chosenItems_[i] = -1;
            chosenCounts_[i] = 0;
        }
        CountItemPages();
        func_02081ea4(menu, 0x11, 0);
        func_020804fc(menu, 0x11);
        DrawItems();
        flags_ |= ALCHEMY_MENU_ITEMS;
        SetLayoutIngredients(&layout_);
        pot_->SetIngredients(chosenItems_, chosenCounts_);
        func_0208203c(&repeat_);
        cursor_ = 0;
        pot_->ShowItem(-1, 0);
        step_++;
    }
    else if (step_ == 1)
    {
        if (UpdateItemButtons())
            return;
        cursor_ = &categoryCursor_;
        if (previousCursor_ != *cursor_)
        {
            CountItemPages();
            DrawItems();
        }
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            if (!HasCategoryItems())
                return;
            func_02080c68(menu, group_, 1);
            func_02081ea4(menu, group_, 1);
            func_02080c68(menu, 0x11, 0);
            step_++;
        }
        else if (IsCancelled())
        {
            resetBlend_ = 1;
            func_0207fe44(menu);
            func_0208203c(&repeat_);
            cursor_ = 0;
            itemCursor_ = -1;
            state_ = AlchemyMenuState_Main;
            step_ = 0;
            flags_ &= ~ALCHEMY_MENU_ITEMS;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0;
            messageStep_ = 0;
        }
        CheckClose();
    }
    else if (step_ == 2)
    {
        for (unsigned char i = 0; i < 3; i++)
        {
            chosenItems_[i] = -1;
            chosenCounts_[i] = 0;
        }
        OpenItems();
        pot_->SetIngredients(chosenItems_, chosenCounts_);
        step_++;
    }
    else if (step_ == 3)
    {
        if (UpdateItems())
            return;
        if (IsConfirmed() && previousCursor_ == *cursor_)
        {
            unsigned char category = 0;
            short item = 0;
            unsigned char count = 0;
            GetSelectedItem(&category, &item, &count);
            if (count != 0)
            {
                func_0205eaa0(data_02108760, 1, 0);
                func_0208203c(&repeat_);
                cursor_ = 0;
                func_02081ea4(menu_, 0x11, 1);
                category_ = category;
                item_ = item;
                count_ = 1;
                step_++;
                flags_ &= ~ALCHEMY_MENU_ITEMS;
                flags_ |= ALCHEMY_MENU_MESSAGE;
                message_ = 9;
                messageStep_ = 0;
                return;
            }
        }
        else if (IsCancelled())
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            itemCursor_ = -1;
            step_ = 0;
        }
        CheckClose();
    }
    else if (step_ == 4)
    {
        OpenCount();
        repeatDelay_ = 0;
        step_++;
    }
    else if (step_ == 5)
    {
        arrowTimer_ = 0;
        int result = UpdateCount();
        if (result == 1)
            return;
        if (func_02012444(data_02114e30, 1) || result == 2)
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            flags_ &= ~ALCHEMY_MENU_COUNT;
            func_0207fdcc(menu, 6);
            TakeIngredient(category_, item_, count_);
            pot_->SetIngredients(chosenItems_, chosenCounts_);
            state_ = AlchemyMenuState_Ingredient2;
            step_ = 0;
            times_ = count_;
            message_ = 0x39;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE | ALCHEMY_MENU_100;
            return;
        }
        if (IsCancelled() || result == 3)
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            flags_ &= ~ALCHEMY_MENU_COUNT;
            func_0207fdcc(menu, 6);
            step_ = 0;
            message_ = 0x24;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE | ALCHEMY_MENU_100;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10AlchemyPot14SetIngredientsEPsPh(); // AlchemyPot::SetIngredients
    void _ZN10AlchemyPot8ShowItemEsa(); // AlchemyPot::ShowItem
    void _ZN11AlchemyMenu10CheckCloseEv(); // AlchemyMenu::CheckClose
    void _ZN11AlchemyMenu11IsCancelledEv(); // AlchemyMenu::IsCancelled
    void _ZN11AlchemyMenu11IsConfirmedEv(); // AlchemyMenu::IsConfirmed
    void _ZN11AlchemyMenu11UpdateCountEv(); // AlchemyMenu::UpdateCount
    void _ZN11AlchemyMenu11UpdateItemsEv(); // AlchemyMenu::UpdateItems
    void _ZN11AlchemyMenu14CountItemPagesEv(); // AlchemyMenu::CountItemPages
    void _ZN11AlchemyMenu14TakeIngredientEssh(); // AlchemyMenu::TakeIngredient
    void _ZN11AlchemyMenu15GetSelectedItemEPhPsS0_(); // AlchemyMenu::GetSelectedItem
    void _ZN11AlchemyMenu16HasCategoryItemsEv(); // AlchemyMenu::HasCategoryItems
    void _ZN11AlchemyMenu17UpdateItemButtonsEv(); // AlchemyMenu::UpdateItemButtons
    void _ZN11AlchemyMenu9DrawItemsEv(); // AlchemyMenu::DrawItems
    void _ZN11AlchemyMenu9OpenCountEv(); // AlchemyMenu::OpenCount
    void _ZN11AlchemyMenu9OpenItemsEv(); // AlchemyMenu::OpenItems
}

asm void AlchemyMenu::State_Ingredient1()
{
    stmdb sp!, {r3, r4, r5, r6, lr}
    sub sp, sp, #0x4
    mov r5, r0
    ldrb r1, [r5, #0x390]
    ldr r4, [r5, #0x14]
    cmp r1, #0x0
    bne @L0215bd10
    mov r0, r4
    mov r1, #0x10
    bl func_02080c20
    mov r0, r4
    mov r1, #0x11
    bl func_02080c20
    mov r0, r4
    mov r1, #0x11
    mov r2, #0x1
    bl func_02080c68
    ldr r1, [r5, #0x10]
    mov r0, r4
    add r2, r1, #0xa00
    ldrh r3, [r2, #0xe2]
    mov r1, #0x0
    bic r3, r3, #0x10
    strh r3, [r2, #0xe2]
    bl func_0207fdcc
    mov r0, r4
    mov r1, #0x1
    bl func_0207fdcc
    add r0, r5, #0x300
    mov r1, #0x10
    strh r1, [r0, #0x6e]
    ldrsh r1, [r0, #0x62]
    cmp r1, #0x0
    bge @L0215bc18
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_02080468
    add r1, r5, #0x300
    strh r0, [r1, #0x62]
@L0215bc18:
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x0
    bl func_02081ea4
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_020813ec
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x0
    bl func_02080c68
    mov r6, #0x0
    add r0, r5, #0x300
    mvn r3, #0x0
    strh r3, [r0, #0x70]
    strb r6, [r5, #0x38b]
    mov r2, r6
    b @L0215bc88
@L0215bc6c:
    add r0, r5, r6, lsl #0x1
    add r0, r0, #0x300
    strh r3, [r0, #0x78]
    add r1, r5, r6
    add r0, r6, #0x1
    strb r2, [r1, #0x38c]
    and r6, r0, #0xff
@L0215bc88:
    cmp r6, #0x3
    blo @L0215bc6c
    mov r0, r5
    bl _ZN11AlchemyMenu14CountItemPagesEv
    mov r0, r4
    mov r1, #0x11
    mov r2, #0x0
    bl func_02081ea4
    mov r0, r4
    mov r1, #0x11
    bl func_020804fc
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
    add r1, r5, #0x300
    ldrh r2, [r1, #0x94]
    add r0, r5, #0x100
    orr r2, r2, #0x10
    strh r2, [r1, #0x94]
    bl SetLayoutIngredients
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    add r0, r5, #0x9c
    bl func_0208203c
    mov r2, #0x0
    str r2, [r5, #0x44]
    ldr r0, [r5, #0x10]
    sub r1, r2, #0x1
    bl _ZN10AlchemyPot8ShowItemEsa
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215c144
@L0215bd10:
    cmp r1, #0x1
    bne @L0215be50
    bl _ZN11AlchemyMenu17UpdateItemButtonsEv
    cmp r0, #0x0
    bne @L0215c144
    add r0, r5, #0x62
    add r2, r0, #0x300
    str r2, [r5, #0x44]
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x5e]
    ldrsh r0, [r2, #0x0]
    cmp r1, r0
    beq @L0215bd54
    mov r0, r5
    bl _ZN11AlchemyMenu14CountItemPagesEv
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
@L0215bd54:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsConfirmedEv
    cmp r0, #0x0
    beq @L0215bddc
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r1, #0x0
    mov r0, r5
    str r1, [r5, #0x44]
    bl _ZN11AlchemyMenu16HasCategoryItemsEv
    cmp r0, #0x0
    beq @L0215c144
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x1
    bl func_02080c68
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x1
    bl func_02081ea4
    mov r0, r4
    mov r1, #0x11
    mov r2, #0x0
    bl func_02080c68
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215be44
@L0215bddc:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    beq @L0215be44
    mov r1, #0x1
    mov r0, r4
    strb r1, [r5, #0x432]
    bl func_0207fe44
    add r0, r5, #0x9c
    bl func_0208203c
    mov r2, #0x0
    str r2, [r5, #0x44]
    sub r1, r2, #0x1
    add r0, r5, #0x300
    strh r1, [r0, #0x64]
    mov r1, #0x4
    strb r1, [r5, #0x38f]
    strb r2, [r5, #0x390]
    ldrh r1, [r0, #0x94]
    bic r1, r1, #0x10
    strh r1, [r0, #0x94]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x20
    strh r1, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r2, [r5, #0x392]
@L0215be44:
    mov r0, r5
    bl _ZN11AlchemyMenu10CheckCloseEv
    b @L0215c144
@L0215be50:
    cmp r1, #0x2
    bne @L0215beb4
    mov r4, #0x0
    mvn r3, #0x0
    mov r2, r4
    b @L0215be84
@L0215be68:
    add r0, r5, r4, lsl #0x1
    add r0, r0, #0x300
    strh r3, [r0, #0x78]
    add r1, r5, r4
    add r0, r4, #0x1
    strb r2, [r1, #0x38c]
    and r4, r0, #0xff
@L0215be84:
    cmp r4, #0x3
    blo @L0215be68
    mov r0, r5
    bl _ZN11AlchemyMenu9OpenItemsEv
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215c144
@L0215beb4:
    cmp r1, #0x3
    bne @L0215bfe0
    bl _ZN11AlchemyMenu11UpdateItemsEv
    cmp r0, #0x0
    bne @L0215c144
    mov r0, r5
    bl _ZN11AlchemyMenu11IsConfirmedEv
    cmp r0, #0x0
    beq @L0215bfa4
    ldr r1, [r5, #0x44]
    add r0, r5, #0x300
    ldrsh r2, [r0, #0x5e]
    ldrsh r0, [r1, #0x0]
    cmp r2, r0
    bne @L0215bfa4
    mov r4, #0x0
    add r1, sp, #0x1
    add r2, sp, #0x2
    add r3, sp, #0x0
    mov r0, r5
    strb r4, [sp, #0x0]
    strb r4, [sp, #0x1]
    strh r4, [sp, #0x2]
    bl _ZN11AlchemyMenu15GetSelectedItemEPhPsS0_
    ldrb r0, [sp, #0x0]
    cmp r0, #0x0
    beq @L0215bfd4
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, r4
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, r4
    str r0, [r5, #0x44]
    ldr r0, [r5, #0x14]
    mov r1, #0x11
    mov r2, #0x1
    bl func_02081ea4
    ldrb r1, [sp, #0x1]
    add r0, r5, #0x300
    mov r3, #0x1
    strb r1, [r5, #0x38a]
    ldrsh r4, [sp, #0x2]
    mov r2, #0x9
    mov r1, #0x0
    strh r4, [r0, #0x70]
    strb r3, [r5, #0x38b]
    ldrb r3, [r5, #0x390]
    add r3, r3, #0x1
    strb r3, [r5, #0x390]
    ldrh r3, [r0, #0x94]
    bic r3, r3, #0x10
    strh r3, [r0, #0x94]
    ldrh r3, [r0, #0x94]
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    b @L0215c144
@L0215bfa4:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    beq @L0215bfd4
    add r0, r5, #0x9c
    bl func_0208203c
    mov r2, #0x0
    str r2, [r5, #0x44]
    sub r1, r2, #0x1
    add r0, r5, #0x300
    strh r1, [r0, #0x64]
    strb r2, [r5, #0x390]
@L0215bfd4:
    mov r0, r5
    bl _ZN11AlchemyMenu10CheckCloseEv
    b @L0215c144
@L0215bfe0:
    cmp r1, #0x4
    bne @L0215c004
    bl _ZN11AlchemyMenu9OpenCountEv
    mov r0, #0x0
    strb r0, [r5, #0x393]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215c144
@L0215c004:
    cmp r1, #0x5
    bne @L0215c144
    mov r1, #0x0
    strb r1, [r5, #0x42c]
    bl _ZN11AlchemyMenu11UpdateCountEv
    mov r6, r0
    cmp r6, #0x1
    beq @L0215c144
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    bne @L0215c040
    cmp r6, #0x2
    bne @L0215c0dc
@L0215c040:
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, #0x0
    str r0, [r5, #0x44]
    add r2, r5, #0x300
    ldrh r3, [r2, #0x94]
    mov r0, r4
    mov r1, #0x6
    bic r3, r3, #0x8
    strh r3, [r2, #0x94]
    bl func_0207fdcc
    add r0, r5, #0x300
    ldrsh r2, [r0, #0x70]
    ldrb r1, [r5, #0x38a]
    ldrb r3, [r5, #0x38b]
    mov r0, r5
    bl _ZN11AlchemyMenu14TakeIngredientEssh
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    mov r0, #0x6
    strb r0, [r5, #0x38f]
    mov r3, #0x0
    strb r3, [r5, #0x390]
    ldrb r2, [r5, #0x38b]
    mov r1, #0x39
    add r0, r5, #0x300
    strb r2, [r5, #0x387]
    strh r1, [r0, #0x7e]
    strb r3, [r5, #0x392]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x120
    strh r1, [r0, #0x94]
    b @L0215c144
@L0215c0dc:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    bne @L0215c0f4
    cmp r6, #0x3
    bne @L0215c144
@L0215c0f4:
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, #0x0
    str r0, [r5, #0x44]
    add r2, r5, #0x300
    ldrh r3, [r2, #0x94]
    mov r0, r4
    mov r1, #0x6
    bic r3, r3, #0x8
    strh r3, [r2, #0x94]
    bl func_0207fdcc
    mov r2, #0x0
    strb r2, [r5, #0x390]
    add r0, r5, #0x300
    mov r1, #0x24
    strh r1, [r0, #0x7e]
    strb r2, [r5, #0x392]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x120
    strh r1, [r0, #0x94]
@L0215c144:
    add sp, sp, #0x4
    ldmia sp!, {r3, r4, r5, r6, pc}
}
#endif

// NONMATCHING: the C matches 99.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::State_Ingredient2()
{
    Menu* menu = menu_;
    if (step_ == 0)
    {
        func_0207fdcc(menu, 0);
        func_0207fdcc(menu, 1);
        group_ = 0x10;
        if (categoryCursor_ < 0)
            categoryCursor_ = func_02080468(menu, group_);
        func_02081ea4(menu, group_, 0);
        func_020813ec(menu, group_);
        func_02080c68(menu, group_, 0);
        item_ = -1;
        count_ = 0;
        CountItemPages();
        func_02081ea4(menu, 0x11, 0);
        func_020804fc(menu, 0x11);
        DrawItems();
        flags_ |= ALCHEMY_MENU_ITEMS;
        func_02080c68(menu, 0x11, 1);
        SetLayoutIngredients(&layout_);
        pot_->SetIngredients(chosenItems_, chosenCounts_);
        func_0208203c(&repeat_);
        cursor_ = 0;
        pot_->ShowItem(-1, 0);
        step_++;
    }
    else if (step_ == 1)
    {
        if (UpdateItemButtons())
            return;
        cursor_ = &categoryCursor_;
        if (previousCursor_ != *cursor_)
        {
            CountItemPages();
            DrawItems();
        }
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            if (!HasCategoryItems())
                return;
            func_02080c68(menu, group_, 1);
            func_02081ea4(menu, group_, 1);
            func_02080c68(menu, 0x11, 0);
            step_++;
        }
        else if (IsCancelled())
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            state_ = AlchemyMenuState_Ingredient1;
            step_ = 0;
            ReturnIngredient();
            pot_->SetIngredients(chosenItems_, chosenCounts_);
            DrawItems();
        }
        CheckClose();
    }
    else if (step_ == 2)
    {
        OpenItems();
        pot_->SetIngredients(chosenItems_, chosenCounts_);
        step_++;
    }
    else if (step_ == 3)
    {
        if (UpdateItems())
            return;
        if (IsConfirmed() && previousCursor_ == *cursor_)
        {
            unsigned char category = 0;
            short item = 0;
            unsigned char count = 0;
            GetSelectedItem(&category, &item, &count);
            if (count != 0)
            {
                func_0205eaa0(data_02108760, 1, 0);
                func_0208203c(&repeat_);
                cursor_ = 0;
                func_02081ea4(menu_, 0x11, 1);
                category_ = category;
                item_ = item;
                count_ = 1;
                step_++;
                flags_ &= ~ALCHEMY_MENU_ITEMS;
                flags_ |= ALCHEMY_MENU_MESSAGE;
                message_ = 9;
                messageStep_ = 0;
                return;
            }
        }
        else if (IsCancelled())
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            itemCursor_ = -1;
            step_ = 0;
        }
        CheckClose();
    }
    else if (step_ == 4)
    {
        OpenCount();
        repeatDelay_ = 0;
        step_++;
    }
    else if (step_ == 5)
    {
        arrowTimer_ = 0;
        int result = UpdateCount();
        if (result == 1)
            return;
        if (func_02012444(data_02114e30, 1) || result == 2)
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            flags_ &= ~ALCHEMY_MENU_COUNT;
            func_0207fdcc(menu, 6);
            TakeIngredient(category_, item_, count_);
            pot_->SetIngredients(chosenItems_, chosenCounts_);
            state_ = AlchemyMenuState_Ingredient3;
            step_ = 0;
            times_ = count_;
            message_ = 0x3a;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE | ALCHEMY_MENU_100;
            return;
        }
        if (IsCancelled() || result == 3)
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            flags_ &= ~ALCHEMY_MENU_COUNT;
            func_0207fdcc(menu, 6);
            step_ = 0;
            message_ = 0x24;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE | ALCHEMY_MENU_100;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11AlchemyMenu16ReturnIngredientEv(); // AlchemyMenu::ReturnIngredient
}

asm void AlchemyMenu::State_Ingredient2()
{
    stmdb sp!, {r3, r4, r5, r6, lr}
    sub sp, sp, #0x4
    mov r5, r0
    ldrb r1, [r5, #0x390]
    ldr r4, [r5, #0x14]
    cmp r1, #0x0
    bne @L0215c290
    mov r0, r4
    mov r1, #0x0
    bl func_0207fdcc
    mov r0, r4
    mov r1, #0x1
    bl func_0207fdcc
    add r0, r5, #0x300
    mov r1, #0x10
    strh r1, [r0, #0x6e]
    ldrsh r1, [r0, #0x62]
    cmp r1, #0x0
    bge @L0215c1b4
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_02080468
    add r1, r5, #0x300
    strh r0, [r1, #0x62]
@L0215c1b4:
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x0
    bl func_02081ea4
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_020813ec
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x0
    bl func_02080c68
    add r1, r5, #0x300
    mvn r2, #0x0
    mov r0, r5
    strh r2, [r1, #0x70]
    mov r1, #0x0
    strb r1, [r5, #0x38b]
    bl _ZN11AlchemyMenu14CountItemPagesEv
    mov r0, r4
    mov r1, #0x11
    mov r2, #0x0
    bl func_02081ea4
    mov r0, r4
    mov r1, #0x11
    bl func_020804fc
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
    mov r0, r4
    add r3, r5, #0x300
    ldrh r4, [r3, #0x94]
    mov r1, #0x11
    mov r2, #0x1
    orr r4, r4, #0x10
    strh r4, [r3, #0x94]
    bl func_02080c68
    add r0, r5, #0x100
    bl SetLayoutIngredients
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    add r0, r5, #0x9c
    bl func_0208203c
    mov r2, #0x0
    str r2, [r5, #0x44]
    ldr r0, [r5, #0x10]
    sub r1, r2, #0x1
    bl _ZN10AlchemyPot8ShowItemEsa
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215c670
@L0215c290:
    cmp r1, #0x1
    bne @L0215c3b4
    bl _ZN11AlchemyMenu17UpdateItemButtonsEv
    cmp r0, #0x0
    bne @L0215c670
    add r0, r5, #0x62
    add r2, r0, #0x300
    str r2, [r5, #0x44]
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x5e]
    ldrsh r0, [r2, #0x0]
    cmp r1, r0
    beq @L0215c2d4
    mov r0, r5
    bl _ZN11AlchemyMenu14CountItemPagesEv
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
@L0215c2d4:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsConfirmedEv
    cmp r0, #0x0
    beq @L0215c35c
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r1, #0x0
    mov r0, r5
    str r1, [r5, #0x44]
    bl _ZN11AlchemyMenu16HasCategoryItemsEv
    cmp r0, #0x0
    beq @L0215c670
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x1
    bl func_02080c68
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x1
    bl func_02081ea4
    mov r0, r4
    mov r1, #0x11
    mov r2, #0x0
    bl func_02080c68
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215c3a8
@L0215c35c:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    beq @L0215c3a8
    add r0, r5, #0x9c
    bl func_0208203c
    mov r1, #0x0
    str r1, [r5, #0x44]
    mov r0, #0x5
    strb r0, [r5, #0x38f]
    mov r0, r5
    strb r1, [r5, #0x390]
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
@L0215c3a8:
    mov r0, r5
    bl _ZN11AlchemyMenu10CheckCloseEv
    b @L0215c670
@L0215c3b4:
    cmp r1, #0x2
    bne @L0215c3e0
    bl _ZN11AlchemyMenu9OpenItemsEv
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215c670
@L0215c3e0:
    cmp r1, #0x3
    bne @L0215c50c
    bl _ZN11AlchemyMenu11UpdateItemsEv
    cmp r0, #0x0
    bne @L0215c670
    mov r0, r5
    bl _ZN11AlchemyMenu11IsConfirmedEv
    cmp r0, #0x0
    beq @L0215c4d0
    ldr r1, [r5, #0x44]
    add r0, r5, #0x300
    ldrsh r2, [r0, #0x5e]
    ldrsh r0, [r1, #0x0]
    cmp r2, r0
    bne @L0215c4d0
    mov r4, #0x0
    add r1, sp, #0x1
    add r2, sp, #0x2
    add r3, sp, #0x0
    mov r0, r5
    strb r4, [sp, #0x0]
    strb r4, [sp, #0x1]
    strh r4, [sp, #0x2]
    bl _ZN11AlchemyMenu15GetSelectedItemEPhPsS0_
    ldrb r0, [sp, #0x0]
    cmp r0, #0x0
    beq @L0215c500
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, r4
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, r4
    str r0, [r5, #0x44]
    ldr r0, [r5, #0x14]
    mov r1, #0x11
    mov r2, #0x1
    bl func_02081ea4
    ldrb r1, [sp, #0x1]
    add r0, r5, #0x300
    mov r3, #0x1
    strb r1, [r5, #0x38a]
    ldrsh r4, [sp, #0x2]
    mov r2, #0x9
    mov r1, #0x0
    strh r4, [r0, #0x70]
    strb r3, [r5, #0x38b]
    ldrb r3, [r5, #0x390]
    add r3, r3, #0x1
    strb r3, [r5, #0x390]
    ldrh r3, [r0, #0x94]
    bic r3, r3, #0x10
    strh r3, [r0, #0x94]
    ldrh r3, [r0, #0x94]
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    b @L0215c670
@L0215c4d0:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    beq @L0215c500
    add r0, r5, #0x9c
    bl func_0208203c
    mov r2, #0x0
    str r2, [r5, #0x44]
    sub r1, r2, #0x1
    add r0, r5, #0x300
    strh r1, [r0, #0x64]
    strb r2, [r5, #0x390]
@L0215c500:
    mov r0, r5
    bl _ZN11AlchemyMenu10CheckCloseEv
    b @L0215c670
@L0215c50c:
    cmp r1, #0x4
    bne @L0215c530
    bl _ZN11AlchemyMenu9OpenCountEv
    mov r0, #0x0
    strb r0, [r5, #0x393]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215c670
@L0215c530:
    cmp r1, #0x5
    bne @L0215c670
    mov r1, #0x0
    strb r1, [r5, #0x42c]
    bl _ZN11AlchemyMenu11UpdateCountEv
    mov r6, r0
    cmp r6, #0x1
    beq @L0215c670
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    bne @L0215c56c
    cmp r6, #0x2
    bne @L0215c608
@L0215c56c:
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, #0x0
    str r0, [r5, #0x44]
    add r2, r5, #0x300
    ldrh r3, [r2, #0x94]
    mov r0, r4
    mov r1, #0x6
    bic r3, r3, #0x8
    strh r3, [r2, #0x94]
    bl func_0207fdcc
    add r0, r5, #0x300
    ldrsh r2, [r0, #0x70]
    ldrb r1, [r5, #0x38a]
    ldrb r3, [r5, #0x38b]
    mov r0, r5
    bl _ZN11AlchemyMenu14TakeIngredientEssh
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    mov r0, #0x7
    strb r0, [r5, #0x38f]
    mov r3, #0x0
    strb r3, [r5, #0x390]
    ldrb r2, [r5, #0x38b]
    mov r1, #0x3a
    add r0, r5, #0x300
    strb r2, [r5, #0x387]
    strh r1, [r0, #0x7e]
    strb r3, [r5, #0x392]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x120
    strh r1, [r0, #0x94]
    b @L0215c670
@L0215c608:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    bne @L0215c620
    cmp r6, #0x3
    bne @L0215c670
@L0215c620:
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, #0x0
    str r0, [r5, #0x44]
    add r2, r5, #0x300
    ldrh r3, [r2, #0x94]
    mov r0, r4
    mov r1, #0x6
    bic r3, r3, #0x8
    strh r3, [r2, #0x94]
    bl func_0207fdcc
    mov r2, #0x0
    strb r2, [r5, #0x390]
    add r0, r5, #0x300
    mov r1, #0x24
    strh r1, [r0, #0x7e]
    strb r2, [r5, #0x392]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x120
    strh r1, [r0, #0x94]
@L0215c670:
    add sp, sp, #0x4
    ldmia sp!, {r3, r4, r5, r6, pc}
}
#endif

// NONMATCHING: the C matches 98.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::State_Ingredient3()
{
    Menu* menu = menu_;
    if (step_ == 0)
    {
        func_0207fdcc(menu, 0);
        func_0207fdcc(menu, 1);
        group_ = 0x10;
        if (categoryCursor_ < 0)
            categoryCursor_ = func_02080468(menu, group_);
        func_02081ea4(menu, group_, 0);
        func_020813ec(menu, group_);
        func_02080c68(menu, group_, 0);
        item_ = -1;
        count_ = 0;
        CountItemPages();
        func_02081ea4(menu, 0x11, 0);
        func_020804fc(menu, 0x11);
        DrawItems();
        flags_ |= ALCHEMY_MENU_ITEMS | ALCHEMY_MENU_MESSAGE;
        func_02080c68(menu, 0x11, 1);
        SetLayoutIngredients(&layout_);
        pot_->SetIngredients(chosenItems_, chosenCounts_);
        func_0208203c(&repeat_);
        cursor_ = 0;
        pot_->ShowItem(-1, 0);
        step_++;
    }
    else if (step_ == 1)
    {
        if (UpdateItemButtons())
            return;
        cursor_ = &categoryCursor_;
        if (previousCursor_ != *cursor_)
        {
            CountItemPages();
            DrawItems();
        }
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            if (HasCategoryItems())
            {
                func_02080c68(menu, group_, 1);
                func_02081ea4(menu, group_, 1);
                func_02080c68(menu, 0x11, 0);
                step_++;
                return;
            }
        }
        else
        {
            if (IsCancelled())
            {
                func_0208203c(&repeat_);
                cursor_ = 0;
                state_ = AlchemyMenuState_Ingredient2;
                step_ = 0;
                ReturnIngredient();
                pot_->SetIngredients(chosenItems_, chosenCounts_);
                DrawItems();
            }
            CheckClose();
        }
    }
    else if (step_ == 2)
    {
        OpenItems();
        pot_->SetIngredients(chosenItems_, chosenCounts_);
        step_++;
    }
    else if (step_ == 3)
    {
        if (UpdateItems())
            return;
        if (IsConfirmed() && previousCursor_ == *cursor_)
        {
            unsigned char category = 0;
            short item = 0;
            unsigned char count = 0;
            GetSelectedItem(&category, &item, &count);
            if (count != 0)
            {
                func_0205eaa0(data_02108760, 1, 0);
                func_0208203c(&repeat_);
                cursor_ = 0;
                func_02081ea4(menu_, 0x11, 1);
                category_ = category;
                item_ = item;
                count_ = 1;
                step_++;
                flags_ &= ~ALCHEMY_MENU_ITEMS;
                flags_ |= ALCHEMY_MENU_MESSAGE;
                message_ = 9;
                messageStep_ = 0;
                return;
            }
        }
        else if (IsCancelled())
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            itemCursor_ = -1;
            step_ = 0;
        }
        CheckClose();
    }
    else if (step_ == 4)
    {
        OpenCount();
        repeatDelay_ = 0;
        step_++;
    }
    else if (step_ == 5)
    {
        arrowTimer_ = 0;
        int result = UpdateCount();
        if (result == 1)
            return;
        if (func_02012444(data_02114e30, 1) || result == 2)
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            flags_ &= ~ALCHEMY_MENU_COUNT;
            func_0207fdcc(menu, 6);
            TakeIngredient(category_, item_, count_);
            pot_->SetIngredients(chosenItems_, chosenCounts_);
            step_++;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0xa;
            messageStep_ = 0;
            return;
        }
        if (IsCancelled() || result == 3)
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            flags_ &= ~ALCHEMY_MENU_COUNT;
            func_0207fdcc(menu, 6);
            step_ = 0;
            message_ = 0x24;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE | ALCHEMY_MENU_100;
            return;
        }
    }
    else if (step_ == 6)
    {
        pot_->ShowNames(1);
        OpenChoice();
        step_++;
    }
    else if (step_ == 7)
    {
        switch (UpdateChoice())
        {
        case 1:
            state_ = AlchemyMenuState_Make;
            showResult_ = 0;
            step_ = 0;
            break;
        case -1:
            while (chosenItems_[0] > 0)
                ReturnIngredient();
            pot_->SetIngredients(chosenItems_, chosenCounts_);
            state_ = AlchemyMenuState_Ingredient1;
            step_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0x24;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_100;
            break;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10AlchemyPot9ShowNamesEi(); // AlchemyPot::ShowNames
    void _ZN11AlchemyMenu10OpenChoiceEv(); // AlchemyMenu::OpenChoice
    void _ZN11AlchemyMenu12UpdateChoiceEv(); // AlchemyMenu::UpdateChoice
}

asm void AlchemyMenu::State_Ingredient3()
{
    stmdb sp!, {r3, r4, r5, r6, lr}
    sub sp, sp, #0x4
    mov r5, r0
    ldrb r1, [r5, #0x390]
    ldr r4, [r5, #0x14]
    cmp r1, #0x0
    bne @L0215c7bc
    mov r0, r4
    mov r1, #0x0
    bl func_0207fdcc
    mov r0, r4
    mov r1, #0x1
    bl func_0207fdcc
    add r0, r5, #0x300
    mov r1, #0x10
    strh r1, [r0, #0x6e]
    ldrsh r1, [r0, #0x62]
    cmp r1, #0x0
    bge @L0215c6e0
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_02080468
    add r1, r5, #0x300
    strh r0, [r1, #0x62]
@L0215c6e0:
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x0
    bl func_02081ea4
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    bl func_020813ec
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x0
    bl func_02080c68
    add r1, r5, #0x300
    mvn r2, #0x0
    strh r2, [r1, #0x70]
    mov r1, #0x0
    mov r0, r5
    strb r1, [r5, #0x38b]
    bl _ZN11AlchemyMenu14CountItemPagesEv
    mov r0, r4
    mov r1, #0x11
    mov r2, #0x0
    bl func_02081ea4
    mov r0, r4
    mov r1, #0x11
    bl func_020804fc
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
    add r3, r5, #0x300
    mov r0, r4
    ldrh r4, [r3, #0x94]
    mov r1, #0x11
    mov r2, #0x1
    orr r4, r4, #0x30
    strh r4, [r3, #0x94]
    bl func_02080c68
    add r0, r5, #0x100
    bl SetLayoutIngredients
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    add r0, r5, #0x9c
    bl func_0208203c
    mov r2, #0x0
    str r2, [r5, #0x44]
    ldr r0, [r5, #0x10]
    sub r1, r2, #0x1
    bl _ZN10AlchemyPot8ShowItemEsa
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215cc60
@L0215c7bc:
    cmp r1, #0x1
    bne @L0215c8e0
    bl _ZN11AlchemyMenu17UpdateItemButtonsEv
    cmp r0, #0x0
    bne @L0215cc60
    add r0, r5, #0x62
    add r2, r0, #0x300
    str r2, [r5, #0x44]
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x5e]
    ldrsh r0, [r2, #0x0]
    cmp r1, r0
    beq @L0215c800
    mov r0, r5
    bl _ZN11AlchemyMenu14CountItemPagesEv
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
@L0215c800:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsConfirmedEv
    cmp r0, #0x0
    beq @L0215c888
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r1, #0x0
    mov r0, r5
    str r1, [r5, #0x44]
    bl _ZN11AlchemyMenu16HasCategoryItemsEv
    cmp r0, #0x0
    beq @L0215cc60
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x1
    bl func_02080c68
    add r0, r5, #0x300
    ldrsh r1, [r0, #0x6e]
    mov r0, r4
    mov r2, #0x1
    bl func_02081ea4
    mov r0, r4
    mov r1, #0x11
    mov r2, #0x0
    bl func_02080c68
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215cc60
@L0215c888:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    beq @L0215c8d4
    add r0, r5, #0x9c
    bl func_0208203c
    mov r1, #0x0
    str r1, [r5, #0x44]
    mov r0, #0x6
    strb r0, [r5, #0x38f]
    mov r0, r5
    strb r1, [r5, #0x390]
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    mov r0, r5
    bl _ZN11AlchemyMenu9DrawItemsEv
@L0215c8d4:
    mov r0, r5
    bl _ZN11AlchemyMenu10CheckCloseEv
    b @L0215cc60
@L0215c8e0:
    cmp r1, #0x2
    bne @L0215c90c
    bl _ZN11AlchemyMenu9OpenItemsEv
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215cc60
@L0215c90c:
    cmp r1, #0x3
    bne @L0215ca38
    bl _ZN11AlchemyMenu11UpdateItemsEv
    cmp r0, #0x0
    bne @L0215cc60
    mov r0, r5
    bl _ZN11AlchemyMenu11IsConfirmedEv
    cmp r0, #0x0
    beq @L0215c9fc
    ldr r1, [r5, #0x44]
    add r0, r5, #0x300
    ldrsh r2, [r0, #0x5e]
    ldrsh r0, [r1, #0x0]
    cmp r2, r0
    bne @L0215c9fc
    mov r4, #0x0
    add r1, sp, #0x1
    add r2, sp, #0x2
    add r3, sp, #0x0
    mov r0, r5
    strb r4, [sp, #0x0]
    strb r4, [sp, #0x1]
    strh r4, [sp, #0x2]
    bl _ZN11AlchemyMenu15GetSelectedItemEPhPsS0_
    ldrb r0, [sp, #0x0]
    cmp r0, #0x0
    beq @L0215ca2c
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, r4
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, r4
    str r0, [r5, #0x44]
    ldr r0, [r5, #0x14]
    mov r1, #0x11
    mov r2, #0x1
    bl func_02081ea4
    ldrb r1, [sp, #0x1]
    add r0, r5, #0x300
    mov r3, #0x1
    strb r1, [r5, #0x38a]
    ldrsh r4, [sp, #0x2]
    mov r2, #0x9
    mov r1, #0x0
    strh r4, [r0, #0x70]
    strb r3, [r5, #0x38b]
    ldrb r3, [r5, #0x390]
    add r3, r3, #0x1
    strb r3, [r5, #0x390]
    ldrh r3, [r0, #0x94]
    bic r3, r3, #0x10
    strh r3, [r0, #0x94]
    ldrh r3, [r0, #0x94]
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    b @L0215cc60
@L0215c9fc:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    beq @L0215ca2c
    add r0, r5, #0x9c
    bl func_0208203c
    mov r2, #0x0
    str r2, [r5, #0x44]
    sub r1, r2, #0x1
    add r0, r5, #0x300
    strh r1, [r0, #0x64]
    strb r2, [r5, #0x390]
@L0215ca2c:
    mov r0, r5
    bl _ZN11AlchemyMenu10CheckCloseEv
    b @L0215cc60
@L0215ca38:
    cmp r1, #0x4
    bne @L0215ca5c
    bl _ZN11AlchemyMenu9OpenCountEv
    mov r0, #0x0
    strb r0, [r5, #0x393]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215cc60
@L0215ca5c:
    cmp r1, #0x5
    bne @L0215cb98
    mov r1, #0x0
    strb r1, [r5, #0x42c]
    bl _ZN11AlchemyMenu11UpdateCountEv
    mov r6, r0
    cmp r6, #0x1
    beq @L0215cc60
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    bne @L0215ca98
    cmp r6, #0x2
    bne @L0215cb2c
@L0215ca98:
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, #0x0
    str r0, [r5, #0x44]
    add r2, r5, #0x300
    ldrh r3, [r2, #0x94]
    mov r0, r4
    mov r1, #0x6
    bic r3, r3, #0x8
    strh r3, [r2, #0x94]
    bl func_0207fdcc
    add r0, r5, #0x300
    ldrsh r2, [r0, #0x70]
    mov r0, r5
    ldrb r1, [r5, #0x38a]
    ldrb r3, [r5, #0x38b]
    bl _ZN11AlchemyMenu14TakeIngredientEssh
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    ldrb r1, [r5, #0x390]
    add r0, r5, #0x300
    mov r2, #0xa
    add r1, r1, #0x1
    strb r1, [r5, #0x390]
    ldrh r3, [r0, #0x94]
    mov r1, #0x0
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    b @L0215cc60
@L0215cb2c:
    mov r0, r5
    bl _ZN11AlchemyMenu11IsCancelledEv
    cmp r0, #0x0
    bne @L0215cb44
    cmp r6, #0x3
    bne @L0215cc60
@L0215cb44:
    add r0, r5, #0x9c
    bl func_0208203c
    mov r0, #0x0
    str r0, [r5, #0x44]
    add r2, r5, #0x300
    ldrh r3, [r2, #0x94]
    mov r0, r4
    mov r1, #0x6
    bic r3, r3, #0x8
    strh r3, [r2, #0x94]
    bl func_0207fdcc
    mov r2, #0x0
    strb r2, [r5, #0x390]
    add r0, r5, #0x300
    mov r1, #0x24
    strh r1, [r0, #0x7e]
    strb r2, [r5, #0x392]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x120
    strh r1, [r0, #0x94]
    b @L0215cc60
@L0215cb98:
    cmp r1, #0x6
    bne @L0215cbc4
    ldr r0, [r5, #0x10]
    mov r1, #0x1
    bl _ZN10AlchemyPot9ShowNamesEi
    mov r0, r5
    bl _ZN11AlchemyMenu10OpenChoiceEv
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215cc60
@L0215cbc4:
    cmp r1, #0x7
    bne @L0215cc60
    bl _ZN11AlchemyMenu12UpdateChoiceEv
    mvn r1, #0x0
    cmp r0, r1
    beq @L0215cbfc
    cmp r0, #0x1
    bne @L0215cc60
    mov r0, #0x8
    strb r0, [r5, #0x38f]
    mov r0, #0x0
    str r0, [r5, #0x3b4]
    strb r0, [r5, #0x390]
    b @L0215cc60
@L0215cbfc:
    add r4, r5, #0x300
    b @L0215cc0c
@L0215cc04:
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
@L0215cc0c:
    ldrsh r0, [r4, #0x78]
    cmp r0, #0x0
    bgt @L0215cc04
    ldr r0, [r5, #0x10]
    add r1, r5, #0x378
    add r2, r5, #0x38c
    bl _ZN10AlchemyPot14SetIngredientsEPsPh
    mov r0, #0x5
    strb r0, [r5, #0x38f]
    mov r3, #0x0
    strb r3, [r5, #0x390]
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    mov r1, #0x24
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strh r1, [r0, #0x7e]
    strb r3, [r5, #0x392]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x100
    strh r1, [r0, #0x94]
@L0215cc60:
    add sp, sp, #0x4
    ldmia sp!, {r3, r4, r5, r6, pc}
}
#endif

// NONMATCHING: the C matches 97.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::State_Make()
{
    AlchemyPot* pot = pot_;
    BackgroundLoader::GetInstance();
    if (step_ == 0)
    {
        showResult_ = 0;
        times_ = 0;
        Recipe* recipe = FindRecipe(chosenItems_, chosenCounts_, &times_);
        recipe_ = recipe;
        if (recipe != 0)
        {
            successRate_ = ingredients_.GetSuccessRate(recipe->id_);
            step_++;
            return;
        }
        ReturnIngredient();
        ReturnIngredient();
        ReturnIngredient();
        step_ = 0x78;
        flags_ |= ALCHEMY_MENU_MESSAGE;
        message_ = 0xb;
        messageStep_ = 0;
    }
    else if (step_ == 1)
    {
        LoadResult(0);
        step_++;
    }
    else if (step_ == 2)
    {
        if (resultTask_ == -1)
        {
            if (UpdateResult(0))
            {
                LoadResultSprite(results_);
                return;
            }
        }
        else if (UpdateResultSprite())
        {
            int result = func_020dd4c4(func_020100a8(GameState::GetInstance()), results_);
            step_ = 5;
            if (result & 0x10)
            {
                flags_ |= ALCHEMY_MENU_MESSAGE;
                message_ = female_ + 4;
                messageStep_ = 0;
                step_++;
            }
        }
    }
    else if (step_ == 3)
    {
        OpenChoice();
        step_++;
    }
    else if (step_ == 4)
    {
        switch (UpdateChoice())
        {
        case 1:
            step_++;
            return;
        case -1:
            ReturnIngredient();
            ReturnIngredient();
            ReturnIngredient();
            step_ = 0x78;
            return;
        }
    }
    else if (step_ == 5)
    {
        if (!pot->IsLoadingIngredients())
        {
            int great = 0;
            flags_ &= ~ALCHEMY_MENU_GREAT;
            Recipe* recipe = recipe_;
            if (recipe != 0 && recipe->greatRecipe_ > 0)
                great = 1;
            if (great)
            {
                successRate_ = ingredients_.GetSuccessRate(recipe_->greatRecipe_);
                message_ = 0xd;
                messageStep_ = 0;
                flags_ |= ALCHEMY_MENU_MESSAGE;
                step_++;
                if (NextRandomMax(GetBTRandom(), 10000) / 100U < (unsigned int)successRate_)
                    flags_ |= ALCHEMY_MENU_GREAT;
                LoadResult((flags_ & ALCHEMY_MENU_GREAT) ? 1 : 0);
                return;
            }
            func_02080c04(menu_, 0x10);
            func_02080c04(menu_, 0x11);
            func_02080c04(menu_, 1);
            func_02080c04(menu_, 0);
            pot_->flags_ |= ALCHEMY_POT_MAKING;
            resetBlend_ = 1;
            fadeTimer_ = 0;
            nextStep_ = 0x64;
            step_ = 0x96;
        }
    }
    else if (step_ == 6)
    {
        if (IsMessageAdvanced() && resultTask_ == -1)
        {
            if (UpdateResult((flags_ & ALCHEMY_MENU_GREAT) ? 1 : 0))
            {
                LoadResultSprite(results_);
                return;
            }
        }
        else if (resultTask_ != -1 && UpdateResultSprite())
        {
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = female_ + 0xe;
            messageStep_ = 0;
            step_++;
            return;
        }
    }
    else if (step_ == 7)
    {
        if (IsMessageAdvanced())
        {
            short message = 0x10;
            if (successRate_ >= 3 && successRate_ < 10)
                message = 0x11;
            else if (successRate_ >= 10 && successRate_ <= 99)
                message = 0x12;
            else if (successRate_ == 100)
                message = female_ + 0x16;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = message;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 8)
    {
        if (!pot->IsLoadingIngredients() && IsMessageAdvanced())
        {
            short message = 0x13;
            step_++;
            if (successRate_ == 100)
            {
                step_ = 0xb;
                message = 0x18;
            }
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = message;
            messageStep_ = 0;
        }
    }
    else if (step_ == 9)
    {
        if (IsMessageAdvanced())
        {
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0x14;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 10)
    {
        if (IsMessageAdvanced())
        {
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0x15;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 11)
    {
        OpenChoice();
        step_++;
    }
    else if (step_ == 12)
    {
        switch (UpdateChoice())
        {
        case 1:
        {
            if (flags_ & ALCHEMY_MENU_GREAT)
            {
                Recipe* recipe = recipe_;
                ingredients_.AddResult(recipe->greatRecipe_, recipe->id_, &table_);
            }
            else
            {
                ingredients_.AddResult(recipe_->id_, -1, &table_);
            }
            GiveResult(results_, recipe_, times_);
            LoadInventory();
            itemCursor_ = -1;
            step_++;
            return;
        }
        case -1:
            ReturnIngredient();
            ReturnIngredient();
            ReturnIngredient();
            flags_ = (flags_ | ALCHEMY_MENU_MESSAGE) & ~ALCHEMY_MENU_GREAT;
            func_02080c20(menu_, 0);
            message_ = 0x19;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            step_ = 0x5a;
            return;
        }
    }
    else if (step_ == 0x5a)
    {
        if (IsMessageAdvanced())
        {
            func_02080c20(menu_, 0);
            message_ = 0x24;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE | ALCHEMY_MENU_100;
            state_ = AlchemyMenuState_Ingredient1;
            step_ = 0;
        }
    }
    else if (step_ == 13)
    {
        message_ = 0x36;
        messageStep_ = 0;
        func_02080c04(menu_, 0);
        step_++;
    }
    else if (step_ == 14)
    {
        flags_ |= ALCHEMY_MENU_SAVING;
        if (BackgroundLoader::GetInstance()->GetNumQueuedTasks() <= 0)
        {
            func_020466e4(func_020d6c00(), 0x80);
            func_020a9ea4(save_);
            step_++;
        }
    }
    else if (step_ == 15)
    {
        BackgroundLoader::AddLockGlobal();
        BackgroundLoader::FreeAllocationsGlobal();
        int retries = 8;
        func_0202ae18();
        if (func_0202c540())
            retries = 0x14;
        if (func_020aad1c(save_, data_0211e33c, retries, 0) == 1)
        {
            func_020466f4(func_020d6c00(), 0x80);
            step_++;
            flags_ &= ~ALCHEMY_MENU_SAVING;
        }
        BackgroundLoader::RemoveLockGlobal();
    }
    else if (step_ == 16)
    {
        message_ = 0x37;
        messageStep_ = 0;
        step_++;
    }
    else if (step_ == 17)
    {
        if (IsMessageAdvanced())
        {
            message_ = 0x1a;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            func_02080c20(menu_, 0);
            step_++;
        }
    }
    else if (step_ == 18)
    {
        arrowTimer_ = 0;
        if (IsMessageAdvanced())
        {
            func_02080c04(menu_, 0x10);
            func_02080c04(menu_, 0x11);
            func_02080c04(menu_, 1);
            func_02080c04(menu_, 0);
            pot_->flags_ |= ALCHEMY_POT_MAKING;
            resetBlend_ = 1;
            fadeTimer_ = 0;
            nextStep_ = 0x13;
            step_ = 0x96;
        }
    }
    else if (step_ == 19)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_WORK;
        step_++;
    }
    else if (step_ == 20)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_OUT;
        step_++;
    }
    else if (step_ == 21)
    {
        showResult_ = 1;
        const char** name = func_020e5294(itemNames_, results_[0].item_);
        if (name != 0)
        {
            memset(texts_[0], 0, 0x80);
            func_020e4864(*name, texts_[0], 1, 0, 0, 0);
            func_02080f8c(menu_, 0x7f, texts_[0]);
        }
        func_020805f4(menu_, 0x7f);
        func_020813ec(menu_, 0x12);
        int great = 1;
        pot->flags_ |= ALCHEMY_POT_ANIMATION_END;
        saved_ = 1;
        int sound = 0x3e;
        if (!(flags_ & ALCHEMY_MENU_GREAT))
            great = 0;
        if (great)
        {
            sound = 0x3f;
            pot_->StartEffect();
        }
        func_0209c830(data_02109bf4, sound);
        message_ = 0xc;
        messageStep_ = 0;
        step_++;
    }
    else if (step_ == 22)
    {
        if (IsMessageAdvanced())
        {
            message_ = 0x38;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 23)
    {
        if (IsMessageAdvanced())
        {
            func_0207fdcc(menu_, 0x12);
            int great = 0;
            showResult_ = 0;
            short message = 0x1f;
            pot->flags_ &= ~ALCHEMY_POT_ANIMATION_DONE;
            if (flags_ & ALCHEMY_MENU_GREAT)
                great = 1;
            if (great)
            {
                pot_->StopEffect();
                message = female_ + 0x1b;
            }
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = message;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 24)
    {
        if (IsMessageAdvanced())
        {
            short message = 0x20;
            int great;
            if (flags_ & ALCHEMY_MENU_GREAT)
                great = 1;
            else
                great = 0;
            if (great)
                message = female_ + 0x1d;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = message;
            messageStep_ = 0;
            step_ = 0x78;
            flags_ &= ~ALCHEMY_MENU_GREAT;
        }
    }
    else if (step_ == 0x64)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_WORK;
        step_++;
    }
    else if (step_ == 0x65)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_OUT;
        step_++;
    }
    else if (step_ == 0x66)
    {
        if (recipe_ != 0)
        {
            showResult_ = 1;
            const char** name = func_020e5294(itemNames_, results_[0].item_);
            if (name != 0)
            {
                memset(texts_[0], 0, 0x80);
                func_020e4864(*name, texts_[0], 1, 0, 0, 0);
                func_02080f8c(menu_, 0x7f, texts_[0]);
            }
            func_020805f4(menu_, 0x7f);
            func_020813ec(menu_, 0x12);
            ingredients_.AddResult(recipe_->id_, -1, &table_);
            GiveResult(results_, recipe_, times_);
            LoadInventory();
            itemCursor_ = -1;
            saved_ = 1;
            func_0209c830(data_02109bf4, 0x3e);
            pot->flags_ |= ALCHEMY_POT_ANIMATION_END;
            func_02080c04(menu_, 0);
            message_ = 0xc;
            messageStep_ = 0;
            step_++;
            return;
        }
        ReturnIngredient();
        ReturnIngredient();
        ReturnIngredient();
        flags_ |= ALCHEMY_MENU_MESSAGE;
        message_ = 0xb;
        messageStep_ = 0;
        step_ = 0x78;
    }
    else if (step_ == 0x67)
    {
        if (IsMessageAdvanced())
        {
            message_ = 0x38;
            messageStep_ = 0;
            step_ = 0x78;
        }
    }
    else if (step_ == 0x78)
    {
        if (saved_ != 0)
        {
            arrowTimer_ = 0;
            return;
        }
        if (IsMessageAdvanced())
        {
            func_0207fdcc(menu_, 0x12);
            pot->flags_ &= ~ALCHEMY_POT_ANIMATION_DONE;
            func_02080c20(menu_, 0);
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0x24;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_100;
            state_ = AlchemyMenuState_Ingredient1;
            step_ = 0;
        }
    }
    else if (step_ == 0x96)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_OPEN;
        fadeTimer_++;
        if (fadeTimer_ >= 10)
        {
            fadeTimer_ = 0;
            pot->flags_ &= ~ALCHEMY_POT_ANIMATION_OPEN;
            pot->flags_ |= ALCHEMY_POT_ANIMATION_IN;
            step_ = nextStep_;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10AlchemyPot10StopEffectEv(); // AlchemyPot::StopEffect
    void _ZN10AlchemyPot11StartEffectEv(); // AlchemyPot::StartEffect
    void _ZN10AlchemyPot20IsLoadingIngredientsEv(); // AlchemyPot::IsLoadingIngredients
    void _ZN11AlchemyMenu10FindRecipeEPsPhS1_(); // AlchemyMenu::FindRecipe
    void _ZN11AlchemyMenu10LoadResultEi(); // AlchemyMenu::LoadResult
    void _ZN11AlchemyMenu10OpenChoiceEv(); // AlchemyMenu::OpenChoice
    void _ZN11AlchemyMenu12UpdateChoiceEv(); // AlchemyMenu::UpdateChoice
    void _ZN11AlchemyMenu12UpdateResultEi(); // AlchemyMenu::UpdateResult
    void _ZN11AlchemyMenu13LoadInventoryEv(); // AlchemyMenu::LoadInventory
    void _ZN11AlchemyMenu16LoadResultSpriteEP13PotIngredient(); // AlchemyMenu::LoadResultSprite
    void _ZN11AlchemyMenu16ReturnIngredientEv(); // AlchemyMenu::ReturnIngredient
    void _ZN11AlchemyMenu17IsMessageAdvancedEv(); // AlchemyMenu::IsMessageAdvanced
    void _ZN11AlchemyMenu18UpdateResultSpriteEv(); // AlchemyMenu::UpdateResultSprite
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader17GetNumQueuedTasksEv(); // BackgroundLoader::GetNumQueuedTasks
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN18AlchemyIngredients14GetSuccessRateEs(); // AlchemyIngredients::GetSuccessRate
    void _ZN18AlchemyIngredients9AddResultEssP11RecipeTable(); // AlchemyIngredients::AddResult
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _u32_div_f();
}

asm void AlchemyMenu::State_Make()
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x8
    mov r5, r0
    ldr r4, [r5, #0x10]
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r0, [r5, #0x390]
    cmp r0, #0x0
    bne @L0215cd28
    mov r4, #0x0
    add r3, r5, #0x87
    str r4, [r5, #0x3b4]
    mov r0, r5
    add r1, r5, #0x378
    add r2, r5, #0x38c
    add r3, r3, #0x300
    strb r4, [r5, #0x387]
    bl _ZN11AlchemyMenu10FindRecipeEPsPhS1_
    str r0, [r5, #0x34]
    cmp r0, #0x0
    beq @L0215cce4
    ldrsh r1, [r0, #0x0]
    add r0, r5, #0x74
    bl _ZN18AlchemyIngredients14GetSuccessRateEs
    add r1, r5, #0x300
    strh r0, [r1, #0x82]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215cce4:
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, #0x78
    strb r0, [r5, #0x390]
    add r0, r5, #0x300
    ldrh r3, [r0, #0x94]
    mov r2, #0xb
    mov r1, r4
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    b @L0215dadc
@L0215cd28:
    cmp r0, #0x1
    bne @L0215cd4c
    mov r0, r5
    mov r1, #0x0
    bl _ZN11AlchemyMenu10LoadResultEi
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215cd4c:
    cmp r0, #0x2
    bne @L0215cdf0
    ldr r1, [r5, #0x428]
    mvn r0, #0x0
    cmp r1, r0
    mov r0, r5
    bne @L0215cd88
    mov r1, #0x0
    bl _ZN11AlchemyMenu12UpdateResultEi
    cmp r0, #0x0
    beq @L0215dadc
    mov r0, r5
    add r1, r5, #0x17c
    bl _ZN11AlchemyMenu16LoadResultSpriteEP13PotIngredient
    b @L0215dadc
@L0215cd88:
    bl _ZN11AlchemyMenu18UpdateResultSpriteEv
    cmp r0, #0x0
    beq @L0215dadc
    bl _ZN9GameState11GetInstanceEv
    bl func_020100a8
    mov r0, r0, lsl #0x18
    mov r0, r0, asr #0x18
    add r1, r5, #0x17c
    bl func_020dd4c4
    mov r1, #0x5
    strb r1, [r5, #0x390]
    tst r0, #0x10
    beq @L0215dadc
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    mov r1, #0x0
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    ldrb r2, [r5, #0x396]
    add r2, r2, #0x4
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215cdf0:
    cmp r0, #0x3
    bne @L0215ce10
    mov r0, r5
    bl _ZN11AlchemyMenu10OpenChoiceEv
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215ce10:
    cmp r0, #0x4
    bne @L0215ce64
    mov r0, r5
    bl _ZN11AlchemyMenu12UpdateChoiceEv
    mvn r1, #0x0
    cmp r0, r1
    beq @L0215ce40
    cmp r0, #0x1
    ldreqb r0, [r5, #0x390]
    addeq r0, r0, #0x1
    streqb r0, [r5, #0x390]
    b @L0215dadc
@L0215ce40:
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, #0x78
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215ce64:
    cmp r0, #0x5
    bne @L0215cfa4
    mov r0, r4
    bl _ZN10AlchemyPot20IsLoadingIngredientsEv
    cmp r0, #0x0
    bne @L0215dadc
    add r0, r5, #0x300
    ldrh r1, [r0, #0x94]
    mov r2, #0x0
    bic r1, r1, #0x40
    strh r1, [r0, #0x94]
    ldr r0, [r5, #0x34]
    cmp r0, #0x0
    beq @L0215cea8
    ldrsh r0, [r0, #0x14]
    cmp r0, #0x0
    movgt r2, #0x1
@L0215cea8:
    cmp r2, #0x0
    beq @L0215cf3c
    ldr r1, [r5, #0x34]
    add r0, r5, #0x74
    ldrsh r1, [r1, #0x14]
    bl _ZN18AlchemyIngredients14GetSuccessRateEs
    add r1, r5, #0x300
    strh r0, [r1, #0x82]
    mov r0, #0xd
    strh r0, [r1, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrh r0, [r1, #0x94]
    orr r0, r0, #0x20
    strh r0, [r1, #0x94]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    bl GetBTRandom
    ldr r1, =0x2710
    bl NextRandomMax
    mov r1, #0x64
    bl _u32_div_f
    add r1, r5, #0x300
    ldrsh r2, [r1, #0x82]
    cmp r0, r2
    ldrloh r0, [r1, #0x94]
    orrlo r0, r0, #0x40
    strloh r0, [r1, #0x94]
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x40
    movne r1, #0x1
    moveq r1, #0x0
    mov r0, r5
    bl _ZN11AlchemyMenu10LoadResultEi
    b @L0215dadc
@L0215cf3c:
    ldr r0, [r5, #0x14]
    mov r1, #0x10
    bl func_02080c04
    ldr r0, [r5, #0x14]
    mov r1, #0x11
    bl func_02080c04
    ldr r0, [r5, #0x14]
    mov r1, #0x1
    bl func_02080c04
    ldr r0, [r5, #0x14]
    mov r1, #0x0
    bl func_02080c04
    ldr r0, [r5, #0x10]
    mov r3, #0x1
    add r0, r0, #0xa00
    ldrh r4, [r0, #0xe2]
    mov r2, #0x0
    mov r1, #0x64
    orr r4, r4, #0x10
    strh r4, [r0, #0xe2]
    strb r3, [r5, #0x432]
    strb r2, [r5, #0x42d]
    strb r1, [r5, #0x42e]
    mov r0, #0x96
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215cfa4:
    cmp r0, #0x6
    bne @L0215d054
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215d000
    ldr r1, [r5, #0x428]
    mvn r0, #0x0
    cmp r1, r0
    bne @L0215d000
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x40
    movne r1, #0x1
    moveq r1, #0x0
    mov r0, r5
    bl _ZN11AlchemyMenu12UpdateResultEi
    cmp r0, #0x0
    beq @L0215dadc
    mov r0, r5
    add r1, r5, #0x17c
    bl _ZN11AlchemyMenu16LoadResultSpriteEP13PotIngredient
    b @L0215dadc
@L0215d000:
    ldr r1, [r5, #0x428]
    mvn r0, #0x0
    cmp r1, r0
    beq @L0215dadc
    mov r0, r5
    bl _ZN11AlchemyMenu18UpdateResultSpriteEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    mov r1, #0x0
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    ldrb r2, [r5, #0x396]
    add r2, r2, #0xe
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d054:
    cmp r0, #0x7
    bne @L0215d0f0
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    ldrsh r0, [r0, #0x82]
    mov r3, #0x10
    cmp r0, #0x3
    blt @L0215d08c
    cmp r0, #0xa
    movlt r3, #0x11
    blt @L0215d0c4
@L0215d08c:
    add r0, r5, #0x300
    ldrsh r0, [r0, #0x82]
    cmp r0, #0xa
    blt @L0215d0a8
    cmp r0, #0x63
    movle r3, #0x12
    ble @L0215d0c4
@L0215d0a8:
    add r0, r5, #0x300
    ldrsh r0, [r0, #0x82]
    cmp r0, #0x64
    ldreqb r0, [r5, #0x396]
    addeq r0, r0, #0x16
    moveq r0, r0, lsl #0x10
    moveq r3, r0, asr #0x10
@L0215d0c4:
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    mov r1, #0x0
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strh r3, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d0f0:
    cmp r0, #0x8
    bne @L0215d160
    mov r0, r4
    bl _ZN10AlchemyPot20IsLoadingIngredientsEv
    cmp r0, #0x0
    bne @L0215dadc
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    ldrb r1, [r5, #0x390]
    add r0, r5, #0x300
    mov r3, #0x13
    add r1, r1, #0x1
    strb r1, [r5, #0x390]
    ldrsh r0, [r0, #0x82]
    mov r1, #0x0
    cmp r0, #0x64
    moveq r0, #0xb
    streqb r0, [r5, #0x390]
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    moveq r3, #0x18
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strh r3, [r0, #0x7e]
    strb r1, [r5, #0x392]
    b @L0215dadc
@L0215d160:
    cmp r0, #0x9
    bne @L0215d1a8
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    ldrh r3, [r0, #0x94]
    mov r2, #0x14
    mov r1, #0x0
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d1a8:
    cmp r0, #0xa
    bne @L0215d1f0
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    ldrh r3, [r0, #0x94]
    mov r2, #0x15
    mov r1, #0x0
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d1f0:
    cmp r0, #0xb
    bne @L0215d210
    mov r0, r5
    bl _ZN11AlchemyMenu10OpenChoiceEv
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d210:
    cmp r0, #0xc
    bne @L0215d31c
    mov r0, r5
    bl _ZN11AlchemyMenu12UpdateChoiceEv
    mvn r1, #0x0
    cmp r0, r1
    beq @L0215d2b8
    cmp r0, #0x1
    bne @L0215dadc
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x40
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    beq @L0215d26c
    ldr r2, [r5, #0x34]
    add r0, r5, #0x74
    ldrsh r1, [r2, #0x14]
    ldrsh r2, [r2, #0x0]
    add r3, r5, #0x14c
    bl _ZN18AlchemyIngredients9AddResultEssP11RecipeTable
    b @L0215d284
@L0215d26c:
    ldr r1, [r5, #0x34]
    add r0, r5, #0x74
    ldrsh r1, [r1, #0x0]
    add r3, r5, #0x14c
    mvn r2, #0x0
    bl _ZN18AlchemyIngredients9AddResultEssP11RecipeTable
@L0215d284:
    ldrb r2, [r5, #0x387]
    ldr r1, [r5, #0x34]
    add r0, r5, #0x17c
    bl GiveResult
    mov r0, r5
    bl _ZN11AlchemyMenu13LoadInventoryEv
    add r0, r5, #0x300
    mvn r1, #0x0
    strh r1, [r0, #0x64]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d2b8:
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    mov r1, #0x0
    orr r2, r2, #0x20
    bic r2, r2, #0x40
    strh r2, [r0, #0x94]
    ldr r0, [r5, #0x14]
    bl func_02080c20
    add r0, r5, #0x300
    mov r1, #0x19
    strh r1, [r0, #0x7e]
    mov r1, #0x0
    strb r1, [r5, #0x392]
    ldrh r2, [r0, #0x94]
    mov r1, #0x5a
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strb r1, [r5, #0x390]
    b @L0215dadc
@L0215d31c:
    cmp r0, #0x5a
    bne @L0215d370
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    ldr r0, [r5, #0x14]
    mov r1, #0x0
    bl func_02080c20
    add r0, r5, #0x300
    mov r1, #0x24
    strh r1, [r0, #0x7e]
    mov r3, #0x0
    strb r3, [r5, #0x392]
    ldrh r2, [r0, #0x94]
    mov r1, #0x5
    orr r2, r2, #0x120
    strh r2, [r0, #0x94]
    strb r1, [r5, #0x38f]
    strb r3, [r5, #0x390]
    b @L0215dadc
@L0215d370:
    cmp r0, #0xd
    bne @L0215d3a4
    add r0, r5, #0x300
    mov r1, #0x36
    strh r1, [r0, #0x7e]
    mov r1, #0x0
    strb r1, [r5, #0x392]
    ldr r0, [r5, #0x14]
    bl func_02080c04
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d3a4:
    cmp r0, #0xe
    bne @L0215d3f0
    add r0, r5, #0x300
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x200
    strh r1, [r0, #0x94]
    bl _ZN16BackgroundLoader11GetInstanceEv
    bl _ZN16BackgroundLoader17GetNumQueuedTasksEv
    cmp r0, #0x0
    bgt @L0215dadc
    bl func_020d6c00
    mov r1, #0x80
    bl func_020466e4
    add r0, r5, #0x3c
    bl func_020a9ea4
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d3f0:
    cmp r0, #0xf
    bne @L0215d460
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    mov r4, #0x8
    bl func_0202ae18
    bl func_0202c540
    cmp r0, #0x0
    movne r4, #0x14
    ldr r1, =data_0211e33c
    mov r2, r4
    add r0, r5, #0x3c
    mov r3, #0x0
    bl func_020aad1c
    cmp r0, #0x1
    bne @L0215d458
    bl func_020d6c00
    mov r1, #0x80
    bl func_020466f4
    ldrb r1, [r5, #0x390]
    add r0, r5, #0x300
    add r1, r1, #0x1
    strb r1, [r5, #0x390]
    ldrh r1, [r0, #0x94]
    bic r1, r1, #0x200
    strh r1, [r0, #0x94]
@L0215d458:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    b @L0215dadc
@L0215d460:
    cmp r0, #0x10
    bne @L0215d48c
    add r0, r5, #0x300
    mov r1, #0x37
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d48c:
    cmp r0, #0x11
    bne @L0215d4dc
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    mov r1, #0x1a
    strh r1, [r0, #0x7e]
    mov r1, #0x0
    strb r1, [r5, #0x392]
    ldrh r2, [r0, #0x94]
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    ldr r0, [r5, #0x14]
    bl func_02080c20
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d4dc:
    cmp r0, #0x12
    bne @L0215d564
    mov r1, #0x0
    mov r0, r5
    strb r1, [r5, #0x42c]
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    ldr r0, [r5, #0x14]
    mov r1, #0x10
    bl func_02080c04
    ldr r0, [r5, #0x14]
    mov r1, #0x11
    bl func_02080c04
    ldr r0, [r5, #0x14]
    mov r1, #0x1
    bl func_02080c04
    ldr r0, [r5, #0x14]
    mov r1, #0x0
    bl func_02080c04
    ldr r0, [r5, #0x10]
    mov r3, #0x1
    add r0, r0, #0xa00
    ldrh r4, [r0, #0xe2]
    mov r2, #0x0
    mov r1, #0x13
    orr r4, r4, #0x10
    strh r4, [r0, #0xe2]
    strb r3, [r5, #0x432]
    strb r2, [r5, #0x42d]
    strb r1, [r5, #0x42e]
    mov r0, #0x96
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d564:
    cmp r0, #0x13
    bne @L0215d58c
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x100
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d58c:
    cmp r0, #0x14
    bne @L0215d5b4
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x200
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d5b4:
    cmp r0, #0x15
    bne @L0215d6ac
    mov r0, #0x1
    str r0, [r5, #0x3b4]
    add r0, r5, #0x100
    ldrsh r1, [r0, #0xec]
    add r0, r5, #0x170
    bl func_020e5294
    movs r6, r0
    beq @L0215d624
    ldr r0, [r5, #0x4]
    mov r1, #0x0
    ldr r0, [r0, #0x0]
    mov r2, #0x80
    bl memset
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r1, [r5, #0x4]
    ldr r0, [r6, #0x0]
    ldr r1, [r1, #0x0]
    mov r2, #0x1
    bl func_020e4864
    ldr r1, [r5, #0x4]
    ldr r0, [r5, #0x14]
    ldr r2, [r1, #0x0]
    mov r1, #0x7f
    bl func_02080f8c
@L0215d624:
    ldr r0, [r5, #0x14]
    mov r1, #0x7f
    bl func_020805f4
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_020813ec
    add r0, r4, #0xa00
    ldrh r2, [r0, #0xe2]
    mov r3, #0x1
    add r1, r5, #0x300
    orr r2, r2, #0x400
    strh r2, [r0, #0xe2]
    strb r3, [r5, #0x42f]
    ldrh r0, [r1, #0x94]
    mov r4, #0x3e
    tst r0, #0x40
    moveq r3, #0x0
    cmp r3, #0x0
    beq @L0215d67c
    ldr r0, [r5, #0x10]
    mov r4, #0x3f
    bl _ZN10AlchemyPot11StartEffectEv
@L0215d67c:
    ldr r0, =data_02109bf4
    mov r1, r4
    bl func_0209c830
    add r0, r5, #0x300
    mov r1, #0xc
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d6ac:
    cmp r0, #0x16
    bne @L0215d6e8
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    mov r1, #0x38
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d6e8:
    cmp r0, #0x17
    bne @L0215d784
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_0207fdcc
    mov r6, #0x0
    str r6, [r5, #0x3b4]
    add r0, r4, #0xa00
    ldrh r2, [r0, #0xe2]
    add r1, r5, #0x300
    mov r3, #0x1f
    bic r2, r2, #0x800
    strh r2, [r0, #0xe2]
    ldrh r0, [r1, #0x94]
    tst r0, #0x40
    movne r6, #0x1
    cmp r6, #0x0
    beq @L0215d758
    ldr r0, [r5, #0x10]
    bl _ZN10AlchemyPot10StopEffectEv
    ldrb r0, [r5, #0x396]
    add r0, r0, #0x1b
    mov r0, r0, lsl #0x10
    mov r3, r0, asr #0x10
@L0215d758:
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    mov r1, #0x0
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strh r3, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d784:
    cmp r0, #0x18
    bne @L0215d7fc
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    mov r4, #0x20
    mov r2, #0x0
    tst r0, #0x40
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    ldrneb r0, [r5, #0x396]
    mov r1, #0x78
    addne r0, r0, #0x1d
    movne r0, r0, lsl #0x10
    movne r4, r0, asr #0x10
    add r0, r5, #0x300
    ldrh r3, [r0, #0x94]
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r4, [r0, #0x7e]
    strb r2, [r5, #0x392]
    strb r1, [r5, #0x390]
    ldrh r1, [r0, #0x94]
    bic r1, r1, #0x40
    strh r1, [r0, #0x94]
    b @L0215dadc
@L0215d7fc:
    cmp r0, #0x64
    bne @L0215d824
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x100
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d824:
    cmp r0, #0x65
    bne @L0215d84c
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x200
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d84c:
    cmp r0, #0x66
    bne @L0215d9b4
    ldr r0, [r5, #0x34]
    cmp r0, #0x0
    beq @L0215d970
    mov r0, #0x1
    str r0, [r5, #0x3b4]
    add r0, r5, #0x100
    ldrsh r1, [r0, #0xec]
    add r0, r5, #0x170
    bl func_020e5294
    movs r6, r0
    beq @L0215d8c8
    ldr r0, [r5, #0x4]
    mov r1, #0x0
    ldr r0, [r0, #0x0]
    mov r2, #0x80
    bl memset
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r1, [r5, #0x4]
    ldr r0, [r6, #0x0]
    ldr r1, [r1, #0x0]
    mov r2, #0x1
    bl func_020e4864
    ldr r1, [r5, #0x4]
    ldr r0, [r5, #0x14]
    ldr r2, [r1, #0x0]
    mov r1, #0x7f
    bl func_02080f8c
@L0215d8c8:
    ldr r0, [r5, #0x14]
    mov r1, #0x7f
    bl func_020805f4
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_020813ec
    ldr r1, [r5, #0x34]
    add r0, r5, #0x74
    ldrsh r1, [r1, #0x0]
    add r3, r5, #0x14c
    mvn r2, #0x0
    bl _ZN18AlchemyIngredients9AddResultEssP11RecipeTable
    ldrb r2, [r5, #0x387]
    add r0, r5, #0x17c
    ldr r1, [r5, #0x34]
    bl GiveResult
    mov r0, r5
    bl _ZN11AlchemyMenu13LoadInventoryEv
    mvn r1, #0x0
    add r0, r5, #0x300
    strh r1, [r0, #0x64]
    mov r0, #0x1
    strb r0, [r5, #0x42f]
    ldr r0, =data_02109bf4
    mov r1, #0x3e
    bl func_0209c830
    add r0, r4, #0xa00
    ldrh r2, [r0, #0xe2]
    mov r1, #0x0
    orr r2, r2, #0x400
    strh r2, [r0, #0xe2]
    ldr r0, [r5, #0x14]
    bl func_02080c04
    mov r1, #0xc
    add r0, r5, #0x300
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d970:
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ReturnIngredientEv
    add r0, r5, #0x300
    ldrh r3, [r0, #0x94]
    mov r2, #0xb
    mov r1, #0x0
    orr r3, r3, #0x20
    strh r3, [r0, #0x94]
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    mov r0, #0x78
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d9b4:
    cmp r0, #0x67
    bne @L0215d9ec
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    add r0, r5, #0x300
    mov r1, #0x38
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    mov r0, #0x78
    strb r0, [r5, #0x390]
    b @L0215dadc
@L0215d9ec:
    cmp r0, #0x78
    bne @L0215da7c
    ldrb r0, [r5, #0x42f]
    cmp r0, #0x0
    movne r0, #0x0
    strneb r0, [r5, #0x42c]
    bne @L0215dadc
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215dadc
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_0207fdcc
    add r0, r4, #0xa00
    ldrh r2, [r0, #0xe2]
    mov r1, #0x0
    bic r2, r2, #0x800
    strh r2, [r0, #0xe2]
    ldr r0, [r5, #0x14]
    bl func_02080c20
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    mov r1, #0x24
    mov r3, #0x0
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strh r1, [r0, #0x7e]
    strb r3, [r5, #0x392]
    ldrh r2, [r0, #0x94]
    mov r1, #0x5
    orr r2, r2, #0x100
    strh r2, [r0, #0x94]
    strb r1, [r5, #0x38f]
    strb r3, [r5, #0x390]
    b @L0215dadc
@L0215da7c:
    cmp r0, #0x96
    bne @L0215dadc
    add r1, r4, #0xa00
    ldrh r2, [r1, #0xe2]
    add r0, r4, #0xe2
    add r3, r0, #0xa00
    orr r0, r2, #0x2000
    strh r0, [r1, #0xe2]
    ldrb r0, [r5, #0x42d]
    add r1, r0, #0x1
    and r0, r1, #0xff
    strb r1, [r5, #0x42d]
    cmp r0, #0xa
    blo @L0215dadc
    mov r0, #0x0
    strb r0, [r5, #0x42d]
    ldrh r0, [r3, #0x0]
    bic r0, r0, #0x2000
    strh r0, [r3, #0x0]
    ldrh r0, [r3, #0x0]
    orr r0, r0, #0x80
    strh r0, [r3, #0x0]
    ldrb r0, [r5, #0x42e]
    strb r0, [r5, #0x390]
@L0215dadc:
    add sp, sp, #0x8
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void AlchemyMenu::State_Recipes()
{
    if (step_ == 0)
    {
        background_ = 2;
        DrawBookTitle(1);
        group_ = 8;
        if (bookCursor_ < 0)
            bookCursor_ = 0x24;
        menu_->cursor_ = bookCursor_;
        func_020813ec(menu_, group_);
        func_0208203c(&repeat_);
        cursor_ = 0;
        step_++;
    }
    else if (step_ == 1)
    {
        cursor_ = &bookCursor_;
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            int open = 0;
            cursor_ = 0;
            filterCursor_ = -1;
            recipeCursor_ = -1;
            filterCategory_ = -1;
            filterKind_ = -1;
            switch (bookCursor_)
            {
            case 0x24:
                open = 1;
                break;
            case 0x25:
                filterCategory_ = 0;
                step_++;
                break;
            case 0x26:
                step_++;
                break;
            case 0x27:
                filterCategory_ = 7;
                open = 1;
                break;
            case 0x28:
                filterCategory_ = 8;
                open = 1;
                break;
            }
            if (open)
            {
                state_ = AlchemyMenuState_RecipeList;
                step_ = 0;
                flags_ |= ALCHEMY_MENU_BOOK;
            }
            short count = 0;
            func_02071ffc(&table_, filterCategory_, filterKind_, sort_, 0x10, &count);
            Recipe* recipes = table_.unk_0;
            recipes_ = recipes;
            pageStart_ = recipes;
            CountPages();
            func_0207fdcc(menu_, group_);
            return;
        }
        if (IsCancelled())
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            func_0207fe44(menu_);
            state_ = AlchemyMenuState_Main;
            step_ = 0;
            background_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = 0;
            messageStep_ = 0;
            pot_->CloseWindow();
        }
        CheckClose();
    }
    else if (step_ == 2)
    {
        background_ = 2;
        DrawBookTitle(0);
        short book = bookCursor_;
        if (book == 0x25)
        {
            group_ = 0xc;
            if (filterCursor_ < 0)
                filterCursor_ = 0x48;
        }
        else if (book == 0x26)
        {
            group_ = 0xb;
            if (filterCursor_ < 0)
                filterCursor_ = 0x40;
        }
        menu_->cursor_ = filterCursor_;
        func_020813ec(menu_, group_);
        func_0208203c(&repeat_);
        cursor_ = 0;
        step_++;
    }
    else if (step_ == 3)
    {
        cursor_ = &filterCursor_;
        if (IsConfirmed())
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            recipeCursor_ = -1;
            GetFilter(filterCursor_, &filterCategory_, &filterKind_);
            short count = 0;
            func_02071ffc(&table_, filterCategory_, filterKind_, sort_, 0x10, &count);
            Recipe* recipes = table_.unk_0;
            recipes_ = recipes;
            pageStart_ = recipes;
            CountPages();
            func_0207fdcc(menu_, group_);
            state_ = AlchemyMenuState_RecipeList;
            step_ = 0;
            flags_ |= ALCHEMY_MENU_BOOK;
            return;
        }
        if (IsCancelled())
        {
            func_0208203c(&repeat_);
            cursor_ = 0;
            filterCursor_ = -1;
            func_0207fdcc(menu_, group_);
            step_ = 0;
        }
        CheckClose();
    }
}

void AlchemyMenu::State_RecipeList()
{
    if (step_ == 0)
    {
        background_ = 1;
        func_0207fdcc(menu_, 0);
        func_0207fdcc(menu_, 1);
        DrawBookTitle(0);
        DrawFilter();
        DrawSort();
        group_ = 9;
        if (recipeCursor_ < 0)
            recipeCursor_ = 0x29;
        menu_->cursor_ = recipeCursor_;
        DrawRecipes();
        func_0208203c(&repeat_);
        cursor_ = 0;
        step_++;
    }
    else if (step_ == 1)
    {
        cursor_ = &recipeCursor_;
        int result = menuResult_;
        int pageChanged = 0;
        if (result & 0x10)
        {
            pageChanged = 1;
            page_++;
        }
        else if (result & 0x20)
        {
            pageChanged = 1;
            page_--;
        }
        if (page_ == 0xff)
            page_ = pages_ - 1;
        if (pages_ <= page_)
            page_ = 0;
        Recipe* recipe = GetRecipe(recipeCursor_ - 0x29);
        RecipeRecord* record = 0;
        if (recipe != 0)
        {
            record = ingredients_.FindRecord(recipe->id_);
            ingredients_.GetAmounts(recipe->id_, amounts_);
        }
        pot_->ShowRecipe(recipe, record, amounts_);
        if (pageChanged)
        {
            DrawRecipes();
            return;
        }
        unsigned char button = GetRecipeButton();
        if (button == 1)
        {
            ChangeSort();
            return;
        }
        if (button == 4)
        {
            if (recipe != 0 && record != 0)
            {
                AlchemyPot* pot = pot_;
                int shown = (pot->window_.flags_ & ITEM_INFO_WINDOW_NAMES) ? 1 : 0;
                pot->ShowNames(shown == 0 ? 1 : 0);
                func_0205eaa0(data_02108760, 1, 0);
                return;
            }
            return;
        }
        if (IsConfirmed() || button == 2)
        {
            if (recipe != 0 && record != 0)
            {
                if (!record->made_)
                    return;
                recipe_ = recipe;
                menu_->cursor_ = *cursor_;
                func_0205eaa0(data_02108760, 1, 0);
                func_0208203c(&repeat_);
                cursor_ = 0;
                if (ingredients_.SetRecipe(recipe->id_))
                {
                    func_02081ea4(menu_, 9, 1);
                    message_ = 3;
                    messageStep_ = 0;
                    flags_ |= ALCHEMY_MENU_MESSAGE;
                    count_ = 1;
                    times_ = 1;
                    step_++;
                    return;
                }
                func_02081ea4(menu_, 9, 1);
                message_ = 2;
                messageStep_ = 0;
                flags_ |= ALCHEMY_MENU_MESSAGE;
                step_ = 0x64;
                return;
            }
        }
        else if (IsCancelled() || button == 3)
        {
            if (button == 3)
                func_0205eaa0(data_02108760, 1, 0);
            func_0207fdcc(menu_, group_);
            func_0207fdcc(menu_, 0xe);
            func_0207fdcc(menu_, 0xf);
            state_ = AlchemyMenuState_Recipes;
            step_ = 0;
            func_0208203c(&repeat_);
            cursor_ = 0;
            pot_->CloseWindow();
            background_ = 2;
            if (bookCursor_ == 0x25 || bookCursor_ == 0x26)
                step_ = 2;
            flags_ &= ~ALCHEMY_MENU_BOOK;
        }
        CheckClose();
    }
    else if (step_ == 2)
    {
        OpenChoice();
        step_++;
    }
    else if (step_ == 3)
    {
        signed char choice = UpdateChoice();
        if (choice != -1)
        {
            if (choice != 1)
                return;
            LoadResult(0);
            step_++;
            return;
        }
        step_ = 0;
    }
    else if (step_ == 4)
    {
        arrowTimer_ = 0;
        if (resultTask_ == -1)
        {
            unsigned char done = UpdateResult(0);
            if (done == 0)
                return;
            LoadResultSprite(results_);
            return;
        }
        else
        {
            unsigned char done = UpdateResultSprite();
            if (done == 0)
                return;
            showResult_ = 0;
            if (!(func_020dd4c4(func_020100a8(GameState::GetInstance()), results_) & 4))
            {
                step_ = 7;
                return;
            }
            message_ = female_ + 4;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 5)
    {
        OpenChoice();
        step_++;
    }
    else if (step_ == 6)
    {
        signed char choice = UpdateChoice();
        if (choice != -1)
        {
            if (choice == 1)
                step_++;
            return;
        }
        step_ = 0;
    }
    else if (step_ == 7)
    {
        if (ingredients_.HasIngredients(2))
        {
            message_ = 6;
            messageStep_ = 0;
            step_++;
        return;
        }
        message_ = 8;
        messageStep_ = 0;
        state_ = AlchemyMenuState_MakeRecipe;
        pot_->CloseWindow();
        step_ = 0;
    }
    else if (step_ == 8)
    {
        func_02080c68(menu_, 9, 1);
        DrawTimes();
        flags_ |= ALCHEMY_MENU_COUNT;
        repeatDelay_ = 0;
        step_++;
    }
    else if (step_ == 9)
    {
        arrowTimer_ = 0;
        unsigned char result = UpdateTimes();
        if (result == 1)
            return;
        if (func_02012444(data_02114e30, 1) || result == 2)
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0208203c(&repeat_);
            cursor_ = 0;
            times_ = count_;
            func_0207fdcc(menu_, 0xa);
            state_ = AlchemyMenuState_MakeRecipe;
            pot_->CloseWindow();
            step_ = 0;
            message_ = 7;
            messageStep_ = 0;
            flags_ &= ~ALCHEMY_MENU_COUNT;
            return;
        }
        unsigned char cancelled = IsCancelled();
        if (cancelled == 0 && result != 3)
            return;
        func_0207fdcc(menu_, 0xa);
        step_ = 0;
        flags_ &= ~ALCHEMY_MENU_COUNT;
        count_ = 1;
        UpdateMultiplier();
    }
    else if (step_ == 0x64)
    {
        unsigned char advanced = IsMessageAdvanced();
        if (advanced == 0)
            return;
        message_ = 1;
        messageStep_ = 0;
        flags_ |= ALCHEMY_MENU_MESSAGE;
        step_++;
    }
    else if (step_ == 0x65)
    {
        unsigned char advanced = IsMessageAdvanced();
        if (advanced != 0)
        {
            advanced = 0;
            step_ = 0;
        }
    }
}

void AlchemyMenu::SetListShown(Menu* menu, int shown, unsigned char* background)
{
    if (menu == 0)
        return;
    if (shown)
    {
        flags_ |= ALCHEMY_MENU_BOOK;
        *background = 1;
        func_02080c20(menu, 0xd);
        func_02080c20(menu, 0xe);
        func_02080c20(menu, 0xf);
        func_02080c20(menu, 9);
        return;
    }
    flags_ &= ~ALCHEMY_MENU_BOOK;
    *background = 0;
    func_02080c04(menu, 0xd);
    func_02080c04(menu, 0xe);
    func_02080c04(menu, 0xf);
    func_02080c04(menu, 9);
}

// NONMATCHING: the C matches 97.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::State_MakeRecipe()
{
    AlchemyPot* pot = pot_;
    BackgroundLoader::GetInstance();
    if (step_ == 0)
    {
        showResult_ = 0;
        if (IsMessageAdvanced())
        {
            func_0207fdcc(menu_, 0);
            func_0207fdcc(menu_, 1);
            func_02080c68(menu_, 9, 0);
            flags_ &= ~ALCHEMY_MENU_GREAT;
            if (recipe_->greatRecipe_ >= 0)
            {
                successRate_ = ingredients_.GetSuccessRate(recipe_->greatRecipe_);
                message_ = 0xd;
                messageStep_ = 0;
                flags_ |= ALCHEMY_MENU_MESSAGE;
                step_++;
                if (NextRandomMax(GetBTRandom(), 10000) / 100U < (unsigned int)successRate_)
                    flags_ |= ALCHEMY_MENU_GREAT;
                LoadResult((flags_ & ALCHEMY_MENU_GREAT) ? 1 : 0);
                return;
            }
            pot->flags_ &= ~ALCHEMY_POT_ITEM_SHOWN;
            fadeTimer_ = 0;
            nextStep_ = 0x64;
            step_ = 0x96;
            SetListShown(menu_, 0, &background_);
        }
    }
    else if (step_ == 1)
    {
        if (IsMessageAdvanced() && resultTask_ == -1)
        {
            if (UpdateResult((flags_ & ALCHEMY_MENU_GREAT) ? 1 : 0))
            {
                LoadResultSprite(results_);
                return;
            }
        }
        else if (resultTask_ != -1 && UpdateResultSprite())
        {
            message_ = female_ + 0xe;
            messageStep_ = 0;
            step_++;
            return;
        }
    }
    else if (step_ == 2)
    {
        if (IsMessageAdvanced())
        {
            short message = 0x10;
            if (successRate_ >= 3 && successRate_ < 10)
                message = 0x11;
            else if (successRate_ >= 10 && successRate_ <= 99)
                message = 0x12;
            else if (successRate_ == 100)
                message = female_ + 0x16;
            message_ = message;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 3)
    {
        if (IsMessageAdvanced())
        {
            short message = 0x13;
            step_++;
            if (successRate_ == 100)
            {
                step_ = 6;
                message = 0x18;
            }
            message_ = message;
            messageStep_ = 0;
        }
    }
    else if (step_ == 4)
    {
        if (IsMessageAdvanced())
        {
            message_ = 0x14;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 5)
    {
        if (IsMessageAdvanced())
        {
            message_ = 0x15;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 6)
    {
        OpenChoice();
        step_++;
    }
    else if (step_ == 7)
    {
        switch (UpdateChoice())
        {
        case 1:
        {
            if (flags_ & ALCHEMY_MENU_GREAT)
            {
                Recipe* recipe = recipe_;
                ingredients_.AddResult(recipe->greatRecipe_, recipe->id_, &table_);
            }
            else
            {
                ingredients_.AddResult(recipe_->id_, -1, &table_);
            }
            GiveResult(results_, recipe_, times_);
            unsigned char page = page_;
            unsigned char pages = pages_;
            LoadInventory();
            page_ = page;
            pages_ = pages;
            step_++;
            return;
        }
        case -1:
            message_ = 0x19;
            messageStep_ = 0;
            flags_ = (flags_ | ALCHEMY_MENU_MESSAGE) & ~ALCHEMY_MENU_GREAT;
            step_ = 0x5a;
            return;
        }
    }
    else if (step_ == 0x5a)
    {
        if (IsMessageAdvanced())
        {
            func_02080c20(menu_, 0);
            message_ = 1;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            step_ = 0x79;
        }
    }
    else if (step_ == 8)
    {
        if (BackgroundLoader::GetInstance()->GetNumQueuedTasks() <= 0)
            step_++;
    }
    else if (step_ == 9)
    {
        message_ = 0x36;
        messageStep_ = 0;
        func_02080c04(menu_, 0);
        step_++;
    }
    else if (step_ == 10)
    {
        flags_ |= ALCHEMY_MENU_SAVING;
        if (BackgroundLoader::GetInstance()->GetNumQueuedTasks() <= 0)
        {
            func_020466e4(func_020d6c00(), 0x80);
            func_020a9ea4(save_);
            step_++;
        }
    }
    else if (step_ == 11)
    {
        BackgroundLoader::AddLockGlobal();
        BackgroundLoader::FreeAllocationsGlobal();
        int retries = 8;
        func_0202ae18();
        if (func_0202c540())
            retries = 0x14;
        if (func_020aad1c(save_, data_0211e33c, retries, 0) == 1)
        {
            func_020466f4(func_020d6c00(), 0x80);
            step_++;
            flags_ &= ~ALCHEMY_MENU_SAVING;
        }
        BackgroundLoader::RemoveLockGlobal();
    }
    else if (step_ == 12)
    {
        message_ = 0x37;
        messageStep_ = 0;
        step_++;
    }
    else if (step_ == 13)
    {
        if (IsMessageAdvanced())
        {
            message_ = 0x1a;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            step_++;
        }
    }
    else if (step_ == 14)
    {
        arrowTimer_ = 0;
        if (IsMessageAdvanced())
        {
            SetListShown(menu_, 0, &background_);
            pot->flags_ &= ~ALCHEMY_POT_ITEM_SHOWN;
            fadeTimer_ = 0;
            nextStep_ = 0xf;
            step_ = 0x96;
        }
    }
    else if (step_ == 15)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_WORK;
        step_++;
    }
    else if (step_ == 16)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_OUT;
        step_++;
    }
    else if (step_ == 17)
    {
        showResult_ = 1;
        const char** name = func_020e5294(itemNames_, results_[0].item_);
        if (name != 0)
        {
            memset(texts_[0], 0, 0x80);
            func_020e4864(*name, texts_[0], 1, 0, 0, 0);
            func_02080f8c(menu_, 0x7f, texts_[0]);
        }
        func_020805f4(menu_, 0x7f);
        func_020813ec(menu_, 0x12);
        int great = 1;
        pot->flags_ |= ALCHEMY_POT_ANIMATION_END;
        saved_ = 1;
        int sound = 0x3e;
        if (!(flags_ & ALCHEMY_MENU_GREAT))
            great = 0;
        if (great)
        {
            sound = 0x3f;
            pot_->StartEffect();
        }
        func_0209c830(data_02109bf4, sound);
        func_02080c04(menu_, 0);
        message_ = 0xc;
        messageStep_ = 0;
        step_++;
    }
    else if (step_ == 18)
    {
        if (IsMessageAdvanced())
        {
            int great;
            if (flags_ & ALCHEMY_MENU_GREAT)
                great = 1;
            else
                great = 0;
            if (great)
                pot->StopEffect();
            message_ = 0x38;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 19)
    {
        if (IsMessageAdvanced())
        {
            func_0207fdcc(menu_, 0x12);
            int great = 0;
            showResult_ = 0;
            short message = 0x1f;
            pot->flags_ &= ~ALCHEMY_POT_ANIMATION_DONE;
            if (flags_ & ALCHEMY_MENU_GREAT)
                great = 1;
            if (great)
                message = female_ + 0x1b;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            message_ = message;
            messageStep_ = 0;
            step_++;
        }
    }
    else if (step_ == 20)
    {
        if (IsMessageAdvanced())
        {
            short message = 0x20;
            int great;
            if (flags_ & ALCHEMY_MENU_GREAT)
                great = 1;
            else
                great = 0;
            if (great)
                message = female_ + 0x1d;
            message_ = message;
            messageStep_ = 0;
            step_ = 0x78;
        }
    }
    else if (step_ == 0x64)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_WORK;
        step_++;
    }
    else if (step_ == 0x65)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_OUT;
        step_++;
    }
    else if (step_ == 0x66)
    {
        ingredients_.AddResult(recipe_->id_, -1, &table_);
        GiveResult(results_, recipe_, times_);
        unsigned char page = page_;
        unsigned char pages = pages_;
        LoadInventory();
        page_ = page;
        pages_ = pages;
        showResult_ = 1;
        const char** name = func_020e5294(itemNames_, results_[0].item_);
        if (name != 0)
        {
            memset(texts_[0], 0, 0x80);
            func_020e4864(*name, texts_[0], 1, 0, 0, 0);
            func_02080f8c(menu_, 0x7f, texts_[0]);
        }
        func_020805f4(menu_, 0x7f);
        func_020813ec(menu_, 0x12);
        pot->flags_ |= ALCHEMY_POT_ANIMATION_END;
        saved_ = 1;
        func_0209c830(data_02109bf4, 0x3e);
        message_ = 0xc;
        messageStep_ = 0;
        step_++;
    }
    else if (step_ == 0x67)
    {
        if (IsMessageAdvanced())
        {
            message_ = 0x38;
            messageStep_ = 0;
            step_ = 0x78;
        }
    }
    else if (step_ == 0x78)
    {
        if (saved_ != 0)
        {
            arrowTimer_ = 0;
            return;
        }
        Unknown_020dbd9c* effect = &pot->subEffect_;
        if (effect != 0 && effect->unk_14 != 0)
            return;
        if (IsMessageAdvanced())
        {
            func_0207fdcc(menu_, 0x12);
            showResult_ = 0;
            pot->flags_ &= ~ALCHEMY_POT_ANIMATION_DONE;
            message_ = 1;
            messageStep_ = 0;
            flags_ |= ALCHEMY_MENU_MESSAGE;
            step_++;
        }
    }
    else if (step_ == 0x79)
    {
        if (IsMessageAdvanced())
        {
            SetListShown(menu_, 1, &background_);
            func_0207fdcc(menu_, 0);
            func_0207fdcc(menu_, 1);
            state_ = AlchemyMenuState_RecipeList;
            step_ = 0;
        }
    }
    else if (step_ == 0x96)
    {
        pot->flags_ |= ALCHEMY_POT_ANIMATION_OPEN;
        fadeTimer_++;
        if (fadeTimer_ >= 10)
        {
            fadeTimer_ = 0;
            pot->flags_ &= ~ALCHEMY_POT_ANIMATION_OPEN;
            pot->flags_ |= ALCHEMY_POT_ANIMATION_IN;
            step_ = nextStep_;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11AlchemyMenu12SetListShownEP4MenuiPh(); // AlchemyMenu::SetListShown
}

asm void AlchemyMenu::State_MakeRecipe()
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x8
    mov r5, r0
    ldr r4, [r5, #0x10]
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r0, [r5, #0x390]
    cmp r0, #0x0
    bne @L0215e7e0
    mov r1, #0x0
    mov r0, r5
    str r1, [r5, #0x3b4]
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    ldr r0, [r5, #0x14]
    mov r1, #0x0
    bl func_0207fdcc
    ldr r0, [r5, #0x14]
    mov r1, #0x1
    bl func_0207fdcc
    ldr r0, [r5, #0x14]
    mov r1, #0x9
    mov r2, #0x0
    bl func_02080c68
    add r0, r5, #0x300
    ldrh r1, [r0, #0x94]
    bic r1, r1, #0x40
    strh r1, [r0, #0x94]
    ldr r0, [r5, #0x34]
    ldrsh r1, [r0, #0x14]
    cmp r1, #0x0
    blt @L0215e7a0
    add r0, r5, #0x74
    bl _ZN18AlchemyIngredients14GetSuccessRateEs
    add r1, r5, #0x300
    strh r0, [r1, #0x82]
    mov r0, #0xd
    strh r0, [r1, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrh r0, [r1, #0x94]
    orr r0, r0, #0x20
    strh r0, [r1, #0x94]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    bl GetBTRandom
    ldr r1, =0x2710
    bl NextRandomMax
    mov r1, #0x64
    bl _u32_div_f
    add r1, r5, #0x300
    ldrsh r2, [r1, #0x82]
    cmp r0, r2
    ldrloh r0, [r1, #0x94]
    orrlo r0, r0, #0x40
    strloh r0, [r1, #0x94]
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x40
    movne r1, #0x1
    moveq r1, #0x0
    mov r0, r5
    bl _ZN11AlchemyMenu10LoadResultEi
    b @L0215f2a0
@L0215e7a0:
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    add r3, r5, #0x97
    mov r2, #0x0
    bic r1, r1, #0x40
    strh r1, [r0, #0xe2]
    strb r2, [r5, #0x42d]
    mov r0, #0x64
    strb r0, [r5, #0x42e]
    mov r0, #0x96
    strb r0, [r5, #0x390]
    ldr r1, [r5, #0x14]
    mov r0, r5
    add r3, r3, #0x300
    bl _ZN11AlchemyMenu12SetListShownEP4MenuiPh
    b @L0215f2a0
@L0215e7e0:
    cmp r0, #0x1
    bne @L0215e884
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215e83c
    ldr r1, [r5, #0x428]
    mvn r0, #0x0
    cmp r1, r0
    bne @L0215e83c
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x40
    movne r1, #0x1
    moveq r1, #0x0
    mov r0, r5
    bl _ZN11AlchemyMenu12UpdateResultEi
    cmp r0, #0x0
    beq @L0215f2a0
    mov r0, r5
    add r1, r5, #0x17c
    bl _ZN11AlchemyMenu16LoadResultSpriteEP13PotIngredient
    b @L0215f2a0
@L0215e83c:
    ldr r1, [r5, #0x428]
    mvn r0, #0x0
    cmp r1, r0
    beq @L0215f2a0
    mov r0, r5
    bl _ZN11AlchemyMenu18UpdateResultSpriteEv
    cmp r0, #0x0
    beq @L0215f2a0
    ldrb r2, [r5, #0x396]
    add r0, r5, #0x300
    mov r1, #0x0
    add r2, r2, #0xe
    strh r2, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215e884:
    cmp r0, #0x2
    bne @L0215e914
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r0, r5, #0x300
    ldrsh r0, [r0, #0x82]
    mov r1, #0x10
    cmp r0, #0x3
    blt @L0215e8bc
    cmp r0, #0xa
    movlt r1, #0x11
    blt @L0215e8f4
@L0215e8bc:
    add r0, r5, #0x300
    ldrsh r0, [r0, #0x82]
    cmp r0, #0xa
    blt @L0215e8d8
    cmp r0, #0x63
    movle r1, #0x12
    ble @L0215e8f4
@L0215e8d8:
    add r0, r5, #0x300
    ldrsh r0, [r0, #0x82]
    cmp r0, #0x64
    ldreqb r0, [r5, #0x396]
    addeq r0, r0, #0x16
    moveq r0, r0, lsl #0x10
    moveq r1, r0, asr #0x10
@L0215e8f4:
    add r0, r5, #0x300
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215e914:
    cmp r0, #0x3
    bne @L0215e968
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    ldrb r1, [r5, #0x390]
    add r0, r5, #0x300
    mov r2, #0x13
    add r1, r1, #0x1
    strb r1, [r5, #0x390]
    ldrsh r0, [r0, #0x82]
    cmp r0, #0x64
    moveq r0, #0x6
    streqb r0, [r5, #0x390]
    moveq r2, #0x18
    add r0, r5, #0x300
    strh r2, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    b @L0215f2a0
@L0215e968:
    cmp r0, #0x4
    bne @L0215e9a4
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r0, r5, #0x300
    mov r1, #0x14
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215e9a4:
    cmp r0, #0x5
    bne @L0215e9e0
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r0, r5, #0x300
    mov r1, #0x15
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215e9e0:
    cmp r0, #0x6
    bne @L0215ea00
    mov r0, r5
    bl _ZN11AlchemyMenu10OpenChoiceEv
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ea00:
    cmp r0, #0x7
    bne @L0215eadc
    mov r0, r5
    bl _ZN11AlchemyMenu12UpdateChoiceEv
    mvn r1, #0x0
    cmp r0, r1
    beq @L0215eaac
    cmp r0, #0x1
    bne @L0215f2a0
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x40
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    beq @L0215ea5c
    ldr r2, [r5, #0x34]
    add r0, r5, #0x74
    ldrsh r1, [r2, #0x14]
    ldrsh r2, [r2, #0x0]
    add r3, r5, #0x14c
    bl _ZN18AlchemyIngredients9AddResultEssP11RecipeTable
    b @L0215ea74
@L0215ea5c:
    ldr r1, [r5, #0x34]
    add r0, r5, #0x74
    ldrsh r1, [r1, #0x0]
    add r3, r5, #0x14c
    mvn r2, #0x0
    bl _ZN18AlchemyIngredients9AddResultEssP11RecipeTable
@L0215ea74:
    ldrb r2, [r5, #0x387]
    ldr r1, [r5, #0x34]
    add r0, r5, #0x17c
    bl GiveResult
    ldrb r4, [r5, #0x388]
    ldrb r6, [r5, #0x389]
    mov r0, r5
    bl _ZN11AlchemyMenu13LoadInventoryEv
    strb r4, [r5, #0x388]
    strb r6, [r5, #0x389]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215eaac:
    add r0, r5, #0x300
    mov r1, #0x19
    strh r1, [r0, #0x7e]
    mov r1, #0x0
    strb r1, [r5, #0x392]
    ldrh r2, [r0, #0x94]
    mov r1, #0x5a
    orr r2, r2, #0x20
    bic r2, r2, #0x40
    strh r2, [r0, #0x94]
    strb r1, [r5, #0x390]
    b @L0215f2a0
@L0215eadc:
    cmp r0, #0x5a
    bne @L0215eb2c
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    ldr r0, [r5, #0x14]
    mov r1, #0x0
    bl func_02080c20
    add r0, r5, #0x300
    mov r1, #0x1
    strh r1, [r0, #0x7e]
    mov r1, #0x0
    strb r1, [r5, #0x392]
    ldrh r2, [r0, #0x94]
    mov r1, #0x79
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strb r1, [r5, #0x390]
    b @L0215f2a0
@L0215eb2c:
    cmp r0, #0x8
    bne @L0215eb50
    bl _ZN16BackgroundLoader11GetInstanceEv
    bl _ZN16BackgroundLoader17GetNumQueuedTasksEv
    cmp r0, #0x0
    ldrleb r0, [r5, #0x390]
    addle r0, r0, #0x1
    strleb r0, [r5, #0x390]
    b @L0215f2a0
@L0215eb50:
    cmp r0, #0x9
    bne @L0215eb84
    add r0, r5, #0x300
    mov r1, #0x36
    strh r1, [r0, #0x7e]
    mov r1, #0x0
    strb r1, [r5, #0x392]
    ldr r0, [r5, #0x14]
    bl func_02080c04
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215eb84:
    cmp r0, #0xa
    bne @L0215ebd0
    add r0, r5, #0x300
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x200
    strh r1, [r0, #0x94]
    bl _ZN16BackgroundLoader11GetInstanceEv
    bl _ZN16BackgroundLoader17GetNumQueuedTasksEv
    cmp r0, #0x0
    bgt @L0215f2a0
    bl func_020d6c00
    mov r1, #0x80
    bl func_020466e4
    add r0, r5, #0x3c
    bl func_020a9ea4
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ebd0:
    cmp r0, #0xb
    bne @L0215ec40
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    mov r4, #0x8
    bl func_0202ae18
    bl func_0202c540
    cmp r0, #0x0
    movne r4, #0x14
    ldr r1, =data_0211e33c
    mov r2, r4
    add r0, r5, #0x3c
    mov r3, #0x0
    bl func_020aad1c
    cmp r0, #0x1
    bne @L0215ec38
    bl func_020d6c00
    mov r1, #0x80
    bl func_020466f4
    ldrb r1, [r5, #0x390]
    add r0, r5, #0x300
    add r1, r1, #0x1
    strb r1, [r5, #0x390]
    ldrh r1, [r0, #0x94]
    bic r1, r1, #0x200
    strh r1, [r0, #0x94]
@L0215ec38:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    b @L0215f2a0
@L0215ec40:
    cmp r0, #0xc
    bne @L0215ec6c
    add r0, r5, #0x300
    mov r1, #0x37
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ec6c:
    cmp r0, #0xd
    bne @L0215ecb4
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r0, r5, #0x300
    mov r1, #0x1a
    strh r1, [r0, #0x7e]
    mov r1, #0x0
    strb r1, [r5, #0x392]
    ldrh r1, [r0, #0x94]
    orr r1, r1, #0x20
    strh r1, [r0, #0x94]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ecb4:
    cmp r0, #0xe
    bne @L0215ed18
    mov r1, #0x0
    mov r0, r5
    strb r1, [r5, #0x42c]
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r2, r5, #0x97
    ldr r1, [r5, #0x14]
    mov r0, r5
    add r3, r2, #0x300
    mov r2, #0x0
    bl _ZN11AlchemyMenu12SetListShownEP4MenuiPh
    add r0, r4, #0xa00
    ldrh r3, [r0, #0xe2]
    mov r2, #0x0
    mov r1, #0xf
    bic r3, r3, #0x40
    strh r3, [r0, #0xe2]
    strb r2, [r5, #0x42d]
    strb r1, [r5, #0x42e]
    mov r0, #0x96
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ed18:
    cmp r0, #0xf
    bne @L0215ed40
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x100
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ed40:
    cmp r0, #0x10
    bne @L0215ed68
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x200
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ed68:
    cmp r0, #0x11
    bne @L0215ee6c
    mov r0, #0x1
    str r0, [r5, #0x3b4]
    add r0, r5, #0x100
    ldrsh r1, [r0, #0xec]
    add r0, r5, #0x170
    bl func_020e5294
    movs r6, r0
    beq @L0215edd8
    ldr r0, [r5, #0x4]
    mov r1, #0x0
    ldr r0, [r0, #0x0]
    mov r2, #0x80
    bl memset
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r1, [r5, #0x4]
    ldr r0, [r6, #0x0]
    ldr r1, [r1, #0x0]
    mov r2, #0x1
    bl func_020e4864
    ldr r1, [r5, #0x4]
    ldr r0, [r5, #0x14]
    ldr r2, [r1, #0x0]
    mov r1, #0x7f
    bl func_02080f8c
@L0215edd8:
    ldr r0, [r5, #0x14]
    mov r1, #0x7f
    bl func_020805f4
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_020813ec
    add r0, r4, #0xa00
    ldrh r2, [r0, #0xe2]
    mov r3, #0x1
    add r1, r5, #0x300
    orr r2, r2, #0x400
    strh r2, [r0, #0xe2]
    strb r3, [r5, #0x42f]
    ldrh r0, [r1, #0x94]
    mov r4, #0x3e
    tst r0, #0x40
    moveq r3, #0x0
    cmp r3, #0x0
    beq @L0215ee30
    ldr r0, [r5, #0x10]
    mov r4, #0x3f
    bl _ZN10AlchemyPot11StartEffectEv
@L0215ee30:
    ldr r0, =data_02109bf4
    mov r1, r4
    bl func_0209c830
    ldr r0, [r5, #0x14]
    mov r1, #0x0
    bl func_02080c04
    add r0, r5, #0x300
    mov r1, #0xc
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ee6c:
    cmp r0, #0x12
    bne @L0215eecc
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x40
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    beq @L0215eea8
    mov r0, r4
    bl _ZN10AlchemyPot10StopEffectEv
@L0215eea8:
    add r0, r5, #0x300
    mov r1, #0x38
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215eecc:
    cmp r0, #0x13
    bne @L0215ef5c
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_0207fdcc
    mov r6, #0x0
    str r6, [r5, #0x3b4]
    add r0, r4, #0xa00
    ldrh r2, [r0, #0xe2]
    add r1, r5, #0x300
    mov r3, #0x1f
    bic r2, r2, #0x800
    strh r2, [r0, #0xe2]
    ldrh r0, [r1, #0x94]
    mov r1, #0x0
    tst r0, #0x40
    movne r6, #0x1
    cmp r6, #0x0
    ldrneb r0, [r5, #0x396]
    addne r0, r0, #0x1b
    movne r0, r0, lsl #0x10
    movne r3, r0, asr #0x10
    add r0, r5, #0x300
    ldrh r2, [r0, #0x94]
    orr r2, r2, #0x20
    strh r2, [r0, #0x94]
    strh r3, [r0, #0x7e]
    strb r1, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215ef5c:
    cmp r0, #0x14
    bne @L0215efbc
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    mov r1, #0x20
    tst r0, #0x40
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    ldrneb r0, [r5, #0x396]
    addne r0, r0, #0x1d
    movne r0, r0, lsl #0x10
    movne r1, r0, asr #0x10
    add r0, r5, #0x300
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    mov r0, #0x78
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215efbc:
    cmp r0, #0x64
    bne @L0215efe4
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x100
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215efe4:
    cmp r0, #0x65
    bne @L0215f00c
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x200
    strh r1, [r0, #0xe2]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215f00c:
    cmp r0, #0x66
    bne @L0215f11c
    ldr r1, [r5, #0x34]
    add r0, r5, #0x74
    ldrsh r1, [r1, #0x0]
    add r3, r5, #0x14c
    mvn r2, #0x0
    bl _ZN18AlchemyIngredients9AddResultEssP11RecipeTable
    ldrb r2, [r5, #0x387]
    ldr r1, [r5, #0x34]
    add r0, r5, #0x17c
    bl GiveResult
    ldrb r6, [r5, #0x388]
    ldrb r7, [r5, #0x389]
    mov r0, r5
    bl _ZN11AlchemyMenu13LoadInventoryEv
    strb r6, [r5, #0x388]
    strb r7, [r5, #0x389]
    mov r0, #0x1
    str r0, [r5, #0x3b4]
    add r0, r5, #0x100
    ldrsh r1, [r0, #0xec]
    add r0, r5, #0x170
    bl func_020e5294
    movs r6, r0
    beq @L0215f0bc
    ldr r0, [r5, #0x4]
    mov r1, #0x0
    ldr r0, [r0, #0x0]
    mov r2, #0x80
    bl memset
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r1, [r5, #0x4]
    ldr r0, [r6, #0x0]
    ldr r1, [r1, #0x0]
    mov r2, #0x1
    bl func_020e4864
    ldr r1, [r5, #0x4]
    ldr r0, [r5, #0x14]
    ldr r2, [r1, #0x0]
    mov r1, #0x7f
    bl func_02080f8c
@L0215f0bc:
    ldr r0, [r5, #0x14]
    mov r1, #0x7f
    bl func_020805f4
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_020813ec
    add r1, r4, #0xa00
    ldrh r3, [r1, #0xe2]
    ldr r0, =data_02109bf4
    mov r2, #0x1
    orr r3, r3, #0x400
    strh r3, [r1, #0xe2]
    mov r1, #0x3e
    strb r2, [r5, #0x42f]
    bl func_0209c830
    add r0, r5, #0x300
    mov r1, #0xc
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215f11c:
    cmp r0, #0x67
    bne @L0215f154
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r0, r5, #0x300
    mov r1, #0x38
    strh r1, [r0, #0x7e]
    mov r0, #0x0
    strb r0, [r5, #0x392]
    mov r0, #0x78
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215f154:
    cmp r0, #0x78
    bne @L0215f1e4
    ldrb r0, [r5, #0x42f]
    cmp r0, #0x0
    movne r0, #0x0
    strneb r0, [r5, #0x42c]
    bne @L0215f2a0
    add r0, r4, #0x2a0
    adds r0, r0, #0x1000
    ldrneb r0, [r0, #0x14]
    cmpne r0, #0x0
    bne @L0215f2a0
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    ldr r0, [r5, #0x14]
    mov r1, #0x12
    bl func_0207fdcc
    mov r12, #0x0
    str r12, [r5, #0x3b4]
    add r0, r4, #0xa00
    ldrh r3, [r0, #0xe2]
    add r1, r5, #0x300
    mov r2, #0x1
    bic r3, r3, #0x800
    strh r3, [r0, #0xe2]
    strh r2, [r1, #0x7e]
    strb r12, [r5, #0x392]
    ldrh r0, [r1, #0x94]
    orr r0, r0, #0x20
    strh r0, [r1, #0x94]
    ldrb r0, [r5, #0x390]
    add r0, r0, #0x1
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215f1e4:
    cmp r0, #0x79
    bne @L0215f240
    mov r0, r5
    bl _ZN11AlchemyMenu17IsMessageAdvancedEv
    cmp r0, #0x0
    beq @L0215f2a0
    add r2, r5, #0x97
    ldr r1, [r5, #0x14]
    mov r0, r5
    add r3, r2, #0x300
    mov r2, #0x1
    bl _ZN11AlchemyMenu12SetListShownEP4MenuiPh
    ldr r0, [r5, #0x14]
    mov r1, #0x0
    bl func_0207fdcc
    ldr r0, [r5, #0x14]
    mov r1, #0x1
    bl func_0207fdcc
    mov r0, #0xa
    strb r0, [r5, #0x38f]
    mov r0, #0x0
    strb r0, [r5, #0x390]
    b @L0215f2a0
@L0215f240:
    cmp r0, #0x96
    bne @L0215f2a0
    add r1, r4, #0xa00
    ldrh r2, [r1, #0xe2]
    add r0, r4, #0xe2
    add r3, r0, #0xa00
    orr r0, r2, #0x2000
    strh r0, [r1, #0xe2]
    ldrb r0, [r5, #0x42d]
    add r1, r0, #0x1
    and r0, r1, #0xff
    strb r1, [r5, #0x42d]
    cmp r0, #0xa
    blo @L0215f2a0
    mov r0, #0x0
    strb r0, [r5, #0x42d]
    ldrh r0, [r3, #0x0]
    bic r0, r0, #0x2000
    strh r0, [r3, #0x0]
    ldrh r0, [r3, #0x0]
    orr r0, r0, #0x80
    strh r0, [r3, #0x0]
    ldrb r0, [r5, #0x42e]
    strb r0, [r5, #0x390]
@L0215f2a0:
    add sp, sp, #0x8
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

void AlchemyMenu::State_FadeOut()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    if (step_ == 0)
    {
        if (choice_ != 0)
            func_020e25e8(choice_);
        SetBrightness(resources, -0x10, 0x10);
        if (!(flags_ & ALCHEMY_MENU_NO_SCENE))
            func_0209c678(data_02109bf4, 0xf);
        step_++;
    }
    else if (step_ == 1)
    {
        if (!IsBrightnessTransitionActive(resources))
        {
            state_ = AlchemyMenuState_End;
            step_ = 0;
        }
    }
}

void AlchemyMenu::DrawMainTexts()
{
    short text = -1;
    switch (mainCursor_)
    {
    case 2:
        text = 4;
        break;
    case 3:
        text = 7;
        break;
    case 4:
        break;
    }
    short item = 5;
    for (unsigned char i = 0; i < 3; i++)
    {
        func_0208103c(menu_, item, text);
        item++;
        if (text >= 0)
            text++;
    }
    func_020813ec(menu_, 3);
}

// NONMATCHING: the C matches 66.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::UpdateItemPage()
{
    if (!(flags_ & ALCHEMY_MENU_PAGES))
        return;
    int result = menuResult_;
    int changed = 0;
    if (result & 0x10)
    {
        changed = 1;
        page_++;
    }
    else if (result & 0x20)
    {
        changed = 1;
        page_--;
    }
    if (page_ == 0xff)
        page_ = pages_ - 1;
    if (pages_ <= page_)
        page_ = 0;
    if (!changed)
        return;
    unsigned short size = GetCategorySize();
    short position = page_ * 8 + (short)(itemCursor_ - func_02080468(menu_, 0x11));
    if (size <= position)
        position = size - 1;
    itemCursor_ = func_02080468(menu_, 0x11) + (short)(position % 8);
    DrawItems();
    ShowSelectedItem();
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11AlchemyMenu15GetCategorySizeEv(); // AlchemyMenu::GetCategorySize
    void _ZN11AlchemyMenu16ShowSelectedItemEv(); // AlchemyMenu::ShowSelectedItem
    void _ZN11AlchemyMenu9DrawItemsEv(); // AlchemyMenu::DrawItems
}

asm void AlchemyMenu::UpdateItemPage()
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r0
    add r0, r5, #0x300
    ldrh r0, [r0, #0x94]
    tst r0, #0x4
    ldmeqia sp!, {r3, r4, r5, pc}
    ldr r0, [r5, #0x350]
    mov r2, #0x0
    tst r0, #0x10
    ldrneb r0, [r5, #0x388]
    movne r2, #0x1
    addne r0, r0, #0x1
    strneb r0, [r5, #0x388]
    bne @L0215f424
    tst r0, #0x20
    ldrneb r0, [r5, #0x388]
    movne r2, #0x1
    subne r0, r0, #0x1
    strneb r0, [r5, #0x388]
@L0215f424:
    ldrb r0, [r5, #0x388]
    cmp r0, #0xff
    ldreqb r0, [r5, #0x389]
    subeq r0, r0, #0x1
    streqb r0, [r5, #0x388]
    ldrb r1, [r5, #0x389]
    ldrb r0, [r5, #0x388]
    cmp r1, r0
    movls r0, #0x0
    strlsb r0, [r5, #0x388]
    cmp r2, #0x0
    ldmeqia sp!, {r3, r4, r5, pc}
    mov r0, r5
    bl _ZN11AlchemyMenu15GetCategorySizeEv
    mov r4, r0
    ldr r0, [r5, #0x14]
    mov r1, #0x11
    bl func_02080468
    add r1, r5, #0x300
    ldrsh r2, [r1, #0x64]
    ldrb r1, [r5, #0x388]
    sub r0, r2, r0
    mov r0, r0, lsl #0x10
    mov r1, r1, lsl #0x3
    add r0, r1, r0, asr #0x10
    mov r0, r0, lsl #0x10
    cmp r4, r0, asr #0x10
    mov r0, r0, asr #0x10
    suble r0, r4, #0x1
    movle r0, r0, lsl #0x10
    movle r0, r0, asr #0x10
    mov r1, r0, lsr #0x1f
    rsb r0, r1, r0, lsl #0x1d
    add r1, r1, r0, ror #0x1d
    mov r4, r1, lsl #0x10
    ldr r0, [r5, #0x14]
    mov r1, #0x11
    bl func_02080468
    add r2, r0, r4, asr #0x10
    add r1, r5, #0x300
    mov r0, r5
    strh r2, [r1, #0x64]
    bl _ZN11AlchemyMenu9DrawItemsEv
    mov r0, r5
    bl _ZN11AlchemyMenu16ShowSelectedItemEv
    ldmia sp!, {r3, r4, r5, pc}
}
#endif

// NONMATCHING: the C matches 69.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::DrawItems()
{
    short category = categoryCursor_ - 0x5b;
    unsigned short position = page_ * 8;
    Menu* menu = menu_;
    unsigned char* counts = counts_[category];
    short* items = items_[category];
    unsigned int size = sizes_[category];
    short name = 0x64;
    short icon = 0x6c;
    short count = 0x74;
    func_02080b54(menu, 0x11);
    func_02080608(menu, 0x11);
    flags_ &= ~ALCHEMY_MENU_PAGES;
    if (size > 8)
        flags_ |= ALCHEMY_MENU_PAGES;
    for (unsigned char i = 0; i < 8; i++)
    {
        if (size > position && items[position] > 0)
        {
            func_020806c4(menu, name);
            func_02080b40(menu, name);
            func_02080b40(menu, icon);
            func_02080b40(menu, count);
            const char** text = func_020e5294(itemNames_, items[position]);
            if (text != 0)
            {
                memset(texts_[i], 0, 4);
                func_020e4864(*text, texts_[i], 1, 0, 0, 0);
                func_02080f8c(menu_, name, texts_[i]);
            }
            func_020805f4(menu, name);
            unsigned char amount = counts[position];
            if (item_ == items[position])
                amount -= count_;
            func_02080fa8(menu, count, amount);
        }
        name++;
        icon++;
        count++;
        position++;
    }
    func_02080b40(menu, 0x7c);
    func_02080b40(menu, 0x7d);
    func_02080b40(menu, 0x7e);
    func_02080fa8(menu, 0x7c, page_ + 1);
    func_02080fa8(menu, 0x7d, pages_);
    func_02081130(menu, 0x11, (flags_ & ALCHEMY_MENU_PAGES) ? 1 : 0);
    func_020813ec(menu, 0x11);
}
#else
asm void AlchemyMenu::DrawItems()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x18
    mov r10, r0
    add r0, r10, #0x300
    ldrsh r0, [r0, #0x62]
    ldrb r1, [r10, #0x388]
    ldr r7, [r10, #0x4c]
    sub r0, r0, #0x5b
    mov r0, r0, lsl #0x10
    mov r2, r1, lsl #0x13
    mov r9, r0, asr #0x10
    mov r8, r2, lsr #0x10
    ldr r2, [r7, r9, lsl #0x2]
    ldr r5, [r10, #0x48]
    ldr r4, [r10, #0x14]
    ldr r6, [r10, #0x50]
    mov r3, r9, lsl #0x1
    str r2, [sp, #0xc]
    ldrh r2, [r6, r3]
    ldr r5, [r5, r9, lsl #0x2]
    mov r0, r4
    mov r1, #0x11
    str r2, [sp, #0x8]
    mov r6, #0x64
    mov r11, #0x6c
    mov r7, #0x74
    bl func_02080b54
    mov r0, r4
    mov r1, #0x11
    bl func_02080608
    add r1, r10, #0x300
    ldr r0, [sp, #0x8]
    ldrh r2, [r1, #0x94]
    cmp r0, #0x8
    add r3, r10, #0x394
    bic r0, r2, #0x4
    strh r0, [r1, #0x94]
    ldrhih r0, [r3, #0x0]
    mov r9, #0x0
    orrhi r0, r0, #0x4
    strhih r0, [r3, #0x0]
    add r0, r10, #0x300
    str r0, [sp, #0x14]
    b @L0215f6bc
@L0215f58c:
    ldr r0, [sp, #0x8]
    cmp r0, r8
    bls @L0215f684
    mov r0, r8, lsl #0x1
    ldrsh r0, [r5, r0]
    cmp r0, #0x0
    ble @L0215f684
    mov r0, r4
    mov r1, r6
    bl func_020806c4
    mov r0, r4
    mov r1, r6
    bl func_02080b40
    mov r0, r4
    mov r1, r11
    bl func_02080b40
    mov r0, r4
    mov r1, r7
    bl func_02080b40
    mov r1, r8, lsl #0x1
    ldrsh r1, [r5, r1]
    add r0, r10, #0x170
    bl func_020e5294
    str r0, [sp, #0x10]
    cmp r0, #0x0
    beq @L0215f644
    ldr r0, [r10, #0x4]
    mov r1, #0x0
    ldr r0, [r0, r9, lsl #0x2]
    mov r2, #0x4
    bl memset
    mov r0, #0x0
    str r0, [sp, #0x0]
    str r0, [sp, #0x4]
    ldr r0, [sp, #0x10]
    ldr r1, [r10, #0x4]
    ldr r0, [r0, #0x0]
    ldr r1, [r1, r9, lsl #0x2]
    mov r2, #0x1
    mov r3, #0x0
    bl func_020e4864
    ldr r2, [r10, #0x4]
    ldr r0, [r10, #0x14]
    ldr r2, [r2, r9, lsl #0x2]
    mov r1, r6
    bl func_02080f8c
@L0215f644:
    mov r0, r4
    mov r1, r6
    bl func_020805f4
    ldr r0, [sp, #0xc]
    ldrb r2, [r0, r8]
    ldr r0, [sp, #0x14]
    ldrsh r1, [r0, #0x70]
    mov r0, r8, lsl #0x1
    ldrsh r0, [r5, r0]
    cmp r1, r0
    ldreqb r0, [r10, #0x38b]
    mov r1, r7
    subeq r0, r2, r0
    andeq r2, r0, #0xff
    mov r0, r4
    bl func_02080fa8
@L0215f684:
    add r0, r6, #0x1
    mov r0, r0, lsl #0x10
    mov r6, r0, asr #0x10
    add r0, r11, #0x1
    mov r0, r0, lsl #0x10
    mov r11, r0, asr #0x10
    add r0, r7, #0x1
    mov r0, r0, lsl #0x10
    mov r7, r0, asr #0x10
    add r0, r8, #0x1
    mov r0, r0, lsl #0x10
    mov r8, r0, lsr #0x10
    add r0, r9, #0x1
    and r9, r0, #0xff
@L0215f6bc:
    cmp r9, #0x8
    blo @L0215f58c
    mov r0, r4
    mov r1, #0x7c
    bl func_02080b40
    mov r0, r4
    mov r1, #0x7d
    bl func_02080b40
    mov r0, r4
    mov r1, #0x7e
    bl func_02080b40
    ldrb r2, [r10, #0x388]
    mov r0, r4
    mov r1, #0x7c
    add r2, r2, #0x1
    bl func_02080fa8
    ldrb r2, [r10, #0x389]
    mov r0, r4
    mov r1, #0x7d
    bl func_02080fa8
    add r0, r10, #0x300
    ldrh r0, [r0, #0x94]
    mov r1, #0x11
    tst r0, #0x4
    movne r2, #0x1
    moveq r2, #0x0
    mov r0, r4
    bl func_02081130
    mov r0, r4
    mov r1, #0x11
    bl func_020813ec
    add sp, sp, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void AlchemyMenu::ShowSelectedItem()
{
    short* items = GetCategoryItems();
    if (items == 0)
        return;
    unsigned short position = (unsigned short)(page_ * 8);
    position += itemCursor_ - 0x64;
    CategorySprites sprites = sCategorySprites;
    short category = categoryCursor_ - 0x5b;
    if (category < 0)
        category = 0;
    if (category > 8)
        category = 8;
    pot_->ShowItem(items[position], sprites.sprites_[category]);
}

void AlchemyMenu::DrawRecipes()
{
    Recipe* recipe = GetPageStart(page_);
    pageStart_ = recipe;
    if (recipe == 0)
        return;
    flags_ &= ~ALCHEMY_MENU_PAGES;
    if (pages_ > 1)
        flags_ |= ALCHEMY_MENU_PAGES;
    Menu* menu = menu_;
    func_02080bac(menu, 9);
    func_0208065c(menu, 9);
    func_02080fa8(menu, 0x3a, page_ + 1);
    func_02080fa8(menu, 0x3b, pages_);
    Recipe* entry = pageStart_;
    const char* unknown = func_020e0434(&menuTexts_, 0x25);
    short item = 0x29;
    for (unsigned char i = 0; i < 0x10; i++)
    {
        if (entry != 0)
        {
            func_02080f8c(menu, item, unknown);
            func_02080cc0(menu, item, 3);
            RecipeRecord* record = ingredients_.FindRecord(entry->id_);
            if (record != 0)
            {
                const char* text = unknown;
                if (record->made_)
                {
                    const char** name = func_020e5294(itemNames_, entry->item_);
                    if (name != 0)
                    {
                        memset(texts_[i], 0, 4);
                        func_020e4864(*name, texts_[i], 1, 0, 0, 0);
                        text = texts_[i];
                    }
                }
                func_02080f8c(menu, item, text);
                func_020805f4(menu, item);
                func_02080cc0(menu, item, 0xf);
            }
            entry = entry->next_;
        }
        else
        {
            func_020806b0(menu, item);
            func_02080b2c(menu, item);
        }
        item++;
    }
    func_02080c68(menu, 9, 0);
    func_02081ea4(menu, 9, 0);
    func_02081130(menu, 9, (flags_ & ALCHEMY_MENU_PAGES) ? 1 : 0);
    func_020813ec(menu, 9);
}

void AlchemyMenu::DrawTimes()
{
    func_02080fa8(menu_, 0x3d, count_);
    func_020813ec(menu_, 0xa);
    group_ = 0xa;
}

// NONMATCHING: the C matches 96.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::DrawBookTitle(int total)
{
    Menu* menu = menu_;
    func_02080b54(menu, 0xd);
    func_02080b40(menu, 0x56);
    func_0208103c(menu_, 0x56, 0x2b);
    unsigned char state = state_;
    if (state != AlchemyMenuState_RecipeList && state != AlchemyMenuState_BookList)
    {
        short text = 0x2c;
        if (!total)
        {
            switch (bookCursor_)
            {
            case 0x26:
                text = 0x13;
                break;
            case 0x25:
                text = 0x12;
                break;
            }
        }
        func_0208103c(menu, 0x57, text);
        func_02080b40(menu, 0x57);
        func_020806d8(menu, 0xd, 0x57, 1, 4);
        if (total)
        {
            unsigned short count = ingredients_.CountRecipes();
            int percent = (count / 448.0f) * 10000.0f;
            int rate = (percent - percent % 100) / 100;
            if (count != 0 && rate <= 0)
                rate = 1;
            if (rate > 100)
                rate = 100;
            func_02080fa8(menu, 0x58, rate);
            func_02080b40(menu, 0x58);
            func_0208103c(menu_, 0x56, 0x2e);
        }
    }
    func_02081164(menu, 0xd, 1);
    func_020813ec(menu, 0xd);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN18AlchemyIngredients12CountRecipesEv(); // AlchemyIngredients::CountRecipes
}

asm void AlchemyMenu::DrawBookTitle(int total)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r5, r0
    ldr r4, [r5, #0x14]
    mov r6, r1
    mov r0, r4
    mov r1, #0xd
    bl func_02080b54
    mov r0, r4
    mov r1, #0x56
    bl func_02080b40
    ldr r0, [r5, #0x14]
    mov r1, #0x56
    mov r2, #0x2b
    bl func_0208103c
    ldrb r0, [r5, #0x38f]
    cmp r0, #0xa
    cmpne r0, #0x3
    beq @L0215fb54
    cmp r6, #0x0
    mov r2, #0x2c
    bne @L0215fa90
    add r0, r5, #0x300
    ldrsh r0, [r0, #0x66]
    cmp r0, #0x25
    beq @L0215fa8c
    cmp r0, #0x26
    moveq r2, #0x13
    b @L0215fa90
@L0215fa8c:
    mov r2, #0x12
@L0215fa90:
    mov r0, r4
    mov r1, #0x57
    bl func_0208103c
    mov r0, r4
    mov r1, #0x57
    bl func_02080b40
    mov r2, #0x4
    mov r0, r4
    mov r1, #0xd
    str r2, [sp, #0x0]
    mov r2, #0x57
    mov r3, #0x1
    bl func_020806d8
    cmp r6, #0x0
    beq @L0215fb54
    add r0, r5, #0x74
    bl _ZN18AlchemyIngredients12CountRecipesEv
    mov r0, r0, lsl #0x10
    mov r7, r0, lsr #0x10
    mov r0, r7
    bl _ffltu
    ldr r1, =0x43e00000
    bl _fdiv
    ldr r1, =0x461c4000
    bl _fmul
    bl _ffix
    mov r6, r0
    mov r1, #0x64
    bl _s32_div_f
    sub r0, r6, r1
    mov r1, #0x64
    bl _s32_div_f
    cmp r7, #0x0
    mov r2, r0
    beq @L0215fb24
    cmp r2, #0x0
    movle r2, #0x1
@L0215fb24:
    cmp r2, #0x64
    movgt r2, #0x64
    mov r0, r4
    mov r1, #0x58
    bl func_02080fa8
    mov r0, r4
    mov r1, #0x58
    bl func_02080b40
    ldr r0, [r5, #0x14]
    mov r1, #0x56
    mov r2, #0x2e
    bl func_0208103c
@L0215fb54:
    mov r0, r4
    mov r1, #0xd
    mov r2, #0x1
    bl func_02081164
    mov r0, r4
    mov r1, #0xd
    bl func_020813ec
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

void AlchemyMenu::DrawFilter()
{
    Menu* menu = menu_;
    short text = 0x2f;
    switch (bookCursor_)
    {
    case 0x28:
        text = 0x15;
        break;
    case 0x27:
        text = 0x14;
        break;
    }
    switch (filterCursor_)
    {
    case 0x48:
        text = 0x1d;
        break;
    case 0x49:
        text = 0x1e;
        break;
    case 0x4a:
        text = 0x1f;
        break;
    case 0x4b:
        text = 0x20;
        break;
    case 0x4c:
        text = 0x21;
        break;
    case 0x4d:
        text = 0x22;
        break;
    case 0x4e:
        text = 0x23;
        break;
    case 0x4f:
        text = 0x24;
        break;
    case 0x50:
        text = 0x25;
        break;
    case 0x51:
        text = 0x26;
        break;
    case 0x52:
        text = 0x27;
        break;
    case 0x53:
        text = 0x28;
        break;
    case 0x40:
        text = 0x17;
        break;
    case 0x41:
        text = 0x18;
        break;
    case 0x42:
        text = 0x19;
        break;
    case 0x43:
        text = 0x1a;
        break;
    case 0x44:
        text = 0x1b;
        break;
    case 0x45:
        text = 0x1c;
        break;
    }
    func_0208103c(menu, 0x59, text);
    func_0208108c(menu, 0x59);
    func_02081164(menu, 0xe, 1);
    func_020813ec(menu, 0xe);
    func_02080c68(menu, 0xe, 2);
    func_02080c20(menu, 0xe);
}

void AlchemyMenu::DrawSort()
{
    Menu* menu = menu_;
    func_0208103c(menu, 0x5a, sort_ + 0x29);
    func_02080798(menu, 0x5a, 1);
    func_02081164(menu, 0xf, 1);
    func_020813ec(menu, 0xf);
    func_02080c68(menu, 0xf, 2);
    func_02080c20(menu, 0xf);
}

Recipe* AlchemyMenu::FindRecipe(short* items, unsigned char* counts, unsigned char* times)
{
    short ingredients[3] = {0};
    unsigned char amounts[3] = {0};
    for (unsigned char i = 0; i < 3; i++)
    {
        short item = items[i];
        if (item > 0)
        {
            for (unsigned char j = 0; j < 3; j++)
            {
                short ingredient = ingredients[j];
                if (item == ingredient)
                {
                    ingredients[j] = item;
                    amounts[j] += counts[i];
                    break;
                }
                if (ingredient <= 0)
                {
                    ingredients[j] = item;
                    amounts[j] = counts[i];
                    break;
                }
            }
        }
    }
    return func_02071da4(&table_, ingredients, amounts, times);
}

// NONMATCHING: the C matches 68.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void AlchemyMenu::LoadResultSprite(PotIngredient* result)
{
    if (result == 0)
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_02075cdc(&resultSprite_);
    resultSprite_.unk_3c = 5;
    resultSprite_.unk_5e = 1;
    resultSprite_.unk_14 = func_0203be4c(func_0203bd08()) + 0x1b8;
    resultSprite_.unk_38 = 0x10000;
    resultSprite_.unk_40 = 0;
    char path[0x40];
    sprintf(path, STRING(0xf4, "data/ani/d_%c%03d.spr"), result->entry_.letter_, func_020de234(result));
    resultTask_ = loader->QueueLoadFile(path, 0);
}
#else
asm void AlchemyMenu::LoadResultSprite(PotIngredient* result)
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x40
    movs r6, r1
    mov r5, r0
    beq @L0215fec0
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r4, r0
    add r0, r5, #0x3b8
    bl func_02075cdc
    mov r0, #0x5
    str r0, [r5, #0x3f4]
    mov r0, #0x1
    strb r0, [r5, #0x416]
    bl func_0203bd08
    bl func_0203be4c
    add r0, r0, #0x1b8
    str r0, [r5, #0x3cc]
    mov r0, #0x10000
    str r0, [r5, #0x3f0]
    mov r1, #0x0
    str r1, [r5, #0x3f8]
    mov r0, r6
    bl func_020de234
    ldr r1, [r6, #0x10]
    mov r3, r0
    mov r0, r1, lsl #0x4
    mov r2, r0, lsr #0x18
    ldr r1, =sStrings+0xf4
    add r0, sp, #0x0
    bl sprintf
    mov r0, r4
    add r1, sp, #0x0
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r5, #0x428]
@L0215fec0:
    add sp, sp, #0x40
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

// NONMATCHING: the C matches 82.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
unsigned char AlchemyMenu::UpdateResultSprite()
{
    SafeAllocator* allocators;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (!loader->GetTaskStatus(resultTask_))
        return 0;
    allocators = allocators_;
    allocators[9].Reset();
    void* data = 0;
    unsigned int size = 0;
    loader->GetLoadedFileByID(resultTask_, &data, &size);
    func_02076080(&resultSprite_, &allocators[9], data, size);
    loader->RemoveTask(resultTask_);
    resultTask_ = -1;
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
}

asm unsigned char AlchemyMenu::UpdateResultSprite()
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x8
    mov r6, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldr r1, [r6, #0x428]
    mov r5, r0
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    moveq r0, #0x0
    beq @L0215ff4c
    ldr r4, [r6, #0xc]
    add r0, r4, #0xb4
    bl _ZN13SafeAllocator5ResetEv
    mov r0, #0x0
    str r0, [sp, #0x4]
    str r0, [sp, #0x0]
    ldr r1, [r6, #0x428]
    add r2, sp, #0x4
    add r3, sp, #0x0
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r2, [sp, #0x4]
    ldr r3, [sp, #0x0]
    add r0, r6, #0x3b8
    add r1, r4, #0xb4
    bl func_02076080
    ldr r1, [r6, #0x428]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r6, #0x428]
    mov r0, #0x1
@L0215ff4c:
    add sp, sp, #0x8
    ldmia sp!, {r4, r5, r6, pc}
}
#endif
