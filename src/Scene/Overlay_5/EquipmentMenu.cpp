// Overlay 5, the equipment menu (see EquipmentMenu.h)
// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_5/EquipmentMenu.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "Graphics/Vector.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/Cache.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include "System/LoadToVRAM.h"
#include "System/TouchScreen.h"
#include "Text/MessageName.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define REG_DISPCNT (*(volatile unsigned int*)0x04000000)
#define REG_BG0CNT (*(volatile unsigned short*)0x04000008)
#define REG_BG1CNT (*(volatile unsigned short*)0x0400000a)
#define REG_BG2CNT (*(volatile unsigned short*)0x0400000c)
#define REG_BG3CNT (*(volatile unsigned short*)0x0400000e)
#define REG_BLDCNT 0x04000050
#define GXFIFO_BEGIN_VTXS (*(volatile unsigned int*)0x04000500)
#define GXFIFO_END_VTXS (*(volatile unsigned int*)0x04000504)

// The flags of EquipmentMenu::flags_
#define EQUIPMENT_LOADING 2
#define EQUIPMENT_KINDS 4
#define EQUIPMENT_ARROWS 8
#define EQUIPMENT_LOAD_ITEM 0x10
#define EQUIPMENT_LOAD_EQUIPPED 0x20
#define EQUIPMENT_LOAD_PAGE 0x40
#define EQUIPMENT_LOAD_DRAG 0x80
#define EQUIPMENT_KIND_CHANGED 0x100
#define EQUIPMENT_NAMES 0x200
#define EQUIPMENT_STATE_0 0x400
#define EQUIPMENT_SORT_ICON 0x800
#define EQUIPMENT_FRAME_BLINK 0x1000
#define EQUIPMENT_ARROWS_BLINK 0x2000
#define EQUIPMENT_FADE 0x10000
#define EQUIPMENT_PREVIOUS_PAGE 0x20000
#define EQUIPMENT_NEXT_PAGE 0x40000
#define EQUIPMENT_SORT 0x80000

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    // The runtime's functions, for the assembly of the NONMATCHING functions
    void _d2f();
    void _dflt();
    void _fadd();
    void _fflt();
    void _ffix();
    void _fls();
    void _fmul();
    double func_0200b454(double x);

    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];
    extern TouchState data_02114e54;

    PartyMember* func_0200ff1c(GameState* gameState, int index);
    GameResources* func_0200fb8c(GameState* gameState);
    int func_0200fb08(GameState* gameState);
    void func_0200ff58(GameState* gameState, int index);
    int func_020100a8(GameState* gameState);
    void* func_020100bc(GameState* gameState);
    char* func_02010828(GameState* gameState);
    int func_02012444(void* pad, int buttons);
    void func_02012a84(TouchState* touch, int* x, int* y);
    char* func_02012fe4();
    short func_0201e830(void* data);
    void func_0202ae18();
    int func_0202b7d8();
    void func_0202ec84(void* camera, Vector3fix* position, int* x, int* y);
    void func_0203a46c(MenuModel* model, int x, int y, int z);
    void func_0203b4d8(GameResources* resources, int);
    void func_0203b4e8(GameResources* resources, int);
    void* func_0203b628();
    void func_0203b634(void*);
    void func_0203b66c(void*);
    void func_0203b678(void*, int, int);
    MessageSystem* func_020421a0();
    void func_020439b0(MessageSystem* messages, int);
    void func_02045d14(MessageSystem* messages, const char* text, unsigned short* codes, int);
    void func_02045f3c(MessageSystem* messages, unsigned short* codes, int x, int y, int color, int, int, int, int, int);
    void func_020462d0(MessageSystem* messages, unsigned short* codes, int count);
    void func_02046608(MessageSystem* messages, int, const char* format, char* output, int size, int, int);
    int func_0204684c(void* archive, const char* name, void** files, int count, unsigned int* sizes, int);
    int func_02046900(void* archive);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    void func_0204719c(MenuModel* model);
    void func_02047230(MenuModel* model);
    void func_02047b30(MenuModel* model, void* file, unsigned int size, SafeAllocator* allocator);
    void func_02047b40(MenuModel* model, void* file, SafeAllocator* allocator);
    void func_0204af38(BackgroundGraphics* background, int, void*);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204afb4(BackgroundGraphics* background);
    void func_0204b010(BackgroundGraphics* background, int);
    void func_0204b04c(BackgroundGraphics* background, int);
    void func_0204b088(BackgroundGraphics* background, int);
    void func_0204b0e8(BackgroundGraphics* background, int);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b12c(BackgroundGraphics* background, void*);
    void func_0204b174(BackgroundGraphics* background, void* file, void*, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* background, int);
    void func_0204b5e8(BackgroundGraphics* background, int, int);
    void func_0204b8d0(BackgroundGraphics* background, unsigned char, int, int, int, int, int, int, unsigned short);
    void func_0204bc74(BackgroundGraphics* background, int, int, int, int, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, void*, void* pixels, int);
    short func_02052df8(PartyMember* member, int);
    short* func_02052e14(PartyMember* member);
    int func_020546a8();
    int func_0205bb84(WindowCursor* cursor);
    void func_0205bef8(WindowCursor* cursor);
    void func_0205bf58(WindowCursor* cursor, int ticks);
    void func_0205cf78(TextWindow* window, Canvas* canvases, int count);
    void func_0205cfd4(TextWindow* window);
    void func_0205d048(TextWindow* window);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d6a0(TextWindow* window, int);
    void func_0205eaa0(void* sound, int effect, int);
    void func_02074af4(void* state);
    void func_02074bd0(void* state);
    short* func_0207c5f8(void* lists, int list);
    signed char* func_0207c60c(void* lists, int list);
    short func_0207c620(void* lists, int list);
    int func_0207c638(void* lists, int list);
    int func_0207c7a0(void* lists, short item, int list);
    void func_0207de48(VRAMManagerState* state, int textureSize, int paletteSize);
    void func_0207df50(VRAMManagerState* state);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);
    void func_020c5588(unsigned short, int, int, int, int);
    void func_020dc7e8(int, signed char member);
    PartEntry* func_020dedd0(PartNameTable* items, short id);
    int func_020de234(PartEntry* item, int);
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, short id);
    int func_020e28dc(void*);
    void func_020e2794(void*, int);
    void func_020e2834(void*);
    void func_020e2cc4(void*, int);
    void func_020e2d24(void*, int, int);
    GameResources* func_ov017_0218b5b0();
    // The screen that runs the menu
    MemberScreen* func_ov017_021a193c(void* data);
    void func_ov017_021c9e00(int member, int, int, int);
    // MemberScreen::DoNothing, which overlay 5 calls with arguments
    void _ZN12MemberScreen9DoNothingEv(MemberScreen* screen, int member, short item, unsigned char list);
    void func_02046380(MessageSystem* messages);
    void func_020483f0(PartyMember* member, int);
    int func_0204c7cc(Canvas* canvas);
    void func_02052d7c(PartyMember* member, int part, short item);
    // What func_02052e2c returns
    struct Unknown_02052e2c
    {
        char unk_0[0x16];
        short unk_16;
    };
    Unknown_02052e2c* func_02052e2c(PartyMember* member);
    PartyMemberData* func_02053c6c(PartyMember* member);
    unsigned char func_0205d0e0(TextWindow* window, int ticks);
    void func_0205d304(TextWindow* window, unsigned short* text, int, int, int, int, unsigned char* colors, int);
    void func_0205d5d0(TextWindow* window, int, unsigned short* text, int, int);
    Canvas* func_0205d81c(TextWindow* window, int);
    void func_0207c378(void* lists, short item, int count, int list);
    void func_0207c484(void* lists, short item, int count, int list);
    int func_0207caa4(void* lists, short item, int list);
    void func_0207cb38(void* lists, int index, int list, short item, int count);
    void func_02083738(PartyMemberData* data, int category);
    void func_0208358c(PartyMemberData* data, PartEntry* item, int);
    void func_02083e28(PartyMemberData* data, int);
    void func_020dcf7c(short item, MessageName* name);
    int func_020dd4c4(signed char member, PartEntry* item);
    PartEntry* func_020deda4(PartNameTable* items, int letter, PartEntry* item);
    void func_020e46c4(MessageName* name);
    short func_020017b0(int x);
    void func_02041b70(unsigned short* text, int index, const char* option);
    void func_02041c08(unsigned short* text, int index, int, int, int);
    void func_02041ea4(unsigned short* text, int index);
    void func_02042058(unsigned short* text, const char* separator);
    int func_020420e8(const char* text, int large);
    void func_020473c8(MenuModel* model, int);
    void func_02047554(MenuModel* model, int, int);
    int func_0204c7e0(Canvas* canvas);
    void func_0205ae8c(SpriteRenderer* renderer);
    void func_0205bc24(void* frame, int);
    void func_0205c53c(WindowBase* base);
    void func_0205cef8(TextWindow* window);
    void func_0205cf04(TextWindow* window);
    void func_0205cf10(TextWindow* window);
    void func_0205cf1c(TextWindow* window);
    signed char func_0205d794(TextWindow* window);
    Canvas* func_0205d8c4(TextWindow* window);
    int func_0205da38(TextWindow* window, int);
    void func_0206819c(int name, char* output, int);
    void func_0207c51c(void* lists, int list);
    void func_0209c830(void* sound, int);
    int func_0209ca2c(void* sound);
    void func_020c51a4(Matrix4x3* matrix);
    int func_020d2f88(const char* text, const char* search);
    int func_020dd768(PartEntry* item);
    void func_020de1d4(PartEntry* item);
    void func_020e1674(void*, int, int);
    void func_020e16dc(void*, int, int);
    void func_020e1e24(void*, short* width, short* height, int);
    void func_020e2490(void* choice, int, int, SpriteAnimationList* animations, SafeAllocator* allocator, int, int);
    void func_020e25e8(void* choice);
    void func_020e263c(void* choice, int ticks);
    void func_020e280c(void* choice, int);
    void func_020e28f0(void* choice, short x, short y);
    int func_020e2918(void* choice);
    int func_020e2984(void* choice);
    void func_020e4bf4(MessageName* name, int member);
}

// The strings of the functions, which the compiler pools in this order. Load() is in assembly for now (NONMATCHING),
// which can't reference the compiler's pool, so they're in an array for it
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] __attribute__((aligned(4))) =
    "data/bin/menu/str_eq.gp2\0str_eq_<LG>.nat\0data/prm/itemsort.gp2\0itemsort_<LG>.bin\0%d\0\n";
#define STRING(offset, text) (sStrings + (offset))
#endif

// The states of the menu (see state_)
typedef void (EquipmentMenu::*EquipmentState)();
static EquipmentState sStates[8] = {
    &EquipmentMenu::State_Start, &EquipmentMenu::State_Open, &EquipmentMenu::State_Kinds,
    &EquipmentMenu::State_Equipped, &EquipmentMenu::State_Page, &EquipmentMenu::State_Menu,
    &EquipmentMenu::State_Move, &EquipmentMenu::State_Sort,
};

void EquipmentMenu::CreateAllocators(SafeAllocator* allocator, SafeAllocator* allocator2)
{
    if (allocator == NULL || allocator2 == NULL)
        return;
    modelAllocator_.CreateTypeA(allocator2->Allocate(0x1300), 0x1300);
    for (int i = 0; i < 8; i++)
        equippedAllocators_[i].CreateTypeA(allocator2->Allocate(0xe0), 0xe0);
    for (int i = 0; i < 16; i++)
        itemAllocators_[i].CreateTypeA(allocator2->Allocate(0xe0), 0xe0);
    dragAllocator_.CreateTypeA(allocator2->Allocate(0xe0), 0xe0);
    textAllocator_.CreateTypeA(allocator2->Allocate(0xc00), 0xc00);
    infoAllocator_.CreateTypeA(allocator->Allocate(0x1e00), 0x1e00);
    allocator_.CreateTypeA(allocator->Allocate(0x4b00), 0x4b00);
    sortAllocator_.CreateTypeA(allocator->Allocate(0x4a00), 0x4a00);
    modelTableAllocator_.CreateTypeA(allocator->Allocate(0x1e00), 0x1e00);
    unk_280.CreateTypeA(allocator2->Allocate(0x200), 0x200);
    pageFiles_ = (char*)allocator->Allocate(0x800);
    dragFile_ = (char*)allocator2->Allocate(0x200);
    equippedFiles_ = (char*)allocator->Allocate(0x800);
    itemFile_ = (char*)allocator2->Allocate(0x200);
}

void EquipmentMenu::LoadVRAM()
{
    for (int i = 0; i < 24; i++)
    {
        func_0207de48(&slotVramStates_[i], 0x120, 0x20);
        func_0207df50(&slotVramStates_[i]);
    }
    func_0207de48(&dragVramState_, 0x120, 0x20);
    func_0207df50(&dragVramState_);
    func_0207de48(&vramState_, 0x3000, 0x400);
    func_0207df50(&vramState_);
}

void EquipmentMenu::Initialize()
{
    unk_e7c = 0;
    unk_e7d = 0;
    func_02074af4(screenState_);
    layers_ = (REG_DISPCNT & 0x1f00) >> 8;
    unk_3dc2 = func_0201e830(func_02012fe4() + 0x6c);
    allocator_.ResetAllocatorPointer();
    modelAllocator_.ResetAllocatorPointer();
    for (int i = 0; i < 8; i++)
        equippedAllocators_[i].ResetAllocatorPointer();
    for (int i = 0; i < 16; i++)
        itemAllocators_[i].ResetAllocatorPointer();
    dragAllocator_.ResetAllocatorPointer();
    textAllocator_.ResetAllocatorPointer();
    unk_230.ResetAllocatorPointer();
    infoAllocator_.ResetAllocatorPointer();
    sortAllocator_.ResetAllocatorPointer();
    modelTableAllocator_.ResetAllocatorPointer();
    unk_280.ResetAllocatorPointer();
    items_ = NULL;
    func_020dfc40(&texts_);
    text_ = NULL;
    layout_.Initialize();
    unk_e64 = NULL;
    unk_e68 = 0;
    func_0204af64(&backgrounds_[0]);
    func_0204af64(&backgrounds_[1]);
    func_0204af64(&backgrounds_[2]);
    func_0205cfd4(&window_);
    for (int i = 0; i < 3; i++)
        func_0204c684(&canvases_[i]);
    pixels_ = NULL;
    infoWindow_.Initialize(-1, 0);
    sortList_.Initialize();
    modelTable_.Initialize();
    frame_.Initialize();
    for (int i = 0; i < 36; i++)
        func_0204719c(&models_[i]);
    for (int i = 0; i < 24; i++)
        func_0204719c(&slotModels_[i]);
    func_0204719c(&dragModel_);
    dragged_ = -1;
    unk_3d7c = 0;
    unk_3d80 = 0;
    unk_3d84 = 0;
    pageFiles_ = NULL;
    dragFile_ = NULL;
    equippedFiles_ = NULL;
    itemFile_ = NULL;
    for (int i = 0; i < 24; i++)
    {
        slots_[i].item_ = -1;
        slots_[i].count_ = 0;
        slots_[i].equipped_ = 0;
        slots_[i].vramState_ = NULL;
        slots_[i].model_ = NULL;
        slots_[i].x_ = 0;
        slots_[i].y_ = 0;
        slots_[i].offset_ = -1;
        slots_[i].loadedItem_ = -1;
    }
    GameState* gameState = GameState::GetInstance();
    char* party = func_02010828(gameState);
    for (int i = 0; i < 8; i++)
        itemCounts_[i] = func_0207c620(party + 0x1d4, GetList(i));
    unk_3da8 = 0;
    equippedStep_ = 0;
    pageStep_ = 0;
    dragStep_ = 0;
    unk_3dac = 0;
    equippedStart_ = 0;
    equippedEnd_ = 0;
    pageStart_ = 0;
    pageEnd_ = 0;
    loading_ = 0;
    state_ = 2;
    lastState_ = 2;
    step_ = 0;
    slot_ = 0;
    kind_ = 0;
    unk_3dbe = 0;
    page_ = 0;
    lastPage_ = 0;
    loadStep_ = 0;
    task_ = 0;
    memset(&flags_, 0, sizeof(flags_));
    unk_3dc0 = -1;
    func_0205bef8(&cursor_);
    cursor_.unk_3d = 0;
    unk_3dd0 = 0;
    unk_3dd1 = 0;
    unk_3dd2 = 0;
    unk_3dd3 = 0;
    for (int i = 0; i < 8; i++)
        sortOrders_[i] = 0;
    menuStep_ = 0;
    menuResult_ = 0;
    menuChoice_ = 0;
    menuState_ = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 0x40; j++)
            names_[i][j] = 0xffff;
        longNames_[i] = 0;
    }
    animationX_ = 0;
    ticks_ = 0;
    animationTime_ = 0;
    animationPhase_ = 0;
    blinks_ = 3;
    blinkTimer_ = 30;
    blinkTimer2_ = 30;
    fadeStep_ = 0;
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    int* members = screen->members_;
    int memberCount = screen->memberCount_;
    for (int kind = 0; kind < 8; kind++)
    {
        unsigned char list = GetList(kind);
        int part = GetPart(kind);
        int count = func_0207c638(party + 0x1d4, list);
        short equipped[4];
        __clear(equipped, sizeof(equipped));
        for (int i = 0; i < memberCount; i++)
        {
            PartyMember* member = func_0200ff1c(gameState, members[i]);
            if (member == NULL)
                continue;
            equipped[i] = func_02052df8(member, part);
            if (equipped[i] <= 0)
                continue;
            int j;
            for (j = 0; j < i; j++)
                ;
            if (!func_0207c7a0(party + 0x1d4, equipped[i], 9))
                count++;
        }
        if (count > 0)
            pageCounts_[kind] = (count - 1) / 16 + 1;
        else
            pageCounts_[kind] = 1;
        short* items = func_0207c5f8(party + 0x1d4, list);
        short itemCount = func_0207c620(party + 0x1d4, list);
        int last = 0;
        for (int i = 0; i < itemCount; i++)
        {
            if (items[i] > 0 && last < i)
                last = i;
        }
        unsigned char pages = last / 16 + 1;
        if (pages > pageCounts_[kind])
            pageCounts_[kind] = pages;
        pages_[kind] = 0;
    }
    unk_3e04 = 0;
    touchTime_ = 0;
    tappedSlot_ = -2;
    tapTimer_ = 0;
    touchX_ = -1;
    touchY_ = -1;
}

void EquipmentMenu::Finish()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    infoWindow_.Finish();
    func_020c5588(unk_3dc2, 0x10, 0x7fff, 0, 0);
    GameState* gameState = GameState::GetInstance();
    func_0203b4e8(func_0200fb8c(gameState), 0x800);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (layers_ << 8);
    func_0205d6a0(&window_, 1);
    func_0205d048(&window_);
    func_02074bd0(screenState_);
    func_0204b010(&backgrounds_[0], 0);
    func_0204b04c(&backgrounds_[0], 0);
    func_0204b088(&backgrounds_[0], 0);
    func_0204afb4(&backgrounds_[0]);
    if (pageFiles_ != NULL)
    {
        memset(pageFiles_, 0, 0x20);
        CleanInvalidateCacheRange(pageFiles_, 0x20);
        LoadToMainBG1CharacterData(pageFiles_, 0, 0x20);
    }
    modelAllocator_.Destroy();
    for (int i = 0; i < 8; i++)
        equippedAllocators_[i].Destroy();
    for (int i = 0; i < 16; i++)
        itemAllocators_[i].Destroy();
    dragAllocator_.Destroy();
    textAllocator_.Destroy();
    allocator_.Destroy();
    unk_230.Destroy();
    infoAllocator_.Destroy();
    sortAllocator_.Destroy();
    modelTableAllocator_.Destroy();
    unk_280.Destroy();
    pageFiles_ = NULL;
    dragFile_ = NULL;
    equippedFiles_ = NULL;
    itemFile_ = NULL;
    text_ = NULL;
}

static int sCanvasSizes[3] = {0x280, 0x80, 0x40};

