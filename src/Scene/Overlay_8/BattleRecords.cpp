// Overlay 8, the battle records (see BattleRecords.h)
// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_8/BattleRecords.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "Graphics/Vector.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "Scene/Overlay_23/BattleEnd.h"
#include "System/TouchScreen.h"
#include "System/VRAM.h"
#include "Text/MessageName.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define REG_DISPCNT_SUB (*(volatile unsigned int*)0x04001000)
#define REG_BG0CNT_SUB (*(volatile unsigned short*)0x04001008)
#define REG_BG1CNT_SUB (*(volatile unsigned short*)0x0400100a)
#define REG_BG2CNT_SUB (*(volatile unsigned short*)0x0400100c)
#define REG_BG3CNT_SUB (*(volatile unsigned short*)0x0400100e)
#define REG_MTX_PUSH (*(volatile unsigned int*)0x04000444)
#define REG_MTX_POP (*(volatile unsigned int*)0x04000448)

// A title (ttlname%d.gp2) or a guide (see BattleEnd.cpp)
struct GuideEntry
{
    unsigned int unk_0;
    const char* text_;
    int unk_8;
};

// The flags and the records of the game in the save data (GameState + 0x104 + 0x7400)
struct SavedRecords
{
    GameFlags flags_;
    PlayRecords records_;
};

// What func_0202ae18 returns
struct Unknown_0202ae18
{
    char unk_0[0x100d];
    unsigned char unk_100d;
};

// The title that the protagonist shows (GameState + 0x569c)
struct HeroTitle
{
    char unk_0[4];
    unsigned int unk_4_0 : 19;
    int title_ : 11;
    unsigned int unk_4_30 : 2;
};

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];
    extern TouchState data_02114e54;
    extern unsigned char data_0211e33c[];

    GameResources* func_0200fb8c(GameState* gameState);
    PartyMember* func_0200ff1c(GameState* gameState, int index);
    int func_020100a8(GameState* gameState);
    void func_020100c4(GameState* gameState, void* camera);
    void func_020103f0(GameState* gameState, unsigned short* hours, unsigned char* minutes, unsigned char* seconds);
    void func_020104cc(GameState* gameState, unsigned short* hours, unsigned char* minutes, unsigned char* seconds);
    short func_0201081c(GameState* gameState);
    int func_02012430(void* pad, int buttons);
    int func_02012444(void* pad, int buttons);
    void func_02012a84(TouchState* touch, int* x, int* y);
    void func_02012fe4();
    void func_02017d68();
    Unknown_0202ae18* func_0202ae18();
    int func_0202b7d8();
    int func_0202ba00(void*);
    int func_0202c508(void*);
    int func_0202c540(void*);
    void func_0202e5c0(void* camera, int x, int y, int z);
    void func_0202e5c8(void* camera, int x, int y, int z);
    void func_02041a5c(char* text, int);
    void func_02041a90(char* text, int x, int y);
    void func_02041e70(char* text, int color);
    void func_0204201c(char* text, const char* append, int);
    void func_02042058(char* text, const char* append);
    int func_020420e8(const char* text, int large);
    MessageSystem* func_020421a0();
    void func_02042764(const void* codes, char* text, int);
    void func_02043124(MessageSystem* messages);
    void func_02043204(MessageSystem* messages);
    void func_020432c4(MessageSystem* messages);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    void func_02045cac(MessageSystem* messages);
    void func_02046380(MessageSystem* messages);
    void func_02046574(MessageSystem* messages, int index, const char* text);
    void func_020465c0(MessageSystem* messages, int index, int value);
    void func_020465d8(MessageSystem* messages, int index, int);
    void func_020465f0(MessageSystem* messages, int index, int digits);
    void func_02046608(MessageSystem* messages, int, const char* format, char* output, int size, int, int);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    int func_02046900(void* archive);
    void func_0204af38(BackgroundGraphics* background, int, SafeAllocator* allocator);
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
    void func_0204b8d0(BackgroundGraphics* background, int, int, int, int, int, int, int, int);
    void func_0204bc74(BackgroundGraphics* background, int, int, int, int, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, unsigned int size);
    void func_0205a198(Sprite* sprite);
    void func_0205a234(SpriteAnimationList* list);
    void func_0205a330(SpriteAnimationList* list, int ticks);
    void func_0205a370(SpriteAnimationList* list, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* list, int index);
    void func_0205a42c(SpriteAnimationList* list, int, int);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a494(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205ae8c(SpriteRenderer* renderer);
    void func_0205af84(SpriteRenderer* renderer, Sprite* sprite, int);
    void func_0205afb0(SpriteRenderer* renderer, Sprite* sprite, int);
    int func_0205bafc(WindowCursor* cursor);
    int func_0205bb84(WindowCursor* cursor);
    void func_0205bef8(WindowCursor* cursor);
    void func_0205bf58(WindowCursor* cursor, int ticks);
    void func_0205cf78(TextWindow* window, Canvas* canvases, int count);
    void func_0205cfd4(TextWindow* window);
    void func_0205d048(TextWindow* window);
    unsigned char func_0205d0e0(TextWindow* window, int ticks);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d304(TextWindow* window, char* text, int, int, int, int, int, int);
    void func_0205d5d0(TextWindow* window, int, char* text, int, int);
    void func_0205d6a0(TextWindow* window, int);
    Canvas* func_0205d81c(TextWindow* window, unsigned char canvas);
    void func_0205eaa0(void* sound, int effect, int);
    char* func_0205ec34();
    int func_0206dfb0(void*, void*, int flag);
    void func_020727d8(TextList* texts);
    void func_020727f8(TextList* texts, const char* path, int id, char* output, int);
    void func_02072928(TextList* texts, void* file, unsigned int size, int id, char* output, int);
    const char* func_02072a68(TextList* texts, short id);
    void func_0207df50(void* state);
    void func_0207df90(void* state);
    void func_0207dfac(void* state);
    void* func_02094a00();
    void func_02094b34(void* music, int, int, int, int);
    void func_02094b40(void* music);
    int func_02094b4c(void* music);
    void func_0209c3b4(void* sound, int);
    void func_0209c678(void* sound, int);
    int func_0209ca2c(void* sound);
    int func_0209cae8(void* sound);
    void func_0209fe9c(TitleScript* script);
    void func_0209fee4(TitleScript* script, SafeAllocator* allocator, void* file, unsigned int size);
    void func_0209ff64(TitleScript* script, int);
    void func_0209ff6c(TitleScript* script);
    void func_020a05d8(PlayRecords* records, int);
    unsigned int func_020a0870(PlayRecords* records);
    unsigned int func_020a08a4(PlayRecords* records);
    unsigned int func_020a08d8(PlayRecords* records);
    unsigned int func_020a090c(PlayRecords* records);
    void func_020a13c4(void* guides);
    void func_020a13e4(void* guides, SafeAllocator* allocator, short* ids, unsigned short count, int);
    GuideEntry* func_020a15bc(void* guides, short id);
    void func_020a2010(void* camera);
    void func_020a27a0(void* camera);
    void func_020ac0b4(unsigned int* count);
    void func_020ca458(int value, void* destination, unsigned int size);
    char* func_020d2f88(const char* text, const char* search);
    int func_020d2ff0(const char* text);
    int func_020d3018(const char* a, const char* b);
    void* func_020d6c00();
    void func_020dc2bc();
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, int id);
    const char* func_020e046c(char* output, void* file, unsigned int size, short id);
    void func_020e46c4(MessageName* name);
    void func_020e4b34(MessageName* name, char* text, char* text2, int, int, int, int, int female, int, int, int, int);
    void func_020e4c74(MessageName* name, GameObject* object);
    GameResources* func_ov017_0218b5b0();
}

// The strings of the functions, which the compiler pools in this order. The functions in assembly (NONMATCHING) can't
// reference the compiler's pool, so they're in an array for them
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] __attribute__((aligned(4))) =
    "data/scenario/title_clr.stb\0data/scenario/cmtFileTbl.bin\0data/scenario/title_gyalel.stb\0"
    "data/bin/menu/str_jr.gp2\0str_jr_<LG>.nat\0data/bin/ttlname%d.gp2\0ttlname%d_<LG>.nat\0\0sake\0stand\0"
    "data/bin/profstr.gp2\0profstr_<LG>.bin\0\n\0<val";
#define STRING(offset, text) (sStrings + (offset))
#endif

static char sFormat[] = "%s";

// The title that the protagonist shows
static inline HeroTitle* GetHeroTitle(GameState* gameState)
{
    return (HeroTitle*)((char*)gameState + 0x569c);
}

// The data of the save file in GameState
static inline char* GetSaveData(GameState* gameState)
{
    return (char*)gameState + 0x104;
}

// The records in the save data
static inline SavedRecords* GetSavedRecords(GameState* gameState)
{
    return (SavedRecords*)(GetSaveData(gameState) + 0x7400);
}

// The records of the last clear of the game
static inline ClearRecords* GetClearRecords(GameState* gameState)
{
    return &GetSavedRecords(gameState)->records_.lastClear_;
}

static void ResetTime(PlayTime* time);

// Scrolls the menu to show an item (the compiler doesn't inline functions with conditions)
#define SCROLL_TO(index)                                                                                                   if ((index) > top_ + 5)                                                                                                    top_ = (index) - 5;                                                                                                else if ((index) < top_)                                                                                                   top_ = (index)

void BattleRecords::CreateAllocators(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;
    backgroundAllocator_.CreateTypeA(allocator->Allocate(0x2400), 0x2400);
    textAllocator_.CreateTypeA(allocator->Allocate(0x800), 0x800);
    if (mode_ == 0)
    {
        allocator_.CreateTypeA(allocator->Allocate(0x1000), 0x1000);
        spriteAllocator_.CreateTypeA(allocator->Allocate(0x200), 0x200);
        iconAllocator_.CreateTypeA(allocator->Allocate(0x400), 0x400);
        modelAllocator_.CreateTypeA(allocator->Allocate(0x8800), 0x8800);
        titleAllocator_.CreateTypeA(allocator->Allocate(0x8000), 0x8000);
        guideAllocator_.CreateTypeA(allocator->Allocate(0x8000), 0x8000);
        renderer_ = (SpriteRenderer*)allocator->Allocate(0x54);
        sprites_ = (Sprite*)allocator->Allocate(0x2d0);
        animations_ = (SpriteAnimationList*)allocator->Allocate(8);
        text_ = (char*)func_020421a0()->unk_5c;
    }
    else
    {
        text_ = (char*)allocator->Allocate(0x960);
    }
    pixels_ = backgroundAllocator_.Allocate(0x1c00);
}

void BattleRecords::Initialize()
{
    func_020466e4(func_020d6c00(), 0xf);
    allocator_.ResetAllocatorPointer();
    backgroundAllocator_.ResetAllocatorPointer();
    textAllocator_.ResetAllocatorPointer();
    spriteAllocator_.ResetAllocatorPointer();
    iconAllocator_.ResetAllocatorPointer();
    modelAllocator_.ResetAllocatorPointer();
    titleAllocator_.ResetAllocatorPointer();
    guideAllocator_.ResetAllocatorPointer();
    func_020dfc40(&texts_);
    text_ = NULL;
    func_020a13c4(titleTable_);
    func_0204af64(&backgrounds_[0]);
    func_0204af64(&backgrounds_[1]);
    func_0204af64(&backgrounds_[2]);
    func_0205cfd4(&window_);
    for (int i = 0; i < 6; i++)
        func_0204c684(&canvases_[i]);
    pixels_ = NULL;
    renderer_ = NULL;
    sprites_ = NULL;
    animations_ = NULL;
    iconRenderer_ = NULL;
    sprites_ = NULL;
    func_0205bef8(&cursor_);
    model_.Initialize();
    func_020a2010(camera_);
    titles_ = NULL;
    guide_ = NULL;
    page_ = NULL;
    state_ = 0;
    step_ = 0;
    loadStep_ = 0;
    exit_ = 0;
    title_ = -1;
    comment_ = -1;
    flags_ = 0;
    unk_b1c = 0;
    task_ = 0;
    mode_ = 0;
    kind_ = 0;
    top_ = 0;
    closed_ = 0;
    titleX_ = 0;
    guest_ = NULL;
    guestRecords_ = NULL;
    guestTexts_ = NULL;
    guestTitles_ = NULL;
    ResetTime(&times_[0]);
    ResetTime(&times_[1]);
    SavedRecords* saved = GetSavedRecords(GameState::GetInstance());
    if (saved->records_.unk_10_0 != 0)
        flags_ |= RECORDS_ITEM_4;
    if (saved->records_.lastClear_.title_ != 0)
        flags_ |= RECORDS_CLEAR_ITEM;
    InitializeItems();
}

static void ResetTime(PlayTime* time)
{
    time->hours_ = 0;
    time->minutes_ = 0;
    time->seconds_ = 0;
}

void BattleRecords::Finish()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    if (renderer_ != NULL)
        func_0205a494(renderer_);
    if (iconRenderer_ != NULL)
        func_0205a494(iconRenderer_);
    if (guide_ != NULL)
        guide_->Finish();
    MessageSystem* messages = func_020421a0();
    func_02045cac(messages);
    func_02043204(messages);
    func_02043124(messages);
    messages->unk_2d8 = NULL;
    messages->unk_2dc = NULL;
    messages->unk_2e0 = NULL;
    BackgroundGraphics* backgrounds[3] = {&backgrounds_[0], &backgrounds_[1], &backgrounds_[2]};
    for (int i = 0; i < 3; i++)
    {
        BackgroundGraphics* background = backgrounds[i];
        func_0204b010(background, 0);
        func_0204b04c(background, 0);
        func_0204b088(background, 0);
        func_0204afb4(background);
    }
    func_020ca458(0, (void*)0x06000000, GetMainBGAssignedVRAMSize());
    func_0205d048(&window_);
    model_.Destroy();
    text_ = NULL;
    pixels_ = NULL;
    SafeAllocator* allocators[8] = {&allocator_,       &backgroundAllocator_, &textAllocator_,  &spriteAllocator_,
                                    &iconAllocator_,   &modelAllocator_,      &titleAllocator_, &guideAllocator_};
    for (int i = 0; i < 7; i++)
        allocators[i]->Destroy();
    if (exit_ == 0)
    {
        if (mode_ == 0)
        {
            func_02012fe4();
            func_02017d68();
        }
        func_020466f4(func_020d6c00(), 0xf);
    }
}

int BattleRecords::Update()
{
    CheckClose();
    unsigned int ticks = GameState::GetInstance()->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    func_0205d0e0(&window_, ticks);
    TurnModel(ticks);
    model_.AdvanceEffects();
    UpdateAnimation(ticks);
    UpdateTime(0);
    UpdateTime(1);
    StateFunction states[15] = {
        &BattleRecords::State_Load,  &BattleRecords::State_Setup,     &BattleRecords::State_Guide,
        &BattleRecords::State_Main,  &BattleRecords::State_FadeOut,   &BattleRecords::State_Exit1,
        &BattleRecords::State_Exit2, &BattleRecords::State_Exit3,     &BattleRecords::State_Exit4,
        &BattleRecords::State_Exit5, &BattleRecords::State_Exit6,     &BattleRecords::State_Exit7,
        &BattleRecords::State_LastClear, &BattleRecords::State_Close, NULL,
    };
    if (states[state_] == NULL)
        return 0;
    (this->*states[state_])(ticks);
    if (titles_ != NULL)
        func_0209ff6c(titles_);
    if (guide_ != NULL)
        guide_->Update();
    if (state_ == 14)
        return 1;
    return 0;
}

void BattleRecords::Draw1()
{
    signed char state = state_;
    if (state == 0 || state == 1 || state == 14)
        return;
    if (guide_ == NULL)
    {
        func_0205d1e0(&window_);
        func_0205d228(&window_);
        func_0205d274(&window_);
    }
    if (mode_ == 1)
        return;
    if (state_ == 3 && step_ < 1)
        return;
    DrawItems();
    DrawArrows();
    DrawBackButton();
    DrawCursor();
    if (guide_ == NULL)
        return;
    guide_->Draw1();
}

void BattleRecords::Draw3D()
{
    signed char state = state_;
    if (state == 0 || state == 14)
        return;
    if (flags_ & RECORDS_NO_MODEL)
        return;
    REG_MTX_PUSH = 0;
    model_.Draw(false);
    REG_MTX_POP = 1;
}

void BattleRecords::Draw2()
{
    signed char state = state_;
    if (state == 0 || state == 1 || state == 14)
        return;
    if (mode_ == 0)
        func_0204b088(&backgrounds_[0], 0);
    if (guide_ != NULL)
    {
        guide_->Draw2();
        return;
    }
    if (flags_ & RECORDS_TIME1_CHANGED)
    {
        memset(text_, 0, 0x960);
        WriteTime(text_, 0, NULL);
        func_0205d5d0(&window_, 1, text_, 1, 0);
        flags_ &= ~RECORDS_TIME1_CHANGED;
    }
    RefreshTime(1);
    func_0205d2bc(&window_);
}

