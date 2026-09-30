// The window of the information on an item (see ItemInfoWindow.h): its sprite, its description, its stats, where
// it's found and which monsters drop it
#include "Scene/Overlay_23/ItemInfoWindow.h"
#include "Bestiary/MonsterInfoScreen.h"
#include "Scene/Overlay_23/MenuObjects.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/BGBases.h"
#include "System/Cache.h"
#include "System/LoadToVRAM.h"
#include "System/Timing.h"
#include <std_library_functions.h>

// The stats of a party member with an item (see func_020dd8b4)
struct MemberStats
{
    char unk_0[0x3e];
    unsigned short unk_3e;
    char unk_40[2];
    unsigned short unk_42;
    char unk_44[4];
    float unk_48;
    char unk_4c[4];
    float unk_50;
    char unk_54[4];
    float unk_58;
    char unk_5c[0xa];
    unsigned short unk_66;
    char unk_68[2];
    unsigned short unk_6a;
    char unk_6c[2];
    unsigned short unk_6e;
    char unk_70[2];
    unsigned short unk_72;
    char unk_74[2];
    unsigned short unk_76;
    char unk_78[2];
    unsigned short unk_7a;
};


struct Unknown_0203bd08;

extern "C"
{
    // The heap of the canvas buffer
    extern char data_02114e20[];
    // The GP2 archive of the items' information and its files
    extern const char* data_020f2a10;
    extern const char* data_020f2a14;
    extern const char* data_020f2a1c;
    extern const char* data_020f2a20;
    extern const char* data_020f2a28;
    extern const char* data_020f2b68;

    void __clear(void* buffer, unsigned long size);
    // The runtime's float functions, for the assembly of the NONMATCHING functions
    void _fadd();
    void _fdiv();
    void _feq();
    void _fflt();
    void _ffltu();
    void _ffix();
    void _fls();
    void _fneq();
    void _fsub();
    void _fmul();
    void _fgr();
    void _fgeq();
    void _fleq();
    long atol(const char* text);
    unsigned short func_020017b0(int value);
    double func_0200c578(float value);
    GameResources* func_0200fb8c(GameState* gameState);
    int func_0201079c(GameState* gameState);
    void* func_02012d88(void* heap, unsigned int size);
    void func_02012da4(void* heap, void* block);
    void* func_02012fe4();
    int func_0201bb78(void* flags, unsigned short id);
    Unknown_0203bd08* func_0203bd08();
    unsigned int func_0203be40(Unknown_0203bd08*);
    unsigned int func_0203be4c(Unknown_0203bd08*);
    int func_020420e8(const char* text, int);
    void* func_020421a0();
    void func_02046608(void* font, int, const char* input, char* output, int, int, int);
    void* func_020467f0(void* archive, int index, char** name, unsigned int* size);
    int func_02046900(void* archive);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b2e0(BackgroundGraphics* background, void* file);
    void func_0204b3a0(BackgroundGraphics* background, void* file);
    void func_0204b5b4(BackgroundGraphics* background, int priority);
    void func_0204b5e8(BackgroundGraphics* background, int x, int y);
    void func_0204c684(Canvas* canvas);
    void func_0204f41c(Canvas* canvas, short x, short y, const char* text, int font, int color, unsigned short* width,
                       unsigned short* height, int);
    void func_0205a198(Sprite* sprite);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void* func_0205ec34();
    void func_0206819c(const char* input, char* output, int);
    int func_0206dfb0(void* flags, void* flags2, int id);
    int func_0206e384();
    int func_0206e3d4(void* flags, int);
    void func_02074af4(void* state);
    void func_02074b64(void* state);
    void func_02074bd0(void* state);
    void func_02074bf4(void* state);
    void func_02075cdc(Unknown_02075cdc* graphics);
    void func_02075d58(Unknown_02075cdc* graphics);
    void func_02075d64(Unknown_02075cdc* graphics);
    void func_02075db0(Unknown_02075cdc* graphics, int x, int y);
    void func_02076080(Unknown_02075cdc* graphics, SafeAllocator* allocator, void* file, unsigned int size);
    void* func_02094a00();
    void func_02094ab0(void* music);
    void func_02094b30(void* music, int id, int);
    bool func_02094b4c(void* music);
    int func_020ac020(int, short* monsters, MonsterRecord* records, int count);
    void func_020ac2d4(int, short* ids, void* results, int count);
    void func_020dc2bc();
    void func_020dc2d0(int);
    int func_020dd19c(int member, unsigned char type);
    int func_020dd4c4(signed char member, PartEntry* item);
    int func_020dd718(signed char member, short id);
    void func_020dd7ac(MemberStats* stats);
    void func_020dd8b4(MemberStats* stats, signed char member, PartEntry* item, int);
    unsigned short func_020de194(PartEntry* item);
    int func_020de234(PartEntry* item, int);
    PartEntry* func_020dedd0(PartNameTable* names, short id);
    int func_020dee58(PartEntry* item);
    void func_020df828(ItemInfoTable* table);
    void func_020df83c(ItemInfoTable* table);
    void func_020df850(ItemInfoTable* table, SafeAllocator* allocator, void* file, unsigned int size, short item);
    void func_020dfc40(TextTable* texts);
    void func_020dfc6c(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    void func_020e0028(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size, short* ids, int count);
    const char* func_020e0434(TextTable* texts, short id);
    void func_020e046c(char* output, void* file, unsigned int size, short item);
    const char* func_020e51cc(int id);
}


#define REG_DISPCNT (*(volatile unsigned int*)0x04000000)
#define REG_DISPCNT_SUB (*(volatile unsigned int*)0x04001000)
#define REG_BG0CNT_SUB (*(volatile unsigned short*)0x04001008)
#define REG_BG1CNT_SUB (*(volatile unsigned short*)0x0400100a)
#define REG_BG2CNT_SUB (*(volatile unsigned short*)0x0400100c)
#define REG_BG3CNT_SUB (*(volatile unsigned short*)0x0400100e)
#define REG_BG0HOFS_SUB (*(volatile unsigned int*)0x04001010)
#define REG_BG1HOFS_SUB (*(volatile unsigned int*)0x04001014)

// The files of the backgrounds and of the layout in the archive of a background
static char sBncl[] = ".bncl";
static char sBncg[] = ".bncg";
static char sBnsc[] = ".bnsc";
static char sLia[] = ".lia";
static const char* sExtensions[] = {sBncg, sBncl, sBnsc, sLia};

// The states of ItemInfoWindow::Update() (see sStatesGuard) and the steps of ItemInfoWindow::UpdateLoad()
static void (ItemInfoWindow::*sStates[4])() = {&ItemInfoWindow::State_Open, &ItemInfoWindow::State_Update,
                                               &ItemInfoWindow::State_Close};
static int (ItemInfoWindow::*sSteps[])() = {
    &ItemInfoWindow::Load_Background,   &ItemInfoWindow::Load_BackgroundWait,
    &ItemInfoWindow::Load_Sprite,       &ItemInfoWindow::Load_SpriteWait,
    &ItemInfoWindow::Load_Layout,       &ItemInfoWindow::Load_LayoutWait,
    &ItemInfoWindow::Load_Description,  &ItemInfoWindow::Load_DescriptionWait,
    &ItemInfoWindow::Load_Places,       &ItemInfoWindow::Load_PlacesWait,
    &ItemInfoWindow::Load_FieldNames,   &ItemInfoWindow::Load_FieldNamesWait,
    &ItemInfoWindow::Load_Drops,        &ItemInfoWindow::Load_DropsWait,
    &ItemInfoWindow::Load_MonsterNames, &ItemInfoWindow::Load_MonsterNamesWait,
};

// The file's strings: in the original the compiler pools them after the other data, which the assembly of the
// NONMATCHING functions can't reference, so they're one array here (see src/Scene/Overlay_20/StartupScene.cpp)
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] __attribute__((aligned(4))) =
    "%.1f\0<x>\0%2d\0%3d\0(\0%d\0)\0data/ani/oiij.gp2\0oiij_<LG>.pac\0data/ani/oiir.gp2\0oiir_<LG>.pac\0"
    "data/bin/menu/str_ii.gp2\0str_ii_<LG>.nat\0data/ani/bg_iidc.pac\0data/ani/bg_iilist.pac\0"
    "data/ani/bglii2%d.gp2\0bglii2%d_<LG>.pac\0data/ani/bgii2%d.gp2\0bgii2%d_<LG>.pac\0"
    "data/ani/al_qu.spr\0data/ani/d_%c%03d.spr\0data/ani/lay_iie.lia\0data/ani/lay_iiu.lia";
#define STRING(offset, text) (sStrings + (offset))
#endif

// Cancels the loading of the files
#define CANCEL_TASKS()                  \
    {                                   \
        CancelTask(&task_);             \
        for (int i = 0; i < 7; i++)     \
            CancelTask(&tasks_[i]);     \
    }

static unsigned int ParseItemId(const char* text);
static unsigned int SetUpCanvas(Canvas* canvas, short x, short y, short width, short height);
static unsigned int LoadCanvas(Canvas* canvas, unsigned int offset, unsigned short palette, int bg1);

// The layers that the main screen shows (GX_GetVisiblePlane() and GX_SetVisiblePlane() of the SDK)
static inline unsigned int GetVisiblePlanes()
{
    return (REG_DISPCNT & 0x1f00) >> 8;
}

static inline void SetVisiblePlanes(unsigned int planes)
{
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (planes << 8);
}

static inline int IsEquipment(const PartEntry* item)
{
    return item->category_ <= 7 ? 1 : 0;
}

#define SHOW_ELEMENT(layout, id)                            \
    {                                                       \
        LayoutElement* element = (layout)->FindElement(id); \
        if (element != NULL)                                \
            element->flags_ |= LAYOUT_ELEMENT_FLAG_VISIBLE; \
    }

#define HIDE_ELEMENT(layout, id)                             \
    {                                                        \
        LayoutElement* element = (layout)->FindElement(id);  \
        if (element != NULL)                                 \
            element->flags_ &= ~LAYOUT_ELEMENT_FLAG_VISIBLE; \
    }

void ItemSparkles::Initialize(int enabled)
{
    enabled_ = enabled;
    counter_ = 0;
    delay_ = 0;
    memset(sparkles_, 0, sizeof(sparkles_));
    sparkles_[0].duration_ = 0xf;
    sparkles_[1].duration_ = 0xf;
    sparkles_[2].duration_ = 0x17;
    GetCurrentTimestamp();
}

// Defined after the first function, so that the compiler keeps them in this order, the original's
static const unsigned char sUnused[0x23] = {0xa, 0xf, 6, 0xf, 0xf, 8, 0xa, 8, 0xc, 0xf, 0xf, 8, 0xa, 9, 9, 0xb, 0xa, 0xf,
                                            0xf, 8, 8, 0xa, 3, 8, 0xa, 0xf, 5, 0xa, 0xa, 2, 0xf, 0xa, 0xf, 0xf, 8};