// NONMATCHING: the C matches 97.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
int EquipmentMenu::Load()
{
    if (loadStep_ == 0xff)
        return 1;
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loadStep_ == 0)
    {
        InitializeSlots();
        LoadEquipped();
        LoadPage();
        flags_ |= EQUIPMENT_LOAD_EQUIPPED;
        equippedStep_ = 0;
        flags_ |= EQUIPMENT_LOAD_PAGE;
        pageStep_ = 0;
        loadStep_++;
    }
    else if (loadStep_ == 1)
    {
        if (pageStep_ == 0)
            loadStep_++;
    }
    else if (loadStep_ == 2)
    {
        BackgroundLoader::AddLockGlobal();
        BackgroundLoader::FreeAllocationsGlobal();
        unsigned int size;
        void* file = ExtractFileFromGP2(STRING(0, "data/bin/menu/str_eq.gp2"), STRING(0x19, "str_eq_<LG>.nat"), &size);
        textAllocator_.Reset();
        func_020dfec0(&texts_, &textAllocator_, file, size);
        BackgroundLoader::RemoveLockGlobal();
        text_ = (unsigned short*)func_020421a0()->unk_5c;
        func_020c5588(0, 0, 0x7fff, 0, 0);
        func_0203b4d8(resources, 0x800);
        void* unk = func_0203b628();
        func_0203b678(unk, 0, 1);
        func_0203b66c(unk);
        func_0203b634(unk);
        func_0204b11c(&backgrounds_[0], 0);
        backgrounds_[0].unk_1c_0_ = 0;
        backgrounds_[0].unk_1c_4_ = 1;
        func_0204b5b4(&backgrounds_[0], 3);
        func_0204b5e8(&backgrounds_[0], 0, 0);
        func_0204b12c(&backgrounds_[0], this);
        func_0204af38(&backgrounds_[0], 6, this);
        func_0204b11c(&backgrounds_[1], 0);
        backgrounds_[1].unk_1c_0_ = 0;
        backgrounds_[1].unk_1c_4_ = 2;
        func_0204b5b4(&backgrounds_[1], 2);
        func_0204b5e8(&backgrounds_[1], 0, 0);
        func_0204b12c(&backgrounds_[1], this);
        func_0204af38(&backgrounds_[1], 9, this);
        func_0204b11c(&backgrounds_[2], 0);
        backgrounds_[2].unk_1c_0_ = 0;
        backgrounds_[2].unk_1c_4_ = 3;
        func_0204b5b4(&backgrounds_[2], 0);
        func_0204b5e8(&backgrounds_[2], 0, 0);
        func_0204b12c(&backgrounds_[2], this);
        REG_BG1CNT = (REG_BG1CNT & 0x43) | 0x1d00;
        REG_BG2CNT = (REG_BG2CNT & 0x43) | 0x1e00;
        REG_BG3CNT = (REG_BG3CNT & 0x43) | 0x1f04;
        ColorEffect_ConfigureAlphaBlend(REG_BLDCNT, 1, 2, 10, 6);
        const char* inner = func_020e0434(&texts_, 0x3e9);
        task_ = loader->QueueLoadFileInGP2(func_020e0434(&texts_, 0x3e8), inner, NULL);
        loadStep_++;
    }
    else if (loadStep_ == 3)
    {
        if (loader->GetTaskStatus(task_))
        {
            Canvas* canvas;
            char name[4];
            void* archive;
            unsigned int archiveSize;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &archive, &archiveSize);
            int count = func_02046900(archive);
            for (int i = 0; i < count; i++)
            {
                void* file = func_020467f0(archive, i, name, &size);
                if (file == NULL)
                    continue;
                if (i == 0)
                    func_0204b174(&backgrounds_[2], file, this, size);
                else if (i <= 8)
                    func_0204b174(&backgrounds_[0], file, this, size);
                else
                    func_0204b174(&backgrounds_[1], file, this, size);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            func_0204bc74(&backgrounds_[1], 0, 0, 0, 0x20, 0x19, 0);
            func_0204b0e8(&backgrounds_[1], 0);
            func_0204bc74(&backgrounds_[2], 0, 0, 0, 0x20, 0x19, 0);
            func_0204b0e8(&backgrounds_[2], 0);
            func_0204b8d0(&backgrounds_[0], 0, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
            func_0204b0e8(&backgrounds_[0], 0);
            func_0204b8d0(&backgrounds_[0], 1, 0, 0, 0, 0x14, 0x10, 2, 0xffff);
            func_0204b0e8(&backgrounds_[0], 0);
            pixels_ = allocator_.Allocate(0x2400);
            for (int i = 0; i < 3; i++)
            {
                canvas = &canvases_[i];
                func_0204c7a8(canvas, this, pixels_, sCanvasSizes[i]);
                canvas->background_ = &backgrounds_[2];
            }
            window_.background_ = &backgrounds_[2];
            window_.unk_b2 = 1;
            func_0205cf78(&window_, canvases_, 3);
            task_ = loader->QueueLoadFile(func_020e0434(&texts_, 0x3ea), NULL);
            loadStep_++;
        }
    }
    else if (loadStep_ == 4)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* archive;
            unsigned int archiveSize;
            loader->GetLoadedFileByID(task_, &archive, &archiveSize);
            int count = func_02046900(archive);
            int vocation = func_0200fb08(gameState);
            int model = 0;
            void* files[0x26];
            unsigned int sizes[0x26];
            if (func_0204684c(archive, func_020e0434(&texts_, 0x7d0), files, count, sizes, 0))
            {
                func_0207df90(&vramState_);
                for (int i = 0; i < count; i++)
                {
                    if (i == 35)
                    {
                        if (vocation == 2 || vocation == 3)
                            continue;
                    }
                    else if (i == 36)
                    {
                        if (vocation != 2)
                            continue;
                    }
                    else if (i == 37)
                    {
                        if (vocation != 3)
                            continue;
                    }
                    func_02047b30(&models_[model], files[i], sizes[i], &modelAllocator_);
                    model++;
                }
                func_0207dfac(&vramState_);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            task_ = loader->QueueLoadFileInGP2(STRING(0x29, "data/prm/itemsort.gp2"),
                                               STRING(0x3f, "itemsort_<LG>.bin"), NULL);
            loadStep_++;
        }
    }
    else if (loadStep_ == 5)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            sortAllocator_.Reset();
            sortList_.Initialize();
            sortList_.Load(&sortAllocator_, file, size, NULL, 0);
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
        }
    }
    else
    {
        REG_BG0CNT = (REG_BG0CNT & ~3) | 1;
        REG_BG1CNT = (REG_BG1CNT & ~3) | 3;
        REG_BG2CNT = (REG_BG2CNT & ~3) | 2;
        REG_BG3CNT = REG_BG3CNT & ~3;
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
        frame_.corners_ = (char*)models_;
        frame_.size_ = 0x8000;
        frame_.left_ = -0x3000;
        frame_.right_ = 0x3000;
        frame_.top_ = -0x3000;
        frame_.bottom_ = 0x3000;
        frame_.SetTargetPosition(0x85000, 0x17000);
        frame_.SetPosition(0x85000, 0x17000);
        frame_.SetTargetSize(0x76000, 0x16000);
        frame_.SetSize(0x76000, 0x16000);
        frame_.z_ = 0x5000;
        state_ = 0;
        flags_ |= EQUIPMENT_STATE_0;
        SetCursor();
        cursor_.unk_3c = 0;
        flags_ |= EQUIPMENT_KINDS | EQUIPMENT_ARROWS;
        GameState::GetInstance();
        int member = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_;
        func_020dc7e8(5, member);
        infoAllocator_.Reset();
        infoWindow_.Initialize(slots_[0].item_, 0);
        infoWindow_.flags_ |= 0xd0;
        infoWindow_.CreateAllocators(&infoAllocator_);
        infoWindow_.names_ = items_;
        infoWindow_.member_ = member;
        loadStep_ = 0xff;
        return 1;
    }
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11CursorFrame11SetPositionEii(); // CursorFrame::SetPosition
    void _ZN11CursorFrame13SetTargetSizeEii(); // CursorFrame::SetTargetSize
    void _ZN11CursorFrame17SetTargetPositionEii(); // CursorFrame::SetTargetPosition
    void _ZN11CursorFrame7SetSizeEii(); // CursorFrame::SetSize
    void _ZN12ItemSortList10InitializeEv(); // ItemSortList::Initialize
    void _ZN12ItemSortList4LoadEP13SafeAllocatorPKvjPKss(); // ItemSortList::Load
    void _ZN13EquipmentMenu12LoadEquippedEv(); // EquipmentMenu::LoadEquipped
    void _ZN13EquipmentMenu15InitializeSlotsEv(); // EquipmentMenu::InitializeSlots
    void _ZN13EquipmentMenu8LoadPageEv(); // EquipmentMenu::LoadPage
    void _ZN13EquipmentMenu9SetCursorEv(); // EquipmentMenu::SetCursor
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN14ItemInfoWindow10InitializeEsa(); // ItemInfoWindow::Initialize
    void _ZN14ItemInfoWindow16CreateAllocatorsEP13SafeAllocator(); // ItemInfoWindow::CreateAllocators
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm int EquipmentMenu::Load()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x168
    mov r10, r0
    add r0, r10, #0x3000
    ldrb r0, [r0, #0xdc4]
    cmp r0, #0xff
    moveq r0, #0x1
    beq @L02154ce4
    bl _ZN9GameState11GetInstanceEv
    mov r6, r0
    bl func_0200fb8c
    mov r4, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    add r1, r10, #0x3000
    ldrb r2, [r1, #0xdc4]
    mov r7, r0
    cmp r2, #0x0
    bne @L02154404
    mov r0, r10
    bl _ZN13EquipmentMenu15InitializeSlotsEv
    mov r0, r10
    bl _ZN13EquipmentMenu12LoadEquippedEv
    mov r0, r10
    bl _ZN13EquipmentMenu8LoadPageEv
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdcc]
    mov r2, #0x0
    orr r1, r1, #0x20
    str r1, [r0, #0xdcc]
    strb r2, [r0, #0xda9]
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x40
    str r1, [r0, #0xdcc]
    strb r2, [r0, #0xdaa]
    ldrb r1, [r0, #0xdc4]
    add r1, r1, #0x1
    strb r1, [r0, #0xdc4]
    b @L02154ce0
@L02154404:
    cmp r2, #0x1
    bne @L02154420
    ldrb r0, [r1, #0xdaa]
    cmp r0, #0x0
    addeq r0, r2, #0x1
    streqb r0, [r1, #0xdc4]
    b @L02154ce0
@L02154420:
    cmp r2, #0x2
    bne @L021546a4
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    ldr r0, =sStrings
    ldr r1, =sStrings+0x19
    add r2, sp, #0x34
    bl ExtractFileFromGP2
    mov r5, r0
    add r0, r10, #0x21c
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x1f8
    ldr r3, [sp, #0x34]
    mov r2, r5
    add r0, r0, #0xc00
    add r1, r10, #0x21c
    bl func_020dfec0
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    bl func_020421a0
    ldr r1, [r0, #0x5c]
    mov r0, #0x0
    str r1, [r10, #0xe10]
    ldr r2, =0x7fff
    mov r1, r0
    mov r3, r0
    str r0, [sp, #0x0]
    bl func_020c5588
    mov r0, r4
    mov r1, #0x800
    bl func_0203b4d8
    bl func_0203b628
    mov r4, r0
    mov r1, #0x0
    mov r2, #0x1
    bl func_0203b678
    mov r0, r4
    bl func_0203b66c
    mov r0, r4
    bl func_0203b634
    add r0, r10, #0x284
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b11c
    ldrb r1, [r10, #0xea0]
    add r0, r10, #0x284
    add r0, r0, #0xc00
    bic r1, r1, #0xf
    strb r1, [r10, #0xea0]
    and r1, r1, #0xff
    bic r1, r1, #0xf0
    orr r1, r1, #0x10
    strb r1, [r10, #0xea0]
    mov r1, #0x3
    bl func_0204b5b4
    add r0, r10, #0x284
    mov r1, #0x0
    add r0, r0, #0xc00
    mov r2, r1
    bl func_0204b5e8
    add r0, r10, #0x284
    add r0, r0, #0xc00
    mov r1, r10
    bl func_0204b12c
    add r0, r10, #0x284
    add r0, r0, #0xc00
    mov r1, #0x6
    mov r2, r10
    bl func_0204af38
    add r0, r10, #0x2a4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b11c
    ldrb r1, [r10, #0xec0]
    add r0, r10, #0x2a4
    add r0, r0, #0xc00
    bic r2, r1, #0xf
    and r1, r2, #0xff
    bic r1, r1, #0xf0
    orr r2, r1, #0x20
    mov r1, #0x2
    strb r2, [r10, #0xec0]
    bl func_0204b5b4
    add r0, r10, #0x2a4
    mov r1, #0x0
    mov r2, r1
    add r0, r0, #0xc00
    bl func_0204b5e8
    add r0, r10, #0x2a4
    mov r1, r10
    add r0, r0, #0xc00
    bl func_0204b12c
    add r0, r10, #0x2a4
    add r0, r0, #0xc00
    mov r1, #0x9
    mov r2, r10
    bl func_0204af38
    add r0, r10, #0x2c4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b11c
    ldrb r1, [r10, #0xee0]
    add r0, r10, #0x2c4
    add r0, r0, #0xc00
    bic r1, r1, #0xf
    strb r1, [r10, #0xee0]
    and r1, r1, #0xff
    bic r1, r1, #0xf0
    orr r1, r1, #0x30
    strb r1, [r10, #0xee0]
    mov r1, #0x0
    bl func_0204b5b4
    add r0, r10, #0x2c4
    mov r1, #0x0
    add r0, r0, #0xc00
    mov r2, r1
    bl func_0204b5e8
    add r0, r10, #0x2c4
    add r0, r0, #0xc00
    mov r1, r10
    bl func_0204b12c
    ldr r4, =0x400000a
    mov r5, #0x6
    ldrh r2, [r4, #0x0]
    add r0, r4, #0x46
    mov r1, #0x1
    and r2, r2, #0x43
    orr r2, r2, #0x1d00
    strh r2, [r4, #0x0]
    ldrh r6, [r4, #0x2]
    mov r2, #0x2
    mov r3, #0xa
    and r6, r6, #0x43
    orr r6, r6, #0x1e00
    strh r6, [r4, #0x2]
    ldrh r6, [r4, #0x4]
    and r6, r6, #0x43
    orr r6, r6, #0x304
    orr r6, r6, #0x1c00
    strh r6, [r4, #0x4]
    str r5, [sp, #0x0]
    bl ColorEffect_ConfigureAlphaBlend
    add r0, r10, #0x1f8
    ldr r1, =0x3e9
    add r0, r0, #0xc00
    bl func_020e0434
    mov r4, r0
    add r0, r10, #0x1f8
    add r0, r0, #0xc00
    mov r1, #0x3e8
    bl func_020e0434
    mov r1, r0
    mov r0, r7
    mov r2, r4
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    add r1, r10, #0x3000
    str r0, [r1, #0xdc8]
    ldrb r0, [r1, #0xdc4]
    add r0, r0, #0x1
    strb r0, [r1, #0xdc4]
    b @L02154ce0
@L021546a4:
    cmp r2, #0x3
    bne @L02154948
    ldr r1, [r1, #0xdc8]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02154ce0
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdc8]
    add r2, sp, #0x2c
    add r3, sp, #0x28
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x2c]
    bl func_02046900
    mov r8, r0
    mov r9, #0x0
    add r4, r10, #0x2a4
    add r5, r10, #0x284
    add r6, r10, #0x2c4
    add r11, sp, #0x30
    b @L02154760
@L021546f8:
    ldr r0, [sp, #0x2c]
    mov r1, r9
    mov r2, r11
    add r3, sp, #0x24
    bl func_020467f0
    movs r1, r0
    beq @L0215475c
    cmp r9, #0x0
    bne @L02154730
    ldr r3, [sp, #0x24]
    mov r2, r10
    add r0, r6, #0xc00
    bl func_0204b174
    b @L0215475c
@L02154730:
    cmp r9, #0x8
    bgt @L0215474c
    ldr r3, [sp, #0x24]
    mov r2, r10
    add r0, r5, #0xc00
    bl func_0204b174
    b @L0215475c
@L0215474c:
    ldr r3, [sp, #0x24]
    mov r2, r10
    add r0, r4, #0xc00
    bl func_0204b174
@L0215475c:
    add r9, r9, #0x1
@L02154760:
    cmp r9, r8
    blt @L021546f8
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdc8]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mov r1, #0x0
    add r0, r10, #0x3000
    mvn r2, #0x0
    str r2, [r0, #0xdc8]
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    add r4, r10, #0x2a4
    mov r2, r1
    mov r3, r1
    add r0, r4, #0xc00
    str r1, [sp, #0x8]
    bl func_0204bc74
    mov r0, r4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b0e8
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    str r0, [sp, #0x4]
    add r0, r10, #0x2c4
    add r0, r0, #0xc00
    mov r2, r1
    mov r3, r1
    str r1, [sp, #0x8]
    bl func_0204bc74
    add r0, r10, #0x2c4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b0e8
    mov r1, #0x0
    str r1, [sp, #0x0]
    str r1, [sp, #0x4]
    mov r0, #0x20
    str r0, [sp, #0x8]
    mov r0, #0x18
    str r0, [sp, #0xc]
    ldr r2, =0xffff
    add r0, r10, #0x284
    str r2, [sp, #0x10]
    add r0, r0, #0xc00
    mov r2, r1
    mov r3, r1
    bl func_0204b8d0
    add r0, r10, #0x284
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b0e8
    mov r2, #0x0
    str r2, [sp, #0x0]
    mov r0, #0x14
    str r0, [sp, #0x4]
    mov r0, #0x10
    str r0, [sp, #0x8]
    mov r0, #0x2
    str r0, [sp, #0xc]
    ldr r1, =0xffff
    add r0, r10, #0x284
    str r1, [sp, #0x10]
    add r0, r0, #0xc00
    mov r1, #0x1
    mov r3, r2
    bl func_0204b8d0
    add r0, r10, #0x284
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b0e8
    mov r0, r10
    mov r1, #0x2400
    bl _ZN13SafeAllocator8AllocateEj
    add r4, r10, #0x1000
    str r0, [r4, #0x240]
    add r0, r10, #0x2c4
    mov r9, #0x0
    add r6, r10, #0xfa0
    add r5, r0, #0xc00
    ldr r11, =sCanvasSizes
    b @L021548e0
@L021548bc:
    mov r0, #0xe0
    mla r8, r9, r0, r6
    ldr r2, [r4, #0x240]
    ldr r3, [r11, r9, lsl #0x2]
    mov r0, r8
    mov r1, r10
    bl func_0204c7a8
    str r5, [r8, #0x4]
    add r9, r9, #0x1
@L021548e0:
    cmp r9, #0x3
    blt @L021548bc
    add r0, r10, #0x2c4
    add r1, r0, #0xc00
    add r0, r10, #0x2e4
    str r1, [r10, #0xf7c]
    mov r3, #0x1
    add r0, r0, #0xc00
    add r1, r10, #0xfa0
    mov r2, #0x3
    strb r3, [r10, #0xf96]
    bl func_0205cf78
    add r0, r10, #0x1f8
    ldr r1, =0x3ea
    add r0, r0, #0xc00
    bl func_020e0434
    mov r1, r0
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    add r1, r10, #0x3000
    str r0, [r1, #0xdc8]
    ldrb r0, [r1, #0xdc4]
    add r0, r0, #0x1
    strb r0, [r1, #0xdc4]
    b @L02154ce0
@L02154948:
    cmp r2, #0x4
    bne @L02154aa8
    ldr r1, [r1, #0xdc8]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02154ce0
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdc8]
    add r2, sp, #0x20
    add r3, sp, #0x1c
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x20]
    bl func_02046900
    mov r5, r0
    mov r0, r6
    bl func_0200fb08
    mov r6, r0
    add r0, r10, #0x1f8
    add r0, r0, #0xc00
    mov r1, #0x7d0
    mov r8, #0x0
    bl func_020e0434
    add r2, sp, #0x38
    mov r1, r0
    str r2, [sp, #0x0]
    mov r0, r8
    str r0, [sp, #0x4]
    ldr r0, [sp, #0x20]
    add r2, sp, #0xd0
    mov r3, r5
    bl func_0204684c
    cmp r0, #0x0
    beq @L02154a60
    add r0, r10, #0x294
    bl func_0207df90
    add r0, r10, #0xa70
    mov r9, r8
    add r4, r0, #0x1000
    add r11, sp, #0xd0
    b @L02154a50
@L021549ec:
    cmp r9, #0x23
    bne @L02154a08
    cmp r6, #0x2
    beq @L02154a4c
    cmp r6, #0x3
    bne @L02154a2c
    b @L02154a4c
@L02154a08:
    cmp r9, #0x24
    bne @L02154a1c
    cmp r6, #0x2
    bne @L02154a4c
    b @L02154a2c
@L02154a1c:
    cmp r9, #0x25
    bne @L02154a2c
    cmp r6, #0x3
    bne @L02154a4c
@L02154a2c:
    mov r0, #0x88
    mla r0, r8, r0, r4
    add r2, sp, #0x38
    ldr r1, [r11, r9, lsl #0x2]
    ldr r2, [r2, r9, lsl #0x2]
    add r3, r10, #0x14
    bl func_02047b30
    add r8, r8, #0x1
@L02154a4c:
    add r9, r9, #0x1
@L02154a50:
    cmp r9, r5
    blt @L021549ec
    add r0, r10, #0x294
    bl func_0207dfac
@L02154a60:
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdc8]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    ldr r1, =sStrings+0x29
    ldr r2, =sStrings+0x3f
    mov r0, r7
    add r4, r10, #0x3000
    mvn r5, #0x0
    mov r3, #0x0
    str r5, [r4, #0xdc8]
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    mov r1, r4
    str r0, [r1, #0xdc8]
    ldrb r0, [r1, #0xdc4]
    add r0, r0, #0x1
    strb r0, [r1, #0xdc4]
    b @L02154ce0
@L02154aa8:
    cmp r2, #0x5
    bne @L02154b3c
    ldr r1, [r1, #0xdc8]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02154ce0
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdc8]
    add r2, sp, #0x18
    add r3, sp, #0x14
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r10, #0x258
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x9e0
    add r0, r0, #0x1000
    bl _ZN12ItemSortList10InitializeEv
    mov r0, #0x0
    str r0, [sp, #0x0]
    str r0, [sp, #0x4]
    add r0, r10, #0x9e0
    ldr r2, [sp, #0x18]
    ldr r3, [sp, #0x14]
    add r0, r0, #0x1000
    add r1, r10, #0x258
    bl _ZN12ItemSortList4LoadEP13SafeAllocatorPKvjPKss
    add r1, r10, #0x3000
    ldr r1, [r1, #0xdc8]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    add r0, r10, #0x3000
    mvn r1, #0x0
    str r1, [r0, #0xdc8]
    ldrb r1, [r0, #0xdc4]
    add r1, r1, #0x1
    strb r1, [r0, #0xdc4]
    b @L02154ce0
@L02154b3c:
    ldr r1, =0x4000008
    add r0, r10, #0xa70
    ldrh r3, [r1, #0x0]
    mov r6, #0x8000
    add r7, r0, #0x1000
    bic r3, r3, #0x3
    orr r3, r3, #0x1
    strh r3, [r1, #0x0]
    ldrh r3, [r1, #0x2]
    add r2, r10, #0x234
    mov r8, #0x4000000
    bic r0, r3, #0x3
    orr r0, r0, #0x3
    strh r0, [r1, #0x2]
    ldrh r0, [r1, #0x4]
    add r3, r10, #0x1000
    sub r5, r6, #0xb000
    bic r0, r0, #0x3
    orr r0, r0, #0x2
    strh r0, [r1, #0x4]
    ldrh r9, [r1, #0x6]
    add r0, r2, #0x1800
    mov r4, #0x3000
    bic r2, r9, #0x3
    strh r2, [r1, #0x6]
    ldr r2, [r8, #0x0]
    mov r1, #0x85000
    bic r2, r2, #0x1f00
    orr r2, r2, #0x1f00
    str r2, [r8, #0x0]
    str r7, [r3, #0xa34]
    str r6, [r3, #0xa38]
    str r5, [r3, #0xa3c]
    str r4, [r3, #0xa40]
    str r5, [r3, #0xa44]
    mov r2, #0x17000
    str r4, [r3, #0xa48]
    bl _ZN11CursorFrame17SetTargetPositionEii
    add r0, r10, #0x234
    add r0, r0, #0x1800
    mov r1, #0x85000
    mov r2, #0x17000
    bl _ZN11CursorFrame11SetPositionEii
    add r0, r10, #0x234
    add r0, r0, #0x1800
    mov r1, #0x76000
    mov r2, #0x16000
    bl _ZN11CursorFrame13SetTargetSizeEii
    add r0, r10, #0x234
    add r0, r0, #0x1800
    mov r1, #0x76000
    mov r2, #0x16000
    bl _ZN11CursorFrame7SetSizeEii
    add r0, r10, #0x1000
    mov r1, #0x5000
    str r1, [r0, #0xa6c]
    add r1, r10, #0x3000
    mov r0, #0x0
    strb r0, [r1, #0xdb8]
    ldr r2, [r1, #0xdcc]
    mov r0, r10
    orr r2, r2, #0x400
    str r2, [r1, #0xdcc]
    bl _ZN13EquipmentMenu9SetCursorEv
    add r0, r10, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0xa30]
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0xc
    str r1, [r0, #0xdcc]
    bl _ZN9GameState11GetInstanceEv
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r4, [r0, #0x4fc]
    mov r0, #0x5
    mov r1, r4, lsl #0x18
    mov r1, r1, asr #0x18
    bl func_020dc7e8
    add r0, r10, #0x244
    bl _ZN13SafeAllocator5ResetEv
    add r1, r10, #0x2d00
    add r0, r10, #0x244
    add r0, r0, #0x1000
    ldrsh r1, [r1, #0x90]
    mov r2, #0x0
    bl _ZN14ItemInfoWindow10InitializeEsa
    add r2, r10, #0x1900
    ldrh r3, [r2, #0xb8]
    add r1, r10, #0x244
    add r0, r1, #0x1000
    orr r3, r3, #0xd0
    strh r3, [r2, #0xb8]
    bl _ZN14ItemInfoWindow16CreateAllocatorsEP13SafeAllocator
    ldr r1, [r10, #0xdf4]
    add r0, r10, #0x1000
    str r1, [r0, #0x28c]
    strb r4, [r0, #0x9be]
    add r0, r10, #0x3000
    mov r1, #0xff
    strb r1, [r0, #0xdc4]
    mov r0, #0x1
    b @L02154ce4
@L02154ce0:
    mov r0, #0x0
@L02154ce4:
    add sp, sp, #0x168
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void CursorFrame::SetTargetPosition(int x, int y)
{
    target_[0] = x + left_;
    target_[1] = y + top_;
}

void CursorFrame::SetPosition(int x, int y)
{
    current_[0] = x + left_;
    current_[1] = y + top_;
}

void CursorFrame::SetTargetSize(int width, int height)
{
    target_[2] = right_ + (width - left_);
    target_[3] = bottom_ + (height - top_);
}

void CursorFrame::SetSize(int width, int height)
{
    current_[2] = right_ + (width - left_);
    current_[3] = bottom_ + (height - top_);
}

void EquipmentMenu::LoadModelTable(void* file, unsigned int size)
{
    modelTableAllocator_.Reset();
    modelTable_.Initialize();
    modelTable_.Load(&modelTableAllocator_, file, size);
}

static void SetUnk56e(PartyMember* member, signed char value);

static inline void Translate(int x, int y, int z)
{
    GXFIFO_MATRIX_TRANSLATE = x;
    GXFIFO_MATRIX_TRANSLATE = y;
    GXFIFO_MATRIX_TRANSLATE = z;
}

static inline void PushTranslate(int x, int y, int z)
{
    GXFIFO_MATRIX_PUSH = 0;
    GXFIFO_MATRIX_TRANSLATE = x;
    GXFIFO_MATRIX_TRANSLATE = y;
    GXFIFO_MATRIX_TRANSLATE = z;
}


void EquipmentMenu::Update()
{
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    ticks_ = ticks;
    frame_.Update(1);
    infoWindow_.Update();
    if (UpdateFade())
    {
        UpdateLoading();
        return;
    }
    if (unk_3dd1 != 0 && unk_3dd1 != 8 && unk_3dd1 != 9)
    {
        UpdateDialog(ticks);
        UpdateLoading();
        return;
    }
    if (tapTimer_ > 0)
    {
        tapTimer_ -= ticks;
        if (tapTimer_ <= 0)
        {
            tapTimer_ = 0;
            tappedSlot_ = -2;
        }
    }
    if (sStates[state_] == NULL)
        return;
    (this->*sStates[state_])();
    UpdateLoading();
}

void EquipmentMenu::Draw2D()
{
    if (state_ == 1)
        return;
    if (state_ != 0)
    {
        if (state_ == 3)
        {
            int ticks = GameState::GetInstance()->GetTickCount();
            if (ticks == 0)
                ticks = 1;
            if (blinks_ > 0)
            {
                blinkTimer_ -= ticks;
                if (blinkTimer_ <= 0)
                {
                    if (!(flags_ & EQUIPMENT_FRAME_BLINK))
                    {
                        flags_ |= EQUIPMENT_FRAME_BLINK;
                        blinkTimer_ += 30;
                    }
                    else
                    {
                        flags_ &= ~EQUIPMENT_FRAME_BLINK;
                        blinkTimer_ += 30;
                        blinks_--;
                    }
                }
            }
            blinkTimer2_ -= ticks;
            if (blinkTimer2_ <= 0)
            {
                if (!(flags_ & EQUIPMENT_ARROWS_BLINK))
                {
                    flags_ |= EQUIPMENT_ARROWS_BLINK;
                    blinkTimer2_ += 30;
                }
                else
                {
                    flags_ &= ~EQUIPMENT_ARROWS_BLINK;
                    blinkTimer2_ += 30;
                }
            }
        }
        if (!(flags_ & EQUIPMENT_FRAME_BLINK))
            frame_.Draw(0, 0x7fff);
        if (!(flags_ & EQUIPMENT_ARROWS_BLINK))
            DrawKindArrows();
        DrawTabs();
        DrawPageArrows();
        DrawSortButton();
        DrawPageNumber();
        DrawCounts();
        func_0205d1e0(&window_);
        func_0205d228(&window_);
        func_0205d274(&window_);
    }
    DrawModels();
    if (unk_e64 != NULL && func_020e28dc(unk_e64))
        func_020e2794(unk_e64, unk_e68);
    DrawCursor();
    DrawKinds();
    if (!(flags_ & EQUIPMENT_NAMES) && unk_3e04 <= 0)
    {
        DrawNames();
        return;
    }
    unk_3e04--;
}

void EquipmentMenu::DrawSub()
{
    if (loadStep_ != 0xff)
        return;
    func_0205d2bc(&window_);
    DrawSortIcon();
    if (flags_ & EQUIPMENT_KIND_CHANGED)
    {
        func_0204b088(&backgrounds_[1], 0);
        flags_ &= ~EQUIPMENT_KIND_CHANGED;
    }
    if (flags_ & EQUIPMENT_NAMES)
    {
        WriteNames();
        flags_ &= ~EQUIPMENT_NAMES;
    }
    if (unk_e64 != NULL)
    {
        char* unk = *(char**)((char*)unk_e64 + 0x10);
        func_020e2d24(unk + 0x28, 0x1f, 1);
        func_020e2cc4(unk + 0x28, func_020e28dc(unk_e64));
        func_020e2834(unk_e64);
    }
    UpdateModels();
}

void EquipmentMenu::Reload()
{
    LoadEquipped();
    flags_ |= EQUIPMENT_LOAD_EQUIPPED;
    equippedStep_ = 0;
}

void EquipmentMenu::SetMember(int member, int change)
{
    short item = slots_[slot_].item_;
    infoWindow_.member_ = member;
    infoWindow_.flags_ |= 0x80;
    if (change)
        infoWindow_.ChangeItem(item);
    else
        infoWindow_.SetItem(item);
}

// NONMATCHING: the C matches 87.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::DrawLevel(int level, short x, int y, unsigned short color)
{
    MessageSystem* messages = func_020421a0();
    GXFIFO_MATRIX_PUSH = 0;
    GXFIFO_BEGIN_VTXS = 1;
    GXFIFO_MATRIX_TRANSLATE = 0;
    GXFIFO_MATRIX_TRANSLATE = -0x3ff000;
    GXFIFO_MATRIX_TRANSLATE = 0;
    int tens = level / 10;
    int units = level % 10;
    if (tens != 0)
    {
        short tensX = x;
        if (units == 1)
            tensX++;
        if (tens == 1)
            tensX++;
        func_02045f3c(messages, digits_[tens], tensX, y, color, 8, 0, 0, 0, 0x11);
    }
    short unitsX = x + 5;
    if (units == 1)
        unitsX++;
    func_02045f3c(messages, digits_[units], unitsX, y, color, 8, 0, 0, 0, 0x11);
    GXFIFO_END_VTXS = 0;
    GXFIFO_MATRIX_POP = 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _s32_div_f();
}

asm void EquipmentMenu::DrawLevel(int level, short x, int y, unsigned short color)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x18
    mov r9, r0
    mov r6, r1
    mov r8, r2
    mov r7, r3
    bl func_020421a0
    mov r4, r0
    ldr r2, =0x4000444
    mov r3, #0x0
    str r3, [r2, #0x0]
    mov r0, #0x1
    str r0, [r2, #0xbc]
    str r3, [r2, #0x2c]
    ldr r1, =0xffc01000
    str r3, [r2, #0x2c]
    mov r0, r6
    str r1, [r2, #0x2c]
    mov r1, #0xa
    bl _s32_div_f
    mov r5, r0
    mov r0, r6
    mov r1, #0xa
    bl _s32_div_f
    mov r6, r1
    cmp r5, #0x0
    mov r2, r8
    beq @L0215532c
    cmp r6, #0x1
    addeq r0, r8, #0x1
    moveq r0, r0, lsl #0x10
    moveq r2, r0, asr #0x10
    cmp r5, #0x1
    addeq r0, r2, #0x1
    moveq r0, r0, lsl #0x10
    moveq r2, r0, asr #0x10
    add r0, r9, #0x20c
    ldrh r3, [sp, #0x38]
    add r1, r0, #0x3c00
    mov r0, #0x6
    mla r1, r5, r0, r1
    str r3, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r5, #0x0
    str r5, [sp, #0x8]
    str r5, [sp, #0xc]
    str r5, [sp, #0x10]
    mov r5, #0x11
    mov r0, r4
    mov r3, r7
    str r5, [sp, #0x14]
    bl func_02045f3c
@L0215532c:
    add r0, r8, #0x5
    mov r0, r0, lsl #0x10
    mov r2, r0, asr #0x10
    cmp r6, #0x1
    addeq r0, r2, #0x1
    moveq r0, r0, lsl #0x10
    moveq r2, r0, asr #0x10
    add r0, r9, #0x20c
    ldrh r3, [sp, #0x38]
    add r1, r0, #0x3c00
    mov r0, #0x6
    mla r1, r6, r0, r1
    str r3, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r5, #0x0
    str r5, [sp, #0x8]
    str r5, [sp, #0xc]
    mov r0, r4
    mov r3, r7
    str r5, [sp, #0x10]
    mov r4, #0x11
    str r4, [sp, #0x14]
    bl func_02045f3c
    ldr r1, =0x4000504
    mov r0, r5
    str r0, [r1, #0x0]
    mov r0, #0x1
    str r0, [r1, #-0xbc]
    add sp, sp, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

// NONMATCHING: the C matches 92.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::GetSlotPosition(int slot, int* x, int* y)
{
    if (slot >= 0 && slot < 8)
    {
        *x = 0x85;
        *y = 0x17;
        return;
    }
    if (slot < 8 || slot >= 24)
        return;
    int index = slot - 8;
    *x = (index % 4) * 26 + 0x8d;
    *y = (index / 4) * 26 + 0x34;
}
#else
asm void EquipmentMenu::GetSlotPosition(int slot, int* x, int* y)
{
    stmdb sp!, {r3, lr}
    cmp r1, #0x0
    blt @L021553d8
    cmp r1, #0x8
    movlt r0, #0x85
    strlt r0, [r2, #0x0]
    movlt r0, #0x17
    strlt r0, [r3, #0x0]
    ldmltia sp!, {r3, pc}
@L021553d8:
    cmp r1, #0x8
    ldmltia sp!, {r3, pc}
    cmp r1, #0x18
    ldmgeia sp!, {r3, pc}
    sub lr, r1, #0x8
    mov r1, lr, lsr #0x1f
    rsb r0, r1, lr, lsl #0x1e
    mov r12, lr, asr #0x1
    add r1, r1, r0, ror #0x1e
    add r12, lr, r12, lsr #0x1e
    mov r0, #0x1a
    mul lr, r1, r0
    mov r1, r12, asr #0x2
    mul r0, r1, r0
    add r1, lr, #0x8d
    str r1, [r2, #0x0]
    add r0, r0, #0x34
    str r0, [r3, #0x0]
    ldmia sp!, {r3, pc}
}
#endif

// NONMATCHING: the C matches 80.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::InitializeSlots()
{
    long y;
    EquipmentSlot* slot;
    for (int i = 0; i < 8; i++)
    {
        EquipmentSlot* slot = &slots_[i];
        slot->vramState_ = &slotVramStates_[i];
        slot->model_ = &slotModels_[i];
        slot->x_ = 0x85000;
        slot->y_ = 0x16000;
        MenuModel* model = slot->model_;
        model->position_.x = 0x85000;
        model->position_.y = 0x16000;
        model->position_.z = 0;
    }
    for (int i = 0; i < 16; i++)
    {
        slot = &slots_[i + 8];
        slot->model_ = &slotModels_[i + 8];
        slot->vramState_ = &slotVramStates_[i + 8];
        unsigned int x = (i % 16 % 4) * 26 + 0x8d;
        y = (i % 16 / 4) * 26 + 0x34;
        MenuModel* model = slot->model_;
        slot->x_ = x << 12;
        slot->y_ = y << 12;
        model->position_.x = x << 12;
        model->position_.y = y << 12;
        model->position_.z = 0;
    }
}
#else
asm void EquipmentMenu::InitializeSlots()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov r2, #0x0
    add r1, r0, #0xd90
    add r3, r0, #0x30
    add r10, r3, #0x3000
    add r1, r1, #0x2000
    add r11, r0, #0x304
    mov r9, #0x85000
    mov r8, #0x16000
    mov r6, r2
    mov r3, #0x1c
    mov r4, #0x70
    mov r5, #0x88
    b @L0215548c
@L0215545c:
    mla lr, r2, r3, r1
    mla r12, r2, r4, r11
    mla r7, r2, r5, r10
    str r12, [lr, #0x4]
    str r7, [lr, #0x8]
    str r9, [lr, #0xc]
    str r8, [lr, #0x10]
    ldr r7, [lr, #0x8]
    add r2, r2, #0x1
    str r9, [r7, #0x1c]
    str r8, [r7, #0x20]
    str r6, [r7, #0x24]
@L0215548c:
    cmp r2, #0x8
    blt @L0215545c
    mov r12, #0x0
    add r1, r0, #0xd90
    mov r5, #0x1a
    add r2, r1, #0x2000
    add r3, r0, #0x30
    add r1, r0, #0x304
    add r0, r3, #0x3000
    mov r7, r12
    mov lr, #0x70
    mov r4, #0x88
    mov r6, r5
    b @L02155538
@L021554c4:
    mov r8, r12, lsr #0x1f
    rsb r3, r8, r12, lsl #0x1c
    add r9, r8, r3, ror #0x1c
    mov r10, r9, lsr #0x1f
    rsb r8, r10, r9, lsl #0x1e
    add r8, r10, r8, ror #0x1e
    mov r10, r9, asr #0x1
    add r10, r9, r10, lsr #0x1e
    mul r9, r8, r5
    add r3, r12, #0x8
    mov r8, r10, asr #0x2
    mul r10, r8, r6
    add r8, r10, #0x34
    mov r10, #0x1c
    mla r10, r3, r10, r2
    mla r11, r3, lr, r1
    str r11, [r10, #0x4]
    mla r11, r3, r4, r0
    add r9, r9, #0x8d
    mov r9, r9, lsl #0xc
    str r11, [r10, #0x8]
    mov r8, r8, lsl #0xc
    str r9, [r10, #0xc]
    str r8, [r10, #0x10]
    ldr r3, [r10, #0x8]
    add r12, r12, #0x1
    str r9, [r3, #0x1c]
    str r8, [r3, #0x20]
    str r7, [r3, #0x24]
@L02155538:
    cmp r12, #0x10
    blt @L021554c4
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

static const unsigned char sEquippedParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};

// NONMATCHING: the C matches 64.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::LoadEquipped()
{
    GameState* gameState = GameState::GetInstance();
    PartyMember* member =
        func_0200ff1c(gameState, func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_);
    short* equipment = func_02052e14(member);
    EquipmentSlot* slots = slots_;
    for (int i = 0; i < 8; i++)
    {
        slots[i].item_ = equipment[sEquippedParts[i]];
        slots[i].count_ = 1;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void EquipmentMenu::LoadEquipped()
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r4
    bl func_0200ff1c
    bl func_02052e14
    add r1, r5, #0xd90
    add r4, r1, #0x2000
    mov r6, #0x0
    ldr r12, =sEquippedParts
    mov r2, #0x1
    mov r1, #0x1c
    b @L021555b0
@L02155590:
    ldrb r3, [r12, r6]
    mul lr, r6, r1
    mov r3, r3, lsl #0x1
    ldrsh r3, [r0, r3]
    add r5, r4, lr
    add r6, r6, #0x1
    strh r3, [r4, lr]
    strb r2, [r5, #0x2]
@L021555b0:
    cmp r6, #0x8
    blt @L02155590
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void EquipmentMenu::LoadPage()
{
    static unsigned char sPageLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};
    char* party = func_02010828(GameState::GetInstance());
    short* items = func_0207c5f8(party + 0x1d4, sPageLists[kind_]);
    signed char* counts = func_0207c60c(party + 0x1d4, sPageLists[kind_]);
    signed char page = page_;
    for (int i = 0; i < 16; i++)
    {
        EquipmentSlot* slot = &slots_[i + 8];
        int index = i + page * 16;
        short item = items[index];
        signed char count = counts[index];
        if (item == slot->loadedItem_)
            slot->equipped_ = 1;
        else
            slot->equipped_ = 0;
        slot->item_ = item;
        slot->count_ = count;
    }
}

int EquipmentMenu::GetTouchedSlot(int x, int y)
{
    for (int i = 0; i < 16; i++)
    {
        int left = (i % 4) * 26 + 0x8d;
        int top = (i / 4) * 26 + 0x34;
        int right = left + 0x18;
        int bottom = top + 0x18;
        if (x >= left && y >= top && x <= right && y <= bottom)
            return i + 8;
    }
    return -1;
}

void EquipmentMenu::UpdateLoading()
{
    if (flags_ & EQUIPMENT_LOAD_DRAG)
    {
        if (dragStep_ == 0)
        {
            memset(dragFile_, 0, 0x200);
            EquipmentSlot* slot = &slots_[dragged_];
            slot->offset_ = -1;
            PartEntry* item = func_020dedd0(items_, slot->item_);
            if (item != NULL)
            {
                char path[0x80];
                __clear(path, sizeof(path));
                int number = func_020de234(item, 0);
                sprintf(path, func_020e0434(&texts_, 0x7d1), (char)item->letter_, number);
                if (LoadFileIntoMemory(path, dragFile_, NULL))
                    slot->offset_ = 0;
                int x;
                int y;
                GetSlotPosition(dragged_, &x, &y);
                func_0203a46c(&dragModel_, x << 12, y << 12, 0x2000);
                dragStep_++;
                loading_++;
            }
            flags_ &= ~EQUIPMENT_LOAD_DRAG;
        }
    }
    else if (flags_ & EQUIPMENT_LOAD_ITEM)
    {
        if (unk_3da8 == 0)
        {
            memset(itemFile_, 0, 0x200);
            EquipmentSlot* slot = &slots_[unk_3dac];
            slot->offset_ = -1;
            PartEntry* item = func_020dedd0(items_, slot->item_);
            if (item != NULL)
            {
                char path[0x80];
                __clear(path, sizeof(path));
                int number = func_020de234(item, 0);
                sprintf(path, func_020e0434(&texts_, 0x7d1), (char)item->letter_, number);
                if (LoadFileIntoMemory(path, itemFile_, NULL))
                    slot->offset_ = 0;
                unk_3da8++;
                loading_++;
            }
            flags_ &= ~EQUIPMENT_LOAD_ITEM;
        }
    }
    else if (flags_ & EQUIPMENT_LOAD_EQUIPPED)
    {
        if (equippedStep_ == 0)
        {
            for (int i = 0; i < 8; i++)
            {
                slots_[i].Unload();
                slots_[i].offset_ = -1;
            }
            equippedStart_ = 0;
            equippedEnd_ = 8;
            equippedStep_++;
            loading_++;
        }
        else if (equippedStep_ == 2)
        {
            memset(equippedFiles_, 0, 0x800);
            int offset = 0;
            signed char count = 0;
            for (int i = equippedStart_; i < equippedEnd_; i++)
            {
                EquipmentSlot* slot = &slots_[i];
                slot->offset_ = -1;
                PartEntry* item = func_020dedd0(items_, slot->item_);
                if (item != NULL)
                {
                    unsigned int size = 0;
                    char path[0x80];
                    __clear(path, sizeof(path));
                    int number = func_020de234(item, 0);
                    sprintf(path, func_020e0434(&texts_, 0x7d1), (char)item->letter_, number);
                    if (LoadFileIntoMemory(path, equippedFiles_ + offset, &size))
                    {
                        slot->offset_ = offset;
                        size = (size + 3) & ~3;
                        offset += size;
                    }
                }
                if (++count == 4)
                    break;
            }
            if (equippedStart_ == equippedEnd_)
            {
                equippedStep_++;
                flags_ &= ~EQUIPMENT_LOAD_EQUIPPED;
            }
        }
    }
    else if (flags_ & EQUIPMENT_LOAD_PAGE)
    {
        if (pageStep_ == 0)
        {
            for (int i = 8; i < 24; i++)
            {
                EquipmentSlot* slot = &slots_[i];
                if (slot->equipped_ == 0)
                {
                    slot->Unload();
                    slot->offset_ = -1;
                }
            }
            pageStart_ = 8;
            pageEnd_ = 24;
            pageStep_++;
            loading_++;
        }
        else if (pageStep_ == 2)
        {
            memset(pageFiles_, 0, 0x800);
            int offset = 0;
            signed char count = 0;
            for (int i = pageStart_; i < pageEnd_; i++)
            {
                EquipmentSlot* slot = &slots_[i];
                slot->offset_ = -1;
                if (slot->equipped_ != 0)
                    continue;
                PartEntry* item = func_020dedd0(items_, slot->item_);
                if (item != NULL)
                {
                    unsigned int size = 0;
                    char path[0x80];
                    __clear(path, sizeof(path));
                    int number = func_020de234(item, 0);
                    sprintf(path, func_020e0434(&texts_, 0x7d1), (char)item->letter_, number);
                    if (LoadFileIntoMemory(path, pageFiles_ + offset, &size))
                    {
                        slot->offset_ = offset;
                        size = (size + 3) & ~3;
                        offset += size;
                    }
                }
                if (++count == 4)
                    break;
            }
            pageStep_++;
            if (pageStart_ == pageEnd_)
            {
                for (int i = 8; i < 24; i++)
                    slots_[i].equipped_ = 0;
                pageStep_ = 4;
                flags_ &= ~EQUIPMENT_LOAD_PAGE;
            }
        }
    }
}

void EquipmentSlot::Unload()
{
    if (vramState_ != NULL)
        func_0207df50(vramState_);
    if (model_ != NULL)
        func_02047230(model_);
    loadedItem_ = -1;
}

void EquipmentMenu::UpdateModels()
{
    unsigned char loading = loading_;
    if (loading != 0)
    {
        if (dragStep_ == 1)
        {
            EquipmentSlot* slot = &slots_[dragged_];
            if (slot->offset_ == 0)
            {
                func_02047230(&dragModel_);
                func_0207df50(&dragVramState_);
                func_0207df90(&dragVramState_);
                dragAllocator_.Reset();
                func_02047b40(&dragModel_, dragFile_, &dragAllocator_);
                func_0207dfac(&dragVramState_);
            }
            slot->offset_ = -1;
            slot->equipped_ = 0;
            memset(dragFile_, 0, 0x200);
            loading_--;
            dragStep_ = 0;
        }
        else if (unk_3da8 == 1)
        {
            EquipmentSlot* slot = &slots_[unk_3dac];
            VRAMManagerState* vramState = slot->vramState_;
            MenuModel* model = slot->model_;
            if (slot->offset_ == 0)
            {
                slot->Unload();
                func_0207df90(vramState);
                equippedAllocators_[unk_3dac].Reset();
                func_02047b40(model, itemFile_, &equippedAllocators_[unk_3dac]);
                slot->loadedItem_ = slot->item_;
                func_0207dfac(vramState);
            }
            model->unk_82 = 0x1f;
            model->alpha_ = 0x7fff;
            func_0203a46c(model, slot->x_, slot->y_, 0);
            slot->offset_ = -1;
            slot->equipped_ = 0;
            memset(itemFile_, 0, 0x200);
            loading_--;
            unk_3da8 = 0;
        }
        else if (equippedStep_ == 1)
        {
            for (int i = 0; i < 8; i++)
                equippedAllocators_[i].Reset();
            equippedStep_++;
        }
        else if (equippedStep_ == 2)
        {
            signed char count = 0;
            int i = equippedStart_;
            for (; i < equippedEnd_; i++)
            {
                if (count == 4)
                    break;
                EquipmentSlot* slot = &slots_[i];
                VRAMManagerState* vramState = slot->vramState_;
                int offset = slot->offset_;
                MenuModel* model = slot->model_;
                if (offset >= 0)
                {
                    slot->Unload();
                    func_0207df90(vramState);
                    equippedAllocators_[i].Reset();
                    func_02047b40(model, equippedFiles_ + offset, &equippedAllocators_[i]);
                    slot->loadedItem_ = slot->item_;
                    func_0207dfac(vramState);
                }
                model->unk_82 = 0x1f;
                model->alpha_ = 0x7fff;
                func_0203a46c(model, slot->x_, slot->y_, 0);
                slot->offset_ = -1;
                slot->equipped_ = 0;
                count++;
            }
            memset(equippedFiles_, 0, 0x800);
            equippedStart_ += count;
        }
        else if (equippedStep_ == 3)
        {
            loading_ = loading - 1;
            equippedStep_ = 0;
        }
        else if (pageStep_ == 1)
        {
            for (int i = 0; i < 16; i++)
            {
                if (slots_[i + 8].equipped_ == 0)
                    itemAllocators_[i].Reset();
            }
            pageStep_++;
        }
        else if (pageStep_ == 3)
        {
            signed char count = 0;
            int i = pageStart_;
            for (; i < pageEnd_; i++)
            {
                if (count == 4)
                    break;
                EquipmentSlot* slot = &slots_[i];
                VRAMManagerState* vramState = slot->vramState_;
                MenuModel* model = slot->model_;
                if (slot->equipped_ != 0)
                {
                    count++;
                    continue;
                }
                int offset = slot->offset_;
                if (offset >= 0)
                {
                    slot->Unload();
                    func_0207df90(vramState);
                    itemAllocators_[i - 8].Reset();
                    func_02047b40(model, pageFiles_ + offset, &itemAllocators_[i - 8]);
                    slot->loadedItem_ = slot->item_;
                    func_0207dfac(vramState);
                }
                model->unk_82 = 0x1f;
                model->alpha_ = 0x7fff;
                func_0203a46c(model, slot->x_, slot->y_, 0);
                slot->offset_ = -1;
                slot->equipped_ = 0;
                count++;
            }
            memset(pageFiles_, 0, 0x800);
            pageStart_ += count;
            pageStep_ = 2;
        }
        else if (pageStep_ == 4)
        {
            loading_ = loading - 1;
            pageStep_ = 0;
        }
        flags_ |= EQUIPMENT_LOADING;
        return;
    }
    flags_ &= ~EQUIPMENT_LOADING;
}

void EquipmentMenu::UpdateTouch()
{
    int x;
    int y;
    func_02012a84(&data_02114e54, &x, &y);
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    if (data_02114e54.touching_)
    {
        if (x == 0 || y == 0)
            return;
        MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
        if (!(flags_ & EQUIPMENT_STATE_0) && (screen->flags_ & MEMBER_SCREEN_BACK_PRESSED))
        {
            func_0205eaa0(data_02108760, 0x1b, 0);
            SetState(1);
            return;
        }
        TouchTop(x, y);
        if (!(flags_ & EQUIPMENT_STATE_0) && x >= 0x80 && y >= 0xb0)
        {
            SetState(7);
            flags_ |= EQUIPMENT_SORT;
            return;
        }
        if (unk_3dc0 != -1)
            return;
        TouchPage(x, y);
        TouchModel(x, y);
        if (x > 0x83 && y > 0x15 && y < 0x2e)
        {
            SetState(3);
            slot_ = kind_;
            MoveFrame(state_, 0);
        }
        if (dragged_ < 0)
            return;
        if (tappedSlot_ == dragged_)
        {
            if (tapTimer_ > 0)
            {
                if (slots_[slot_].item_ >= 0)
                {
                    SetState(5);
                    func_0205eaa0(data_02108760, 1, 0);
                    screen->flags_ &= ~MEMBER_SCREEN_TURNING;
                    screen->flags_ &= ~MEMBER_SCREEN_CHANGE_MEMBER;
                }
                func_02047230(&dragModel_);
                dragged_ = -1;
                unk_3dc0 = -1;
                touchTime_ = 0;
                tappedSlot_ = -2;
                tapTimer_ = 0;
                return;
            }
            tappedSlot_ = -2;
            tapTimer_ = 0;
        }
        touchTime_ = 0;
        touchX_ = x;
        touchY_ = y;
    }
    else if (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0)
    {
        Drag(x, y);
        if (dragged_ >= 0)
            touchTime_ += ticks;
    }
    else if (data_02114e54.unk_54 != 0)
    {
        if (dragged_ >= 0)
        {
            int dx = touchX_ - (short)x;
            int dy = touchY_ - (short)y;
            int moved = 0;
            if (dx * dx + dy * dy >= 25)
                moved = 1;
            if (touchTime_ <= 20 && moved == 0)
            {
                tapTimer_ = 20;
                tappedSlot_ = dragged_;
            }
            else
            {
                touchTime_ = 0;
                tappedSlot_ = -2;
                tapTimer_ = 0;
            }
            touchX_ = -1;
            touchY_ = -1;
        }
        Drop(x, y);
        func_02047230(&dragModel_);
        dragged_ = -1;
        unk_3dc0 = -1;
    }
}

// NONMATCHING: the C matches 97.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::TouchTop(int x, int y)
{
    int changed = 0;
    if ((flags_ & EQUIPMENT_KINDS) && y > 1 && y < 0x13 && x > 0x81 && x < 0xff)
    {
        unsigned char kind = kind_;
        int left = 0x71;
        for (int i = 0; i < 8; i++)
        {
            left += 0x10;
            if (i == 7)
                left--;
            if (x >= left && x < left + 0x10)
            {
                kind = i;
                break;
            }
        }
        flags_ |= EQUIPMENT_KIND_CHANGED;
        changed = SetKind(kind, 0);
        SetState(2);
        MoveFrame(state_, kind);
    }
    if ((flags_ & EQUIPMENT_ARROWS) && y > 0x9d && y < 0xae)
    {
        int direction = 0;
        if (x > 0x89 && x < 0x99)
            direction = -1;
        if (x > 0xe6 && x < 0xf6)
            direction = 1;
        if (direction == 0)
            return;
        changed = TurnPage(direction);
        if (direction < 0)
            flags_ |= EQUIPMENT_PREVIOUS_PAGE;
        else
            flags_ |= EQUIPMENT_NEXT_PAGE;
    }
    if (changed)
        LoadPage();
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13EquipmentMenu7SetKindEhi(); // EquipmentMenu::SetKind
    void _ZN13EquipmentMenu8LoadPageEv(); // EquipmentMenu::LoadPage
    void _ZN13EquipmentMenu8SetStateEh(); // EquipmentMenu::SetState
    void _ZN13EquipmentMenu8TurnPageEi(); // EquipmentMenu::TurnPage
    void _ZN13EquipmentMenu9MoveFrameEjh(); // EquipmentMenu::MoveFrame
}

asm void EquipmentMenu::TouchTop(int x, int y)
{
    stmdb sp!, {r4, r5, r6, r7, r8, lr}
    mov r8, r0
    add r0, r8, #0x3000
    ldr r3, [r0, #0xdcc]
    mov r7, r1
    mov r6, r2
    tst r3, #0x4
    mov r5, #0x0
    beq @L0215671c
    cmp r6, #0x1
    ble @L0215671c
    cmp r6, #0x13
    bge @L0215671c
    cmp r7, #0x81
    ble @L0215671c
    cmp r7, #0xff
    bge @L0215671c
    ldrb r4, [r0, #0xdbc]
    mov r1, #0x71
    b @L021566d0
@L021566a8:
    add r1, r1, #0x10
    cmp r5, #0x7
    subeq r1, r1, #0x1
    cmp r7, r1
    add r0, r1, #0x10
    blt @L021566cc
    cmp r7, r0
    andlt r4, r5, #0xff
    blt @L021566d8
@L021566cc:
    add r5, r5, #0x1
@L021566d0:
    cmp r5, #0x8
    blt @L021566a8
@L021566d8:
    add r3, r8, #0x3000
    ldr r1, [r3, #0xdcc]
    mov r0, r8
    orr r5, r1, #0x100
    mov r1, r4
    mov r2, #0x0
    str r5, [r3, #0xdcc]
    bl _ZN13EquipmentMenu7SetKindEhi
    mov r5, r0
    mov r0, r8
    mov r1, #0x2
    bl _ZN13EquipmentMenu8SetStateEh
    add r0, r8, #0x3000
    ldrb r1, [r0, #0xdb8]
    mov r0, r8
    mov r2, r4
    bl _ZN13EquipmentMenu9MoveFrameEjh
@L0215671c:
    add r0, r8, #0x3000
    ldr r0, [r0, #0xdcc]
    tst r0, #0x8
    beq @L02156798
    cmp r6, #0x9d
    ble @L02156798
    cmp r6, #0xae
    bge @L02156798
    cmp r7, #0x89
    mov r4, #0x0
    ble @L02156750
    cmp r7, #0x99
    sublt r4, r4, #0x1
@L02156750:
    cmp r7, #0xe6
    ble @L02156760
    cmp r7, #0xf6
    movlt r4, #0x1
@L02156760:
    cmp r4, #0x0
    ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
    mov r0, r8
    mov r1, r4
    bl _ZN13EquipmentMenu8TurnPageEi
    mov r5, r0
    add r0, r8, #0x3000
    cmp r4, #0x0
    ldrlt r1, [r0, #0xdcc]
    orrlt r1, r1, #0x20000
    strlt r1, [r0, #0xdcc]
    ldrge r1, [r0, #0xdcc]
    orrge r1, r1, #0x40000
    strge r1, [r0, #0xdcc]
@L02156798:
    cmp r5, #0x0
    ldmeqia sp!, {r4, r5, r6, r7, r8, pc}
    mov r0, r8
    bl _ZN13EquipmentMenu8LoadPageEv
    ldmia sp!, {r4, r5, r6, r7, r8, pc}
}
#endif

void EquipmentMenu::TouchPage(int x, int y)
{
    GameState::GetInstance();
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    if (!CanEquip(screen->member_))
        return;
    dragged_ = GetTouchedSlot(x, y);
    if (dragged_ >= 8 && dragged_ < 24)
    {
        if (slots_[dragged_].item_ == -1)
        {
            dragged_ = -1;
            unk_3dc0 = -1;
            return;
        }
        SetState(4);
        slot_ = dragged_;
        MoveFrame(state_, slot_);
        func_0205bb04(&cursor_, slot_ - 8);
        swapped_ = (slot_ - 8) + page_ * 16;
        unk_3dc0 = 0;
        flags_ |= EQUIPMENT_LOAD_DRAG;
        func_0205eaa0(data_02108760, 2, 0);
        screen->flags_ &= ~MEMBER_SCREEN_TURNING;
        screen->flags_ &= ~MEMBER_SCREEN_CHANGE_MEMBER;
        flags_ &= ~EQUIPMENT_KINDS;
        flags_ &= ~EQUIPMENT_ARROWS;
        return;
    }
    dragged_ = -1;
    unk_3dc0 = -1;
}

void EquipmentMenu::TouchModel(int x, int y)
{
    GameState* gameState;
    Object3D* body;
    gameState = GameState::GetInstance();
    static const Vector3fix sTouchOffsets[8] = {
        {0, 0xd000, 0},          {0, 0x18000, 0},         {0, 0, 0},       {-0x8000, 0x7000, 0x6000},
        {0x6000, 0x7000, 0x4000}, {0, 0x7000, 0},          {-0x5000, 0xa000, 0x4000}, {0x5000, 0xa000, 0x4000},
    };
    static const signed char sTouchParts[8] = {0, 6, 5, 7, 8, 1, 4, 4};
    static unsigned char sTouchKinds[8] = {3, 2, 6, 0, 1, 5, 4, 4};
    static unsigned char sTouchLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};
    unsigned char page;
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    unsigned int member = screen->member_;
    if (!CanEquip(member))
        return;
    body = screen->GetBody();
    GetTouchedSlot(x, y);
    short item = -1;
    unsigned char kind = 0xff;
    if (x > 0 && x < 0x80)
    {
        int screenX[8];
        void* camera;
        int dx;
        int screenY[8];
        camera = func_020100bc(gameState);
        int count;
        Matrix4x3 matrix;
        Vector3fix positions[8];
        matrix = RotationMatrixY(body->rotation_.y);
        for (int i = 0; i < 8; i++)
        {
            Mat4x3_ApplyToVector(&sTouchOffsets[i], &matrix, &positions[i]);
            func_0202ec84(camera, &positions[i], &screenX[i], &screenY[i]);
        }
        PartyMember* partyMember = func_0200ff1c(gameState, member);
        count = 0;
        float radii[8];
        int touched[8];
        for (int i = 0; i < 8; i++)
        {
            radii[i] = 20.0f;
            int dy = y - screenY[i];
            int dx = x - screenX[i];
            if ((float)func_0200b454(dx * dx + dy * dy) < radii[i])
                touched[count++] = i;
        }
        if (count > 0)
        {
            int equippedCount = 0;
            int found = 0;
            int equipped[8];
            for (int i = 0; i < count; i++)
            {
                int part = touched[i];
                if (func_02052df8(partyMember, sTouchParts[part]) > 0)
                {
                    equipped[equippedCount] = part;
                    found = 1;
                    equippedCount++;
                }
            }
            if (found)
            {
                int best = equipped[0];
                int bestZ = positions[best].z;
                for (int i = 1; i < equippedCount; i++)
                {
                    int part = equipped[i];
                    if (bestZ < positions[part].z)
                    {
                        best = part;
                        bestZ = positions[part].z;
                    }
                }
                kind = sTouchKinds[best];
                item = func_02052df8(partyMember, sTouchParts[best]);
            }
            else
            {
                int best = touched[0];
                int bestZ = positions[best].z;
                for (int i = 1; i < count; i++)
                {
                    int part = touched[i];
                    if (bestZ < positions[part].z)
                    {
                        best = part;
                        bestZ = positions[part].z;
                    }
                }
                kind = sTouchKinds[best];
                if (kind_ != kind)
                {
                    SetKind(kind, 1);
                    slot_ = 8;
                    SetState(4);
                    MoveFrame(state_, slot_);
                    flags_ |= EQUIPMENT_KIND_CHANGED;
                    LoadPage();
                    return;
                }
            }
        }
    }
    else if (x > 0x84 && x < 0x9d && y > 0x16 && y < 0x2d)
    {
        kind = kind_;
        item = slots_[kind].item_;
    }
    if (item <= 0)
        return;
    int changed = 0;
    if (kind_ != kind)
    {
        changed = 1;
        SetKind(kind, 1);
        flags_ |= EQUIPMENT_KIND_CHANGED;
    }
    short* items = func_0207c5f8(func_02010828(gameState) + 0x1d4, sTouchLists[kind_]);
    int empty = -1;
    int index = -1;
    for (short i = 0; i < itemCounts_[kind_]; i++)
    {
        short other = items[i];
        if (item == other)
        {
            index = i;
            break;
        }
        if (empty < 0 && other == -1)
            empty = i;
    }
    if (index < 0)
        index = empty;
    page = index / 16;
    if (page_ != page)
    {
        lastPage_ = page_;
        page_ = page;
        changed = 1;
        pages_[kind_] = page_;
    }
    if (changed)
    {
        LoadPage();
        flags_ |= EQUIPMENT_LOAD_PAGE;
        pageStep_ = 0;
    }
    SetState(3);
    dragged_ = kind_;
    slot_ = dragged_;
    func_0205bb04(&cursor_, dragged_);
    unk_3dc0 = 1;
    flags_ |= EQUIPMENT_LOAD_DRAG;
    func_0205eaa0(data_02108760, 2, 0);
    screen->flags_ &= ~MEMBER_SCREEN_TURNING;
    screen->flags_ &= ~MEMBER_SCREEN_CHANGE_MEMBER;
    flags_ &= ~EQUIPMENT_KINDS;
    flags_ &= ~EQUIPMENT_ARROWS;
}

// NONMATCHING: the C matches 59.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::Drag(int x, int y)
{
    long modelX;
    if (dragged_ < 0)
        return;
    Vector3fix position = dragModel_.position_;
    if (modelX < 1)
        modelX = 1;
    unsigned long currentX;
    long currentY = position.y >> 12;
    long modelY = y - 12;
    if (modelX > 0xe7)
        modelX = 0xe7;
    if (modelY < 1)
        modelY = 1;
    currentX = position.x >> 12;
    if (modelY > 0xa7)
        modelY = 0xa7;
    if (abs(currentX - modelX) < 3)
        modelX = currentX;
    if (abs(currentY - modelY) < 3)
        modelY = currentY;
    func_0203a46c(&dragModel_, modelX << 12, modelY << 12, 0x2000);
}
#else
asm void EquipmentMenu::Drag(int x, int y)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
    sub sp, sp, #0xc
    mov r5, r0
    add r0, r5, #0x3d00
    ldrsh r0, [r0, #0x78]
    mov r6, r1
    mov r3, r2
    cmp r0, #0x0
    blt @L02156ec4
    add r0, r5, #0x10c
    add r0, r0, #0x3c00
    add r4, sp, #0x0
    ldmia r0, {r0, r1, r2}
    stmia r4, {r0, r1, r2}
    sub r4, r6, #0xc
    ldr r1, [sp, #0x0]
    ldr r0, [sp, #0x4]
    cmp r4, #0x1
    movlt r4, #0x1
    cmp r4, #0xe7
    sub r8, r3, #0xc
    movgt r4, #0xe7
    cmp r8, #0x1
    movlt r8, #0x1
    cmp r8, #0xa7
    mov r6, r1, asr #0xc
    mov r7, r0, asr #0xc
    movgt r8, #0xa7
    sub r0, r6, r4
    bl abs
    cmp r0, #0x3
    sub r0, r7, r8
    movlt r4, r6
    bl abs
    cmp r0, #0x3
    movlt r8, r7
    add r0, r5, #0xcf0
    add r0, r0, #0x3000
    mov r1, r4, lsl #0xc
    mov r2, r8, lsl #0xc
    mov r3, #0x2000
    bl func_0203a46c
@L02156ec4:
    add sp, sp, #0xc
    ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
}
#endif

void EquipmentMenu::Drop(int x, int y)
{
    static unsigned char sDropLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};
    if (dragged_ < 0)
        return;
    GameState::GetInstance();
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    Vector3fix position = dragModel_.position_;
    MenuModel* model = slots_[dragged_].model_;
    position.z = 0;
    model->SetPosition(&position);
    model->unk_82 = 0;
    if (dragged_ >= 0 && dragged_ < 8)
        model->unk_82 = 0x1f;
    if (x < 0x80)
    {
        if (unk_3dc0 == 0)
            Equip(slots_[dragged_].item_, 0);
    }
    else if (y > 0x15 && y < 0x2e)
    {
        if (x > 0x83 && unk_3dc0 == 0)
            Equip(slots_[dragged_].item_, 0);
    }
    else if (y > 0x30 && unk_3dc0 == 1)
    {
        Equip(0xffff, 0);
    }
    if (unk_3dc0 == 0)
    {
        int slot = GetTouchedSlot(x, y);
        if (slot >= 8 && slot < 24 && slot_ != slot)
        {
            short index = (slot - 8) + page_ * 16;
            char* party = func_02010828(GameState::GetInstance());
            short* items = func_0207c5f8(party + 0x1d4, sDropLists[kind_]);
            signed char* counts = func_0207c60c(party + 0x1d4, sDropLists[kind_]);
            short swapped = swapped_;
            short item = items[swapped];
            signed char count = counts[swapped];
            items[swapped] = items[index];
            counts[swapped_] = counts[index];
            items[index] = item;
            counts[index] = count;
            LoadPage();
            flags_ |= EQUIPMENT_LOAD_PAGE;
            pageStep_ = 0;
            swapped_ = -1;
            slot_ = slot;
        }
    }
    MoveFrame(state_, slot_);
    func_0205bb04(&cursor_, slot_ - 8);
    screen->flags_ |= MEMBER_SCREEN_TURNING | MEMBER_SCREEN_CHANGE_MEMBER;
    flags_ |= EQUIPMENT_KINDS | EQUIPMENT_ARROWS;
}

void MenuModel::SetPosition(const Vector3fix* position)
{
    position_.x = position->x;
    position_.y = position->y;
    position_.z = position->z;
}

int EquipmentMenu::IsConfirmed()
{
    int confirmed = 0;
    if (!func_02012444(data_02114e30, 0x30) && func_02012444(data_02114e30, 0x401))
        confirmed = 1;
    return confirmed;
}

// NONMATCHING: the C matches 87.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::SetCursor()
{
    int columns;
    int rows;
    int unk;
    int count;
    int unk2;
    short index;
    signed char unk3;
    signed char unk4;
    switch (state_)
    {
    case 0:
        rows = 8;
        columns = 1;
        unk = 0;
        count = 8;
        unk2 = 1;
        unk3 = 0;
        unk4 = 1;
        index = kind_;
        break;
    case 2:
        rows = 1;
        columns = 8;
        unk = 0;
        unk2 = 1;
        count = 8;
        unk3 = 1;
        unk4 = 0;
        index = kind_;
        break;
    case 3:
        rows = 1;
        columns = 8;
        unk = 0;
        unk2 = 1;
        count = 8;
        unk3 = 1;
        unk4 = 0;
        index = kind_;
        break;
    case 4:
    case 6:
        unk = 1;
        columns = 4;
        rows = 4;
        unk2 = 1;
        unk3 = 1;
        index = (short)(slot_ - 8);
        count = 16;
        unk4 = 0;
        break;
    }
    func_0205bef8(&cursor_);
    func_0205ba68(&cursor_, columns, rows, unk);
    func_0205bacc(&cursor_, count);
    cursor_.unk_4 = unk2;
    func_0205bb04(&cursor_, (short)index);
    cursor_.unk_3c = unk3;
    cursor_.unk_3d = unk4;
}
#else
asm void EquipmentMenu::SetCursor()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov r9, r0
    add r1, r9, #0x3000
    ldrb r0, [r1, #0xdb8]
    cmp r0, #0x6
    addls pc, pc, r0, lsl #0x2
    b @L021572b0
@L021571ec:
    b @L02157208
    b @L021572b0
    b @L02157230
    b @L02157258
    b @L02157280
    b @L021572b0
    b @L02157280
@L02157208:
    mov r0, #0x8
    mov r4, #0x1
    str r0, [sp, #0x0]
    mov r11, #0x0
    mov r10, r0
    mov r5, r4
    mov r7, r11
    mov r8, r4
    ldrb r6, [r1, #0xdbc]
    b @L021572b0
@L02157230:
    mov r0, #0x1
    str r0, [sp, #0x0]
    mov r4, #0x8
    mov r11, #0x0
    mov r5, r0
    mov r10, r4
    mov r7, r5
    mov r8, r11
    ldrb r6, [r1, #0xdbc]
    b @L021572b0
@L02157258:
    mov r0, #0x1
    str r0, [sp, #0x0]
    mov r4, #0x8
    mov r11, #0x0
    mov r5, r0
    mov r10, r4
    mov r7, r5
    mov r8, r11
    ldrb r6, [r1, #0xdbc]
    b @L021572b0
@L02157280:
    add r0, r9, #0x3d00
    ldrsb r0, [r0, #0xbb]
    mov r11, #0x1
    mov r4, #0x4
    sub r0, r0, #0x8
    mov r0, r0, lsl #0x10
    str r4, [sp, #0x0]
    mov r5, r11
    mov r7, r11
    mov r6, r0, asr #0x10
    mov r10, #0x10
    mov r8, #0x0
@L021572b0:
    add r0, r9, #0x1f4
    add r0, r0, #0x1800
    bl func_0205bef8
    add r0, r9, #0x1f4
    ldr r2, [sp, #0x0]
    add r0, r0, #0x1800
    mov r1, r4
    mov r3, r11
    bl func_0205ba68
    add r0, r9, #0x1f4
    mov r1, r10
    add r0, r0, #0x1800
    bl func_0205bacc
    add r0, r9, #0x1f4
    add r2, r9, #0x1000
    add r0, r0, #0x1800
    mov r1, r6
    str r5, [r2, #0x9f8]
    bl func_0205bb04
    add r0, r9, #0x1000
    strb r7, [r0, #0xa30]
    strb r8, [r0, #0xa31]
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void EquipmentMenu::UpdateKeys()
{
    if (func_02012444(data_02114e30, 2))
    {
        SetState(1);
        MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
        screen->flags_ |= MEMBER_SCREEN_BACK_PRESSED;
        func_0205eaa0(data_02108760, 0x1b, 0);
        return;
    }
    if (func_02012444(data_02114e30, 4))
    {
        if (state_ == 2 || state_ == 3 || state_ == 4)
        {
            SetState(7);
            flags_ |= EQUIPMENT_SORT;
            return;
        }
    }
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    func_0205bf58(&cursor_, ticks);
    func_0205bb84(&cursor_);
    switch (state_)
    {
    case 2:
        UpdateKinds();
        return;
    case 3:
        UpdateEquipped();
        return;
    case 4:
        UpdatePage();
        return;
    }
}

void EquipmentMenu::UpdateKinds()
{
    if (func_02012444(data_02114e30, 0x80))
    {
        SetState(3);
        slot_ = kind_;
        if (func_02012444(data_02114e30, 0x80))
            func_0205eaa0(data_02108760, 2, 0);
        else if (IsConfirmed())
            func_0205eaa0(data_02108760, 1, 0);
        MoveFrame(state_, slot_);
        return;
    }
    if (!SetKind(func_0205bb84(&cursor_), 0))
        return;
    flags_ |= EQUIPMENT_KIND_CHANGED;
    MoveFrame(state_, kind_);
    LoadPage();
}

void EquipmentMenu::UpdateEquipped()
{
    int up = 0;
    if (func_02012444(data_02114e30, 0x40))
        up = 1;
    if (up)
    {
        SetState(2);
        MoveFrame(state_, func_0205bb84(&cursor_));
        return;
    }
    int down = 0;
    if (func_02012444(data_02114e30, 0x80))
        down = 1;
    if (!up)
    {
        GameState::GetInstance();
        MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
        if (!CanEquip(screen->member_))
            return;
        if (IsConfirmed())
        {
            if (slots_[kind_].item_ < 0)
            {
                down = 1;
            }
            else
            {
                SetState(5);
                func_0205eaa0(data_02108760, 1, 0);
                screen->flags_ &= ~MEMBER_SCREEN_TURNING;
                screen->flags_ &= ~MEMBER_SCREEN_CHANGE_MEMBER;
            }
        }
    }
    if (down)
    {
        SetState(4);
        slot_ = 8;
        func_0205bb04(&cursor_, slot_ - 8);
        if (func_02012444(data_02114e30, 0x80))
            func_0205eaa0(data_02108760, 2, 0);
        else if (IsConfirmed())
            func_0205eaa0(data_02108760, 1, 0);
        MoveFrame(state_, slot_);
        return;
    }
    if (!SetKind(func_0205bb84(&cursor_), 0))
        return;
    slot_ = kind_;
    flags_ |= EQUIPMENT_KIND_CHANGED;
    LoadPage();
}

void EquipmentMenu::UpdatePage()
{
    signed char slot;
    int index = slot_ - 8;
    int cursor;
    if (index < 4 && func_02012444(data_02114e30, 0x40))
    {
        SetState(3);
        slot_ = kind_;
        MoveFrame(state_, func_0205bb84(&cursor_));
        return;
    }
    int column = index % 4;
    int changed = 0;
    if (column == 0)
    {
        if (func_02012444(data_02114e30, 0x20))
        {
            changed = TurnPage(-1);
            flags_ |= EQUIPMENT_PREVIOUS_PAGE;
        }
    }
    else if (column == 3 && func_02012444(data_02114e30, 0x10))
    {
        changed = TurnPage(1);
        flags_ |= EQUIPMENT_NEXT_PAGE;
    }
    if (changed != 0)
        LoadPage();
    else
    {
        flags_ &= ~EQUIPMENT_PREVIOUS_PAGE;
        flags_ &= ~EQUIPMENT_NEXT_PAGE;
    }
    cursor = func_0205bb84(&cursor_) + 8;
    slot = slot_;
    if (cursor != slot)
    {
        slot_ = cursor;
        func_0205eaa0(data_02108760, 2, 0);
        MoveFrame(state_, slot_);
        return;
    }
    if (cursor != slot)
        return;
    GameState::GetInstance();
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    if (!CanEquip(screen->member_))
        return;
    if (!IsConfirmed())
        return;
    if (slots_[slot_].item_ < 0)
        return;
    SetState(5);
    func_0205eaa0(data_02108760, 1, 0);
    screen->flags_ &= ~MEMBER_SCREEN_TURNING;
    screen->flags_ &= ~MEMBER_SCREEN_CHANGE_MEMBER;
}

void EquipmentMenu::SetState(unsigned char state)
{
    lastState_ = state_;
    state_ = state;
    step_ = 0;
    if (state_ == 0)
    {
        unk_3dbe = kind_;
        flags_ |= EQUIPMENT_STATE_0;
    }
    else
    {
        flags_ &= ~EQUIPMENT_STATE_0;
    }
    if (state_ == 0 && lastState_ == 1)
    {
        blinks_ = 3;
        blinkTimer_ = 30;
        blinkTimer2_ = 30;
        flags_ &= ~EQUIPMENT_FRAME_BLINK;
        flags_ &= ~EQUIPMENT_ARROWS_BLINK;
    }
    else if (lastState_ == 3)
    {
        blinks_ = 0;
        flags_ &= ~EQUIPMENT_FRAME_BLINK;
    }
    if (state_ != 5 && state_ != 1 && state_ != 7)
        SetCursor();
}

void EquipmentMenu::MoveFrame(unsigned int state, unsigned char slot)
{
    int x = 0;
    int y = 0;
    switch (state)
    {
    case 2:
        x = slot * 16 + 0x81;
        if (slot == 7)
            x--;
        frame_.SetTargetPosition(x << 12, 0x1000);
        frame_.SetTargetSize(0xf000, 0x11000);
        break;
    case 3:
        frame_.SetTargetPosition(0x85000, 0x17000);
        frame_.SetTargetSize(0x76000, 0x16000);
        break;
    case 4:
    case 6:
        GetSlotPosition(slot, &x, &y);
        frame_.SetTargetPosition(x << 12, y << 12);
        frame_.SetTargetSize(0x18000, 0x18000);
        break;
    }
}

int EquipmentMenu::CanEquip(int member)
{
    GameState* gameState = GameState::GetInstance();
    func_0202ae18();
    if (func_0202b7d8())
    {
        GameObject* object = gameState->GetGameObjectByIndex(member);
        if (object == NULL)
            return 0;
        unsigned short flags = object->obj3D_.unknown_0_;
        int leader = func_020100a8(gameState);
        if (flags & 0x200)
        {
            if (member != leader)
                return 0;
        }
        else if (flags & 0x1000)
        {
            func_0200ff58(gameState, member);
            if (leader != func_020546a8())
                return 0;
        }
    }
    return 1;
}

static signed char sEquipParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};
static unsigned char sEquipLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};
static unsigned char sEquipLists2[8] = {0, 1, 4, 2, 5, 3, 6, 7};

// NONMATCHING: the C matches 94.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::Equip(int item, int keep)
{
    int index;
    PartEntry* entry;
    char* party;
    GameState* gameState = GameState::GetInstance();
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    long member = screen->member_;
    PartyMember* partyMember = func_0200ff1c(gameState, member);
    if (partyMember == NULL)
        return;
    party = func_02010828(gameState);
    if (item == 0xffff)
    {
        signed char part = sEquipParts[kind_];
        short current = func_02052df8(partyMember, part);
        PartEntry* entry = func_020dedd0(items_, current);
        if (entry == NULL)
            return;
        if (entry->cursed_ == 1)
        {
            unk_3dd1 = 12;
            flags_ |= 0x8000;
            return;
        }
        short replacement = -1;
        int unk = -1;
        if (part == 0)
        {
            unk = 0;
            replacement = 1000;
        }
        func_02052d7c(partyMember, part, -1);
        PartyMemberData* data = func_02053c6c(partyMember);
        PartEntry* replacementEntry = func_020dedd0(items_, replacement);
        if (replacementEntry != NULL)
        {
            func_0208358c(data, replacementEntry, unk);
        }
        else
        {
            func_02083738(data, entry->category_);
            if (entry->category_ == 7)
                SetUnk56e(partyMember, 1);
        }
        if (part == 0)
            func_02052e2c(partyMember)->unk_16 = -1;
        if (current == 0x4680 && RemoveUnwearable(partyMember->index_))
        {
            if (unk_3dd1 == 10 && keep)
                unk_3dd2 = 14;
            else
                unk_3dd1 = 14;
        }
        func_02083e28(partyMember->data_, 0);
        func_ov017_021c9e00(partyMember->index_, 0, 0, 1);
        screen->flags_ |= MEMBER_SCREEN_LOAD_MODEL;
        if (!keep)
            func_0207c378(party + 0x1d4, current, 1, sEquipLists[kind_]);
        slots_[slot_].item_ = -1;
        SetMember(func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_, 1);
        LoadEquipped();
        flags_ |= EQUIPMENT_LOAD_ITEM;
        unk_3da8 = 0;
        unk_3dac = kind_;
        if (!keep)
        {
            LoadPage();
            for (int i = 8; i < 24; i++)
            {
                if (current == slots_[i].item_ && slots_[i].count_ == 1)
                {
                    flags_ |= EQUIPMENT_LOAD_PAGE;
                    pageStep_ = 0;
                    break;
                }
            }
        }
        func_0205eaa0(data_02108760, 0x5c, 0);
        flags_ |= EQUIPMENT_NAMES | 1;
        return;
    }
    entry = func_020dedd0(items_, item);
    if (entry == NULL)
        return;
    long part = -1;
    unsigned long letter = entry->letter_;
    switch (letter)
    {
    case 'a':
        part = 4;
        break;
    case 'b':
        part = 0;
        break;
    case 'c':
        part = 9;
        break;
    case 'g':
        part = 4;
        break;
    case 'm':
        part = 6;
        break;
    case 'r':
        part = 5;
        break;
    case 'w':
        part = 7;
        break;
    case 's':
        part = 8;
        break;
    case 'p':
        part = 1;
        break;
    }
    int error = func_020dd4c4((signed char)partyMember->index_, entry);
    if (error != 0)
    {
        if (error & 0x100)
        {
            unk_3dd1 = 5;
            return;
        }
        if (error & 0x80)
        {
            unk_3dd1 = 2;
            if (func_02052df8(partyMember, 9) == 0x4680)
                unk_3dd1 = 7;
            return;
        }
        if (error & 0x10)
        {
            unk_3dd1 = 6;
            return;
        }
        if (error & 2)
        {
            unk_3dd1 = 4;
            return;
        }
        if (error & 1)
        {
            unk_3dd1 = 3;
            return;
        }
        if (error & 4)
            unk_3dd1 = 1;
        return;
    }
    short current = func_02052df8(partyMember, part);
    if (current == (short)item)
        return;
    PartEntry* currentEntry = func_020dedd0(items_, current);
    if (currentEntry != NULL && currentEntry->cursed_ == 1)
    {
        unk_3dd1 = 12;
        flags_ |= 0x8000;
        return;
    }
    if (part >= 0)
    {
        if (current == 0x4680 && RemoveUnwearable(partyMember->index_))
            unk_3dd1 = 14;
        func_02052d7c(partyMember, part, (unsigned short)item);
        PartyMemberData* data = func_02053c6c(partyMember);
        func_0208358c(data, entry, -1);
        func_02083e28(data, 0);
        func_ov017_021c9e00(partyMember->index_, 0, 0, 1);
        if (entry->category_ == 7)
            SetUnk56e(partyMember, 1);
        SetMember(func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_, 1);
    }
    if (letter == 'b')
    {
        PartEntry* other = func_020deda4(items_, 'a', entry);
        if (other != NULL)
            func_02052e2c(partyMember)->unk_16 = other->unk_18;
    }
    if (entry->cursed_ == 1)
    {
        if (unk_3dd1 == 14)
            unk_3dd2 = 14;
        unk_3dd1 = 13;
        flags_ |= 0x8000;
        func_020483f0(partyMember, 4);
        func_ov017_021c9e00(member, 0, 0, 1);
    }
    unsigned int sound = entry->model_->sound_;
    if (sound == 1)
        func_0205eaa0(data_02108760, 3, 0);
    else if (sound == 2)
        func_0205eaa0(data_02108760, 4, 0);
    screen->flags_ |= MEMBER_SCREEN_LOAD_MODEL;
    unsigned char list = sEquipLists2[kind_];
    signed char hadItem = func_0207c7a0(party + 0x1d4, item, list);
    signed char hadCurrent = func_0207c7a0(party + 0x1d4, current, list);
    if (hadItem == 1 && hadCurrent == 0)
    {
        int index = func_0207caa4(party + 0x1d4, item, list);
        func_0207c484(party + 0x1d4, item, 1, list);
        if (index >= 0)
            func_0207cb38(party + 0x1d4, index, list, current, 1);
        else
            func_0207c378(party + 0x1d4, current, 1, list);
    }
    else
    {
        func_0207c484(party + 0x1d4, item, 1, list);
        func_0207c378(party + 0x1d4, current, 1, list);
    }
    _ZN12MemberScreen9DoNothingEv(screen, member, item, sEquipLists2[kind_]);
    LoadEquipped();
    flags_ |= EQUIPMENT_LOAD_ITEM;
    unk_3da8 = 0;
    unk_3dac = kind_;
    slot_ = kind_;
    frame_.SetTargetPosition(0x85000, 0x17000);
    frame_.SetTargetSize(0x76000, 0x16000);
    LoadPage();
    for (int i = 8; i < 24; i++)
    {
        if (current == slots_[i].item_ && slots_[i].count_ == 1)
        {
            flags_ |= EQUIPMENT_LOAD_PAGE;
            pageStep_ = 0;
            break;
        }
    }
    flags_ |= EQUIPMENT_NAMES | 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11CursorFrame13SetTargetSizeEii(); // CursorFrame::SetTargetSize
    void _ZN11CursorFrame17SetTargetPositionEii(); // CursorFrame::SetTargetPosition
    void _ZN13EquipmentMenu12LoadEquippedEv(); // EquipmentMenu::LoadEquipped
    void _ZN13EquipmentMenu16RemoveUnwearableEi(); // EquipmentMenu::RemoveUnwearable
    void _ZN13EquipmentMenu8LoadPageEv(); // EquipmentMenu::LoadPage
    void _ZN13EquipmentMenu9SetMemberEii(); // EquipmentMenu::SetMember
}

asm void EquipmentMenu::Equip(int item, int keep)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x10
    mov r9, r0
    mov r8, r1
    mov r6, r2
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    str r0, [sp, #0xc]
    ldr r0, [r0, #0x4fc]
    str r0, [sp, #0x4]
    ldr r1, [sp, #0x4]
    mov r0, r4
    bl func_0200ff1c
    movs r5, r0
    beq @L021583dc
    mov r0, r4
    bl func_02010828
    ldr r1, =0xffff
    mov r4, r0
    cmp r8, r1
    bne @L02157e78
    add r0, r9, #0x3000
    ldrb r2, [r0, #0xdbc]
    ldr r1, =sEquipParts
    mov r0, r5
    ldrsb r7, [r1, r2]
    mov r1, r7
    bl func_02052df8
    mov r8, r0
    ldr r0, [r9, #0xdf4]
    mov r1, r8
    bl func_020dedd0
    movs r10, r0
    beq @L021583dc
    ldr r0, [r10, #0x8]
    mov r0, r0, lsl #0xd
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    bne @L02157c3c
    add r0, r9, #0x3000
    mov r1, #0xc
    strb r1, [r0, #0xdd1]
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x8000
    str r1, [r0, #0xdcc]
    b @L021583dc
@L02157c3c:
    mvn r11, #0x0
    cmp r7, #0x0
    str r11, [sp, #0x8]
    moveq r0, #0x0
    streq r0, [sp, #0x8]
    mov r0, r5
    mov r1, r7
    mvn r2, #0x0
    moveq r11, #0x3e8
    bl func_02052d7c
    mov r0, r5
    bl func_02053c6c
    mov r1, r11
    mov r11, r0
    ldr r0, [r9, #0xdf4]
    bl func_020dedd0
    movs r1, r0
    beq @L02157c94
    ldr r2, [sp, #0x8]
    mov r0, r11
    bl func_0208358c
    b @L02157cc8
@L02157c94:
    ldr r1, [r10, #0x8]
    mov r0, r11
    mov r1, r1, lsl #0x1c
    mov r1, r1, lsr #0x1c
    bl func_02083738
    ldr r0, [r10, #0x8]
    mov r0, r0, lsl #0x1c
    mov r0, r0, lsr #0x1c
    cmp r0, #0x7
    bne @L02157cc8
    mov r0, r5
    mov r1, #0x1
    bl SetUnk56e
@L02157cc8:
    cmp r7, #0x0
    bne @L02157ce0
    mov r0, r5
    bl func_02052e2c
    mvn r1, #0x0
    strh r1, [r0, #0x16]
@L02157ce0:
    ldr r0, =0x4680
    cmp r8, r0
    bne @L02157d2c
    ldrsh r1, [r5, #0x4]
    mov r0, r9
    bl _ZN13EquipmentMenu16RemoveUnwearableEi
    cmp r0, #0x0
    beq @L02157d2c
    add r0, r9, #0x3000
    ldrb r1, [r0, #0xdd1]
    cmp r1, #0xa
    bne @L02157d20
    cmp r6, #0x0
    movne r1, #0xe
    strneb r1, [r0, #0xdd2]
    bne @L02157d2c
@L02157d20:
    add r0, r9, #0x3000
    mov r1, #0xe
    strb r1, [r0, #0xdd1]
@L02157d2c:
    ldr r0, [r5, #0x150]
    mov r1, #0x0
    bl func_02083e28
    mov r1, #0x0
    ldrsh r0, [r5, #0x4]
    mov r2, r1
    mov r3, #0x1
    bl func_ov017_021c9e00
    ldr r0, [sp, #0xc]
    cmp r6, #0x0
    add r0, r0, #0x600
    ldrh r1, [r0, #0x34]
    orr r1, r1, #0x4
    strh r1, [r0, #0x34]
    bne @L02157d88
    add r0, r9, #0x3000
    ldrb r2, [r0, #0xdbc]
    ldr r0, =sEquipLists
    mov r1, r8
    ldrb r3, [r0, r2]
    add r0, r4, #0x1d4
    mov r2, #0x1
    bl func_0207c378
@L02157d88:
    add r0, r9, #0x3d00
    ldrsb r1, [r0, #0xbb]
    mov r0, #0x1c
    mvn r2, #0x0
    mla r0, r1, r0, r9
    add r0, r0, #0x2d00
    strh r2, [r0, #0x90]
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r9
    mov r2, #0x1
    bl _ZN13EquipmentMenu9SetMemberEii
    mov r0, r9
    bl _ZN13EquipmentMenu12LoadEquippedEv
    add r0, r9, #0x3000
    ldr r2, [r0, #0xdcc]
    mov r1, #0x0
    orr r2, r2, #0x10
    str r2, [r0, #0xdcc]
    strb r1, [r0, #0xda8]
    ldrb r1, [r0, #0xdbc]
    add r0, r9, #0x3d00
    cmp r6, #0x0
    strh r1, [r0, #0xac]
    bne @L02157e50
    mov r0, r9
    bl _ZN13EquipmentMenu8LoadPageEv
    mov r3, #0x8
    mov r0, #0x1c
    b @L02157e48
@L02157e0c:
    mla r1, r3, r0, r9
    add r1, r1, #0x2d00
    ldrsh r2, [r1, #0x90]
    cmp r8, r2
    ldreqsb r1, [r1, #0x92]
    cmpeq r1, #0x1
    bne @L02157e44
    add r0, r9, #0x3000
    ldr r2, [r0, #0xdcc]
    mov r1, #0x0
    orr r2, r2, #0x40
    str r2, [r0, #0xdcc]
    strb r1, [r0, #0xdaa]
    b @L02157e50
@L02157e44:
    add r3, r3, #0x1
@L02157e48:
    cmp r3, #0x18
    blt @L02157e0c
@L02157e50:
    ldr r0, =data_02108760
    mov r1, #0x5c
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r9, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x200
    orr r1, r1, #0x1
    str r1, [r0, #0xdcc]
    b @L021583dc
@L02157e78:
    mov r1, r8, lsl #0x10
    ldr r0, [r9, #0xdf4]
    mov r1, r1, asr #0x10
    bl func_020dedd0
    movs r10, r0
    beq @L021583dc
    ldr r0, [r10, #0x10]
    mvn r7, #0x0
    mov r0, r0, lsl #0x4
    mov r6, r0, lsr #0x18
    cmp r6, #0x70
    bhi @L02157ee8
    bhs @L02157f28
    cmp r6, #0x67
    bhi @L02157edc
    subs r0, r6, #0x61
    addpl pc, pc, r0, lsl #0x2
    b @L02157f44
    b @L02157f30
    b @L02157f20
    b @L02157f40
    b @L02157f44
    b @L02157f44
    b @L02157f44
    b @L02157f38
@L02157edc:
    cmp r6, #0x6d
    moveq r7, #0x6
    b @L02157f44
@L02157ee8:
    cmp r6, #0x72
    bhi @L02157ef8
    moveq r7, #0x5
    b @L02157f44
@L02157ef8:
    cmp r6, #0x77
    bhi @L02157f44
    cmp r6, #0x73
    blo @L02157f44
    beq @L02157f18
    cmp r6, #0x77
    moveq r7, #0x7
    b @L02157f44
@L02157f18:
    mov r7, #0x8
    b @L02157f44
@L02157f20:
    mov r7, #0x0
    b @L02157f44
@L02157f28:
    mov r7, #0x1
    b @L02157f44
@L02157f30:
    mov r7, #0x4
    b @L02157f44
@L02157f38:
    mov r7, #0x4
    b @L02157f44
@L02157f40:
    mov r7, #0x9
@L02157f44:
    ldrsh r0, [r5, #0x4]
    mov r1, r10
    mov r0, r0, lsl #0x18
    mov r0, r0, asr #0x18
    bl func_020dd4c4
    cmp r0, #0x0
    beq @L02157ffc
    tst r0, #0x100
    addne r0, r9, #0x3000
    movne r1, #0x5
    strneb r1, [r0, #0xdd1]
    bne @L021583dc
    tst r0, #0x80
    beq @L02157fac
    mov r0, r5
    add r2, r9, #0x3000
    mov r3, #0x2
    mov r1, #0x9
    strb r3, [r2, #0xdd1]
    bl func_02052df8
    ldr r1, =0x4680
    cmp r0, r1
    addeq r0, r9, #0x3000
    moveq r1, #0x7
    streqb r1, [r0, #0xdd1]
    b @L021583dc
@L02157fac:
    tst r0, #0x10
    addne r0, r9, #0x3000
    movne r1, #0x6
    strneb r1, [r0, #0xdd1]
    bne @L021583dc
    tst r0, #0x2
    addne r0, r9, #0x3000
    movne r1, #0x4
    strneb r1, [r0, #0xdd1]
    bne @L021583dc
    tst r0, #0x1
    addne r0, r9, #0x3000
    movne r1, #0x3
    strneb r1, [r0, #0xdd1]
    bne @L021583dc
    tst r0, #0x4
    addne r0, r9, #0x3000
    movne r1, #0x1
    strneb r1, [r0, #0xdd1]
    b @L021583dc
@L02157ffc:
    mov r0, r5
    mov r1, r7
    bl func_02052df8
    mov r11, r0
    mov r0, r8, lsl #0x10
    cmp r11, r0, asr #0x10
    beq @L021583dc
    ldr r0, [r9, #0xdf4]
    mov r1, r11
    bl func_020dedd0
    cmp r0, #0x0
    beq @L0215805c
    ldr r0, [r0, #0x8]
    mov r0, r0, lsl #0xd
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    bne @L0215805c
    add r0, r9, #0x3000
    mov r1, #0xc
    strb r1, [r0, #0xdd1]
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x8000
    str r1, [r0, #0xdcc]
    b @L021583dc
@L0215805c:
    cmp r7, #0x0
    blt @L02158120
    ldr r0, =0x4680
    cmp r11, r0
    bne @L0215808c
    ldrsh r1, [r5, #0x4]
    mov r0, r9
    bl _ZN13EquipmentMenu16RemoveUnwearableEi
    cmp r0, #0x0
    addne r0, r9, #0x3000
    movne r1, #0xe
    strneb r1, [r0, #0xdd1]
@L0215808c:
    mov r0, r8, lsl #0x10
    mov r0, r0, lsr #0x10
    mov r2, r0, lsl #0x10
    mov r0, r5
    mov r1, r7
    mov r2, r2, asr #0x10
    bl func_02052d7c
    mov r0, r5
    bl func_02053c6c
    mov r7, r0
    mov r1, r10
    mvn r2, #0x0
    bl func_0208358c
    mov r0, r7
    mov r1, #0x0
    bl func_02083e28
    ldrsh r0, [r5, #0x4]
    mov r1, #0x0
    mov r2, r1
    mov r3, #0x1
    bl func_ov017_021c9e00
    ldr r0, [r10, #0x8]
    mov r0, r0, lsl #0x1c
    mov r0, r0, lsr #0x1c
    cmp r0, #0x7
    bne @L02158100
    mov r0, r5
    mov r1, #0x1
    bl SetUnk56e
@L02158100:
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r9
    mov r2, #0x1
    bl _ZN13EquipmentMenu9SetMemberEii
@L02158120:
    cmp r6, #0x62
    bne @L02158150
    ldr r0, [r9, #0xdf4]
    mov r2, r10
    mov r1, #0x61
    bl func_020deda4
    movs r6, r0
    beq @L02158150
    mov r0, r5
    bl func_02052e2c
    ldrsh r1, [r6, #0x18]
    strh r1, [r0, #0x16]
@L02158150:
    ldr r0, [r10, #0x8]
    mov r0, r0, lsl #0xd
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    bne @L021581b0
    add r0, r9, #0x3000
    ldrb r1, [r0, #0xdd1]
    add r2, r9, #0x3000
    cmp r1, #0xe
    moveq r1, #0xe
    streqb r1, [r0, #0xdd2]
    mov r0, #0xd
    strb r0, [r2, #0xdd1]
    ldr r1, [r2, #0xdcc]
    mov r0, r5
    orr r3, r1, #0x8000
    mov r1, #0x4
    str r3, [r2, #0xdcc]
    bl func_020483f0
    mov r1, #0x0
    ldr r0, [sp, #0x4]
    mov r2, r1
    mov r3, #0x1
    bl func_ov017_021c9e00
@L021581b0:
    ldr r0, [r10, #0x0]
    ldr r0, [r0, #0x0]
    mov r0, r0, lsl #0x3
    mov r0, r0, lsr #0x1e
    cmp r0, #0x1
    bne @L021581dc
    ldr r0, =data_02108760
    mov r1, #0x3
    mov r2, #0x0
    bl func_0205eaa0
    b @L021581f4
@L021581dc:
    cmp r0, #0x2
    bne @L021581f4
    ldr r0, =data_02108760
    mov r1, #0x4
    mov r2, #0x0
    bl func_0205eaa0
@L021581f4:
    ldr r0, [sp, #0xc]
    add r1, r9, #0x3000
    add r0, r0, #0x600
    ldrh r3, [r0, #0x34]
    mov r2, r8, lsl #0x10
    orr r3, r3, #0x4
    strh r3, [r0, #0x34]
    ldrb r3, [r1, #0xdbc]
    ldr r1, =sEquipLists2
    add r0, r4, #0x1d4
    ldrb r6, [r1, r3]
    mov r1, r2, asr #0x10
    mov r2, r6
    bl func_0207c7a0
    mov r3, r0, lsl #0x18
    mov r1, r11
    mov r2, r6
    add r0, r4, #0x1d4
    mov r5, r3, asr #0x18
    bl func_0207c7a0
    mov r0, r0, lsl #0x18
    mov r0, r0, asr #0x18
    cmp r5, #0x1
    cmpeq r0, #0x0
    mov r1, r8, lsl #0x10
    bne @L021582c8
    mov r2, r6
    add r0, r4, #0x1d4
    mov r1, r1, asr #0x10
    bl func_0207caa4
    mov r1, r8, lsl #0x10
    mov r5, r0
    mov r3, r6
    mov r1, r1, asr #0x10
    add r0, r4, #0x1d4
    mov r2, #0x1
    bl func_0207c484
    cmp r5, #0x0
    blt @L021582b0
    mov r7, #0x1
    mov r1, r5
    mov r2, r6
    mov r3, r11
    add r0, r4, #0x1d4
    str r7, [sp, #0x0]
    bl func_0207cb38
    b @L021582f0
@L021582b0:
    mov r1, r11
    mov r3, r6
    add r0, r4, #0x1d4
    mov r2, #0x1
    bl func_0207c378
    b @L021582f0
@L021582c8:
    mov r3, r6
    add r0, r4, #0x1d4
    mov r1, r1, asr #0x10
    mov r2, #0x1
    bl func_0207c484
    mov r1, r11
    mov r3, r6
    add r0, r4, #0x1d4
    mov r2, #0x1
    bl func_0207c378
@L021582f0:
    add r0, r9, #0x3000
    ldrb r1, [r0, #0xdbc]
    ldr r0, =sEquipLists2
    mov r2, r8, lsl #0x10
    ldrb r3, [r0, r1]
    ldr r0, [sp, #0xc]
    ldr r1, [sp, #0x4]
    mov r2, r2, asr #0x10
    bl _ZN12MemberScreen9DoNothingEv
    mov r0, r9
    bl _ZN13EquipmentMenu12LoadEquippedEv
    add r3, r9, #0x3000
    ldr r1, [r3, #0xdcc]
    mov r0, #0x0
    orr r1, r1, #0x10
    str r1, [r3, #0xdcc]
    strb r0, [r3, #0xda8]
    add r0, r9, #0x234
    ldrb r2, [r3, #0xdbc]
    add r1, r9, #0x3d00
    add r0, r0, #0x1800
    strh r2, [r1, #0xac]
    ldrb r4, [r3, #0xdbc]
    mov r1, #0x85000
    mov r2, #0x17000
    strb r4, [r3, #0xdbb]
    bl _ZN11CursorFrame17SetTargetPositionEii
    add r0, r9, #0x234
    add r0, r0, #0x1800
    mov r1, #0x76000
    mov r2, #0x16000
    bl _ZN11CursorFrame13SetTargetSizeEii
    mov r0, r9
    bl _ZN13EquipmentMenu8LoadPageEv
    mov r3, #0x8
    mov r0, #0x1c
    b @L021583c0
@L02158384:
    mla r1, r3, r0, r9
    add r1, r1, #0x2d00
    ldrsh r2, [r1, #0x90]
    cmp r11, r2
    ldreqsb r1, [r1, #0x92]
    cmpeq r1, #0x1
    bne @L021583bc
    add r0, r9, #0x3000
    ldr r2, [r0, #0xdcc]
    mov r1, #0x0
    orr r2, r2, #0x40
    str r2, [r0, #0xdcc]
    strb r1, [r0, #0xdaa]
    b @L021583c8
@L021583bc:
    add r3, r3, #0x1
@L021583c0:
    cmp r3, #0x18
    blt @L02158384
@L021583c8:
    add r0, r9, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x200
    orr r1, r1, #0x1
    str r1, [r0, #0xdcc]
@L021583dc:
    add sp, sp, #0x10
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

static void SetUnk56e(PartyMember* member, signed char value)
{
    PartyMemberData* data = member->data_;
    if (data != NULL)
        data->unk_56e = value;
}

int EquipmentMenu::RemoveUnwearable(int member)
{
    static const unsigned char sRemoveParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};
    GameState* gameState = GameState::GetInstance();
    PartyMember* partyMember = func_0200ff1c(gameState, member);
    if (partyMember == NULL)
        return 0;
    int removed = 0;
    unsigned int female = partyMember->data_->appearance_.female_;
    for (int i = 0; i < 7; i++)
    {
        unsigned char part = sRemoveParts[i];
        short current = func_02052df8(partyMember, part);
        PartEntry* entry = func_020dedd0(items_, current);
        if (entry == NULL)
            continue;
        unsigned int wearable[2];
        wearable[0] = entry->model_->unk_4_27;
        wearable[1] = entry->model_->unk_4_28;
        if (wearable[female] != 0)
            continue;
        short replacement = -1;
        int unk = -1;
        if (part == 0)
        {
            unk = 0;
            replacement = 1000;
        }
        func_02052d7c(partyMember, part, -1);
        PartyMemberData* data = func_02053c6c(partyMember);
        PartEntry* replacementEntry = func_020dedd0(items_, replacement);
        if (replacementEntry != NULL)
            func_0208358c(data, replacementEntry, unk);
        else
            func_02083738(data, entry->category_);
        func_0207c378(func_02010828(gameState) + 0x1d4, current, 1, entry->category_);
        removed = 1;
    }
    return removed;
}

// The lists of the kinds, for GetList(): defined here to get the original's layout (see tools/data_order.py)
static unsigned char sLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};

// NONMATCHING: the C matches 87.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
int EquipmentMenu::SetKind(unsigned char kind, int silent)
{
    if (kind == kind_)
        return 0;
    if (!silent)
        func_0205eaa0(data_02108760, 1, 0);
    unk_3dbe = kind_;
    lastPage_ = page_;
    pages_[kind_] = page_;
    kind_ = kind;
    page_ = pages_[kind];
    flags_ |= EQUIPMENT_LOAD_PAGE | EQUIPMENT_SORT_ICON;
    pageStep_ = 0;
    return 1;
}
#else
asm int EquipmentMenu::SetKind(unsigned char kind, int silent)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r5, r0
    add r0, r5, #0x3000
    ldrb r0, [r0, #0xdbc]
    mov r4, r1
    cmp r4, r0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, pc}
    cmp r2, #0x0
    bne @L02158598
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
@L02158598:
    add r3, r5, #0x3000
    ldrb r2, [r3, #0xdbc]
    and r0, r4, #0xff
    add r1, r5, r0
    strb r2, [r3, #0xdbe]
    add r0, r5, #0x3d00
    ldrsb lr, [r0, #0xbd]
    add r2, r1, #0x3000
    mov r12, #0x0
    strb lr, [r3, #0xdbf]
    ldrb r1, [r3, #0xdbc]
    ldrsb lr, [r0, #0xbd]
    mov r0, #0x1
    add r1, r5, r1
    add r1, r1, #0x3000
    strb lr, [r1, #0xdfc]
    strb r4, [r3, #0xdbc]
    ldrb r1, [r2, #0xdfc]
    strb r1, [r3, #0xdbd]
    ldr r1, [r3, #0xdcc]
    orr r1, r1, #0x840
    str r1, [r3, #0xdcc]
    strb r12, [r3, #0xdaa]
    ldmia sp!, {r3, r4, r5, pc}
}
#endif

int EquipmentMenu::TurnPage(int direction)
{
    unsigned char last = pageCounts_[kind_] - 1;
    signed char page = page_;
    signed char next = page + direction;
    if (next < 0)
        next = last;
    if (next > last)
        next = 0;
    int changed = 1;
    if (next == page)
        changed = 0;
    if (changed)
    {
        func_0205eaa0(data_02108760, 1, 0);
        if (direction < 0)
            flags_ |= EQUIPMENT_PREVIOUS_PAGE;
        else
            flags_ |= EQUIPMENT_NEXT_PAGE;
        unk_3dbe = kind_;
        lastPage_ = page_;
        page_ = next;
        flags_ |= EQUIPMENT_LOAD_PAGE;
        pageStep_ = 0;
    }
    return changed;
}


static const Vector3fix sPartOffsets[8] = {
    {0, 0xd000, 0},          {0, 0x18000, 0},         {0, 0, 0},       {-0x8000, 0x7000, 0x6000},
    {0x6000, 0x7000, 0x4000}, {0, 0x7000, 0},          {-0x5000, 0xa000, 0x4000}, {0x5000, 0xa000, 0x4000},
};
static const unsigned char sPartKinds[8] = {3, 2, 6, 0, 1, 5, 4, 4};

// NONMATCHING: the C matches 86.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
unsigned char EquipmentMenu::GetTouchedPart(int x, int y)
{
    GameState* gameState;
    int dy;
    unsigned long part;
    gameState = GameState::GetInstance();
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    int member = screen->member_;
    if (x > 0 && x < 0x80)
    {
        int screenX[8];
        unsigned long best;
        int screenY[8];
        void* camera = func_020100bc(gameState);
        Vector3fix positions[8];
        Matrix4x3 matrix = RotationMatrixY(screen->GetBody()->rotation_.y);
        float radii[8];
        for (int i = 0; i < 8; i++)
        {
            Mat4x3_ApplyToVector(&sPartOffsets[i], &matrix, &positions[i]);
            func_0202ec84(camera, &positions[i], &screenX[i], &screenY[i]);
        }
        func_0200ff1c(gameState, member);
        int count;
        unsigned int touched[8];
        count = 0;
        for (int i = 0; i < 8; i++)
        {
            radii[i] = 20.0f;
            dy = y - screenY[i];
            long dx = x - screenX[i];
            if ((float)func_0200b454(dx * dx + dy * dy) < radii[i])
                touched[count++] = i;
        }
        if (count > 0)
        {
            int best = touched[0];
            int bestZ = sPartOffsets[best].z;
            for (int i = 1; i < count; i++)
            {
                int part = touched[i];
                if (bestZ < sPartOffsets[part].z)
                {
                    best = part;
                    bestZ = sPartOffsets[part].z;
                }
            }
            return sPartKinds[best];
        }
    }
    return 0xff;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12MemberScreen7GetBodyEv(); // MemberScreen::GetBody
}

asm unsigned char EquipmentMenu::GetTouchedPart(int x, int y)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x140
    mov r10, r1
    mov r9, r2
    bl _ZN9GameState11GetInstanceEv
    mov r5, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    mov r4, r0
    cmp r10, #0x0
    ldr r8, [r4, #0x4fc]
    ble @L0215885c
    cmp r10, #0x80
    bge @L0215885c
    mov r0, r5
    bl func_020100bc
    mov r6, r0
    mov r0, r4
    bl _ZN12MemberScreen7GetBodyEv
    ldr r1, [r0, #0x54]
    add r0, sp, #0x0
    bl RotationMatrixY
    add r11, sp, #0x0
    add r7, sp, #0x70
    mov r4, #0x3
@L02158730:
    ldmia r11!, {r0, r1, r2, r3}
    stmia r7!, {r0, r1, r2, r3}
    subs r4, r4, #0x1
    bne @L02158730
    mov r7, #0x0
    add r11, sp, #0xe0
    b @L02158788
@L0215874c:
    mov r0, #0xc
    mul r4, r7, r0
    ldr r0, =sPartOffsets
    add r1, sp, #0x70
    add r0, r0, r4
    add r2, r11, r4
    bl Mat4x3_ApplyToVector
    add r2, sp, #0xc0
    add r3, sp, #0xa0
    add r1, r11, r4
    mov r0, r6
    add r2, r2, r7, lsl #0x2
    add r3, r3, r7, lsl #0x2
    bl func_0202ec84
    add r7, r7, #0x1
@L02158788:
    cmp r7, #0x8
    blt @L0215874c
    mov r0, r5
    mov r1, r8
    bl func_0200ff1c
    mov r8, #0x0
    mov r7, r8
    ldr r6, =0x41a00000
    add r5, sp, #0x50
    add r4, sp, #0xa0
    add r11, sp, #0xc0
    b @L021587f8
@L021587b8:
    ldr r0, [r4, r7, lsl #0x2]
    ldr r1, [r11, r7, lsl #0x2]
    sub r2, r9, r0
    mul r0, r2, r2
    sub r1, r10, r1
    mla r0, r1, r1, r0
    str r6, [r5, r7, lsl #0x2]
    bl _dflt
    bl func_0200b454
    bl _d2f
    ldr r1, [r5, r7, lsl #0x2]
    bl _fls
    addlo r0, sp, #0x30
    strlo r7, [r0, r8, lsl #0x2]
    addlo r8, r8, #0x1
    add r7, r7, #0x1
@L021587f8:
    cmp r7, #0x8
    blt @L021587b8
    cmp r8, #0x0
    ble @L0215885c
    ldr r5, [sp, #0x30]
    mov r0, #0xc
    mul r0, r5, r0
    ldr r4, =sPartOffsets+0x8
    mov r7, #0x1
    ldr r6, [r4, r0]
    add r3, sp, #0x30
    mov r0, #0xc
    b @L02158848
@L0215882c:
    ldr r2, [r3, r7, lsl #0x2]
    add r7, r7, #0x1
    mul r1, r2, r0
    ldr r1, [r4, r1]
    cmp r6, r1
    movlt r5, r2
    movlt r6, r1
@L02158848:
    cmp r7, r8
    blt @L0215882c
    ldr r0, =sPartKinds
    ldrb r0, [r0, r5]
    b @L02158860
@L0215885c:
    mov r0, #0xff
@L02158860:
    add sp, sp, #0x140
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 98.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::UpdateDialog(int ticks)
{
    func_0205d0e0(&window_, ticks);
    if (unk_3dd0 == 0)
    {
        OpenDialog();
        unk_3dd0++;
    }
    else if (unk_3dd0 == 1)
    {
        if (func_0204c7cc(func_0205d81c(&window_, 0)))
        {
            if (unk_3dd1 == 12 || unk_3dd1 == 13)
                flags_ |= EQUIPMENT_FADE;
        }
        unk_3dd0++;
    }
    else if (unk_3dd0 == 2)
    {
        unsigned int close = 0;
        unsigned char touching = data_02114e54.touching_;
        if (IsConfirmed() | touching)
        {
            func_0205eaa0(data_02108760, 1, 0);
            if (unk_3dd2 != 0)
            {
                unk_3dd1 = unk_3dd2;
                unk_3dd2 = 0;
                memset(text_, 0, 0x960);
                WriteMessage(text_);
                func_0205d5d0(&window_, 0, text_, 1, 0);
                return;
            }
            close = 1;
        }
        else if (func_02012444(data_02114e30, 2))
        {
            close = 1;
        }
        if (close)
        {
            func_0205d6a0(&window_, 0);
            unk_3dd0 = 0;
            unk_3dd1 = 0;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13EquipmentMenu10OpenDialogEv(); // EquipmentMenu::OpenDialog
    void _ZN13EquipmentMenu11IsConfirmedEv(); // EquipmentMenu::IsConfirmed
    void _ZN13EquipmentMenu12WriteMessageEPt(); // EquipmentMenu::WriteMessage
}

asm void EquipmentMenu::UpdateDialog(int ticks)
{
    stmdb sp!, {r3, r4, r5, r6, lr}
    sub sp, sp, #0x4
    mov r4, r0
    add r0, r4, #0x2e4
    add r0, r0, #0xc00
    bl func_0205d0e0
    add r0, r4, #0x3000
    ldrb r0, [r0, #0xdd0]
    cmp r0, #0x0
    bne @L021588bc
    mov r0, r4
    bl _ZN13EquipmentMenu10OpenDialogEv
    add r0, r4, #0x3000
    ldrb r1, [r0, #0xdd0]
    add r1, r1, #0x1
    strb r1, [r0, #0xdd0]
    b @L021589e0
@L021588bc:
    cmp r0, #0x1
    bne @L02158914
    add r0, r4, #0x2e4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0205d81c
    bl func_0204c7cc
    cmp r0, #0x0
    beq @L02158900
    add r0, r4, #0x3000
    ldrb r0, [r0, #0xdd1]
    cmp r0, #0xc
    cmpne r0, #0xd
    addeq r0, r4, #0x3000
    ldreq r1, [r0, #0xdcc]
    orreq r1, r1, #0x10000
    streq r1, [r0, #0xdcc]
@L02158900:
    add r0, r4, #0x3000
    ldrb r1, [r0, #0xdd0]
    add r1, r1, #0x1
    strb r1, [r0, #0xdd0]
    b @L021589e0
@L02158914:
    cmp r0, #0x2
    bne @L021589e0
    ldr r1, =data_02114e54
    mov r0, r4
    ldrb r6, [r1, #0x55]
    mov r5, #0x0
    bl _ZN13EquipmentMenu11IsConfirmedEv
    orrs r0, r0, r6
    beq @L021589a4
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, r5
    bl func_0205eaa0
    add r0, r4, #0x3000
    ldrb r1, [r0, #0xdd2]
    cmp r1, #0x0
    beq @L0215899c
    strb r1, [r0, #0xdd1]
    mov r1, r5
    strb r1, [r0, #0xdd2]
    ldr r0, [r4, #0xe10]
    mov r2, #0x960
    bl memset
    ldr r1, [r4, #0xe10]
    mov r0, r4
    bl _ZN13EquipmentMenu12WriteMessageEPt
    mov r1, r5
    str r1, [sp, #0x0]
    add r0, r4, #0x2e4
    ldr r2, [r4, #0xe10]
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
    b @L021589e0
@L0215899c:
    mov r5, #0x1
    b @L021589b8
@L021589a4:
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    movne r5, #0x1
@L021589b8:
    cmp r5, #0x0
    beq @L021589e0
    add r0, r4, #0x2e4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0205d6a0
    add r0, r4, #0x3000
    mov r1, #0x0
    strb r1, [r0, #0xdd0]
    strb r1, [r0, #0xdd1]
@L021589e0:
    add sp, sp, #0x4
    ldmia sp!, {r3, r4, r5, r6, pc}
}
#endif

void EquipmentMenu::OpenDialog()
{
    unsigned int unk;
    unk = 1;
    TextWindow* window = &window_;
    if (unk_3dd1 >= 8 && unk_3dd1 <= 14)
    {
        window->width_ = 0x20;
        window->height_ = 9;
        unk = 0;
        window->unk_a4 = 0;
        window->unk_a6 = 0xf;
        window->unk_ac = 0xc;
        window->unk_ae = 0x14;
        window->unk_b7 = 0xc;
        window->unk_a8 = 0xc;
        window->unk_aa = 0xb;
    }
    else
    {
        window->width_ = 0x18;
        window->height_ = 5;
        window->unk_a4 = 4;
        window->unk_a6 = 0xa;
        window->unk_ac = 0xa;
        window->unk_ae = 0xe;
        window->unk_b7 = 0xa;
        window->unk_a8 = 6;
        window->unk_aa = 9;
    }
    window->unk_b1 = 0;
    window->unk_b5 = 0;
    window->unk_b6 = 0;
    memset(text_, 0, 0x960);
    int choice = WriteMessage(text_);
    int choices = 0;
    unsigned char colors[4];
    __clear(colors, sizeof(colors));
    if (choice)
    {
        choices = 1;
        for (int i = 1; i < 4; i++)
            colors[i] = 2;
    }
    func_0205d304(window, text_, 0, unk, 0, choices, colors, 0);
}

// NONMATCHING: the C matches 84.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
int EquipmentMenu::WriteMessage(unsigned short* text)
{
    if (text == NULL)
        return 0;
    MessageSystem* messages = func_020421a0();
    char itemName2[0x80];
    func_02046380(messages);
    GameState* gameState = GameState::GetInstance();
    long member = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_;
    PartyMember* partyMember = func_0200ff1c(gameState, member);
    MessageName name2;
    if (partyMember == NULL)
        return 0;
    func_020e4bf4(&name2, member);
    MessageName name;
    char itemName[0x80];
    messages->unk_10 = &name2;
    __clear(itemName2, sizeof(itemName2));
    __clear(itemName, sizeof(itemName));
    func_020e46c4(&name);
    name.unk_4 = itemName2;
    name.text_ = itemName;
    if (flags_ & 0x8000)
    {
        PartEntry* entry = &partyMember->data_->equipment_[GetCategory(kind_)];
        if (entry != NULL)
        {
            func_02046380(messages);
            func_020dcf7c(entry->unk_18, &name);
            messages->unk_18 = &name;
        }
        flags_ &= ~0x8000;
    }
    else
    {
        func_020dcf7c(slots_[slot_].item_, &name);
        messages->unk_18 = &name;
    }
    long id = -1;
    char buffer[0x800];
    int width = 0xe3;
    if (unk_3dd1 <= 7)
        PartEntry* entry;
        width = 0xb4;
    switch (unk_3dd1)
    {
    case 2:
        id = 10001;
        break;
    case 3:
        id = 10002;
        break;
    case 1:
        id = 10003;
        break;
    case 4:
        id = 10004;
        break;
    case 5:
        id = 10005;
        break;
    case 6:
        id = 10006;
        break;
    case 7:
        id = 10007;
        break;
    case 8:
        id = 11000;
        break;
    case 9:
        id = 11001;
        break;
    case 10:
        id = 11002;
        break;
    case 11:
        id = 11003;
        break;
    case 12:
        id = 11004;
        break;
    case 13:
        id = 11005;
        break;
    case 14:
        id = 11006;
        break;
    }
    if (id >= 0)
        sprintf((char*)text, func_020e0434(&texts_, id));
    __clear(buffer, sizeof(buffer));
    func_02046608(messages, 10, (const char*)text, buffer, width, 0, 0);
    sprintf((char*)text, buffer);
    if (id >= 11000 && id <= 11006)
        return 1;
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13EquipmentMenu11GetCategoryEi(); // EquipmentMenu::GetCategory
}

asm int EquipmentMenu::WriteMessage(unsigned short* text)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, lr}
    sub sp, sp, #0x124
    sub sp, sp, #0x800
    movs r6, r1
    mov r7, r0
    moveq r0, #0x0
    beq @L02158dc0
    bl func_020421a0
    mov r5, r0
    bl func_02046380
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r8, [r0, #0x4fc]
    mov r0, r4
    mov r1, r8
    bl func_0200ff1c
    movs r4, r0
    moveq r0, #0x0
    beq @L02158dc0
    add r0, sp, #0x18
    mov r1, r8
    bl func_020e4bf4
    add r0, sp, #0x800
    add r2, sp, #0x18
    add r0, r0, #0xa4
    mov r1, #0x80
    str r2, [r5, #0x10]
    bl __clear
    add r0, sp, #0x800
    add r0, r0, #0x24
    mov r1, #0x80
    bl __clear
    add r0, sp, #0xc
    bl func_020e46c4
    add r0, sp, #0x800
    add r1, sp, #0x800
    add r0, r0, #0x24
    add r1, r1, #0xa4
    str r0, [sp, #0x10]
    add r0, r7, #0x3000
    str r1, [sp, #0xc]
    ldr r1, [r0, #0xdcc]
    tst r1, #0x8000
    beq @L02158c4c
    ldrb r1, [r0, #0xdbc]
    mov r0, r7
    bl _ZN13EquipmentMenu11GetCategoryEi
    ldr r1, [r4, #0x150]
    and r2, r0, #0xff
    add r0, r1, #0x194
    adds r4, r0, r2, lsl #0x5
    beq @L02158c38
    mov r0, r5
    bl func_02046380
    ldrsh r0, [r4, #0x18]
    add r1, sp, #0xc
    bl func_020dcf7c
    add r0, sp, #0xc
    str r0, [r5, #0x18]
@L02158c38:
    add r0, r7, #0x3000
    ldr r1, [r0, #0xdcc]
    bic r1, r1, #0x8000
    str r1, [r0, #0xdcc]
    b @L02158c74
@L02158c4c:
    add r0, r7, #0x3d00
    ldrsb r2, [r0, #0xbb]
    mov r0, #0x1c
    add r1, sp, #0xc
    mla r0, r2, r0, r7
    add r0, r0, #0x2d00
    ldrsh r0, [r0, #0x90]
    bl func_020dcf7c
    add r0, sp, #0xc
    str r0, [r5, #0x18]
@L02158c74:
    add r0, r7, #0x3000
    ldrb r0, [r0, #0xdd1]
    mov r8, #0xe3
    sub r4, r8, #0xe4
    cmp r0, #0x7
    movls r8, #0xb4
    cmp r0, #0xe
    addls pc, pc, r0, lsl #0x2
    b @L02158d40
@L02158c98:
    b @L02158d40
    b @L02158ce4
    b @L02158cd4
    b @L02158cdc
    b @L02158cec
    b @L02158cf4
    b @L02158cfc
    b @L02158d04
    b @L02158d0c
    b @L02158d14
    b @L02158d1c
    b @L02158d24
    b @L02158d2c
    b @L02158d34
    b @L02158d3c
@L02158cd4:
    ldr r4, =0x2711
    b @L02158d40
@L02158cdc:
    ldr r4, =0x2712
    b @L02158d40
@L02158ce4:
    ldr r4, =0x2713
    b @L02158d40
@L02158cec:
    ldr r4, =0x2714
    b @L02158d40
@L02158cf4:
    ldr r4, =0x2715
    b @L02158d40
@L02158cfc:
    ldr r4, =0x2716
    b @L02158d40
@L02158d04:
    ldr r4, =0x2717
    b @L02158d40
@L02158d0c:
    ldr r4, =0x2af8
    b @L02158d40
@L02158d14:
    ldr r4, =0x2af9
    b @L02158d40
@L02158d1c:
    ldr r4, =0x2afa
    b @L02158d40
@L02158d24:
    ldr r4, =0x2afb
    b @L02158d40
@L02158d2c:
    ldr r4, =0x2afc
    b @L02158d40
@L02158d34:
    ldr r4, =0x2afd
    b @L02158d40
@L02158d3c:
    ldr r4, =0x2afe
@L02158d40:
    cmp r4, #0x0
    blt @L02158d64
    add r0, r7, #0x1f8
    mov r1, r4
    add r0, r0, #0xc00
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    bl sprintf
@L02158d64:
    add r0, sp, #0x24
    mov r1, #0x800
    bl __clear
    str r8, [sp, #0x0]
    mov r7, #0x0
    str r7, [sp, #0x4]
    add r3, sp, #0x24
    mov r0, r5
    mov r2, r6
    mov r1, #0xa
    str r7, [sp, #0x8]
    bl func_02046608
    add r1, sp, #0x24
    mov r0, r6
    bl sprintf
    ldr r0, =0x2af8
    cmp r4, r0
    blt @L02158dbc
    add r0, r0, #0x6
    cmp r4, r0
    movle r0, #0x1
    ble @L02158dc0
@L02158dbc:
    mov r0, #0x0
@L02158dc0:
    add sp, sp, #0x124
    add sp, sp, #0x800
    ldmia sp!, {r3, r4, r5, r6, r7, r8, pc}
}
#endif

// NONMATCHING: the C matches 68.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::UpdateMenu(int ticks)
{
    Canvas* canvas = func_0205d8c4(&window_);
    if (canvas != NULL && func_0204c7cc(canvas) && !(canvas->flags_ & 2))
        func_0205bc24(&window_.base_.frame_, -1);
    menuResult_ = func_0205d0e0(&window_, ticks);
    switch (menuState_)
    {
    case 0:
        Menu_Open();
        break;
    case 1:
        Menu_Equip();
        break;
    case 2:
        Menu_Close();
        break;
    case 3:
        Menu_Discard();
        break;
    case 4:
        Menu_Cancel();
        break;
    }
    UpdateMenuText();
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13EquipmentMenu10Menu_CloseEv(); // EquipmentMenu::Menu_Close
    void _ZN13EquipmentMenu10Menu_EquipEv(); // EquipmentMenu::Menu_Equip
    void _ZN13EquipmentMenu11Menu_CancelEv(); // EquipmentMenu::Menu_Cancel
    void _ZN13EquipmentMenu12Menu_DiscardEv(); // EquipmentMenu::Menu_Discard
    void _ZN13EquipmentMenu14UpdateMenuTextEv(); // EquipmentMenu::UpdateMenuText
    void _ZN13EquipmentMenu9Menu_OpenEv(); // EquipmentMenu::Menu_Open
}

asm void EquipmentMenu::UpdateMenu(int ticks)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r5, r0
    add r0, r5, #0x2e4
    add r0, r0, #0xc00
    mov r4, r1
    bl func_0205d8c4
    movs r6, r0
    beq @L02158e50
    bl func_0204c7cc
    cmp r0, #0x0
    beq @L02158e50
    ldrb r0, [r6, #0xc5]
    tst r0, #0x2
    bne @L02158e50
    add r0, r5, #0x2e4
    add r0, r0, #0xc00
    add r0, r0, #0x4
    mvn r1, #0x0
    bl func_0205bc24
@L02158e50:
    add r0, r5, #0x2e4
    mov r1, r4
    add r0, r0, #0xc00
    bl func_0205d0e0
    add r1, r5, #0x3000
    strb r0, [r1, #0xddd]
    ldrb r0, [r1, #0xddf]
    cmp r0, #0x4
    addls pc, pc, r0, lsl #0x2
    b @L02158ec4
@L02158e78:
    b @L02158e8c
    b @L02158e98
    b @L02158ea4
    b @L02158eb0
    b @L02158ebc
@L02158e8c:
    mov r0, r5
    bl _ZN13EquipmentMenu9Menu_OpenEv
    b @L02158ec4
@L02158e98:
    mov r0, r5
    bl _ZN13EquipmentMenu10Menu_EquipEv
    b @L02158ec4
@L02158ea4:
    mov r0, r5
    bl _ZN13EquipmentMenu10Menu_CloseEv
    b @L02158ec4
@L02158eb0:
    mov r0, r5
    bl _ZN13EquipmentMenu12Menu_DiscardEv
    b @L02158ec4
@L02158ebc:
    mov r0, r5
    bl _ZN13EquipmentMenu11Menu_CancelEv
@L02158ec4:
    mov r0, r5
    bl _ZN13EquipmentMenu14UpdateMenuTextEv
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

// NONMATCHING: the C matches 90.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::UpdateMenuText()
{
    if (menuResult_ == 0)
        return;
    int touched = 0;
    if (menuResult_ == 2)
    {
        if (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0)
        {
            if (window_.base_.frame_.unk_30 < 0)
                return;
            touched = 1;
        }
    }
    memset(text_, 0, 0x960);
    unsigned char unk = window_.unk_b0;
    if (unk == 1)
        WriteMenu(text_, touched);
    func_0205d5d0(&window_, unk, text_, 1, 0);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13EquipmentMenu9WriteMenuEPti(); // EquipmentMenu::WriteMenu
}

asm void EquipmentMenu::UpdateMenuText()
{
    stmdb sp!, {r3, r4, r5, r6, lr}
    sub sp, sp, #0x4
    mov r4, r0
    add r0, r4, #0x3000
    ldrb r0, [r0, #0xddd]
    cmp r0, #0x0
    beq @L02158f74
    cmp r0, #0x2
    mov r5, #0x0
    bne @L02158f28
    ldr r0, =data_02114e54
    ldrb r1, [r0, #0x5f]
    cmp r1, #0x0
    ldrneh r0, [r0, #0x24]
    cmpne r0, #0x0
    beq @L02158f28
    add r0, r4, #0x2e4
    add r0, r0, #0xc00
    ldr r0, [r0, #0x34]
    cmp r0, #0x0
    blt @L02158f74
    mov r5, #0x1
@L02158f28:
    ldr r0, [r4, #0xe10]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldrb r6, [r4, #0xf94]
    cmp r6, #0x1
    bne @L02158f54
    ldr r1, [r4, #0xe10]
    mov r0, r4
    mov r2, r5
    bl _ZN13EquipmentMenu9WriteMenuEPti
@L02158f54:
    mov r0, #0x0
    str r0, [sp, #0x0]
    add r0, r4, #0x2e4
    ldr r2, [r4, #0xe10]
    mov r1, r6
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
@L02158f74:
    add sp, sp, #0x4
    ldmia sp!, {r3, r4, r5, r6, pc}
}
#endif

void EquipmentMenu::Menu_Open()
{
    if (menuStep_ == 0)
    {
        OpenMenu();
        func_0205cef8(&window_);
        func_0205cf04(&window_);
        menuStep_++;
    }
    else if (menuStep_ == 1)
    {
        menuChoice_ = func_0205d794(&window_);
        if (IsConfirmed() | func_0205da38(&window_, 0x14))
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_0205cf10(&window_);
            func_0205cf1c(&window_);
            func_0205d6a0(&window_, 0);
            if (slot_ >= 0 && slot_ < 8)
            {
                switch (menuChoice_)
                {
                case 0:
                    menuState_ = 1;
                    break;
                case 1:
                    menuState_ = 3;
                    break;
                case 2:
                    menuState_ = 4;
                    break;
                }
            }
            else
            {
                switch (menuChoice_)
                {
                case 0:
                    menuState_ = 1;
                    break;
                case 1:
                    menuState_ = 2;
                    break;
                case 2:
                    menuState_ = 3;
                    break;
                case 3:
                    menuState_ = 4;
                    break;
                }
            }
            menuStep_ = 0;
            return;
        }
        if (!func_02012444(data_02114e30, 2))
            return;
        func_0205cf10(&window_);
        func_0205cf1c(&window_);
        func_0205d6a0(&window_, 0);
        menuState_ = 4;
        menuStep_ = 0;
    }
}

void EquipmentMenu::Menu_Equip()
{
    if (menuStep_ == 0)
    {
        if (slot_ >= 0 && slot_ < 8)
            Equip(0xffff, 0);
        else if (slot_ >= 8 && slot_ < 24)
            Equip(slots_[slot_].item_, 0);
        menuStep_++;
    }
    else if (menuStep_ == 1)
    {
        menuState_ = 4;
        menuStep_ = 0;
    }
}

void EquipmentMenu::Menu_Close()
{
    if (menuStep_ != 0)
        return;
    func_0205d6a0(&window_, 1);
    SetState(6);
    menuStep_ = 0;
    menuChoice_ = 0;
    menuState_ = 0;
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    screen->flags_ |= MEMBER_SCREEN_TURNING | MEMBER_SCREEN_CHANGE_MEMBER;
}

// NONMATCHING: the C matches 97.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::Menu_Discard()
{
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    if (unk_e64 != NULL && func_020e28dc(unk_e64))
        func_020e263c(unk_e64, ticks);
    if (menuStep_ == 0)
    {
        unk_3dd1 = 8;
        OpenDialog();
        OpenChoice();
        menuStep_++;
    }
    else if (menuStep_ == 1)
    {
        int choice = func_020e2918(unk_e64);
        if (choice >= 0)
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_020e25e8(unk_e64);
        }
        else if (func_020e2984(unk_e64))
        {
            func_020e25e8(unk_e64);
            choice = -2;
        }
        if (choice == 0)
        {
            PartEntry* item = func_020dedd0(items_, slots_[slot_].item_);
            int result = func_020dd768(item);
            if (result == 1)
            {
                unk_3dd1 = 10;
                memset(text_, 0, 0x960);
                WriteMessage(text_);
                if (slot_ >= 0 && slot_ < 8)
                {
                    if (item->cursed_ != 0)
                    {
                        unk_3dd1 = 12;
                        memset(text_, 0, 0x960);
                        WriteMessage(text_);
                        func_0205d5d0(&window_, 0, text_, 1, 0);
                        menuState_ = 4;
                        menuStep_ = 0;
                        return;
                    }
                    Equip(0xffff, 1);
                }
                else if (slot_ >= 8 && slot_ < 24)
                {
                    char* party = func_02010828(GameState::GetInstance());
                    short id = item->unk_18;
                    func_0207c484(party + 0x1d4, id, 1, item->category_);
                    int reload = 1;
                    LoadPage();
                    for (int i = 8; i < 24; i++)
                    {
                        if (id == slots_[i].item_)
                        {
                            reload = 0;
                            break;
                        }
                    }
                    if (reload)
                    {
                        flags_ |= EQUIPMENT_LOAD_PAGE;
                        pageStep_ = 0;
                    }
                }
                func_0205d5d0(&window_, 0, text_, 1, 0);
            }
            else if (result == 2)
            {
                unk_3dd1 = 9;
                memset(text_, 0, 0x960);
                WriteMessage(text_);
                func_0205d5d0(&window_, 0, text_, 1, 0);
                menuStep_++;
                return;
            }
            else if (result == 4)
            {
                unk_3dd1 = 11;
                memset(text_, 0, 0x960);
                WriteMessage(text_);
                func_0205d5d0(&window_, 0, text_, 1, 0);
            }
            menuState_ = 4;
            menuStep_ = 0;
        }
        else if (choice == -2 || choice == 1)
        {
            menuState_ = 4;
            menuStep_ = 0;
        }
    }
    else if (menuStep_ == 2)
    {
        OpenChoice();
        menuStep_++;
    }
    else if (menuStep_ == 3)
    {
        int choice = func_020e2918(unk_e64);
        if (choice >= 0)
        {
            func_0205eaa0(data_02108760, 1, 0);
            func_020e25e8(unk_e64);
        }
        else if (func_020e2984(unk_e64))
        {
            func_020e25e8(unk_e64);
            choice = -2;
        }
        if (choice == 0)
        {
            unk_3dd1 = 10;
            memset(text_, 0, 0x960);
            WriteMessage(text_);
            if (slot_ >= 0 && slot_ < 8)
            {
                if (func_020dedd0(items_, slots_[slot_].item_)->cursed_ != 0)
                {
                    unk_3dd1 = 12;
                    memset(text_, 0, 0x960);
                    WriteMessage(text_);
                    func_0205d5d0(&window_, 0, text_, 1, 0);
                    menuState_ = 4;
                    menuStep_ = 0;
                    return;
                }
                Equip(0xffff, 1);
            }
            else if (slot_ >= 8 && slot_ < 24)
            {
                char* party = func_02010828(GameState::GetInstance());
                PartEntry* item = func_020dedd0(items_, slots_[slot_].item_);
                short id = item->unk_18;
                func_0207c484(party + 0x1d4, id, 1, item->category_);
                int reload = 1;
                LoadPage();
                for (int i = 8; i < 24; i++)
                {
                    if (id == slots_[i].item_)
                    {
                        reload = 0;
                        break;
                    }
                }
                if (reload)
                {
                    flags_ |= EQUIPMENT_LOAD_PAGE;
                    pageStep_ = 0;
                }
            }
            func_0205d5d0(&window_, 0, text_, 1, 0);
            menuState_ = 4;
            menuStep_ = 0;
        }
        else if (choice == -2 || choice == 1)
        {
            menuState_ = 4;
            menuStep_ = 0;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13EquipmentMenu10OpenChoiceEv(); // EquipmentMenu::OpenChoice
    void _ZN13EquipmentMenu10OpenDialogEv(); // EquipmentMenu::OpenDialog
    void _ZN13EquipmentMenu12WriteMessageEPt(); // EquipmentMenu::WriteMessage
    void _ZN13EquipmentMenu5EquipEii(); // EquipmentMenu::Equip
    void _ZN13EquipmentMenu8LoadPageEv(); // EquipmentMenu::LoadPage
    void _ZNK9GameState12GetTickCountEv(); // GameState::GetTickCount
}

asm void EquipmentMenu::Menu_Discard()
{
    stmdb sp!, {r3, r4, r5, r6, lr}
    sub sp, sp, #0x4
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    bl _ZNK9GameState12GetTickCountEv
    movs r4, r0
    ldr r0, [r5, #0xe64]
    moveq r4, #0x1
    cmp r0, #0x0
    beq @L021592b4
    bl func_020e28dc
    cmp r0, #0x0
    beq @L021592b4
    ldr r0, [r5, #0xe64]
    mov r1, r4
    bl func_020e263c
@L021592b4:
    add r1, r5, #0x3000
    ldrb r0, [r1, #0xddc]
    cmp r0, #0x0
    bne @L021592f0
    mov r2, #0x8
    mov r0, r5
    strb r2, [r1, #0xdd1]
    bl _ZN13EquipmentMenu10OpenDialogEv
    mov r0, r5
    bl _ZN13EquipmentMenu10OpenChoiceEv
    add r0, r5, #0x3000
    ldrb r1, [r0, #0xddc]
    add r1, r1, #0x1
    strb r1, [r0, #0xddc]
    b @L02159840
@L021592f0:
    cmp r0, #0x1
    bne @L021595d8
    ldr r0, [r5, #0xe64]
    bl func_020e2918
    movs r4, r0
    bmi @L02159324
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    ldr r0, [r5, #0xe64]
    bl func_020e25e8
    b @L02159340
@L02159324:
    ldr r0, [r5, #0xe64]
    bl func_020e2984
    cmp r0, #0x0
    beq @L02159340
    ldr r0, [r5, #0xe64]
    bl func_020e25e8
    mvn r4, #0x1
@L02159340:
    cmp r4, #0x0
    bne @L021595b0
    add r0, r5, #0x3d00
    ldrsb r2, [r0, #0xbb]
    mov r1, #0x1c
    ldr r0, [r5, #0xdf4]
    mla r1, r2, r1, r5
    add r1, r1, #0x2d00
    ldrsh r1, [r1, #0x90]
    bl func_020dedd0
    mov r6, r0
    bl func_020dd768
    cmp r0, #0x1
    bne @L021594ec
    add r0, r5, #0x3000
    mov r1, #0xa
    strb r1, [r0, #0xdd1]
    ldr r0, [r5, #0xe10]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldr r1, [r5, #0xe10]
    mov r0, r5
    bl _ZN13EquipmentMenu12WriteMessageEPt
    add r0, r5, #0x3d00
    ldrsb r0, [r0, #0xbb]
    cmp r0, #0x0
    blt @L02159438
    cmp r0, #0x8
    bge @L02159438
    ldr r0, [r6, #0x8]
    mov r0, r0, lsl #0xd
    movs r0, r0, lsr #0x1f
    beq @L02159424
    add r0, r5, #0x3000
    mov r1, #0xc
    strb r1, [r0, #0xdd1]
    ldr r0, [r5, #0xe10]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldr r1, [r5, #0xe10]
    mov r0, r5
    bl _ZN13EquipmentMenu12WriteMessageEPt
    mov r1, #0x0
    str r1, [sp, #0x0]
    add r0, r5, #0x2e4
    ldr r2, [r5, #0xe10]
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
    add r0, r5, #0x3000
    mov r1, #0x4
    strb r1, [r0, #0xddf]
    mov r1, #0x0
    strb r1, [r0, #0xddc]
    b @L02159840
@L02159424:
    ldr r1, =0xffff
    mov r0, r5
    mov r2, #0x1
    bl _ZN13EquipmentMenu5EquipEii
    b @L021594cc
@L02159438:
    cmp r0, #0x8
    blt @L021594cc
    cmp r0, #0x18
    bge @L021594cc
    bl _ZN9GameState11GetInstanceEv
    bl func_02010828
    ldr r1, [r6, #0x8]
    ldrsh r4, [r6, #0x18]
    mov r2, r1, lsl #0x1c
    mov r3, r2, lsr #0x1c
    add r0, r0, #0x1d4
    mov r1, r4
    mov r2, #0x1
    bl func_0207c484
    mov r0, r5
    mov r6, #0x1
    bl _ZN13EquipmentMenu8LoadPageEv
    mov r2, #0x8
    mov r0, #0x1c
    b @L021594a4
@L02159488:
    mla r1, r2, r0, r5
    add r1, r1, #0x2d00
    ldrsh r1, [r1, #0x90]
    cmp r4, r1
    moveq r6, #0x0
    beq @L021594ac
    add r2, r2, #0x1
@L021594a4:
    cmp r2, #0x18
    blt @L02159488
@L021594ac:
    cmp r6, #0x0
    beq @L021594cc
    add r0, r5, #0x3000
    ldr r2, [r0, #0xdcc]
    mov r1, #0x0
    orr r2, r2, #0x40
    str r2, [r0, #0xdcc]
    strb r1, [r0, #0xdaa]
@L021594cc:
    mov r1, #0x0
    str r1, [sp, #0x0]
    add r0, r5, #0x2e4
    ldr r2, [r5, #0xe10]
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
    b @L02159598
@L021594ec:
    cmp r0, #0x2
    bne @L0215954c
    add r0, r5, #0x3000
    mov r1, #0x9
    strb r1, [r0, #0xdd1]
    ldr r0, [r5, #0xe10]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldr r1, [r5, #0xe10]
    mov r0, r5
    bl _ZN13EquipmentMenu12WriteMessageEPt
    mov r1, #0x0
    str r1, [sp, #0x0]
    add r0, r5, #0x2e4
    ldr r2, [r5, #0xe10]
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
    add r0, r5, #0x3000
    ldrb r1, [r0, #0xddc]
    add r1, r1, #0x1
    strb r1, [r0, #0xddc]
    b @L02159840
@L0215954c:
    cmp r0, #0x4
    bne @L02159598
    add r0, r5, #0x3000
    mov r1, #0xb
    strb r1, [r0, #0xdd1]
    ldr r0, [r5, #0xe10]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldr r1, [r5, #0xe10]
    mov r0, r5
    bl _ZN13EquipmentMenu12WriteMessageEPt
    mov r1, #0x0
    str r1, [sp, #0x0]
    add r0, r5, #0x2e4
    ldr r2, [r5, #0xe10]
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
@L02159598:
    add r0, r5, #0x3000
    mov r1, #0x4
    strb r1, [r0, #0xddf]
    mov r1, #0x0
    strb r1, [r0, #0xddc]
    b @L02159840
@L021595b0:
    mvn r0, #0x1
    cmp r4, r0
    cmpne r4, #0x1
    bne @L02159840
    add r0, r5, #0x3000
    mov r1, #0x4
    strb r1, [r0, #0xddf]
    mov r1, #0x0
    strb r1, [r0, #0xddc]
    b @L02159840
@L021595d8:
    cmp r0, #0x2
    bne @L021595fc
    mov r0, r5
    bl _ZN13EquipmentMenu10OpenChoiceEv
    add r0, r5, #0x3000
    ldrb r1, [r0, #0xddc]
    add r1, r1, #0x1
    strb r1, [r0, #0xddc]
    b @L02159840
@L021595fc:
    cmp r0, #0x3
    bne @L02159840
    ldr r0, [r5, #0xe64]
    bl func_020e2918
    movs r4, r0
    bmi @L02159630
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    ldr r0, [r5, #0xe64]
    bl func_020e25e8
    b @L0215964c
@L02159630:
    ldr r0, [r5, #0xe64]
    bl func_020e2984
    cmp r0, #0x0
    beq @L0215964c
    ldr r0, [r5, #0xe64]
    bl func_020e25e8
    mvn r4, #0x1
@L0215964c:
    cmp r4, #0x0
    bne @L0215981c
    add r0, r5, #0x3000
    mov r1, #0xa
    strb r1, [r0, #0xdd1]
    ldr r0, [r5, #0xe10]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldr r1, [r5, #0xe10]
    mov r0, r5
    bl _ZN13EquipmentMenu12WriteMessageEPt
    add r0, r5, #0x3d00
    ldrsb r1, [r0, #0xbb]
    cmp r1, #0x0
    blt @L0215972c
    cmp r1, #0x8
    bge @L0215972c
    mov r0, #0x1c
    mla r0, r1, r0, r5
    add r0, r0, #0x2d00
    ldrsh r1, [r0, #0x90]
    ldr r0, [r5, #0xdf4]
    bl func_020dedd0
    ldr r0, [r0, #0x8]
    mov r0, r0, lsl #0xd
    movs r0, r0, lsr #0x1f
    beq @L02159718
    add r0, r5, #0x3000
    mov r1, #0xc
    strb r1, [r0, #0xdd1]
    ldr r0, [r5, #0xe10]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldr r1, [r5, #0xe10]
    mov r0, r5
    bl _ZN13EquipmentMenu12WriteMessageEPt
    mov r1, #0x0
    str r1, [sp, #0x0]
    add r0, r5, #0x2e4
    ldr r2, [r5, #0xe10]
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
    add r0, r5, #0x3000
    mov r1, #0x4
    strb r1, [r0, #0xddf]
    mov r1, #0x0
    strb r1, [r0, #0xddc]
    b @L02159840
@L02159718:
    ldr r1, =0xffff
    mov r0, r5
    mov r2, #0x1
    bl _ZN13EquipmentMenu5EquipEii
    b @L021597e8
@L0215972c:
    cmp r1, #0x8
    blt @L021597e8
    cmp r1, #0x18
    bge @L021597e8
    bl _ZN9GameState11GetInstanceEv
    bl func_02010828
    add r1, r5, #0x3d00
    ldrsb r2, [r1, #0xbb]
    mov r1, #0x1c
    mov r4, r0
    mla r0, r2, r1, r5
    add r0, r0, #0x2d00
    ldrsh r1, [r0, #0x90]
    ldr r0, [r5, #0xdf4]
    bl func_020dedd0
    mov r1, r0
    add r0, r4, #0x1d4
    ldrsh r4, [r1, #0x18]
    ldr r1, [r1, #0x8]
    mov r2, #0x1
    mov r1, r1, lsl #0x1c
    mov r3, r1, lsr #0x1c
    mov r1, r4
    bl func_0207c484
    mov r0, r5
    mov r6, #0x1
    bl _ZN13EquipmentMenu8LoadPageEv
    mov r2, #0x8
    mov r0, #0x1c
    b @L021597c0
@L021597a4:
    mla r1, r2, r0, r5
    add r1, r1, #0x2d00
    ldrsh r1, [r1, #0x90]
    cmp r4, r1
    moveq r6, #0x0
    beq @L021597c8
    add r2, r2, #0x1
@L021597c0:
    cmp r2, #0x18
    blt @L021597a4
@L021597c8:
    cmp r6, #0x0
    beq @L021597e8
    add r0, r5, #0x3000
    ldr r2, [r0, #0xdcc]
    mov r1, #0x0
    orr r2, r2, #0x40
    str r2, [r0, #0xdcc]
    strb r1, [r0, #0xdaa]
@L021597e8:
    mov r1, #0x0
    str r1, [sp, #0x0]
    add r0, r5, #0x2e4
    ldr r2, [r5, #0xe10]
    add r0, r0, #0xc00
    mov r3, #0x1
    bl func_0205d5d0
    add r0, r5, #0x3000
    mov r1, #0x4
    strb r1, [r0, #0xddf]
    mov r1, #0x0
    strb r1, [r0, #0xddc]
    b @L02159840
@L0215981c:
    mvn r0, #0x1
    cmp r4, r0
    cmpne r4, #0x1
    bne @L02159840
    add r0, r5, #0x3000
    mov r1, #0x4
    strb r1, [r0, #0xddf]
    mov r1, #0x0
    strb r1, [r0, #0xddc]
@L02159840:
    add sp, sp, #0x4
    ldmia sp!, {r3, r4, r5, r6, pc}
}
#endif

void EquipmentMenu::Menu_Cancel()
{
    if (menuStep_ != 0)
        return;
    func_0205d6a0(&window_, 1);
    if (slot_ >= 0 && slot_ < 8)
        SetState(3);
    else if (slot_ >= 8 && slot_ < 24)
        SetState(4);
    menuStep_ = 0;
    menuChoice_ = 0;
    menuState_ = 0;
    MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
    screen->flags_ |= MEMBER_SCREEN_TURNING | MEMBER_SCREEN_CHANGE_MEMBER;
    flags_ |= EQUIPMENT_KINDS | EQUIPMENT_ARROWS;
}

// NONMATCHING: the C matches 94.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::OpenMenu()
{
    WindowBase* base = &window_.base_;
    TextWindow* window = &window_;
    func_0205c53c(base);
    int count = 4;
    if (slot_ >= 0 && slot_ < 8)
        count = 3;
    func_0205ba68(&base->frame_, 1, count, 0);
    func_0205ba68(&base->cursor_, 1, count, 0);
    func_0205bacc(&base->frame_, count);
    func_0205bacc(&base->cursor_, count);
    base->frame_.unk_4 = 1;
    base->cursor_.unk_4 = 1;
    signed char choice = menuChoice_;
    func_0205bcdc(&base->frame_, choice);
    func_0205bb04(&base->cursor_, (short)choice);
    window->unk_a8 = 0xc;
    window->unk_aa = 8;
    window->unk_ac = 0xa;
    window->unk_ae = 0xe;
    window->unk_b7 = 0xa;
    window->unk_b1 = 1;
    window->unk_b5 = 0;
    window->unk_b6 = 0;
    memset(text_, 0, 0x960);
    WriteMenu(text_, 0);
    func_0205d304(window, text_, 0, 1, 0, 0, NULL, 0);
}
#else
asm void EquipmentMenu::OpenMenu()
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x10
    mov r5, r0
    add r0, r5, #0x2e4
    add r4, r0, #0xc00
    mov r0, r4
    bl func_0205c53c
    add r0, r5, #0x3d00
    ldrsb r0, [r0, #0xbb]
    mov r6, #0x4
    cmp r0, #0x0
    blt @L0215993c
    cmp r0, #0x8
    movlt r6, #0x3
@L0215993c:
    mov r2, r6
    add r0, r4, #0x4
    mov r1, #0x1
    mov r3, #0x0
    bl func_0205ba68
    mov r2, r6
    add r0, r4, #0x54
    mov r1, #0x1
    mov r3, #0x0
    bl func_0205ba68
    mov r1, r6
    add r0, r4, #0x4
    bl func_0205bacc
    mov r1, r6
    add r0, r4, #0x54
    bl func_0205bacc
    mov r0, #0x1
    str r0, [r4, #0x8]
    str r0, [r4, #0x58]
    add r0, r5, #0x3d00
    ldrsb r6, [r0, #0xde]
    add r0, r4, #0x4
    mov r1, r6
    bl func_0205bcdc
    add r0, r4, #0x54
    mov r1, r6
    bl func_0205bb04
    add r0, r5, #0x2e4
    add r4, r0, #0xc00
    mov r0, #0xc
    strh r0, [r4, #0xa8]
    mov r0, #0x8
    strh r0, [r4, #0xaa]
    mov r1, #0xa
    strh r1, [r4, #0xac]
    mov r0, #0xe
    strh r0, [r4, #0xae]
    strb r1, [r4, #0xb7]
    mov r0, #0x1
    strb r0, [r4, #0xb1]
    mov r1, #0x0
    strb r1, [r4, #0xb5]
    strb r1, [r4, #0xb6]
    ldr r0, [r5, #0xe10]
    mov r2, #0x960
    bl memset
    mov r0, r5
    ldr r1, [r5, #0xe10]
    mov r2, #0x0
    bl _ZN13EquipmentMenu9WriteMenuEPti
    mov r0, r4
    mov r2, #0x0
    str r2, [sp, #0x0]
    str r2, [sp, #0x4]
    str r2, [sp, #0x8]
    str r2, [sp, #0xc]
    ldr r1, [r5, #0xe10]
    mov r3, #0x1
    bl func_0205d304
    add sp, sp, #0x10
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

// NONMATCHING: the C matches 86.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::WriteMenu(unsigned short* text, int touched)
{
    if (text == NULL)
        return;
    signed char choice = menuChoice_;
    if (touched)
        func_02041c08(text, choice, 8, 5, 5);
    func_02041ea4(text, choice);
    int count = 4;
    int equipped = 0;
    if (slot_ >= 0 && slot_ < 8)
    {
        count--;
        equipped = 1;
    }
    const char* separator = func_020e0434(&texts_, 100);
    unsigned int width = 0;
    for (int i = 0; i < count; i++)
    {
        short id = i;
        if (equipped)
        {
            id++;
            if (i == 0)
                id = 4;
        }
        const char* option = func_020e0434(&texts_, id);
        int optionWidth = func_020420e8(option, 0);
        if (width < optionWidth)
        func_02041b70(text, i, option);
            width = optionWidth;
        func_02041b70(text, i, option);
        if (i != count - 1)
            func_02042058(text, separator);
    }
    int tiles = (width + 0x1b) & ~7;
    int columns = (tiles >> 3) + ((tiles >> 3) & 1);
    window_.width_ = columns;
    window_.height_ = 7;
    window_.unk_a4 = (0x20 - columns) >> 1;
    window_.unk_a6 = 9;
}
#else
asm void EquipmentMenu::WriteMenu(unsigned short* text, int touched)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x10
    movs r9, r1
    mov r10, r0
    beq @L02159b6c
    add r0, r10, #0x3d00
    cmp r2, #0x0
    ldrsb r4, [r0, #0xde]
    beq @L02159a70
    mov r3, #0x5
    str r3, [sp, #0x0]
    mov r0, r9
    mov r1, r4
    mov r2, #0x8
    str r3, [sp, #0x4]
    bl func_02041c08
@L02159a70:
    mov r0, r9
    mov r1, r4
    bl func_02041ea4
    add r0, r10, #0x3d00
    ldrsb r0, [r0, #0xbb]
    mov r5, #0x4
    mov r6, #0x0
    cmp r0, #0x0
    blt @L02159aa0
    cmp r0, #0x8
    sublt r5, r5, #0x1
    movlt r6, #0x1
@L02159aa0:
    add r11, r10, #0x1f8
    add r0, r11, #0xc00
    mov r1, #0x64
    bl func_020e0434
    mov r7, #0x0
    str r0, [sp, #0xc]
    mov r8, r7
    sub r4, r5, #0x1
    b @L02159b2c
@L02159ac4:
    mov r0, r8, lsl #0x10
    cmp r6, #0x0
    mov r1, r0, asr #0x10
    beq @L02159ae8
    add r0, r1, #0x1
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    cmp r8, #0x0
    moveq r1, #0x4
@L02159ae8:
    add r0, r11, #0xc00
    bl func_020e0434
    mov r1, #0x0
    str r0, [sp, #0x8]
    bl func_020420e8
    cmp r7, r0
    movlt r7, r0
    ldr r2, [sp, #0x8]
    mov r0, r9
    mov r1, r8
    bl func_02041b70
    cmp r8, r4
    beq @L02159b28
    ldr r1, [sp, #0xc]
    mov r0, r9
    bl func_02042058
@L02159b28:
    add r8, r8, #0x1
@L02159b2c:
    cmp r8, r5
    blt @L02159ac4
    add r0, r7, #0x1b
    bic r1, r0, #0x7
    mov r0, r1, asr #0x3
    and r0, r0, #0x1
    add r2, r0, r1, asr #0x3
    add r0, r10, #0xf00
    rsb r1, r2, #0x20
    strh r2, [r0, #0x84]
    mov r2, #0x7
    strh r2, [r0, #0x86]
    mov r1, r1, asr #0x1
    strh r1, [r0, #0x88]
    mov r1, #0x9
    strh r1, [r0, #0x8a]
@L02159b6c:
    add sp, sp, #0x10
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 90.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::OpenChoice()
{
    func_020e280c(unk_e64, -1);
    (*(char**)((char*)unk_e64 + 0xc))[0x39] = 0x4c;
    void* unk = *(void**)((char*)unk_e64 + 0x10);
    func_020e16dc(unk, 0, 0x18c6);
    func_020e1674(unk, 1, 0);
    short width;
    short height;
    func_020e1e24(unk, &width, &height, 0);
    func_020e28f0(unk_e64, width, height + 4);
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    func_020e263c(unk_e64, ticks);
    func_0205eaa0(data_02108760, 5, 0);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK9GameState12GetTickCountEv(); // GameState::GetTickCount
}

asm void EquipmentMenu::OpenChoice()
{
    stmdb sp!, {r3, r4, r5, lr}
    mov r4, r0
    ldr r0, [r4, #0xe64]
    mvn r1, #0x0
    bl func_020e280c
    ldr r1, [r4, #0xe64]
    mov r0, #0x4c
    ldr r1, [r1, #0xc]
    ldr r2, =0x18c6
    strb r0, [r1, #0x39]
    ldr r0, [r4, #0xe64]
    mov r1, #0x0
    ldr r5, [r0, #0x10]
    mov r0, r5
    bl func_020e16dc
    mov r0, r5
    mov r1, #0x1
    mov r2, #0x0
    bl func_020e1674
    mov r0, r5
    add r1, sp, #0x2
    add r2, sp, #0x0
    mov r3, #0x0
    bl func_020e1e24
    ldrsh r2, [sp, #0x0]
    ldrsh r1, [sp, #0x2]
    ldr r0, [r4, #0xe64]
    add r2, r2, #0x4
    mov r2, r2, lsl #0x10
    mov r2, r2, asr #0x10
    bl func_020e28f0
    bl _ZN9GameState11GetInstanceEv
    bl _ZNK9GameState12GetTickCountEv
    movs r1, r0
    ldr r0, [r4, #0xe64]
    moveq r1, #0x1
    bl func_020e263c
    ldr r0, =data_02108760
    mov r1, #0x5
    mov r2, #0x0
    bl func_0205eaa0
    ldmia sp!, {r3, r4, r5, pc}
}
#endif

void EquipmentMenu::CreateChoice(SpriteAnimationList* animations, SpriteRenderer* renderer)
{
    unk_280.Reset();
    unk_e64 = unk_280.Allocate(0x24);
    func_020e2490(unk_e64, 0, 1, animations, &unk_280, 4, 0x40);
    unk_e68 = (int)renderer;
}

// NONMATCHING: the C matches 84.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::DrawModels()
{
    float currentX;
    EquipmentSlot* slot;
    short item;
    float currentY;
    for (int frame = 0; frame < 31; frame++)
    {
        for (int i = 0; i < 24; i++)
        {
            int targetX;
            slot = &slots_[i];
            MenuModel* model = slot->model_;
            if (i == dragged_ || slot->item_ < 0)
                continue;
            int x = model->position_.x;
            int targetY = slot->y_;
            int y = model->position_.y;
            int dx = targetX - x;
            int dy = targetY - y;
            if (dx == 0 && dy == 0)
                continue;
            Vector3fix position;
            float currentX = x;
            position.x = currentX + 0.01f * dx;
            float currentY = y;
            position.y = currentY + 0.01f * dy;
            position.z = 0;
            if (func_020017b0(targetX - position.x) < 0x800 && func_020017b0(targetY - position.y) < 0x800)
            {
                position.x = targetX;
                position.y = targetY;
                position.z = 0;
            }
            model->SetPosition(&position);
        }
    }
    for (int i = 0; i < 24; i++)
    {
        short alpha = slotModels_[i].unk_82;
        if (alpha < 0x1f)
            slotModels_[i].unk_82 = alpha + 1;
    }
    if (dragged_ >= 0)
    {
        short alpha = dragModel_.unk_82;
        if (alpha < 0x1f)
            dragModel_.unk_82 = alpha + 1;
    }
    if (state_ == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            EquipmentSlot* slot = &slots_[i];
            if (i == dragged_ || slot->item_ < 0)
                continue;
            MenuModel* model = slot->model_;
            Vector3fix position = model->position_;
            position.y = (i * 0x18) << 12;
            model->SetPosition(&position);
            GXFIFO_MATRIX_PUSH = 0;
            func_020473c8(model, 1);
            GXFIFO_MATRIX_POP = 1;
            if (unk_3da8 == 0 && equippedStep_ == 0)
            {
                GXFIFO_MATRIX_PUSH = 0;
                Translate(position.x + 0x8000, position.y + 0x8000, position.z + 0x1000);
                models_[35].alpha_ = 0xf0a;
                func_02047554(&models_[35], 0, 1);
                GXFIFO_MATRIX_POP = 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < 24; i++)
        {
            EquipmentSlot* slot = &slots_[i];
            if (i == slot_ && slot_ >= 8 && slot_ < 24)
            {
                MenuModel* model = slot->model_;
                Vector3fix position = model->position_;
                GXFIFO_MATRIX_PUSH = 0;
                Translate(slot->x_, slot->y_, position.z - 0x1000);
                models_[34].alpha_ = 0x25f;
                func_020473c8(&models_[34], 1);
                GXFIFO_MATRIX_POP = 1;
            }
            short item = slot->item_;
            if (item < 0)
                continue;
            PartEntry* entry = func_020dedd0(items_, item);
            if (entry != NULL)
            {
                MenuModel* model = slot->model_;
                if (func_020dd4c4(func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_, entry))
                {
                    Vector3fix position = model->position_;
                    if (i >= 8 && i < 24)
                    {
                        GXFIFO_MATRIX_PUSH = 0;
                        Translate(slot->x_, slot->y_, position.z - 0x1000);
                        models_[34].alpha_ = 0x1ce7;
                        func_020473c8(&models_[34], 1);
                        GXFIFO_MATRIX_POP = 1;
                    }
                    model->alpha_ = 0x3def;
                }
                else
                {
                    model->alpha_ = 0x7fff;
                }
            }
            if (i == dragged_)
                continue;
            if (i != kind_ && i < 8)
                continue;
            GXFIFO_MATRIX_PUSH = 0;
            MenuModel* model = slot->model_;
            func_020473c8(model, 1);
            GXFIFO_MATRIX_POP = 1;
            if (i < 8 && unk_3da8 == 0 && equippedStep_ == 0)
            {
                Vector3fix position = model->position_;
                GXFIFO_MATRIX_PUSH = 0;
                Translate(position.x + 0x8000, position.y + 0x8000, position.z + 0x1000);
                models_[35].alpha_ = 0xf0a;
                func_02047554(&models_[35], 0, 1);
                GXFIFO_MATRIX_POP = 1;
            }
        }
    }
    if (dragged_ >= 0 && dragStep_ == 0)
    {
        GXFIFO_MATRIX_PUSH = 0;
        func_020473c8(&dragModel_, 1);
        GXFIFO_MATRIX_POP = 1;
        Vector3fix position = dragModel_.position_;
        frame_.SetTargetPosition(position.x, position.y);
        frame_.SetPosition(position.x, position.y);
        frame_.SetTargetSize(0x18000, 0x18000);
        frame_.SetSize(0x18000, 0x18000);
        if (dragged_ < 8 && dragStep_ == 0)
        {
            Vector3fix position2 = dragModel_.position_;
            GXFIFO_MATRIX_PUSH = 0;
            Translate(position2.x + 0x8000, position2.y + 0x8000, position2.z + 0x1000);
            models_[35].alpha_ = 0xf0a;
            func_02047554(&models_[35], 0, 1);
            GXFIFO_MATRIX_POP = 1;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9MenuModel11SetPositionEPK8Vector3i(); // MenuModel::SetPosition
}

asm void EquipmentMenu::DrawModels()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x78
    mov r10, r0
    mov r4, #0x0
    b @L02159dc4
@L02159c9c:
    add r0, r10, #0xd90
    add r11, r0, #0x2000
    add r0, r10, #0x3d00
    mov r5, #0x0
    str r0, [sp, #0x18]
    b @L02159db8
@L02159cb4:
    mov r0, #0x1c
    mla r1, r5, r0, r11
    ldr r0, [sp, #0x18]
    ldr r9, [r1, #0x8]
    ldrsh r0, [r0, #0x78]
    cmp r5, r0
    beq @L02159db4
    ldrsh r0, [r1, #0x0]
    cmp r0, #0x0
    blt @L02159db4
    ldr r0, [r9, #0x1c]
    ldr r6, [r1, #0xc]
    ldr r7, [r1, #0x10]
    ldr r1, [r9, #0x20]
    str r1, [sp, #0x4]
    subs r1, r6, r0
    str r1, [sp, #0x0]
    ldr r1, [sp, #0x4]
    sub r8, r7, r1
    cmpeq r8, #0x0
    beq @L02159db4
    bl _fflt
    str r0, [sp, #0x8]
    ldr r0, [sp, #0x0]
    bl _fflt
    mov r1, r0
    ldr r0, =0x3c23d70a
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0x8]
    bl _fadd
    bl _ffix
    str r0, [sp, #0x6c]
    ldr r0, [sp, #0x4]
    bl _fflt
    str r0, [sp, #0xc]
    mov r0, r8
    bl _fflt
    mov r1, r0
    ldr r0, =0x3c23d70a
    bl _fmul
    mov r1, r0
    ldr r0, [sp, #0xc]
    bl _fadd
    bl _ffix
    str r0, [sp, #0x70]
    mov r0, #0x0
    str r0, [sp, #0x74]
    ldr r0, [sp, #0x6c]
    sub r0, r6, r0
    bl func_020017b0
    cmp r0, #0x800
    bge @L02159da8
    ldr r0, [sp, #0x70]
    sub r0, r7, r0
    bl func_020017b0
    cmp r0, #0x800
    movlt r0, #0x0
    strlt r6, [sp, #0x6c]
    strlt r7, [sp, #0x70]
    strlt r0, [sp, #0x74]
@L02159da8:
    mov r0, r9
    add r1, sp, #0x6c
    bl _ZN9MenuModel11SetPositionEPK8Vector3i
@L02159db4:
    add r5, r5, #0x1
@L02159db8:
    cmp r5, #0x18
    blt @L02159cb4
    add r4, r4, #0x1
@L02159dc4:
    cmp r4, #0x1f
    blt @L02159c9c
    add r0, r10, #0xb2
    add r2, r0, #0x3000
    mov r4, #0x0
    mov r0, #0x88
    b @L02159df8
@L02159de0:
    mul r3, r4, r0
    ldrsh r1, [r2, r3]
    add r4, r4, #0x1
    cmp r1, #0x1f
    addlt r1, r1, #0x1
    strlth r1, [r2, r3]
@L02159df8:
    cmp r4, #0x18
    blt @L02159de0
    add r0, r10, #0x3d00
    ldrsh r1, [r0, #0x78]
    cmp r1, #0x0
    blt @L02159e20
    ldrsh r1, [r0, #0x72]
    cmp r1, #0x1f
    addlt r1, r1, #0x1
    strlth r1, [r0, #0x72]
@L02159e20:
    add r5, r10, #0x3000
    ldrb r0, [r5, #0xdb8]
    ldr r6, =0x4000444
    cmp r0, #0x0
    bne @L02159f34
    add r0, r10, #0xd90
    add r7, r0, #0x2000
    add r0, r10, #0x2d00
    mov r8, #0x0
    add r4, r10, #0x108
    str r0, [sp, #0x1c]
    add r11, r10, #0x3d00
    b @L02159f28
@L02159e54:
    mov r0, #0x1c
    mla r1, r8, r0, r7
    ldrsh r0, [r11, #0x78]
    cmp r8, r0
    beq @L02159f24
    ldrsh r0, [r1, #0x0]
    cmp r0, #0x0
    blt @L02159f24
    mov r0, #0x18
    mul r0, r8, r0
    ldr r9, [r1, #0x8]
    mov r12, r0, lsl #0xc
    add r0, r9, #0x1c
    add r3, sp, #0x60
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r0, r9
    mov r1, r3
    str r12, [sp, #0x64]
    bl _ZN9MenuModel11SetPositionEPK8Vector3i
    mov r1, #0x0
    str r1, [r6, #0x0]
    mov r0, r9
    mov r1, #0x1
    bl func_020473c8
    mov r0, #0x1
    str r0, [r6, #0x4]
    ldrb r0, [r5, #0xda8]
    cmp r0, #0x0
    ldreqb r0, [r5, #0xda9]
    cmpeq r0, #0x0
    bne @L02159f24
    ldr r2, [sp, #0x68]
    ldr r1, [sp, #0x60]
    ldr r0, [sp, #0x64]
    add r3, r2, #0x1000
    mov r2, #0x0
    str r2, [r6, #0x0]
    add r1, r1, #0x8000
    add r9, r0, #0x8000
    str r1, [r6, #0x2c]
    str r9, [r6, #0x2c]
    ldr r2, =0xf0a
    ldr r1, [sp, #0x1c]
    str r3, [r6, #0x2c]
    strh r2, [r1, #0x88]
    add r0, r4, #0x2c00
    mov r1, #0x0
    mov r2, #0x1
    bl func_02047554
    mov r0, #0x1
    str r0, [r6, #0x4]
@L02159f24:
    add r8, r8, #0x1
@L02159f28:
    cmp r8, #0x8
    blt @L02159e54
    b @L0215a168
@L02159f34:
    add r0, r10, #0xd90
    add r0, r0, #0x2000
    str r0, [sp, #0x10]
    add r0, r10, #0x108
    mov r7, #0x0
    str r0, [sp, #0x20]
    add r4, r10, #0x2d00
    add r11, r10, #0x3d00
    b @L0215a160
@L02159f58:
    ldr r0, [sp, #0x10]
    mov r1, #0x1c
    mla r8, r7, r1, r0
    ldrsb r0, [r11, #0xbb]
    cmp r7, r0
    bne @L02159fd4
    cmp r0, #0x8
    blt @L02159fd4
    cmp r0, #0x18
    bge @L02159fd4
    ldr r0, [r8, #0x8]
    ldr r9, [r8, #0xc]
    add r0, r0, #0x1c
    ldr r3, [r8, #0x10]
    add r12, sp, #0x54
    ldmia r0, {r0, r1, r2}
    stmia r12, {r0, r1, r2}
    mov r0, #0x0
    str r0, [r6, #0x0]
    str r9, [r6, #0x2c]
    str r3, [r6, #0x2c]
    ldr r1, [sp, #0x5c]
    add r0, r10, #0x2c80
    sub r1, r1, #0x1000
    str r1, [r6, #0x2c]
    ldr r1, =0x25f
    strh r1, [r4, #0x0]
    mov r1, #0x1
    bl func_020473c8
    mov r0, #0x1
    str r0, [r6, #0x4]
@L02159fd4:
    ldrsh r0, [r8, #0x0]
    cmp r0, #0x0
    blt @L0215a15c
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    ldr r0, [r10, #0xdf4]
    bl func_020dedd0
    str r0, [sp, #0x14]
    cmp r0, #0x0
    beq @L0215a0a0
    ldr r9, [r8, #0x8]
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r0, [r0, #0x4fc]
    ldr r1, [sp, #0x14]
    mov r0, r0, lsl #0x18
    mov r0, r0, asr #0x18
    bl func_020dd4c4
    cmp r0, #0x0
    beq @L0215a098
    ldr r12, [r8, #0xc]
    add r0, r9, #0x1c
    ldr lr, [r8, #0x10]
    add r3, sp, #0x48
    ldmia r0, {r0, r1, r2}
    cmp r7, #0x8
    stmia r3, {r0, r1, r2}
    blt @L0215a08c
    cmp r7, #0x18
    bge @L0215a08c
    mov r0, #0x0
    str r0, [r6, #0x0]
    str r12, [r6, #0x2c]
    str lr, [r6, #0x2c]
    ldr r1, [sp, #0x50]
    add r0, r10, #0x2c80
    sub r1, r1, #0x1000
    str r1, [r6, #0x2c]
    ldr r1, =0x1ce7
    strh r1, [r4, #0x0]
    mov r1, #0x1
    bl func_020473c8
    mov r0, #0x1
    str r0, [r6, #0x4]
@L0215a08c:
    ldr r0, =0x3def
    strh r0, [r9, #0x80]
    b @L0215a0a0
@L0215a098:
    ldr r0, =0x7fff
    strh r0, [r9, #0x80]
@L0215a0a0:
    ldrsh r0, [r11, #0x78]
    cmp r7, r0
    beq @L0215a15c
    ldr r8, [r8, #0x8]
    ldrb r0, [r5, #0xdbc]
    cmp r7, r0
    beq @L0215a0c4
    cmp r7, #0x8
    blt @L0215a15c
@L0215a0c4:
    mov r0, #0x0
    str r0, [r6, #0x0]
    mov r0, r8
    mov r1, #0x1
    bl func_020473c8
    mov r0, #0x1
    str r0, [r6, #0x4]
    cmp r7, #0x8
    bge @L0215a15c
    ldrb r0, [r5, #0xda8]
    cmp r0, #0x0
    ldreqb r0, [r5, #0xda9]
    cmpeq r0, #0x0
    bne @L0215a15c
    add r0, r8, #0x1c
    add r3, sp, #0x3c
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r0, #0x0
    str r0, [r6, #0x0]
    ldr r1, [sp, #0x3c]
    ldr r0, [sp, #0x20]
    add r1, r1, #0x8000
    str r1, [r6, #0x2c]
    ldr r2, [sp, #0x40]
    add r0, r0, #0x2c00
    add r2, r2, #0x8000
    str r2, [r6, #0x2c]
    ldr r3, [sp, #0x44]
    mov r1, #0x0
    add r3, r3, #0x1000
    str r3, [r6, #0x2c]
    ldr r3, =0xf0a
    mov r2, #0x1
    strh r3, [r4, #0x88]
    bl func_02047554
    mov r0, #0x1
    str r0, [r6, #0x4]
@L0215a15c:
    add r7, r7, #0x1
@L0215a160:
    cmp r7, #0x18
    blt @L02159f58
@L0215a168:
    add r0, r10, #0x3d00
    ldrsh r0, [r0, #0x78]
    cmp r0, #0x0
    blt @L0215a2a0
    add r0, r10, #0x3000
    ldrb r0, [r0, #0xdab]
    cmp r0, #0x0
    bne @L0215a2a0
    add r0, r10, #0xcf0
    ldr r2, =0x4000444
    mov r3, #0x0
    add r0, r0, #0x3000
    mov r1, #0x1
    str r3, [r2, #0x0]
    bl func_020473c8
    add r0, r10, #0x10c
    ldr r1, =0x4000448
    mov r2, #0x1
    add r3, sp, #0x30
    str r2, [r1, #0x0]
    add r0, r0, #0x3c00
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldr r4, [sp, #0x34]
    add r0, r10, #0x234
    ldr r1, [sp, #0x30]
    mov r2, r4
    add r0, r0, #0x1800
    bl _ZN11CursorFrame17SetTargetPositionEii
    add r0, r10, #0x234
    ldr r1, [sp, #0x30]
    mov r2, r4
    add r0, r0, #0x1800
    bl _ZN11CursorFrame11SetPositionEii
    add r0, r10, #0x234
    mov r1, #0x18000
    add r0, r0, #0x1800
    mov r2, r1
    bl _ZN11CursorFrame13SetTargetSizeEii
    add r0, r10, #0x234
    mov r1, #0x18000
    add r0, r0, #0x1800
    mov r2, r1
    bl _ZN11CursorFrame7SetSizeEii
    add r0, r10, #0x3d00
    ldrsh r0, [r0, #0x78]
    cmp r0, #0x8
    bge @L0215a2a0
    add r0, r10, #0x3000
    ldrb r0, [r0, #0xdab]
    cmp r0, #0x0
    bne @L0215a2a0
    add r0, r10, #0x10c
    add r0, r0, #0x3c00
    add r3, sp, #0x24
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    ldr r5, =0x4000444
    mov r1, #0x0
    str r1, [r5, #0x0]
    ldr r2, [sp, #0x24]
    add r0, r10, #0x108
    add r2, r2, #0x8000
    str r2, [r5, #0x2c]
    ldr r2, [sp, #0x28]
    ldr r4, =0xf0a
    add r2, r2, #0x8000
    str r2, [r5, #0x2c]
    ldr r2, [sp, #0x2c]
    add r3, r10, #0x2d00
    add r2, r2, #0x1000
    str r2, [r5, #0x2c]
    add r0, r0, #0x2c00
    mov r2, #0x1
    strh r4, [r3, #0x88]
    bl func_02047554
    mov r1, #0x1
    str r1, [r5, #0x4]
@L0215a2a0:
    add sp, sp, #0x78
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void EquipmentMenu::DrawPageArrows()
{
    if (pageCounts_[kind_] == 1)
        return;
    short leftX = 0x8e;
    short leftY = 0xa0;
    if (flags_ & EQUIPMENT_PREVIOUS_PAGE)
    {
        leftX--;
        leftY++;
        flags_ &= ~EQUIPMENT_PREVIOUS_PAGE;
    }
    short rightX = 0xeb;
    short rightY = 0xa0;
    if (flags_ & EQUIPMENT_NEXT_PAGE)
    {
        rightX++;
        rightY++;
        flags_ &= ~EQUIPMENT_NEXT_PAGE;
    }
    func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->DrawArrows1(leftX, leftY, rightX, rightY);
}

void EquipmentMenu::DrawKindArrows()
{
    if (state_ != 3)
        return;
    func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->DrawArrows2(0xbd, 0x10, 0xbd, 0x2f);
}

void EquipmentMenu::DrawSortButton()
{
    short x = 0x80;
    short y = 0xb0;
    if (flags_ & EQUIPMENT_SORT)
    {
        x++;
        y++;
        flags_ &= ~EQUIPMENT_SORT;
    }
    func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->DrawArrow3(x, y);
}

static const unsigned char sKindParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};

// NONMATCHING: the C matches 91.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::DrawKinds()
{
    GameState* gameState = GameState::GetInstance();
    PartyMember* member = func_0200ff1c(gameState, func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_);
    short* equipment = func_02052e14(member);
    if (state_ != 0)
        return;
    for (int i = 0; i < 8; i++)
    {
        int selected = 0;
        if (i == kind_)
            selected = 1;
        int base = selected * 11;
        MenuModel* models = models_;
        GXFIFO_MATRIX_PUSH = 0;
        GXFIFO_MATRIX_TRANSLATE = 0x7f000;
        int y = (i * 0x18) << 12;
        GXFIFO_MATRIX_TRANSLATE = y;
        GXFIFO_MATRIX_TRANSLATE = -0x200000;
        func_02047554(&models[base + 4], 0, 1);
        GXFIFO_MATRIX_POP = 1;
        GXFIFO_MATRIX_PUSH = 0;
        GXFIFO_MATRIX_TRANSLATE = 0x100000;
        GXFIFO_MATRIX_TRANSLATE = y;
        GXFIFO_MATRIX_TRANSLATE = -0x200000;
        Matrix4x3 matrix;
        matrix = RotationMatrixY(0x3244);
        func_020c51a4(&matrix);
        func_02047554(&models[base + 4], 0, 1);
        GXFIFO_MATRIX_POP = 1;
        GXFIFO_MATRIX_PUSH = 0;
        GXFIFO_MATRIX_TRANSLATE = 0x70000;
        GXFIFO_MATRIX_TRANSLATE = y;
        GXFIFO_MATRIX_TRANSLATE = -0x200000;
        GXFIFO_MATRIX_SCALE = 0x14000;
        GXFIFO_MATRIX_SCALE = 0x1000;
        GXFIFO_MATRIX_SCALE = 0x1000;
        func_02047554(&models_[base + 5], 0, 1);
        GXFIFO_MATRIX_POP = 1;
        MenuModel* icon = &models_[base + 7 + i];
        if (equipment[sKindParts[i]] > 0)
            icon = &models_[base + 6];
        GXFIFO_MATRIX_PUSH = 0;
        GXFIFO_MATRIX_TRANSLATE = 0x85000;
        GXFIFO_MATRIX_TRANSLATE = y;
        GXFIFO_MATRIX_TRANSLATE = -0x1ff000;
        func_02047554(icon, 0, 1);
        GXFIFO_MATRIX_POP = 1;
    }
}
#else
asm void EquipmentMenu::DrawKinds()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x60
    mov r9, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r4
    bl func_0200ff1c
    bl func_02052e14
    add r1, r9, #0x3000
    ldrb r1, [r1, #0xdb8]
    mov r11, r0
    cmp r1, #0x0
    bne @L0215a608
    mov r6, #0x0
    b @L0215a600
@L0215a468:
    add r0, r9, #0x3000
    ldrb r0, [r0, #0xdbc]
    mov r1, #0x0
    ldr r3, =0x4000444
    cmp r6, r0
    moveq r1, #0x1
    mov r0, #0xb
    mul r7, r1, r0
    mov r0, #0x18
    mul r8, r6, r0
    mov r1, #0x0
    add r4, r7, #0x4
    mov r0, #0x88
    mul r5, r4, r0
    add r2, r9, #0xa70
    add r4, r2, #0x1000
    str r1, [r3, #0x0]
    mov r0, #0x7f000
    str r0, [r3, #0x2c]
    mov r8, r8, lsl #0xc
    str r8, [r3, #0x2c]
    sub r10, r1, #0x200000
    add r0, r4, r5
    mov r2, #0x1
    str r10, [r3, #0x2c]
    bl func_02047554
    ldr r3, =0x4000448
    mov r0, #0x1
    str r0, [r3, #0x0]
    mov r0, #0x0
    str r0, [r3, #-0x4]
    mov r2, #0x100000
    str r2, [r3, #0x28]
    ldr r1, =0x3244
    add r0, sp, #0x0
    str r8, [r3, #0x28]
    sub r2, r2, #0x300000
    str r2, [r3, #0x28]
    bl RotationMatrixY
    add r10, sp, #0x0
    add lr, sp, #0x30
    mov r12, #0x3
@L0215a510:
    ldmia r10!, {r0, r1, r2, r3}
    stmia lr!, {r0, r1, r2, r3}
    subs r12, r12, #0x1
    bne @L0215a510
    add r0, sp, #0x30
    bl func_020c51a4
    add r0, r4, r5
    mov r1, #0x0
    mov r2, #0x1
    bl func_02047554
    add r1, r9, #0xa70
    add r4, r1, #0x1000
    ldr r0, =0x4000448
    mov r2, #0x1
    str r2, [r0, #0x0]
    mov r1, #0x0
    mov r3, #0x70000
    str r1, [r0, #-0x4]
    str r3, [r0, #0x28]
    sub r3, r3, #0x270000
    str r8, [r0, #0x28]
    str r3, [r0, #0x28]
    mov r3, #0x14000
    str r3, [r0, #0x24]
    mov r3, #0x1000
    str r3, [r0, #0x24]
    str r3, [r0, #0x24]
    add r3, r7, #0x5
    mov r0, #0x88
    mla r0, r3, r0, r4
    bl func_02047554
    add r0, r9, #0xa70
    ldr r2, =sKindParts
    add r1, r0, #0x1000
    ldrb r0, [r2, r6]
    ldr r2, =0x4000448
    mov r3, #0x1
    str r3, [r2, #0x0]
    mov r0, r0, lsl #0x1
    ldrsh r0, [r11, r0]
    add r2, r7, #0x7
    add r3, r2, r6
    mov r2, #0x88
    cmp r0, #0x0
    mla r0, r3, r2, r1
    addgt r3, r7, #0x6
    mlagt r0, r3, r2, r1
    mov r2, #0x85000
    ldr r4, =0x4000444
    mov r1, #0x0
    str r1, [r4, #0x0]
    str r2, [r4, #0x2c]
    sub r3, r2, #0x284000
    str r8, [r4, #0x2c]
    mov r2, #0x1
    str r3, [r4, #0x2c]
    bl func_02047554
    mov r1, #0x1
    str r1, [r4, #0x4]
    add r6, r6, #0x1
@L0215a600:
    cmp r6, #0x8
    blt @L0215a468
@L0215a608:
    add sp, sp, #0x60
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void EquipmentMenu::DrawSortIcon()
{
    if (!(flags_ & EQUIPMENT_SORT_ICON))
        return;
    if (state_ == 0 || state_ == 1)
    {
        func_0204b8d0(&backgrounds_[0], 0, 0x16, 0x16, 0x16, 0x16, 10, 2, 0xffff);
    }
    else
    {
        unsigned char tile = 5;
        if (sortOrders_[kind_] == 1)
            tile = 4;
        else if (sortOrders_[kind_] == 2)
            tile = 2;
        else if (sortOrders_[kind_] == 3)
            tile = 3;
        func_0204b8d0(&backgrounds_[0], tile, 0, 0, 0x16, 0x16, 10, 2, 0xffff);
    }
    func_0204b0e8(&backgrounds_[0], 0);
    flags_ &= ~EQUIPMENT_SORT_ICON;
}

void EquipmentMenu::DrawTabs()
{
    if (!(flags_ & EQUIPMENT_KIND_CHANGED))
        return;
    func_0204b010(&backgrounds_[1], 0);
    func_0204b8d0(&backgrounds_[1], 0, 0, 0, 0x10, 0, 0x10, 0x16, 0xffff);
    func_0204b8d0(&backgrounds_[1], kind_ + 1, 0, 0, (short)(kind_ * 2 + 0xf), 0, 4, 3, 0xffff);
    func_0204b04c(&backgrounds_[1], 0);
}

// NONMATCHING: the C matches 76.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::DrawCursor()
{
    short x;
    unsigned char kind;
    int choice;
    short y;
    Canvas* canvas = func_0205d8c4(&window_);
    if (canvas != NULL)
    {
        short y;
        kind = canvas->unk_c4;
        if (unk_e64 != NULL && func_020e28dc(unk_e64))
        {
            func_0205ae8c((SpriteRenderer*)unk_e68);
        }
        else if (kind == 1 && func_0204c7e0(canvas))
        {
            short x = canvas->unk_bc + (short)(canvas->x_ * 8);
            short y = canvas->unk_be + (short)(canvas->y_ * 8);
            if (kind == 2)
            {
                x = 0xd4;
                int choice = func_0205d794(&window_);
                if (choice == 0)
                    y = 0x57;
                else if (choice == 1)
                    y = 0x65;
            }
            func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->DrawCursor(x - 8, y - 2);
        }
    }
    if (state_ != 0)
        return;
    func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->DrawCursor(0x74, y);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12MemberScreen10DrawCursorEss(); // MemberScreen::DrawCursor
}

asm void EquipmentMenu::DrawCursor()
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r5, r0
    add r0, r5, #0x2e4
    add r0, r0, #0xc00
    bl func_0205d8c4
    movs r6, r0
    beq @L0215a8d0
    ldr r0, [r5, #0xe64]
    ldrb r4, [r6, #0xc4]
    cmp r0, #0x0
    beq @L0215a830
    bl func_020e28dc
    cmp r0, #0x0
    beq @L0215a830
    ldr r0, [r5, #0xe68]
    bl func_0205ae8c
    b @L0215a8d0
@L0215a830:
    cmp r4, #0x1
    bne @L0215a8d0
    mov r0, r6
    bl func_0204c7e0
    cmp r0, #0x0
    beq @L0215a8d0
    ldrsh r0, [r6, #0xac]
    ldrsh r1, [r6, #0xae]
    ldrsh r3, [r6, #0xbc]
    mov r0, r0, lsl #0x13
    ldrsh r2, [r6, #0xbe]
    mov r1, r1, lsl #0x13
    add r0, r3, r0, asr #0x10
    add r1, r2, r1, asr #0x10
    mov r0, r0, lsl #0x10
    mov r1, r1, lsl #0x10
    cmp r4, #0x2
    mov r4, r0, asr #0x10
    mov r6, r1, asr #0x10
    bne @L0215a8a4
    add r0, r5, #0x2e4
    add r0, r0, #0xc00
    mov r4, #0xd4
    bl func_0205d794
    cmp r0, #0x0
    moveq r6, #0x57
    beq @L0215a8a4
    cmp r0, #0x1
    moveq r6, #0x65
@L0215a8a4:
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    sub r1, r4, #0x8
    sub r2, r6, #0x2
    mov r1, r1, lsl #0x10
    mov r2, r2, lsl #0x10
    mov r1, r1, asr #0x10
    mov r2, r2, asr #0x10
    bl _ZN12MemberScreen10DrawCursorEss
@L0215a8d0:
    add r0, r5, #0x3000
    ldrb r1, [r0, #0xdb8]
    cmp r1, #0x0
    ldmneia sp!, {r4, r5, r6, pc}
    ldrb r1, [r0, #0xdbc]
    mov r0, #0x18
    smulbb r0, r1, r0
    add r0, r0, #0x4
    mov r0, r0, lsl #0x10
    mov r4, r0, asr #0x10
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    mov r2, r4
    mov r1, #0x74
    bl _ZN12MemberScreen10DrawCursorEss
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

unsigned char EquipmentMenu::GetPart(int kind)
{
    static unsigned char sParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};
    if ((unsigned int)kind >= 8)
        return 0;
    return sParts[kind];
}

unsigned char EquipmentMenu::GetCategory(int kind)
{
    static unsigned char sCategories[8] = {8, 9, 7, 0, 5, 1, 6, 10};
    if ((unsigned int)kind >= 8)
        return 0;
    return sCategories[kind];
}

unsigned char EquipmentMenu::GetList(int kind)
{
    if ((unsigned int)kind >= 8)
        return 0;
    return sLists[kind];
}

void EquipmentMenu::WriteDigits()
{
    MessageSystem* messages = func_020421a0();
    messages->unk_195b_7 = 0;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 3; j++)
            digits_[i][j] = 0xffff;
        int digit = i % 10;
        char text[2];
        sprintf(text, STRING(0x51, "%d"), digit);
        func_02045d14(messages, text, digits_[i], 0);
        if (digit == 9)
        {
            func_020439b0(messages, 0);
            messages->unk_195b_7 = 1;
        }
    }
    messages->unk_195b_7 = 0;
}

void EquipmentMenu::DrawPageNumber()
{
    MessageSystem* messages = func_020421a0();
    int page = page_ + 1;
    int count = pageCounts_[kind_];
    GXFIFO_MATRIX_PUSH = 0;
    GXFIFO_BEGIN_VTXS = 1;
    GXFIFO_MATRIX_TRANSLATE = 0;
    GXFIFO_MATRIX_TRANSLATE = 0;
    GXFIFO_MATRIX_TRANSLATE = -0x3ff000;
    int tens = count / 10;
    if (tens != 0)
    {
        func_02045f3c(messages, digits_[tens], 0xc8, 0x9e, 0x7fff, 8, 0, 0, 0, 0x11);
        func_02045f3c(messages, digits_[count % 10], 0xd0, 0x9e, 0x7fff, 8, 0, 0, 0, 0x11);
    }
    else
    {
        func_02045f3c(messages, digits_[count], 0xcc, 0x9e, 0x7fff, 8, 0, 0, 0, 0x11);
    }
    tens = page / 10;
    if (tens != 0)
    {
        func_02045f3c(messages, digits_[tens], 0xa8, 0x9e, 0x7fff, 8, 0, 0, 0, 0x11);
        func_02045f3c(messages, digits_[page % 10], 0xb0, 0x9e, 0x7fff, 8, 0, 0, 0, 0x11);
    }
    else
    {
        func_02045f3c(messages, digits_[page], 0xac, 0x9e, 0x7fff, 8, 0, 0, 0, 0x11);
    }
    GXFIFO_END_VTXS = 0;
    GXFIFO_MATRIX_POP = 1;
}

// NONMATCHING: the C matches 91.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::DrawCounts()
{
    EquipmentSlot* slots;
    int y;
    int x;
    int count;
    MessageSystem* messages = func_020421a0();
    slots = slots_;
    int units;
    long tens;
    for (int i = 8; i < 24; i++)
    {
        EquipmentSlot* slot;
        unsigned long color;
        int item;
        item = slots[i].item_;
        slot = &slots[i];
        if (item < 0)
            continue;
        count = slot->count_;
        x = slot->x_ >> 12;
        y = slot->y_ >> 12;
        tens = count / 10;
        int units = count % 10;
        color = 0x7fff;
        if (item > 0)
        {
            PartEntry* entry = func_020dedd0(items_, item);
            if (entry != NULL &&
                func_020dd4c4(func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_, entry))
                color = 0x1ce7;
        }
        GXFIFO_MATRIX_PUSH = 0;
        GXFIFO_BEGIN_VTXS = 1;
        GXFIFO_MATRIX_TRANSLATE = 0;
        GXFIFO_MATRIX_TRANSLATE = 0;
        GXFIFO_MATRIX_TRANSLATE = -0x3ff000;
        if (tens != 0)
            func_02045f3c(messages, digits_[tens + 10], x + 0xb, y + 0xc, color, 8, 0, 0, 0, 0x11);
        func_02045f3c(messages, digits_[units + 10], x + 0x11, y + 0xc, color, 8, 0, 0, 0, 0x11);
        GXFIFO_END_VTXS = 0;
        GXFIFO_MATRIX_POP = 1;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _s32_div_f();
}

asm void EquipmentMenu::DrawCounts()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x24
    mov r10, r0
    bl func_020421a0
    str r0, [sp, #0x1c]
    add r0, r10, #0x20c
    add r1, r10, #0xd90
    add r4, r0, #0x3c00
    add r0, r1, #0x2000
    mov r7, #0x8
    str r0, [sp, #0x20]
    b @L0215ae5c
@L0215acf0:
    mov r0, #0x1c
    mul r1, r7, r0
    ldr r0, [sp, #0x20]
    ldrsh r9, [r0, r1]
    add r2, r0, r1
    cmp r9, #0x0
    blt @L0215ae58
    ldrsb r8, [r2, #0x2]
    ldr r1, [r2, #0xc]
    ldr r0, [r2, #0x10]
    mov r6, r1, asr #0xc
    mov r5, r0, asr #0xc
    mov r1, #0xa
    mov r0, r8
    bl _s32_div_f
    mov r11, r0
    mov r0, r8
    mov r1, #0xa
    bl _s32_div_f
    str r1, [sp, #0x18]
    cmp r9, #0x0
    ldr r8, =0x7fff
    ble @L0215ad90
    mov r0, r9, lsl #0x10
    mov r1, r0, asr #0x10
    ldr r0, [r10, #0xdf4]
    bl func_020dedd0
    movs r9, r0
    beq @L0215ad90
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r0, [r0, #0x4fc]
    mov r1, r9
    mov r0, r0, lsl #0x18
    mov r0, r0, asr #0x18
    bl func_020dd4c4
    cmp r0, #0x0
    ldrne r8, =0x1ce7
@L0215ad90:
    ldr r0, =0x4000444
    mov r1, #0x0
    str r1, [r0, #0x0]
    mov r1, #0x1
    str r1, [r0, #0xbc]
    mov r1, #0x0
    str r1, [r0, #0x2c]
    str r1, [r0, #0x2c]
    ldr r1, =0xffc01000
    cmp r11, #0x0
    str r1, [r0, #0x2c]
    beq @L0215ae00
    add r2, r11, #0xa
    mov r0, #0x6
    mla r1, r2, r0, r4
    str r8, [sp, #0x0]
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    mov r0, #0x11
    str r0, [sp, #0x14]
    ldr r0, [sp, #0x1c]
    add r2, r6, #0xb
    add r3, r5, #0xc
    bl func_02045f3c
@L0215ae00:
    ldr r0, [sp, #0x18]
    str r8, [sp, #0x0]
    add r2, r0, #0xa
    mov r0, #0x6
    mla r1, r2, r0, r4
    mov r0, #0x8
    str r0, [sp, #0x4]
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    mov r0, #0x11
    str r0, [sp, #0x14]
    ldr r0, [sp, #0x1c]
    add r2, r6, #0x11
    add r3, r5, #0xc
    bl func_02045f3c
    ldr r0, =0x4000444
    mov r1, #0x0
    str r1, [r0, #0xc0]
    mov r1, #0x1
    str r1, [r0, #0x4]
@L0215ae58:
    add r7, r7, #0x1
@L0215ae5c:
    cmp r7, #0x18
    blt @L0215acf0
    add sp, sp, #0x24
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void EquipmentMenu::WriteNames()
{
    // A table that nothing uses, which the original has here
    static const signed char sUnusedParts[8] = {0, 6, 5, 7, 8, 1, 4, 4};
    sUnusedParts;
    // The equipment's parts in the order of the kinds of the menu
    static const unsigned char sNameParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};
    MessageSystem* messages = func_020421a0();
    GameState* gameState = GameState::GetInstance();
    PartyMember* member =
        func_0200ff1c(gameState, func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_);
    if (member == NULL)
        return;
    short* equipment = func_02052e14(member);
    for (int i = 0; i < 8; i++)
    {
        func_020462d0(messages, names_[i], 0x40);
        for (int j = 0; j < 0x40; j++)
            names_[i][j] = 0xffff;
        longNames_[i] = 0;
    }
    for (int i = 0; i < 8; i++)
    {
        short item = equipment[sNameParts[i]];
        PartEntry* entry = func_020dedd0(items_, item);
        char text[0x80];
        __clear(text, sizeof(text));
        if (entry != NULL)
        {
            char name[0x80];
            __clear(name, sizeof(name));
            func_0206819c(entry->unk_4, name, 0);
            func_02046608(messages, 0, name, text, 0x58, 0, 0);
        }
        else if (item <= 0)
        {
            func_02046608(messages, 0, func_020e0434(&texts_, 0x2ee0), text, 0x58, 0, 0);
        }
        else
        {
            func_02046608(messages, 0, func_020e0434(&texts_, 0x32c7), text, 0x58, 0, 0);
        }
        if (func_020d2f88(text, STRING(0x54, "\n")))
            longNames_[i] = 1;
        func_02045d14(messages, text, names_[i], 0);
        func_020439b0(messages, 0);
        unk_3e04 = 2;
    }
}

static const unsigned char sNameParts2[8] = {7, 8, 6, 0, 4, 1, 5, 9};

// NONMATCHING: the C matches 84.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::DrawNames()
{
    MessageSystem* messages = func_020421a0();
    GameState* gameState = GameState::GetInstance();
    PartyMember* member =
        func_0200ff1c(gameState, func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_);
    if (member == NULL)
        return;
    short* equipment = func_02052e14(member);
    int y = 0x1c;
    if (state_ == 0)
    {
        for (int i = 0; i < 8; i++)
        {
            int color;
            if (func_020dedd0(items_, equipment[sNameParts2[i]]) != NULL)
                color = 0x7fff;
            else
                color = 0x3def;
            int nameY = i * 0x18;
            if (i == kind_)
                color = 0xf0a;
            if (longNames_[i] != 0)
                nameY -= 5;
            GXFIFO_MATRIX_PUSH = 0;
            GXFIFO_BEGIN_VTXS = 1;
            GXFIFO_MATRIX_TRANSLATE = 0;
            GXFIFO_MATRIX_TRANSLATE = 0;
            GXFIFO_MATRIX_TRANSLATE = -0x3ff000;
            func_02045f3c(messages, names_[i], 0xa0, nameY + 6, color, 10, 0, 0, 0, 9);
            GXFIFO_END_VTXS = 0;
            GXFIFO_MATRIX_POP = 1;
        }
        return;
    }
    int color;
    if (func_020dedd0(items_, equipment[sNameParts2[kind_]]) != NULL)
        color = 0x7fff;
    else
        color = 0x3def;
    if (state_ == 3)
        color = 0xf0a;
    if (longNames_[kind_] != 0)
        y -= 5;
    GXFIFO_MATRIX_PUSH = 0;
    GXFIFO_BEGIN_VTXS = 1;
    GXFIFO_MATRIX_TRANSLATE = 0;
    GXFIFO_MATRIX_TRANSLATE = 0;
    GXFIFO_MATRIX_TRANSLATE = -0x3ff000;
    func_02045f3c(messages, names_[kind_], 0xa0, y, color, 10, 0, 0, 0, 9);
    GXFIFO_END_VTXS = 0;
    GXFIFO_MATRIX_POP = 1;
}
#else
asm void EquipmentMenu::DrawNames()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x18
    mov r10, r0
    bl func_020421a0
    mov r7, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r4
    bl func_0200ff1c
    cmp r0, #0x0
    beq @L0215b298
    bl func_02052e14
    add r4, r10, #0x3000
    ldrb r1, [r4, #0xdb8]
    mov r8, r0
    mov r5, #0x1c
    cmp r1, #0x0
    bne @L0215b1cc
    mov r9, #0x0
    add r0, r10, #0x284
    add r5, r0, #0x3c00
    mov r11, r9
    ldr r6, =0x4000444
    b @L0215b1c0
@L0215b114:
    ldr r1, =sNameParts2
    ldr r0, [r10, #0xdf4]
    ldrb r1, [r1, r9]
    mov r1, r1, lsl #0x1
    ldrsh r1, [r8, r1]
    bl func_020dedd0
    cmp r0, #0x0
    ldrne r0, =0x7fff
    ldrb r1, [r4, #0xdbc]
    ldreq r0, =0x3def
    cmp r9, r1
    mov r1, #0x18
    mul r2, r9, r1
    add r1, r10, r9
    add r1, r1, #0x4000
    ldrb r1, [r1, #0x284]
    ldreq r0, =0xf0a
    cmp r1, #0x0
    subne r2, r2, #0x5
    add r3, r2, #0x6
    str r11, [r6, #0x0]
    mov r1, #0x1
    str r1, [r6, #0xbc]
    str r11, [r6, #0x2c]
    ldr r1, =0xffc01000
    str r11, [r6, #0x2c]
    str r1, [r6, #0x2c]
    str r0, [sp, #0x0]
    mov r0, #0xa
    stmib sp, {r0, r11}
    str r11, [sp, #0xc]
    str r11, [sp, #0x10]
    mov r0, #0x9
    str r0, [sp, #0x14]
    mov r0, r7
    add r1, r5, r9, lsl #0x7
    mov r2, #0xa0
    bl func_02045f3c
    mov r0, #0x0
    str r0, [r6, #0xc0]
    mov r0, #0x1
    str r0, [r6, #0x4]
    add r9, r9, #0x1
@L0215b1c0:
    cmp r9, #0x8
    blt @L0215b114
    b @L0215b298
@L0215b1cc:
    ldrb r2, [r4, #0xdbc]
    ldr r1, =sNameParts2
    ldr r0, [r10, #0xdf4]
    ldrb r1, [r1, r2]
    mov r1, r1, lsl #0x1
    ldrsh r1, [r8, r1]
    bl func_020dedd0
    add r1, r10, #0x3000
    cmp r0, #0x0
    ldrne r0, =0x7fff
    ldrb r1, [r1, #0xdb8]
    ldreq r0, =0x3def
    ldr r2, =0x4000444
    cmp r1, #0x3
    add r1, r10, #0x3000
    ldrb r1, [r1, #0xdbc]
    mov r3, #0x0
    ldreq r0, =0xf0a
    add r1, r10, r1
    add r1, r1, #0x4000
    ldrb r1, [r1, #0x284]
    cmp r1, #0x0
    str r3, [r2, #0x0]
    mov r1, #0x1
    str r1, [r2, #0xbc]
    str r3, [r2, #0x2c]
    ldr r1, =0xffc01000
    str r3, [r2, #0x2c]
    str r1, [r2, #0x2c]
    str r0, [sp, #0x0]
    mov r0, #0xa
    stmib sp, {r0, r3}
    str r3, [sp, #0xc]
    add r0, r10, #0x284
    add r2, r0, #0x3c00
    str r3, [sp, #0x10]
    mov r1, #0x9
    str r1, [sp, #0x14]
    add r1, r10, #0x3000
    ldrb r1, [r1, #0xdbc]
    subne r5, r5, #0x5
    mov r0, r7
    add r1, r2, r1, lsl #0x7
    mov r3, r5
    mov r2, #0xa0
    bl func_02045f3c
    ldr r1, =0x4000504
    mov r0, #0x0
    str r0, [r1, #0x0]
    mov r0, #0x1
    str r0, [r1, #-0xbc]
@L0215b298:
    add sp, sp, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 92.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::State_Start()
{
    if (step_ == 0)
    {
        if (!IsBrightnessTransitionActive(func_ov017_0218b5b0()))
            step_++;
    }
    else if (step_ == 1)
    {
        int touched = 0;
        int changed = 0;
        unsigned char kind = 0xff;
        int touching = 0;
        if (data_02114e54.touching_)
        {
            touching = 1;
            int x;
            int y;
            func_02012a84(&data_02114e54, &x, &y);
            kind = GetTouchedPart(x, y);
            if (kind != 0xff)
            {
                touched = 1;
                changed = 1;
            }
            else if (x > 0x80)
            {
                for (int i = 0; i < 8; i++)
                {
                    int top = i * 0x18;
                    if (y > top && y < top + 0x18)
                    {
                        touched = 1;
                        changed = 1;
                        kind = i;
                        break;
                    }
                }
            }
        }
        if (!touching)
        {
            touched = 1;
            int ticks = GameState::GetInstance()->GetTickCount();
            if (ticks == 0)
                ticks = 1;
            func_0205bf58(&cursor_, ticks);
            kind = func_0205bb84(&cursor_);
            if (IsConfirmed())
                changed = 1;
        }
        if (touched && kind_ != kind)
        {
            unk_3dbe = kind_;
            lastPage_ = page_;
            pages_[kind_] = page_;
            kind_ = kind;
            page_ = pages_[kind];
        }
        slot_ = kind_;
        SetMember(func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_, 0);
        if (changed)
        {
            func_0205eaa0(data_02108760, 1, 0);
            LoadPage();
            flags_ |= EQUIPMENT_LOAD_PAGE;
            pageStep_ = 0;
            SetState(1);
            for (int i = 0; i < 8; i++)
            {
                EquipmentSlot* slot = &slots_[i];
                if (i == dragged_ || slot->item_ < 0)
                    continue;
                MenuModel* model = slot->model_;
                Vector3fix position = model->position_;
                position.y = 0x17000;
                model->SetPosition(&position);
            }
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13EquipmentMenu11IsConfirmedEv(); // EquipmentMenu::IsConfirmed
    void _ZN13EquipmentMenu14GetTouchedPartEii(); // EquipmentMenu::GetTouchedPart
    void _ZN13EquipmentMenu8LoadPageEv(); // EquipmentMenu::LoadPage
    void _ZN13EquipmentMenu8SetStateEh(); // EquipmentMenu::SetState
    void _ZN13EquipmentMenu9SetMemberEii(); // EquipmentMenu::SetMember
    void _ZN9MenuModel11SetPositionEPK8Vector3i(); // MenuModel::SetPosition
}

asm void EquipmentMenu::State_Start()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x14
    mov r8, r0
    add r0, r8, #0x3000
    ldrb r0, [r0, #0xdba]
    cmp r0, #0x0
    bne @L0215b2f8
    bl func_ov017_0218b5b0
    bl IsBrightnessTransitionActive
    cmp r0, #0x0
    addeq r0, r8, #0x3000
    ldreqb r1, [r0, #0xdba]
    addeq r1, r1, #0x1
    streqb r1, [r0, #0xdba]
    b @L0215b510
@L0215b2f8:
    cmp r0, #0x1
    bne @L0215b510
    ldr r0, =data_02114e54
    mov r4, #0x0
    ldrb r1, [r0, #0x55]
    mov r5, r4
    mov r7, r4
    cmp r1, #0x0
    mov r6, #0xff
    beq @L0215b3a0
    add r1, sp, #0x4
    add r2, sp, #0x0
    mov r7, #0x1
    bl func_02012a84
    ldr r1, [sp, #0x4]
    ldr r2, [sp, #0x0]
    mov r0, r8
    bl _ZN13EquipmentMenu14GetTouchedPartEii
    mov r6, r0
    cmp r6, #0xff
    movne r4, r7
    movne r5, r4
    bne @L0215b3a0
    ldr r0, [sp, #0x4]
    cmp r0, #0x80
    ble @L0215b3a0
    mov r3, r4
    ldr r1, [sp, #0x0]
    mov r0, #0x18
    b @L0215b398
@L0215b370:
    mul r2, r3, r0
    cmp r1, r2
    add r2, r2, #0x18
    ble @L0215b394
    cmp r1, r2
    movlt r4, #0x1
    movlt r5, r4
    andlt r6, r3, #0xff
    blt @L0215b3a0
@L0215b394:
    add r3, r3, #0x1
@L0215b398:
    cmp r3, #0x8
    blt @L0215b370
@L0215b3a0:
    cmp r7, #0x0
    bne @L0215b3e8
    mov r4, #0x1
    bl _ZN9GameState11GetInstanceEv
    bl _ZNK9GameState12GetTickCountEv
    movs r1, r0
    add r0, r8, #0x1f4
    moveq r1, r4
    add r0, r0, #0x1800
    bl func_0205bf58
    add r0, r8, #0x1f4
    add r0, r0, #0x1800
    bl func_0205bb84
    and r6, r0, #0xff
    mov r0, r8
    bl _ZN13EquipmentMenu11IsConfirmedEv
    cmp r0, #0x0
    movne r5, #0x1
@L0215b3e8:
    cmp r4, #0x0
    addne r2, r8, #0x3000
    ldrneb r0, [r2, #0xdbc]
    cmpne r0, r6
    beq @L0215b438
    strb r0, [r2, #0xdbe]
    add r0, r8, #0x3d00
    ldrsb r3, [r0, #0xbd]
    and r1, r6, #0xff
    add r1, r8, r1
    strb r3, [r2, #0xdbf]
    ldrb r3, [r2, #0xdbc]
    ldrsb r4, [r0, #0xbd]
    add r1, r1, #0x3000
    add r0, r8, r3
    add r0, r0, #0x3000
    strb r4, [r0, #0xdfc]
    strb r6, [r2, #0xdbc]
    ldrb r0, [r1, #0xdfc]
    strb r0, [r2, #0xdbd]
@L0215b438:
    add r0, r8, #0x3000
    ldrb r1, [r0, #0xdbc]
    strb r1, [r0, #0xdbb]
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r8
    mov r2, #0x0
    bl _ZN13EquipmentMenu9SetMemberEii
    cmp r5, #0x0
    beq @L0215b510
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    mov r0, r8
    bl _ZN13EquipmentMenu8LoadPageEv
    add r2, r8, #0x3000
    ldr r1, [r2, #0xdcc]
    mov r0, r8
    orr r1, r1, #0x40
    str r1, [r2, #0xdcc]
    mov r3, #0x0
    mov r1, #0x1
    strb r3, [r2, #0xdaa]
    bl _ZN13EquipmentMenu8SetStateEh
    add r0, r8, #0xd90
    add r7, r8, #0x3d00
    mov r5, #0x0
    add r4, r0, #0x2000
    add r9, sp, #0x8
    mov r8, #0x17000
    mov r6, #0x1c
    b @L0215b508
@L0215b4c8:
    ldrsh r0, [r7, #0x78]
    mla r1, r5, r6, r4
    cmp r5, r0
    beq @L0215b504
    ldrsh r0, [r1, #0x0]
    cmp r0, #0x0
    blt @L0215b504
    ldr r3, [r1, #0x8]
    add r0, r3, #0x1c
    ldmia r0, {r0, r1, r2}
    stmia r9, {r0, r1, r2}
    mov r0, r3
    mov r1, r9
    str r8, [sp, #0xc]
    bl _ZN9MenuModel11SetPositionEPK8Vector3i
@L0215b504:
    add r5, r5, #0x1
@L0215b508:
    cmp r5, #0x8
    blt @L0215b4c8
@L0215b510:
    add sp, sp, #0x14
    ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
}
#endif

static const unsigned char sOpenParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};
static const unsigned char sCloseParts[8] = {7, 8, 6, 0, 4, 1, 5, 9};

// NONMATCHING: the C matches 91.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::State_Open()
{
    unsigned char step = step_;
    if (step == 0 && animationPhase_ == 0)
    {
        SetState(1);
        flags_ |= EQUIPMENT_KIND_CHANGED;
        GameState* gameState = GameState::GetInstance();
        PartyMember* member =
            func_0200ff1c(gameState, func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_);
        short* equipment = func_02052e14(member);
        animationTime_ += ticks_;
        if (animationTime_ >= 3)
        {
            animationTime_ -= 3;
            animationX_ += 0x29;
            if (animationX_ >= 0x7b)
            {
                animationX_ = 0x7b;
                animationPhase_ = 1;
            }
        }
        if (state_ == 1)
        {
            for (int i = 0; i < 8; i++)
            {
                int selected = 0;
                if (i == kind_)
                    selected = 1;
                int base = selected * 11;
                int y = (i * 0x18) << 12;
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (animationX_ + 0x7f) << 12;
                MenuModel* models = models_;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x200000;
                func_02047554(&models[base + 4], 0, 1);
                GXFIFO_MATRIX_POP = 1;
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (animationX_ + 0x100) << 12;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x200000;
                Matrix4x3 matrix;
                matrix = RotationMatrixY(0x3244);
                func_020c51a4(&matrix);
                func_02047554(&models[base + 4], 0, 1);
                GXFIFO_MATRIX_POP = 1;
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (animationX_ + 0x70) << 12;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x200000;
                GXFIFO_MATRIX_SCALE = 0x14000;
                GXFIFO_MATRIX_SCALE = 0x1000;
                GXFIFO_MATRIX_SCALE = 0x1000;
                func_02047554(&models_[base + 5], 0, 1);
                GXFIFO_MATRIX_POP = 1;
                MenuModel* icon = &models_[base + 7 + i];
                if (equipment[sOpenParts[i]] > 0)
                    icon = &models_[base + 6];
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (animationX_ + 0x85) << 12;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x1ff000;
                func_02047554(icon, 0, 1);
                GXFIFO_MATRIX_POP = 1;
            }
        }
        if (animationPhase_ == 1)
        {
            step_++;
            animationX_ = 0;
            animationTime_ = 0;
            animationPhase_ = 0;
        }
    }
    else if (step == 1 && animationPhase_ == 0)
    {
        flags_ |= EQUIPMENT_KIND_CHANGED;
        animationTime_ += ticks_;
        if (animationTime_ >= 3)
        {
            animationTime_ -= 3;
            animationX_ += 6;
            if (animationX_ >= 0x10)
            {
                animationX_ = 0x10;
                animationPhase_ = 1;
            }
        }
        func_0204b010(&backgrounds_[1], 0);
        func_0204b8d0(&backgrounds_[1], 0, 0, 0, (short)(0x20 - animationX_), 0, 0x10, 0x16, 0xffff);
        func_0204b8d0(&backgrounds_[1], kind_ + 1, 0, 0, (short)((short)(kind_ * 2 + 0xf) + 0x10 - animationX_), 0, 4,
                      3, 0xffff);
        func_0204b04c(&backgrounds_[1], 0);
        if (animationPhase_ == 1)
        {
            step_++;
            animationX_ = 0;
            animationTime_ = 0;
        }
    }
    else if (step == 2 && animationPhase_ == 1)
    {
        SetState(3);
        flags_ |= EQUIPMENT_KIND_CHANGED;
        MoveFrame(state_, slot_);
        frame_.SetPosition(0x85000, 0x17000);
        frame_.SetSize(0x76000, 0x16000);
        flags_ |= EQUIPMENT_SORT_ICON;
    }
    else if (step == 0 && animationPhase_ == 1)
    {
        flags_ |= EQUIPMENT_SORT_ICON;
        SetState(1);
        flags_ |= EQUIPMENT_KIND_CHANGED;
        animationTime_ += ticks_;
        if (animationTime_ >= 3)
        {
            animationTime_ -= 3;
            animationX_ += 6;
            if (animationX_ >= 0x10)
            {
                animationX_ = 0x10;
                animationPhase_ = 2;
            }
        }
        func_0204b010(&backgrounds_[1], 0);
        func_0204b8d0(&backgrounds_[1], 0, 0, 0, (short)(animationX_ + 0x10), 0, 0x10, 0x16, 0xffff);
        func_0204b8d0(&backgrounds_[1], kind_ + 1, 0, 0, animationX_ + (short)(kind_ * 2 + 0xf), 0, 4, 3, 0xffff);
        func_0204b04c(&backgrounds_[1], 0);
        if (animationPhase_ == 2)
        {
            step_++;
            animationX_ = 0;
            animationTime_ = 0;
        }
    }
    else if (step == 1 && animationPhase_ == 2)
    {
        GameState* gameState = GameState::GetInstance();
        PartyMember* member =
            func_0200ff1c(gameState, func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_);
        short* equipment = func_02052e14(member);
        animationTime_ += ticks_;
        if (animationTime_ >= 3)
        {
            animationTime_ -= 3;
            animationX_ += 0x29;
            if (animationX_ >= 0x7b)
            {
                animationX_ = 0x7b;
                animationPhase_ = 1;
            }
        }
        if (state_ == 1)
        {
            for (int i = 0; i < 8; i++)
            {
                int selected = 0;
                if (i == kind_)
                    selected = 1;
                int base = selected * 11;
                int y = (i * 0x18) << 12;
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (0xfa - animationX_) << 12;
                MenuModel* models = models_;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x200000;
                func_02047554(&models[base + 4], 0, 1);
                GXFIFO_MATRIX_POP = 1;
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (0x17b - animationX_) << 12;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x200000;
                Matrix4x3 matrix;
                matrix = RotationMatrixY(0x3244);
                func_020c51a4(&matrix);
                func_02047554(&models[base + 4], 0, 1);
                GXFIFO_MATRIX_POP = 1;
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (0xeb - animationX_) << 12;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x200000;
                GXFIFO_MATRIX_SCALE = 0x14000;
                GXFIFO_MATRIX_SCALE = 0x1000;
                GXFIFO_MATRIX_SCALE = 0x1000;
                func_02047554(&models_[base + 5], 0, 1);
                GXFIFO_MATRIX_POP = 1;
                MenuModel* icon = &models_[base + 7 + i];
                if (equipment[sCloseParts[i]] > 0)
                    icon = &models_[base + 6];
                GXFIFO_MATRIX_PUSH = 0;
                GXFIFO_MATRIX_TRANSLATE = (0x100 - animationX_) << 12;
                GXFIFO_MATRIX_TRANSLATE = y;
                GXFIFO_MATRIX_TRANSLATE = -0x1ff000;
                func_02047554(icon, 0, 1);
                GXFIFO_MATRIX_POP = 1;
            }
        }
        if (animationPhase_ == 1)
        {
            step_ = 0;
            animationX_ = 0;
            animationTime_ = 0;
            animationPhase_ = 0;
            SetState(0);
            flags_ |= EQUIPMENT_KIND_CHANGED;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11CursorFrame11SetPositionEii(); // CursorFrame::SetPosition
    void _ZN11CursorFrame7SetSizeEii(); // CursorFrame::SetSize
    void _ZN13EquipmentMenu8SetStateEh(); // EquipmentMenu::SetState
    void _ZN13EquipmentMenu9MoveFrameEjh(); // EquipmentMenu::MoveFrame
}

asm void EquipmentMenu::State_Open()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0xd8
    mov r9, r0
    add r1, r9, #0x3000
    ldrb r3, [r1, #0xdba]
    cmp r3, #0x0
    ldreq r1, [r1, #0xdec]
    cmpeq r1, #0x0
    bne @L0215b800
    mov r1, #0x1
    bl _ZN13EquipmentMenu8SetStateEh
    add r0, r9, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x100
    str r1, [r0, #0xdcc]
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r4
    bl func_0200ff1c
    bl func_02052e14
    add r2, r9, #0x3000
    ldr r4, [r2, #0xde8]
    ldr r3, [r2, #0xde4]
    str r0, [sp, #0x14]
    add r0, r4, r3
    add r1, r9, #0x1e8
    str r0, [r2, #0xde8]
    cmp r0, #0x3
    add r3, r1, #0x3c00
    blt @L0215b5e0
    ldr r1, [r3, #0x0]
    add r0, r9, #0x3d00
    sub r1, r1, #0x3
    str r1, [r3, #0x0]
    ldrsh r1, [r0, #0xe2]
    add r1, r1, #0x29
    strh r1, [r0, #0xe2]
    ldrsh r1, [r0, #0xe2]
    cmp r1, #0x7b
    movge r1, #0x7b
    strgeh r1, [r0, #0xe2]
    movge r0, #0x1
    strge r0, [r2, #0xdec]
@L0215b5e0:
    add r0, r9, #0x3000
    ldrb r0, [r0, #0xdb8]
    cmp r0, #0x1
    bne @L0215b7cc
    mov r6, #0x0
    b @L0215b7c4
@L0215b5f8:
    add r0, r9, #0x3000
    ldrb r0, [r0, #0xdbc]
    add r4, r9, #0xa70
    mov r1, #0x0
    cmp r6, r0
    moveq r1, #0x1
    mov r0, #0xb
    mul r7, r1, r0
    mov r0, #0x18
    ldr r3, =0x4000444
    mov r1, #0x0
    str r1, [r3, #0x0]
    add r2, r9, #0x3d00
    ldrsh r5, [r2, #0xe2]
    mul r0, r6, r0
    add r5, r5, #0x7f
    mov r10, r5, lsl #0xc
    str r10, [r3, #0x2c]
    add r8, r7, #0x4
    mov r2, #0x88
    mul r5, r8, r2
    mov r8, r0, lsl #0xc
    add r4, r4, #0x1000
    str r8, [r3, #0x2c]
    sub r10, r1, #0x200000
    add r0, r4, r5
    mov r2, #0x1
    str r10, [r3, #0x2c]
    bl func_02047554
    ldr r3, =0x4000448
    mov r0, #0x1
    str r0, [r3, #0x0]
    mov r2, #0x0
    str r2, [r3, #-0x4]
    add r0, r9, #0x3d00
    ldrsh r10, [r0, #0xe2]
    ldr r1, =0x3244
    add r0, sp, #0x48
    add r10, r10, #0x100
    mov r10, r10, lsl #0xc
    str r10, [r3, #0x28]
    str r8, [r3, #0x28]
    sub r2, r2, #0x200000
    str r2, [r3, #0x28]
    bl RotationMatrixY
    add r12, sp, #0x48
    add r11, sp, #0xa8
    mov r10, #0x3
@L0215b6b8:
    ldmia r12!, {r0, r1, r2, r3}
    stmia r11!, {r0, r1, r2, r3}
    subs r10, r10, #0x1
    bne @L0215b6b8
    add r0, sp, #0xa8
    bl func_020c51a4
    add r0, r4, r5
    mov r1, #0x0
    mov r2, #0x1
    bl func_02047554
    add r2, r9, #0xa70
    add r4, r2, #0x1000
    mov r1, #0x0
    ldr r0, =0x4000448
    mov r2, #0x1
    str r2, [r0, #0x0]
    str r1, [r0, #-0x4]
    add r3, r9, #0x3d00
    ldrsh r10, [r3, #0xe2]
    sub r5, r1, #0x200000
    mov r3, #0x14000
    add r10, r10, #0x70
    mov r10, r10, lsl #0xc
    str r10, [r0, #0x28]
    str r8, [r0, #0x28]
    str r5, [r0, #0x28]
    str r3, [r0, #0x24]
    mov r3, #0x1000
    str r3, [r0, #0x24]
    str r3, [r0, #0x24]
    add r3, r7, #0x5
    mov r0, #0x88
    mla r0, r3, r0, r4
    bl func_02047554
    add r0, r9, #0xa70
    ldr r2, =sOpenParts
    add r1, r0, #0x1000
    ldrb r0, [r2, r6]
    ldr r3, =0x4000448
    mov r4, #0x1
    mov r2, r0, lsl #0x1
    ldr r0, [sp, #0x14]
    str r4, [r3, #0x0]
    ldrsh r0, [r0, r2]
    add r2, r7, #0x7
    add r3, r2, r6
    mov r2, #0x88
    cmp r0, #0x0
    mla r0, r3, r2, r1
    addgt r3, r7, #0x6
    mlagt r0, r3, r2, r1
    ldr r5, =0x4000444
    mov r1, #0x0
    str r1, [r5, #0x0]
    add r2, r9, #0x3d00
    ldrsh r4, [r2, #0xe2]
    ldr r3, =0xffe01000
    mov r2, #0x1
    add r4, r4, #0x85
    mov r4, r4, lsl #0xc
    str r4, [r5, #0x2c]
    str r8, [r5, #0x2c]
    str r3, [r5, #0x2c]
    bl func_02047554
    mov r1, #0x1
    str r1, [r5, #0x4]
    add r6, r6, #0x1
@L0215b7c4:
    cmp r6, #0x8
    blt @L0215b5f8
@L0215b7cc:
    add r1, r9, #0x3000
    ldr r0, [r1, #0xdec]
    cmp r0, #0x1
    bne @L0215be3c
    ldrb r3, [r1, #0xdba]
    add r0, r9, #0x3d00
    mov r2, #0x0
    add r3, r3, #0x1
    strb r3, [r1, #0xdba]
    strh r2, [r0, #0xe2]
    str r2, [r1, #0xde8]
    str r2, [r1, #0xdec]
    b @L0215be3c
@L0215b800:
    cmp r3, #0x1
    addeq r1, r9, #0x3000
    ldreq r0, [r1, #0xdec]
    cmpeq r0, #0x0
    bne @L0215b974
    ldr r2, [r1, #0xdcc]
    add r0, r9, #0x1e8
    orr r2, r2, #0x100
    str r2, [r1, #0xdcc]
    ldr r3, [r1, #0xde8]
    ldr r2, [r1, #0xde4]
    add r4, r0, #0x3c00
    add r0, r3, r2
    str r0, [r1, #0xde8]
    cmp r0, #0x3
    blt @L0215b874
    ldr r2, [r4, #0x0]
    add r0, r9, #0x3d00
    sub r2, r2, #0x3
    str r2, [r4, #0x0]
    ldrsh r2, [r0, #0xe2]
    add r2, r2, #0x6
    strh r2, [r0, #0xe2]
    ldrsh r2, [r0, #0xe2]
    cmp r2, #0x10
    movge r2, #0x10
    strgeh r2, [r0, #0xe2]
    movge r0, #0x1
    strge r0, [r1, #0xdec]
@L0215b874:
    add r0, r9, #0x2a4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b010
    add r0, r9, #0x3d00
    ldrsh r0, [r0, #0xe2]
    mov r1, #0x0
    add r4, r9, #0x2a4
    rsb r0, r0, #0x20
    mov r0, r0, lsl #0x10
    mov r0, r0, asr #0x10
    stmia sp, {r0, r1}
    mov r0, #0x10
    str r0, [sp, #0x8]
    mov r0, #0x16
    str r0, [sp, #0xc]
    ldr r5, =0xffff
    mov r2, r1
    mov r3, r1
    add r0, r4, #0xc00
    str r5, [sp, #0x10]
    bl func_0204b8d0
    add r0, r9, #0x3000
    ldrb r4, [r0, #0xdbc]
    add r1, r9, #0x3d00
    ldrsh r1, [r1, #0xe2]
    mov r0, r4, lsl #0x1
    add r0, r0, #0xf
    mov r0, r0, lsl #0x10
    mov r3, r0, asr #0x10
    add r3, r3, #0x10
    sub r1, r3, r1
    mov r1, r1, lsl #0x10
    add r0, r9, #0x2a4
    mov r2, #0x0
    mov r1, r1, asr #0x10
    stmia sp, {r1, r2}
    mov r1, #0x4
    str r1, [sp, #0x8]
    mov r3, #0x3
    str r3, [sp, #0xc]
    mov r1, r5
    add r4, r4, #0x1
    str r1, [sp, #0x10]
    add r0, r0, #0xc00
    mov r3, r2
    and r1, r4, #0xff
    bl func_0204b8d0
    add r0, r9, #0x2a4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b04c
    add r1, r9, #0x3000
    ldr r0, [r1, #0xdec]
    cmp r0, #0x1
    bne @L0215be3c
    ldrb r3, [r1, #0xdba]
    add r0, r9, #0x3d00
    mov r2, #0x0
    add r3, r3, #0x1
    strb r3, [r1, #0xdba]
    strh r2, [r0, #0xe2]
    str r2, [r1, #0xde8]
    b @L0215be3c
@L0215b974:
    cmp r3, #0x2
    addeq r0, r9, #0x3000
    ldreq r0, [r0, #0xdec]
    cmpeq r0, #0x1
    bne @L0215b9f0
    mov r0, r9
    mov r1, #0x3
    bl _ZN13EquipmentMenu8SetStateEh
    add r2, r9, #0x3000
    ldr r1, [r2, #0xdcc]
    mov r0, r9
    orr r1, r1, #0x100
    str r1, [r2, #0xdcc]
    ldrb r1, [r2, #0xdb8]
    ldrb r2, [r2, #0xdbb]
    bl _ZN13EquipmentMenu9MoveFrameEjh
    add r0, r9, #0x234
    add r0, r0, #0x1800
    mov r1, #0x85000
    mov r2, #0x17000
    bl _ZN11CursorFrame11SetPositionEii
    add r0, r9, #0x234
    add r0, r0, #0x1800
    mov r1, #0x76000
    mov r2, #0x16000
    bl _ZN11CursorFrame7SetSizeEii
    add r0, r9, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x800
    str r1, [r0, #0xdcc]
    b @L0215be3c
@L0215b9f0:
    cmp r3, #0x0
    addeq r2, r9, #0x3000
    ldreq r0, [r2, #0xdec]
    cmpeq r0, #0x1
    bne @L0215bb78
    ldr r1, [r2, #0xdcc]
    mov r0, r9
    orr r3, r1, #0x800
    mov r1, #0x1
    str r3, [r2, #0xdcc]
    bl _ZN13EquipmentMenu8SetStateEh
    add r1, r9, #0x3000
    ldr r2, [r1, #0xdcc]
    add r0, r9, #0x1e8
    orr r2, r2, #0x100
    str r2, [r1, #0xdcc]
    ldr r3, [r1, #0xde8]
    ldr r2, [r1, #0xde4]
    add r4, r0, #0x3c00
    add r0, r3, r2
    str r0, [r1, #0xde8]
    cmp r0, #0x3
    blt @L0215ba80
    ldr r2, [r4, #0x0]
    add r0, r9, #0x3d00
    sub r2, r2, #0x3
    str r2, [r4, #0x0]
    ldrsh r2, [r0, #0xe2]
    add r2, r2, #0x6
    strh r2, [r0, #0xe2]
    ldrsh r2, [r0, #0xe2]
    cmp r2, #0x10
    movge r2, #0x10
    strgeh r2, [r0, #0xe2]
    movge r0, #0x2
    strge r0, [r1, #0xdec]
@L0215ba80:
    add r0, r9, #0x2a4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b010
    add r0, r9, #0x3d00
    ldrsh r0, [r0, #0xe2]
    mov r1, #0x0
    add r4, r9, #0x2a4
    add r0, r0, #0x10
    mov r0, r0, lsl #0x10
    mov r0, r0, asr #0x10
    stmia sp, {r0, r1}
    mov r0, #0x10
    str r0, [sp, #0x8]
    mov r0, #0x16
    str r0, [sp, #0xc]
    ldr r5, =0xffff
    mov r2, r1
    mov r3, r1
    add r0, r4, #0xc00
    str r5, [sp, #0x10]
    bl func_0204b8d0
    add r0, r9, #0x3000
    ldrb r4, [r0, #0xdbc]
    add r0, r9, #0x3d00
    ldrsh r5, [r0, #0xe2]
    mov r1, r4, lsl #0x1
    add r1, r1, #0xf
    mov r1, r1, lsl #0x10
    add r1, r5, r1, asr #0x10
    mov r1, r1, lsl #0x10
    add r3, r9, #0x2a4
    add r0, r3, #0xc00
    mov r2, #0x0
    mov r1, r1, asr #0x10
    stmia sp, {r1, r2}
    mov r1, #0x4
    str r1, [sp, #0x8]
    mov r3, #0x3
    str r3, [sp, #0xc]
    ldr r1, =0xffff
    add r4, r4, #0x1
    str r1, [sp, #0x10]
    mov r3, r2
    and r1, r4, #0xff
    bl func_0204b8d0
    add r0, r9, #0x2a4
    add r0, r0, #0xc00
    mov r1, #0x0
    bl func_0204b04c
    add r1, r9, #0x3000
    ldr r0, [r1, #0xdec]
    cmp r0, #0x2
    bne @L0215be3c
    ldrb r3, [r1, #0xdba]
    add r0, r9, #0x3d00
    mov r2, #0x0
    add r3, r3, #0x1
    strb r3, [r1, #0xdba]
    strh r2, [r0, #0xe2]
    str r2, [r1, #0xde8]
    b @L0215be3c
@L0215bb78:
    cmp r3, #0x1
    addeq r0, r9, #0x3000
    ldreq r0, [r0, #0xdec]
    cmpeq r0, #0x2
    bne @L0215be3c
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    mov r0, r4
    bl func_0200ff1c
    bl func_02052e14
    add r2, r9, #0x3000
    ldr r4, [r2, #0xde8]
    ldr r3, [r2, #0xde4]
    mov r11, r0
    add r0, r4, r3
    add r1, r9, #0x1e8
    str r0, [r2, #0xde8]
    cmp r0, #0x3
    add r3, r1, #0x3c00
    blt @L0215bc10
    ldr r1, [r3, #0x0]
    add r0, r9, #0x3d00
    sub r1, r1, #0x3
    str r1, [r3, #0x0]
    ldrsh r1, [r0, #0xe2]
    add r1, r1, #0x29
    strh r1, [r0, #0xe2]
    ldrsh r1, [r0, #0xe2]
    cmp r1, #0x7b
    movge r1, #0x7b
    strgeh r1, [r0, #0xe2]
    movge r0, #0x1
    strge r0, [r2, #0xdec]
@L0215bc10:
    add r0, r9, #0x3000
    ldrb r0, [r0, #0xdb8]
    cmp r0, #0x1
    bne @L0215bdfc
    mov r6, #0x0
    b @L0215bdf4
@L0215bc28:
    add r0, r9, #0x3000
    ldrb r0, [r0, #0xdbc]
    add r4, r9, #0xa70
    mov r1, #0x0
    cmp r6, r0
    moveq r1, #0x1
    mov r0, #0xb
    mul r7, r1, r0
    mov r0, #0x18
    ldr r3, =0x4000444
    mov r1, #0x0
    str r1, [r3, #0x0]
    add r2, r9, #0x3d00
    ldrsh r5, [r2, #0xe2]
    mul r0, r6, r0
    rsb r5, r5, #0xfa
    mov r10, r5, lsl #0xc
    str r10, [r3, #0x2c]
    add r8, r7, #0x4
    mov r2, #0x88
    mul r5, r8, r2
    mov r8, r0, lsl #0xc
    add r4, r4, #0x1000
    str r8, [r3, #0x2c]
    sub r10, r1, #0x200000
    add r0, r4, r5
    mov r2, #0x1
    str r10, [r3, #0x2c]
    bl func_02047554
    ldr r3, =0x4000448
    mov r1, #0x1
    str r1, [r3, #0x0]
    mov r2, #0x0
    str r2, [r3, #-0x4]
    add r0, r9, #0x3d00
    ldrsh r10, [r0, #0xe2]
    rsb r1, r1, #0x17c
    add r0, sp, #0x18
    sub r1, r1, r10
    mov r1, r1, lsl #0xc
    str r1, [r3, #0x28]
    ldr r1, =0x3244
    str r8, [r3, #0x28]
    sub r2, r2, #0x200000
    str r2, [r3, #0x28]
    bl RotationMatrixY
    add r10, sp, #0x18
    add lr, sp, #0x78
    mov r12, #0x3
@L0215bcec:
    ldmia r10!, {r0, r1, r2, r3}
    stmia lr!, {r0, r1, r2, r3}
    subs r12, r12, #0x1
    bne @L0215bcec
    add r0, sp, #0x78
    bl func_020c51a4
    add r0, r4, r5
    mov r1, #0x0
    mov r2, #0x1
    bl func_02047554
    add r2, r9, #0xa70
    add r4, r2, #0x1000
    mov r1, #0x0
    ldr r0, =0x4000448
    mov r2, #0x1
    str r2, [r0, #0x0]
    str r1, [r0, #-0x4]
    add r3, r9, #0x3d00
    ldrsh r10, [r3, #0xe2]
    sub r5, r1, #0x200000
    mov r3, #0x14000
    rsb r10, r10, #0xeb
    mov r10, r10, lsl #0xc
    str r10, [r0, #0x28]
    str r8, [r0, #0x28]
    str r5, [r0, #0x28]
    str r3, [r0, #0x24]
    mov r3, #0x1000
    str r3, [r0, #0x24]
    str r3, [r0, #0x24]
    add r3, r7, #0x5
    mov r0, #0x88
    mla r0, r3, r0, r4
    bl func_02047554
    add r0, r9, #0xa70
    ldr r2, =sCloseParts
    add r1, r0, #0x1000
    ldrb r0, [r2, r6]
    ldr r2, =0x4000448
    mov r3, #0x1
    str r3, [r2, #0x0]
    mov r0, r0, lsl #0x1
    ldrsh r0, [r11, r0]
    add r2, r7, #0x7
    add r3, r2, r6
    mov r2, #0x88
    cmp r0, #0x0
    mla r0, r3, r2, r1
    addgt r3, r7, #0x6
    mlagt r0, r3, r2, r1
    ldr r5, =0x4000444
    mov r1, #0x0
    str r1, [r5, #0x0]
    add r2, r9, #0x3d00
    ldrsh r4, [r2, #0xe2]
    ldr r3, =0xffe01000
    mov r2, #0x1
    rsb r4, r4, #0x100
    mov r4, r4, lsl #0xc
    str r4, [r5, #0x2c]
    str r8, [r5, #0x2c]
    str r3, [r5, #0x2c]
    bl func_02047554
    mov r1, #0x1
    str r1, [r5, #0x4]
    add r6, r6, #0x1
@L0215bdf4:
    cmp r6, #0x8
    blt @L0215bc28
@L0215bdfc:
    add r2, r9, #0x3000
    ldr r0, [r2, #0xdec]
    cmp r0, #0x1
    bne @L0215be3c
    mov r1, #0x0
    strb r1, [r2, #0xdba]
    add r0, r9, #0x3d00
    strh r1, [r0, #0xe2]
    str r1, [r2, #0xde8]
    mov r0, r9
    str r1, [r2, #0xdec]
    bl _ZN13EquipmentMenu8SetStateEh
    add r0, r9, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x100
    str r1, [r0, #0xdcc]
@L0215be3c:
    add sp, sp, #0xd8
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void EquipmentMenu::State_Kinds()
{
    infoWindow_.SetItem(-1);
    int touched = 0;
    if (data_02114e54.touching_ || (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0) ||
        data_02114e54.unk_54 != 0)
    {
        UpdateTouch();
        touched = 1;
    }
    if (touched)
        return;
    UpdateKeys();
}

void EquipmentMenu::State_Equipped()
{
    int touched = 0;
    if (data_02114e54.touching_ || (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0) ||
        data_02114e54.unk_54 != 0)
    {
        UpdateTouch();
        touched = 1;
    }
    if (!touched)
        UpdateKeys();
    SetMember(func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_, 0);
}

void EquipmentMenu::State_Page()
{
    int touched = 0;
    if (data_02114e54.touching_ || (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0) ||
        data_02114e54.unk_54 != 0)
    {
        UpdateTouch();
        touched = 1;
    }
    if (!touched)
        UpdateKeys();
    int member = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_;
    PartEntry* entry = func_020dedd0(items_, slots_[slot_].item_);
    if (entry != NULL)
    {
        if (func_020dd4c4(member, entry))
            infoWindow_.flags_ |= 0x100;
        else
            infoWindow_.flags_ &= ~0x100;
    }
    SetMember(member, 0);
}

void EquipmentMenu::State_Menu()
{
    int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    UpdateMenu(ticks);
}

static unsigned char sMoveLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};

// NONMATCHING: the C matches 91.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::State_Move()
{
    GameState* gameState;
    short item;
    if (step_ == 0)
    {
        swapped_ = (slot_ - 8) + page_ * 16;
        frame_.corners_ = (char*)&models_[30];
        step_++;
    }
    else if (step_ == 1)
    {
        MemberScreen* screen = func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708);
        SetMember(screen->member_, 0);
        GameState* gameState = GameState::GetInstance();
        int touching = 0;
        int touched = 0;
        if (data_02114e54.touching_)
        {
            touching = 1;
            int x;
            int y;
            func_02012a84(&data_02114e54, &x, &y);
            flags_ = (flags_ & ~EQUIPMENT_KINDS) | EQUIPMENT_ARROWS;
            TouchTop(x, y);
            int slot = GetTouchedSlot(x, y);
            if (slot >= 8 && slot < 24)
            {
                slot_ = slot;
                touched = 1;
                func_0205bb04(&cursor_, slot_ - 8);
                MoveFrame(state_, slot_);
            }
        }
        else if (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0)
        {
            touching = 1;
        }
        else if (data_02114e54.unk_54 != 0)
        {
            touching = 1;
        }
        if (!touching)
        {
            int ticks = gameState->GetTickCount();
            if (ticks == 0)
                ticks = 1;
            func_0205bf58(&cursor_, ticks);
            int changed = 0;
            int column = (slot_ - 8) % 4;
            if (column == 0)
            {
                if (func_02012444(data_02114e30, 0x20))
                    changed = TurnPage(-1);
            }
            else if (column == 3 && func_02012444(data_02114e30, 0x10))
            {
                changed = TurnPage(1);
            }
            if (changed)
                LoadPage();
        }
        signed char page = page_;
        short swapped = swapped_;
        if (swapped >= (short)(page * 16) && swapped < (short)((short)(page * 16) + 16))
        {
            CursorFrame frame;
            frame.Initialize();
            frame.corners_ = (char*)&models_[26];
            frame.size_ = 0x8000;
            frame.left_ = -0x3000;
            frame.right_ = 0x3000;
            frame.bottom_ = 0x3000;
            frame.top_ = -0x3000;
            int x;
            int y;
            GetSlotPosition(swapped_ % 16 + 8, &x, &y);
            int frameX = x << 12;
            int frameY = y << 12;
            frame.SetTargetPosition(frameX, frameY);
            frame.SetPosition(frameX, frameY);
            frame.SetTargetSize(0x18000, 0x18000);
            frame.SetSize(0x18000, 0x18000);
            frame.z_ = 0x4800;
            frame.Draw(0, 0x7fff);
        }
        int cursor = func_0205bb84(&cursor_) + 8;
        signed char slot = slot_;
        if (cursor != slot)
        {
            slot_ = cursor;
            func_0205eaa0(data_02108760, 2, 0);
            MoveFrame(state_, slot_);
            return;
        }
        if (IsConfirmed() || touched)
        {
            short index = (slot_ - 8) + page_ * 16;
            char* party = func_02010828(gameState);
            short* items = func_0207c5f8(party + 0x1d4, sMoveLists[kind_]);
            signed char* counts = func_0207c60c(party + 0x1d4, sMoveLists[kind_]);
            short swapped2 = swapped_;
            signed char count = counts[swapped2];
            items[swapped2] = items[index];
            item = items[swapped2];
            items[index] = item;
            counts[swapped_] = counts[index];
            items[index] = item;
            counts[index] = count;
            LoadPage();
            flags_ |= EQUIPMENT_LOAD_PAGE;
            pageStep_ = 0;
            swapped_ = -1;
            SetState(4);
            func_0205eaa0(data_02108760, 1, 0);
            screen->flags_ |= MEMBER_SCREEN_TURNING | MEMBER_SCREEN_CHANGE_MEMBER;
            frame_.corners_ = (char*)models_;
            flags_ |= EQUIPMENT_KINDS | EQUIPMENT_ARROWS;
        }
        else if (func_02012444(data_02114e30, 2))
        {
            swapped_ = -1;
            SetState(4);
            screen->flags_ |= MEMBER_SCREEN_TURNING | MEMBER_SCREEN_CHANGE_MEMBER;
            frame_.corners_ = (char*)models_;
            flags_ |= EQUIPMENT_KINDS | EQUIPMENT_ARROWS;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11CursorFrame10InitializeEv(); // CursorFrame::Initialize
    void _ZN11CursorFrame11SetPositionEii(); // CursorFrame::SetPosition
    void _ZN11CursorFrame13SetTargetSizeEii(); // CursorFrame::SetTargetSize
    void _ZN11CursorFrame17SetTargetPositionEii(); // CursorFrame::SetTargetPosition
    void _ZN11CursorFrame4DrawEis(); // CursorFrame::Draw
    void _ZN11CursorFrame7SetSizeEii(); // CursorFrame::SetSize
    void _ZN13EquipmentMenu11IsConfirmedEv(); // EquipmentMenu::IsConfirmed
    void _ZN13EquipmentMenu14GetTouchedSlotEii(); // EquipmentMenu::GetTouchedSlot
    void _ZN13EquipmentMenu15GetSlotPositionEiPiS0_(); // EquipmentMenu::GetSlotPosition
    void _ZN13EquipmentMenu8LoadPageEv(); // EquipmentMenu::LoadPage
    void _ZN13EquipmentMenu8SetStateEh(); // EquipmentMenu::SetState
    void _ZN13EquipmentMenu8TouchTopEii(); // EquipmentMenu::TouchTop
    void _ZN13EquipmentMenu8TurnPageEi(); // EquipmentMenu::TurnPage
    void _ZN13EquipmentMenu9MoveFrameEjh(); // EquipmentMenu::MoveFrame
    void _ZN13EquipmentMenu9SetMemberEii(); // EquipmentMenu::SetMember
}

asm void EquipmentMenu::State_Move()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x4c
    mov r4, r0
    add r2, r4, #0x3000
    ldrb r0, [r2, #0xdba]
    cmp r0, #0x0
    bne @L0215c0ac
    add r0, r4, #0x3d00
    ldrsb r5, [r0, #0xbb]
    ldrsb r3, [r0, #0xbd]
    add r1, r4, #0xa60
    sub r5, r5, #0x8
    add r3, r5, r3, lsl #0x4
    strh r3, [r0, #0xe0]
    add r1, r1, #0x2000
    add r0, r4, #0x1000
    str r1, [r0, #0xa34]
    ldrb r0, [r2, #0xdba]
    add r0, r0, #0x1
    strb r0, [r2, #0xdba]
    b @L0215c514
@L0215c0ac:
    cmp r0, #0x1
    bne @L0215c514
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    mov r7, r0
    ldr r1, [r7, #0x4fc]
    mov r0, r4
    mov r2, #0x0
    bl _ZN13EquipmentMenu9SetMemberEii
    bl _ZN9GameState11GetInstanceEv
    mov r5, r0
    ldr r0, =data_02114e54
    mov r6, #0x0
    ldrb r1, [r0, #0x55]
    mov r8, r6
    cmp r1, #0x0
    beq @L0215c188
    add r1, sp, #0xc
    add r2, sp, #0x8
    mov r6, #0x1
    bl func_02012a84
    add r1, r4, #0x3000
    ldr r2, [r1, #0xdcc]
    mov r0, r4
    bic r2, r2, #0x4
    orr r2, r2, #0x8
    str r2, [r1, #0xdcc]
    ldr r1, [sp, #0xc]
    ldr r2, [sp, #0x8]
    bl _ZN13EquipmentMenu8TouchTopEii
    ldr r1, [sp, #0xc]
    ldr r2, [sp, #0x8]
    mov r0, r4
    bl _ZN13EquipmentMenu14GetTouchedSlotEii
    cmp r0, #0x8
    blt @L0215c1b0
    cmp r0, #0x18
    bge @L0215c1b0
    add r1, r4, #0x3000
    strb r0, [r1, #0xdbb]
    add r0, r4, #0x3d00
    ldrsb r1, [r0, #0xbb]
    add r0, r4, #0x1f4
    add r0, r0, #0x1800
    sub r1, r1, #0x8
    mov r8, r6
    bl func_0205bb04
    add r0, r4, #0x3000
    ldrb r1, [r0, #0xdb8]
    ldrb r2, [r0, #0xdbb]
    mov r0, r4
    bl _ZN13EquipmentMenu9MoveFrameEjh
    b @L0215c1b0
@L0215c188:
    ldrb r1, [r0, #0x5f]
    cmp r1, #0x0
    ldrneh r0, [r0, #0x24]
    cmpne r0, #0x0
    movne r6, #0x1
    bne @L0215c1b0
    ldr r0, =data_02114e54
    ldrb r0, [r0, #0x54]
    cmp r0, #0x0
    movne r6, #0x1
@L0215c1b0:
    cmp r6, #0x0
    bne @L0215c258
    mov r0, r5
    bl _ZNK9GameState12GetTickCountEv
    movs r1, r0
    add r0, r4, #0x1f4
    moveq r1, #0x1
    add r0, r0, #0x1800
    bl func_0205bf58
    add r0, r4, #0x3d00
    ldrsb r0, [r0, #0xbb]
    mov r6, #0x0
    sub r0, r0, #0x8
    mov r1, r0, lsr #0x1f
    rsb r0, r1, r0, lsl #0x1e
    adds r0, r1, r0, ror #0x1e
    bne @L0215c21c
    ldr r0, =data_02114e30
    mov r1, #0x20
    bl func_02012444
    cmp r0, #0x0
    beq @L0215c248
    mov r0, r4
    mvn r1, #0x0
    bl _ZN13EquipmentMenu8TurnPageEi
    mov r6, r0
    b @L0215c248
@L0215c21c:
    cmp r0, #0x3
    bne @L0215c248
    ldr r0, =data_02114e30
    mov r1, #0x10
    bl func_02012444
    cmp r0, #0x0
    beq @L0215c248
    mov r0, r4
    mov r1, #0x1
    bl _ZN13EquipmentMenu8TurnPageEi
    mov r6, r0
@L0215c248:
    cmp r6, #0x0
    beq @L0215c258
    mov r0, r4
    bl _ZN13EquipmentMenu8LoadPageEv
@L0215c258:
    add r0, r4, #0x3d00
    ldrsb r2, [r0, #0xbd]
    ldrsh r1, [r0, #0xe0]
    mov r0, r2, lsl #0x14
    mov r2, r0, asr #0x10
    add r2, r2, #0x10
    cmp r1, r0, asr #0x10
    mov r0, r2, lsl #0x10
    blt @L0215c344
    cmp r1, r0, asr #0x10
    bge @L0215c344
    add r0, sp, #0x10
    bl _ZN11CursorFrame10InitializeEv
    mov r2, #0x8000
    sub r1, r2, #0xb000
    mov r0, #0x3000
    add r3, r4, #0x2840
    str r3, [sp, #0x10]
    str r2, [sp, #0x14]
    str r1, [sp, #0x18]
    str r0, [sp, #0x1c]
    str r0, [sp, #0x24]
    str r1, [sp, #0x20]
    add r0, r4, #0x3d00
    ldrsh r0, [r0, #0xe0]
    add r2, sp, #0x4
    add r3, sp, #0x0
    mov r1, r0, lsr #0x1f
    rsb r0, r1, r0, lsl #0x1c
    add r1, r1, r0, ror #0x1c
    mov r0, r4
    add r1, r1, #0x8
    bl _ZN13EquipmentMenu15GetSlotPositionEiPiS0_
    ldr r1, [sp, #0x4]
    ldr r0, [sp, #0x0]
    mov r6, r1, lsl #0xc
    mov r9, r0, lsl #0xc
    add r0, sp, #0x10
    mov r1, r6
    mov r2, r9
    bl _ZN11CursorFrame17SetTargetPositionEii
    mov r1, r6
    mov r2, r9
    add r0, sp, #0x10
    bl _ZN11CursorFrame11SetPositionEii
    mov r1, #0x18000
    add r0, sp, #0x10
    mov r2, r1
    bl _ZN11CursorFrame13SetTargetSizeEii
    mov r1, #0x18000
    add r0, sp, #0x10
    mov r2, r1
    bl _ZN11CursorFrame7SetSizeEii
    mov r0, #0x4800
    str r0, [sp, #0x48]
    ldr r2, =0x7fff
    add r0, sp, #0x10
    mov r1, #0x0
    bl _ZN11CursorFrame4DrawEis
@L0215c344:
    add r0, r4, #0x1f4
    add r0, r0, #0x1800
    bl func_0205bb84
    add r1, r4, #0x3d00
    ldrsb r1, [r1, #0xbb]
    add r6, r0, #0x8
    cmp r6, r1
    beq @L0215c394
    ldr r0, =data_02108760
    add r3, r4, #0x3000
    mov r1, #0x2
    mov r2, #0x0
    strb r6, [r3, #0xdbb]
    bl func_0205eaa0
    add r0, r4, #0x3000
    ldrb r1, [r0, #0xdb8]
    ldrb r2, [r0, #0xdbb]
    mov r0, r4
    bl _ZN13EquipmentMenu9MoveFrameEjh
    b @L0215c514
@L0215c394:
    bne @L0215c514
    mov r0, r4
    bl _ZN13EquipmentMenu11IsConfirmedEv
    cmp r0, #0x0
    cmpeq r8, #0x0
    beq @L0215c4b8
    add r0, r4, #0x3d00
    ldrsb r2, [r0, #0xbb]
    ldrsb r1, [r0, #0xbd]
    mov r0, r5
    sub r2, r2, #0x8
    add r1, r2, r1, lsl #0x4
    mov r9, r1, lsl #0x10
    mov r8, r9, asr #0x10
    bl func_02010828
    add r1, r4, #0x3000
    ldrb r2, [r1, #0xdbc]
    ldr r1, =sMoveLists
    mov r6, r0
    ldrb r1, [r1, r2]
    add r0, r6, #0x1d4
    bl func_0207c5f8
    add r1, r4, #0x3000
    ldrb r2, [r1, #0xdbc]
    ldr r1, =sMoveLists
    mov r5, r0
    ldrb r1, [r1, r2]
    add r0, r6, #0x1d4
    bl func_0207c60c
    add r1, r4, #0x3d00
    ldrsh r6, [r1, #0xe0]
    mov r3, r8, lsl #0x1
    ldrsh r2, [r5, r3]
    mov lr, r6, lsl #0x1
    ldrsb r6, [r0, r6]
    ldrsh r12, [r5, lr]
    strh r2, [r5, lr]
    ldrsb r2, [r0, r8]
    ldrsh r1, [r1, #0xe0]
    strb r2, [r0, r1]
    strh r12, [r5, r3]
    strb r6, [r0, r9, asr #0x10]
    mov r0, r4
    bl _ZN13EquipmentMenu8LoadPageEv
    add r0, r4, #0x3000
    ldr r2, [r0, #0xdcc]
    mov r1, #0x0
    orr r2, r2, #0x40
    str r2, [r0, #0xdcc]
    strb r1, [r0, #0xdaa]
    sub r1, r1, #0x1
    add r0, r4, #0x3d00
    strh r1, [r0, #0xe0]
    mov r0, r4
    mov r1, #0x4
    bl _ZN13EquipmentMenu8SetStateEh
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    add r0, r7, #0x600
    ldrh r2, [r0, #0x34]
    add r1, r4, #0xa70
    add r1, r1, #0x1000
    orr r2, r2, #0x81
    strh r2, [r0, #0x34]
    add r0, r4, #0x1000
    str r1, [r0, #0xa34]
    add r0, r4, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0xc
    str r1, [r0, #0xdcc]
    b @L0215c514
@L0215c4b8:
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    beq @L0215c514
    mov r0, r4
    add r2, r4, #0x3d00
    mvn r3, #0x0
    mov r1, #0x4
    strh r3, [r2, #0xe0]
    bl _ZN13EquipmentMenu8SetStateEh
    add r0, r7, #0x600
    ldrh r2, [r0, #0x34]
    add r1, r4, #0xa70
    add r1, r1, #0x1000
    orr r2, r2, #0x81
    strh r2, [r0, #0x34]
    add r0, r4, #0x1000
    str r1, [r0, #0xa34]
    add r0, r4, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0xc
    str r1, [r0, #0xdcc]
@L0215c514:
    add sp, sp, #0x4c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
}
#endif

static unsigned char sSortLists2[8] = {0, 1, 4, 2, 5, 3, 6, 7};
static unsigned char sSortLists[8] = {0, 1, 4, 2, 5, 3, 6, 7};

// NONMATCHING: the C matches 79.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void EquipmentMenu::State_Sort()
{
    unsigned long byWearable;
    ItemSortEntry* entry;
    short count;
    char* party = func_02010828(GameState::GetInstance());
    long member;
    byWearable = 0;
    count = itemCounts_[kind_];
    signed char* counts = func_0207c60c(party + 0x1d4, sSortLists2[kind_]);
    short* items = func_0207c5f8(party + 0x1d4, sSortLists2[kind_]);
    func_0207c51c(party + 0x1d4, sSortLists[kind_]);
    int sorted = 0;
    if (sortOrders_[kind_] == 0 || sortOrders_[kind_] == 1)
    {
        sortList_.Reset();
        sortList_.SortAll2(-1, sSortLists[kind_], -1);
        sorted = 1;
    }
    else if (sortOrders_[kind_] == 3)
    {
        sortList_.Reset();
        sortList_.SortAll(-1, sSortLists[kind_], -1);
        sorted = 1;
    }
    else if (sortOrders_[kind_] == 2)
    {
        byWearable = 1;
        sorted = 1;
    }
    if (sorted)
    {
        short newItems[0x110];
        signed char newCounts[0x110];
        int selected = slots_[slot_].item_;
        for (int i = 0; i < 0x110; i++)
        {
            newItems[i] = -1;
            newCounts[i] = 0;
        }
        if (!byWearable)
        {
            ItemSortEntry* entry = sortList_.first_;
            int index = 0;
            while (entry != NULL)
            {
                for (int i = 0; i < count; i++)
                {
                    short item = items[i];
                    if (entry->id_ == item)
                    {
                        newItems[index] = item;
                        newCounts[index] = counts[i];
                        index++;
                        entry = entry->next_;
                        break;
                    }
                    if (i == count - 1)
                        entry = entry->next_;
                }
            }
        }
        else
        {
            EquipmentModel* info;
            PartEntry item;
            member = (signed char)func_ov017_021a193c(func_ov017_0218b5b0()->unknown_ptr_3708)->member_;
            func_020de1d4(&item);
            PartModelInfo model;
            memset(&model, 0, sizeof(model));
            int index = 0;
            item.model_ = &model;
            int unwearable = 0;
            for (int i = 0; i < count; i++)
            {
                int id = items[i];
                if (id <= 0)
                    continue;
                func_020de1d4(&item);
                memset(&model, 0, sizeof(model));
                item.model_ = &model;
                EquipmentModel* info = modelTable_.Find(id);
                if (info != NULL)
                {
                    item.unk_18 = info->id_;
                    item.category_ = info->category_;
                    model.unk_0_0 = info->unk_4_0;
                    model.unk_0_7 = info->unk_4_7;
                    model.unk_4_0 = info->unk_4_11;
                    model.unk_0_29 = info->unk_4_23;
                    model.unk_0_30 = info->unk_4_24;
                    model.unk_4_27 = info->unk_4_26;
                    model.unk_4_28 = info->unk_4_27;
                    model.unk_4_29 = info->unk_4_28;
                }
                if (func_020dd4c4(member, &item))
                {
                    unwearable++;
                }
                else
                {
                    newItems[index] = items[i];
                    index++;
                    newCounts[index] = counts[i];
                    items[i] = -1;
                    counts[i] = 0;
                }
            }
            func_0207c51c(party + 0x1d4, sSortLists[kind_]);
            memcpy(&newItems[index], items, unwearable * 2);
            memcpy(&newCounts[index], counts, unwearable);
        }
        memcpy(items, newItems, count * 2);
        memcpy(counts, newCounts, count);
        if (slot_ >= 8 && slot_ < 24)
        {
            short index = -1;
            for (int i = 0; i < count; i++)
            {
                if (selected == items[i])
                {
                    index = i;
                    break;
                }
            }
            if (index >= 0)
            {
                lastPage_ = page_;
                page_ = index / 16;
                signed char slot = slot_;
                slot_ = index % 16 + 8;
                if (slot != slot_)
                {
                    MoveFrame(4, slot_);
                    func_0205bb04(&cursor_, slot_ - 8);
                }
            }
        }
        func_0205eaa0(data_02108760, 1, 0);
    }
    if (sortOrders_[kind_] == 0 || sortOrders_[kind_] == 1)
    {
        sortOrders_[kind_] = 3;
        flags_ |= EQUIPMENT_SORT_ICON;
    }
    else if (sortOrders_[kind_] == 3)
    {
        sortOrders_[kind_] = 2;
        flags_ |= EQUIPMENT_SORT_ICON;
    }
    else if (sortOrders_[kind_] == 2)
    {
        sortOrders_[kind_] = 1;
        flags_ |= EQUIPMENT_SORT_ICON;
    }
    LoadPage();
    infoWindow_.SetItem(slots_[slot_].item_);
    flags_ |= EQUIPMENT_LOAD_PAGE;
    pageStep_ = 0;
    SetState(lastState_);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12ItemSortList5ResetEv(); // ItemSortList::Reset
    void _ZN12ItemSortList7SortAllEiii(); // ItemSortList::SortAll
    void _ZN12ItemSortList8SortAll2Eiii(); // ItemSortList::SortAll2
    void _ZN14ItemInfoWindow7SetItemEs(); // ItemInfoWindow::SetItem
    void _ZN19EquipmentModelTable4FindEi(); // EquipmentModelTable::Find
}

asm void EquipmentMenu::State_Sort()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x388
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    bl func_02010828
    add r1, r10, #0x3000
    ldrb r3, [r1, #0xdbc]
    ldr r1, =sSortLists2
    mov r4, r0
    add r0, r10, r3, lsl #0x1
    add r2, r0, #0x3d00
    ldrb r1, [r1, r3]
    add r0, r4, #0x1d4
    ldrsh r5, [r2, #0x98]
    bl func_0207c5f8
    add r1, r10, #0x3000
    ldrb r2, [r1, #0xdbc]
    ldr r1, =sSortLists2
    mov r6, r0
    ldrb r1, [r1, r2]
    add r0, r4, #0x1d4
    bl func_0207c60c
    add r1, r10, #0x3000
    ldrb r2, [r1, #0xdbc]
    ldr r1, =sSortLists
    mov r7, r0
    ldrb r1, [r1, r2]
    add r0, r4, #0x1d4
    bl func_0207c51c
    add r0, r10, #0x3000
    ldrb r1, [r0, #0xdbc]
    add r0, r10, #0x1d4
    add r0, r0, #0x3c00
    ldrb r0, [r0, r1]
    mov r2, #0x0
    mov r8, r2
    cmp r0, #0x0
    cmpne r0, #0x1
    bne @L0215c604
    add r0, r10, #0x9e0
    add r0, r0, #0x1000
    bl _ZN12ItemSortList5ResetEv
    add r0, r10, #0x3000
    ldrb r3, [r0, #0xdbc]
    ldr r2, =sSortLists
    add r0, r10, #0x9e0
    mvn r1, #0x0
    ldrb r2, [r2, r3]
    mov r3, r1
    add r0, r0, #0x1000
    bl _ZN12ItemSortList8SortAll2Eiii
    mov r2, #0x1
    b @L0215c650
@L0215c604:
    cmp r0, #0x3
    bne @L0215c644
    add r0, r10, #0x9e0
    add r0, r0, #0x1000
    bl _ZN12ItemSortList5ResetEv
    add r0, r10, #0x3000
    ldrb r3, [r0, #0xdbc]
    ldr r2, =sSortLists
    add r0, r10, #0x9e0
    mvn r1, #0x0
    ldrb r2, [r2, r3]
    mov r3, r1
    add r0, r0, #0x1000
    bl _ZN12ItemSortList7SortAllEiii
    mov r2, #0x1
    b @L0215c650
@L0215c644:
    cmp r0, #0x2
    moveq r8, #0x1
    moveq r2, r8
@L0215c650:
    cmp r2, #0x0
    beq @L0215ca74
    add r0, r10, #0x3d00
    ldrsb r2, [r0, #0xbb]
    mov r1, #0x1c
    mov r0, #0x0
    mla r1, r2, r1, r10
    add r1, r1, #0x2d00
    ldrsh r1, [r1, #0x90]
    mvn r11, #0x0
    add r3, sp, #0x168
    str r1, [sp, #0x8]
    mov r2, r0
    add r1, sp, #0x58
    b @L0215c69c
@L0215c68c:
    mov r9, r0, lsl #0x1
    strb r2, [r1, r0]
    strh r11, [r3, r9]
    add r0, r0, #0x1
@L0215c69c:
    cmp r0, #0x110
    blt @L0215c68c
    cmp r8, #0x0
    bne @L0215c724
    add r0, r10, #0x1000
    mov r3, #0x0
    ldr r2, [r0, #0x9e0]
    sub r8, r5, #0x1
    mov r1, r3
    add r11, sp, #0x168
    add r9, sp, #0x58
    b @L0215c718
@L0215c6cc:
    mov r4, r1
    b @L0215c710
@L0215c6d4:
    mov r0, r4, lsl #0x1
    ldrsh r0, [r6, r0]
    ldrsh r12, [r2, #0x8]
    cmp r12, r0
    bne @L0215c704
    mov r12, r3, lsl #0x1
    strh r0, [r11, r12]
    ldrsb r0, [r7, r4]
    strb r0, [r9, r3]
    add r3, r3, #0x1
    ldr r2, [r2, #0x0]
    b @L0215c718
@L0215c704:
    cmp r4, r8
    ldreq r2, [r2, #0x0]
    add r4, r4, #0x1
@L0215c710:
    cmp r4, r5
    blt @L0215c6d4
@L0215c718:
    cmp r2, #0x0
    bne @L0215c6cc
    b @L0215c984
@L0215c724:
    bl func_ov017_0218b5b0
    add r0, r0, #0x3000
    ldr r0, [r0, #0x708]
    bl func_ov017_021a193c
    ldr r1, [r0, #0x4fc]
    add r0, sp, #0x38
    mov r1, r1, lsl #0x18
    mov r1, r1, asr #0x18
    str r1, [sp, #0x4]
    bl func_020de1d4
    add r0, sp, #0x18
    mov r1, #0x0
    mov r2, #0x20
    bl memset
    mov r8, #0x0
    add r0, sp, #0x18
    str r0, [sp, #0x38]
    mvn r0, #0x0
    str r0, [sp, #0xc]
    add r0, r10, #0x1ec
    str r0, [sp, #0x10]
    ldr r0, [sp, #0xc]
    mov r11, r8
    add r0, r0, #0x1000
    mov r9, r8
    str r0, [sp, #0x14]
    b @L0215c93c
@L0215c790:
    mov r0, r9, lsl #0x1
    ldrsh r0, [r6, r0]
    str r0, [sp, #0x0]
    cmp r0, #0x0
    ble @L0215c938
    add r0, sp, #0x38
    bl func_020de1d4
    add r0, sp, #0x18
    mov r1, #0x0
    mov r2, #0x20
    bl memset
    ldr r1, [sp, #0x0]
    add r0, sp, #0x18
    str r0, [sp, #0x38]
    ldr r0, [sp, #0x10]
    add r0, r0, #0x1800
    bl _ZN19EquipmentModelTable4FindEi
    cmp r0, #0x0
    beq @L0215c8ec
    ldrsh r3, [r0, #0x0]
    ldr r1, [sp, #0x40]
    ldr r2, [sp, #0x18]
    strh r3, [sp, #0x50]
    ldrh r12, [r0, #0x2]
    bic r1, r1, #0xf
    ldr r3, [sp, #0x1c]
    mov r12, r12, lsl #0x1c
    mov r12, r12, lsr #0x1c
    and r12, r12, #0xf
    orr r1, r1, r12
    str r1, [sp, #0x40]
    ldr r1, [sp, #0xc]
    bic r2, r2, #0x7f
    and r1, r3, r1, lsl #0xc
    ldr r3, [r0, #0x4]
    mov r3, r3, lsl #0x19
    mov r3, r3, lsr #0x19
    and r3, r3, #0x7f
    orr r2, r2, r3
    str r2, [sp, #0x18]
    ldr r3, [r0, #0x4]
    bic r2, r2, #0x780
    mov r3, r3, lsl #0x15
    mov r3, r3, lsr #0x1c
    mov r3, r3, lsl #0x1c
    orr r2, r2, r3, lsr #0x15
    str r2, [sp, #0x18]
    ldr r3, [r0, #0x4]
    bic r2, r2, #0x20000000
    mov r12, r3, lsl #0x9
    ldr r3, [sp, #0x14]
    and r3, r3, r12, lsr #0x14
    orr r1, r1, r3
    str r1, [sp, #0x1c]
    ldr r3, [r0, #0x4]
    bic r1, r1, #0x8000000
    mov r3, r3, lsl #0x8
    mov r3, r3, lsr #0x1f
    mov r3, r3, lsl #0x1f
    orr r2, r2, r3, lsr #0x2
    str r2, [sp, #0x18]
    ldr r3, [r0, #0x4]
    bic r2, r2, #0xc0000000
    mov r3, r3, lsl #0x6
    mov r3, r3, lsr #0x1e
    orr r2, r2, r3, lsl #0x1e
    str r2, [sp, #0x18]
    ldr r2, [r0, #0x4]
    mov r2, r2, lsl #0x5
    mov r2, r2, lsr #0x1f
    mov r2, r2, lsl #0x1f
    orr r1, r1, r2, lsr #0x4
    str r1, [sp, #0x1c]
    ldr r2, [r0, #0x4]
    bic r1, r1, #0x10000000
    mov r2, r2, lsl #0x4
    mov r2, r2, lsr #0x1f
    mov r2, r2, lsl #0x1f
    orr r1, r1, r2, lsr #0x3
    str r1, [sp, #0x1c]
    ldr r0, [r0, #0x4]
    bic r1, r1, #0x20000000
    mov r0, r0, lsl #0x3
    mov r0, r0, lsr #0x1f
    mov r0, r0, lsl #0x1f
    orr r0, r1, r0, lsr #0x2
    str r0, [sp, #0x1c]
@L0215c8ec:
    ldr r0, [sp, #0x4]
    add r1, sp, #0x38
    bl func_020dd4c4
    cmp r0, #0x0
    addne r11, r11, #0x1
    bne @L0215c938
    mov r0, r9, lsl #0x1
    ldrsh r3, [r6, r0]
    mov r2, r8, lsl #0x1
    add r1, sp, #0x168
    strh r3, [r1, r2]
    ldrsb r2, [r7, r9]
    add r1, sp, #0x58
    strb r2, [r1, r8]
    ldr r1, [sp, #0xc]
    add r8, r8, #0x1
    strh r1, [r6, r0]
    mov r0, #0x0
    strb r0, [r7, r9]
@L0215c938:
    add r9, r9, #0x1
@L0215c93c:
    cmp r9, r5
    blt @L0215c790
    add r0, r10, #0x3000
    ldrb r2, [r0, #0xdbc]
    ldr r1, =sSortLists
    add r0, r4, #0x1d4
    ldrb r1, [r1, r2]
    bl func_0207c51c
    add r0, sp, #0x168
    mov r1, r6
    add r0, r0, r8, lsl #0x1
    mov r2, r11, lsl #0x1
    bl memcpy
    add r0, sp, #0x58
    mov r2, r11
    add r0, r0, r8
    mov r1, r7
    bl memcpy
@L0215c984:
    add r1, sp, #0x168
    mov r0, r6
    mov r2, r5, lsl #0x1
    bl memcpy
    add r1, sp, #0x58
    mov r0, r7
    mov r2, r5
    bl memcpy
    add r0, r10, #0x3d00
    ldrsb r0, [r0, #0xbb]
    cmp r0, #0x8
    blt @L0215ca64
    cmp r0, #0x18
    bge @L0215ca64
    mvn r7, #0x0
    mov r2, #0x0
    b @L0215c9e8
@L0215c9c8:
    mov r0, r2, lsl #0x1
    ldrsh r1, [r6, r0]
    ldr r0, [sp, #0x8]
    cmp r0, r1
    moveq r0, r2, lsl #0x10
    moveq r7, r0, asr #0x10
    beq @L0215c9f0
    add r2, r2, #0x1
@L0215c9e8:
    cmp r2, r5
    blt @L0215c9c8
@L0215c9f0:
    cmp r7, #0x0
    blt @L0215ca64
    add r4, r10, #0x3d00
    ldrsb r5, [r4, #0xbd]
    mov r0, r7, asr #0x3
    add r3, r10, #0x3000
    add r0, r7, r0, lsr #0x1c
    mov r2, r7, lsr #0x1f
    rsb r1, r2, r7, lsl #0x1c
    add r1, r2, r1, ror #0x1c
    strb r5, [r3, #0xdbf]
    mov r0, r0, asr #0x4
    strb r0, [r3, #0xdbd]
    ldrsb r2, [r4, #0xbb]
    add r0, r1, #0x8
    strb r0, [r3, #0xdbb]
    ldrsb r1, [r4, #0xbb]
    cmp r2, r1
    beq @L0215ca64
    and r2, r1, #0xff
    mov r0, r10
    mov r1, #0x4
    bl _ZN13EquipmentMenu9MoveFrameEjh
    mov r0, r4
    ldrsb r1, [r0, #0xbb]
    add r0, r10, #0x1f4
    add r0, r0, #0x1800
    sub r1, r1, #0x8
    bl func_0205bb04
@L0215ca64:
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
@L0215ca74:
    add r0, r10, #0x3000
    ldrb r3, [r0, #0xdbc]
    add r1, r10, #0x1d4
    add r2, r1, #0x3c00
    ldrb r1, [r2, r3]
    cmp r1, #0x0
    cmpne r1, #0x1
    bne @L0215cab0
    mov r0, #0x3
    strb r0, [r2, r3]
    add r0, r10, #0x3000
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x800
    str r1, [r0, #0xdcc]
    b @L0215cae8
@L0215cab0:
    cmp r1, #0x3
    bne @L0215cad0
    mov r1, #0x2
    strb r1, [r2, r3]
    ldr r1, [r0, #0xdcc]
    orr r1, r1, #0x800
    str r1, [r0, #0xdcc]
    b @L0215cae8
@L0215cad0:
    cmp r1, #0x2
    moveq r1, #0x1
    streqb r1, [r2, r3]
    ldreq r1, [r0, #0xdcc]
    orreq r1, r1, #0x800
    streq r1, [r0, #0xdcc]
@L0215cae8:
    mov r0, r10
    bl _ZN13EquipmentMenu8LoadPageEv
    add r0, r10, #0x3d00
    ldrsb r1, [r0, #0xbb]
    mov r0, #0x1c
    add r2, r10, #0x244
    mla r0, r1, r0, r10
    add r0, r0, #0x2d00
    ldrsh r1, [r0, #0x90]
    add r0, r2, #0x1000
    bl _ZN14ItemInfoWindow7SetItemEs
    add r0, r10, #0x3000
    ldr r2, [r0, #0xdcc]
    mov r1, #0x0
    orr r2, r2, #0x40
    str r2, [r0, #0xdcc]
    strb r1, [r0, #0xdaa]
    ldrb r1, [r0, #0xdb9]
    mov r0, r10
    bl _ZN13EquipmentMenu8SetStateEh
    add sp, sp, #0x388
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

int EquipmentMenu::UpdateFade()
{
    if (!(flags_ & EQUIPMENT_FADE))
        return 0;
    unsigned char step = fadeStep_;
    if (step == 0)
    {
        func_0209c830(data_02109bf4, 0x3d);
        fadeStep_++;
    }
    if (step == 1)
    {
        if (func_0209ca2c(data_02109bf4))
            return 1;
        flags_ &= ~EQUIPMENT_FADE;
        fadeStep_ = 0;
        return 0;
    }
    return 1;
}