void BattleRecords::Close()
{
    flags_ |= RECORDS_CLOSE;
}

void BattleRecords::SetState(signed char state)
{
    state_ = state;
    step_ = 0;
}

static int IsScriptDone(TitleScript* script);

// Clears a guide page
static inline void ClearPage(GuidePage* page)
{
    page->unk_0_0 = 0;
    page->unk_0_9 = 0;
    page->unk_0_18 = 0;
    page->unk_0_27 = 0;
    page->layout_ = 0;
    page->text_ = NULL;
    page->unk_8 = 0;
    memset(page->title_, 0, sizeof(page->title_));
    memset(page->buffer_, 0, sizeof(page->buffer_));
    page->text_ = page->buffer_;
}

// Copies a guide to a page, with its own copy of the text
static inline void SetPage(GuidePage* page, GuideEntry* entry)
{
    if (entry == NULL)
        return;
    GuideEntry* header = (GuideEntry*)page;
    header->unk_0 = entry->unk_0;
    header->text_ = entry->text_;
    header->unk_8 = entry->unk_8;
    page->text_ = page->buffer_;
    const char* text = entry->text_;
    if (text == NULL)
        return;
    memset(page->buffer_, 0, sizeof(page->buffer_));
    sprintf(page->buffer_ + func_020d2ff0(page->buffer_), sFormat, text);
}

// The position, the rotation and the scale of the model
static const Vector3fix sPosition = {0xb000, -0x6000, 0};
static const Vector3fix sRotation = {0, 0x5ccc, 0};
static const Vector3fix sScale = {0x1000, 0x1000, 0x1000};