// The layouts of the kinds of item: the equipment's and the others'
static const unsigned char sBackgroundKinds[2] = {2, 1};
// The sprites of the equipment that the vocations can't use, by unk_4_27 and unk_4_28 of the item's model
static const unsigned char sForbiddenSprites[2][2] = {{0, 0x17}, {0x16, 0}};
static const int sUnused2[15] = {3, 2, 4, 1, 0x800, 0x800, 0x1800, 4, 3, 0x800, 0x800, 4, 0xc, 0x800, 0x90};
// The elements of the names of the monsters that drop the item
static const short sMonsterNameIds[2] = {0xb, 0xc};
static const int sUnused3[3] = {2, 4, 4};
// The elements of the places where the item is found
static const short sPlaceIds[3] = {7, 8, 9};
// The IDs of the elements of the stats (see ItemInfoWindow::DrawStats()): the names, the labels, the signs and the
// values of the item's stats, of the party member's, and of the party member's with the item
static const short sStatNames[4] = {0xf, 0x10, 0x11, 0x12};
static const short sStatLabels[4] = {0xa, 0xc, 0xd, 0xe};
static const short sStatSigns[4] = {0x17, 0x18, 0x19, 0x1a};
static const short sStatValues[4] = {0x13, 0x14, 0x15, 0x16};
static const short sStatNames2[4] = {0xf, 0x10, 0x11, 0x12};
static const short sStatLabels2[4] = {0xa, 0xc, 0xd, 0xe};
static const short sStatSigns2[4] = {0x17, 0x18, 0x19, 0x1a};
static const short sStatValues2[4] = {0x13, 0x14, 0x15, 0x16};
static const short sStatNames3[4] = {0x2f, 0x30, 0x31, 0x32};
static const short sStatLabels3[4] = {0xa, 0xc, 0xd, 0xe};
static const short sStatValues3[4] = {0x33, 0x34, 0x35, 0x36};
static const short sStatArrows3[4] = {0x3b, 0x3c, 0x3d, 0x3e};
static const short sStatNewValues3[4] = {0x37, 0x38, 0x39, 0x3a};
// The vocations that the icons show, and the elements of the icons
static const unsigned char sVocations[13] = {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
static const short sVocationIcons[12] = {0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x25, 0x24, 0x27, 0x28, 0x26};
static const short sVocationElements[12] = {0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x25, 0x24, 0x27, 0x28, 0x26};
static const int sUnused4[2] = {9, 0x20};

static ItemInfoTable* sDrops;
// The canvas buffer (0x1800 bytes)
static void* sBuffer;
static TextTable* sFieldNames;
// The palettes of the canvases
static int sPalette;
static int sPalette2;
// The texts of the window
static TextTable* sTexts;
static int sPalette3;
// The guard of sStates: in the original, sStates is a static variable of ItemInfoWindow::Update() with this guard,
// which the compiler places after the variables before it and before the next ones, so it's written by hand here
static int sStatesGuard;
static ItemInfoWindow* sWindow;
static ItemInfoTable* sPlaces;
static TextTable* sMonsterNames;
static ItemSparkles sSparkles;

void ItemSparkles::Update()
{
    if (!enabled_)
        return;
    unsigned long long time = (GetCurrentTimestamp() << 6) / 0x82ea;
    int i = 0;
    if (time - time_ > 30)
    {
        time_ = time;
    }
    else
        return;
    for (; i < 3; i++)
    {
        sparkles_[i].timer_--;
        if (sparkles_[i].timer_ <= 0)
            sparkles_[i].timer_ = 0;
    }
    delay_--;
    if (delay_ <= 0)
    {
        delay_ = 0;
        for (int k = 0; k < 3; k++)
        {
            ItemSparkle* sparkle = &sparkles_[k];
            if (sparkles_[k].timer_ > 0 || rand() % 5 != 0)
                continue;
            sparkle->timer_ = sparkle->duration_;
            sparkle->x_ = rand() % 50;
            sparkle->y_ = rand() % 15;
            for (int j = 0; j < 3; j++)
            {
                if (k != j && sparkles_[j].timer_ > 0 && abs(sparkle->x_ - sparkles_[j].x_) <= 12 &&
                    abs(sparkle->y_ - sparkles_[j].y_) <= 12)
                {
                    sparkle->timer_ = 0;
                    break;
                }
            }
            delay_ = 2;
            break;
        }
    }
    counter_++;
    if (counter_ >= 40)
        counter_ = 0;
}

// The screen base of the background that the canvases are drawn on
static unsigned short* GetScreenBase(signed char screen, int bg1)
{
    if (screen == 1)
        return (unsigned short*)GetSubBG0ScreenBase();
    if (bg1)
        return (unsigned short*)GetMainBG1ScreenBase();
    return (unsigned short*)GetMainBG2ScreenBase();
}

void ItemInfoWindow::CancelTask(int* task)
{
    if (task == NULL)
        return;
    if (*task < 0)
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    loader->RemoveTask(*task);
    *task = -1;
}

// The IDs of the fields and of the items where an item is found (see ParseItemId())
// NONMATCHING: the C matches 79.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler swaps the registers of the loop's index and of the number of IDs
#ifdef NONMATCHING
static void GetPlaceIds(ItemInfoTable* table, short* ids, short* count)
{
    ItemInfoList* list = table->list_;
    ItemInfoEntry* entry = list->entries_;
    int i = 0;
    short n = 0;
    short entries = list->count_;
    for (; i < entries; i++, entry++)
    {
        const char* text;
        if (entry->enabled_ && (text = entry->text_) != NULL)
        {
            char c = text[0];
            if (c == 'f')
            {
                ids[n++] = atol(text + 5);
            }
            else if (c >= 'A' && c <= 'Z')
            {
                unsigned short id = ParseItemId(text);
                if (id != 0)
                    ids[n++] = id;
            }
        }
    }
    *count = n;
}
#else
static asm void GetPlaceIds(ItemInfoTable* table, short* ids, short* count)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    ldr r0, [r0, #0x8]
    mov r5, #0x0
    mov r9, r1
    mov r8, r2
    mov r7, r5
    ldr r4, [r0, #0x4]
    ldrsh r6, [r0, #0x2]
    b @L021db3b0
@L021db338:
    ldrb r0, [r4, #0x1]
    cmp r0, #0x0
    ldrne r0, [r4, #0x4]
    cmpne r0, #0x0
    beq @L021db3a8
    ldrsb r1, [r0, #0x0]
    cmp r1, #0x66
    bne @L021db378
    add r0, r0, #0x5
    bl atol
    add r1, r5, #0x1
    mov r2, r5, lsl #0x1
    mov r1, r1, lsl #0x10
    strh r0, [r9, r2]
    mov r5, r1, asr #0x10
    b @L021db3a8
@L021db378:
    cmp r1, #0x41
    blt @L021db3a8
    cmp r1, #0x5a
    bgt @L021db3a8
    bl ParseItemId
    mov r0, r0, lsl #0x10
    movs r2, r0, lsr #0x10
    addne r0, r5, #0x1
    movne r1, r5, lsl #0x1
    movne r0, r0, lsl #0x10
    strneh r2, [r9, r1]
    movne r5, r0, asr #0x10
@L021db3a8:
    add r7, r7, #0x1
    add r4, r4, #0x8
@L021db3b0:
    cmp r7, r6
    blt @L021db338
    strh r5, [r8, #0x0]
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

// The original doesn't inline it
#pragma dont_inline on
// Draws a number with a decimal, aligned to the right of x
static void DrawDecimal(Canvas* canvas, short x, short y, float value, unsigned char color)
{
    char text[0x40] = {0};
    sprintf(text, STRING(0x0, "%.1f"), func_0200c578(value));
    unsigned short width;
    unsigned short height;
    func_0204f41c(canvas, x - func_020420e8(text, 0), y, text, 8, color, &width, &height, 0);
}
#pragma dont_inline reset

// Moves an element to the canvas' position, to draw it on the canvas, and returns its position
static void TakeElement(Layout* layout, Canvas* canvas, short id, short* x, short* y)
{
    LayoutElement* element = layout->FindElement(id);
    if (element == NULL)
        return;
    short elementX = 0;
    short elementY = 0;
    layout->AddPosition(id, &elementX, &elementY);
    short left = elementX >> 3;
    short top = elementY >> 3;
    canvas->x_ = left;
    canvas->y_ = top;
    *x = element->x_;
    *y = element->y_;
    element->x_ = 0;
    element->y_ = 0;
}

LayoutElement* Layout::FindElement(short id)
{
    LayoutElement* elements = elements_;
    if (elements == NULL)
        return NULL;
    unsigned short count = numElements_;
    if (count == 0)
        return NULL;
    for (unsigned short i = 0; i < count; i++)
    {
        LayoutElement* element = &elements[i];
        if (element->id_ == id)
            return element;
    }
    return NULL;
}

void Layout::SetElementPosition(short id, short x, short y)
{
    LayoutElement* element = FindElement(id);
    if (element != NULL)
    {
        element->x_ = x;
        element->y_ = y;
    }
}

// The ID of an item (a letter for the kind and two digits), or 0
static unsigned int ParseItemId(const char* text)
{
    unsigned int id = 0;
    char buffer[5] = {0};
    strncpy(buffer, text, 4);
    buffer[3] = 0;
    unsigned short number = (short)atol(buffer + 1) * 100;
    char kind = buffer[0];
    if (kind == 'C')
        id = number;
    else if (kind == 'M')
        id = number + 1000;
    else if (kind == 'X')
        id = number + 4000;
    else if (kind == 'D')
        id = number + 7000;
    else if (kind == 'T')
        id = number + 9000;
    else if (kind == 'S')
        id = number + 5000;
    else if (kind == 'H')
    {
        id = number + 15000;
        if (id == 15800)
            id = 20056;
    }
    return id;
}

// Draws where the item is found
// NONMATCHING: the C matches 83.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler assigns the registers of the loop's variables in another order
#ifdef NONMATCHING
static void DrawPlaces(Layout* layout, Canvas* canvas)
{
    const char* found = func_020e0434(sTexts, 0x1f);
    const char* none = func_020e0434(sTexts, 0x1e);
    const char* trade = func_020e0434(sTexts, 0x2a);
    const char* alchemy = func_020e51cc(0x56);
    SHOW_ELEMENT(layout, 0xf);
    SHOW_ELEMENT(layout, 0xa);
    layout->SetText(7, found, 10, 15);
    layout->SetText(8, found, 10, 15);
    layout->SetText(9, found, 10, 15);
    layout->SetText(0xa, none, 10, 15);
    ItemPlace places[4];
    memset(places, 0, sizeof(places));
    unsigned char count = 0;
    ItemInfoList* list = sPlaces->list_;
    if (list != NULL)
    {
        int i = 0;
        ItemInfoEntry* entry = list->entries_;
        short entries = list->count_;
        for (; i < entries; i++, entry++)
        {
            ItemPlace place;
            place.text_ = NULL;
            place.kind_ = 0;
            const char* text;
            if (!entry->enabled_ || (text = entry->text_) == NULL)
                continue;
            char c = text[0];
            if (c == 'f')
            {
                if (strlen(text) >= 5)
                {
                    char number[4] = {0};
                    memcpy(number, entry->text_ + 2, 2);
                    short field = atol(number);
                    if (!func_0201bb78(func_02012fe4(), field + 20000))
                        continue;
                    text = func_020e0434(sFieldNames, atol(entry->text_ + 5));
                    place.kind_ = 2;
                }
            }
            else if (c == 'a')
            {
                short recipe = atol(text + 1);
                void* flags = func_0205ec34();
                if (!func_0206dfb0(flags, (char*)flags + 0x8c, 0x1198))
                    continue;
                struct
                {
                    short id_;
                    unsigned short known_ : 1;
                } result;
                memset(&result, 0, sizeof(result));
                func_020ac2d4(0, &recipe, &result, 1);
                if (result.id_ == 0 || !result.known_)
                    continue;
                place.kind_ = 1;
                text = alchemy;
            }
            else if (c == 'b')
            {
                void* flags = func_0205ec34();
                int bits = func_0206e384();
                if (!((1 << (func_0206e3d4(flags, 0x17) - 1)) & (bits << 0x10)))
                    continue;
                place.kind_ = 3;
                text = trade;
            }
            else if (c >= 'A' && c <= 'Z')
            {
                void* flags = func_02012fe4();
                unsigned short id = ParseItemId(entry->text_);
                if (id == 0)
                    continue;
                if (!func_0201bb78(flags, id))
                    continue;
                text = func_020e0434(sFieldNames, id);
                place.kind_ = 4;
            }
            if (text == NULL)
                continue;
            place.text_ = text;
            places[count] = place;
            count++;
            if (count == 4)
                break;
        }
    }
    if (func_0201079c(GameState::GetInstance()) == 1)
        count = 0;
    unsigned char shown = count;
    if (count == 4)
        shown = 3;
    int last = shown - 1;
    for (int i = 0; i < last; i++)
    {
        for (int j = 0; j < last - i; j++)
        {
            if (places[j].kind_ < places[j + 1].kind_)
            {
                ItemPlace place = places[j];
                places[j] = places[j + 1];
                places[j + 1] = place;
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (i == count)
            break;
        layout->SetText(sPlaceIds[i], places[i].text_, 10, 15);
    }
    if (count != 4)
        HIDE_ELEMENT(layout, 0xa);
    short x;
    short y;
    TakeElement(layout, canvas, 0xf, &x, &y);
    if (sBuffer != NULL)
    {
        layout->SetCanvas(canvas);
        layout->Draw();
    }
    layout->SetElementPosition(0xf, x, y);
    HIDE_ELEMENT(layout, 0xf);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN6Layout11FindElementEs(); // Layout::FindElement
    void _ZN6Layout18SetElementPositionEsss(); // Layout::SetElementPosition
    void _ZN6Layout4DrawEv(); // Layout::Draw
    void _ZN6Layout7SetTextEsPKchh(); // Layout::SetText
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9ItemPlaceaSERKS_(); // ItemPlace::operator=
}

static asm void DrawPlaces(Layout* layout, Canvas* canvas)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x4c
    ldr r2, =sDrops
    mov r10, r0
    ldr r0, [r2, #0x14]
    mov r9, r1
    mov r1, #0x1f
    bl func_020e0434
    ldr r1, =sDrops
    mov r4, r0
    ldr r0, [r1, #0x14]
    mov r1, #0x1e
    bl func_020e0434
    ldr r1, =sDrops
    mov r5, r0
    ldr r0, [r1, #0x14]
    mov r1, #0x2a
    bl func_020e0434
    str r0, [sp, #0x8]
    mov r0, #0x56
    bl func_020e51cc
    str r0, [sp, #0x4]
    mov r0, r10
    mov r1, #0xf
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r10
    mov r1, #0xa
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    mov r6, #0xf
    mov r2, r4
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r10
    mov r1, #0x7
    mov r3, #0xa
    str r6, [sp, #0x0]
    bl _ZN6Layout7SetTextEsPKchh
    mov r3, r6
    str r3, [sp, #0x0]
    mov r0, r10
    mov r2, r4
    mov r1, #0x8
    mov r3, #0xa
    bl _ZN6Layout7SetTextEsPKchh
    mov r0, r6
    str r0, [sp, #0x0]
    mov r2, r4
    mov r0, r10
    mov r1, #0x9
    mov r3, #0xa
    bl _ZN6Layout7SetTextEsPKchh
    mov r0, r6
    mov r1, #0xa
    str r0, [sp, #0x0]
    mov r2, r5
    mov r0, r10
    mov r3, r1
    bl _ZN6Layout7SetTextEsPKchh
    add r0, sp, #0x2c
    mov r1, #0x0
    mov r2, #0x20
    bl memset
    ldr r0, =sDrops
    mov r8, #0x0
    ldr r0, [r0, #0x24]
    ldr r0, [r0, #0x8]
    cmp r0, #0x0
    beq @L021db98c
    mov r7, r8
    ldr r5, [r0, #0x4]
    ldrsh r6, [r0, #0x2]
    b @L021db984
@L021db76c:
    mov r0, #0x0
    str r0, [sp, #0x24]
    strb r0, [sp, #0x28]
    ldrb r0, [r5, #0x1]
    cmp r0, #0x0
    beq @L021db97c
    ldr r4, [r5, #0x4]
    cmp r4, #0x0
    beq @L021db950
    ldrsb r0, [r4, #0x0]
    cmp r0, #0x66
    bne @L021db82c
    mov r0, r4
    bl strlen
    cmp r0, #0x5
    blo @L021db950
    add r0, sp, #0x20
    mov r1, #0x4
    bl __clear
    ldr r1, [r5, #0x4]
    add r0, sp, #0x20
    mov r2, #0x2
    add r1, r1, #0x2
    bl memcpy
    add r0, sp, #0x20
    bl atol
    mov r0, r0, lsl #0x10
    mov r4, r0, asr #0x10
    bl func_02012fe4
    add r1, r4, #0xe20
    add r1, r1, #0x4000
    mov r1, r1, lsl #0x10
    mov r1, r1, lsr #0x10
    bl func_0201bb78
    cmp r0, #0x0
    beq @L021db97c
    ldr r0, [r5, #0x4]
    add r0, r0, #0x5
    bl atol
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    ldr r0, =sDrops
    ldr r0, [r0, #0x8]
    bl func_020e0434
    mov r4, r0
    mov r0, #0x2
    strb r0, [sp, #0x28]
    b @L021db950
@L021db82c:
    cmp r0, #0x61
    bne @L021db8a8
    add r0, r4, #0x1
    bl atol
    strh r0, [sp, #0x10]
    bl func_0205ec34
    ldr r2, =0x1198
    add r1, r0, #0x8c
    bl func_0206dfb0
    cmp r0, #0x0
    beq @L021db97c
    add r0, sp, #0x1c
    mov r1, #0x0
    mov r2, #0x4
    bl memset
    mov r0, #0x0
    add r1, sp, #0x10
    add r2, sp, #0x1c
    mov r3, #0x1
    bl func_020ac2d4
    ldrsh r0, [sp, #0x1c]
    cmp r0, #0x0
    beq @L021db97c
    ldrh r0, [sp, #0x1e]
    mov r0, r0, lsl #0x1f
    movs r0, r0, lsr #0x1f
    beq @L021db97c
    mov r0, #0x1
    strb r0, [sp, #0x28]
    ldr r4, [sp, #0x4]
    b @L021db950
@L021db8a8:
    cmp r0, #0x62
    bne @L021db8f0
    bl func_0205ec34
    mov r11, r0
    bl func_0206e384
    mov r4, r0
    mov r0, r11
    mov r1, #0x17
    bl func_0206e3d4
    sub r1, r0, #0x1
    mov r0, #0x1
    mov r0, r0, lsl r1
    tst r0, r4, lsl #0x10
    beq @L021db97c
    mov r0, #0x3
    strb r0, [sp, #0x28]
    ldr r4, [sp, #0x8]
    b @L021db950
@L021db8f0:
    cmp r0, #0x41
    blt @L021db950
    cmp r0, #0x5a
    bgt @L021db950
    bl func_02012fe4
    mov r11, r0
    ldr r0, [r5, #0x4]
    bl ParseItemId
    mov r0, r0, lsl #0x10
    movs r4, r0, lsr #0x10
    beq @L021db97c
    mov r0, r11
    mov r1, r4
    bl func_0201bb78
    cmp r0, #0x0
    beq @L021db97c
    mov r0, r4, lsl #0x10
    mov r1, r0, asr #0x10
    ldr r0, =sDrops
    ldr r0, [r0, #0x8]
    bl func_020e0434
    mov r4, r0
    mov r0, #0x4
    strb r0, [sp, #0x28]
@L021db950:
    cmp r4, #0x0
    beq @L021db97c
    add r0, sp, #0x2c
    add r0, r0, r8, lsl #0x3
    add r1, sp, #0x24
    str r4, [sp, #0x24]
    bl _ZN9ItemPlaceaSERKS_
    add r0, r8, #0x1
    and r8, r0, #0xff
    cmp r8, #0x4
    beq @L021db98c
@L021db97c:
    add r7, r7, #0x1
    add r5, r5, #0x8
@L021db984:
    cmp r7, r6
    blt @L021db76c
@L021db98c:
    bl _ZN9GameState11GetInstanceEv
    bl func_0201079c
    cmp r0, #0x1
    moveq r8, #0x0
    mov r0, r8
    cmp r8, #0x4
    moveq r0, #0x3
    mov r6, #0x0
    sub r4, r0, #0x1
    b @L021dba28
@L021db9b4:
    mov r7, #0x0
    sub r11, r4, r6
    b @L021dba1c
@L021db9c0:
    add r1, r7, #0x1
    add r0, sp, #0x30
    ldrb r2, [r0, r7, lsl #0x3]
    ldrb r0, [r0, r1, lsl #0x3]
    mov r5, r1, lsl #0x3
    mov r1, r7, lsl #0x3
    cmp r2, r0
    bhs @L021dba18
    add r0, sp, #0x2c
    add r2, sp, #0x2c
    ldr r2, [r2, r1]
    add r0, r0, r1
    ldr r1, [r0, #0x4]
    str r2, [sp, #0x14]
    str r1, [sp, #0x18]
    add r1, sp, #0x2c
    add r1, r1, r5
    bl _ZN9ItemPlaceaSERKS_
    add r0, sp, #0x2c
    add r0, r0, r5
    add r1, sp, #0x14
    bl _ZN9ItemPlaceaSERKS_
@L021dba18:
    add r7, r7, #0x1
@L021dba1c:
    cmp r7, r11
    blt @L021db9c0
    add r6, r6, #0x1
@L021dba28:
    cmp r6, r4
    blt @L021db9b4
    mov r7, #0x0
    mov r6, #0xf
    ldr r5, =sPlaceIds
    add r4, sp, #0x2c
    mov r11, #0xa
    b @L021dba70
@L021dba48:
    cmp r7, r8
    beq @L021dba78
    mov r0, r7, lsl #0x1
    str r6, [sp, #0x0]
    ldrsh r1, [r5, r0]
    ldr r2, [r4, r7, lsl #0x3]
    mov r0, r10
    mov r3, r11
    bl _ZN6Layout7SetTextEsPKchh
    add r7, r7, #0x1
@L021dba70:
    cmp r7, #0x3
    blt @L021dba48
@L021dba78:
    cmp r8, #0x4
    beq @L021dba9c
    mov r0, r10
    mov r1, #0xa
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L021dba9c:
    add r4, sp, #0xc
    add r3, sp, #0xe
    mov r0, r10
    mov r1, r9
    mov r2, #0xf
    str r4, [sp, #0x0]
    bl TakeElement
    ldr r0, =sDrops
    ldr r0, [r0, #0x4]
    cmp r0, #0x0
    beq @L021dbadc
    mov r0, r10
    str r9, [r10, #0x4]
    mov r1, #0x1
    strh r1, [r10, #0x12]
    bl _ZN6Layout4DrawEv
@L021dbadc:
    ldrsh r2, [sp, #0xe]
    ldrsh r3, [sp, #0xc]
    mov r0, r10
    mov r1, #0xf
    bl _ZN6Layout18SetElementPositionEsss
    mov r0, r10
    mov r1, #0xf
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add sp, sp, #0x4c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

ItemPlace& ItemPlace::operator=(const ItemPlace& other)
{
    text_ = other.text_;
    kind_ = other.kind_;
    return *this;
}

// The stats of an item
// The stats that the window shows (12 of them, 5 in tenths)
static void GetItemStats(PartEntry* item, float* stats)
{
    if (item == NULL || stats == NULL)
        return;
    PartModelInfo* info = item->model_;
    if (info == NULL)
        return;
    stats[0] = info->unk_8_0;
    stats[1] = info->unk_8_10;
    stats[2] = info->unk_8_20 / 10.0f;
    stats[3] = info->unk_c_0 / 10.0f;
    stats[4] = info->unk_c_10 / 10.0f;
    stats[5] = 0;
    stats[6] = info->unk_10_0;
    stats[7] = info->unk_10_10;
    stats[8] = info->unk_10_20;
    stats[9] = info->unk_14_0;
    stats[10] = info->unk_14_10;
    stats[11] = info->unk_14_20;
}

// The stats of a party member with an item, or with its equipment
static void GetMemberStats(signed char member, float* stats, PartEntry* item)
{
    MemberStats memberStats;
    func_020dd7ac(&memberStats);
    func_020dd8b4(&memberStats, member, item, 1);
    stats[0] = memberStats.unk_3e;
    stats[1] = memberStats.unk_42;
    stats[2] = memberStats.unk_48;
    stats[3] = memberStats.unk_50;
    stats[4] = memberStats.unk_58;
    stats[5] = 0;
    stats[6] = memberStats.unk_66;
    stats[7] = memberStats.unk_6a;
    stats[8] = memberStats.unk_6e;
    stats[9] = memberStats.unk_72;
    stats[10] = memberStats.unk_76;
    stats[11] = memberStats.unk_7a;
}

// Hides the elements of the layout that the kind of item doesn't have
static void SetUpLayout(Layout* layout, PartEntry* item)
{
    if (layout == NULL || item == NULL)
        return;
    if (IsEquipment(item))
    {
        HIDE_ELEMENT(layout, 9);
        HIDE_ELEMENT(layout, 0x1c);
        HIDE_ELEMENT(layout, 0x1b);
        HIDE_ELEMENT(layout, 0xb);
        HIDE_ELEMENT(layout, 0x2a);
        HIDE_ELEMENT(layout, 0x2c);
        return;
    }
    HIDE_ELEMENT(layout, 0x14);
    HIDE_ELEMENT(layout, 0x13);
    HIDE_ELEMENT(layout, 0x10);
    HIDE_ELEMENT(layout, 0x12);
    HIDE_ELEMENT(layout, 0xf);
    HIDE_ELEMENT(layout, 0xe);
    layout->SetText(0x19, func_020e0434(sTexts, 0x24), 10, 15);
    layout->SetText(0x17, func_020e0434(sTexts, 0x23), 8, 15);
    layout->SetText(0x1a, func_020e0434(sTexts, 0x25), 10, 15);
    layout->SetText(0x18, func_020e0434(sTexts, 0x23), 8, 15);
    layout->SetText(0x15, func_020e0434(sTexts, 0x26), 10, 15);
    layout->SetText(0x16, func_020e0434(sTexts, 0x27), 10, 15);
}

void ItemInfoWindow::SetBuffer(void* buffer)
{
    if (buffer == NULL)
        return;
    sBuffer = buffer;
    externalBuffer_ = 1;
}

void ItemInfoWindow::CreateAllocators(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;
    allocator_.CreateTypeA(allocator->Allocate(0xd33), 0xd33);
    textAllocator_.CreateTypeA(allocator->Allocate(0x4cc), 0x4cc);
    infoAllocator_.CreateTypeA(allocator->Allocate(0x400), 0x400);
    sprite_ = (Unknown_02075cdc*)allocator->Allocate(0x70);
    nextSprite_ = (Unknown_02075cdc*)allocator->Allocate(0x70);
    spriteAllocator_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator));
    nextSpriteAllocator_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator));
    windowSpriteAllocator_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator));
    windowSpriteAllocator_->CreateTypeA(allocator->Allocate(0x180), 0x180);
    func_02075cdc(sprite_);
    func_02075cdc(nextSprite_);
    sprite_->unk_5e = screen_;
    sprite_->unk_3c = 0;
    nextSprite_->unk_5e = screen_;
    nextSprite_->unk_38 = 0x120;
    nextSprite_->unk_3c = 1;
    spriteAllocator_->CreateTypeA(allocator->Allocate(0x280), 0x280);
    nextSpriteAllocator_->CreateTypeA(allocator->Allocate(0x280), 0x280);
}

void ItemInfoWindow::Initialize(short item, signed char mode)
{
    sBuffer = NULL;
    allocator_.ResetAllocatorPointer();
    textAllocator_.ResetAllocatorPointer();
    infoAllocator_.ResetAllocatorPointer();
    spriteAllocator_ = NULL;
    nextSpriteAllocator_ = NULL;
    windowSpriteAllocator_ = NULL;
    names_ = NULL;
    item_ = NULL;
    nextItem_ = NULL;
    func_020dfc40(&texts_);
    func_020df828(&places_);
    func_020df828(&drops_);
    func_020dfc40(&fieldNames_);
    func_020dfc40(&monsterNames_);
    sprite_ = NULL;
    nextSprite_ = NULL;
    layout_.Initialize();
    unk_128 = 0;
    unk_129 = 0;
    func_0205a444(&renderer_);
    for (unsigned char i = 0; i < 30; i++)
        func_0205a198(&sprites_[i]);
    memset(description_, 0, sizeof(description_));
    layers_ = 0;
    task_ = -1;
    for (int i = 0; i < 7; i++)
        tasks_[i] = -1;
    unk_758 = 0;
    vramOffset_ = 0;
    itemId_ = item;
    nextItemId_ = item;
    flags_ = 0;
    state_ = 0;
    step_ = 0;
    background_ = 0;
    backgroundKind_ = -1;
    member_ = -1;
    equipmentLayout_ = -1;
    externalBuffer_ = 0;
    inMenu_ = 0;
    windowSprites_ = -1;
    nextWindowSprites_ = 1;
    windowSpriteTask_ = -1;
    ClearNames();
    namesOffset_ = 0;
    namesSize_ = 0;
    multiplier_ = 1;
    statsOffset_ = 0;
    statsSize_ = 0;
    sPalette3 = 5;
    sPalette = 9;
    sPalette2 = 0;
    mode_ = mode;
    screen_ = 1;
    if (mode == 1)
    {
        screen_ = 0;
        flags_ |= ITEM_INFO_WINDOW_NAMES;
    }
    numMonsters_ = 0;
    memset(monsters_, 0, sizeof(monsters_));
    sTexts = &texts_;
    sPlaces = &places_;
    sDrops = &drops_;
    sFieldNames = &fieldNames_;
    sMonsterNames = &monsterNames_;
    sWindow = this;
    flags_ |= ITEM_INFO_WINDOW_NO_SPRITE;
    sSparkles.Initialize(0);
}

void ItemInfoWindow::Finish()
{
    CancelTask(&windowSpriteTask_);
    nextWindowSprites_ = -1;
    if (!(flags_ & ITEM_INFO_WINDOW_KEEP_MUSIC))
        func_02094ab0(func_02094a00());
    CANCEL_TASKS();
    if (nextSprite_ != NULL)
        func_02075d58(nextSprite_);
    if (sprite_ != NULL)
        func_02075d58(sprite_);
    if (mode_ != 1)
        RestoreScreen();
    if (windowSpriteAllocator_ != NULL)
        windowSpriteAllocator_->Destroy();
    if (nextSpriteAllocator_ != NULL)
        nextSpriteAllocator_->Destroy();
    if (spriteAllocator_ != NULL)
        spriteAllocator_->Destroy();
    infoAllocator_.Destroy();
    textAllocator_.Destroy();
    allocator_.Destroy();
    if (sBuffer != NULL)
    {
        if (!externalBuffer_)
            func_02012da4(data_02114e20, sBuffer);
        sBuffer = NULL;
    }
    Initialize(-1, mode_);
}

int ItemInfoWindow::Update()
{
    sSparkles.Update();
    // The compiler's guard of a static table: see sStatesGuard
    if (!(sStatesGuard & 1))
    {
        sStates[3] = NULL;
        sStatesGuard |= 1;
    }
    if (sStates[state_] == NULL)
        return 1;
    (this->*sStates[state_])();
    return 0;
}

// NONMATCHING: the C matches 75.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler keeps the sparkles' address and the float constants in other registers
#ifdef NONMATCHING
void ItemInfoWindow::DrawSprites()
{
    if (mode_ == 1 && !(inMenu_ && (flags_ & ITEM_INFO_WINDOW_LAYOUT)))
        return;
    if (!(flags_ & ITEM_INFO_WINDOW_SPRITE) || item_ == NULL)
        return;
    unsigned int oam;
    if (screen_ == 0)
        oam = func_0203be40(func_0203bd08());
    else
        oam = func_0203be4c(func_0203bd08());
    if (sSparkles.enabled_)
    {
        for (int i = 0; i < 3; i++)
        {
            ItemSparkle* sparkle = &sSparkles.sparkles_[i];
            int frame = 0;
            if (i == 2)
            {
                float time = 0.0001f + (float)(20 - (sSparkles.sparkles_[i].timer_ - 3)) / 20.0f;
                if (time < 0.2f)
                    frame = 1;
                else if (time < 0.4f)
                    frame = 2;
                else if (time < 0.6f)
                    frame = 3;
                else if (time < 0.8f)
                    frame = 2;
                else if (time < 1.0f)
                    frame = 1;
            }
            else
            {
                float time = 0.0001f + (float)(10 - (sSparkles.sparkles_[i].timer_ - 5)) / 10.0f;
                if (time < 0.25f)
                    frame = 1;
                else if (time < 0.75f)
                    frame = 2;
                else if (time < 1.0f)
                    frame = 1;
            }
            if (frame > 0)
            {
                Sprite* sprite;
                if (frame == 1)
                    sprite = &sprites_[26];
                else if (frame == 2)
                    sprite = &sprites_[27];
                else
                    sprite = &sprites_[28];
                int y = (sparkle->y_ + 10) << 12;
                int x = (sparkle->x_ + 0xca) << 12;
                sprite->x_ = x;
                sprite->y_ = y;
                sprite->unk_22 = i + 0x48;
                func_0205ac40(&renderer_, sprite);
            }
        }
    }
    if (!(flags_ & ITEM_INFO_WINDOW_QUEST))
    {
        int x = 0xcb;
        for (unsigned char i = 0; i < item_->rank_; i++)
        {
            Sprite* sprite = &sprites_[21];
            int offset = 0;
            if (item_->rank_ == 5)
            {
                sprite = &sprites_[24];
                offset = 1;
                int shine = abs(20 - sSparkles.counter_) - 5;
                if (shine < 0)
                    shine = 0;
                else if (shine > 10)
                    shine = 10;
                for (int j = 2; j <= 6; j++)
                {
                    int level = shine + j * 3 - 14;
                    int red = level * 10 / 10 + 14;
                    int green = level * 3 / 10 + 29;
                    if (red > 31)
                        red = 31;
                    if (green > 31)
                        green = 31;
                    if (red < 0)
                        red = 0;
                    if (green < 0)
                        green = 0;
                    unsigned short color = red | (green << 5) | (green << 10);
                    int offset = j * 2;
                    CleanInvalidateCacheRange(&color, 2);
                    if (screen_ == 0)
                        LoadToMainObjStandardPalette(&color, offset + 0xe0, 2);
                    else
                        LoadToSubObjStandardPalette(&color, offset + 0xe0, 2);
                }
            }
            sprite->x_ = (x + offset) << 12;
            sprite->y_ = (offset + 0xb) << 12;
            sprite->unk_22 = i + 0x4c;
            func_0205ac40(&renderer_, sprite);
            x += 8;
        }
    }
    Sprite* sprite = &sprites_[func_020dee58(item_) + 1];
    sprite->x_ = 0x10000;
    sprite->y_ = 0x8000;
    sprite->unk_22 = 0x52;
    func_0205ac40(&renderer_, sprite);
    if (IsEquipment(item_))
    {
        PartModelInfo* info = item_->model_;
        int forbidden = 0;
        int forbidden2 = 0;
        if (info != NULL)
        {
            if (info->unk_4_27 == 1)
                forbidden = 1;
            if (info->unk_4_28 == 1)
                forbidden2 = 1;
        }
        unsigned char index = sForbiddenSprites[forbidden][forbidden2];
        if (index != 0)
        {
            Sprite* sprite = &sprites_[index];
            sprite->x_ = 0x90000;
            sprite->y_ = 0x8000;
            sprite->unk_22 = 0x53;
            func_0205ac40(&renderer_, sprite);
        }
        if (!(flags_ & ITEM_INFO_WINDOW_NO_SPRITE))
        {
            func_0203bd08();
            sprite_->unk_14 = oam + 0x2a0;
            func_02075db0(sprite_, 0x1c, 0x34);
        }
    }
    else if (!(flags_ & ITEM_INFO_WINDOW_NO_SPRITE))
    {
        sprite_->unk_14 = oam + 0x2a0;
        func_02075db0(sprite_, 0x1c, 0x34);
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _s32_div_f();
}

asm void ItemInfoWindow::DrawSprites()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x10
    mov r10, r0
    add r0, r10, #0x700
    ldrsb r1, [r0, #0x7b]
    cmp r1, #0x1
    bne @L021dc558
    ldrb r1, [r10, #0x79b]
    mov r1, r1, lsl #0x1e
    movs r1, r1, lsr #0x1f
    beq @L021dc9c4
    ldrh r0, [r0, #0x74]
    tst r0, #0x2000
    beq @L021dc9c4
@L021dc558:
    add r0, r10, #0x700
    ldrh r1, [r0, #0x74]
    tst r1, #0x2
    ldrne r1, [r10, #0x4c]
    cmpne r1, #0x0
    beq @L021dc9c4
    ldrsb r0, [r0, #0x7c]
    cmp r0, #0x0
    bne @L021dc58c
    bl func_0203bd08
    bl func_0203be40
    str r0, [sp, #0x4]
    b @L021dc598
@L021dc58c:
    bl func_0203bd08
    bl func_0203be4c
    str r0, [sp, #0x4]
@L021dc598:
    ldr r0, =sDrops
    ldrb r0, [r0, #0x50]
    cmp r0, #0x0
    beq @L021dc720
    ldr r0, =0x41a00000
    mov r6, #0x0
    sub r11, r0, #0x800000
    ldr r0, =0x3e4ccccd
    add r8, r10, #0x1b8
    sub r5, r0, #0xff000000
    b @L021dc718
@L021dc5c4:
    ldr r0, =sSparkles
    mov r1, r6, lsl #0x3
    cmp r6, #0x2
    ldrsh r1, [r0, r1]
    add r7, r0, r6, lsl #0x3
    mov r4, #0x0
    bne @L021dc668
    sub r0, r1, #0x3
    rsb r0, r0, #0x14
    bl _fflt
    ldr r1, =0x41a00000
    bl _fdiv
    mov r1, r0
    ldr r0, =0x38d1b717
    bl _fadd
    ldr r1, =0x3e4ccccd
    mov r9, r0
    bl _fls
    movlo r4, #0x1
    blo @L021dc6c0
    ldr r1, =0x3e4ccccd
    mov r0, r9
    add r1, r1, #0x800000
    bl _fls
    movlo r4, #0x2
    blo @L021dc6c0
    ldr r1, =0x3f19999a
    mov r0, r9
    bl _fls
    movlo r4, #0x3
    blo @L021dc6c0
    mov r0, r9
    mov r1, r5
    bl _fls
    movlo r4, #0x2
    blo @L021dc6c0
    mov r0, r9
    mov r1, #0x3f800000
    bl _fls
    movlo r4, #0x1
    b @L021dc6c0
@L021dc668:
    sub r0, r1, #0x5
    rsb r0, r0, #0xa
    bl _fflt
    mov r1, r11
    bl _fdiv
    mov r1, r0
    ldr r0, =0x38d1b717
    bl _fadd
    mov r1, #0x3e800000
    mov r9, r0
    bl _fls
    movlo r4, #0x1
    blo @L021dc6c0
    mov r0, r9
    mov r1, #0x3f400000
    bl _fls
    movlo r4, #0x2
    blo @L021dc6c0
    mov r0, r9
    mov r1, #0x3f800000
    bl _fls
    movlo r4, #0x1
@L021dc6c0:
    cmp r4, #0x0
    ble @L021dc714
    cmp r4, #0x1
    addeq r4, r10, #0x590
    beq @L021dc6e0
    cmp r4, #0x2
    addeq r4, r8, #0x400
    addne r4, r10, #0x5e0
@L021dc6e0:
    ldrsh r2, [r7, #0x6]
    ldrsh r1, [r7, #0x4]
    add r0, r6, #0x48
    add r2, r2, #0xa
    mov r2, r2, lsl #0xc
    add r1, r1, #0xca
    mov r1, r1, lsl #0xc
    str r1, [r4, #0x14]
    str r2, [r4, #0x18]
    strb r0, [r4, #0x22]
    mov r1, r4
    add r0, r10, #0x12c
    bl func_0205ac40
@L021dc714:
    add r6, r6, #0x1
@L021dc718:
    cmp r6, #0x3
    blt @L021dc5c4
@L021dc720:
    add r0, r10, #0x700
    ldrh r0, [r0, #0x74]
    tst r0, #0x1000
    bne @L021dc884
    mov r11, #0xcb
    mov r9, #0x0
    b @L021dc86c
@L021dc73c:
    add r0, r10, #0xc8
    cmp r1, #0x5
    add r4, r0, #0x400
    mov r5, #0x0
    bne @L021dc834
    ldr r0, =sDrops
    add r4, r10, #0x540
    ldrsh r0, [r0, #0x4c]
    mov r5, #0x1
    rsb r0, r0, #0x14
    bl abs
    subs r6, r0, #0x5
    movmi r6, #0x0
    bmi @L021dc77c
    cmp r6, #0xa
    movgt r6, #0xa
@L021dc77c:
    add r0, r10, #0x700
    mov r7, #0x2
    str r0, [sp, #0x8]
    b @L021dc82c
@L021dc78c:
    add r0, r7, r7, lsl #0x1
    add r0, r6, r0
    sub r1, r0, #0xe
    mov r0, #0xa
    mul r0, r1, r0
    str r1, [sp, #0x0]
    mov r1, #0xa
    bl _s32_div_f
    add r8, r0, #0xe
    ldr r0, [sp, #0x0]
    mov r1, #0xa
    add r0, r0, r0, lsl #0x1
    bl _s32_div_f
    cmp r8, #0x1f
    add r1, r0, #0x1d
    movgt r8, #0x1f
    cmp r1, #0x1f
    movgt r1, #0x1f
    cmp r8, #0x0
    movlt r8, #0x0
    cmp r1, #0x0
    movlt r1, #0x0
    orr r0, r8, r1, lsl #0x5
    orr r0, r0, r1, lsl #0xa
    strh r0, [sp, #0xc]
    add r0, sp, #0xc
    mov r1, #0x2
    mov r8, r7, lsl #0x1
    bl CleanInvalidateCacheRange
    ldr r0, [sp, #0x8]
    add r1, r8, #0xe0
    ldrsb r0, [r0, #0x7c]
    mov r2, #0x2
    cmp r0, #0x0
    add r0, sp, #0xc
    bne @L021dc824
    bl LoadToMainObjStandardPalette
    b @L021dc828
@L021dc824:
    bl LoadToSubObjStandardPalette
@L021dc828:
    add r7, r7, #0x1
@L021dc82c:
    cmp r7, #0x6
    ble @L021dc78c
@L021dc834:
    add r0, r11, r5
    mov r1, r0, lsl #0xc
    add r0, r5, #0xb
    str r1, [r4, #0x14]
    mov r0, r0, lsl #0xc
    mov r1, r4
    str r0, [r4, #0x18]
    add r2, r9, #0x4c
    add r0, r10, #0x12c
    strb r2, [r4, #0x22]
    bl func_0205ac40
    add r0, r9, #0x1
    add r11, r11, #0x8
    and r9, r0, #0xff
@L021dc86c:
    ldr r0, [r10, #0x4c]
    ldr r0, [r0, #0x8]
    mov r0, r0, lsl #0x14
    cmp r9, r0, lsr #0x1d
    mov r1, r0, lsr #0x1d
    blo @L021dc73c
@L021dc884:
    ldr r0, [r10, #0x4c]
    bl func_020dee58
    add r2, r0, #0x1
    add r1, r10, #0x180
    mov r0, #0x28
    mla r1, r2, r0, r1
    mov r0, #0x10000
    str r0, [r1, #0x14]
    mov r0, #0x8000
    str r0, [r1, #0x18]
    mov r0, #0x52
    strb r0, [r1, #0x22]
    add r0, r10, #0x12c
    bl func_0205ac40
    ldr r1, [r10, #0x4c]
    ldr r0, [r1, #0x8]
    mov r0, r0, lsl #0x1c
    mov r0, r0, lsr #0x1c
    cmp r0, #0x7
    movls r0, #0x1
    movhi r0, #0x0
    cmp r0, #0x0
    beq @L021dc994
    ldr r3, [r1, #0x0]
    mov r1, #0x0
    mov r2, r1
    cmp r3, #0x0
    beq @L021dc91c
    ldr r0, [r3, #0x4]
    mov r0, r0, lsl #0x4
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    ldr r0, [r3, #0x4]
    moveq r1, #0x1
    mov r0, r0, lsl #0x3
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    moveq r2, #0x1
@L021dc91c:
    ldr r0, =sForbiddenSprites
    add r0, r0, r1, lsl #0x1
    ldrb r2, [r2, r0]
    cmp r2, #0x0
    beq @L021dc95c
    add r1, r10, #0x180
    mov r0, #0x28
    mla r1, r2, r0, r1
    mov r0, #0x90000
    str r0, [r1, #0x14]
    mov r0, #0x8000
    str r0, [r1, #0x18]
    mov r2, #0x53
    add r0, r10, #0x12c
    strb r2, [r1, #0x22]
    bl func_0205ac40
@L021dc95c:
    add r0, r10, #0x700
    ldrh r0, [r0, #0x74]
    tst r0, #0x8
    bne @L021dc9c4
    bl func_0203bd08
    ldr r0, [sp, #0x4]
    ldr r1, [r10, #0xc4]
    add r0, r0, #0x2a0
    str r0, [r1, #0x14]
    ldr r0, [r10, #0xc4]
    mov r1, #0x1c
    mov r2, #0x34
    bl func_02075db0
    b @L021dc9c4
@L021dc994:
    add r0, r10, #0x700
    ldrh r0, [r0, #0x74]
    tst r0, #0x8
    bne @L021dc9c4
    ldr r0, [sp, #0x4]
    ldr r1, [r10, #0xc4]
    add r0, r0, #0x2a0
    str r0, [r1, #0x14]
    ldr r0, [r10, #0xc4]
    mov r1, #0x1c
    mov r2, #0x34
    bl func_02075db0
@L021dc9c4:
    add sp, sp, #0x10
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void ItemInfoWindow::Reset(SafeAllocator* allocator, short item, PartNameTable* names, unsigned short flags)
{
    func_0200fb8c(GameState::GetInstance());
    SetBrightness(-0x10, 1);
    CANCEL_TASKS();
    Finish();
    Initialize(item, mode_);
    flags_ |= flags;
    CreateAllocators(allocator);
    names_ = names;
}

void ItemInfoWindow::Close()
{
    if (state_ == 2)
        return;
    CANCEL_TASKS();
    state_ = 2;
    step_ = 0;
}

void ItemInfoWindow::SetItem(short item)
{
    if (state_ == 0 || !(flags_ & ITEM_INFO_WINDOW_CHANGE))
    {
        nextItemId_ = item;
        if (loadStep_ <= 0 || state_ == 0)
        {
            itemId_ = item;
            return;
        }
    }
    if (itemId_ == item)
    {
        if (names_ != NULL)
        {
            PartEntry* entry = func_020dedd0(names_, itemId_);
            if (item_ != entry)
                item_ = entry;
        }
        return;
    }
    ChangeItem(item);
}

// The kind of the background of an item (see sBackgroundKinds)
static unsigned char GetBackgroundKind(PartEntry* item)
{
    if (item == NULL)
        return 0;
    return sBackgroundKinds[IsEquipment(item)];
}

void ItemInfoWindow::ChangeItem(short item)
{
    if (state_ == 0)
    {
        nextItemId_ = item;
        return;
    }
    if (!(flags_ & ITEM_INFO_WINDOW_CHANGE))
        return;
    CANCEL_TASKS();
    itemId_ = item;
    nextItemId_ = itemId_;
    loadStep_ = 0;
    flags_ |= ITEM_INFO_WINDOW_LOAD | ITEM_INFO_WINDOW_NO_SPRITE;
    if (screen_ == 1)
    {
        memset((void*)GetSubBG0ScreenBase(), 0, 0x800);
        return;
    }
    memset((void*)GetMainBG2ScreenBase(), 0, 0x800);
}

void ItemInfoWindow::SetUpSubScreen()
{
    if (screen_ != 1)
        return;
    REG_BG0CNT_SUB = (REG_BG0CNT_SUB & 0x43) | 0xf00;
    REG_BG1CNT_SUB = (REG_BG1CNT_SUB & 0x43) | 0xe00;
    REG_BG0CNT_SUB = REG_BG0CNT_SUB & ~3;
    REG_BG1CNT_SUB = (REG_BG1CNT_SUB & ~3) | 1;
    REG_BG2CNT_SUB = (REG_BG2CNT_SUB & ~3) | 2;
    REG_BG3CNT_SUB = (REG_BG3CNT_SUB & ~3) | 3;
    REG_BG0HOFS_SUB = 0;
    REG_BG1HOFS_SUB = 0;
    memset((void*)GetSubBG0ScreenBase(), 0, 0x800);
    memset((void*)GetSubBG2ScreenBase(), 0, 0x800);
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1300;
}

void ItemInfoWindow::RestoreScreen()
{
    if (screen_ == 1)
    {
        func_02074bf4(screenState_);
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | (layers_ << 8);
        return;
    }
    func_02074bd0(screenState_);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (layers_ << 8);
}

void ItemInfoWindow::ClearBackground()
{
    memset((void*)GetMainBG1ScreenBase(), 0, 0x800);
}

void ItemInfoWindow::SetInMenu(unsigned char inMenu)
{
    if (inMenu_ && !inMenu)
    {
        memset((void*)GetMainBG1ScreenBase(), 0, 0x800);
        memset((void*)GetMainBG2ScreenBase(), 0, 0x800);
        ResetItem();
    }
    inMenu_ = inMenu;
}

void ItemInfoWindow::ResetItem()
{
    BackgroundLoader::GetInstance();
    if (state_ != 0)
    {
        CANCEL_TASKS();
        loadStep_ = 0;
        flags_ |= ITEM_INFO_WINDOW_LOAD;
    }
    nextItemId_ = -1;
    itemId_ = -2;
    backgroundKind_ = -1;
    flags_ &= ~ITEM_INFO_WINDOW_CHANGE;
    flags_ &= ~ITEM_INFO_WINDOW_LAYOUT;
}

void ItemInfoWindow::ClearNames()
{
    for (int i = 0; i < 3; i++)
        memberNames_[i] = NULL;
}

void ItemInfoWindow::SetName(int index, const char* name, unsigned char count, unsigned char maximum,
                             unsigned char unk)
{
    memberNames_[index] = name;
    memberCounts_[index] = count;
    memberMaxima_[index] = maximum;
    memberUnk_[index] = unk;
}

void ItemInfoWindow::SetMultiplier(unsigned char multiplier)
{
    multiplier_ = multiplier;
}

// Draws a text on a canvas
#define DRAW_TEXT(canvas, x, y, text, font, color)                          \
    {                                                                       \
        unsigned short width;                                               \
        unsigned short height;                                              \
        func_0204f41c(canvas, x, y, text, font, color, &width, &height, 0); \
    }

// NONMATCHING: the C matches 94.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original computes the row before the check of the sprites, in a register of its own
#ifdef NONMATCHING
void ItemInfoWindow::DrawNames(Canvas* canvas)
{
    if (sBuffer == NULL)
        return;
    if (screen_ == 0)
    {
        unsigned short color = 0x110f;
        int palette = sPalette << 5;
        CleanInvalidateCacheRange(&color, 2);
        LoadToMainBGStandardPalette(&color, palette + 0x12, 2);
    }
    char text[0x40] = {0};
    void* font = func_020421a0();
    for (int i = 0; i < 3; i++)
    {
        const char* name = memberNames_[i];
        if (name == NULL)
            continue;
        unsigned char count = multiplier_ * memberCounts_[i];
        unsigned char maximum = memberMaxima_[i];
        int color = 15;
        unsigned char unk = memberUnk_[i];
        if (count > maximum)
            color = 9;
        if (count == 0)
            continue;
        if (windowSprites_ == 1)
        {
            short line = i * 14 + 7;
            char codes[0x100] = {0};
            char formatted[0x100] = {0};
            func_0206819c(name, codes, 0);
            func_02046608(font, 10, codes, formatted, 0x400, 0, 0);
            DRAW_TEXT(canvas, 0, line, formatted, 10, color);
            sprintf(text, STRING(0x5, "<x>"));
            DRAW_TEXT(canvas, 0x72, line, text, 8, color);
            sprintf(text, STRING(0x9, "%2d"), count);
            DRAW_TEXT(canvas, 0x7d, line, text, 8, color);
            sprintf(text, STRING(0xd, "%3d"), maximum);
            DRAW_TEXT(canvas, 0xa1, line, text, 8, color);
            sprintf(text, STRING(0x11, "("));
            DRAW_TEXT(canvas, 0xc0, line, text, 10, color);
            sprintf(text, STRING(0x13, "%d"), unk);
            DRAW_TEXT(canvas, 0xc3, line, text, 8, color);
            sprintf(text, STRING(0x16, ")"));
            DRAW_TEXT(canvas, 0xc8, line, text, 10, color);
        }
        else
        {
            char codes[0x100] = {0};
            char formatted[0x100] = {0};
            func_0206819c(name, codes, 0);
            func_02046608(font, 10, codes, formatted, 0x400, 0, 0);
            short y = i * 14;
            DRAW_TEXT(canvas, 0x40, y, formatted, 10, color);
            sprintf(text, STRING(0x5, "<x>"));
            DRAW_TEXT(canvas, 0xc0, y, text, 8, color);
            sprintf(text, STRING(0x9, "%2d"), count);
            DRAW_TEXT(canvas, 0xc8, y, text, 8, color);
        }
    }
}
#else
asm void ItemInfoWindow::DrawNames(Canvas* canvas)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x8c
    sub sp, sp, #0x400
    ldr r2, =sDrops
    mov r10, r0
    ldr r0, [r2, #0x4]
    mov r9, r1
    cmp r0, #0x0
    beq @L021dd318
    add r0, r10, #0x700
    ldrsb r0, [r0, #0x7c]
    cmp r0, #0x0
    bne @L021dcf3c
    ldr r1, =0x110f
    add r0, sp, #0x48
    strh r1, [sp, #0x48]
    ldr r2, [r2, #0xc]
    mov r1, #0x2
    mov r4, r2, lsl #0x5
    bl CleanInvalidateCacheRange
    add r0, sp, #0x48
    add r1, r4, #0x12
    mov r2, #0x2
    bl LoadToMainBGStandardPalette
@L021dcf3c:
    add r0, sp, #0x4a
    mov r1, #0x40
    bl __clear
    bl func_020421a0
    str r0, [sp, #0x18]
    add r0, r10, #0x700
    mov r4, #0x0
    str r0, [sp, #0x1c]
    b @L021dd310
@L021dcf60:
    add r0, r10, r4, lsl #0x2
    ldr r11, [r0, #0x784]
    cmp r11, #0x0
    beq @L021dd30c
    add r0, r10, r4
    ldrb r2, [r10, #0x799]
    ldrb r1, [r0, #0x790]
    ldrb r6, [r0, #0x793]
    ldrb r0, [r0, #0x796]
    mov r7, #0xf
    str r0, [sp, #0x14]
    smulbb r0, r2, r1
    and r5, r0, #0xff
    cmp r5, r6
    movhi r7, #0x9
    cmp r5, #0x0
    beq @L021dd30c
    ldr r0, [sp, #0x1c]
    mov r1, #0x100
    ldrsb r0, [r0, #0x7d]
    cmp r0, #0x1
    mov r0, #0xe
    mul r0, r4, r0
    bne @L021dd1f4
    add r0, r0, #0x7
    mov r0, r0, lsl #0x10
    mov r8, r0, asr #0x10
    add r0, sp, #0x300
    add r0, r0, #0x8a
    bl __clear
    add r0, sp, #0x200
    add r0, r0, #0x8a
    mov r1, #0x100
    bl __clear
    add r1, sp, #0x300
    mov r0, r11
    add r1, r1, #0x8a
    mov r2, #0x0
    bl func_0206819c
    mov r0, #0x400
    str r0, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    add r2, sp, #0x300
    add r3, sp, #0x200
    ldr r0, [sp, #0x18]
    mov r1, #0xa
    add r2, r2, #0x8a
    add r3, r3, #0x8a
    bl func_02046608
    mov r0, #0xa
    stmia sp, {r0, r7}
    add r0, sp, #0x46
    str r0, [sp, #0x8]
    add r0, sp, #0x44
    str r0, [sp, #0xc]
    mov r0, #0x0
    add r3, sp, #0x200
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0x0
    mov r2, r8
    add r3, r3, #0x8a
    bl func_0204f41c
    ldr r1, =sStrings+0x5
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0x8
    stmia sp, {r0, r7}
    add r0, sp, #0x42
    str r0, [sp, #0x8]
    add r0, sp, #0x40
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0x72
    mov r2, r8
    add r3, sp, #0x4a
    bl func_0204f41c
    ldr r1, =sStrings+0x9
    mov r2, r5
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0x8
    stmia sp, {r0, r7}
    add r0, sp, #0x3e
    str r0, [sp, #0x8]
    add r0, sp, #0x3c
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0x7d
    mov r2, r8
    add r3, sp, #0x4a
    bl func_0204f41c
    ldr r1, =sStrings+0xd
    mov r2, r6
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0x8
    stmia sp, {r0, r7}
    add r0, sp, #0x3a
    str r0, [sp, #0x8]
    add r0, sp, #0x38
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0xa1
    mov r2, r8
    add r3, sp, #0x4a
    bl func_0204f41c
    ldr r1, =sStrings+0x11
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0xa
    stmia sp, {r0, r7}
    add r0, sp, #0x36
    str r0, [sp, #0x8]
    add r0, sp, #0x34
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0xc0
    mov r2, r8
    add r3, sp, #0x4a
    bl func_0204f41c
    ldr r2, [sp, #0x14]
    ldr r1, =sStrings+0x13
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0x8
    stmia sp, {r0, r7}
    add r0, sp, #0x32
    str r0, [sp, #0x8]
    add r0, sp, #0x30
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0xc3
    mov r2, r8
    add r3, sp, #0x4a
    bl func_0204f41c
    ldr r1, =sStrings+0x16
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0xa
    stmia sp, {r0, r7}
    add r0, sp, #0x2e
    str r0, [sp, #0x8]
    add r0, sp, #0x2c
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r2, r8
    mov r0, r9
    mov r1, #0xc8
    add r3, sp, #0x4a
    bl func_0204f41c
    b @L021dd30c
@L021dd1f4:
    mov r0, r0, lsl #0x10
    mov r6, r0, asr #0x10
    add r0, sp, #0x100
    add r0, r0, #0x8a
    bl __clear
    add r0, sp, #0x8a
    mov r1, #0x100
    bl __clear
    add r1, sp, #0x100
    mov r0, r11
    add r1, r1, #0x8a
    mov r2, #0x0
    bl func_0206819c
    mov r0, #0x400
    str r0, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    add r2, sp, #0x100
    ldr r0, [sp, #0x18]
    mov r1, #0xa
    add r2, r2, #0x8a
    add r3, sp, #0x8a
    bl func_02046608
    mov r0, #0xa
    stmia sp, {r0, r7}
    add r0, sp, #0x2a
    str r0, [sp, #0x8]
    add r0, sp, #0x28
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0x40
    mov r2, r6
    add r3, sp, #0x8a
    bl func_0204f41c
    ldr r1, =sStrings+0x5
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0x8
    stmia sp, {r0, r7}
    add r0, sp, #0x26
    str r0, [sp, #0x8]
    add r0, sp, #0x24
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r0, r9
    mov r1, #0xc0
    mov r2, r6
    add r3, sp, #0x4a
    bl func_0204f41c
    ldr r1, =sStrings+0x9
    mov r2, r5
    add r0, sp, #0x4a
    bl sprintf
    mov r0, #0x8
    stmia sp, {r0, r7}
    add r0, sp, #0x22
    str r0, [sp, #0x8]
    add r0, sp, #0x20
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    mov r2, r6
    mov r0, r9
    mov r1, #0xc8
    add r3, sp, #0x4a
    bl func_0204f41c
@L021dd30c:
    add r4, r4, #0x1
@L021dd310:
    cmp r4, #0x3
    blt @L021dcf60
@L021dd318:
    add sp, sp, #0x8c
    add sp, sp, #0x400
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

unsigned int ItemInfoWindow::DrawNameBox()
{
    unsigned int result = inMenu_;
    if (result)
    {
        Canvas canvas;
        func_0204c684(&canvas);
        result = SetUpCanvas(&canvas, 3, 0x10, 0x1a, 6);
        if (result)
        {
            DrawNames(&canvas);
            if (namesOffset_ != 0)
                return LoadCanvas(&canvas, namesOffset_, sPalette, 1);
            unsigned int size = LoadCanvas(&canvas, vramOffset_, sPalette, 1);
            namesOffset_ = vramOffset_;
            namesSize_ = size;
            vramOffset_ += size;
            return vramOffset_;
        }
    }
    return result;
}

void ItemInfoWindow::DrawArrow()
{
    if (mode_ == 1 && !(inMenu_ && (flags_ & ITEM_INFO_WINDOW_LAYOUT)))
        return;
    if (windowSprites_ == 1)
    {
        if (!(flags_ & ITEM_INFO_WINDOW_NAMES))
            return;
        Sprite* sprite = &sprites_[29];
        sprite->unk_26 = 1;
        sprite->x_ = 0x10000;
        sprite->y_ = 0x68000;
        sprite->unk_22 = 0x58;
        func_0205ac40(&renderer_, sprite);
    }
    else if (windowSprites_ == 2)
    {
        if (!(flags_ & ITEM_INFO_WINDOW_NAMES))
            return;
        Sprite* sprite = &sprites_[29];
        sprite->unk_26 = 2;
        sprite->x_ = 0x10000;
        sprite->y_ = 0x68000;
        sprite->unk_22 = 0x58;
        func_0205ac40(&renderer_, sprite);
    }
}

void ItemInfoWindow::LoadWindowSprites(signed char sprites)
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (sprites == windowSprites_)
    {
        if (windowSpriteTask_ < 0)
            return;
        loader->RemoveTask(windowSpriteTask_);
        windowSpriteTask_ = -1;
        nextWindowSprites_ = windowSprites_;
        return;
    }
    if (sprites == nextWindowSprites_)
        return;
    if (windowSpriteTask_ >= 0)
    {
        loader->RemoveTask(windowSpriteTask_);
        windowSpriteTask_ = -1;
        nextWindowSprites_ = -1;
    }
    if (sprites == 2)
        windowSpriteTask_ =
            loader->QueueLoadFileInGP2(STRING(0x18, "data/ani/oiij.gp2"), STRING(0x2a, "oiij_<LG>.pac"), NULL);
    else
        windowSpriteTask_ =
            loader->QueueLoadFileInGP2(STRING(0x38, "data/ani/oiir.gp2"), STRING(0x4a, "oiir_<LG>.pac"), NULL);
    flags_ |= ITEM_INFO_WINDOW_NO_SPRITE;
    nextWindowSprites_ = sprites;
}

void ItemInfoWindow::State_Open()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_0200fb8c(GameState::GetInstance());
    if (step_ == 0)
    {
        if (sBuffer == NULL)
            sBuffer = func_02012d88(data_02114e20, 0x1800);
        if (!(flags_ & ITEM_INFO_WINDOW_FADE))
        {
            step_ = 2;
            return;
        }
        if (mode_ != 1)
            SetBrightness(-0x10, 8);
        step_++;
    }
    if (step_ == 1 && !IsFading())
    {
        if (mode_ != 1)
            func_020dc2bc();
        step_++;
    }
    if (step_ == 2)
    {
        if (flags_ & ITEM_INFO_WINDOW_KEEP_MUSIC)
        {
            step_ = 4;
            return;
        }
        func_02094b30(func_02094a00(), 0x1fa, 0);
        step_++;
    }
    else if (step_ == 3)
    {
        if (func_02094b4c(func_02094a00()))
            step_++;
    }
    if (step_ == 4)
    {
        if (screen_ == 1)
            func_02074b64(screenState_);
        else
            func_02074af4(screenState_);
        renderer_.unk_50 = screen_;
        renderer_.SetSprites(sprites_, 30);
        task_ = loader->QueueLoadFileInGP2(STRING(0x38, "data/ani/oiir.gp2"), STRING(0x4a, "oiir_<LG>.pac"),
                                           NULL);
        step_++;
    }
    else if (step_ == 5 && loader->GetTaskStatus(task_))
    {
        windowSpriteAllocator_->Reset();
        char* name;
        void* file;
        unsigned int size;
        unsigned int fileSize;
        loader->GetLoadedFileByID(task_, &file, &size);
        if (file != NULL && size != 0)
        {
            int count = func_02046900(file);
            for (int i = 0; i < count; i++)
            {
                func_0205a528(&renderer_, func_020467f0(file, i, &name, &fileSize), fileSize, windowSpriteAllocator_);
            }
        }
        windowSprites_ = 1;
        loader->RemoveTask(task_);
        task_ = -1;
        step_++;
    }
    if (step_ == 6)
    {
        task_ = loader->QueueLoadFileInGP2(STRING(0x58, "data/bin/menu/str_ii.gp2"),
                                           STRING(0x71, "str_ii_<LG>.nat"), NULL);
        step_++;
    }
    else if (step_ == 7 && loader->GetTaskStatus(task_))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(task_, &file, &size);
        textAllocator_.Reset();
        if (file != NULL && size != 0)
            func_020dfec0(&texts_, &textAllocator_, file, size);
        loader->RemoveTask(task_);
        task_ = -1;
        step_++;
    }
    if (step_ == 8)
    {
        unsigned int layers;
        if (screen_ == 1)
            layers = REG_DISPCNT_SUB;
        else
            layers = REG_DISPCNT;
        layers_ = (layers & 0x1f00) >> 8;
        if (mode_ != 1)
            SetUpSubScreen();
        state_ = 1;
        step_ = 0;
        CANCEL_TASKS();
        loadStep_ = 0;
        flags_ |= ITEM_INFO_WINDOW_LOAD;
    }
}

void ItemInfoWindow::State_Update()
{
    if (!(flags_ & ITEM_INFO_WINDOW_NO_UPDATE))
        UpdateLoad();
    UpdateWindowSprites();
    if (windowSprites_ >= 0)
    {
        DrawSprites();
        DrawArrow();
    }
    if (!(flags_ & ITEM_INFO_WINDOW_FADE))
        return;
    func_0200fb8c(GameState::GetInstance());
    if (!(flags_ & ITEM_INFO_WINDOW_FADE_IN))
        return;
    SetBrightness(0, 8);
    flags_ &= ~ITEM_INFO_WINDOW_FADE_IN;
}

void ItemInfoWindow::State_Close()
{
    func_0200fb8c(GameState::GetInstance());
    if (step_ == 0)
    {
        DrawSprites();
        DrawArrow();
        if (!(flags_ & ITEM_INFO_WINDOW_FADE))
        {
            state_ = 3;
            return;
        }
        SetBrightness(-0x10, 8);
        step_++;
    }
    if (step_ == 1)
    {
        DrawSprites();
        DrawArrow();
        if (!IsFading())
            step_++;
    }
    if (step_ == 2)
    {
        Finish();
        if (flags_ & ITEM_INFO_WINDOW_KEEP_BRIGHTNESS)
        {
            state_ = 3;
            return;
        }
        if (mode_ != 1)
            func_020dc2d0(0);
        state_ = 3;
    }
}

void ItemInfoWindow::UpdateWindowSprites()
{
    if (windowSpriteTask_ < 0)
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (!loader->GetTaskStatus(windowSpriteTask_))
        return;
    windowSpriteAllocator_->Reset();
    char* name;
    void* file;
    unsigned int size;
    unsigned int fileSize;
    loader->GetLoadedFileByID(windowSpriteTask_, &file, &size);
    if (file != NULL && size != 0)
    {
        int count = func_02046900(file);
        for (int i = 0; i < count; i++)
        {
            func_0205a528(&renderer_, func_020467f0(file, i, &name, &fileSize), fileSize, windowSpriteAllocator_);
        }
    }
    windowSprites_ = nextWindowSprites_;
    loader->RemoveTask(windowSpriteTask_);
    windowSpriteTask_ = -1;
}

void ItemInfoWindow::SetBrightness(int brightness, int frames)
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    if (screen_ == 1)
    {
        SetSubBrightness(resources, brightness, frames);
        return;
    }
    SetMainBrightness(resources, brightness, frames);
}

int ItemInfoWindow::IsFading()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    int fading;
    if (screen_ == 1)
        fading = IsSubBrightnessTransitionActive(resources);
    else
        fading = IsMainBrightnessTransitionActive(resources);
    if (fading)
        return 1;
    return 0;
}

// Sets a canvas that draws on the canvas buffer, at a place of the background
static unsigned int SetUpCanvas(Canvas* canvas, short x, short y, short width, short height)
{
    unsigned int result = 0;
    if (sBuffer != NULL && canvas != NULL)
    {
        memset(sBuffer, 0, 0x1800);
        result = 1;
        canvas->pixels_ = sBuffer;
        canvas->x_ = x;
        canvas->y_ = y;
        canvas->width_ = width;
        canvas->height_ = height;
    }
    return result;
}

// Copies a canvas to the VRAM of the background, at an offset, and writes its tiles in the background's screen
// NONMATCHING: the C matches 83.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler gives the screen and the row other registers
#ifdef NONMATCHING
static unsigned int LoadCanvas(Canvas* canvas, unsigned int offset, unsigned short palette, int bg1)
{
    unsigned int size = 0;
    if (sBuffer != NULL && canvas != NULL)
    {
        short width = canvas->width_;
        signed char screen = sWindow->screen_;
        short height = canvas->height_;
        size = (width * height) << 5;
        int x = canvas->x_;
        int y = canvas->y_;
        if (screen == 1)
        {
            CleanInvalidateCacheRange(sBuffer, size);
            LoadToSubBG0CharacterData(sBuffer, offset, size);
        }
        else
        {
            CleanInvalidateCacheRange(sBuffer, size);
            if (bg1)
                LoadToMainBG1CharacterData(sBuffer, offset, size);
            else
                LoadToMainBG2CharacterData(sBuffer, offset, size);
        }
        unsigned int tile = (offset << 11) >> 16;
        unsigned short* base = GetScreenBase(screen, bg1);
        if (base != NULL)
        {
            for (short i = 0; i < height; i++)
            {
                unsigned short* tiles = base + (y << 5) + x;
                for (short j = 0; j < width; j++)
                {
                    unsigned short value = tile;
                    value |= palette << 12;
                    CleanInvalidateCacheRange(&value, 2);
                    tile = (unsigned short)(tile + 1);
                    *tiles = value;
                    tiles++;
                }
                y++;
            }
        }
    }
    return size;
}
#else
static asm unsigned int LoadCanvas(Canvas* canvas, unsigned int offset, unsigned short palette, int bg1)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x10
    ldr r5, =sDrops
    mov r10, r1
    ldr r1, [r5, #0x4]
    mov r9, r3
    cmp r1, #0x0
    str r2, [sp, #0x0]
    mov r4, #0x0
    cmpne r0, #0x0
    beq @L021dddf0
    ldr r2, [r5, #0x20]
    ldrsh r5, [r0, #0xa8]
    add r2, r2, #0x700
    ldrsb r7, [r2, #0x7c]
    ldrsh r6, [r0, #0xaa]
    cmp r7, #0x1
    smulbb r2, r5, r6
    mov r4, r2, lsl #0x5
    ldrsh r2, [r0, #0xac]
    str r2, [sp, #0x8]
    ldrsh r8, [r0, #0xae]
    mov r0, r1
    mov r1, r4
    bne @L021ddd18
    bl CleanInvalidateCacheRange
    ldr r0, =sDrops
    mov r1, r10
    ldr r0, [r0, #0x4]
    mov r2, r4
    bl LoadToSubBG0CharacterData
    b @L021ddd50
@L021ddd18:
    bl CleanInvalidateCacheRange
    cmp r9, #0x0
    beq @L021ddd3c
    ldr r0, =sDrops
    mov r1, r10
    ldr r0, [r0, #0x4]
    mov r2, r4
    bl LoadToMainBG1CharacterData
    b @L021ddd50
@L021ddd3c:
    ldr r0, =sDrops
    mov r1, r10
    ldr r0, [r0, #0x4]
    mov r2, r4
    bl LoadToMainBG2CharacterData
@L021ddd50:
    mov r2, r10, lsl #0xb
    mov r0, r7
    mov r1, r9
    mov r7, r2, lsr #0x10
    bl GetScreenBase
    str r0, [sp, #0x4]
    cmp r0, #0x0
    beq @L021dddf0
    mov r9, #0x0
    b @L021ddde8
@L021ddd78:
    ldr r0, [sp, #0x4]
    mov r10, #0x0
    add r1, r0, r8, lsl #0x6
    ldr r0, [sp, #0x8]
    add r11, r1, r0, lsl #0x1
    b @L021dddd0
@L021ddd90:
    strh r7, [sp, #0xc]
    ldrh r3, [sp, #0xc]
    ldr r2, [sp, #0x0]
    add r0, sp, #0xc
    orr r2, r3, r2, lsl #0xc
    mov r1, #0x2
    strh r2, [sp, #0xc]
    bl CleanInvalidateCacheRange
    add r0, r7, #0x1
    ldrh r1, [sp, #0xc]
    mov r0, r0, lsl #0x10
    mov r7, r0, lsr #0x10
    add r0, r10, #0x1
    mov r0, r0, lsl #0x10
    strh r1, [r11], #0x2
    mov r10, r0, asr #0x10
@L021dddd0:
    cmp r10, r5
    blt @L021ddd90
    add r0, r9, #0x1
    mov r0, r0, lsl #0x10
    add r8, r8, #0x1
    mov r9, r0, asr #0x10
@L021ddde8:
    cmp r9, r6
    blt @L021ddd78
@L021dddf0:
    mov r0, r4
    add sp, sp, #0x10
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void ItemInfoWindow::DrawItemName()
{
    if (nextItem_ != NULL)
    {
        Canvas canvas;
        func_0204c684(&canvas);
        if (SetUpCanvas(&canvas, 4, 1, 0xf, 2))
        {
            PartEntry* item = nextItem_;
            if (sBuffer != NULL && item != NULL)
            {
                char formatted[0x80];
                char codes[0x80];
                void* font = func_020421a0();
                __clear(codes, sizeof(codes));
                __clear(formatted, sizeof(formatted));
                func_0206819c((const char*)item->unk_4, codes, 0);
                func_02046608(font, 10, codes, formatted, 0x100, 0, 0);
                unsigned short width;
                unsigned short height;
                func_0204f41c(&canvas, (0x70 - (short)func_020420e8(formatted, 0)) >> 1, 3, formatted, 10, 15, &height,
                              &width, 0);
            }
            vramOffset_ += LoadCanvas(&canvas, vramOffset_, sPalette, 0);
        }
    }
    if (flags_ & ITEM_INFO_WINDOW_NAMES)
        DrawNameBox();
}

// NONMATCHING: the C matches 78.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler assigns the registers of the loops' variables in another order
#ifdef NONMATCHING
void ItemInfoWindow::DrawStats()
{
    Canvas canvas;
    func_0204c684(&canvas);
    if (!SetUpCanvas(&canvas, 0, 0, 0x14, 9))
        return;
    if (member_ < 0)
    {
        PartEntry* item = item_;
        short statY;
        short statX;
        unsigned short height;
        unsigned short width;
        short y;
        short x;
        float values[6];
        float stats[12];
        unsigned char indices[6];
        TakeElement(&layout_, &canvas, 0xb, &x, &y);
        SHOW_ELEMENT(&layout_, 0xb);
        SHOW_ELEMENT(&layout_, 0x2d);
        HIDE_ELEMENT(&layout_, 0x2e);
        HIDE_ELEMENT(&layout_, 0x2c);
        __clear(stats, sizeof(stats));
        __clear(indices, sizeof(indices));
        GetItemStats(item, stats);
        unsigned char count = 0;
        __clear(values, sizeof(values));
        for (unsigned char i = 0; i < 12; i++)
        {
            if (stats[i] != 0.0f)
            {
                values[count] = stats[i];
                indices[count] = i;
                count++;
                if (count >= 4)
                    break;
            }
        }
        for (unsigned char i = 0; i < 4; i++)
        {
            short name = sStatNames[i];
            if (i < count)
            {
                SHOW_ELEMENT(&layout_, name);
                SHOW_ELEMENT(&layout_, sStatLabels[i]);
                HIDE_ELEMENT(&layout_, sStatSigns[i]);
            }
            else
            {
                HIDE_ELEMENT(&layout_, name);
                HIDE_ELEMENT(&layout_, sStatLabels[i]);
                HIDE_ELEMENT(&layout_, sStatSigns[i]);
            }
        }
        for (unsigned char i = 0; i < count; i++)
        {
            float value = values[i];
            int text = indices[i] + 0xc;
            layout_.SetText(sStatLabels[i], func_020e0434(sTexts, text), 10, 15);
            short id = sStatValues[i];
            layout_.GetPosition(id, &statX, &statY);
            switch (text - 0xe)
            {
            case 0:
            case 1:
            case 2:
            case 3:
                if (sBuffer != NULL)
                {
                    func_0204f41c(&canvas, statX + 1, statY, func_020e0434(sTexts, 0x1a), 8, 15, &width, &height, 0);
                    DrawDecimal(&canvas, statX, statY, value, 15);
                }
                HIDE_ELEMENT(&layout_, id);
                break;
            default:
                if (value < 0.0f)
                {
                    short sign = sStatSigns[i];
                    SHOW_ELEMENT(&layout_, sign);
                    layout_.SetText(sign, func_020e0434(sTexts, 0x19), 8, 15);
                }
                short numberId = sStatValues[i];
                layout_.SetNumber(numberId, func_020017b0((int)value), 8, 15, 1, 3, 0, 0);
                SHOW_ELEMENT(&layout_, numberId);
                break;
            }
        }
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0xb, x, y);
        HIDE_ELEMENT(&layout_, 0xb);
    }
    else if (func_020dd718(member_, item_->unk_18))
    {
        signed char member = member_;
        PartEntry* item = item_;
        short statY;
        short statX;
        unsigned short height;
        unsigned short width;
        short y;
        short x;
        float values[6];
        float stats[12];
        float memberStats[12];
        unsigned char indices[6];
        TakeElement(&layout_, &canvas, 0xb, &x, &y);
        SHOW_ELEMENT(&layout_, 0xb);
        SHOW_ELEMENT(&layout_, 0x2d);
        HIDE_ELEMENT(&layout_, 0x2e);
        HIDE_ELEMENT(&layout_, 0x2c);
        __clear(memberStats, sizeof(memberStats));
        __clear(stats, sizeof(stats));
        __clear(indices, sizeof(indices));
        GetMemberStats(member, memberStats, NULL);
        GetItemStats(item, stats);
        unsigned char count = 0;
        __clear(values, sizeof(values));
        for (unsigned char i = 0; i < 12; i++)
        {
            int shown = 0;
            if (i == 3 && item->category_ == 1)
            {
                if (stats[3] != 0.0f)
                    shown = 1;
            }
            if (shown || stats[i] != 0.0f)
            {
                values[count] = memberStats[i];
                indices[count] = i;
                count++;
                if (count >= 4)
                    break;
            }
        }
        for (unsigned char i = 0; i < 4; i++)
        {
            short name = sStatNames2[i];
            if (i < count)
            {
                SHOW_ELEMENT(&layout_, name);
                SHOW_ELEMENT(&layout_, sStatLabels2[i]);
                SHOW_ELEMENT(&layout_, sStatSigns2[i]);
            }
            else
            {
                HIDE_ELEMENT(&layout_, name);
                HIDE_ELEMENT(&layout_, sStatLabels2[i]);
                HIDE_ELEMENT(&layout_, sStatSigns2[i]);
            }
        }
        for (unsigned char i = 0; i < count; i++)
        {
            float value = values[i];
            int text = indices[i] + 0xc;
            layout_.SetText(sStatLabels2[i], func_020e0434(sTexts, text), 10, 15);
            short id = sStatValues2[i];
            layout_.GetPosition(id, &statX, &statY);
            switch (text - 0xe)
            {
            case 0:
            case 1:
            case 2:
            case 3:
                if (sBuffer != NULL)
                {
                    func_0204f41c(&canvas, statX + 1, statY, func_020e0434(sTexts, 0x1a), 8, 15, &width, &height, 0);
                    DrawDecimal(&canvas, statX, statY, value, 15);
                }
                HIDE_ELEMENT(&layout_, id);
                break;
            default:
                short numberId = sStatValues2[i];
                layout_.SetNumber(numberId, func_020017b0((int)value), 8, 15, 1, 3, 0, 0);
                SHOW_ELEMENT(&layout_, numberId);
                break;
            }
            short sign = sStatSigns2[i];
            SHOW_ELEMENT(&layout_, sign);
            layout_.SetText(sign, func_020e0434(sTexts, 0x22), 8, 15);
        }
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0xb, x, y);
        HIDE_ELEMENT(&layout_, 0xb);
    }
    else if (!func_020dd4c4(member_, item_))
    {
        signed char member = member_;
        PartEntry* item = item_;
        short statY;
        short statX;
        unsigned short height;
        unsigned short width;
        short y;
        short x;
        unsigned char changes[12];
        float newStats[12];
        float memberStats[12];
        unsigned char indices[6];
        TakeElement(&layout_, &canvas, 0xb, &x, &y);
        SHOW_ELEMENT(&layout_, 0xb);
        HIDE_ELEMENT(&layout_, 0x2d);
        SHOW_ELEMENT(&layout_, 0x2e);
        HIDE_ELEMENT(&layout_, 0x2c);
        __clear(memberStats, sizeof(memberStats));
        GetMemberStats(member, memberStats, NULL);
        __clear(newStats, sizeof(newStats));
        GetMemberStats(member, newStats, item);
        PartModelInfo* info = NULL;
        __clear(changes, sizeof(changes));
        if (item != NULL && item->unk_18 > 0)
            info = item->model_;
        if (info != NULL)
        {
            if (info->unk_8_0 != 0)
                changes[0] = 1;
            if (info->unk_8_10 != 0)
                changes[1] = 1;
            if (info->unk_8_20 / 10.0f != 0.0f)
                changes[2] = 1;
            if (info->unk_c_0 / 10.0f != 0.0f)
                changes[3] = 1;
            if (info->unk_c_10 / 10.0f != 0.0f)
                changes[4] = 1;
            if (info->unk_10_0 != 0)
                changes[6] = 1;
            if (info->unk_10_10 != 0)
                changes[7] = 1;
            if (info->unk_10_20 != 0)
                changes[8] = 1;
            if (info->unk_14_0 != 0)
                changes[9] = 1;
            if (info->unk_14_10 != 0)
                changes[10] = 1;
            if (info->unk_14_20 != 0)
                changes[11] = 1;
            if (item->category_ == 1 && (memberStats[3] != 0.0f || newStats[3] != 0.0f))
                changes[3] = 1;
        }
        __clear(indices, sizeof(indices));
        unsigned char count = 0;
        for (unsigned char i = 0; i < 12; i++)
        {
            if (changes[i] || memberStats[i] - newStats[i] != 0.0f)
            {
                indices[count] = i;
                count++;
                if (count >= 4)
                    break;
            }
        }
        for (unsigned char i = 0; i < 4; i++)
        {
            short name = sStatNames3[i];
            if (i < count)
            {
                SHOW_ELEMENT(&layout_, name);
                SHOW_ELEMENT(&layout_, sStatLabels3[i]);
            }
            else
            {
                HIDE_ELEMENT(&layout_, name);
                HIDE_ELEMENT(&layout_, sStatLabels3[i]);
            }
        }
        for (unsigned char i = 0; i < count; i++)
        {
            unsigned char index = indices[i];
            int text = index + 0xc;
            layout_.SetText(sStatLabels3[i], func_020e0434(sTexts, text), 10, 15);
            short id = sStatValues3[i];
            layout_.GetPosition(id, &statX, &statY);
            float value = memberStats[index];
            switch (text - 0xe)
            {
            case 0:
            case 1:
            case 2:
            case 3:
                if (sBuffer != NULL)
                {
                    func_0204f41c(&canvas, statX + 1, statY, func_020e0434(sTexts, 0x1a), 8, 15, &width, &height, 0);
                    DrawDecimal(&canvas, statX, statY, value, 15);
                }
                HIDE_ELEMENT(&layout_, id);
                break;
            default:
                short numberId = sStatValues3[i];
                layout_.SetNumber(numberId, func_020017b0((int)value), 8, 15, 1, 3, 0, 0);
                SHOW_ELEMENT(&layout_, numberId);
                break;
            }
            layout_.SetText(sStatArrows3[i], func_020e0434(sTexts, 0x20), 8, 15);
            float newValue = newStats[index];
            int color = 9;
            if (value == newValue)
                color = 15;
            else if (value < newValue)
                color = 5;
            short newId = sStatNewValues3[i];
            layout_.GetPosition(newId, &statX, &statY);
            switch (text - 0xe)
            {
            case 0:
            case 1:
            case 2:
            case 3:
                if (sBuffer != NULL)
                {
                    func_0204f41c(&canvas, statX + 1, statY, func_020e0434(sTexts, 0x1a), 8, color, &width, &height,
                                  0);
                    DrawDecimal(&canvas, statX, statY, newValue, color);
                }
                HIDE_ELEMENT(&layout_, newId);
                break;
            default:
                short numberId = sStatNewValues3[i];
                layout_.SetNumber(numberId, func_020017b0((int)newValue), 8, color, 1, 3, 0, 0);
                SHOW_ELEMENT(&layout_, numberId);
                break;
            }
        }
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0xb, x, y);
        HIDE_ELEMENT(&layout_, 0xb);
    }
    else
    {
        short y;
        short x;
        TakeElement(&layout_, &canvas, 0xb, &x, &y);
        SHOW_ELEMENT(&layout_, 0xb);
        SHOW_ELEMENT(&layout_, 0x2c);
        LayoutElement* element = layout_.FindElement(0x2c);
        if (element != NULL)
            element->flags_ |= LAYOUT_ELEMENT_FLAG_CENTERED;
        layout_.SetText(0x2c, func_020e0434(sTexts, 0x21), 10, 15);
        HIDE_ELEMENT(&layout_, 0xa);
        HIDE_ELEMENT(&layout_, 0xc);
        HIDE_ELEMENT(&layout_, 0xd);
        HIDE_ELEMENT(&layout_, 0xe);
        HIDE_ELEMENT(&layout_, 0x2d);
        HIDE_ELEMENT(&layout_, 0x2e);
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0xb, x, y);
        HIDE_ELEMENT(&layout_, 0xb);
    }
    if (statsOffset_ != 0)
    {
        LoadCanvas(&canvas, statsOffset_, sPalette, 0);
        return;
    }
    unsigned int size = LoadCanvas(&canvas, vramOffset_, sPalette, 0);
    statsOffset_ = vramOffset_;
    statsSize_ = size;
    vramOffset_ += size;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN6Layout11GetPositionEsPsS0_(); // Layout::GetPosition
    void _ZN6Layout9SetNumberEsihhhhhh(); // Layout::SetNumber
}

asm void ItemInfoWindow::DrawStats()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x25c
    mov r4, r0
    add r0, sp, #0x17c
    bl func_0204c684
    mov r1, #0x0
    mov r5, #0x9
    add r0, sp, #0x17c
    mov r2, r1
    mov r3, #0x14
    str r5, [sp, #0x0]
    bl SetUpCanvas
    cmp r0, #0x0
    beq @L021df210
    add r0, r4, #0x700
    ldrsb r0, [r0, #0x7a]
    cmp r0, #0x0
    bge @L021de3f8
    ldr r5, [r4, #0x4c]
    add r6, sp, #0x32
    add r1, sp, #0x17c
    add r3, sp, #0x30
    add r0, r4, #0xcc
    mov r2, #0xb
    str r6, [sp, #0x0]
    bl TakeElement
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2d
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2e
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2c
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, sp, #0x134
    mov r1, #0x30
    bl __clear
    add r0, sp, #0x48
    mov r1, #0x6
    bl __clear
    add r1, sp, #0x134
    mov r0, r5
    bl GetItemStats
    add r0, sp, #0x164
    mov r1, #0x18
    mov r8, #0x0
    bl __clear
    mov r9, r8
    add r7, sp, #0x134
    add r6, sp, #0x164
    add r5, sp, #0x48
    mov r10, r8
    b @L021de0b4
@L021de080:
    ldr r1, [r7, r9, lsl #0x2]
    mov r0, r10
    bl _fneq
    beq @L021de0ac
    ldr r1, [r7, r9, lsl #0x2]
    add r0, r8, #0x1
    str r1, [r6, r8, lsl #0x2]
    strb r9, [r5, r8]
    and r8, r0, #0xff
    cmp r8, #0x4
    bhs @L021de0bc
@L021de0ac:
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021de0b4:
    cmp r9, #0xc
    blo @L021de080
@L021de0bc:
    mov r9, #0x0
    ldr r6, =sStatLabels
    ldr r7, =sStatNames
    ldr r5, =sStatSigns
    b @L021de188
@L021de0d0:
    mov r0, r9, lsl #0x1
    ldrsh r1, [r7, r0]
    cmp r9, r8
    add r0, r4, #0xcc
    bhs @L021de12c
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r6, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r5, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    b @L021de170
@L021de12c:
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r6, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r5, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
@L021de170:
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021de188:
    cmp r9, #0x4
    blo @L021de0d0
    mov r9, #0x0
    ldr r11, =sStatValues
    ldr r5, =sDrops
    b @L021de394
@L021de1a0:
    add r0, sp, #0x164
    ldr r7, [r0, r9, lsl #0x2]
    add r0, sp, #0x48
    ldrb r1, [r0, r9]
    ldr r0, [r5, #0x14]
    add r1, r1, #0xc
    mov r1, r1, lsl #0x10
    mov r6, r1, asr #0x10
    mov r1, r6
    bl func_020e0434
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r2, r0
    ldr r1, =sStatLabels
    mov r3, r9, lsl #0x1
    ldrsh r1, [r1, r3]
    add r0, r4, #0xcc
    mov r3, #0xa
    bl _ZN6Layout7SetTextEsPKchh
    mov r0, r9, lsl #0x1
    ldrsh r10, [r11, r0]
    add r0, r4, #0xcc
    add r2, sp, #0x38
    mov r1, r10
    add r3, sp, #0x3a
    bl _ZN6Layout11GetPositionEsPsS0_
    sub r0, r6, #0xe
    cmp r0, #0x3
    addls pc, pc, r0, lsl #0x2
    b @L021de2c4
@L021de218:
    b @L021de228
    b @L021de228
    b @L021de228
    b @L021de228
@L021de228:
    ldr r0, [r5, #0x4]
    cmp r0, #0x0
    beq @L021de2a4
    ldr r0, [r5, #0x14]
    mov r1, #0x1a
    bl func_020e0434
    mov r1, #0x8
    str r1, [sp, #0x0]
    mov r1, #0xf
    str r1, [sp, #0x4]
    add r1, sp, #0x34
    str r1, [sp, #0x8]
    add r1, sp, #0x36
    str r1, [sp, #0xc]
    mov r1, #0x0
    str r1, [sp, #0x10]
    ldrsh r1, [sp, #0x38]
    mov r3, r0
    ldrsh r2, [sp, #0x3a]
    add r1, r1, #0x1
    mov r1, r1, lsl #0x10
    add r0, sp, #0x17c
    mov r1, r1, asr #0x10
    bl func_0204f41c
    mov r0, #0xf
    str r0, [sp, #0x0]
    ldrsh r1, [sp, #0x38]
    ldrsh r2, [sp, #0x3a]
    mov r3, r7
    add r0, sp, #0x17c
    bl DrawDecimal
@L021de2a4:
    mov r1, r10
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    b @L021de38c
@L021de2c4:
    mov r0, r7
    mov r1, #0x0
    bl _fls
    bhs @L021de324
    ldr r0, =sStatSigns
    mov r1, r9, lsl #0x1
    ldrsh r6, [r0, r1]
    add r0, r4, #0xcc
    mov r1, r6
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    ldr r0, [r5, #0x14]
    mov r1, #0x19
    bl func_020e0434
    mov r2, #0xf
    str r2, [sp, #0x0]
    mov r2, r0
    mov r1, r6
    add r0, r4, #0xcc
    mov r3, #0x8
    bl _ZN6Layout7SetTextEsPKchh
@L021de324:
    mov r0, r7
    bl _ffix
    bl func_020017b0
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r1, #0x1
    mov r2, r0
    mov r0, r9, lsl #0x1
    str r1, [sp, #0x4]
    mov r1, #0x3
    ldrsh r6, [r11, r0]
    str r1, [sp, #0x8]
    mov r1, #0x0
    str r1, [sp, #0xc]
    str r1, [sp, #0x10]
    add r0, r4, #0xcc
    mov r3, #0x8
    mov r1, r6
    bl _ZN6Layout9SetNumberEsihhhhhh
    mov r1, r6
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L021de38c:
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021de394:
    cmp r9, r8
    blo @L021de1a0
    ldr r0, =sDrops
    ldr r0, [r0, #0x4]
    cmp r0, #0x0
    beq @L021de3c4
    add r1, sp, #0x17c
    str r1, [r4, #0xd0]
    mov r1, #0x1
    add r0, r4, #0xcc
    strh r1, [r4, #0xde]
    bl _ZN6Layout4DrawEv
@L021de3c4:
    ldrsh r2, [sp, #0x30]
    ldrsh r3, [sp, #0x32]
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout18SetElementPositionEsss
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    b @L021df1b0
@L021de3f8:
    ldr r1, [r4, #0x4c]
    ldrsh r1, [r1, #0x18]
    bl func_020dd718
    cmp r0, #0x0
    add r0, r4, #0x700
    beq @L021de8b8
    ldrsb r5, [r0, #0x7a]
    ldr r6, [r4, #0x4c]
    add r7, sp, #0x26
    add r1, sp, #0x17c
    add r3, sp, #0x24
    add r0, r4, #0xcc
    mov r2, #0xb
    str r7, [sp, #0x0]
    bl TakeElement
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2d
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2e
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2c
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, sp, #0xbc
    mov r1, #0x30
    bl __clear
    add r0, sp, #0xec
    mov r1, #0x30
    bl __clear
    add r0, sp, #0x42
    mov r1, #0x6
    bl __clear
    add r1, sp, #0xbc
    mov r0, r5
    mov r2, #0x0
    bl GetMemberStats
    add r1, sp, #0xec
    mov r0, r6
    bl GetItemStats
    mov r8, #0x0
    add r0, sp, #0x11c
    mov r1, #0x18
    bl __clear
    mov r9, r8
    ldr r5, [sp, #0xc8]
    add r11, sp, #0xbc
    add r10, sp, #0xec
    b @L021de578
@L021de508:
    cmp r9, #0x3
    ldreq r0, [r6, #0x8]
    mov r7, #0x0
    moveq r0, r0, lsl #0x1c
    moveq r0, r0, lsr #0x1c
    cmpeq r0, #0x1
    bne @L021de534
    mov r0, r5
    mov r1, r7
    bl _fneq
    movne r7, #0x1
@L021de534:
    cmp r7, #0x0
    bne @L021de54c
    ldr r1, [r10, r9, lsl #0x2]
    mov r0, #0x0
    bl _fneq
    beq @L021de570
@L021de54c:
    ldr r2, [r11, r9, lsl #0x2]
    add r0, sp, #0x11c
    str r2, [r0, r8, lsl #0x2]
    add r0, sp, #0x42
    add r1, r8, #0x1
    strb r9, [r0, r8]
    and r8, r1, #0xff
    cmp r8, #0x4
    bhs @L021de580
@L021de570:
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021de578:
    cmp r9, #0xc
    blo @L021de508
@L021de580:
    mov r9, #0x0
    ldr r6, =sStatLabels2
    ldr r7, =sStatNames2
    ldr r5, =sStatSigns2
    b @L021de658
@L021de594:
    mov r0, r9, lsl #0x1
    ldrsh r1, [r7, r0]
    cmp r9, r8
    add r0, r4, #0xcc
    bhs @L021de5fc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r6, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r5, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    b @L021de64c
@L021de5fc:
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r6, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r9, lsl #0x1
    ldrsh r1, [r5, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
@L021de64c:
    strneb r1, [r0, #0x16]
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021de658:
    cmp r9, #0x4
    blo @L021de594
    mov r9, #0x0
    ldr r11, =sStatValues2
    ldr r5, =sDrops
    b @L021de854
@L021de670:
    add r0, sp, #0x11c
    ldr r7, [r0, r9, lsl #0x2]
    add r0, sp, #0x42
    ldrb r1, [r0, r9]
    ldr r0, [r5, #0x14]
    add r1, r1, #0xc
    mov r1, r1, lsl #0x10
    mov r6, r1, asr #0x10
    mov r1, r6
    bl func_020e0434
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r2, r0
    ldr r1, =sStatLabels2
    mov r3, r9, lsl #0x1
    ldrsh r1, [r1, r3]
    add r0, r4, #0xcc
    mov r3, #0xa
    bl _ZN6Layout7SetTextEsPKchh
    mov r0, r9, lsl #0x1
    ldrsh r10, [r11, r0]
    add r0, r4, #0xcc
    add r2, sp, #0x2c
    mov r1, r10
    add r3, sp, #0x2e
    bl _ZN6Layout11GetPositionEsPsS0_
    sub r0, r6, #0xe
    cmp r0, #0x3
    addls pc, pc, r0, lsl #0x2
    b @L021de794
@L021de6e8:
    b @L021de6f8
    b @L021de6f8
    b @L021de6f8
    b @L021de6f8
@L021de6f8:
    ldr r0, [r5, #0x4]
    cmp r0, #0x0
    beq @L021de774
    ldr r0, [r5, #0x14]
    mov r1, #0x1a
    bl func_020e0434
    mov r1, #0x8
    str r1, [sp, #0x0]
    mov r1, #0xf
    str r1, [sp, #0x4]
    add r1, sp, #0x28
    str r1, [sp, #0x8]
    add r1, sp, #0x2a
    str r1, [sp, #0xc]
    mov r1, #0x0
    str r1, [sp, #0x10]
    ldrsh r1, [sp, #0x2c]
    mov r3, r0
    ldrsh r2, [sp, #0x2e]
    add r1, r1, #0x1
    mov r1, r1, lsl #0x10
    add r0, sp, #0x17c
    mov r1, r1, asr #0x10
    bl func_0204f41c
    mov r0, #0xf
    str r0, [sp, #0x0]
    ldrsh r1, [sp, #0x2c]
    ldrsh r2, [sp, #0x2e]
    mov r3, r7
    add r0, sp, #0x17c
    bl DrawDecimal
@L021de774:
    mov r1, r10
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    b @L021de7fc
@L021de794:
    mov r0, r7
    bl _ffix
    bl func_020017b0
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r1, #0x1
    mov r2, r0
    mov r0, r9, lsl #0x1
    str r1, [sp, #0x4]
    mov r1, #0x3
    ldrsh r6, [r11, r0]
    str r1, [sp, #0x8]
    mov r1, #0x0
    str r1, [sp, #0xc]
    str r1, [sp, #0x10]
    add r0, r4, #0xcc
    mov r3, #0x8
    mov r1, r6
    bl _ZN6Layout9SetNumberEsihhhhhh
    mov r1, r6
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L021de7fc:
    ldr r0, =sStatSigns2
    mov r1, r9, lsl #0x1
    ldrsh r6, [r0, r1]
    add r0, r4, #0xcc
    mov r1, r6
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    ldr r0, [r5, #0x14]
    mov r1, #0x22
    bl func_020e0434
    mov r2, #0xf
    str r2, [sp, #0x0]
    mov r2, r0
    mov r1, r6
    add r0, r4, #0xcc
    mov r3, #0x8
    bl _ZN6Layout7SetTextEsPKchh
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021de854:
    cmp r9, r8
    blo @L021de670
    ldr r0, =sDrops
    ldr r0, [r0, #0x4]
    cmp r0, #0x0
    beq @L021de884
    add r1, sp, #0x17c
    str r1, [r4, #0xd0]
    mov r1, #0x1
    add r0, r4, #0xcc
    strh r1, [r4, #0xde]
    bl _ZN6Layout4DrawEv
@L021de884:
    ldrsh r2, [sp, #0x24]
    ldrsh r3, [sp, #0x26]
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout18SetElementPositionEsss
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    b @L021df1b0
@L021de8b8:
    ldrsb r0, [r0, #0x7a]
    ldr r1, [r4, #0x4c]
    bl func_020dd4c4
    cmp r0, #0x0
    add r1, sp, #0x17c
    mov r2, #0xb
    bne @L021df01c
    add r0, r4, #0x700
    ldrsb r6, [r0, #0x7a]
    ldr r5, [r4, #0x4c]
    add r7, sp, #0x1a
    add r3, sp, #0x18
    add r0, r4, #0xcc
    str r7, [sp, #0x0]
    bl TakeElement
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2d
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2e
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2c
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, sp, #0x50
    mov r1, #0x30
    bl __clear
    add r1, sp, #0x50
    mov r0, r6
    mov r2, #0x0
    bl GetMemberStats
    add r0, sp, #0x80
    mov r1, #0x30
    bl __clear
    add r1, sp, #0x80
    mov r0, r6
    mov r2, r5
    bl GetMemberStats
    add r0, sp, #0xb0
    mov r1, #0xc
    mov r6, #0x0
    bl __clear
    cmp r5, #0x0
    beq @L021de9c0
    ldrsh r0, [r5, #0x18]
    cmp r0, #0x0
    ldrgt r6, [r5, #0x0]
@L021de9c0:
    cmp r6, #0x0
    beq @L021deb28
    ldr r0, [r6, #0x8]
    mov r0, r0, lsl #0x16
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xb0]
    ldr r0, [r6, #0x8]
    mov r0, r0, lsl #0xc
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xb1]
    ldr r0, [r6, #0x8]
    mov r0, r0, lsl #0x2
    mov r0, r0, lsr #0x16
    bl _ffltu
    ldr r1, =0x41200000
    bl _fdiv
    mov r1, r0
    mov r0, #0x0
    bl _fneq
    movne r0, #0x1
    strneb r0, [sp, #0xb2]
    ldr r0, [r6, #0xc]
    mov r0, r0, lsl #0x16
    mov r0, r0, lsr #0x16
    bl _ffltu
    ldr r1, =0x41200000
    bl _fdiv
    mov r1, r0
    mov r0, #0x0
    bl _fneq
    movne r0, #0x1
    strneb r0, [sp, #0xb3]
    ldr r0, [r6, #0xc]
    mov r0, r0, lsl #0xc
    mov r0, r0, lsr #0x16
    bl _ffltu
    ldr r1, =0x41200000
    bl _fdiv
    mov r1, r0
    mov r0, #0x0
    bl _fneq
    movne r0, #0x1
    strneb r0, [sp, #0xb4]
    ldr r0, [r6, #0x10]
    mov r0, r0, lsl #0x16
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xb6]
    ldr r0, [r6, #0x10]
    mov r0, r0, lsl #0xc
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xb7]
    ldr r0, [r6, #0x10]
    mov r0, r0, lsl #0x2
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xb8]
    ldr r0, [r6, #0x14]
    mov r0, r0, lsl #0x16
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xb9]
    ldr r0, [r6, #0x14]
    mov r0, r0, lsl #0xc
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xba]
    ldr r0, [r6, #0x14]
    mov r0, r0, lsl #0x2
    movs r0, r0, asr #0x16
    movne r0, #0x1
    strneb r0, [sp, #0xbb]
    ldr r0, [r5, #0x8]
    mov r0, r0, lsl #0x1c
    mov r0, r0, lsr #0x1c
    cmp r0, #0x1
    bne @L021deb28
    ldr r0, [sp, #0x5c]
    mov r1, #0x0
    bl _fneq
    bne @L021deb20
    ldr r0, [sp, #0x8c]
    mov r1, #0x0
    bl _fneq
    beq @L021deb28
@L021deb20:
    mov r0, #0x1
    strb r0, [sp, #0xb3]
@L021deb28:
    add r0, sp, #0x3c
    mov r1, #0x6
    bl __clear
    mov r8, #0x0
    mov r9, r8
    add r7, sp, #0xb0
    add r10, sp, #0x3c
    add r6, sp, #0x50
    add r5, sp, #0x80
    mov r11, r8
    b @L021deb98
@L021deb54:
    ldrb r0, [r7, r9]
    cmp r0, #0x0
    bne @L021deb7c
    ldr r0, [r6, r9, lsl #0x2]
    ldr r1, [r5, r9, lsl #0x2]
    bl _fsub
    mov r1, r0
    mov r0, r11
    bl _fneq
    beq @L021deb90
@L021deb7c:
    add r0, r8, #0x1
    strb r9, [r10, r8]
    and r8, r0, #0xff
    cmp r8, #0x4
    bhs @L021deba0
@L021deb90:
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021deb98:
    cmp r9, #0xc
    blo @L021deb54
@L021deba0:
    mov r7, #0x0
    ldr r6, =sStatNames3
    ldr r5, =sStatLabels3
    b @L021dec34
@L021debb0:
    mov r0, r7, lsl #0x1
    ldrsh r1, [r6, r0]
    cmp r7, r8
    add r0, r4, #0xcc
    bhs @L021debf8
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r7, lsl #0x1
    ldrsh r1, [r5, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    b @L021dec28
@L021debf8:
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r7, lsl #0x1
    ldrsh r1, [r5, r0]
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
@L021dec28:
    strneb r1, [r0, #0x16]
    add r0, r7, #0x1
    and r7, r0, #0xff
@L021dec34:
    cmp r7, #0x4
    blo @L021debb0
    mov r9, #0x0
    ldr r5, =sDrops
    b @L021def7c
@L021dec48:
    add r0, sp, #0x3c
    ldrb r7, [r0, r9]
    ldr r0, [r5, #0x14]
    add r1, r7, #0xc
    mov r1, r1, lsl #0x10
    mov r10, r1, asr #0x10
    mov r1, r10
    bl func_020e0434
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r2, r0
    ldr r1, =sStatLabels3
    mov r3, r9, lsl #0x1
    ldrsh r1, [r1, r3]
    add r0, r4, #0xcc
    mov r3, #0xa
    bl _ZN6Layout7SetTextEsPKchh
    ldr r0, =sStatValues3
    mov r1, r9, lsl #0x1
    ldrsh r11, [r0, r1]
    add r0, r4, #0xcc
    add r2, sp, #0x20
    mov r1, r11
    add r3, sp, #0x22
    bl _ZN6Layout11GetPositionEsPsS0_
    add r0, sp, #0x50
    ldr r6, [r0, r7, lsl #0x2]
    sub r0, r10, #0xe
    cmp r0, #0x3
    addls pc, pc, r0, lsl #0x2
    b @L021ded70
@L021decc4:
    b @L021decd4
    b @L021decd4
    b @L021decd4
    b @L021decd4
@L021decd4:
    ldr r0, [r5, #0x4]
    cmp r0, #0x0
    beq @L021ded50
    ldr r0, [r5, #0x14]
    mov r1, #0x1a
    bl func_020e0434
    mov r1, #0x8
    str r1, [sp, #0x0]
    mov r1, #0xf
    str r1, [sp, #0x4]
    add r1, sp, #0x1c
    str r1, [sp, #0x8]
    add r1, sp, #0x1e
    str r1, [sp, #0xc]
    mov r1, #0x0
    str r1, [sp, #0x10]
    ldrsh r1, [sp, #0x20]
    mov r3, r0
    ldrsh r2, [sp, #0x22]
    add r1, r1, #0x1
    mov r1, r1, lsl #0x10
    add r0, sp, #0x17c
    mov r1, r1, asr #0x10
    bl func_0204f41c
    mov r0, #0xf
    str r0, [sp, #0x0]
    ldrsh r1, [sp, #0x20]
    ldrsh r2, [sp, #0x22]
    add r0, sp, #0x17c
    mov r3, r6
    bl DrawDecimal
@L021ded50:
    mov r1, r11
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    b @L021deddc
@L021ded70:
    mov r0, r6
    bl _ffix
    bl func_020017b0
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r1, #0x1
    str r1, [sp, #0x4]
    mov r1, #0x3
    str r1, [sp, #0x8]
    mov r1, #0x0
    str r1, [sp, #0xc]
    mov r2, r0
    str r1, [sp, #0x10]
    ldr r0, =sStatValues3
    mov r1, r9, lsl #0x1
    ldrsh r11, [r0, r1]
    add r0, r4, #0xcc
    mov r3, #0x8
    mov r1, r11
    bl _ZN6Layout9SetNumberEsihhhhhh
    mov r1, r11
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L021deddc:
    ldr r0, [r5, #0x14]
    mov r1, #0x20
    bl func_020e0434
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r2, r0
    ldr r1, =sStatArrows3
    mov r3, r9, lsl #0x1
    ldrsh r1, [r1, r3]
    add r0, r4, #0xcc
    mov r3, #0x8
    bl _ZN6Layout7SetTextEsPKchh
    add r0, sp, #0x80
    ldr r11, [r0, r7, lsl #0x2]
    mov r7, #0x9
    mov r0, r6
    mov r1, r11
    bl _feq
    moveq r7, #0xf
    beq @L021dee3c
    mov r0, r6
    mov r1, r11
    bl _fls
    movlo r7, #0x5
@L021dee3c:
    ldr r0, =sStatNewValues3
    mov r1, r9, lsl #0x1
    ldrsh r6, [r0, r1]
    add r0, r4, #0xcc
    add r2, sp, #0x20
    mov r1, r6
    add r3, sp, #0x22
    bl _ZN6Layout11GetPositionEsPsS0_
    sub r0, r10, #0xe
    cmp r0, #0x3
    addls pc, pc, r0, lsl #0x2
    b @L021def0c
@L021dee6c:
    b @L021dee7c
    b @L021dee7c
    b @L021dee7c
    b @L021dee7c
@L021dee7c:
    ldr r0, [r5, #0x4]
    cmp r0, #0x0
    beq @L021deeec
    ldr r0, [r5, #0x14]
    mov r1, #0x1a
    bl func_020e0434
    mov r1, #0x8
    stmia sp, {r1, r7}
    add r1, sp, #0x1c
    str r1, [sp, #0x8]
    add r1, sp, #0x1e
    str r1, [sp, #0xc]
    mov r1, #0x0
    str r1, [sp, #0x10]
    ldrsh r1, [sp, #0x20]
    mov r3, r0
    ldrsh r2, [sp, #0x22]
    add r1, r1, #0x1
    mov r1, r1, lsl #0x10
    add r0, sp, #0x17c
    mov r1, r1, asr #0x10
    bl func_0204f41c
    str r7, [sp, #0x0]
    ldrsh r1, [sp, #0x20]
    ldrsh r2, [sp, #0x22]
    mov r3, r11
    add r0, sp, #0x17c
    bl DrawDecimal
@L021deeec:
    mov r1, r6
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    b @L021def74
@L021def0c:
    mov r0, r11
    bl _ffix
    bl func_020017b0
    mov r2, r0
    str r7, [sp, #0x0]
    mov r1, #0x1
    str r1, [sp, #0x4]
    mov r1, #0x3
    str r1, [sp, #0x8]
    mov r1, #0x0
    str r1, [sp, #0xc]
    str r1, [sp, #0x10]
    ldr r0, =sStatNewValues3
    mov r1, r9, lsl #0x1
    ldrsh r6, [r0, r1]
    add r0, r4, #0xcc
    mov r3, #0x8
    mov r1, r6
    bl _ZN6Layout9SetNumberEsihhhhhh
    mov r1, r6
    add r0, r4, #0xcc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L021def74:
    add r0, r9, #0x1
    and r9, r0, #0xff
@L021def7c:
    cmp r9, r8
    blo @L021dec48
    ldr r0, =sDrops
    ldr r0, [r0, #0x4]
    cmp r0, #0x0
    beq @L021defac
    add r1, sp, #0x17c
    str r1, [r4, #0xd0]
    mov r1, #0x1
    add r0, r4, #0xcc
    strh r1, [r4, #0xde]
    bl _ZN6Layout4DrawEv
@L021defac:
    ldrsh r2, [sp, #0x18]
    ldrsh r3, [sp, #0x1a]
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout18SetElementPositionEsss
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    b @L021df1b0
@L021df01c:
    add r5, sp, #0x16
    add r3, sp, #0x14
    add r0, r4, #0xcc
    str r5, [sp, #0x0]
    bl TakeElement
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2c
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2c
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x8
    strneb r1, [r0, #0x16]
    ldr r0, =sDrops
    mov r1, #0x21
    ldr r0, [r0, #0x14]
    bl func_020e0434
    mov r2, r0
    mov r5, #0xf
    add r0, r4, #0xcc
    mov r1, #0x2c
    mov r3, #0xa
    str r5, [sp, #0x0]
    bl _ZN6Layout7SetTextEsPKchh
    add r0, r4, #0xcc
    mov r1, #0xa
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0xc
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0xd
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0xe
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2d
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r4, #0xcc
    mov r1, #0x2e
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    ldr r0, =sDrops
    ldr r0, [r0, #0x4]
    cmp r0, #0x0
    beq @L021df180
    add r1, sp, #0x17c
    str r1, [r4, #0xd0]
    mov r1, #0x1
    add r0, r4, #0xcc
    strh r1, [r4, #0xde]
    bl _ZN6Layout4DrawEv
@L021df180:
    ldrsh r2, [sp, #0x14]
    ldrsh r3, [sp, #0x16]
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout18SetElementPositionEsss
    add r0, r4, #0xcc
    mov r1, #0xb
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L021df1b0:
    ldr r1, [r4, #0x768]
    mov r3, #0x0
    cmp r1, #0x0
    beq @L021df1dc
    ldr r2, =sDrops
    add r0, sp, #0x17c
    ldr r2, [r2, #0xc]
    mov r2, r2, lsl #0x10
    mov r2, r2, lsr #0x10
    bl LoadCanvas
    b @L021df210
@L021df1dc:
    ldr r0, =sDrops
    ldr r1, [r4, #0x75c]
    ldr r2, [r0, #0xc]
    add r0, sp, #0x17c
    mov r2, r2, lsl #0x10
    mov r2, r2, lsr #0x10
    bl LoadCanvas
    ldr r1, [r4, #0x75c]
    str r1, [r4, #0x768]
    str r0, [r4, #0x76c]
    ldr r1, [r4, #0x75c]
    add r0, r1, r0
    str r0, [r4, #0x75c]
@L021df210:
    add sp, sp, #0x25c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// Draws the vocations that can use the item, and grays out the others
// NONMATCHING: the C matches 52.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original keeps the offset of the tile on the stack, and checks the vocation with other instructions
#ifdef NONMATCHING
void ItemInfoWindow::DrawResistances()
{
    Canvas canvas;
    func_0204c684(&canvas);
    if (!SetUpCanvas(&canvas, 0, 0, 7, 0x10))
        return;
    int gray = 0;
    PartModelInfo* info = item_->model_;
    if (info != NULL)
    {
        SHOW_ELEMENT(&layout_, 0x1b);
        unsigned char vocations[13];
        memcpy(vocations, sVocations, sizeof(vocations));
        void* flags = func_0205ec34();
        for (unsigned char i = 7; i < 13; i++)
        {
            if (func_0206dfb0(flags, (char*)flags + 0x8c, i + 0x113f))
                vocations[i] = 1;
        }
        unsigned char i = 1;
        unsigned char index = 0;
        for (; i < 13; index++, i++)
        {
            if (!vocations[i])
                continue;
            int color = 0xe;
            unsigned int type = info->unk_0_7;
            if (type != 0 ? func_020dd19c(i, type) : (unsigned short)(1 << index) & info->unk_4_0)
                color = 0xf;
            if (color == 0xe)
                gray |= 1 << index;
            short icon = sVocationElements[index];
            layout_.SetType(icon, 3);
            layout_.SetIcon(icon, i);
        }
        short y;
        short x;
        TakeElement(&layout_, &canvas, 0x1b, &x, &y);
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0x1b, x, y);
        HIDE_ELEMENT(&layout_, 0x1b);
    }
    unsigned int size = LoadCanvas(&canvas, vramOffset_, sPalette2, 0);
    if (&layout_ != NULL)
    {
        unsigned short* base = GetScreenBase(sWindow->screen_, 0);
        if (base != NULL)
        {
            for (int i = 0; i < 12; i++)
            {
                if (!(gray & (1 << i)))
                    continue;
                short x = 0;
                short y = 0;
                layout_.GetPosition(sVocationIcons[i], &x, &y);
                int tileX = x >> 3;
                int tileY = y >> 3;
                x = tileX;
                y = tileY;
                for (int j = 0; j < 2; j++)
                {
                    int column = tileX;
                    unsigned short* line = base + (tileY << 5);
                    for (int k = 0; k < 2; k++)
                    {
                        unsigned short value = line[column] & 0xfff;
                        value |= 0x1000;
                        CleanInvalidateCacheRange(&value, 2);
                        line[column++] = value;
                    }
                    tileY++;
                }
            }
        }
    }
    vramOffset_ += size;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN6Layout11GetPositionEsPsS0_(); // Layout::GetPosition
    void _ZN6Layout7SetIconEsi(); // Layout::SetIcon
    void _ZN6Layout7SetTypeEsh(); // Layout::SetType
}

asm void ItemInfoWindow::DrawResistances()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x10c
    mov r10, r0
    add r0, sp, #0x2c
    bl func_0204c684
    mov r1, #0x0
    mov r4, #0x10
    add r0, sp, #0x2c
    mov r2, r1
    mov r3, #0x7
    str r4, [sp, #0x0]
    bl SetUpCanvas
    cmp r0, #0x0
    beq @L021df53c
    ldr r0, [r10, #0x4c]
    mov r4, #0x0
    ldr r9, [r0, #0x0]
    cmp r9, #0x0
    beq @L021df3fc
    add r0, r10, #0xcc
    mov r1, #0x1b
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    mov r2, #0xd
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    ldr r1, =sVocations
    add r0, sp, #0x1e
    bl memcpy
    bl func_0205ec34
    mov r8, r0
    mov r7, #0x7
    mov r6, #0x1
    add r5, sp, #0x1e
    b @L021df2cc
@L021df2a8:
    add r2, r7, #0x3f
    mov r0, r8
    add r1, r8, #0x8c
    add r2, r2, #0x1100
    bl func_0206dfb0
    cmp r0, #0x0
    add r0, r7, #0x1
    strneb r6, [r5, r7]
    and r7, r0, #0xff
@L021df2cc:
    cmp r7, #0xd
    blo @L021df2a8
    mov r6, #0x1
    mov r7, #0x0
    mov r11, r6
    add r5, sp, #0x1e
    b @L021df380
@L021df2e8:
    ldrb r0, [r5, r6]
    cmp r0, #0x0
    beq @L021df370
    ldr r0, [r9, #0x0]
    mov r8, #0xe
    mov r0, r0, lsl #0x15
    movs r0, r0, lsr #0x1c
    beq @L021df31c
    and r1, r0, #0xff
    mov r0, r6
    bl func_020dd19c
    cmp r0, #0x0
    b @L021df334
@L021df31c:
    mov r0, r11, lsl r7
    ldr r1, [r9, #0x4]
    mov r0, r0, lsl #0x10
    mov r1, r1, lsl #0x14
    mov r0, r0, lsr #0x10
    tst r0, r1, lsr #0x14
@L021df334:
    movne r8, #0xf
    cmp r8, #0xe
    moveq r0, #0x1
    orreq r4, r4, r0, lsl r7
    ldr r0, =sVocationElements
    mov r1, r7, lsl #0x1
    ldrsh r8, [r0, r1]
    add r0, r10, #0xcc
    mov r2, #0x3
    mov r1, r8
    bl _ZN6Layout7SetTypeEsh
    mov r1, r8
    add r0, r10, #0xcc
    mov r2, r6
    bl _ZN6Layout7SetIconEsi
@L021df370:
    add r0, r7, #0x1
    and r7, r0, #0xff
    add r0, r6, #0x1
    and r6, r0, #0xff
@L021df380:
    cmp r6, #0xd
    blo @L021df2e8
    add r5, sp, #0x1c
    add r1, sp, #0x2c
    add r3, sp, #0x1a
    add r0, r10, #0xcc
    mov r2, #0x1b
    str r5, [sp, #0x0]
    bl TakeElement
    ldr r0, =sDrops
    ldr r0, [r0, #0x4]
    cmp r0, #0x0
    beq @L021df3cc
    add r1, sp, #0x2c
    str r1, [r10, #0xd0]
    mov r1, #0x1
    add r0, r10, #0xcc
    strh r1, [r10, #0xde]
    bl _ZN6Layout4DrawEv
@L021df3cc:
    ldrsh r2, [sp, #0x1a]
    ldrsh r3, [sp, #0x1c]
    add r0, r10, #0xcc
    mov r1, #0x1b
    bl _ZN6Layout18SetElementPositionEsss
    add r0, r10, #0xcc
    mov r1, #0x1b
    bl _ZN6Layout11FindElementEs
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
@L021df3fc:
    ldr r0, =sDrops
    ldr r1, [r10, #0x75c]
    ldr r2, [r0, #0x10]
    add r0, sp, #0x2c
    mov r2, r2, lsl #0x10
    mov r2, r2, lsr #0x10
    mov r3, #0x0
    bl LoadCanvas
    str r0, [sp, #0xc]
    adds r0, r10, #0xcc
    beq @L021df52c
    ldr r0, =sDrops
    mov r1, #0x0
    ldr r0, [r0, #0x20]
    add r0, r0, #0x700
    ldrsb r0, [r0, #0x7c]
    bl GetScreenBase
    str r0, [sp, #0x4]
    cmp r0, #0x0
    beq @L021df52c
    mov r9, #0x0
    b @L021df524
@L021df454:
    mov r0, #0x1
    tst r4, r0, lsl r9
    beq @L021df520
    ldr r0, =sVocationIcons
    mov r1, r9, lsl #0x1
    ldrsh r1, [r0, r1]
    mov r0, #0x0
    add r2, sp, #0x14
    add r3, sp, #0x16
    strh r0, [sp, #0x14]
    strh r0, [sp, #0x16]
    add r0, r10, #0xcc
    bl _ZN6Layout11GetPositionEsPsS0_
    ldrsh r0, [sp, #0x14]
    ldrsh r1, [sp, #0x16]
    mov r6, #0x0
    mov r0, r0, asr #0x3
    str r0, [sp, #0x8]
    mov r5, r1, asr #0x3
    mov r0, r0
    strh r0, [sp, #0x14]
    strh r5, [sp, #0x16]
    b @L021df518
@L021df4b0:
    ldr r0, [sp, #0x4]
    ldr r7, [sp, #0x8]
    mov r8, #0x0
    add r11, r0, r5, lsl #0x6
    b @L021df508
@L021df4c4:
    mov r0, r7, lsl #0x1
    ldrh r3, [r11, r0]
    ldr r2, =0xfff
    str r0, [sp, #0x10]
    and r2, r3, r2
    strh r2, [sp, #0x18]
    ldrh r2, [sp, #0x18]
    add r0, sp, #0x18
    mov r1, #0x2
    orr r2, r2, #0x1000
    strh r2, [sp, #0x18]
    bl CleanInvalidateCacheRange
    ldrh r1, [sp, #0x18]
    ldr r0, [sp, #0x10]
    add r7, r7, #0x1
    add r8, r8, #0x1
    strh r1, [r11, r0]
@L021df508:
    cmp r8, #0x2
    blt @L021df4c4
    add r5, r5, #0x1
    add r6, r6, #0x1
@L021df518:
    cmp r6, #0x2
    blt @L021df4b0
@L021df520:
    add r9, r9, #0x1
@L021df524:
    cmp r9, #0xc
    blt @L021df454
@L021df52c:
    ldr r1, [r10, #0x75c]
    ldr r0, [sp, #0xc]
    add r0, r1, r0
    str r0, [r10, #0x75c]
@L021df53c:
    add sp, sp, #0x10c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void ItemInfoWindow::DrawDescription()
{
    Canvas canvas;
    func_0204c684(&canvas);
    if (SetUpCanvas(&canvas, 0, 0, 0xe, 8))
    {
        PartEntry* item = item_;
        if (item != NULL)
        {
            short group = 0x14;
            short text = 4;
            if (IsEquipment(item))
            {
                group = 0x1c;
                text = 7;
            }
            char formatted[0x100] = {0};
            func_02046608(func_020421a0(), 10, description_, formatted, 0x68, 0, 0);
            layout_.SetText(text, formatted, 10, 15);
            SHOW_ELEMENT(&layout_, group);
            short y;
            short x;
            TakeElement(&layout_, &canvas, group, &x, &y);
            if (sBuffer != NULL)
            {
                layout_.SetCanvas(&canvas);
                layout_.textHeight_ = 0xe;
                layout_.Draw();
            }
            layout_.SetElementPosition(group, x, y);
            HIDE_ELEMENT(&layout_, group);
        }
        vramOffset_ += LoadCanvas(&canvas, vramOffset_, sPalette3, 0);
    }
    if (IsEquipment(item_))
        return;
    if (SetUpCanvas(&canvas, 0, 0, 8, 2))
    {
        PartEntry* item = item_;
        SHOW_ELEMENT(&layout_, 0x10);
        if (item->category_ == 9 || func_020de194(item) == 0)
        {
            HIDE_ELEMENT(&layout_, 5);
            HIDE_ELEMENT(&layout_, 0x17);
            SHOW_ELEMENT(&layout_, 0x19);
        }
        else
        {
            layout_.SetNumber(5, func_020de194(item), 8, 15, 1, 6, 0, 0);
            SHOW_ELEMENT(&layout_, 5);
            SHOW_ELEMENT(&layout_, 0x17);
            HIDE_ELEMENT(&layout_, 0x19);
        }
        short y;
        short x;
        TakeElement(&layout_, &canvas, 0x10, &x, &y);
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0x10, x, y);
        HIDE_ELEMENT(&layout_, 0x10);
        vramOffset_ += LoadCanvas(&canvas, vramOffset_, sPalette3, 0);
    }
    if (SetUpCanvas(&canvas, 0, 0, 8, 2))
    {
        PartEntry* item = item_;
        SHOW_ELEMENT(&layout_, 0x12);
        unsigned short price;
        if (item->category_ == 9 || (price = item->price_) == 0)
        {
            HIDE_ELEMENT(&layout_, 6);
            HIDE_ELEMENT(&layout_, 0x18);
            SHOW_ELEMENT(&layout_, 0x1a);
        }
        else
        {
            layout_.SetNumber(6, price, 8, 15, 1, 6, 0, 0);
            SHOW_ELEMENT(&layout_, 6);
            SHOW_ELEMENT(&layout_, 0x18);
            HIDE_ELEMENT(&layout_, 0x1a);
        }
        short y;
        short x;
        TakeElement(&layout_, &canvas, 0x12, &x, &y);
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0x12, x, y);
        HIDE_ELEMENT(&layout_, 0x12);
        vramOffset_ += LoadCanvas(&canvas, vramOffset_, sPalette3, 0);
    }
}

void ItemInfoWindow::Draw()
{
    UpdateLoad();
    if (windowSprites_ != 2)
        return;
    if (flags_ & ITEM_INFO_WINDOW_NAMES)
    {
        SetVisiblePlanes(GetVisiblePlanes() | 1);
        return;
    }
    SetVisiblePlanes(GetVisiblePlanes() & ~1);
}

void ItemInfoWindow::UpdateLoad()
{
    if (itemId_ != nextItemId_)
        SetItem(nextItemId_);
    if (!(flags_ & ITEM_INFO_WINDOW_LOAD))
        return;
    if (mode_ == 1 && !inMenu_)
    {
        CANCEL_TASKS();
        flags_ |= ITEM_INFO_WINDOW_LOAD;
        loadStep_ = 0;
        return;
    }
    BackgroundLoader::GetInstance();
    while (loadStep_ >= 0 && sSteps[loadStep_] != NULL)
    {
        int previous = loadStep_;
        loadStep_ = (this->*sSteps[loadStep_])();
        if (loadStep_ < 0)
        {
            flags_ &= ~ITEM_INFO_WINDOW_LOAD;
            CANCEL_TASKS();
            return;
        }
        if (previous == loadStep_)
            return;
    }
}

int ItemInfoWindow::Load_Background()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (names_ != NULL)
        nextItem_ = func_020dedd0(names_, itemId_);
    int rare = 0;
    if (nextItem_ != NULL && nextItem_->rank_ == 5)
        rare = 1;
    sSparkles.Initialize(rare);
    unsigned char kind = GetBackgroundKind(nextItem_);
    if (kind == backgroundKind_)
    {
        vramOffset_ = 0x3800;
        if (mode_ == 1)
            vramOffset_ = 0x2800;
        namesOffset_ = 0;
        statsOffset_ = 0;
        DrawItemName();
        SetUpLayout(&layout_, nextItem_);
        item_ = nextItem_;
        nextItem_ = NULL;
        if (screen_ == 1)
        {
            int layers = 0x12;
            if (kind != 0)
                layers |= 1;
            REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | (layers << 8);
        }
        flags_ |= ITEM_INFO_WINDOW_LAYOUT;
        return 2;
    }
    char path[0x40] = {0};
    char name[0x40] = {0};
    int gp2 = 0;
    unsigned char background;
    if (kind == 0 && (background = background_) != 0)
    {
        switch (background)
        {
        case 1:
            sprintf(path, STRING(0x81, "data/ani/bg_iidc.pac"));
            break;
        case 2:
            sprintf(path, STRING(0x96, "data/ani/bg_iilist.pac"));
            break;
        }
    }
    else if ((flags_ & ITEM_INFO_WINDOW_CHANGE) && (background_ == 0 || task_ > 0))
    {
        sprintf(path, STRING(0xad, "data/ani/bglii2%d.gp2"), kind);
        sprintf(name, STRING(0xc3, "bglii2%d_<LG>.pac"), kind);
        gp2 = 1;
    }
    else
    {
        sprintf(path, STRING(0xd5, "data/ani/bgii2%d.gp2"), kind);
        sprintf(name, STRING(0xea, "bgii2%d_<LG>.pac"), kind);
        gp2 = 1;
    }
    if (gp2)
        task_ = loader->QueueLoadFileInGP2(path, name, NULL);
    else
        task_ = loader->QueueLoadFile(path, NULL);
    return 1;
}

int ItemInfoWindow::Load_BackgroundWait()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loader->GetTaskStatus(task_))
    {
        unsigned char kind = GetBackgroundKind(nextItem_);
        void* archive;
        const void* file;
        unsigned int archiveSize;
        unsigned int size;
        char* name;
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        if (archive != NULL && archiveSize != 0)
        {
            BackgroundGraphics background;
            func_0204af64(&background);
            signed char screen = screen_;
            if (screen == 1)
            {
                background.unk_1c_0_ = screen;
                background.unk_1c_4_ = 1;
            }
            else
            {
                background.unk_1c_0_ = screen;
                background.unk_1c_4_ = 3;
            }
            func_0204b5b4(&background, 3);
            func_0204b11c(&background, 0);
            func_0204b5e8(&background, 0, 0);
            if (screen_ == 1)
            {
                int layers = 0x12;
                if (kind != 0)
                    layers |= 1;
                REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | (layers << 8);
            }
            if (kind == 0 && background_ != 0)
            {
                int count = func_02046900(archive);
                for (int i = 0; i < count; i = (unsigned char)(i + 1))
                {
                    file = func_020467f0(archive, i, &name, &size);
                    if (file != NULL)
                    {
                        func_0204b2e0(&background, (void*)file);
                        func_0204b3a0(&background, (void*)file);
                        layout_.Load(&allocator_, (void*)file, size);
                    }
                }
            }
            else
            {
                layout_.Initialize();
                allocator_.Reset();
                for (unsigned char i = 0; i < 4; i++)
                {
                    if (!FindFilesInNarcBySubstring(archive, sExtensions[i], &file, &size, 1))
                        continue;
                    if (i != 3)
                    {
                        func_0204b2e0(&background, (void*)file);
                        func_0204b3a0(&background, (void*)file);
                    }
                    else
                    {
                        layout_.Load(&allocator_, (void*)file, size);
                    }
                }
            }
            vramOffset_ = 0x3800;
            if (mode_ == 1)
                vramOffset_ = 0x2800;
            namesOffset_ = 0;
            statsOffset_ = 0;
            if (screen_ == 1)
            {
                memset((void*)GetSubBG0ScreenBase(), 0, 0x800);
                if (nextItem_ != NULL)
                {
                    DrawItemName();
                    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1300;
                }
            }
            else
            {
                memset((void*)GetMainBG2ScreenBase(), 0, 0x800);
                if (nextItem_ != NULL)
                    DrawItemName();
            }
            SetUpLayout(&layout_, nextItem_);
        }
        backgroundKind_ = kind;
        loader->RemoveTask(task_);
        task_ = -1;
        item_ = nextItem_;
        nextItem_ = NULL;
        unsigned short flags = flags_;
        if ((flags & ITEM_INFO_WINDOW_FADE) && !(flags & ITEM_INFO_WINDOW_CHANGE))
            flags_ = flags | ITEM_INFO_WINDOW_FADE_IN;
        for (int i = 0; i < 7; i++)
            tasks_[i] = -1;
        flags_ |= ITEM_INFO_WINDOW_LAYOUT | ITEM_INFO_WINDOW_CHANGE;
        int result;
        if (item_ == NULL)
            result = -1;
        else
            result = 2;
        return result;
    }
    return 1;
}

int ItemInfoWindow::Load_Sprite()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    int loading = 0;
    if (item_ != NULL)
    {
        char path[0x40] = {0};
        if (flags_ & ITEM_INFO_WINDOW_QUEST)
            sprintf(path, STRING(0xfb, "data/ani/al_qu.spr"), item_->letter_, func_020de234(item_, 0));
        else
            sprintf(path, STRING(0x10e, "data/ani/d_%c%03d.spr"), item_->letter_, func_020de234(item_, 0));
        tasks_[0] = loader->QueueLoadFile(path, NULL);
        loading = 1;
    }
    if (loading)
        return 4;
    flags_ |= ITEM_INFO_WINDOW_NO_SPRITE;
    func_02075d64(nextSprite_);
    return 6;
}

int ItemInfoWindow::Load_SpriteWait()
{
    if (tasks_[0] == -1)
        return 5;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loader->GetTaskStatus(tasks_[0]))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(tasks_[0], &file, &size);
        func_02075d64(nextSprite_);
        if (file != NULL && size != 0)
        {
            nextSpriteAllocator_->Reset();
            func_02076080(nextSprite_, nextSpriteAllocator_, file, size);
            flags_ &= ~ITEM_INFO_WINDOW_NO_SPRITE;
        }
        loader->RemoveTask(tasks_[0]);
        tasks_[0] = -1;
        Unknown_02075cdc* sprite = sprite_;
        sprite_ = nextSprite_;
        nextSprite_ = sprite;
        SafeAllocator* allocator = spriteAllocator_;
        spriteAllocator_ = nextSpriteAllocator_;
        nextSpriteAllocator_ = allocator;
        flags_ |= ITEM_INFO_WINDOW_SPRITE;
        return 5;
    }
    return 3;
}

int ItemInfoWindow::Load_Layout()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (names_ != NULL)
        item_ = func_020dedd0(names_, itemId_);
    if (item_ != NULL)
    {
        signed char equipment = IsEquipment(item_) ? 1 : 0;
        if (equipmentLayout_ != equipment)
        {
            layout_.Initialize();
            if (IsEquipment(item_))
                tasks_[1] = loader->QueueLoadFile(STRING(0x124, "data/ani/lay_iie.lia"), NULL);
            else
                tasks_[1] = loader->QueueLoadFile(STRING(0x139, "data/ani/lay_iiu.lia"), NULL);
        }
    }
    return 6;
}

int ItemInfoWindow::Load_LayoutWait()
{
    if (tasks_[1] == -1)
    {
        if (item_ != NULL)
            SetUpLayout(&layout_, item_);
        return 7;
    }
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loader->GetTaskStatus(tasks_[1]))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(tasks_[1], &file, &size);
        if (file != NULL && size != 0)
        {
            allocator_.Reset();
            layout_.Load(&allocator_, file, size);
        }
        loader->RemoveTask(tasks_[1]);
        tasks_[1] = -1;
        if (item_ != NULL)
        {
            SetUpLayout(&layout_, item_);
            equipmentLayout_ = IsEquipment(item_) ? 1 : 0;
        }
        return 7;
    }
    return 5;
}

int ItemInfoWindow::Load_Description()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (flags_ & ITEM_INFO_WINDOW_QUEST)
        return 8;
    if (item_ == NULL)
        return 3;
    memset(description_, 0, sizeof(description_));
    tasks_[2] = loader->QueueLoadFileInGP2(data_020f2a1c, data_020f2a14, NULL);
    if (IsEquipment(item_))
        return 3;
    if (flags_ & ITEM_INFO_WINDOW_NO_PLACES)
        return 3;
    return 8;
}

int ItemInfoWindow::Load_DescriptionWait()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if ((flags_ & ITEM_INFO_WINDOW_QUEST) || loader->GetTaskStatus(tasks_[2]))
    {
        memset(description_, 0, sizeof(description_));
        if (flags_ & ITEM_INFO_WINDOW_QUEST)
        {
            strcpy(description_, func_020e0434(sTexts, 0x29));
        }
        else
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(tasks_[2], &file, &size);
            if (file != NULL && size != 0)
                func_020e046c(description_, file, size, itemId_);
            loader->RemoveTask(tasks_[2]);
            tasks_[2] = -1;
        }
        func_020df83c(&places_);
        func_020dfc6c(&fieldNames_);
        func_020df83c(&drops_);
        func_020dfc6c(&monsterNames_);
        if (item_ == NULL)
            return -1;
        if (IsEquipment(item_))
        {
            DrawStats();
            DrawResistances();
            DrawDescription();
            return -1;
        }
        DrawDescription();
        return (flags_ & ITEM_INFO_WINDOW_NO_PLACES) ? -1 : 9;
    }
    return tasks_[2] != -1 ? 7 : -1;
}

int ItemInfoWindow::Load_Places()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_020df83c(&places_);
    tasks_[3] = loader->QueueLoadFileInGP2(data_020f2a1c, data_020f2b68, NULL);
    return 10;
}

// NONMATCHING: the C matches 87.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler assigns the registers of the loop's variables in another order
#ifdef NONMATCHING
int ItemInfoWindow::Load_PlacesWait()
{
    if (tasks_[3] == -1)
        return 13;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loader->GetTaskStatus(tasks_[3]))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(tasks_[3], &file, &size);
        if (file != NULL && size != 0)
        {
            func_020dfc6c(&fieldNames_);
            func_020df83c(&drops_);
            func_020dfc6c(&monsterNames_);
            infoAllocator_.Reset();
            func_020df850(&places_, &infoAllocator_, file, size, item_->unk_18);
            ItemInfoList* list = places_.list_;
            if (list != NULL)
            {
                ItemInfoEntry* entry = list->entries_;
                short count = list->count_;
                int i = 0;
                void* flags = func_0205ec34();
                for (; i < count; i++, entry++)
                {
                    const char* text = entry->text_;
                    if (text != NULL && text[0] == 'f' && strlen(text) >= 5 &&
                        !func_0206dfb0(flags, (char*)flags + 0x8c, atol(text + 5) + 0xc12))
                        entry->enabled_ = 0;
                }
            }
            loader->RemoveTask(tasks_[3]);
            tasks_[3] = -1;
            short ids[0xc];
            short count = 0;
            if (places_.list_ != NULL)
                GetPlaceIds(&places_, ids, &count);
            if (count == 0)
            {
                Canvas canvas;
                func_0204c684(&canvas);
                if (SetUpCanvas(&canvas, 0, 0, 0x1c, 6))
                {
                    if (!(flags_ & ITEM_INFO_WINDOW_NO_PLACES))
                        DrawPlaces(&layout_, &canvas);
                    vramOffset_ += LoadCanvas(&canvas, vramOffset_, sPalette, 0);
                }
                CancelTask(&tasks_[4]);
                return 13;
            }
            return 11;
        }
    }
    return 9;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN14ItemInfoWindow10CancelTaskEPi(); // ItemInfoWindow::CancelTask
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
}

asm int ItemInfoWindow::Load_PlacesWait()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x108
    mov r10, r0
    ldr r1, [r10, #0x744]
    mvn r0, #0x0
    cmp r1, r0
    moveq r0, #0xd
    beq @L021e0a3c
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldr r1, [r10, #0x744]
    mov r4, r0
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021e0a38
    ldr r1, [r10, #0x744]
    add r2, sp, #0xc
    add r3, sp, #0x8
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0xc]
    cmp r0, #0x0
    ldrne r0, [sp, #0x8]
    cmpne r0, #0x0
    beq @L021e0a38
    add r0, r10, #0x8c
    bl func_020dfc6c
    add r0, r10, #0x7c
    bl func_020df83c
    add r0, r10, #0xa4
    bl func_020dfc6c
    add r0, r10, #0x28
    bl _ZN13SafeAllocator5ResetEv
    ldr r1, [r10, #0x4c]
    add r0, r10, #0x6c
    ldrsh r2, [r1, #0x18]
    add r1, r10, #0x28
    str r2, [sp, #0x0]
    ldr r2, [sp, #0xc]
    ldr r3, [sp, #0x8]
    bl func_020df850
    ldr r5, [r10, #0x74]
    cmp r5, #0x0
    beq @L021e0964
    ldr r8, [r5, #0x4]
    bl func_0205ec34
    ldrsh r6, [r5, #0x2]
    mov r5, #0x0
    mov r7, r0
    mov r11, r5
    b @L021e095c
@L021e0908:
    ldr r9, [r8, #0x4]
    cmp r9, #0x0
    beq @L021e0954
    ldrsb r0, [r9, #0x0]
    cmp r0, #0x66
    bne @L021e0954
    mov r0, r9
    bl strlen
    cmp r0, #0x5
    blo @L021e0954
    add r0, r9, #0x5
    bl atol
    add r2, r0, #0x12
    mov r0, r7
    add r1, r7, #0x8c
    add r2, r2, #0xc00
    bl func_0206dfb0
    cmp r0, #0x0
    streqb r11, [r8, #0x1]
@L021e0954:
    add r5, r5, #0x1
    add r8, r8, #0x8
@L021e095c:
    cmp r5, r6
    blt @L021e0908
@L021e0964:
    ldr r1, [r10, #0x744]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x744]
    mov r0, #0x0
    strh r0, [sp, #0x4]
    ldr r0, [r10, #0x74]
    cmp r0, #0x0
    beq @L021e099c
    add r1, sp, #0x10
    add r2, sp, #0x4
    add r0, r10, #0x6c
    bl GetPlaceIds
@L021e099c:
    ldrsh r0, [sp, #0x4]
    cmp r0, #0x0
    bne @L021e0a30
    add r0, sp, #0x28
    bl func_0204c684
    mov r1, #0x0
    mov r4, #0x6
    add r0, sp, #0x28
    mov r2, r1
    mov r3, #0x1c
    str r4, [sp, #0x0]
    bl SetUpCanvas
    cmp r0, #0x0
    beq @L021e0a1c
    add r0, r10, #0x700
    ldrh r0, [r0, #0x74]
    tst r0, #0x400
    bne @L021e09f0
    add r1, sp, #0x28
    add r0, r10, #0xcc
    bl DrawPlaces
@L021e09f0:
    ldr r0, =sDrops
    ldr r1, [r10, #0x75c]
    ldr r2, [r0, #0xc]
    add r0, sp, #0x28
    mov r2, r2, lsl #0x10
    mov r2, r2, lsr #0x10
    mov r3, #0x0
    bl LoadCanvas
    ldr r1, [r10, #0x75c]
    add r0, r1, r0
    str r0, [r10, #0x75c]
@L021e0a1c:
    add r0, r10, #0x348
    add r0, r0, #0x400
    bl _ZN14ItemInfoWindow10CancelTaskEPi
    mov r0, #0xd
    b @L021e0a3c
@L021e0a30:
    mov r0, #0xb
    b @L021e0a3c
@L021e0a38:
    mov r0, #0x9
@L021e0a3c:
    add sp, sp, #0x108
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

int ItemInfoWindow::Load_FieldNames()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_020dfc6c(&fieldNames_);
    tasks_[4] = loader->QueueLoadFileInGP2(data_020f2a1c, data_020f2a10, NULL);
    return 12;
}

int ItemInfoWindow::Load_FieldNamesWait()
{
    if (tasks_[4] == -1)
        return 13;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loader->GetTaskStatus(tasks_[4]))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(tasks_[4], &file, &size);
        if (file != NULL && size != 0)
        {
            short ids[0xc];
            short count;
            GetPlaceIds(&places_, ids, &count);
            func_020e0028(&fieldNames_, &infoAllocator_, file, size, ids, (unsigned short)count);
        }
        loader->RemoveTask(tasks_[4]);
        tasks_[4] = -1;
        DrawFields();
        return 13;
    }
    return 11;
}

int ItemInfoWindow::Load_Drops()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_020df83c(&drops_);
    tasks_[5] = loader->QueueLoadFileInGP2(data_020f2a1c, data_020f2a28, NULL);
    return 14;
}

int ItemInfoWindow::Load_DropsWait()
{
    int result = -1;
    if (tasks_[5] != -1)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        if (loader->GetTaskStatus(tasks_[5]))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(tasks_[5], &file, &size);
            if (file != NULL && size != 0)
                func_020df850(&drops_, &infoAllocator_, file, size, item_->unk_18);
            loader->RemoveTask(tasks_[5]);
            tasks_[5] = -1;
            return 15;
        }
        result = 13;
    }
    return result;
}

int ItemInfoWindow::Load_MonsterNames()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_020dfc6c(&monsterNames_);
    tasks_[6] = loader->QueueLoadFileInGP2(data_020f2a1c, data_020f2a20, NULL);
    return 3;
}

// NONMATCHING: the C matches 92.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler assigns the registers of the loop's variables in another order
#ifdef NONMATCHING
int ItemInfoWindow::Load_MonsterNamesWait()
{
    memset(monsters_, 0, sizeof(monsters_));
    short count = 0;
    numMonsters_ = 0;
    ItemInfoList* list = drops_.list_;
    MonsterRecord records[0x18];
    short ids[0x18];
    signed char rare[0x18];
    if (list != NULL)
    {
        ItemInfoEntry* entry = list->entries_;
        short entries = list->count_;
        for (int i = 0; i < entries; i++, entry++)
        {
            const char* text;
            if (!entry->enabled_ || (text = entry->text_) == NULL)
                continue;
            char c = text[0];
            if (c < '0' || c > '9')
                continue;
            short id = atol(text);
            signed char isRare = 0;
            if (id >= 10000)
            {
                id -= 10000;
                isRare = 1;
            }
            rare[count] = isRare;
            ids[count] = id;
            count++;
            if (count >= 0x18)
                break;
        }
    }
    if (count > 0 && func_020ac020(0, ids, records, count))
    {
        for (int i = 0; i < count; i++)
        {
            short id = ids[i];
            if (id < 1 || id > 0x134)
                continue;
            unsigned char isRare = rare[i];
            if (!((isRare == 0 && records[i].dropCount0_ != 0) || (isRare != 0 && records[i].dropCount1_ != 0)))
                continue;
            monsters_[numMonsters_] = id;
            numMonsters_++;
            if (numMonsters_ >= 3)
                break;
        }
    }
    if (numMonsters_ <= 0)
    {
        DrawMonsters();
        return -1;
    }
    int result = -1;
    if (tasks_[6] != -1)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        if (loader->GetTaskStatus(tasks_[6]))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(tasks_[6], &file, &size);
            if (file != NULL && size != 0)
                func_020e0028(&monsterNames_, &infoAllocator_, file, size, monsters_, (unsigned short)numMonsters_);
            loader->RemoveTask(tasks_[6]);
            tasks_[6] = -1;
            DrawMonsters();
            return -1;
        }
        result = 15;
    }
    return result;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN14ItemInfoWindow12DrawMonstersEv(); // ItemInfoWindow::DrawMonsters
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
}

asm int ItemInfoWindow::Load_MonsterNamesWait()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xb8
    mov r10, r0
    add r0, r10, #0xbc
    mov r1, #0x0
    mov r2, #0x6
    bl memset
    mov r9, #0x0
    strh r9, [r10, #0xc2]
    ldr r0, [r10, #0x84]
    cmp r0, #0x0
    beq @L021e0d48
    mov r6, r9
    ldr r8, [r0, #0x4]
    ldrsh r7, [r0, #0x2]
    add r5, sp, #0x28
    add r11, sp, #0x10
    ldr r4, =0x2710
    b @L021e0d40
@L021e0ccc:
    ldrb r0, [r8, #0x1]
    cmp r0, #0x0
    ldrne r0, [r8, #0x4]
    cmpne r0, #0x0
    beq @L021e0d38
    ldrsb r1, [r0, #0x0]
    cmp r1, #0x30
    blt @L021e0d38
    cmp r1, #0x39
    bgt @L021e0d38
    bl atol
    mov r1, r0, lsl #0x10
    mov r0, #0x0
    mov r3, r1, asr #0x10
    cmp r4, r1, asr #0x10
    suble r0, r3, r4
    movle r1, r0, lsl #0x10
    movle r3, r1, asr #0x10
    add r1, r9, #0x1
    movle r0, #0x1
    mov r2, r9, lsl #0x1
    mov r1, r1, lsl #0x10
    strb r0, [r11, r9]
    mov r9, r1, asr #0x10
    strh r3, [r5, r2]
    cmp r9, #0x18
    bge @L021e0d48
@L021e0d38:
    add r6, r6, #0x1
    add r8, r8, #0x8
@L021e0d40:
    cmp r6, r7
    blt @L021e0ccc
@L021e0d48:
    cmp r9, #0x0
    ble @L021e0dfc
    add r1, sp, #0x28
    add r2, sp, #0x58
    mov r3, r9
    mov r0, #0x0
    bl func_020ac020
    cmp r0, #0x0
    beq @L021e0dfc
    mov r4, #0x0
    add r1, sp, #0x10
    add r0, sp, #0x58
    add r2, sp, #0x28
    b @L021e0df4
@L021e0d80:
    mov r3, r4, lsl #0x1
    ldrsh r3, [r2, r3]
    cmp r3, #0x1
    blt @L021e0df0
    cmp r3, #0x134
    bgt @L021e0df0
    ldrb r6, [r1, r4]
    cmp r6, #0x0
    bne @L021e0db4
    ldr r5, [r0, r4, lsl #0x2]
    mov r5, r5, lsl #0xe
    movs r5, r5, lsr #0x19
    bne @L021e0dcc
@L021e0db4:
    cmp r6, #0x0
    beq @L021e0df0
    ldr r5, [r0, r4, lsl #0x2]
    mov r5, r5, lsl #0x7
    movs r5, r5, lsr #0x19
    beq @L021e0df0
@L021e0dcc:
    ldrsh r5, [r10, #0xc2]
    add r5, r10, r5, lsl #0x1
    strh r3, [r5, #0xbc]
    ldrsh r3, [r10, #0xc2]
    add r3, r3, #0x1
    strh r3, [r10, #0xc2]
    ldrsh r3, [r10, #0xc2]
    cmp r3, #0x3
    bge @L021e0dfc
@L021e0df0:
    add r4, r4, #0x1
@L021e0df4:
    cmp r4, r9
    blt @L021e0d80
@L021e0dfc:
    ldrsh r0, [r10, #0xc2]
    cmp r0, #0x0
    bgt @L021e0e18
    mov r0, r10
    bl _ZN14ItemInfoWindow12DrawMonstersEv
    mvn r0, #0x0
    b @L021e0eac
@L021e0e18:
    ldr r1, [r10, #0x750]
    mvn r0, #0x0
    cmp r1, r0
    beq @L021e0eac
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldr r1, [r10, #0x750]
    mov r5, r0
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021e0ea8
    ldr r1, [r10, #0x750]
    add r2, sp, #0xc
    add r3, sp, #0x8
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r2, [sp, #0xc]
    cmp r2, #0x0
    ldrne r3, [sp, #0x8]
    cmpne r3, #0x0
    beq @L021e0e84
    add r0, r10, #0xbc
    str r0, [sp, #0x0]
    ldrh r4, [r10, #0xc2]
    add r0, r10, #0xa4
    add r1, r10, #0x28
    str r4, [sp, #0x4]
    bl func_020e0028
@L021e0e84:
    ldr r1, [r10, #0x750]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r1, #0x0
    mov r0, r10
    str r1, [r10, #0x750]
    bl _ZN14ItemInfoWindow12DrawMonstersEv
    mvn r0, #0x0
    b @L021e0eac
@L021e0ea8:
    mov r0, #0xf
@L021e0eac:
    add sp, sp, #0xb8
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void ItemInfoWindow::DrawFields()
{
    Canvas canvas;
    func_0204c684(&canvas);
    if (!SetUpCanvas(&canvas, 0, 0, 0x1c, 6))
        return;
    if (!(flags_ & ITEM_INFO_WINDOW_NO_PLACES))
        DrawPlaces(&layout_, &canvas);
    vramOffset_ += LoadCanvas(&canvas, vramOffset_, sPalette, 0);
}

void ItemInfoWindow::DrawMonsters()
{
    Canvas canvas;
    func_0204c684(&canvas);
    if (!SetUpCanvas(&canvas, 0, 0, 0x1c, 3))
        return;
    if (!(flags_ & ITEM_INFO_WINDOW_NO_PLACES))
    {
        char names[2][0x80] = {0};
        const char* found = func_020e0434(sTexts, 0x1f);
        const char* none = func_020e0434(sTexts, 0x1e);
        SHOW_ELEMENT(&layout_, 0xe);
        SHOW_ELEMENT(&layout_, 0xd);
        layout_.SetText(0xb, found, 10, 15);
        layout_.SetText(0xc, found, 10, 15);
        layout_.SetText(0xd, none, 10, 15);
        int i = 0;
        short count = sWindow->numMonsters_;
        for (; i < count; i++)
        {
            if (i >= 2)
                break;
            const char* name = func_020e0434(sMonsterNames, sWindow->monsters_[i]);
            if (name != NULL)
            {
                func_0206819c(name, names[i], 0);
                layout_.SetText(sMonsterNameIds[i], names[i], 10, 15);
            }
        }
        if (count != 3)
            HIDE_ELEMENT(&layout_, 0xd);
        short y;
        short x;
        TakeElement(&layout_, &canvas, 0xe, &x, &y);
        if (sBuffer != NULL)
        {
            layout_.SetCanvas(&canvas);
            layout_.Draw();
        }
        layout_.SetElementPosition(0xe, x, y);
        HIDE_ELEMENT(&layout_, 0xe);
    }
    vramOffset_ += LoadCanvas(&canvas, vramOffset_, sPalette, 0);
}