// NONMATCHING: the C matches 93.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void BattleRecords::State_Load(unsigned int ticks)
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_ov017_0218b5b0();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    Unknown_0202ae18* unk = func_0202ae18();
    unsigned char step = step_;
    if (step == 0)
    {
        flags_ |= RECORDS_BUSY;
        char* store = func_0205ec34();
        int noModel = func_0206dfb0(store, store + 0x8c, 0x113b);
        if (noModel)
        {
            flags_ |= RECORDS_NO_MODEL;
            flags_ &= ~RECORDS_TITLES;
        }
        PlayRecords records;
        func_020ac4c0(&records);
        if (records.lastClear_.title_ == 0)
        {
            if (func_0206dfb0(store, store + 0x8c, 0x796) && func_0202c508(unk))
                flags_ |= RECORDS_CLEARED;
        }
        else if (records.lastClear_.title_ != 0)
        {
            flags_ |= RECORDS_CLEAR_ITEM;
        }
        if (!IsFlagSet(RECORDS_TITLES))
        {
            if (!noModel)
                flags_ |= RECORDS_FADE;
            step_ = 2;
            if (mode_ == 1)
                step_ = 3;
            return;
        }
        if (IsFlagSet(RECORDS_CLEARED))
        {
            task_ = loader->QueueLoadFile(STRING(0, "data/scenario/title_clr.stb"), NULL);
        }
        else
        {
            char path[0x80];
            __clear(path, sizeof(path));
            TextList list;
            func_020727d8(&list);
            func_020727f8(&list, STRING(0x1c, "data/scenario/cmtFileTbl.bin"), 1000, path, 2);
            task_ = loader->QueueLoadFile(path, NULL);
            flags_ |= RECORDS_COMMENTS;
        }
        step_++;
    }
    else if (step == 1)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* script;
            unsigned int scriptSize;
            loader->GetLoadedFileByID(task_, &script, &scriptSize);
            titleAllocator_.Reset();
            titles_ = (TitleScript*)titleAllocator_.Allocate(0xd0);
            func_0209fe9c(titles_);
            func_0209fee4(titles_, &titleAllocator_, script, scriptSize);
            func_0209ff64(titles_, 100);
            do
            {
                func_0209ff6c(titles_);
            } while (!IsScriptDone(titles_));
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step == 2)
    {
        if (IsFlagSet(RECORDS_COMMENTS))
        {
            TitleScript* titles = titles_;
            if (titles->count_ > 0)
            {
                title_ = titles->ids_[0];
                comment_ = 1000;
                titleAllocator_.Reset();
                titles_ = NULL;
                flags_ &= ~RECORDS_TITLES;
                flags_ &= ~RECORDS_COMMENTS;
            }
            else
            {
                titleAllocator_.Reset();
                titles_ = NULL;
                flags_ &= ~RECORDS_COMMENTS;
                task_ = loader->QueueLoadFile(STRING(0x39, "data/scenario/title_gyalel.stb"), NULL);
                step_ = 1;
                return;
            }
        }
        void* music = func_02094a00();
        func_02094b40(music);
        func_02094b34(music, 0x6b, 0x1fc, 0, 0);
        step_++;
    }
    else if (step == 3)
    {
        void* music = func_02094a00();
        if (func_02094b4c(music))
        {
            BackgroundLoader::AddLockGlobal();
            BackgroundLoader::FreeAllocationsGlobal();
            unsigned int size;
            void* file = ExtractFileFromGP2(STRING(0x58, "data/bin/menu/str_jr.gp2"), STRING(0x71, "str_jr_<LG>.nat"),
                                            &size);
            textAllocator_.Reset();
            func_020dfec0(&texts_, &textAllocator_, file, size);
            BackgroundLoader::RemoveLockGlobal();
            if (mode_ != 0)
            {
                step_ = 5;
                return;
            }
            func_0204b11c(&backgrounds_[0], 0);
            backgrounds_[0].unk_1c_0_ = 0;
            backgrounds_[0].unk_1c_4_ = 1;
            func_0204b5b4(&backgrounds_[0], 3);
            func_0204b5e8(&backgrounds_[0], 0, 0);
            func_0204b12c(&backgrounds_[0], &allocator_);
            func_0204af38(&backgrounds_[0], 1, &allocator_);
            task_ = loader->QueueLoadFile(func_020e0434(&texts_, 0), NULL);
            step_++;
        }
    }
    else if (step == 4)
    {
        if (loader->GetTaskStatus(task_))
        {
            char name[4];
            void* archive;
            unsigned int archiveSize;
            loader->GetLoadedFileByID(task_, &archive, &archiveSize);
            int count = func_02046900(archive);
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(archive, i, name, &size);
                if (file != NULL)
                    func_0204b174(&backgrounds_[0], file, &allocator_, size);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            func_0204b8d0(&backgrounds_[0], 0, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
            func_0204b0e8(&backgrounds_[0], 0);
            step_++;
        }
    }
    else if (step == 5)
    {
        if (LoadBackgrounds(0))
        {
            if (mode_ == 0)
            {
                func_0205a444(renderer_);
                renderer_->unk_50 = 0;
                renderer_->SetSprites(sprites_, 0x12);
                renderer_->animations_ = animations_;
                for (int i = 0; i < 0x12; i++)
                    func_0205a198(&sprites_[i]);
                func_0205a234(animations_);
                const char* inner = func_020e0434(&texts_, 6);
                task_ = loader->QueueLoadFileInGP2(func_020e0434(&texts_, 5), inner, NULL);
                step_++;
                return;
            }
            step_ = 0xff;
        }
    }
    else if (step == 6)
    {
        if (loader->GetTaskStatus(task_))
        {
            char name[4];
            void* archive;
            unsigned int archiveSize;
            loader->GetLoadedFileByID(task_, &archive, &archiveSize);
            int count = func_02046900(archive);
            spriteAllocator_.Reset();
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(archive, i, name, &size);
                if (file != NULL)
                    func_0205a528(renderer_, file, size, &spriteAllocator_);
            }
            flags_ |= RECORDS_SPRITES;
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step == 7)
    {
        if (LoadIcon())
        {
            if (IsFlagSet(RECORDS_NO_MODEL))
                step_ = 9;
            else
                step_++;
        }
    }
    else if (step == 8)
    {
        char* vram = resources->unknown_2cc;
        func_0207df50(vram + 0x230);
        func_0207df90(vram + 0x230);
        BackgroundLoader::AddLockGlobal();
        unsigned int size = 0;
        if (LoadFileIntoMemory(func_020e0434(&texts_, 10), data_0211e33c, &size))
        {
            ObjectArchiveLoadInfo info;
            info.unk_0 = 0;
            info.unk_14 = 0;
            info.unk_18 = 0;
            info.packageID = 0;
            info.allocator = &modelAllocator_;
            info.fileData = data_0211e33c;
            info.unk_8 = size;
            info.unk_10 = 1;
            model_.LoadFromCCHROrCMOTArchive(&info, NULL);
            Vector3fix scale = sScale;
            model_.SetScale(&scale);
            Vector3fix position = sPosition;
            model_.SetPosition(position);
            Vector3fix rotation = sRotation;
            model_.rotation_ = rotation;
            model_.MaybeSetBCFGAnimation(0, 0);
        }
        BackgroundLoader::RemoveLockGlobal();
        func_0207dfac(vram + 0x230);
        func_020a2010(camera_);
        func_0202e5c0(camera_, 0, 0x8000, 0x40000);
        func_0202e5c8(camera_, 0, 0, 0);
        func_020a27a0(camera_);
        func_020100c4(gameState, camera_);
        step_++;
    }
    else if (step == 9)
    {
        if (!IsFlagSet(RECORDS_TITLES))
        {
            step_ = 0xff;
            return;
        }
        if (IsScriptDone(titles_))
        {
            if (titles_->count_ > 0)
            {
                short ids[50];
                func_020a13c4(titleTable_);
                func_020a13e4(titleTable_, &guideAllocator_, NULL, 0, 1);
                int count = titles_->count_;
                for (int i = 0; i < count; i++)
                    ids[i] = titles_->ids_[i];
                if (((GuideWindow*)titleTable_)->SetShown(ids, titles_->count_) & 1)
                    flags_ |= RECORDS_FIRST_GUIDE;
                short comment;
                if (!IsFlagSet(RECORDS_CLEARED))
                {
                    comment = 1000;
                }
                else
                {
                    GetClearRecords(gameState)->title_ = ids[0];
                    comment = 1001;
                    flags_ |= RECORDS_CLEAR_ITEM;
                }
                comment_ = comment;
                title_ = ids[0];
                titleAllocator_.Reset();
                titles_ = NULL;
                page_ = (GuidePage*)titleAllocator_.Allocate(sizeof(GuidePage));
                ClearPage(page_);
                SetPage(page_, func_020a15bc(titleTable_, ids[0]));
                GameObject* hero = GameState::GetInstance()->GetProtagonist();
                BackgroundLoader::AddLockGlobal();
                unsigned int size = 0;
                char gp2[0x40];
                char inner[0x20];
                __clear(gp2, sizeof(gp2));
                __clear(inner, sizeof(inner));
                sprintf(gp2, STRING(0x81, "data/bin/ttlname%d.gp2"), hero->partyData_->appearance_.female_);
                sprintf(inner, STRING(0x98, "ttlname%d_<LG>.nat"), hero->partyData_->appearance_.female_);
                void* file = ExtractFileFromGP2(gp2, inner, &size);
                if (file != NULL)
                    func_020e046c(page_->title_, file, size, ids[0]);
                BackgroundLoader::RemoveLockGlobal();
            }
            else
            {
                titleAllocator_.Reset();
                titles_ = NULL;
            }
            if (title_ <= 0)
            {
                short comment = func_0201081c(gameState);
                if (func_0202c540(unk))
                {
                    flags_ |= RECORDS_COMMENT;
                    comment = 0x3eb;
                }
                memset(text_, 0, 0x960);
                TextList list;
                func_020727d8(&list);
                func_020727f8(&list, STRING(0x1c, "data/scenario/cmtFileTbl.bin"), comment, text_, 2);
                if (func_020d3018(text_, STRING(0xab, "")) == 0)
                {
                    step_ = 0xff;
                    return;
                }
                task_ = loader->QueueLoadFile(text_, NULL);
                step_++;
                return;
            }
            step_ = 0xff;
        }
    }
    else if (step == 10)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* script;
            unsigned int scriptSize;
            loader->GetLoadedFileByID(task_, &script, &scriptSize);
            titleAllocator_.Reset();
            titles_ = (TitleScript*)titleAllocator_.Allocate(0xd0);
            func_0209fe9c(titles_);
            func_0209fee4(titles_, &titleAllocator_, script, scriptSize);
            func_0209ff64(titles_, 100);
            do
            {
                func_0209ff6c(titles_);
            } while (!IsScriptDone(titles_));
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
        }
    }
    else if (step == 11)
    {
        TitleScript* titles = titles_;
        if (titles->count_ > 0)
        {
            title_ = titles->ids_[0];
            comment_ = func_0201081c(gameState);
            if (IsFlagSet(RECORDS_COMMENT))
            {
                flags_ &= ~RECORDS_COMMENT;
                comment_ = 0x3ea;
                if (func_0202c540(unk))
                    comment_ = 0x3eb;
            }
            titleAllocator_.Reset();
            titles_ = NULL;
            step_ = 0xff;
            return;
        }
        if (IsFlagSet(RECORDS_COMMENT))
        {
            flags_ &= ~RECORDS_COMMENT;
            step_ = 0xff;
            return;
        }
        Unknown_0202ae18* unk2 = func_0202ae18();
        short comment = 0x3ea;
        if (func_0202b7d8() && func_0202c540(unk2))
            comment = 0x3eb;
        memset(text_, 0, 0x960);
        TextList list;
        func_020727d8(&list);
        func_020727f8(&list, STRING(0x1c, "data/scenario/cmtFileTbl.bin"), comment, text_, 2);
        task_ = loader->QueueLoadFile(text_, NULL);
        step_ = 10;
        flags_ |= RECORDS_COMMENT;
    }
    else if (step == 0xff)
    {
        WriteTimes(NULL);
        WriteTitle(NULL);
        WriteCounts(NULL);
        WriteMenu(NULL);
        for (int i = 0; i < 6; i++)
        {
            Canvas* canvas = func_0205d81c(&window_, i);
            if (canvas != NULL)
            {
                if (i != 4 && i != 5)
                    canvas->unk_c2 = 0;
                else
                    canvas->unk_c2 = 1;
            }
        }
        if (mode_ == 0)
        {
            char* vram = resources->unknown_2cc;
            MessageSystem* messages = func_020421a0();
            func_0207df50(vram + 0x5b0);
            func_0207df90(vram + 0x5b0);
            func_020432c4(messages);
            func_0207dfac(vram + 0x5b0);
            func_0209c3b4(data_02109bf4, 0x29);
            state_ = 3;
            step_ = 0;
            if (page_ == NULL)
            {
                flags_ &= ~RECORDS_BUSY;
                InitializeMenu();
                return;
            }
        }
        else
        {
            flags_ &= ~RECORDS_BUSY;
            state_ = 4;
            step_ = 0;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11GuideWindow8SetShownEPKsi(); // GuideWindow::SetShown
    void _ZN13BattleRecords10WriteTimesEP12ClearRecords(); // BattleRecords::WriteTimes
    void _ZN13BattleRecords10WriteTitleEP12ClearRecords(); // BattleRecords::WriteTitle
    void _ZN13BattleRecords11WriteCountsEP12ClearRecords(); // BattleRecords::WriteCounts
    void _ZN13BattleRecords14InitializeMenuEv(); // BattleRecords::InitializeMenu
    void _ZN13BattleRecords15LoadBackgroundsEi(); // BattleRecords::LoadBackgrounds
    void _ZN13BattleRecords8LoadIconEv(); // BattleRecords::LoadIcon
    void _ZN13BattleRecords9WriteMenuEP12ClearRecords(); // BattleRecords::WriteMenu
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN8Object3D21MaybeSetBCFGAnimationEii(); // Object3D::MaybeSetBCFGAnimation
    void _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE(); // Object3D::LoadFromCCHROrCMOTArchive
    void _ZN8Object3D8SetScaleEPK8Vector3i(); // Object3D::SetScale
    void _ZN8Vector3iaSERKS_(); // Vector3i::operator=
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState14GetProtagonistEv(); // GameState::GetProtagonist
}

asm void BattleRecords::State_Load(unsigned int ticks)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x2a0
    mov r4, r0
    bl _ZN9GameState11GetInstanceEv
    mov r6, r0
    bl func_ov017_0218b5b0
    mov r5, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r7, r0
    bl func_0202ae18
    ldrb r1, [r4, #0xb11]
    mov r8, r0
    cmp r1, #0x0
    bne @L02184be8
    ldr r0, [r4, #0xb18]
    orr r0, r0, #0x200000
    str r0, [r4, #0xb18]
    bl func_0205ec34
    mov r5, r0
    ldr r2, =0x113b
    add r1, r5, #0x8c
    bl func_0206dfb0
    movs r6, r0
    ldrne r0, [r4, #0xb18]
    orrne r0, r0, #0x80
    bicne r0, r0, #0x1
    strne r0, [r4, #0xb18]
    add r0, sp, #0x1f0
    bl func_020ac4c0
    add r0, sp, #0x280
    ldr r0, [r0, #0x10]
    movs r0, r0, lsr #0x17
    bne @L02184b04
    ldr r2, =0x796
    mov r0, r5
    add r1, r5, #0x8c
    bl func_0206dfb0
    cmp r0, #0x0
    beq @L02184b14
    mov r0, r8
    bl func_0202c508
    cmp r0, #0x0
    ldrne r0, [r4, #0xb18]
    orrne r0, r0, #0x2
    strne r0, [r4, #0xb18]
    b @L02184b14
@L02184b04:
    cmp r0, #0x0
    ldrne r0, [r4, #0xb18]
    orrne r0, r0, #0x4
    strne r0, [r4, #0xb18]
@L02184b14:
    ldr r0, [r4, #0xb18]
    tst r0, #0x1
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    bne @L02184b58
    cmp r6, #0x0
    ldreq r0, [r4, #0xb18]
    orreq r0, r0, #0x20000
    streq r0, [r4, #0xb18]
    mov r0, #0x2
    strb r0, [r4, #0xb11]
    ldr r0, [r4, #0xb24]
    cmp r0, #0x1
    moveq r0, #0x3
    streqb r0, [r4, #0xb11]
    b @L02185904
@L02184b58:
    ldr r0, [r4, #0xb18]
    tst r0, #0x2
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    beq @L02184b88
    ldr r1, =sStrings
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r4, #0xb20]
    b @L02184bd8
@L02184b88:
    add r0, sp, #0x170
    mov r1, #0x80
    bl __clear
    add r0, sp, #0x60
    bl func_020727d8
    mov r2, #0x2
    str r2, [sp, #0x0]
    ldr r1, =sStrings+0x1c
    add r0, sp, #0x60
    add r3, sp, #0x170
    mov r2, #0x3e8
    bl func_020727f8
    add r1, sp, #0x170
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r4, #0xb20]
    ldr r0, [r4, #0xb18]
    orr r0, r0, #0x400
    str r0, [r4, #0xb18]
@L02184bd8:
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02184be8:
    cmp r1, #0x1
    bne @L02184c90
    ldr r1, [r4, #0xb20]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02185904
    ldr r1, [r4, #0xb20]
    add r2, sp, #0x5c
    add r3, sp, #0x58
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r4, #0x78
    bl _ZN13SafeAllocator5ResetEv
    add r0, r4, #0x78
    mov r1, #0xd0
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r4, #0xb04]
    bl func_0209fe9c
    ldr r0, [r4, #0xb04]
    ldr r2, [sp, #0x5c]
    ldr r3, [sp, #0x58]
    add r1, r4, #0x78
    bl func_0209fee4
    ldr r0, [r4, #0xb04]
    mov r1, #0x64
    bl func_0209ff64
@L02184c54:
    ldr r0, [r4, #0xb04]
    bl func_0209ff6c
    ldr r0, [r4, #0xb04]
    bl IsScriptDone
    cmp r0, #0x0
    beq @L02184c54
    ldr r1, [r4, #0xb20]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r4, #0xb20]
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02184c90:
    cmp r1, #0x2
    bne @L02184d64
    ldr r0, [r4, #0xb18]
    tst r0, #0x400
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    beq @L02184d30
    ldr r1, [r4, #0xb04]
    ldrsh r0, [r1, #0x68]
    cmp r0, #0x0
    ble @L02184cf8
    ldrsh r2, [r1, #0x6a]
    add r1, r4, #0xb00
    add r0, r4, #0x78
    strh r2, [r1, #0x14]
    mov r2, #0x3e8
    strh r2, [r1, #0x16]
    bl _ZN13SafeAllocator5ResetEv
    mov r0, #0x0
    str r0, [r4, #0xb04]
    ldr r0, [r4, #0xb18]
    bic r0, r0, #0x1
    bic r0, r0, #0x400
    str r0, [r4, #0xb18]
    b @L02184d30
@L02184cf8:
    add r0, r4, #0x78
    bl _ZN13SafeAllocator5ResetEv
    mov r2, #0x0
    str r2, [r4, #0xb04]
    ldr r0, [r4, #0xb18]
    ldr r1, =sStrings+0x39
    bic r3, r0, #0x400
    mov r0, r7
    str r3, [r4, #0xb18]
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r4, #0xb20]
    mov r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02184d30:
    bl func_02094a00
    mov r5, r0
    bl func_02094b40
    mov r3, #0x0
    mov r0, r5
    str r3, [sp, #0x0]
    mov r1, #0x6b
    mov r2, #0x1fc
    bl func_02094b34
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02184d64:
    cmp r1, #0x3
    bne @L02184e58
    bl func_02094a00
    bl func_02094b4c
    cmp r0, #0x0
    beq @L02185904
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    ldr r0, =sStrings+0x58
    ldr r1, =sStrings+0x71
    add r2, sp, #0x54
    bl ExtractFileFromGP2
    mov r5, r0
    add r0, r4, #0x28
    bl _ZN13SafeAllocator5ResetEv
    ldr r3, [sp, #0x54]
    mov r2, r5
    add r0, r4, #0xa0
    add r1, r4, #0x28
    bl func_020dfec0
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    ldr r0, [r4, #0xb24]
    cmp r0, #0x0
    movne r0, #0x5
    strneb r0, [r4, #0xb11]
    bne @L02185904
    add r0, r4, #0xd0
    mov r1, #0x0
    bl func_0204b11c
    ldrb r2, [r4, #0xec]
    add r0, r4, #0xd0
    mov r1, #0x3
    bic r3, r2, #0xf
    and r2, r3, #0xff
    bic r2, r2, #0xf0
    orr r2, r2, #0x10
    strb r2, [r4, #0xec]
    bl func_0204b5b4
    mov r1, #0x0
    mov r2, r1
    add r0, r4, #0xd0
    bl func_0204b5e8
    mov r1, r4
    add r0, r4, #0xd0
    bl func_0204b12c
    add r0, r4, #0xd0
    mov r1, #0x1
    mov r2, r4
    bl func_0204af38
    add r0, r4, #0xa0
    mov r1, #0x0
    bl func_020e0434
    mov r1, r0
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r4, #0xb20]
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02184e58:
    cmp r1, #0x4
    bne @L02184f40
    ldr r1, [r4, #0xb20]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02185904
    ldr r1, [r4, #0xb20]
    add r2, sp, #0x4c
    add r3, sp, #0x48
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x4c]
    bl func_02046900
    mov r8, r0
    mov r9, #0x0
    add r6, sp, #0x50
    add r5, sp, #0x44
    b @L02184ed4
@L02184ea4:
    ldr r0, [sp, #0x4c]
    mov r1, r9
    mov r2, r6
    mov r3, r5
    bl func_020467f0
    movs r1, r0
    beq @L02184ed0
    ldr r3, [sp, #0x44]
    mov r2, r4
    add r0, r4, #0xd0
    bl func_0204b174
@L02184ed0:
    add r9, r9, #0x1
@L02184ed4:
    cmp r9, r8
    blt @L02184ea4
    ldr r1, [r4, #0xb20]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r5, #0x0
    mov r1, #0x0
    str r5, [r4, #0xb20]
    str r1, [sp, #0x0]
    str r1, [sp, #0x4]
    mov r0, #0x20
    str r0, [sp, #0x8]
    mov r0, #0x18
    mov r2, r1
    mov r3, r1
    str r0, [sp, #0xc]
    add r5, r5, #0x10000
    add r0, r4, #0xd0
    str r5, [sp, #0x10]
    bl func_0204b8d0
    add r0, r4, #0xd0
    mov r1, #0x0
    bl func_0204b0e8
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02184f40:
    cmp r1, #0x5
    bne @L02185014
    mov r0, r4
    mov r1, #0x0
    bl _ZN13BattleRecords15LoadBackgroundsEi
    cmp r0, #0x0
    beq @L02185904
    ldr r0, [r4, #0xb24]
    cmp r0, #0x0
    bne @L02185008
    ldr r0, [r4, #0x730]
    bl func_0205a444
    ldr r0, [r4, #0x730]
    mov r5, #0x0
    strb r5, [r0, #0x50]
    ldr r2, [r4, #0x734]
    ldr r1, [r4, #0x730]
    mov r0, #0x12
    str r2, [r1, #0x40]
    strh r0, [r1, #0x4c]
    ldr r1, [r4, #0x738]
    ldr r0, [r4, #0x730]
    mov r6, #0x28
    str r1, [r0, #0x3c]
    b @L02184fb4
@L02184fa4:
    ldr r0, [r4, #0x734]
    mla r0, r5, r6, r0
    bl func_0205a198
    add r5, r5, #0x1
@L02184fb4:
    cmp r5, #0x12
    blt @L02184fa4
    ldr r0, [r4, #0x738]
    bl func_0205a234
    add r0, r4, #0xa0
    mov r1, #0x6
    bl func_020e0434
    mov r5, r0
    add r0, r4, #0xa0
    mov r1, #0x5
    bl func_020e0434
    mov r2, r5
    mov r1, r0
    mov r0, r7
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r4, #0xb20]
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02185008:
    mov r0, #0xff
    strb r0, [r4, #0xb11]
    b @L02185904
@L02185014:
    cmp r1, #0x6
    bne @L021850d0
    ldr r1, [r4, #0xb20]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02185904
    ldr r1, [r4, #0xb20]
    add r2, sp, #0x3c
    add r3, sp, #0x38
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x3c]
    bl func_02046900
    mov r8, r0
    add r0, r4, #0x3c
    bl _ZN13SafeAllocator5ResetEv
    mov r9, #0x0
    add r6, sp, #0x40
    add r5, sp, #0x34
    b @L02185098
@L02185068:
    ldr r0, [sp, #0x3c]
    mov r1, r9
    mov r2, r6
    mov r3, r5
    bl func_020467f0
    movs r1, r0
    beq @L02185094
    ldr r0, [r4, #0x730]
    ldr r2, [sp, #0x34]
    add r3, r4, #0x3c
    bl func_0205a528
@L02185094:
    add r9, r9, #0x1
@L02185098:
    cmp r9, r8
    blt @L02185068
    ldr r1, [r4, #0xb18]
    mov r0, r7
    orr r1, r1, #0x80000
    str r1, [r4, #0xb18]
    ldr r1, [r4, #0xb20]
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r4, #0xb20]
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L021850d0:
    cmp r1, #0x7
    bne @L02185114
    mov r0, r4
    bl _ZN13BattleRecords8LoadIconEv
    cmp r0, #0x0
    beq @L02185904
    ldr r0, [r4, #0xb18]
    tst r0, #0x80
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    movne r0, #0x9
    strneb r0, [r4, #0xb11]
    ldreqb r0, [r4, #0xb11]
    addeq r0, r0, #0x1
    streqb r0, [r4, #0xb11]
    b @L02185904
@L02185114:
    cmp r1, #0x8
    bne @L02185278
    add r5, r5, #0x2cc
    add r0, r5, #0x230
    bl func_0207df50
    add r0, r5, #0x230
    bl func_0207df90
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r1, #0x0
    str r1, [sp, #0x30]
    add r0, r4, #0xa0
    mov r1, #0xa
    bl func_020e0434
    ldr r1, =data_0211e33c
    add r2, sp, #0x30
    bl LoadFileIntoMemory
    cmp r0, #0x0
    beq @L02185204
    ldr r7, [sp, #0x30]
    mov r2, #0x0
    ldr r8, =data_0211e33c
    add r9, r4, #0x64
    mov r3, #0x1
    add r1, sp, #0xec
    add r0, r4, #0x790
    str r2, [sp, #0xec]
    str r2, [sp, #0x100]
    str r2, [sp, #0x104]
    str r2, [sp, #0x108]
    str r9, [sp, #0xf8]
    str r8, [sp, #0xf0]
    str r7, [sp, #0xf4]
    str r3, [sp, #0xfc]
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    ldr r0, =sScale
    add r3, sp, #0xe0
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r1, r3
    add r0, r4, #0x790
    bl _ZN8Object3D8SetScaleEPK8Vector3i
    ldr r0, =sPosition
    add r3, sp, #0xd4
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, r4, #0x790
    mov r1, r3
    add r0, r0, #0x44
    bl _ZN8Vector3iaSERKS_
    ldr r0, =sRotation
    add r3, sp, #0xc8
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r1, r3
    add r0, r4, #0x7e0
    bl _ZN8Vector3iaSERKS_
    mov r1, #0x0
    add r0, r4, #0x790
    mov r2, r1
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
@L02185204:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, r5, #0x230
    bl func_0207dfac
    add r0, r4, #0x3c
    add r0, r0, #0x800
    bl func_020a2010
    add r0, r4, #0x3c
    add r0, r0, #0x800
    mov r1, #0x0
    mov r2, #0x8000
    mov r3, #0x40000
    bl func_0202e5c0
    add r0, r4, #0x3c
    add r0, r0, #0x800
    mov r1, #0x0
    mov r2, r1
    mov r3, r1
    bl func_0202e5c8
    add r0, r4, #0x3c
    add r0, r0, #0x800
    bl func_020a27a0
    mov r0, r6
    add r1, r4, #0x3c
    add r1, r1, #0x800
    bl func_020100c4
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L02185278:
    cmp r1, #0x9
    bne @L02185600
    ldr r0, [r4, #0xb18]
    tst r0, #0x1
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    moveq r0, #0xff
    streqb r0, [r4, #0xb11]
    beq @L02185904
    ldr r0, [r4, #0xb04]
    bl IsScriptDone
    cmp r0, #0x0
    beq @L02185904
    ldr r0, [r4, #0xb04]
    ldrsh r0, [r0, #0x68]
    cmp r0, #0x0
    ble @L02185534
    add r0, r4, #0xbc
    bl func_020a13c4
    mov r0, #0x1
    mov r2, #0x0
    str r0, [sp, #0x0]
    mov r3, r2
    add r0, r4, #0xbc
    add r1, r4, #0x8c
    bl func_020a13e4
    ldr r0, [r4, #0xb04]
    mov r5, #0x0
    ldrsh r2, [r0, #0x68]
    add r0, sp, #0x10c
    b @L02185310
@L021852f8:
    ldr r1, [r4, #0xb04]
    mov r3, r5, lsl #0x1
    add r1, r1, r5, lsl #0x1
    ldrsh r1, [r1, #0x6a]
    add r5, r5, #0x1
    strh r1, [r0, r3]
@L02185310:
    cmp r5, r2
    blt @L021852f8
    add r1, sp, #0x10c
    add r0, r4, #0xbc
    bl _ZN11GuideWindow8SetShownEPKsi
    tst r0, #0x1
    ldrne r0, [r4, #0xb18]
    orrne r0, r0, #0x8000
    strne r0, [r4, #0xb18]
    ldr r0, [r4, #0xb18]
    tst r0, #0x2
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    addeq r0, r4, #0xb00
    moveq r1, #0x3e8
    beq @L02185390
    add r0, r6, #0x104
    add r0, r0, #0x7400
    add r3, r0, #0xcc
    add r0, sp, #0x14
    ldr r2, [r3, #0x10]
    ldr r1, =0x7fffff
    ldrsh r0, [r0, #0xf8]
    and r2, r2, r1
    ldr r1, =0x3e9
    orr r0, r2, r0, lsl #0x17
    str r0, [r3, #0x10]
    ldr r2, [r4, #0xb18]
    add r0, r4, #0xb00
    orr r2, r2, #0x4
    str r2, [r4, #0xb18]
@L02185390:
    strh r1, [r0, #0x16]
    add r0, sp, #0x14
    ldrsh r2, [r0, #0xf8]
    add r1, r4, #0xb00
    add r0, r4, #0x78
    strh r2, [r1, #0x14]
    bl _ZN13SafeAllocator5ResetEv
    mov r0, #0x0
    str r0, [r4, #0xb04]
    add r0, r4, #0x78
    mov r1, #0x244
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, #0x200
    mov r5, r0
    str r0, [r4, #0xb0c]
    ldr r0, [r5, #0x0]
    rsb r1, r1, #0x0
    and r1, r0, r1
    ldr r0, =0xfffc01ff
    mov r2, #0x38
    and r1, r1, r0
    ldr r0, =0xf803ffff
    and r0, r1, r0
    bic r0, r0, #0x38000000
    bic r0, r0, #0xc0000000
    str r0, [r5, #0x0]
    mov r1, #0x0
    str r1, [r5, #0x4]
    add r0, r5, #0xc
    str r1, [r5, #0x8]
    bl memset
    add r0, r5, #0x44
    mov r1, #0x0
    mov r2, #0x200
    bl memset
    add r0, r5, #0x44
    str r0, [r5, #0x4]
    add r1, sp, #0x14
    ldrsh r1, [r1, #0xf8]
    add r0, r4, #0xbc
    bl func_020a15bc
    cmp r0, #0x0
    ldr r5, [r4, #0xb0c]
    beq @L02185494
    ldr r2, [r0, #0x0]
    add r1, r5, #0x44
    str r2, [r5, #0x0]
    ldr r2, [r0, #0x4]
    str r2, [r5, #0x4]
    ldr r2, [r0, #0x8]
    stmib r5, {r1, r2}
    ldr r9, [r0, #0x4]
    cmp r9, #0x0
    beq @L02185494
    mov r0, r1
    mov r1, #0x0
    mov r2, #0x200
    bl memset
    add r0, r5, #0x44
    bl func_020d2ff0
    add r3, r5, #0x44
    ldr r1, =sFormat
    mov r2, r9
    add r0, r3, r0
    bl sprintf
@L02185494:
    bl _ZN9GameState11GetInstanceEv
    bl _ZN9GameState14GetProtagonistEv
    mov r5, r0
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    mov r0, #0x0
    str r0, [sp, #0x2c]
    add r0, sp, #0x88
    mov r1, #0x40
    bl __clear
    add r0, sp, #0x68
    mov r1, #0x20
    bl __clear
    ldr r1, [r5, #0x150]
    add r0, sp, #0x88
    ldrb r2, [r1, #0x49c]
    ldr r1, =sStrings+0x81
    mov r2, r2, lsl #0x1f
    mov r2, r2, lsr #0x1f
    bl sprintf
    ldr r1, [r5, #0x150]
    add r0, sp, #0x68
    ldrb r2, [r1, #0x49c]
    ldr r1, =sStrings+0x98
    mov r2, r2, lsl #0x1f
    mov r2, r2, lsr #0x1f
    bl sprintf
    add r0, sp, #0x88
    add r1, sp, #0x68
    add r2, sp, #0x2c
    bl ExtractFileFromGP2
    movs r1, r0
    beq @L0218552c
    add r0, sp, #0x14
    ldr r5, [r4, #0xb0c]
    ldrsh r3, [r0, #0xf8]
    ldr r2, [sp, #0x2c]
    add r0, r5, #0xc
    bl func_020e046c
@L0218552c:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    b @L02185544
@L02185534:
    add r0, r4, #0x78
    bl _ZN13SafeAllocator5ResetEv
    mov r0, #0x0
    str r0, [r4, #0xb04]
@L02185544:
    add r0, r4, #0xb00
    ldrsh r0, [r0, #0x14]
    cmp r0, #0x0
    bgt @L021855f4
    mov r0, r6
    bl func_0201081c
    mov r5, r0
    mov r0, r8
    bl func_0202c540
    cmp r0, #0x0
    ldrne r0, [r4, #0xb18]
    mov r1, #0x0
    orrne r0, r0, #0x100
    strne r0, [r4, #0xb18]
    ldr r0, [r4, #0xb8]
    mov r2, #0x960
    ldrne r5, =0x3eb
    bl memset
    add r0, sp, #0x24
    bl func_020727d8
    mov r0, #0x2
    str r0, [sp, #0x0]
    mov r2, r5, lsl #0x10
    ldr r3, [r4, #0xb8]
    ldr r1, =sStrings+0x1c
    add r0, sp, #0x24
    mov r2, r2, asr #0x10
    bl func_020727f8
    ldr r0, [r4, #0xb8]
    ldr r1, =sStrings+0xab
    bl func_020d3018
    cmp r0, #0x0
    moveq r0, #0xff
    streqb r0, [r4, #0xb11]
    beq @L02185904
    ldr r1, [r4, #0xb8]
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r4, #0xb20]
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L021855f4:
    mov r0, #0xff
    strb r0, [r4, #0xb11]
    b @L02185904
@L02185600:
    cmp r1, #0xa
    bne @L021856a8
    ldr r1, [r4, #0xb20]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02185904
    ldr r1, [r4, #0xb20]
    add r2, sp, #0x20
    add r3, sp, #0x1c
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r4, #0x78
    bl _ZN13SafeAllocator5ResetEv
    add r0, r4, #0x78
    mov r1, #0xd0
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r4, #0xb04]
    bl func_0209fe9c
    ldr r0, [r4, #0xb04]
    ldr r2, [sp, #0x20]
    ldr r3, [sp, #0x1c]
    add r1, r4, #0x78
    bl func_0209fee4
    ldr r0, [r4, #0xb04]
    mov r1, #0x64
    bl func_0209ff64
@L0218566c:
    ldr r0, [r4, #0xb04]
    bl func_0209ff6c
    ldr r0, [r4, #0xb04]
    bl IsScriptDone
    cmp r0, #0x0
    beq @L0218566c
    ldr r1, [r4, #0xb20]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r4, #0xb20]
    ldrb r0, [r4, #0xb11]
    add r0, r0, #0x1
    strb r0, [r4, #0xb11]
    b @L02185904
@L021856a8:
    cmp r1, #0xb
    bne @L021857f8
    ldr r1, [r4, #0xb04]
    ldrsh r0, [r1, #0x68]
    cmp r0, #0x0
    ble @L02185740
    ldrsh r2, [r1, #0x6a]
    add r1, r4, #0xb00
    mov r0, r6
    strh r2, [r1, #0x14]
    bl func_0201081c
    add r1, r4, #0xb00
    strh r0, [r1, #0x16]
    ldr r0, [r4, #0xb18]
    tst r0, #0x100
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    beq @L02185724
    ldr r0, [r4, #0xb18]
    ldr r2, =0x3ea
    bic r1, r0, #0x100
    str r1, [r4, #0xb18]
    add r1, r4, #0xb00
    mov r0, r8
    strh r2, [r1, #0x16]
    bl func_0202c540
    cmp r0, #0x0
    ldrne r1, =0x3eb
    addne r0, r4, #0xb00
    strneh r1, [r0, #0x16]
@L02185724:
    add r0, r4, #0x78
    bl _ZN13SafeAllocator5ResetEv
    mov r0, #0x0
    str r0, [r4, #0xb04]
    mov r0, #0xff
    strb r0, [r4, #0xb11]
    b @L02185904
@L02185740:
    ldr r0, [r4, #0xb18]
    tst r0, #0x100
    movne r0, #0x1
    moveq r0, #0x0
    cmp r0, #0x0
    beq @L02185770
    ldr r1, [r4, #0xb18]
    mov r0, #0xff
    bic r1, r1, #0x100
    str r1, [r4, #0xb18]
    strb r0, [r4, #0xb11]
    b @L02185904
@L02185770:
    bl func_0202ae18
    mov r5, r0
    ldr r6, =0x3ea
    bl func_0202b7d8
    cmp r0, #0x0
    beq @L02185798
    mov r0, r5
    bl func_0202c540
    cmp r0, #0x0
    addne r6, r6, #0x1
@L02185798:
    ldr r0, [r4, #0xb8]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    add r0, sp, #0x14
    bl func_020727d8
    mov r0, #0x2
    str r0, [sp, #0x0]
    ldr r3, [r4, #0xb8]
    ldr r1, =sStrings+0x1c
    add r0, sp, #0x14
    mov r2, r6
    bl func_020727f8
    ldr r1, [r4, #0xb8]
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r4, #0xb20]
    mov r0, #0xa
    strb r0, [r4, #0xb11]
    ldr r0, [r4, #0xb18]
    orr r0, r0, #0x100
    str r0, [r4, #0xb18]
    b @L02185904
@L021857f8:
    cmp r1, #0xff
    bne @L02185904
    mov r0, r4
    mov r1, #0x0
    bl _ZN13BattleRecords10WriteTimesEP12ClearRecords
    mov r0, r4
    mov r1, #0x0
    bl _ZN13BattleRecords10WriteTitleEP12ClearRecords
    mov r0, r4
    mov r1, #0x0
    bl _ZN13BattleRecords11WriteCountsEP12ClearRecords
    mov r0, r4
    mov r1, #0x0
    bl _ZN13BattleRecords9WriteMenuEP12ClearRecords
    mov r8, #0x0
    mov r6, r8
    mov r7, #0x1
    b @L02185868
@L02185840:
    add r0, r4, #0x130
    and r1, r8, #0xff
    bl func_0205d81c
    cmp r0, #0x0
    beq @L02185864
    cmp r8, #0x4
    cmpne r8, #0x5
    streqh r7, [r0, #0xc2]
    strneh r6, [r0, #0xc2]
@L02185864:
    add r8, r8, #0x1
@L02185868:
    cmp r8, #0x6
    blt @L02185840
    ldr r0, [r4, #0xb24]
    cmp r0, #0x0
    bne @L021858e8
    add r6, r5, #0x2cc
    bl func_020421a0
    mov r5, r0
    add r0, r6, #0x5b0
    bl func_0207df50
    add r0, r6, #0x5b0
    bl func_0207df90
    mov r0, r5
    bl func_020432c4
    add r0, r6, #0x5b0
    bl func_0207dfac
    ldr r0, =data_02109bf4
    mov r1, #0x29
    bl func_0209c3b4
    mov r0, #0x3
    strb r0, [r4, #0xb10]
    mov r0, #0x0
    strb r0, [r4, #0xb11]
    ldr r0, [r4, #0xb0c]
    cmp r0, #0x0
    bne @L02185904
    ldr r1, [r4, #0xb18]
    mov r0, r4
    bic r1, r1, #0x200000
    str r1, [r4, #0xb18]
    bl _ZN13BattleRecords14InitializeMenuEv
    b @L02185904
@L021858e8:
    ldr r1, [r4, #0xb18]
    mov r0, #0x4
    bic r1, r1, #0x200000
    str r1, [r4, #0xb18]
    strb r0, [r4, #0xb10]
    mov r0, #0x0
    strb r0, [r4, #0xb11]
@L02185904:
    add sp, sp, #0x2a0
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

// The script of the titles is done
static int IsScriptDone(TitleScript* script)
{
    int done1 = script->unk_60 == -1 ? 1 : 0;
    int done2 = script->unk_64 == -1 ? 1 : 0;
    if (done1 & done2)
        return 1;
    return 0;
}

void BattleRecords::State_Setup(unsigned int ticks)
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    BackgroundLoader::GetInstance();
    unsigned char step = step_;
    if (step == 0 && !IsBrightnessTransitionActive(resources))
        step_++;
    if (step != 1)
        return;
    func_020dc2bc();
    REG_BG0CNT_SUB = (REG_BG0CNT_SUB & 0x43) | 0x600;
    REG_BG1CNT_SUB = (REG_BG1CNT_SUB & 0x43) | 0x704;
    REG_BG0CNT_SUB = (REG_BG0CNT_SUB & ~3) | 2;
    REG_BG1CNT_SUB = (REG_BG1CNT_SUB & ~3) | 3;
    REG_BG2CNT_SUB = (REG_BG2CNT_SUB & ~3) | 1;
    REG_BG3CNT_SUB = REG_BG3CNT_SUB & ~3;
    REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1300;
    state_ = 0;
    step_ = 0;
}

static inline void SetGuideUnk400(GuideWindow* guide, int set)
{
    if (set)
        guide->flags_ |= GUIDE_WINDOW_UNK_400;
    else
        guide->flags_ &= ~GUIDE_WINDOW_UNK_400;
}

static inline void SetGuideUnk800(GuideWindow* guide, int set)
{
    if (set)
        guide->flags_ |= GUIDE_WINDOW_UNK_800;
    else
        guide->flags_ &= ~GUIDE_WINDOW_UNK_800;
}

void BattleRecords::State_Guide(unsigned int ticks)
{
    MessageSystem* messages = func_020421a0();
    GameResources* resources = func_ov017_0218b5b0();
    BackgroundLoader::GetInstance();
    void* music = func_02094a00();
    unsigned char step = step_;
    if (step >= 2)
        messages->unk_19ae = 0;
    if (step == 0)
    {
        if (messages->unk_9a0 != 3)
            return;
        step_++;
    }
    if (step == 1 && (func_02012444(data_02114e30, 0xff3) || data_02114e54.touching_))
        step_++;
    if (step == 2)
    {
        guide_ = (GuideWindow*)titleAllocator_.Allocate(sizeof(GuideWindow));
        guide_->Initialize(0);
        guide_->CreateAllocators(&titleAllocator_);
        guide_->SetPages(page_, 1);
        SetGuideUnk400(guide_, IsFlagSet(RECORDS_FIRST_GUIDE));
        SetGuideUnk800(guide_, IsFlagSet(RECORDS_CLEARED));
        step_++;
    }
    if (step == 3 && (guide_->flags_ & GUIDE_WINDOW_MESSAGE_WINDOW))
        step_++;
    if (step == 4)
    {
        guide_->Finish();
        titleAllocator_.Reset();
        guide_ = NULL;
        page_ = NULL;
        flags_ &= ~RECORDS_BUSY;
        InitializeMenu();
        int flags = flags_;
        if ((flags & RECORDS_FIRST_GUIDE) || (flags & RECORDS_CLEARED))
            flags_ &= ~RECORDS_SHOWN;
        flags_ &= ~RECORDS_FIRST_GUIDE;
        step_++;
    }
    if (step == 5)
    {
        func_0205d6a0(&window_, 1);
        func_02094b40(music);
        func_02094b34(music, 0x6b, 0x1fc, 0, 0);
        step_++;
    }
    if (step == 6)
    {
        if (!func_02094b4c(music))
            return;
        if (LoadIcon())
        {
            step_++;
            step++;
        }
    }
    if (step == 7 && LoadBackgrounds(0))
    {
        SetMainBrightness(resources, 0, 0xf);
        WriteTimes(NULL);
        WriteTitle(NULL);
        WriteCounts(NULL);
        WriteMenu(NULL);
        for (int i = 0; i < 6; i++)
        {
            Canvas* canvas = func_0205d81c(&window_, i);
            if (canvas != NULL)
                canvas->unk_c2 = 0;
        }
        step_++;
    }
    if (step == 8 && !IsBrightnessTransitionActive(resources))
    {
        flags_ |= RECORDS_ITEM_4;
        InitializeItems();
        state_ = 3;
        step_ = 0;
        flags_ |= RECORDS_FADE;
        if (flags_ & RECORDS_CLEARED)
            kind_ = 7;
        InitializeMenu();
        step_ = 1;
    }
}

void BattleRecords::State_Main(unsigned int ticks)
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    MessageSystem* messages = func_020421a0();
    if (messages->busy_ != 0)
        messages->unk_19ae = 0;
    signed char step = step_;
    if (step == 0)
    {
        InitializeMenu();
        step_++;
    }
    if (step == 1)
    {
        if (IsFlagSet(RECORDS_FADE) && IsFlagSet(RECORDS_SHOWN))
        {
            if (messages->unk_9a0 != 3)
                return;
            flags_ &= ~RECORDS_FADE;
        }
        if (IsFlagSet(RECORDS_FADE))
            step++;
        else
            SetBrightness(resources, 0, 0xf);
        step_++;
    }
    if (step == 2)
    {
        if (IsBrightnessTransitionActive(resources))
            return;
        if (!IsFlagSet(RECORDS_NO_MODEL))
        {
            int shown = 1;
            messages->busy_ = 1;
            if (title_ > 0)
            {
                if (!(flags_ & RECORDS_SHOWN))
                    shown = 0;
                if (!shown)
                {
                    if (IsFlagSet(RECORDS_TITLES) && !IsFlagSet(RECORDS_FIRST_GUIDE))
                    {
                        PlayRecords records;
                        func_020ac4c0(&records);
                        func_020a05d8(&records, 1);
                        func_020ac494(&records);
                    }
                    memset(text_, 0, 0x960);
                    char* path = text_;
                    char* inner = path + 0x80;
                    char* comment = path + 0x100;
                    BackgroundLoader::AddLockGlobal();
                    TextList list;
                    unsigned int size;
                    void* file = LoadFileIntoMemory(STRING(0x1c, "data/scenario/cmtFileTbl.bin"), data_0211e33c, &size);
                    if (file != NULL)
                    {
                        func_020727d8(&list);
                        func_02072928(&list, file, size, comment_, path, 0);
                        func_020727d8(&list);
                        func_02072928(&list, file, size, comment_, inner, 1);
                    }
                    file = ExtractFileFromGP2(path, inner, &size);
                    if (file != NULL)
                    {
                        PartyMember* member = func_0200ff1c(gameState, func_020100a8(gameState));
                        func_020727d8(&list);
                        int female = member->data_->appearance_.female_;
                        func_02072928(&list, file, size, title_, comment, female);
                    }
                    BackgroundLoader::RemoveLockGlobal();
                    func_02042058(comment, func_020e0434(&texts_, 1000));
                    func_0204500c(messages, comment, 0, 0xe3);
                    messages->unk_19b2 = 1;
                    messages->unk_19c8 = 1;
                    messages->unk_99c = 2;
                    if (page_ != NULL)
                    {
                        flags_ |= RECORDS_SHOWN;
                        state_ = 2;
                        step_ = 0;
                        return;
                    }
                }
            }
            else
            {
                if (!(flags_ & RECORDS_SHOWN))
                    shown = 0;
                if (!shown)
                {
                    func_0204500c(messages, func_020e0434(&texts_, 10000), 0, 0xe3);
                    messages->unk_19b2 = 1;
                    messages->unk_19c8 = 1;
                    messages->unk_99c = 2;
                }
            }
            if (IsFlagSet(RECORDS_FADE))
            {
                messages->unk_19c5 = 1;
                messages->unk_19b2 = 0;
                flags_ |= RECORDS_SHOWN;
                step_ = 1;
                return;
            }
            flags_ |= RECORDS_MENU;
        }
        flags_ |= RECORDS_CURSOR;
        step_++;
    }
    if (step == 3)
    {
        int result = UpdateMenu(ticks);
        int selected = func_0205bb84(&cursor_);
        SCROLL_TO(selected);
        unsigned char kind = items_[selected];
        if (func_02012444(data_02114e30, 0x401) || result == 1)
        {
            if (!func_0202c540(func_0202ae18()) || kind != 5)
            {
                func_0205eaa0(data_02108760, 1, 0);
                state_ = kind + 5;
                step_ = 0;
                flags_ &= ~RECORDS_CURSOR;
                flags_ &= ~RECORDS_MENU;
                return;
            }
        }
        else if (func_02012444(data_02114e30, 0x806) || result == -2)
        {
            state_ = 13;
            step_ = 0;
            flags_ &= ~RECORDS_CURSOR;
            flags_ &= ~RECORDS_MENU;
        }
    }
}

void BattleRecords::State_FadeOut(unsigned int ticks)
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    func_020421a0();
    if (step_ != 0)
        return;
    SetBrightness(resources, 0, 0xf);
    step_++;
}

void BattleRecords::State_Exit1(unsigned int ticks)
{
    exit_ = 1;
    state_ = 13;
    step_ = 0;
}

void BattleRecords::State_Exit2(unsigned int ticks)
{
    exit_ = 2;
    state_ = 13;
    step_ = 0;
}

void BattleRecords::State_Exit5(unsigned int ticks)
{
    exit_ = 5;
    state_ = 13;
    step_ = 0;
}

void BattleRecords::State_Exit7(unsigned int ticks)
{
    exit_ = 7;
    state_ = 13;
    step_ = 0;
}

void BattleRecords::State_Exit4(unsigned int ticks)
{
    exit_ = 4;
    state_ = 13;
    step_ = 0;
}

void BattleRecords::State_Exit3(unsigned int ticks)
{
    exit_ = 3;
    state_ = 13;
    step_ = 0;
}

void BattleRecords::State_Exit6(unsigned int ticks)
{
    exit_ = 6;
    state_ = 13;
    step_ = 0;
}

// NONMATCHING: the C matches 87.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void BattleRecords::State_LastClear(unsigned int ticks)
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    BackgroundLoader::GetInstance();
    MessageSystem* messages = func_020421a0();
    messages->unk_19ae = 0;
    unsigned char step = step_;
    ClearRecords* records = GetClearRecords(gameState);
    if (step == 0)
    {
        SetSubBrightness(resources, -0x10, 0xf);
        step_++;
        step++;
    }
    if (step == 1 && LoadBackgrounds(1))
    {
        WriteTimes(records);
        WriteTitle(records);
        WriteCounts(records);
        WriteMenu(records);
        for (int i = 0; i < 5; i++)
        {
            Canvas* canvas = func_0205d81c(&window_, i);
            if (canvas != NULL)
                canvas->unk_c2 = 0;
        }
        flags_ |= RECORDS_ICON;
        step_++;
    }
    if (step == 2)
    {
        SetSubBrightness(resources, 0, 0xf);
        step_++;
    }
    if (step == 3)
    {
        if (IsBrightnessTransitionActive(resources))
            return;
        if (title_ != records->title_)
        {
            memset(text_, 0, 0x960);
            char* path = text_;
            char* inner = path + 0x80;
            char* comment = path + 0x100;
            BackgroundLoader::AddLockGlobal();
            TextList list;
            unsigned int size;
            void* file = LoadFileIntoMemory(STRING(0x1c, "data/scenario/cmtFileTbl.bin"), data_0211e33c, &size);
            if (file != NULL)
            {
                func_020727d8(&list);
                func_02072928(&list, file, size, 0x3e9, path, 0);
                func_020727d8(&list);
                func_02072928(&list, file, size, 0x3e9, inner, 1);
            }
            file = ExtractFileFromGP2(path, inner, &size);
            if (file != NULL)
            {
                PartyMember* member = func_0200ff1c(gameState, func_020100a8(gameState));
                func_020727d8(&list);
                int female = member->data_->appearance_.female_;
                func_02072928(&list, file, size, (short)records->title_, comment, female);
            }
            BackgroundLoader::RemoveLockGlobal();
            func_02042058(comment, func_020e0434(&texts_, 1000));
            func_0204500c(messages, comment, 0, 0xe3);
            int shown = 1;
            messages->unk_19b2 = 1;
            messages->unk_19c8 = 1;
            messages->unk_99c = 2;
            if (!(flags_ & RECORDS_TITLE_SHOWN))
                shown = 0;
            if (shown)
            {
                messages->unk_19c5 = 1;
                messages->unk_19b2 = 0;
            }
            else
            {
                messages->unk_19c5 = 0;
            }
            flags_ |= RECORDS_TITLE_SHOWN;
        }
        step_++;
        step++;
    }
    if (step == 4)
    {
        if (messages->unk_9a0 != 3)
            return;
        int close = 0;
        if (func_02012444(data_02114e30, 0x403))
            close = 1;
        int x;
        int y;
        func_02012a84(&data_02114e54, &x, &y);
        if (data_02114e54.touching_)
        {
            int item = GetTouchedItem(x, y);
            if (item == -2)
                close = 1;
            if (items_[item] == 7)
                close = 1;
        }
        if (close)
        {
            func_0205eaa0(data_02108760, 1, 0);
            step_++;
        }
    }
    if (step == 5)
    {
        SetSubBrightness(resources, -0x10, 0xf);
        step_++;
    }
    if (step == 6 && LoadBackgrounds(0))
    {
        WriteTimes(NULL);
        WriteTitle(NULL);
        WriteCounts(NULL);
        WriteMenu(NULL);
        for (int i = 0; i < 6; i++)
        {
            Canvas* canvas = func_0205d81c(&window_, i);
            if (canvas != NULL)
                canvas->unk_c2 = 0;
        }
        flags_ &= ~RECORDS_ICON;
        step_++;
    }
    if (step == 7)
    {
        SetSubBrightness(resources, 0, 0xf);
        step_++;
    }
    if (step == 8 && !IsBrightnessTransitionActive(resources))
    {
        int flags = flags_;
        if (title_ == records->title_)
            flags_ = flags | RECORDS_SHOWN;
        else
            flags_ = (flags | RECORDS_FADE) & ~RECORDS_SHOWN;
        state_ = 3;
        step_ = 2;
        InitializeMenu();
        for (int i = 0; i < itemCount_; i++)
        {
            if (items_[i] == 7)
            {
                func_0205bb04(&cursor_, i);
                SCROLL_TO(i);
                return;
            }
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13BattleRecords10WriteTimesEP12ClearRecords(); // BattleRecords::WriteTimes
    void _ZN13BattleRecords10WriteTitleEP12ClearRecords(); // BattleRecords::WriteTitle
    void _ZN13BattleRecords11WriteCountsEP12ClearRecords(); // BattleRecords::WriteCounts
    void _ZN13BattleRecords14GetTouchedItemEii(); // BattleRecords::GetTouchedItem
    void _ZN13BattleRecords14InitializeMenuEv(); // BattleRecords::InitializeMenu
    void _ZN13BattleRecords15LoadBackgroundsEi(); // BattleRecords::LoadBackgrounds
    void _ZN13BattleRecords9WriteMenuEP12ClearRecords(); // BattleRecords::WriteMenu
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void BattleRecords::State_LastClear(unsigned int ticks)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x24
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    str r0, [sp, #0x8]
    bl func_0200fb8c
    mov r4, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    bl func_020421a0
    mov r5, r0
    ldr r0, [sp, #0x8]
    mov r1, #0x0
    add r0, r0, #0x104
    add r2, r0, #0x7400
    add r0, r5, #0x1000
    strb r1, [r0, #0x9ae]
    ldrb r7, [r10, #0xb11]
    add r6, r2, #0xcc
    cmp r7, #0x0
    bne @L021863fc
    mov r0, r4
    sub r1, r1, #0x10
    mov r2, #0xf
    bl SetSubBrightness
    ldrb r1, [r10, #0xb11]
    add r0, r7, #0x1
    and r7, r0, #0xff
    add r0, r1, #0x1
    strb r0, [r10, #0xb11]
@L021863fc:
    cmp r7, #0x1
    bne @L0218648c
    mov r0, r10
    mov r1, #0x1
    bl _ZN13BattleRecords15LoadBackgroundsEi
    cmp r0, #0x0
    beq @L0218648c
    mov r0, r10
    mov r1, r6
    bl _ZN13BattleRecords10WriteTimesEP12ClearRecords
    mov r0, r10
    mov r1, r6
    bl _ZN13BattleRecords10WriteTitleEP12ClearRecords
    mov r0, r10
    mov r1, r6
    bl _ZN13BattleRecords11WriteCountsEP12ClearRecords
    mov r0, r10
    mov r1, r6
    bl _ZN13BattleRecords9WriteMenuEP12ClearRecords
    mov r9, #0x0
    mov r8, r9
    b @L0218646c
@L02186454:
    add r0, r10, #0x130
    and r1, r9, #0xff
    bl func_0205d81c
    cmp r0, #0x0
    strneh r8, [r0, #0xc2]
    add r9, r9, #0x1
@L0218646c:
    cmp r9, #0x5
    blt @L02186454
    ldr r0, [r10, #0xb18]
    orr r0, r0, #0x10000
    str r0, [r10, #0xb18]
    ldrb r0, [r10, #0xb11]
    add r0, r0, #0x1
    strb r0, [r10, #0xb11]
@L0218648c:
    cmp r7, #0x2
    bne @L021864b0
    mov r0, r4
    mov r1, #0x0
    mov r2, #0xf
    bl SetSubBrightness
    ldrb r0, [r10, #0xb11]
    add r0, r0, #0x1
    strb r0, [r10, #0xb11]
@L021864b0:
    cmp r7, #0x3
    bne @L02186664
    mov r0, r4
    bl IsBrightnessTransitionActive
    cmp r0, #0x0
    bne @L02186884
    add r0, r10, #0xb00
    ldrsh r1, [r0, #0x14]
    ldr r0, [r6, #0x10]
    cmp r1, r0, lsr #0x17
    beq @L02186650
    ldr r0, [r10, #0xb8]
    mov r1, #0x0
    mov r2, #0x960
    bl memset
    ldr r11, [r10, #0xb8]
    add r8, r11, #0x80
    add r9, r11, #0x100
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    ldr r0, =sStrings+0x1c
    ldr r1, =data_0211e33c
    add r2, sp, #0x18
    bl LoadFileIntoMemory
    str r0, [sp, #0xc]
    cmp r0, #0x0
    beq @L02186568
    add r0, sp, #0x1c
    bl func_020727d8
    str r11, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    ldr r1, [sp, #0xc]
    ldr r2, [sp, #0x18]
    ldr r3, =0x3e9
    add r0, sp, #0x1c
    bl func_02072928
    add r0, sp, #0x1c
    bl func_020727d8
    mov r0, #0x1
    str r8, [sp, #0x0]
    str r0, [sp, #0x4]
    add r3, r0, #0x3e8
    ldr r1, [sp, #0xc]
    ldr r2, [sp, #0x18]
    add r0, sp, #0x1c
    bl func_02072928
@L02186568:
    add r2, sp, #0x18
    mov r0, r11
    mov r1, r8
    bl ExtractFileFromGP2
    movs r11, r0
    beq @L021865d0
    ldr r0, [sp, #0x8]
    bl func_020100a8
    mov r1, r0
    ldr r0, [sp, #0x8]
    bl func_0200ff1c
    mov r8, r0
    add r0, sp, #0x1c
    bl func_020727d8
    ldr r0, [r8, #0x150]
    mov r1, r11
    ldrb r2, [r0, #0x49c]
    add r0, sp, #0x1c
    mov r2, r2, lsl #0x1f
    mov r2, r2, lsr #0x1f
    str r9, [sp, #0x0]
    str r2, [sp, #0x4]
    ldr r3, [r6, #0x10]
    ldr r2, [sp, #0x18]
    mov r3, r3, lsr #0x17
    bl func_02072928
@L021865d0:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, r10, #0xa0
    mov r1, #0x3e8
    bl func_020e0434
    mov r1, r0
    mov r0, r9
    bl func_02042058
    mov r1, r9
    mov r0, r5
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r1, #0x1
    add r0, r5, #0x1000
    strb r1, [r0, #0x9b2]
    strb r1, [r0, #0x9c8]
    mov r0, #0x2
    str r0, [r5, #0x99c]
    ldr r0, [r10, #0xb18]
    tst r0, #0x40000
    moveq r1, #0x0
    cmp r1, #0x0
    add r0, r5, #0x1000
    movne r1, #0x1
    strneb r1, [r0, #0x9c5]
    movne r1, #0x0
    strneb r1, [r0, #0x9b2]
    moveq r1, #0x0
    streqb r1, [r0, #0x9c5]
    ldr r0, [r10, #0xb18]
    orr r0, r0, #0x40000
    str r0, [r10, #0xb18]
@L02186650:
    ldrb r1, [r10, #0xb11]
    add r0, r7, #0x1
    and r7, r0, #0xff
    add r0, r1, #0x1
    strb r0, [r10, #0xb11]
@L02186664:
    cmp r7, #0x4
    bne @L02186700
    ldr r0, [r5, #0x9a0]
    cmp r0, #0x3
    bne @L02186884
    ldr r0, =data_02114e30
    ldr r1, =0x403
    mov r5, #0x0
    bl func_02012444
    cmp r0, #0x0
    ldr r0, =data_02114e54
    add r1, sp, #0x14
    add r2, sp, #0x10
    movne r5, #0x1
    bl func_02012a84
    ldr r0, =data_02114e54
    ldrb r0, [r0, #0x55]
    cmp r0, #0x0
    beq @L021866dc
    ldr r1, [sp, #0x14]
    ldr r2, [sp, #0x10]
    mov r0, r10
    bl _ZN13BattleRecords14GetTouchedItemEii
    mvn r1, #0x1
    cmp r0, r1
    add r0, r10, r0
    ldrb r0, [r0, #0x744]
    moveq r5, #0x1
    cmp r0, #0x7
    moveq r5, #0x1
@L021866dc:
    cmp r5, #0x0
    beq @L02186700
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
    ldrb r0, [r10, #0xb11]
    add r0, r0, #0x1
    strb r0, [r10, #0xb11]
@L02186700:
    cmp r7, #0x5
    bne @L02186724
    mov r0, r4
    mvn r1, #0xf
    mov r2, #0xf
    bl SetSubBrightness
    ldrb r0, [r10, #0xb11]
    add r0, r0, #0x1
    strb r0, [r10, #0xb11]
@L02186724:
    cmp r7, #0x6
    bne @L021867b4
    mov r0, r10
    mov r1, #0x0
    bl _ZN13BattleRecords15LoadBackgroundsEi
    cmp r0, #0x0
    beq @L021867b4
    mov r0, r10
    mov r1, #0x0
    bl _ZN13BattleRecords10WriteTimesEP12ClearRecords
    mov r0, r10
    mov r1, #0x0
    bl _ZN13BattleRecords10WriteTitleEP12ClearRecords
    mov r0, r10
    mov r1, #0x0
    bl _ZN13BattleRecords11WriteCountsEP12ClearRecords
    mov r0, r10
    mov r1, #0x0
    bl _ZN13BattleRecords9WriteMenuEP12ClearRecords
    mov r8, #0x0
    mov r5, r8
    b @L02186794
@L0218677c:
    add r0, r10, #0x130
    and r1, r8, #0xff
    bl func_0205d81c
    cmp r0, #0x0
    strneh r5, [r0, #0xc2]
    add r8, r8, #0x1
@L02186794:
    cmp r8, #0x6
    blt @L0218677c
    ldr r0, [r10, #0xb18]
    bic r0, r0, #0x10000
    str r0, [r10, #0xb18]
    ldrb r0, [r10, #0xb11]
    add r0, r0, #0x1
    strb r0, [r10, #0xb11]
@L021867b4:
    cmp r7, #0x7
    bne @L021867d8
    mov r0, r4
    mov r1, #0x0
    mov r2, #0xf
    bl SetSubBrightness
    ldrb r0, [r10, #0xb11]
    add r0, r0, #0x1
    strb r0, [r10, #0xb11]
@L021867d8:
    cmp r7, #0x8
    bne @L02186884
    mov r0, r4
    bl IsBrightnessTransitionActive
    cmp r0, #0x0
    bne @L02186884
    add r0, r10, #0xb00
    ldrsh r1, [r0, #0x14]
    ldr r0, [r6, #0x10]
    cmp r1, r0, lsr #0x17
    ldr r0, [r10, #0xb18]
    mov r1, #0x3
    orreq r0, r0, #0x200
    orrne r0, r0, #0x20000
    bicne r0, r0, #0x200
    str r0, [r10, #0xb18]
    strb r1, [r10, #0xb10]
    mov r1, #0x2
    mov r0, r10
    strb r1, [r10, #0xb11]
    bl _ZN13BattleRecords14InitializeMenuEv
    mov r4, #0x0
    b @L02186878
@L02186834:
    add r0, r10, r4
    ldrb r0, [r0, #0x744]
    cmp r0, #0x7
    bne @L02186874
    mov r1, r4
    add r0, r10, #0x750
    bl func_0205bb04
    ldrb r0, [r10, #0xb29]
    add r1, r0, #0x5
    cmp r4, r1
    subgt r0, r4, #0x5
    strgtb r0, [r10, #0xb29]
    bgt @L02186884
    cmp r4, r0
    strltb r4, [r10, #0xb29]
    b @L02186884
@L02186874:
    add r4, r4, #0x1
@L02186878:
    ldrb r0, [r10, #0x74c]
    cmp r4, r0
    blt @L02186834
@L02186884:
    add sp, sp, #0x24
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void BattleRecords::State_Close(unsigned int ticks)
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    unsigned char step = step_;
    if (step == 0)
    {
        if (mode_ == 0)
        {
            SetBrightness(resources, -0x10, 0xf);
            if (exit_ == 0 && func_0209cae8(data_02109bf4) != 0x29)
                func_0209c678(data_02109bf4, 0xf);
        }
        else
        {
            SetSubBrightness(resources, -0x10, 0xf);
        }
        step_++;
    }
    else if (step == 1)
    {
        if (IsBrightnessTransitionActive(resources))
            return;
        if (func_0209ca2c(data_02109bf4))
            return;
        func_0205d6a0(&window_, 1);
        state_ = 14;
        step_ = 0;
    }
}

// NONMATCHING: the C matches 33.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void BattleRecords::InitializeMenu()
{
    int rows = 1;
    unsigned char count = 1;
    int selected = 0;
    if (state_ == 3)
    {
        rows = itemCount_;
        count = rows;
        for (int i = 0; i < rows; i++)
        {
            if (kind_ == items_[i])
            {
                selected = i;
                break;
            }
        }
        if (rows > 6)
        {
            flags_ |= RECORDS_SCROLL;
            SCROLL_TO(selected);
        }
    }
    func_0205bef8(&cursor_);
    func_0205ba68(&cursor_, 1, rows, 0);
    func_0205bacc(&cursor_, count);
    cursor_.unk_4 = 1;
    func_0205bb04(&cursor_, selected);
}
#else
asm void BattleRecords::InitializeMenu()
{
    stmdb sp!, {r4, r5, r6, r7, r8, lr}
    mov r8, r0
    add r0, r8, #0xb00
    ldrsb r0, [r0, #0x10]
    mov r5, #0x1
    mov r7, r5
    mov r4, r5
    cmp r0, #0x3
    mov r6, #0x0
    bne @L021869f4
    ldrb r7, [r8, #0x74c]
    mov r2, r6
    mov r4, r7
    b @L021869b8
@L0218699c:
    add r0, r8, r2
    ldrb r1, [r8, #0xb28]
    ldrb r0, [r0, #0x744]
    cmp r1, r0
    moveq r6, r2
    beq @L021869c0
    add r2, r2, #0x1
@L021869b8:
    cmp r2, r7
    blt @L0218699c
@L021869c0:
    cmp r7, #0x6
    ble @L021869f4
    ldr r0, [r8, #0xb18]
    orr r0, r0, #0x10
    str r0, [r8, #0xb18]
    ldrb r1, [r8, #0xb29]
    add r0, r1, #0x5
    cmp r6, r0
    subgt r0, r6, #0x5
    strgtb r0, [r8, #0xb29]
    bgt @L021869f4
    cmp r6, r1
    strltb r6, [r8, #0xb29]
@L021869f4:
    add r0, r8, #0x750
    bl func_0205bef8
    mov r1, r5
    mov r2, r7
    add r0, r8, #0x750
    mov r3, #0x0
    bl func_0205ba68
    mov r1, r4
    add r0, r8, #0x750
    bl func_0205bacc
    mov r1, r6
    add r0, r8, #0x750
    str r5, [r8, #0x754]
    bl func_0205bb04
    ldmia sp!, {r4, r5, r6, r7, r8, pc}
}
#endif

int BattleRecords::UpdateMenu(int ticks)
{
    int touched = 0;
    int item = -1;
    int x;
    int y;
    func_02012a84(&data_02114e54, &x, &y);
    if (data_02114e54.touching_)
    {
        touched = 1;
        item = GetTouchedItem(x, y);
        if (item != -1)
            func_0205bb04(&cursor_, item);
    }
    else if (data_02114e54.unk_5f && data_02114e54.unk_24)
    {
        touched = 1;
    }
    else if (data_02114e54.unk_54)
    {
        touched = 1;
    }
    if (!touched)
        func_0205bf58(&cursor_, ticks);
    if (touched)
    {
        if (item == -1)
            return 0;
        if (item == -2)
            return -2;
        if (item >= 0)
            return 1;
    }
    return 0;
}

int BattleRecords::GetTouchedItem(int x, int y)
{
    if (x == 0 || y == 0)
        return -1;
    int count = func_0205bafc(&cursor_);
    if (count > 6)
        count = 6;
    for (int i = 0; i < count; i++)
    {
        int top = i * 16 + 8;
        int bottom = top + 16;
        if (y > top && y < bottom && x > 0x10 && x < 0x98)
            return i + top_;
    }
    unsigned char top;
    int flags = flags_;
    if ((flags & RECORDS_SCROLL) && state_ != 12 && x >= 0x46 && x < 0x52)
    {
        top = top_;
        if (top != 0 && y >= 0 && y < 8)
        {
            top_ = top - 1;
            int last = top_ + 5;
            if (func_0205bb84(&cursor_) > last)
                func_0205bb04(&cursor_, last);
            return -1;
        }
        if (top < 2 && y >= 0x68 && y < 0x70)
        {
            if (top + 6 < itemCount_)
                top_++;
            unsigned char first = top_;
            if (func_0205bb84(&cursor_) < first)
                func_0205bb04(&cursor_, first);
            return -1;
        }
    }
    if (y > 0x60 && y < 0x6a && x > 0xc7 && x < 0xf2)
        return -2;
    if (!(flags & RECORDS_NO_MODEL) && y > 0x10 && y < 0x60 && x > 0xb0 && x < 0xd0 && !(flags & RECORDS_DODGING))
    {
        func_0205eaa0(data_02108760, 0x5e, 0);
        model_.MaybeSetRegularAnimation(STRING(0xac, "sake"), 0);
        flags_ |= RECORDS_DODGING;
    }
    return -1;
}

void BattleRecords::InitializeItems()
{
    itemCount_ = 0;
    for (int i = 0; i < 8; i++)
        items_[i] = 0xff;
    items_[itemCount_++] = 0;
    items_[itemCount_++] = 1;
    items_[itemCount_++] = 2;
    char* store = func_0205ec34();
    if (func_0206dfb0(store, store + 0x8c, 0x1198))
        items_[itemCount_++] = 3;
    if (flags_ & RECORDS_ITEM_4)
        items_[itemCount_++] = 4;
    if (func_0206dfb0(store, store + 0x8c, 0x119d))
        items_[itemCount_++] = 5;
    if (func_0206dfb0(store, store + 0x8c, 0x119b))
        items_[itemCount_++] = 6;
    if (!(flags_ & RECORDS_CLEAR_ITEM))
        return;
    items_[itemCount_++] = 7;
}

void BattleRecords::TurnModel(unsigned int ticks)
{
    int flags = flags_;
    if (flags & RECORDS_TURN_BACK)
    {
        Vector3fix rotation = model_.rotation_;
        int done = 0;
        int y;
        int angle = fix32ReduceAngle0To2Pi(0x5ccc - rotation.y);
        if (angle >= 0 && angle < 0x3244)
        {
            y = rotation.y + angle / 12;
            for (unsigned int i = 0; i < ticks - 1; i++)
                y += fix32ReduceAngle0To2Pi(0x5ccc - y) / 12;
        }
        else if (angle >= 0x3244 && angle < 0x6488)
        {
            y = rotation.y - (0x6488 - angle) / 12;
            for (unsigned int i = 0; i < ticks - 1; i++)
                y -= (0x6488 - fix32ReduceAngle0To2Pi(0x5ccc - y)) / 12;
        }
        rotation.y = fix32ReduceAngle0To2Pi(y);
        model_.rotation_ = rotation;
        int difference = fix32ReduceAngle0To2Pi(0x5ccc - rotation.y);
        int distance = difference < 0 ? -difference : difference;
        if (distance < 0x28)
        {
            done = 1;
        }
        else
        {
            distance = 0x6488 - difference;
            if (distance < 0)
                distance = -distance;
            if (distance < 0x28)
                done = 1;
        }
        if (done)
        {
            rotation.y = fix32ReduceAngle0To2Pi(0x5ccc);
            model_.rotation_ = rotation;
            flags_ &= ~RECORDS_TURN_BACK;
        }
    }
    else if (flags & RECORDS_MENU)
    {
        int left = 0;
        int right = 0;
        if (func_02012430(data_02114e30, 0x200))
            left = 1;
        if (func_02012430(data_02114e30, 0x100))
            right = 1;
        if (left && right)
        {
            flags_ |= RECORDS_TURN_BACK;
            return;
        }
        if (!left && !right)
            return;
        Vector3fix rotation = model_.rotation_;
        if (left)
            rotation.y += (int)(4096.0f * (0.08f * ticks));
        if (right)
            rotation.y -= (int)(4096.0f * (0.08f * ticks));
        rotation.y = fix32ReduceAngle0To2Pi(rotation.y);
        model_.rotation_ = rotation;
    }
}

void BattleRecords::UpdateAnimation(unsigned int ticks)
{
    if (!(flags_ & RECORDS_DODGING))
        return;
    if (!model_.HasAnimationReachedEnd())
        return;
    model_.MaybeSetRegularAnimation(STRING(0xb1, "stand"), 0);
    flags_ &= ~RECORDS_DODGING;
}

void BattleRecords::WriteTimes(ClearRecords* records)
{
    window_.width_ = 5;
    window_.height_ = 2;
    window_.unk_a4 = 7;
    window_.unk_a6 = 7;
    window_.unk_a8 = 2;
    window_.unk_aa = 4;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0x10;
    window_.unk_b7 = 0xa;
    window_.unk_b1 = 1;
    window_.unk_b5 = 1;
    window_.unk_b6 = 1;
    memset(text_, 0, 0x960);
    WriteTime(text_, 0, records);
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 0);
    window_.width_ = 5;
    window_.height_ = 2;
    window_.unk_a4 = 7;
    window_.unk_a6 = 0xc;
    window_.unk_a8 = 2;
    window_.unk_aa = 4;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0x10;
    window_.unk_b7 = 0xa;
    window_.unk_b1 = 2;
    window_.unk_b5 = 1;
    window_.unk_b6 = 1;
    memset(text_, 0, 0x960);
    WriteTime(text_, 1, records);
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 0);
}

void BattleRecords::WriteTime(char* text, int index, ClearRecords* records)
{
    if (text == NULL)
        return;
    PlayTime* time = NULL;
    PlayTime guestTime;
    ResetTime(&guestTime);
    if (index == 0)
    {
        GuestRecords* guest = guestRecords_;
        time = &times_[0];
        if (guest != NULL)
        {
            time = &guestTime;
            guestTime.hours_ = guest->hours1_;
            guestTime.minutes_ = guestRecords_->minutes1_;
        }
        else if (records != NULL)
        {
            time = &records->times_[0];
        }
    }
    else if (index == 1)
    {
        GuestRecords* guest = guestRecords_;
        time = &times_[1];
        if (guest != NULL)
        {
            time = &guestTime;
            guestTime.hours_ = guest->hours2_;
            guestTime.minutes_ = guestRecords_->minutes2_;
        }
        else if (records != NULL)
        {
            time = &records->times_[1];
        }
    }
    if (time == NULL)
        return;
    GameState::GetInstance();
    func_020421a0();
    func_02041e70(text, 0xe);
    func_02041a5c(text, 2);
    char buffer[0x40];
    __clear(buffer, sizeof(buffer));
    const char* format = func_020e0434(&texts_, 0x6e);
    if (format != NULL)
        sprintf(buffer, format, time->hours_, time->minutes_);
    func_02042058(text, buffer);
}

void BattleRecords::RefreshTime(int index)
{
    if (index == 0)
    {
        if (!(flags_ & RECORDS_TIME1_CHANGED))
            return;
        memset(text_, 0, 0x960);
        WriteTime(text_, index, NULL);
        func_0205d5d0(&window_, 1, text_, 1, 0);
        flags_ &= ~RECORDS_TIME1_CHANGED;
    }
    else if (index == 1)
    {
        if (!(flags_ & RECORDS_TIME2_CHANGED))
            return;
        memset(text_, 0, 0x960);
        WriteTime(text_, index, NULL);
        func_0205d5d0(&window_, 2, text_, 1, 0);
        flags_ &= ~RECORDS_TIME2_CHANGED;
    }
}

// NONMATCHING: the C matches 95.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void BattleRecords::UpdateTime(int index)
{
    if (guestRecords_ != NULL)
        return;
    if (state_ == 12 && step_ < 6)
        return;
    GameState* gameState = GameState::GetInstance();
    PlayTime* time = NULL;
    SavedRecords* saved = GetSavedRecords(gameState);
    PlayTime* savedTime = NULL;
    unsigned short hours = 0;
    unsigned char minutes = 0;
    unsigned char seconds = 0;
    if (index == 0)
    {
        time = &times_[0];
        savedTime = &saved->records_.playTime_;
        func_020103f0(gameState, &hours, &minutes, &seconds);
    }
    else if (index == 1)
    {
        savedTime = &saved->records_.unk_4;
        time = &times_[1];
        Unknown_0202ae18* unknown = func_0202ae18();
        int mode = func_0202ba00(unknown);
        int players = unknown->unk_100d;
        if ((mode == 5 && players > 1) || mode == 6)
        {
            func_020104cc(gameState, &hours, &minutes, &seconds);
        }
        else
        {
            hours = 0;
            minutes = 0;
            seconds = 0;
        }
    }
    if (time == NULL || savedTime == NULL)
        return;
    unsigned char previous = time->minutes_;
    ResetTime(time);
    func_020ac614(time, savedTime->hours_ + hours);
    func_020ac644(time, savedTime->minutes_ + minutes);
    time->seconds_ += (unsigned char)(savedTime->seconds_ + seconds);
    if (time->seconds_ > 59)
    {
        unsigned char added = time->seconds_ / 60;
        if (time->hours_ == 9999 && time->minutes_ + added > 59)
        {
            time->hours_ = 9999;
            time->minutes_ = 59;
            time->seconds_ = 59;
        }
        else
        {
            func_020ac644(time, added);
            time->seconds_ %= 60;
        }
    }
    if (time->minutes_ == previous)
        return;
    if (index == 0)
        flags_ |= RECORDS_TIME1_CHANGED;
    else if (index == 1)
        flags_ |= RECORDS_TIME2_CHANGED;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _s32_div_f();
}

asm void BattleRecords::UpdateTime(int index)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    mov r8, r0
    ldr r0, [r8, #0xb34]
    mov r7, r1
    cmp r0, #0x0
    ldmneia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    add r0, r8, #0xb00
    ldrsb r0, [r0, #0x10]
    cmp r0, #0xc
    bne @L021874b0
    ldrb r0, [r8, #0xb11]
    cmp r0, #0x6
    ldmloia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
@L021874b0:
    bl _ZN9GameState11GetInstanceEv
    mov r5, #0x0
    mov r4, r0
    add r1, r4, #0x104
    add r9, r1, #0x7400
    mov r6, r5
    strh r5, [sp, #0x2]
    strb r5, [sp, #0x1]
    strb r5, [sp, #0x0]
    cmp r7, #0x0
    add r1, r9, #0x40
    bne @L021874fc
    add r1, sp, #0x2
    add r2, sp, #0x1
    add r3, sp, #0x0
    add r5, r8, #0xb40
    add r6, r9, #0x3c
    bl func_020103f0
    b @L02187564
@L021874fc:
    cmp r7, #0x1
    bne @L02187564
    add r0, r8, #0x344
    mov r6, r1
    add r5, r0, #0x800
    bl func_0202ae18
    mov r9, r0
    bl func_0202ba00
    add r1, r9, #0x1000
    cmp r0, #0x5
    ldrb r1, [r1, #0xd]
    bne @L02187534
    cmp r1, #0x1
    bgt @L0218753c
@L02187534:
    cmp r0, #0x6
    bne @L02187554
@L0218753c:
    add r1, sp, #0x2
    add r2, sp, #0x1
    add r3, sp, #0x0
    mov r0, r4
    bl func_020104cc
    b @L02187564
@L02187554:
    mov r0, #0x0
    strh r0, [sp, #0x2]
    strb r0, [sp, #0x1]
    strb r0, [sp, #0x0]
@L02187564:
    cmp r5, #0x0
    cmpne r6, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    mov r0, r5
    ldrb r4, [r5, #0x2]
    bl ResetTime
    ldrh r2, [r6, #0x0]
    ldrh r1, [sp, #0x2]
    mov r0, r5
    add r1, r2, r1
    mov r1, r1, lsl #0x10
    mov r1, r1, lsr #0x10
    bl func_020ac614
    ldrb r2, [r6, #0x2]
    ldrb r1, [sp, #0x1]
    mov r0, r5
    add r1, r2, r1
    and r1, r1, #0xff
    bl func_020ac644
    ldrb r1, [r6, #0x3]
    ldrb r0, [sp, #0x0]
    ldrb r2, [r5, #0x3]
    add r0, r1, r0
    and r0, r0, #0xff
    add r1, r2, r0
    and r0, r1, #0xff
    strb r1, [r5, #0x3]
    cmp r0, #0x3b
    bls @L0218762c
    mov r1, #0x3c
    bl _s32_div_f
    ldrh r3, [r5, #0x0]
    ldr r2, =0x270f
    and r1, r0, #0xff
    cmp r3, r2
    bne @L02187614
    ldrb r0, [r5, #0x2]
    add r0, r0, r1
    cmp r0, #0x3b
    strgth r2, [r5, #0x0]
    movgt r0, #0x3b
    strgtb r0, [r5, #0x2]
    strgtb r0, [r5, #0x3]
    bgt @L0218762c
@L02187614:
    mov r0, r5
    bl func_020ac644
    ldrb r0, [r5, #0x3]
    mov r1, #0x3c
    bl _s32_div_f
    strb r1, [r5, #0x3]
@L0218762c:
    ldrb r0, [r5, #0x2]
    cmp r0, r4
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    cmp r7, #0x0
    ldreq r0, [r8, #0xb18]
    orreq r0, r0, #0x800
    streq r0, [r8, #0xb18]
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    cmp r7, #0x1
    ldreq r0, [r8, #0xb18]
    orreq r0, r0, #0x1000
    streq r0, [r8, #0xb18]
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

void BattleRecords::WriteTitle(ClearRecords* records)
{
    window_.width_ = 0x1e;
    window_.height_ = 3;
    window_.unk_a4 = 2;
    window_.unk_a6 = 0;
    window_.unk_a8 = 1;
    window_.unk_aa = 2;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0xa;
    window_.unk_b7 = 0xa;
    window_.unk_b1 = 0;
    window_.unk_b5 = 1;
    window_.unk_b6 = 1;
    memset(text_, 0, 0x960);
    WriteName(text_, records);
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 0);
}

void BattleRecords::WriteName(char* text, ClearRecords* records)
{
    if (text == NULL)
        return;
    GameState* gameState = GameState::GetInstance();
    BackgroundLoader::GetInstance();
    MessageSystem* messages = func_020421a0();
    char name[0x30];
    __clear(name, sizeof(name));
    short title = 0;
    char buffer[0x40];
    __clear(buffer, sizeof(buffer));
    unsigned int female = 0;
    func_02046380(messages);
    MessageName heroName;
    MessageName guestName;
    const void* codes = guest_;
    if (codes == NULL)
    {
        title = GetHeroTitle(gameState)->title_;
        GameObject* hero = gameState->GetProtagonist();
        if (hero != NULL)
        {
            if (title <= 0)
            {
                PartyMemberData* data = hero->partyData_;
                int vocations = 0x50dc;
                if (data->appearance_.female_ == 1)
                    vocations = 0x510e;
                title = vocations - 20000 + data->vocation_;
            }
            female = hero->partyData_->appearance_.female_;
            func_020e46c4(&heroName);
            func_020e4c74(&heroName, hero);
            messages->unk_10 = &heroName;
        }
    }
    else
    {
        GuestRecords* guest = guestRecords_;
        if (guest != NULL)
            title = guest->title_;
        female = guest->female_;
        func_02042764(codes, name, 1);
        func_020e46c4(&guestName);
        func_020e4b34(&guestName, name, name, 0, 0, 0, 0, female, 0, 1, 0, 1);
        messages->unk_10 = &guestName;
    }
    if (title > 0)
    {
        TextList list;
        func_020727d8(&list);
        const char* titleText = NULL;
        unsigned int size = 0;
        if (title < 700)
        {
            if (guestTitles_ != NULL)
            {
                titleText = func_020e0434(guestTitles_, title);
            }
            else
            {
                BackgroundLoader::AddLockGlobal();
                unsigned int namesSize = 0;
                char gp2[0x40];
                char inner[0x20];
                __clear(gp2, sizeof(gp2));
                __clear(inner, sizeof(inner));
                sprintf(gp2, STRING(0x81, "data/bin/ttlname%d.gp2"), female);
                sprintf(inner, STRING(0x98, "ttlname%d_<LG>.nat"), female);
                void* file = ExtractFileFromGP2(gp2, inner, &namesSize);
                if (file != NULL)
                    titleText = func_020e046c(buffer, file, namesSize, title);
                BackgroundLoader::RemoveLockGlobal();
            }
        }
        else
        {
            if (guestTexts_ != NULL)
            {
                titleText = func_02072a68(guestTexts_, (short)(title + 20000));
            }
            else
            {
                BackgroundLoader::AddLockGlobal();
                void* file =
                    ExtractFileFromGP2(STRING(0xb7, "data/bin/profstr.gp2"), STRING(0xcc, "profstr_<LG>.bin"), &size);
                if (file != NULL)
                {
                    func_02072928(&list, file, size, (short)(title + 20000), buffer, 0);
                    titleText = buffer;
                }
                BackgroundLoader::RemoveLockGlobal();
            }
        }
        func_02046574(messages, 0, titleText);
    }
    char* output = text_;
    int format = 100;
    int width = 0xee;
    if (records != NULL)
    {
        format = 101;
        width = 0xdf;
    }
    func_02046608(messages, 10, func_020e0434(&texts_, format), output + 0x760, width, 1, 0);
    int color = 7;
    if (func_020d2f88(output + 0x760, STRING(0xdd, "\n")) != NULL)
        color = 2;
    if (records != NULL)
    {
        titleX_ = (func_020420e8(output + 0x760, 0) + 0x10) << 12;
        if (color == 2)
            titleX_ = 0xe0000;
    }
    func_02041a5c(text, color);
    func_02042058(text, output + 0x760);
}

void BattleRecords::WriteCounts(ClearRecords* records)
{
    window_.width_ = 0x12;
    window_.height_ = 0xb;
    window_.unk_a4 = 0xd;
    window_.unk_a6 = 3;
    window_.unk_a8 = 2;
    window_.unk_aa = 1;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0xf;
    window_.unk_b7 = 0xa;
    window_.unk_b1 = 3;
    window_.unk_b5 = 1;
    window_.unk_b6 = 1;
    memset(text_, 0, 0x960);
    WriteCountTexts(text_, records);
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 0);
}

void BattleRecords::WriteCountTexts(char* text, ClearRecords* records)
{
    SavedRecords* saved;
    int y;
    if (text == NULL)
        return;
    MessageSystem* messages = func_020421a0();
    int count1;
    unsigned int count2;
    unsigned char shown;
    count2 = 0;
    saved = GetSavedRecords(GameState::GetInstance());
    int count3;
    GuestRecords* guest = guestRecords_;
    int count4;
    int count5;
    int count6;
    if (guest != NULL)
    {
        count1 = guest->unk_4_14;
        count2 = guest->unk_0_14;
        count3 = guestRecords_->unk_c_0;
        count4 = guestRecords_->unk_10_0;
        count5 = guestRecords_->unk_c_10;
        count6 = guestRecords_->unk_10_9;
    }
    else if (records != NULL)
    {
        count1 = records->unk_8_0;
        count2 = records->unk_c_0;
        count3 = records->unk_10_0;
        count4 = records->unk_14_0;
        count5 = records->unk_10_9;
        count6 = records->unk_14_8;
    }
    else
    {
        count1 = saved->records_.unk_8_0;
        func_020ac0b4(&count2);
        count3 = saved->records_.unk_10_0;
        count4 = saved->records_.unk_8_24;
        count5 = saved->records_.unk_c_14;
        count6 = saved->records_.unk_10_9;
    }
    if (page_ != NULL)
        count3--;
    if (count1 > 99999)
        count1 = 99999;
    if ((int)count2 > 99999)
        count2 = 99999;
    if (count3 > 999)
        count3 = 999;
    if (count4 > 999)
        count4 = 999;
    if (count5 > 9999)
        count5 = 9999;
    if (count6 > 9999)
        count6 = 9999;
    func_02046380(messages);
    func_020465c0(messages, 0, count1);
    func_020465f0(messages, 0, 5);
    func_020465d8(messages, 0, 1);
    func_020465c0(messages, 1, count2);
    func_020465f0(messages, 1, 5);
    func_020465d8(messages, 1, 1);
    func_020465c0(messages, 2, count3);
    func_020465f0(messages, 2, 5);
    char* store;
    func_020465d8(messages, 2, 1);
    func_020465c0(messages, 3, count4);
    func_020465f0(messages, 3, 5);
    func_020465d8(messages, 3, 1);
    func_020465c0(messages, 4, count5);
    func_020465f0(messages, 4, 5);
    func_020465d8(messages, 4, 1);
    func_020465c0(messages, 5, count6);
    func_020465f0(messages, 5, 5);
    func_020465d8(messages, 5, 1);
    func_02041e70(text, 0xe);
    store = func_0205ec34();
    shown = 0;
    if (records != NULL)
    {
        for (int i = 0; i < 6; i++)
            shown += 1 << i;
    }
    else
    {
        shown += 1;
        if (func_0206dfb0(store, store + 0x8c, 0x1198))
            shown += 2;
        shown += 4;
        if (saved->records_.unk_8_24 != 0)
            shown += 8;
        if (saved->records_.unk_c_14 != 0)
            shown += 0x10;
        if (func_0206dfb0(store, store + 0x8c, 0x1199))
            shown += 0x20;
    }
    int line = 0;
    for (int i = 0; i < 6; i++)
    {
        if (shown & (1 << i))
        {
            char label[0x40];
            y = line * 14;
            func_02041a90(text, 2, y + 7);
            __clear(label, sizeof(label));
            const char* name = func_020e0434(&texts_, (short)(i + 0x78));
            memcpy(label, name, strlen(name));
            char* value = strstr(label, STRING(0xdf, "<val"));
            if (value != NULL)
                *value = 0;
            func_02042058(text, label);
            func_02041a90(text, 0x62, y + 7);
            func_02042058(text, func_020e0434(&texts_, (short)(i + 500)));
            line++;
        }
    }
}

void BattleRecords::WriteMenu(ClearRecords* records)
{
    if (records != NULL)
    {
        window_.width_ = 0x14;
        window_.height_ = 3;
        window_.unk_a4 = 6;
        window_.unk_a6 = 0x11;
        window_.unk_a8 = 0;
        window_.unk_aa = 6;
        window_.unk_ac = 0xc;
        window_.unk_ae = 0xe;
        window_.unk_b7 = 0xc;
        window_.unk_b1 = 4;
        window_.unk_b5 = 1;
        window_.unk_b6 = 1;
        memset(text_, 0, 0x960);
        char* text = text_;
        if (text != NULL)
        {
            func_020421a0();
            if (records != NULL)
            {
                GameObject* hero = GameState::GetInstance()->GetProtagonist();
                char* name = text_ + 0x8e0;
                BackgroundLoader::AddLockGlobal();
                unsigned int size = 0;
                char inner[0x20];
                char gp2[0x40];
                __clear(gp2, sizeof(gp2));
                __clear(inner, sizeof(inner));
                sprintf(gp2, STRING(0x81, "data/bin/ttlname%d.gp2"), hero->partyData_->appearance_.female_);
                sprintf(inner, STRING(0x98, "ttlname%d_<LG>.nat"), hero->partyData_->appearance_.female_);
                void* file = ExtractFileFromGP2(gp2, inner, &size);
                if (file != NULL)
                    func_020e046c(name, file, size, (short)records->title_);
                BackgroundLoader::RemoveLockGlobal();
                int x = (0xa0 - func_020420e8(name, 1)) / 2;
                if (x < 0)
                    x = 0;
                func_02041a90(text, x, 6);
                if (name != NULL)
                    func_02042058(text, name);
            }
            else
            {
                int i;
                int count = 3;
                char* store = func_0205ec34();
                if (func_0206dfb0(store, store + 0x8c, 0x1198))
                    count = 4;
                for (i = 0; i < count; i++)
                {
                    func_02041a90(text, 4, i * 15 + 4);
                    func_02042058(text, func_020e0434(&texts_, (short)(i + 0x82)));
                }
            }
        }
        func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 1);
        return;
    }
    window_.width_ = 0x16;
    window_.height_ = 8;
    window_.unk_a4 = 1;
    window_.unk_a6 = 0xf;
    window_.unk_a8 = 4;
    window_.unk_aa = 5;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0xe;
    window_.unk_b7 = 0xa;
    window_.unk_b1 = 4;
    window_.unk_b5 = 1;
    window_.unk_b6 = 1;
    memset(text_, 0, 0x960);
    char* labels = text_;
    if (labels != NULL)
    {
        func_020421a0();
        if (records != NULL)
        {
            GameObject* hero = GameState::GetInstance()->GetProtagonist();
            char* name = text_ + 0x8e0;
            BackgroundLoader::AddLockGlobal();
            unsigned int size = 0;
            char inner[0x20];
            char gp2[0x40];
            __clear(gp2, sizeof(gp2));
            __clear(inner, sizeof(inner));
            sprintf(gp2, STRING(0x81, "data/bin/ttlname%d.gp2"), hero->partyData_->appearance_.female_);
            sprintf(inner, STRING(0x98, "ttlname%d_<LG>.nat"), hero->partyData_->appearance_.female_);
            void* file = ExtractFileFromGP2(gp2, inner, &size);
            if (file != NULL)
                func_020e046c(name, file, size, (short)records->title_);
            BackgroundLoader::RemoveLockGlobal();
            int x = (0xa0 - func_020420e8(name, 1)) / 2;
            if (x < 0)
                x = 0;
            func_02041a90(labels, x, 6);
            if (name != NULL)
                func_02042058(labels, name);
        }
        else
        {
            int i;
            int count = 3;
            char* store = func_0205ec34();
            if (func_0206dfb0(store, store + 0x8c, 0x1198))
                count = 4;
            for (i = 0; i < count; i++)
            {
                func_02041a90(labels, 4, i * 15 + 4);
                func_02042058(labels, func_020e0434(&texts_, (short)(i + 0x82)));
            }
        }
    }
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 0);
    window_.width_ = 3;
    window_.height_ = 8;
    window_.unk_a4 = 0x1b;
    window_.unk_a6 = 0xf;
    window_.unk_a8 = 4;
    window_.unk_aa = 5;
    window_.unk_ac = 0xa;
    window_.unk_ae = 0xe;
    window_.unk_b7 = 0xa;
    window_.unk_b1 = 5;
    window_.unk_b5 = 1;
    window_.unk_b6 = 1;
    memset(text_, 0, 0x960);
    WriteMenuTexts(text_, 1, records);
    func_0205d304(&window_, text_, 0, 0, 0, 0, 0, 0);
}

void BattleRecords::WriteMenuTexts(char* text, int kind, ClearRecords* records)
{
    if (text == NULL)
        return;
    MessageSystem* messages = func_020421a0();
    if (records != NULL)
    {
        GameObject* hero = GameState::GetInstance()->GetProtagonist();
        char* name = text_ + 0x8e0;
        BackgroundLoader::AddLockGlobal();
        unsigned int size = 0;
        char gp2[0x40];
        char inner[0x20];
        __clear(gp2, sizeof(gp2));
        __clear(inner, sizeof(inner));
        sprintf(gp2, STRING(0x81, "data/bin/ttlname%d.gp2"), hero->partyData_->appearance_.female_);
        sprintf(inner, STRING(0x98, "ttlname%d_<LG>.nat"), hero->partyData_->appearance_.female_);
        void* file = ExtractFileFromGP2(gp2, inner, &size);
        if (file != NULL)
            func_020e046c(name, file, size, (short)records->title_);
        BackgroundLoader::RemoveLockGlobal();
        int x = (0xa0 - func_020420e8(name, 1)) / 2;
        if (x < 0)
            x = 0;
        func_02041a90(text, x, 6);
        if (name != NULL)
            func_02042058(text, name);
        return;
    }
    int count = 3;
    char* store = func_0205ec34();
    if (func_0206dfb0(store, store + 0x8c, 0x1198))
        count = 4;
    if (kind == 0)
    {
        for (int i = 0; i < count; i++)
        {
            func_02041a90(text, 4, i * 15 + 4);
            func_02042058(text, func_020e0434(&texts_, (short)(i + 0x82)));
        }
    }
    else if (kind == 1)
    {
        unsigned int count1;
        unsigned int count2;
        unsigned int count3;
        unsigned int count4;
        GuestRecords* guest = guestRecords_;
        if (guest != NULL)
        {
            count1 = guest->unk_8_14;
            count2 = guest->unk_c_24;
            count3 = guest->unk_8_21;
            count4 = guest->unk_10_23;
        }
        else
        {
            PlayRecords playRecords;
            func_020ac4c0(&playRecords);
            int max1 = playRecords.unk_14_0;
            int max2 = playRecords.unk_14_18;
            int max3 = playRecords.unk_14_9;
            int max4 = playRecords.unk_10_23;
            count1 = func_020a0870(&playRecords);
            count2 = func_020a08d8(&playRecords);
            count3 = func_020a08a4(&playRecords);
            count4 = func_020a090c(&playRecords);
            if (count1 == 0 && max1 > 0)
                count1 = 1;
            if (count2 == 0 && max2 > 0)
                count2 = 1;
            if (count3 == 0 && max3 > 0)
                count3 = 1;
            if (count4 == 0 && max4 > 0)
                count4 = 1;
        }
        func_02046380(messages);
        func_020465c0(messages, 0, count1);
        func_020465c0(messages, 1, count2);
        func_020465c0(messages, 2, count3);
        func_020465c0(messages, 3, count4);
        for (int i = 0; i < count; i++)
        {
            func_02041a5c(text, i * 15 + 4);
            func_0204201c(text, func_020e0434(&texts_, (short)(i + 0x8c)), 0x18);
        }
    }
}

void BattleRecords::DrawItems()
{
    if (flags_ & RECORDS_SPRITES)
    {
        int shown = 0;
        for (int i = 0; i < 6; i++)
        {
            unsigned char kind = items_[top_ + i];
            if (kind != 0xff)
            {
                Sprite* sprite = &sprites_[kind];
                sprite->x_ = 0x10000;
                sprite->y_ = ((shown % 6) << 16) + 0x8000;
                int selected = func_0205bb84(&cursor_) - top_;
                int frame = 1;
                if (selected == i)
                    frame = 2;
                else if (state_ == 12)
                    frame = 3;
                if (func_0202c540(func_0202ae18()) && kind == 5)
                    frame = 3;
                func_0205afb0(renderer_, &sprites_[kind], frame);
                func_0205af84(renderer_, &sprites_[kind], 1);
                func_0205ac40(renderer_, &sprites_[kind]);
                shown++;
            }
        }
    }
    if (!(flags_ & RECORDS_ICON))
        return;
    Sprite* icon = iconSprite_;
    icon->x_ = titleX_;
    icon->y_ = 0x4000;
    icon->unk_26 = 1;
    icon->unk_25 = 0;
    icon->unk_22 = 0x7f;
    func_0205ac40(iconRenderer_, icon);
}

void BattleRecords::DrawCursor()
{
    if (renderer_ == NULL)
        return;
    int flags = flags_;
    if (!(flags & RECORDS_CURSOR))
        return;
    if (!(flags & RECORDS_SPRITES))
        return;
    GameState* gameState = GameState::GetInstance();
    short y = (func_0205bb84(&cursor_) - top_) * 16 + 7;
    func_0205a42c(animations_, 0, 0x3f);
    func_0205a370(animations_, 0);
    SpriteAnimation* animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
        animation->flags_ |= 8;
    func_0205a330(animations_, gameState->GetTickCount());
    animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
    {
        animation->x_ = 4;
        animation->y_ = y;
    }
    func_0205ae8c(renderer_);
}

void BattleRecords::DrawArrows()
{
    static const signed char sArrowSprites[2] = {0xf, 0x10};
    static const int sArrowX = 0x46000;
    static const int sArrowY[2] = {0x1000, 0x68000};
    static const unsigned char sArrowsShown[4][2] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}};
    if (renderer_ == NULL)
        return;
    int flags = flags_;
    if (!(flags & RECORDS_SCROLL))
        return;
    if (!(flags & RECORDS_SPRITES))
        return;
    for (int i = 0; i < 2; i++)
    {
        unsigned char top = top_;
        if (itemCount_ == 7 && top == 1)
            top = 2;
        if (sArrowsShown[top][i])
        {
            Sprite* sprite = &sprites_[sArrowSprites[i]];
            sprite->x_ = sArrowX;
            sprite->y_ = sArrowY[i];
            func_0205af84(renderer_, &sprites_[sArrowSprites[i]], 1);
            func_0205ac40(renderer_, &sprites_[sArrowSprites[i]]);
        }
    }
}

void BattleRecords::DrawBackButton()
{
    if (renderer_ == NULL)
        return;
    if (!(flags_ & RECORDS_SPRITES))
        return;
    Sprite* sprites = sprites_;
    sprites[17].x_ = 0xc8000;
    sprites[17].y_ = 0x62000;
    func_0205af84(renderer_, &sprites_[17], 1);
    func_0205ac40(renderer_, &sprites_[17]);
}

// NONMATCHING: the C matches 97.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
int BattleRecords::LoadBackgrounds(int lastClear)
{
    static const int sCanvasSize = 0x200;
    GameResources* resources = func_ov017_0218b5b0();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    unsigned char step = loadStep_;
    if (step == 0)
    {
        int archive = 1;
        int inner = 2;
        if (lastClear)
        {
            archive = 3;
            inner = 4;
        }
        const char* innerName = func_020e0434(&texts_, inner);
        task_ = loader->QueueLoadFileInGP2(func_020e0434(&texts_, archive), innerName, NULL);
        loadStep_++;
    }
    if (step == 1)
    {
        if (IsBrightnessTransitionActive(resources))
            return 0;
        func_0205d6a0(&window_, 1);
        loadStep_++;
    }
    if (step == 2 && loader->GetTaskStatus(task_))
    {
        int last;
        backgroundAllocator_.Reset();
        func_0204af64(&backgrounds_[1]);
        func_0204b11c(&backgrounds_[1], 0);
        backgrounds_[1].unk_1c_0_ = 1;
        backgrounds_[1].unk_1c_4_ = 0;
        func_0204b5b4(&backgrounds_[1], 1);
        func_0204b5e8(&backgrounds_[1], 0, 0);
        func_0204b12c(&backgrounds_[1], &backgroundAllocator_);
        func_0204af38(&backgrounds_[1], 1, &backgroundAllocator_);
        func_0204af64(&backgrounds_[2]);
        func_0204b11c(&backgrounds_[2], 0);
        backgrounds_[2].unk_1c_0_ = 1;
        backgrounds_[2].unk_1c_4_ = 1;
        func_0204b5b4(&backgrounds_[2], 0);
        func_0204b5e8(&backgrounds_[2], 0, 0);
        func_0204b12c(&backgrounds_[2], &backgroundAllocator_);
        char name[4];
        void* archive;
        unsigned int archiveSize;
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        int i = 0;
        last = count - 1;
        for (; i < count; i++)
        {
            unsigned int size;
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL)
            {
                if (i == last)
                    func_0204b174(&backgrounds_[2], file, &backgroundAllocator_, size);
                else
                    func_0204b174(&backgrounds_[1], file, &backgroundAllocator_, size);
            }
        }
        loader->RemoveTask(task_);
        task_ = -1;
        func_0204b8d0(&backgrounds_[1], 0, 0, 0, 0, 0, 0x20, 0x18, 0xffff);
        func_0204b0e8(&backgrounds_[1], 0);
        func_0204bc74(&backgrounds_[2], 0, 0, 0, 0x20, 0x19, 0);
        func_0204b0e8(&backgrounds_[2], 0);
        Canvas* canvas;
        for (int i = 0; i < 6; i++)
        {
            canvas = &canvases_[i];
            func_0204c7a8(canvas, &backgroundAllocator_, pixels_, sCanvasSize);
            canvas->background_ = &backgrounds_[2];
        }
        window_.background_ = &backgrounds_[2];
        window_.unk_b2 = 1;
        func_0205cf78(&window_, canvases_, 6);
        loadStep_ = 0;
        return 1;
    }
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
}

asm int BattleRecords::LoadBackgrounds(int lastClear)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, lr}
    sub sp, sp, #0x24
    mov r6, r0
    mov r7, r1
    bl func_ov017_0218b5b0
    mov r8, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r5, [r6, #0xb12]
    mov r4, r0
    cmp r5, #0x0
    bne @L02188ad0
    mov r9, #0x1
    cmp r7, #0x0
    mov r1, #0x2
    movne r9, #0x3
    movne r1, #0x4
    add r0, r6, #0xa0
    bl func_020e0434
    mov r7, r0
    mov r1, r9
    add r0, r6, #0xa0
    bl func_020e0434
    mov r1, r0
    mov r2, r7
    mov r0, r4
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r6, #0xb20]
    ldrb r0, [r6, #0xb12]
    add r0, r0, #0x1
    strb r0, [r6, #0xb12]
@L02188ad0:
    cmp r5, #0x1
    bne @L02188b04
    mov r0, r8
    bl IsBrightnessTransitionActive
    cmp r0, #0x0
    movne r0, #0x0
    bne @L02188d6c
    add r0, r6, #0x130
    mov r1, #0x1
    bl func_0205d6a0
    ldrb r0, [r6, #0xb12]
    add r0, r0, #0x1
    strb r0, [r6, #0xb12]
@L02188b04:
    cmp r5, #0x2
    bne @L02188d68
    ldr r1, [r6, #0xb20]
    mov r0, r4
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02188d68
    add r0, r6, #0x14
    bl _ZN13SafeAllocator5ResetEv
    add r0, r6, #0xf0
    bl func_0204af64
    add r0, r6, #0xf0
    mov r1, #0x0
    bl func_0204b11c
    ldrb r2, [r6, #0x10c]
    add r0, r6, #0xf0
    mov r1, #0x1
    bic r2, r2, #0xf
    orr r2, r2, #0x1
    strb r2, [r6, #0x10c]
    and r2, r2, #0xff
    bic r2, r2, #0xf0
    strb r2, [r6, #0x10c]
    bl func_0204b5b4
    mov r1, #0x0
    add r0, r6, #0xf0
    mov r2, r1
    bl func_0204b5e8
    add r0, r6, #0xf0
    add r1, r6, #0x14
    bl func_0204b12c
    add r0, r6, #0xf0
    mov r1, #0x1
    add r2, r6, #0x14
    bl func_0204af38
    add r0, r6, #0x110
    bl func_0204af64
    add r0, r6, #0x110
    mov r1, #0x0
    bl func_0204b11c
    ldrb r2, [r6, #0x12c]
    add r0, r6, #0x110
    mov r1, #0x0
    bic r2, r2, #0xf
    orr r2, r2, #0x1
    strb r2, [r6, #0x12c]
    and r2, r2, #0xff
    bic r2, r2, #0xf0
    orr r2, r2, #0x10
    strb r2, [r6, #0x12c]
    bl func_0204b5b4
    mov r1, #0x0
    add r0, r6, #0x110
    mov r2, r1
    bl func_0204b5e8
    add r0, r6, #0x110
    add r1, r6, #0x14
    bl func_0204b12c
    ldr r1, [r6, #0xb20]
    mov r0, r4
    add r2, sp, #0x1c
    add r3, sp, #0x18
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x1c]
    bl func_02046900
    mov r9, r0
    mov r10, #0x0
    sub r5, r9, #0x1
    add r8, sp, #0x20
    add r7, sp, #0x14
    b @L02188c6c
@L02188c20:
    ldr r0, [sp, #0x1c]
    mov r1, r10
    mov r2, r8
    mov r3, r7
    bl func_020467f0
    movs r1, r0
    beq @L02188c68
    cmp r10, r5
    bne @L02188c58
    ldr r3, [sp, #0x14]
    add r0, r6, #0x110
    add r2, r6, #0x14
    bl func_0204b174
    b @L02188c68
@L02188c58:
    ldr r3, [sp, #0x14]
    add r0, r6, #0xf0
    add r2, r6, #0x14
    bl func_0204b174
@L02188c68:
    add r10, r10, #0x1
@L02188c6c:
    cmp r10, r9
    blt @L02188c20
    ldr r1, [r6, #0xb20]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mov r1, #0x0
    mvn r4, #0x0
    str r4, [r6, #0xb20]
    str r1, [sp, #0x0]
    str r1, [sp, #0x4]
    mov r0, #0x20
    str r0, [sp, #0x8]
    mov r0, #0x18
    str r0, [sp, #0xc]
    add r4, r4, #0x10000
    mov r2, r1
    mov r3, r1
    add r0, r6, #0xf0
    str r4, [sp, #0x10]
    bl func_0204b8d0
    add r0, r6, #0xf0
    mov r1, #0x0
    bl func_0204b0e8
    mov r1, #0x0
    mov r0, #0x20
    str r0, [sp, #0x0]
    mov r0, #0x19
    stmib sp, {r0, r1}
    add r0, r6, #0x110
    mov r2, r1
    mov r3, r1
    bl func_0204bc74
    add r0, r6, #0x110
    mov r1, #0x0
    bl func_0204b0e8
    mov r10, #0x0
    add r8, r6, #0x1ec
    add r5, r6, #0x110
    mov r7, #0x200
    mov r4, #0xe0
    b @L02188d30
@L02188d10:
    mla r9, r10, r4, r8
    ldr r2, [r6, #0x72c]
    mov r0, r9
    mov r3, r7
    add r1, r6, #0x14
    bl func_0204c7a8
    str r5, [r9, #0x4]
    add r10, r10, #0x1
@L02188d30:
    cmp r10, #0x6
    blt @L02188d10
    add r0, r6, #0x110
    str r0, [r6, #0x1c8]
    mov r3, #0x1
    add r0, r6, #0x130
    add r1, r6, #0x1ec
    mov r2, #0x6
    strb r3, [r6, #0x1e2]
    bl func_0205cf78
    mov r0, #0x0
    strb r0, [r6, #0xb12]
    mov r0, #0x1
    b @L02188d6c
@L02188d68:
    mov r0, #0x0
@L02188d6c:
    add sp, sp, #0x24
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif

int BattleRecords::LoadIcon()
{
    // The size of the canvases' pixels, which the original has here (LoadBackgrounds() is in assembly for now)
    static const int sCanvasSize = 0x200;
    sCanvasSize;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    unsigned char step = loadStep_;
    if (step == 0)
    {
        iconRenderer_ = NULL;
        iconSprite_ = NULL;
        iconAllocator_.Reset();
        iconRenderer_ = (SpriteRenderer*)iconAllocator_.Allocate(sizeof(SpriteRenderer));
        iconSprite_ = (Sprite*)iconAllocator_.Allocate(sizeof(Sprite));
        func_0205a444(iconRenderer_);
        iconRenderer_->unk_50 = 1;
        SpriteRenderer* renderer = iconRenderer_;
        renderer->SetSprites(iconSprite_, 1);
        for (int i = 0; i < 1; i++)
            func_0205a198(&iconSprite_[i]);
        task_ = loader->QueueLoadFile(func_020e0434(&texts_, 7), NULL);
        loadStep_++;
    }
    if (step == 1 && loader->GetTaskStatus(task_))
    {
        char name[4];
        void* archive;
        unsigned int archiveSize;
        loader->GetLoadedFileByID(task_, &archive, &archiveSize);
        int count = func_02046900(archive);
        for (int i = 0; i < count; i++)
        {
            unsigned int size;
            void* file = func_020467f0(archive, i, name, &size);
            if (file != NULL)
                func_0205a528(iconRenderer_, file, size, &iconAllocator_);
        }
        loader->RemoveTask(task_);
        task_ = -1;
        loadStep_ = 0;
        return 1;
    }
    return 0;
}

// NONMATCHING: the C matches 88.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void BattleRecords::CheckClose()
{
    int flags = flags_;
    if (!(flags & RECORDS_CLOSE))
        return;
    if ((flags & RECORDS_BUSY) || closed_ != 0)
        return;
    GuideWindow* guide = guide_;
    if (guide != NULL && !(guide->flags_ & GUIDE_WINDOW_MESSAGE_WINDOW))
        guide->Close();
    exit_ = 0;
    state_ = 13;
    step_ = 0;
    closed_++;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11GuideWindow5CloseEv(); // GuideWindow::Close
}

asm void BattleRecords::CheckClose()
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    ldr r0, [r4, #0xb18]
    tst r0, #0x100000
    ldmeqia sp!, {r4, pc}
    tst r0, #0x200000
    ldmneia sp!, {r4, pc}
    ldrb r0, [r4, #0xb2a]
    cmp r0, #0x0
    ldmneia sp!, {r4, pc}
    ldr r0, [r4, #0xb08]
    cmp r0, #0x0
    beq @L02188f38
    add r1, r0, #0x400
    ldrh r1, [r1, #0x38]
    tst r1, #0x4
    bne @L02188f38
    bl _ZN11GuideWindow5CloseEv
@L02188f38:
    mov r1, #0x0
    strb r1, [r4, #0xb13]
    mov r0, #0xd
    strb r0, [r4, #0xb10]
    strb r1, [r4, #0xb11]
    ldrb r0, [r4, #0xb2a]
    add r0, r0, #0x1
    strb r0, [r4, #0xb2a]
    ldmia sp!, {r4, pc}
}
#endif
