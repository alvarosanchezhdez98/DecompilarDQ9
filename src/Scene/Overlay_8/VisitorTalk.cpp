// Overlay 8, talking to a visitor of the inn (see VisitorTalk.h)
// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_8/VisitorTalk.h"
#include "Filesystem/BackgroundLoader.h"
#include "Grotto/Main/TreasureMapDataStructs.h"
#include "GameState/PartyMemberData.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/Cache.h"
#include "System/ColorEffects.h"
#include "System/LoadToVRAM.h"
#include "System/Memory.h"
#include "Text/MessageName.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define REG_DISPCNT (*(volatile unsigned int*)0x04000000)
#define REG_BG0CNT (*(volatile unsigned short*)0x04000008)
#define REG_BG1CNT (*(volatile unsigned short*)0x0400000a)
#define REG_BG2CNT (*(volatile unsigned short*)0x0400000c)
#define REG_BG3CNT (*(volatile unsigned short*)0x0400000e)
#define REG_BLDCNT 0x04000050
#define REG_BG0CNT_SUB (*(volatile unsigned short*)0x04001008)
#define REG_BG1CNT_SUB (*(volatile unsigned short*)0x0400100a)
#define REG_BG2CNT_SUB (*(volatile unsigned short*)0x0400100c)

// What func_0202ae18 returns
struct Unknown_0202ae18
{
    char unk_0[4];
};

// The treasure maps of the save data that func_020ac760 copies and func_020ac734 writes back
struct TreasureMapList
{
    unsigned char count_;
    char unk_1;
    TreasureMapMetadata maps_[99];
};

// A grotto that func_02011818 adds (0x28 bytes)
struct GrottoEntry
{
    unsigned char type_;
    unsigned char quality_;
    unsigned char level_;
    char unk_3;
    unsigned short seed_;
    unsigned char unk_6;
    char discoveredBy_[0xc];
    char clearedBy_[0xd];
    int location_;
    unsigned char flags_;
    char unk_25;
    unsigned short unk_26;
};

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    void func_ov004_0216aa70();

    // FS_OVERLAY_ID() of overlays 4 and 8, which the linker script defines
    extern unsigned int OVERLAY_4_ID[];
    extern unsigned int OVERLAY_8_ID[];

    GameResources* func_0200fb8c(GameState* gameState);
    signed char func_020100b0(GameState* gameState);
    unsigned int func_02011804(GameState* gameState);
    void func_02011818(GameState* gameState, GrottoEntry* entry);
    void func_02011a74(GameState* gameState, int, const char* name);
    void func_02011ab8(GameState* gameState);
    Unknown_0202ae18* func_0202ae18();
    int func_0202b7d8();
    int func_0202c508(Unknown_0202ae18*);
    void func_020397cc(GameObject* object, int);
    void func_0203b4a0(GameResources* resources, int);
    void func_0203b4b0(GameResources* resources, int);
    void func_02041a90(char* text, int x, int y);
    void func_02041cf4(char* text, int color, int x, int width, int y);
    void func_02041e70(char* text, int color);
    void func_02042058(char* text, const char* append);
    int func_020420e8(const char* text, int large);
    MessageSystem* func_020421a0();
    void func_020426bc(const char* name, char* codes, int);
    void func_02042764(const void* codes, char* text, int);
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    int func_020457e0(MessageSystem* messages);
    void func_02046380(MessageSystem* messages);
    void func_020464e8(MessageSystem* messages, int index, const char* text);
    void func_02046574(MessageSystem* messages, int index, const char* text);
    void func_020465c0(MessageSystem* messages, int index, int value);
    void func_020465d8(MessageSystem* messages, int index, int);
    void func_020465f0(MessageSystem* messages, int index, int digits);
    void func_02046608(MessageSystem* messages, int, const char* format, char* output, int size, int, int);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    int func_02046900(void* archive);
    void func_020469b4(void*, void* script);
    int func_02046b08(void*);
    void func_0204af64(BackgroundGraphics* background);
    void func_0204b0e8(BackgroundGraphics* background, int);
    void func_0204b11c(BackgroundGraphics* background, int);
    void func_0204b12c(BackgroundGraphics* background, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* background, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b5b4(BackgroundGraphics* background, int);
    void func_0204b5e8(BackgroundGraphics* background, int, int);
    void func_0204bc74(BackgroundGraphics* background, int, int, int, int, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, unsigned int size);
    PartyMemberData* func_02053c6c(GameObject* member);
    void func_0205a198(Sprite* sprite);
    void func_0205a234(SpriteAnimationList* list);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205cf78(TextWindow* window, Canvas* canvases, int count);
    void func_0205cfd4(TextWindow* window);
    void func_0205d048(TextWindow* window);
    unsigned char func_0205d0e0(TextWindow* window);
    void func_0205d1e0(TextWindow* window);
    void func_0205d228(TextWindow* window);
    void func_0205d274(TextWindow* window);
    void func_0205d2bc(TextWindow* window);
    void func_0205d304(TextWindow* window, char* text, int, int, int, int, int, int);
    void func_0205d6a0(TextWindow* window, int);
    Canvas* func_0205d81c(TextWindow* window, unsigned char canvas);
    void func_0205da88(TextWindow* window, int, int, int);
    void func_0205de24(TextWindow* window, int, int);
    char* func_0205ec34();
    void func_0206df6c(void*, void*, int flag, int);
    int func_0206dfb0(void*, void*, int flag);
    void func_020727d8(TextList* texts);
    void func_020728ac(TextList* texts, SafeAllocator* allocator, void* file, unsigned int size, int, int, int);
    const char* func_02072a68(TextList* texts, short id);
    void func_02074af4(void* state);
    void func_02074bd0(void* state);
    void* func_02094a00();
    void func_02094ab0(void* music);
    void func_02094b34(void* music, int, int, int, int);
    int func_02094b4c(void* music);
    void func_02099304(ProfileData* profile, const char* name, void* sentences, unsigned int size, char* text,
                       int length, int, const char* title, const char* accolade);
    void func_020a1940(unsigned int id);
    void func_020a3720();
    void func_020a395c();
    void func_020ac734(TreasureMapList* maps);
    void func_020ac760(TreasureMapList* maps);
    void* func_020d6c00();
    void func_020dc2bc();
    void func_020dc2d0(int);
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, int id);
    void func_020e4b34(MessageName* name, char* text, char* text2, int, int, int, int, int female, int, int, int, int);
    void func_020e4bf4(MessageName* name, int member);
    GameResources* func_ov017_0218b5b0();
    void func_ov017_021a9ff0(int);
    void func_ov017_021b2174(void* script);
    void func_ov017_021b2ba0(void* script, const char* name);
    void func_ov017_021b2bd0(void* script, void (*function)(), unsigned int overlay);
    void func_ov017_021d1014(signed char member, int, int);
    void func_ov017_021d1118(signed char member, int, int, int);
}

// The strings of the functions, which the compiler pools in this order. The functions in assembly (NONMATCHING) can't
// reference the compiler's pool, so they're in an array for them
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] __attribute__((aligned(4))) =
    "data/bin/ttlname%d.gp2\0ttlname%d_<LG>.nat\0data/bin/tlkpcstr.gp2\0tlkpcstr_<LG>.bin\0data/ani/bg_tm.pac\0"
    "data/ani/obj_tlkpc.pac\0data/bin/profstr.gp2\0profstr_<LG>.bin\0data/bin/profsen.gp2\0profsen_<LG>.bin\0BBB\0"
    "mmate.stb";
#define STRING(offset, text) (sStrings + (offset))
#endif

// The visitors met in the inn
static inline VisitorList* GetVisitors(GameState* gameState)
{
    return (VisitorList*)((char*)gameState + 0x71fc);
}

// A field of the resources of overlay 17
#define RESOURCE(resources, offset, type) (*(type*)((char*)(resources) + (offset)))

static void ClearEntry(GuestEntry* entry);

void VisitorTalk::Initialize(signed char member, GuestData* guest)
{
    GameState* gameState = GameState::GetInstance();
    func_0202ae18();
    unk_10 = 0;
    unk_11 = 0;
    func_02074af4(this);
    layers_ = (REG_DISPCNT & 0x1f00) >> 8;
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x100;
    func_0205cfd4(&window_);
    func_0204af64(&backgrounds_[0]);
    func_0204af64(&backgrounds_[1]);
    func_0204c684(&canvas_);
    func_020727d8(&texts_);
    func_020727d8(&profileTexts_);
    func_020dfc40(&titles_);
    renderer_ = NULL;
    sprites_ = NULL;
    animations_ = NULL;
    allocator_.ResetAllocatorPointer();
    textAllocator_.ResetAllocatorPointer();
    recordsAllocator_.ResetAllocatorPointer();
    spriteAllocator_.ResetAllocatorPointer();
    profileAllocator_.ResetAllocatorPointer();
    titleAllocator_.ResetAllocatorPointer();
    text_ = NULL;
    pixels_ = NULL;
    records_.Initialize();
    ClearEntry(&entry_);
    profile_.year_ = 2000;
    profile_.month_ = 1;
    profile_.day_ = 1;
    profile_.birthdayChosen_ = 0;
    profile_.unk_0_21 = 0;
    profile_.designChosen_ = 0;
    profile_.female_ = 0;
    profile_.initialized_ = 0;
    profile_.accoladeChosen_ = 0;
    profile_.vocationAccolade_ = 1;
    profile_.showBirthday_ = 0;
    profile_.unk_4_0 = 0x1ff;
    profile_.edited_ = 0;
    profile_.title_ = 300;
    profile_.accolade_ = 706;
    profile_.unk_8[0] = 0;
    unk_e98 = 0;
    state_ = 0;
    step_ = 0;
    recordsState_ = 0;
    recordsStep_ = 0;
    textTask_ = -1;
    backgroundTask_ = -1;
    spriteTask_ = -1;
    profileTask_ = -1;
    sentencesTask_ = -1;
    titleTask_ = -1;
    sentences_ = NULL;
    sentencesSize_ = 0;
    done_ = 0;
    saved_ = 0;
    full_ = 0;
    guest_ = guest;
    active_ = 1;
    profileLoaded_ = 0;
    titlesLoaded_ = 0;
    aborted_ = 0;
    member_ = member;
    if (guest_ == NULL)
    {
        GameObject* object = gameState->GetPartyMemberByIndex(member);
        if (object != NULL)
        {
            PartyMemberData* data = func_02053c6c(object);
            if (data != NULL)
            {
                ClearEntry(&entry_);
                char name[0xc];
                __clear(name, sizeof(name));
                func_020426bc(data->name_, name, 1);
                memcpy(entry_.name_, name, sizeof(entry_.name_));
                entry_.used_ = 1;
                func_0202ae18();
                if (func_0202b7d8())
                {
                    func_ov017_021d1014(member, 0, 0);
                    func_ov017_021d1118(member, 1, 1, 0);
                }
            }
        }
    }
    else
    {
        unk_e98 = 0xff;
        memcpy(&profile_, &guest_->profile_, sizeof(ProfileData));
    }
}

static void ClearEntry(GuestEntry* entry)
{
    VectorizedMemset(entry->id_, 0, sizeof(entry->id_));
    memset(entry->name_, 0, sizeof(entry->name_));
    entry->unk_12_0 = 0;
    entry->unk_11 = 0;
    entry->used_ = 0;
    VectorizedMemset(&entry->records_, 0, sizeof(entry->records_));
}

void VisitorTalk::CreateAllocators(SafeAllocator* allocator)
{
    allocator_.CreateTypeA(allocator->Allocate(0xa000), 0xa000);
    textAllocator_.CreateTypeA(allocator->Allocate(0xc00), 0xc00);
    recordsAllocator_.CreateTypeA(allocator->Allocate(0x5c00), 0x5c00);
    spriteAllocator_.CreateTypeA(allocator->Allocate(0x800), 0x800);
    profileAllocator_.CreateTypeA(allocator->Allocate(0x2400), 0x2400);
    titleAllocator_.CreateTypeA(allocator->Allocate(0x5400), 0x5400);
    sprites_ = (Sprite*)allocator->Allocate(0x140);
    renderer_ = (SpriteRenderer*)allocator->Allocate(0x54);
    animations_ = (SpriteAnimationList*)allocator->Allocate(8);
}

unsigned char VisitorTalk::Update()
{
    func_0205d0e0(&window_);
    switch (state_)
    {
        case 2:
            step_ = 0;
            break;
        case 0:
            State_Load();
            break;
        case 1:
            State_Talk();
            break;
    }
    switch (recordsState_)
    {
        case 0:
            OpenRecords();
            break;
        case 1:
            records_.Update();
            break;
        case 2:
            CloseRecords();
            break;
    }
    return done_;
}

void VisitorTalk::Draw1()
{
    func_0205d1e0(&window_);
    func_0205d228(&window_);
    func_0205da88(&window_, 1, 2, 1);
    func_0205d274(&window_);
    DrawCorners();
    if (recordsState_ == 0)
        return;
    if (!active_)
        return;
    records_.Draw1();
}

void VisitorTalk::Draw2()
{
    if (state_ != 0)
        func_0205d2bc(&window_);
    if (recordsState_ == 0)
        return;
    if (!active_)
        return;
    records_.Draw2();
}

void VisitorTalk::Finish()
{
    func_02094ab0(func_02094a00());
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x100;
    *(volatile unsigned short*)REG_BLDCNT = 0;
    func_02074bd0(this);
    func_0205d1e0(&window_);
    func_0205d274(&window_);
    func_0205d2bc(&window_);
    func_0205d048(&window_);
    if (pixels_ != NULL)
    {
        memset(pixels_, 0, 0x20);
        CleanInvalidateCacheRange(pixels_, 0x20);
        LoadToMainBG1CharacterData(pixels_, 0, 0x20);
    }
    text_ = NULL;
    pixels_ = NULL;
    SafeAllocator* allocators[4] = {&allocator_, &textAllocator_, &recordsAllocator_, &spriteAllocator_};
    for (int i = 0; i < 4; i++)
    {
        SafeAllocator* allocator = allocators[i];
        if (allocator->GetSignedAllocator())
            allocator->Destroy();
    }
}

void VisitorTalk::State_Load()
{
    static const int sCanvasSize = 0x100;
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    func_02094a00();
    signed char step = step_;
    if (step == 0)
    {
        if (!func_02046b08(RESOURCE(resources, 0x3700, void*)))
            return;
        func_0203b4a0(func_ov017_0218b5b0(), 0x10);
        func_020466e4(func_020d6c00(), 0xd);
        unsigned int female;
        text_ = (char*)func_020421a0()->unk_5c;
        female = 0;
        GuestData* guest = guest_;
        if (guest == NULL)
        {
            GameObject* member = gameState->GetPartyMemberByIndex(member_);
            if (member == NULL)
            {
                Abort();
                return;
            }
            PartyMemberData* data = func_02053c6c(member);
            if (data != NULL)
                female = data->appearance_.female_;
        }
        else
        {
            female = guest->records_.female_;
        }
        char gp2[0x40];
        char inner[0x20];
        sprintf(gp2, STRING(0, "data/bin/ttlname%d.gp2"), female);
        sprintf(inner, STRING(0x17, "ttlname%d_<LG>.nat"), female);
        textTask_ = loader->QueueLoadFileInGP2(STRING(0x2a, "data/bin/tlkpcstr.gp2"), STRING(0x40, "tlkpcstr_<LG>.bin"),
                                               NULL);
        titleTask_ = loader->QueueLoadFileInGP2(gp2, inner, NULL);
        backgroundTask_ = loader->QueueLoadFile(STRING(0x52, "data/ani/bg_tm.pac"), NULL);
        spriteTask_ = loader->QueueLoadFile(STRING(0x65, "data/ani/obj_tlkpc.pac"), NULL);
        step_++;
    }
    else if (step == 1)
    {
        if (loader->GetTaskStatus(textTask_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(textTask_, &file, &size);
            textAllocator_.Reset();
            func_020728ac(&texts_, &textAllocator_, file, size, 0, 0, 0);
            loader->RemoveTask(textTask_);
            textTask_ = -1;
            step_++;
        }
    }
    else if (step == 2)
    {
        if (loader->GetTaskStatus(titleTask_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(titleTask_, &file, &size);
            titleAllocator_.Reset();
            func_020dfec0(&titles_, &titleAllocator_, file, size);
            titlesLoaded_ = 1;
            loader->RemoveTask(titleTask_);
            titleTask_ = -1;
            allocator_.Reset();
            // The priority and the layer of each background
            unsigned char layers[2] = {1, 2};
            unsigned char priorities[2] = {2, 1};
            BackgroundGraphics* background;
            for (int i = 0; i < 2; i++)
            {
                background = &backgrounds_[i];
                func_0204b11c(background, 0);
                background->unk_1c_0_ = 0;
                background->unk_1c_4_ = layers[i];
                func_0204b5b4(background, priorities[i]);
                func_0204b12c(background, &allocator_);
                func_0204b5e8(background, 0, 0);
            }
            REG_BG1CNT = (REG_BG1CNT & 0x43) | 0x1d00;
            REG_BG2CNT = (REG_BG2CNT & 0x43) | 0x1e00;
            ColorEffect_ConfigureAlphaBlend(REG_BLDCNT, 2, 1, 10, 6);
            step_++;
        }
    }
    else if (step == 3)
    {
        if (loader->GetTaskStatus(backgroundTask_))
        {
            char name[4];
            void* archive;
            unsigned int archiveSize;
            loader->GetLoadedFileByID(backgroundTask_, &archive, &archiveSize);
            int count = func_02046900(archive);
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(archive, i, name, &size);
                if (file != NULL)
                    func_0204b174(&backgrounds_[1], file, &allocator_, size);
            }
            loader->RemoveTask(backgroundTask_);
            backgroundTask_ = -1;
            BackgroundGraphics* background;
            for (int i = 0; i < 2; i++)
            {
                background = &backgrounds_[i];
                func_0204bc74(background, 0, 0, 0, 0x20, 0x19, 0);
                func_0204b0e8(background, 0);
            }
            pixels_ = allocator_.Allocate(0x800);
            func_0204c7a8(&canvas_, &allocator_, pixels_, sCanvasSize);
            canvas_.background_ = &backgrounds_[1];
            window_.background_ = &backgrounds_[0];
            window_.unk_b2 = 2;
            func_0205cf78(&window_, &canvas_, 1);
            for (unsigned char i = 0; i < 8; i++)
            {
                int offset = i * sizeof(Sprite);
                func_0205a198((Sprite*)((char*)sprites_ + offset));
                ((Sprite*)((char*)sprites_ + offset))->unk_22 = i + 4;
            }
            func_0205a234(animations_);
            func_0205a444(renderer_);
            renderer_->unk_50 = 0;
            SpriteRenderer* renderer = renderer_;
            renderer->SetSprites(sprites_, 8);
            renderer_->animations_ = animations_;
            step_++;
        }
    }
    else if (step == 4)
    {
        if (loader->GetTaskStatus(spriteTask_))
        {
            char name[4];
            void* archive;
            unsigned int archiveSize;
            loader->GetLoadedFileByID(spriteTask_, &archive, &archiveSize);
            int count = func_02046900(archive);
            spriteAllocator_.Reset();
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                func_0205a528(renderer_, func_020467f0(archive, i, name, &size), size, &spriteAllocator_);
            }
            loader->RemoveTask(spriteTask_);
            spriteTask_ = -1;
            REG_BG0CNT = (REG_BG0CNT & ~3) | 2;
            REG_BG1CNT = (REG_BG1CNT & ~3) | 1;
            REG_BG2CNT = REG_BG2CNT & ~3;
            REG_BG3CNT = (REG_BG3CNT & ~3) | 3;
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1700;
            func_02094b34(func_02094a00(), 0x6b, 0x206, 0, 0);
            step_++;
        }
    }
    else if (step == 5)
    {
        if (func_02094b4c(func_02094a00()))
        {
            WriteCard();
            profileTask_ = loader->QueueLoadFileInGP2(STRING(0x7c, "data/bin/profstr.gp2"),
                                                      STRING(0x91, "profstr_<LG>.bin"), NULL);
            sentencesTask_ = loader->QueueLoadFileInGP2(STRING(0xa2, "data/bin/profsen.gp2"),
                                                        STRING(0xb7, "profsen_<LG>.bin"), NULL);
            state_ = 1;
            step_ = 0;
        }
    }
}

// The 6 bytes that identify a visitor
struct GuestId
{
    unsigned char bytes_[6];
};

// NONMATCHING: the C matches 69.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void VisitorTalk::State_Talk()
{
    GameState* gameState = GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    MessageSystem* messages = func_020421a0();
    GameResources* resources = func_ov017_0218b5b0();
    char* scene = RESOURCE(resources, 0x3b84, char*);
    signed char step = step_;
    Unknown_0202ae18* unk = func_0202ae18();
    if (step == 0)
    {
        if ((unk_e98 & 2) && loader->GetTaskStatus(profileTask_) && loader->GetTaskStatus(sentencesTask_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(profileTask_, &file, &size);
            profileAllocator_.Reset();
            func_020728ac(&profileTexts_, &profileAllocator_, file, size, 0, 0, 0);
            records_.guestTexts_ = &profileTexts_;
            profileLoaded_ = 1;
            loader->GetLoadedFileByID(sentencesTask_, &file, &size);
            sentences_ = file;
            sentencesSize_ = size;
            func_020466f4(func_020d6c00(), 0x2f);
            func_0203b4b0(func_ov017_0218b5b0(), 0x10);
            step_++;
        }
    }
    else if (step == 1)
    {
        GameObject* member = gameState->GetPartyMemberByIndex(member_);
        PartyMemberData* data = NULL;
        char name[0x30];
        __clear(name, sizeof(name));
        signed char vocation;
        GuestData* guest = guest_;
        if (guest == NULL)
        {
            if (member == NULL)
            {
                Abort();
                return;
            }
            data = func_02053c6c(member);
            vocation = member->partyData_->vocation_;
            func_02042764(entry_.name_, name, 1);
        }
        else
        {
            func_02042764(guest, name, 1);
            vocation = guest_->vocation_;
        }
        if (data != NULL && !profile_.initialized_)
        {
            profile_.female_ = data->appearance_.female_;
            profile_.unk_0_21 = data->appearance_.female_;
            int accolade = 0x50dc;
            profile_.title_ = 300;
            if (data->appearance_.female_ == 1)
                accolade = 0x510e;
            profile_.accolade_ = accolade - 20000 + member->partyData_->vocation_;
            *(int*)profile_.unk_8 = 0;
        }
        int kind;
        if (guest_ != NULL)
            kind = 3;
        else
            kind = 1;
        const char* title = func_02072a68(&profileTexts_, (short)(profile_.title_ + 10000));
        int accolade = profile_.accolade_;
        const char* accoladeText;
        if (accolade < 700)
        {
            accoladeText = func_020e0434(&titles_, (short)accolade);
        }
        else if (accolade < 800)
        {
            int vocations = 0x50dc;
            if (profile_.female_ == 1)
                vocations = 0x510e;
            accoladeText = func_02072a68(&profileTexts_, (short)(vocation + vocations));
        }
        else
        {
            accoladeText = func_02072a68(&profileTexts_, (short)(accolade + 20000));
        }
        char text[0x400];
        func_02099304(&profile_, name, sentences_, sentencesSize_, text, 0x400, kind, title, accoladeText);
        func_02046380(messages);
        int saved = 0;
        char* end = &text[strlen(text)];
        if (guest_ == NULL)
        {
            char* store = func_0205ec34();
            if (!func_0206dfb0(store, store + 0x8c, 0x119b))
            {
                const char* first = func_02072a68(&texts_, 0x66);
                int length = strlen(first);
                memcpy(end, first, length);
                end = &end[length];
                func_0206df6c(store, store + 0x8c, 0x119b, 1);
            }
            GuestId id = *(GuestId*)entry_.id_;
            GuestEntry* entry = GetVisitors(gameState)->entries_;
            for (int i = 0; i < GetVisitors(gameState)->count_; i++)
            {
                GuestId other = id;
                int same;
                int k;
                for (k = 0; k < 6; k++)
                {
                    if (other.bytes_[k] != entry->id_[k])
                        break;
                }
                same = k >= 6;
                if (same)
                {
                    entry->records_ = entry_.records_;
                    saved = 1;
                    break;
                }
                entry++;
            }
            char buffer[0x100];
            memset(buffer, 0, sizeof(buffer));
            if (!saved)
            {
                const char* format = func_02072a68(&texts_, 0x64);
                MessageName memberName;
                func_020e4bf4(&memberName, member_);
                messages->unk_10 = &memberName;
                func_02046608(messages, 0xc, format, buffer, 0xe3, 0, 1);
                memcpy(end, buffer, strlen(buffer));
            }
        }
        messages->unk_99c = profile_.female_ ? 2 : 0;
        messages->unk_19b2 = 1;
        func_0204500c(messages, text, 0, 0xe3);
        messages->busy_ = 1;
        loader->RemoveTask(profileTask_);
        loader->RemoveTask(sentencesTask_);
        profileTask_ = -1;
        sentencesTask_ = -1;
        if (guest_ != NULL)
        {
            if (guest_->hasMap_ && func_0202c508(unk))
            {
                step_ = 3;
                return;
            }
            step_ = 2;
            return;
        }
        if (saved)
            step_ = 2;
        else
            step_ = 100;
    }
    else if (step == 100)
    {
        if (messages->busy_ == 0)
        {
            if (!func_020457e0(messages))
            {
                char buffer[0x80];
                memset(buffer, 0, sizeof(buffer));
                if (GetVisitors(gameState)->count_ >= 16)
                {
                    const char* full = func_02072a68(&texts_, 0x69);
                    memcpy(buffer, full, strlen(full));
                    full_ = 1;
                }
                else
                {
                    const char* format = func_02072a68(&texts_, 0x68);
                    MessageName memberName;
                    func_020e4bf4(&memberName, member_);
                    messages->unk_10 = &memberName;
                    func_02046608(messages, 0xc, format, buffer, 0xe3, 0, 1);
                    AddVisitor();
                }
                messages->unk_99c = profile_.female_ ? 2 : 0;
                messages->unk_19b2 = 1;
                func_0204500c(messages, buffer, 0, 0xe3);
                messages->busy_ = 1;
            }
            step_ = 2;
        }
    }
    else if (step == 2)
    {
        if (messages->busy_ == 0)
        {
            if (!func_020457e0(messages) && full_ != 0)
            {
                memcpy(scene + 0x28, &entry_, sizeof(GuestEntry));
                scene[9] = 1;
                saved_ = 1;
            }
            func_0205d6a0(&window_, 1);
            state_ = 2;
            step_ = 0;
            recordsState_ = 2;
            recordsStep_ = 0;
        }
    }
    else if (step == 3)
    {
        if (messages->busy_ == 0)
        {
            TreasureMapMetadata map = guest_->map_;
            DetailedTreasureMapData details;
            func_020a3720();
            ExportDetailedTreasureMapData(&map, &details, 0, 0);
            func_020a395c();
            if (details.mapType_ == 1)
                func_020464e8(messages, 2, details.regular_.topScreenName_);
            else if (details.mapType_ == 2)
                func_020464e8(messages, 2, details.legacy_.topScreenName_);
            else
            {
                step_ = 2;
                return;
            }
            char guestName[0x30];
            __clear(guestName, sizeof(guestName));
            func_02042764(guest_, guestName, 1);
            MessageName guestMessageName;
            func_020e4b34(&guestMessageName, guestName, guestName, 0, 0, 0, 0, guest_->female_, 0, 1, 0, 1);
            MessageName heroName;
            func_020e4bf4(&heroName, func_020100b0(gameState));
            messages->unk_10 = &guestMessageName;
            messages->arguments_ = &heroName;
            if (func_02011804(gameState) >= 99)
                func_0204500c(messages, func_02072a68(&texts_, 0xc9), 0, 0xe3);
            else
                func_0204500c(messages, func_02072a68(&texts_, 0xca), 0, 0xe3);
            messages->busy_ = 1;
            messages->unk_19b2 = 0;
            step_ = 4;
        }
    }
    else if (step == 4)
    {
        if (messages->busy_ == 0)
        {
            if (func_02011804(gameState) >= 99)
            {
                MessageName heroName;
                func_020e4bf4(&heroName, func_020100b0(gameState));
                messages->arguments_ = &heroName;
                messages->unk_2c8 = 1;
                func_0204500c(messages, func_02072a68(&texts_, 0xcb), 0, 0xe3);
                messages->busy_ = 1;
                messages->unk_19b2 = 1;
                step_ = 5;
                return;
            }
            TreasureMapList maps;
            func_020ac760(&maps);
            VectorizedMemset(&maps.maps_[maps.count_], 0, sizeof(TreasureMapMetadata));
            maps.maps_[maps.count_] = guest_->map_;
            maps.count_++;
            func_020ac734(&maps);
            guest_->hasMap_ = 0;
            step_ = 2;
        }
    }
    else if (step == 5)
    {
        if (messages->busy_ == 0)
        {
            int answer = func_020457e0(messages);
            if (answer == 0)
            {
                step_ = 2;
            }
            else if (answer == 1)
            {
                TreasureMapMetadata map = guest_->map_;
                DetailedTreasureMapData details;
                func_020a3720();
                ExportDetailedTreasureMapData(&map, &details, 0, 0);
                func_020a395c();
                GrottoEntry grotto;
                VectorizedMemset(&grotto, 0, sizeof(grotto));
                grotto.discoveredBy_[0] = 0;
                grotto.clearedBy_[0] = 0;
                grotto.unk_6 = 0;
                grotto.location_ = -1;
                grotto.type_ = map.GetMapType();
                grotto.seed_ = map.SeedOrMinTurns;
                grotto.level_ = map.LegacyBossLevel;
                grotto.unk_6 = 0;
                grotto.quality_ = map.QualityOrLegacyBossID;
                strcpy(grotto.discoveredBy_, map.DiscoveredBy);
                strcpy(grotto.clearedBy_, map.ClearedBy);
                grotto.flags_ = map.TreasureDiscoveryFlags;
                if (grotto.type_ == 2)
                    grotto.unk_26 = (unsigned char)map.SeedOrMinTurns;
                grotto.location_ = map.Location;
                func_02011818(gameState, &grotto);
                if (map.GetMapType() == 1)
                {
                    func_02011ab8(gameState);
                    func_02011a74(gameState, 0, details.regular_.topScreenName_);
                }
                else if (map.GetMapType() == 2)
                {
                    func_02011a74(gameState, 0, details.legacy_.topScreenName_);
                }
                *(unsigned int*)((char*)gameState + 0x6474) = guest_->unk_10_2;
                func_ov017_021a9ff0(0);
                func_0205d6a0(&window_, 1);
                step_ = 2;
            }
        }
    }
    else if (step == 6)
    {
        if (RESOURCE(resources, 0x3b4c, char*)[2] == 0)
        {
            func_020a1940((unsigned int)OVERLAY_8_ID);
            active_ = 0;
            step_ = 7;
        }
    }
    else if (step == 7)
    {
        GameObject* object = gameState->GetUnknownGameObject();
        if (object != NULL)
            func_020397cc(object, 1);
        if (*((char*)gameState + 0x646e) != 0)
        {
            TreasureMapMetadata map = guest_->map_;
            DetailedTreasureMapData details;
            func_020a3720();
            ExportDetailedTreasureMapData(&map, &details, 0, 0);
            func_020a395c();
            if (details.mapType_ == 1)
                func_020464e8(messages, 2, details.regular_.topScreenName_);
            else if (details.mapType_ == 2)
                func_020464e8(messages, 2, details.legacy_.topScreenName_);
            char guestName[0x30];
            __clear(guestName, sizeof(guestName));
            func_02042764(guest_, guestName, 1);
            func_02046574(messages, 0, guestName);
            func_02046574(messages, 1, *(const char**)((char*)gameState->GetUnknownGameObject() + 0x134));
            func_0204500c(messages, func_02072a68(&texts_, 0xca), 0, 0xe3);
            messages->busy_ = 1;
            messages->unk_19b2 = 0;
            guest_->hasMap_ = 0;
        }
        step_ = 2;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11VisitorTalk10AddVisitorEv(); // VisitorTalk::AddVisitor
    void _ZN11VisitorTalk5AbortEv(); // VisitorTalk::Abort
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState20GetUnknownGameObjectEv(); // GameState::GetUnknownGameObject
    void _ZN9GameState21GetPartyMemberByIndexEi(); // GameState::GetPartyMemberByIndex
    void _ZNK19TreasureMapMetadata10GetMapTypeEv(); // TreasureMapMetadata::GetMapType
}

asm void VisitorTalk::State_Talk()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x1700
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    mov r5, r0
    bl func_020421a0
    mov r6, r0
    bl func_ov017_0218b5b0
    mov r7, r0
    add r0, r7, #0x3000
    ldr r8, [r0, #0xb84]
    bl func_0202ae18
    add r1, r10, #0xe00
    ldrsb r2, [r1, #0x9a]
    str r0, [sp, #0x20]
    cmp r2, #0x0
    bne @L02189d94
    ldrb r0, [r10, #0xe98]
    tst r0, #0x2
    beq @L0218aa04
    ldr r1, [r10, #0xeac]
    mov r0, r5
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0218aa04
    ldr r1, [r10, #0xeb0]
    mov r0, r5
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L0218aa04
    ldr r1, [r10, #0xeac]
    add r2, sp, #0x34
    add r3, sp, #0x30
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    add r0, r10, #0x250
    bl _ZN13SafeAllocator5ResetEv
    mov r0, #0x0
    str r0, [sp, #0x0]
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    ldr r2, [sp, #0x34]
    ldr r3, [sp, #0x30]
    add r0, r10, #0x280
    add r1, r10, #0x250
    bl func_020728ac
    add r1, r10, #0x280
    str r1, [r10, #0xde0]
    ldrb r1, [r10, #0xec0]
    mov r0, r5
    add r2, sp, #0x34
    orr r1, r1, #0x2
    strb r1, [r10, #0xec0]
    ldr r1, [r10, #0xeb0]
    add r3, sp, #0x30
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x34]
    str r0, [r10, #0xec4]
    ldr r0, [sp, #0x30]
    str r0, [r10, #0xec8]
    bl func_020d6c00
    mov r1, #0x2f
    bl func_020466f4
    bl func_ov017_0218b5b0
    mov r1, #0x10
    bl func_0203b4b0
    add r0, r10, #0xe00
    ldrsb r0, [r0, #0x9a]
    add r0, r0, #0x1
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L02189d94:
    cmp r2, #0x1
    bne @L0218a278
    ldrsb r1, [r1, #0xb9]
    mov r0, r4
    bl _ZN9GameState21GetPartyMemberByIndexEi
    mov r7, r0
    add r0, sp, #0x114
    mov r1, #0x30
    mov r8, #0x0
    bl __clear
    ldr r0, [r10, #0xebc]
    cmp r0, #0x0
    bne @L02189e14
    cmp r7, #0x0
    bne @L02189ddc
    mov r0, r10
    bl _ZN11VisitorTalk5AbortEv
    b @L0218aa04
@L02189ddc:
    mov r0, r7
    bl func_02053c6c
    ldr r1, [r7, #0x150]
    add r2, r10, #0xf6
    ldr r1, [r1, #0x950]
    mov r8, r0
    mov r3, r1, lsl #0x18
    add r0, r2, #0xd00
    add r1, sp, #0x114
    mov r2, #0x1
    mov r9, r3, asr #0x18
    bl func_02042764
    add r11, sp, #0x114
    b @L02189e3c
@L02189e14:
    add r1, sp, #0x114
    mov r2, #0x1
    bl func_02042764
    ldr r0, [r10, #0xebc]
    add r11, sp, #0x114
    ldr r0, [r0, #0xc]
    mov r0, r0, lsl #0x1c
    mov r0, r0, lsr #0x1c
    mov r0, r0, lsl #0x18
    mov r9, r0, asr #0x18
@L02189e3c:
    cmp r8, #0x0
    beq @L02189ef0
    ldr r0, [r10, #0xe1c]
    mov r1, r0, lsl #0x5
    movs r1, r1, lsr #0x1f
    bne @L02189ef0
    add r1, r8, #0x88
    ldrb r3, [r1, #0x414]
    bic r0, r0, #0x2000000
    ldr r2, =0xfff801ff
    mov r3, r3, lsl #0x1f
    mov r3, r3, lsr #0x1f
    mov r3, r3, lsl #0x1f
    orr r0, r0, r3, lsr #0x6
    str r0, [r10, #0xe1c]
    ldrb r3, [r1, #0x414]
    bic r0, r0, #0x1e00000
    mov r3, r3, lsl #0x1f
    mov r3, r3, lsr #0x1f
    mov r3, r3, lsl #0x1c
    orr r0, r0, r3, lsr #0x7
    str r0, [r10, #0xe1c]
    ldr r3, [r10, #0xe20]
    ldr r0, =0x50dc
    and r2, r3, r2
    orr r2, r2, #0x25800
    str r2, [r10, #0xe20]
    ldrb r1, [r1, #0x414]
    ldr r2, [r7, #0x150]
    mov r1, r1, lsl #0x1f
    mov r1, r1, lsr #0x1f
    cmp r1, #0x1
    ldr r1, =0xffffb1e0
    addeq r0, r0, #0x32
    ldr r2, [r2, #0x950]
    add r0, r0, r1
    add r1, r0, r2
    ldr r2, [r10, #0xe20]
    ldr r0, =0xc007ffff
    mov r1, r1, lsl #0x15
    and r0, r2, r0
    orr r0, r0, r1, lsr #0x2
    str r0, [r10, #0xe20]
    mov r0, #0x0
    strb r0, [r10, #0xe24]
@L02189ef0:
    ldr r1, [r10, #0xe20]
    ldr r0, [r10, #0xebc]
    mov r1, r1, lsl #0xd
    mov r1, r1, asr #0x16
    add r1, r1, #0x710
    add r1, r1, #0x2000
    mov r1, r1, lsl #0x10
    cmp r0, #0x0
    movne r7, #0x3
    add r0, r10, #0x280
    mov r1, r1, asr #0x10
    moveq r7, #0x1
    bl func_02072a68
    ldr r1, [r10, #0xe20]
    mov r8, r0
    mov r0, r1, lsl #0x2
    mov r0, r0, asr #0x15
    cmp r0, #0x2bc
    bge @L02189f50
    mov r1, r0, lsl #0x10
    add r0, r10, #0x288
    mov r1, r1, asr #0x10
    bl func_020e0434
    b @L02189fa0
@L02189f50:
    cmp r0, #0x320
    bge @L02189f88
    ldr r0, [r10, #0xe1c]
    ldr r1, =0x50dc
    mov r0, r0, lsl #0x6
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    addeq r1, r1, #0x32
    add r0, r9, r1
    mov r1, r0, lsl #0x10
    add r0, r10, #0x280
    mov r1, r1, asr #0x10
    bl func_02072a68
    b @L02189fa0
@L02189f88:
    add r0, r0, #0xe20
    add r0, r0, #0x4000
    mov r1, r0, lsl #0x10
    add r0, r10, #0x280
    mov r1, r1, asr #0x10
    bl func_02072a68
@L02189fa0:
    add r2, sp, #0x1300
    mov r1, #0x400
    str r2, [sp, #0x0]
    stmib sp, {r1, r7, r8}
    str r0, [sp, #0x10]
    add r0, r10, #0x21c
    ldr r2, [r10, #0xec4]
    ldr r3, [r10, #0xec8]
    mov r1, r11
    add r0, r0, #0xc00
    bl func_02099304
    mov r0, r6
    bl func_02046380
    add r8, sp, #0x1300
    mov r0, r8
    mov r7, #0x0
    bl strlen
    ldr r1, [r10, #0xebc]
    add r8, r8, r0
    cmp r1, #0x0
    bne @L0218a1bc
    bl func_0205ec34
    mov r11, r0
    ldr r2, =0x119b
    add r1, r11, #0x8c
    bl func_0206dfb0
    cmp r0, #0x0
    bne @L0218a050
    add r0, r10, #0x278
    mov r1, #0x66
    bl func_02072a68
    mov r9, r0
    bl strlen
    mov r1, r9
    mov r9, r0
    mov r0, r8
    mov r2, r9
    bl memcpy
    add r8, r8, r9
    mov r0, r11
    add r1, r11, #0x8c
    ldr r2, =0x119b
    mov r3, #0x1
    bl func_0206df6c
@L0218a050:
    add r0, r4, #0x1fc
    add r12, r0, #0x7000
    add r2, sp, #0x2a
    add r9, r12, #0x4
    add r3, r10, #0xdf0
    mov r1, #0x6
@L0218a068:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L0218a068
    mov r11, #0x0
    add r0, sp, #0x24
    mov lr, r11
    b @L0218a12c
@L0218a088:
    add r4, sp, #0x2a
    add r3, sp, #0x24
    mov r2, #0x6
@L0218a094:
    ldrb r1, [r4], #0x1
    subs r2, r2, #0x1
    strb r1, [r3], #0x1
    bne @L0218a094
    mov r3, lr
    b @L0218a0c4
@L0218a0ac:
    ldrb r2, [r0, r3]
    ldrb r1, [r9, r3]
    cmp r2, r1
    movne r1, #0x0
    bne @L0218a0d0
    add r3, r3, #0x1
@L0218a0c4:
    cmp r3, #0x6
    blt @L0218a0ac
    mov r1, #0x1
@L0218a0d0:
    cmp r1, #0x0
    beq @L0218a124
    ldr r1, [r10, #0xe04]
    add r0, r10, #0xe00
    str r1, [r9, #0x14]
    ldr r1, [r10, #0xe08]
    mov r7, #0x1
    str r1, [r9, #0x18]
    ldr r1, [r10, #0xe0c]
    str r1, [r9, #0x1c]
    ldr r1, [r10, #0xe10]
    str r1, [r9, #0x20]
    ldr r1, [r10, #0xe14]
    str r1, [r9, #0x24]
    ldrsh r0, [r0, #0x18]
    strh r0, [r9, #0x28]
    ldrb r0, [r10, #0xe1a]
    strb r0, [r9, #0x2a]
    ldrb r0, [r10, #0xe1b]
    strb r0, [r9, #0x2b]
    b @L0218a138
@L0218a124:
    add r11, r11, #0x1
    add r9, r9, #0x2c
@L0218a12c:
    ldrb r1, [r12, #0x0]
    cmp r11, r1
    blt @L0218a088
@L0218a138:
    add r0, sp, #0x1200
    mov r1, #0x0
    mov r2, #0x100
    bl memset
    cmp r7, #0x0
    bne @L0218a1bc
    add r0, r10, #0x278
    mov r1, #0x64
    bl func_02072a68
    add r1, r10, #0xe00
    mov r4, r0
    ldrsb r1, [r1, #0xb9]
    add r0, sp, #0x144
    bl func_020e4bf4
    add r1, sp, #0x144
    str r1, [r6, #0x10]
    mov r0, #0xe3
    str r0, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    mov r0, #0x1
    str r0, [sp, #0x8]
    mov r2, r4
    mov r0, r6
    mov r1, #0xc
    add r3, sp, #0x1200
    bl func_02046608
    add r0, sp, #0x1200
    bl strlen
    mov r2, r0
    mov r0, r8
    add r1, sp, #0x1200
    bl memcpy
@L0218a1bc:
    ldr r0, [r10, #0xe1c]
    add r1, sp, #0x1300
    mov r0, r0, lsl #0x6
    movs r0, r0, lsr #0x1f
    moveq r0, #0x0
    movne r0, #0x2
    str r0, [r6, #0x99c]
    mov r0, r6
    add r4, r6, #0x1000
    mov r8, #0x1
    mov r2, #0x0
    mov r3, #0xe3
    strb r8, [r4, #0x9b2]
    bl func_0204500c
    mov r0, r8
    str r0, [r6, #0x998]
    ldr r1, [r10, #0xeac]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    ldr r1, [r10, #0xeb0]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xeac]
    str r0, [r10, #0xeb0]
    ldr r0, [r10, #0xebc]
    cmp r0, #0x0
    beq @L0218a260
    ldrb r0, [r0, #0xb]
    mov r0, r0, lsl #0x18
    movs r0, r0, lsr #0x1f
    beq @L0218a254
    ldr r0, [sp, #0x20]
    bl func_0202c508
    cmp r0, #0x0
    movne r0, #0x3
    strneb r0, [r10, #0xe9a]
    bne @L0218aa04
@L0218a254:
    mov r0, #0x2
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a260:
    cmp r7, #0x0
    movne r0, #0x2
    strneb r0, [r10, #0xe9a]
    moveq r0, #0x64
    streqb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a278:
    cmp r2, #0x64
    bne @L0218a390
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218aa04
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x0
    bne @L0218a384
    add r0, sp, #0x1180
    mov r1, #0x0
    mov r2, #0x80
    bl memset
    add r0, r4, #0x7000
    ldrb r0, [r0, #0x1fc]
    cmp r0, #0x10
    add r0, r10, #0x278
    blo @L0218a2ec
    mov r1, #0x69
    bl func_02072a68
    mov r4, r0
    bl strlen
    mov r2, r0
    add r0, sp, #0x1180
    mov r1, r4
    bl memcpy
    mov r0, #0x1
    strb r0, [r10, #0xebb]
    b @L0218a344
@L0218a2ec:
    mov r1, #0x68
    bl func_02072a68
    add r1, r10, #0xe00
    mov r4, r0
    ldrsb r1, [r1, #0xb9]
    add r0, sp, #0x144
    bl func_020e4bf4
    add r1, sp, #0x144
    str r1, [r6, #0x10]
    mov r0, #0xe3
    str r0, [sp, #0x0]
    mov r1, #0x0
    str r1, [sp, #0x4]
    mov r1, #0x1
    str r1, [sp, #0x8]
    add r3, sp, #0x1180
    mov r0, r6
    mov r2, r4
    mov r1, #0xc
    bl func_02046608
    mov r0, r10
    bl _ZN11VisitorTalk10AddVisitorEv
@L0218a344:
    ldr r0, [r10, #0xe1c]
    add r1, sp, #0x1180
    mov r0, r0, lsl #0x6
    movs r0, r0, lsr #0x1f
    moveq r0, #0x0
    movne r0, #0x2
    str r0, [r6, #0x99c]
    mov r0, r6
    add r4, r6, #0x1000
    mov r5, #0x1
    mov r2, #0x0
    mov r3, #0xe3
    strb r5, [r4, #0x9b2]
    bl func_0204500c
    mov r0, r5
    str r0, [r6, #0x998]
@L0218a384:
    mov r0, #0x2
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a390:
    cmp r2, #0x2
    bne @L0218a404
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218aa04
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x0
    bne @L0218a3dc
    ldrb r0, [r10, #0xebb]
    cmp r0, #0x0
    beq @L0218a3dc
    add r0, r8, #0x28
    add r1, r10, #0xdf0
    mov r2, #0x2c
    bl memcpy
    mov r0, #0x1
    strb r0, [r8, #0x9]
    strb r0, [r10, #0xeba]
@L0218a3dc:
    add r0, r10, #0x18
    mov r1, #0x1
    bl func_0205d6a0
    mov r1, #0x2
    strb r1, [r10, #0xe99]
    mov r0, #0x0
    strb r0, [r10, #0xe9a]
    strb r1, [r10, #0xe9b]
    strb r0, [r10, #0xe9c]
    b @L0218aa04
@L0218a404:
    cmp r2, #0x3
    bne @L0218a59c
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218aa04
    ldr r0, [r10, #0xebc]
    add r2, sp, #0xf8
    add r3, r0, #0x50
    mov r1, #0xe
@L0218a428:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L0218a428
    bl func_020a3720
    mov r2, #0x0
    add r1, sp, #0xf00
    add r0, sp, #0xf8
    add r1, r1, #0xbc
    mov r3, r2
    bl ExportDetailedTreasureMapData
    bl func_020a395c
    ldrb r0, [sp, #0xfbd]
    cmp r0, #0x1
    bne @L0218a47c
    add r2, sp, #0x1000
    add r2, r2, #0x6b
    mov r0, r6
    mov r1, #0x2
    bl func_020464e8
    b @L0218a4a4
@L0218a47c:
    cmp r0, #0x2
    bne @L0218a498
    add r2, sp, #0x1100
    mov r0, r6
    mov r1, #0x2
    bl func_020464e8
    b @L0218a4a4
@L0218a498:
    mov r0, #0x2
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a4a4:
    add r0, sp, #0xc8
    mov r1, #0x30
    bl __clear
    ldr r0, [r10, #0xebc]
    add r1, sp, #0xc8
    mov r2, #0x1
    bl func_02042764
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    str r3, [sp, #0x8]
    ldr r0, [r10, #0xebc]
    mov r2, #0x1
    ldrb r5, [r0, #0x2e]
    add r1, sp, #0xc8
    add r0, sp, #0x144
    mov r5, r5, lsl #0x1f
    mov r5, r5, lsr #0x1f
    str r5, [sp, #0xc]
    str r3, [sp, #0x10]
    str r2, [sp, #0x14]
    str r3, [sp, #0x18]
    str r2, [sp, #0x1c]
    mov r2, r1
    bl func_020e4b34
    mov r0, r4
    bl func_020100b0
    mov r1, r0
    add r0, sp, #0x150
    bl func_020e4bf4
    add r2, sp, #0x144
    mov r0, r4
    add r1, sp, #0x150
    str r2, [r6, #0x10]
    str r1, [r6, #0x0]
    bl func_02011804
    cmp r0, #0x63
    add r0, r10, #0x278
    blo @L0218a560
    mov r1, #0xc9
    bl func_02072a68
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    b @L0218a57c
@L0218a560:
    mov r1, #0xca
    bl func_02072a68
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
@L0218a57c:
    mov r0, #0x1
    str r0, [r6, #0x998]
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    mov r0, #0x4
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a59c:
    cmp r2, #0x4
    bne @L0218a700
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218aa04
    mov r0, r4
    bl func_02011804
    cmp r0, #0x63
    blo @L0218a620
    mov r0, r4
    bl func_020100b0
    mov r1, r0
    add r0, sp, #0x150
    bl func_020e4bf4
    add r1, sp, #0x150
    str r1, [r6, #0x0]
    mov r2, #0x1
    add r0, r10, #0x278
    mov r1, #0xcb
    str r2, [r6, #0x2c8]
    bl func_02072a68
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r1, #0x1
    str r1, [r6, #0x998]
    add r0, r6, #0x1000
    strb r1, [r0, #0x9b2]
    mov r0, #0x5
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a620:
    add r0, sp, #0x400
    add r0, r0, #0xe4
    bl func_020ac760
    add r0, sp, #0x400
    ldrb r1, [sp, #0x4e4]
    add r0, r0, #0xe6
    mov r2, #0x1c
    mla r0, r1, r2, r0
    mov r1, #0x0
    bl VectorizedMemset
    ldr r1, [r10, #0xebc]
    add r4, sp, #0x400
    ldrb r2, [sp, #0x4e4]
    mov r0, #0x1c
    ldrb r3, [r1, #0x50]
    smulbb r0, r2, r0
    add r4, r4, #0xe6
    strb r3, [r4, r0]
    add r2, r4, r0
    add r5, r1, #0x51
    add r4, r2, #0x1
    mov r3, #0xa
@L0218a678:
    ldrb r0, [r5], #0x1
    subs r3, r3, #0x1
    strb r0, [r4], #0x1
    bne @L0218a678
    add r5, r1, #0x5b
    add r4, r2, #0xb
    mov r3, #0xa
@L0218a694:
    ldrb r0, [r5], #0x1
    subs r3, r3, #0x1
    strb r0, [r4], #0x1
    bne @L0218a694
    ldrb r3, [r1, #0x65]
    add r0, sp, #0x400
    add r0, r0, #0xe4
    strb r3, [r2, #0x15]
    ldrb r3, [r1, #0x66]
    strb r3, [r2, #0x16]
    ldrb r3, [r1, #0x67]
    strb r3, [r2, #0x17]
    ldrb r3, [r1, #0x68]
    strb r3, [r2, #0x18]
    ldrh r1, [r1, #0x6a]
    strh r1, [r2, #0x1a]
    ldrb r1, [sp, #0x4e4]
    add r1, r1, #0x1
    strb r1, [sp, #0x4e4]
    bl func_020ac734
    ldr r2, [r10, #0xebc]
    mov r0, #0x2
    ldrb r1, [r2, #0xb]
    bic r1, r1, #0x80
    strb r1, [r2, #0xb]
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a700:
    cmp r2, #0x5
    bne @L0218a890
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218aa04
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x0
    moveq r0, #0x2
    streqb r0, [r10, #0xe9a]
    beq @L0218aa04
    cmp r0, #0x1
    bne @L0218aa04
    ldr r0, [r10, #0xebc]
    add r2, sp, #0xac
    add r3, r0, #0x50
    mov r1, #0xe
@L0218a744:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L0218a744
    bl func_020a3720
    mov r2, #0x0
    add r0, sp, #0xac
    add r1, sp, #0x320
    mov r3, r2
    bl ExportDetailedTreasureMapData
    bl func_020a395c
    add r0, sp, #0x84
    mov r1, #0x0
    mov r2, #0x28
    bl VectorizedMemset
    mov r0, #0x0
    strb r0, [sp, #0x8b]
    strb r0, [sp, #0x97]
    strb r0, [sp, #0x8a]
    sub r0, r0, #0x1
    str r0, [sp, #0xa4]
    add r0, sp, #0xac
    bl _ZNK19TreasureMapMetadata10GetMapTypeEv
    strb r0, [sp, #0x84]
    ldrh r0, [sp, #0xc6]
    ldrb r1, [sp, #0xc4]
    ldrb r2, [sp, #0xc3]
    strh r0, [sp, #0x88]
    mov r0, #0x0
    strb r1, [sp, #0x86]
    strb r0, [sp, #0x8a]
    add r0, sp, #0x8b
    add r1, sp, #0xad
    strb r2, [sp, #0x85]
    bl strcpy
    add r0, sp, #0x97
    add r1, sp, #0xb7
    bl strcpy
    ldrb r0, [sp, #0x84]
    ldrb r1, [sp, #0xc2]
    ldrb r2, [sp, #0xc1]
    cmp r0, #0x2
    ldreqh r0, [sp, #0xc6]
    strb r1, [sp, #0xa8]
    add r1, sp, #0x84
    streqh r0, [sp, #0xaa]
    mov r0, r4
    str r2, [sp, #0xa4]
    bl func_02011818
    add r0, sp, #0xac
    bl _ZNK19TreasureMapMetadata10GetMapTypeEv
    cmp r0, #0x1
    bne @L0218a838
    mov r0, r4
    bl func_02011ab8
    add r2, sp, #0x300
    add r2, r2, #0xcf
    mov r0, r4
    mov r1, #0x0
    bl func_02011a74
    b @L0218a85c
@L0218a838:
    add r0, sp, #0xac
    bl _ZNK19TreasureMapMetadata10GetMapTypeEv
    cmp r0, #0x2
    bne @L0218a85c
    add r2, sp, #0x400
    add r2, r2, #0x64
    mov r0, r4
    mov r1, #0x0
    bl func_02011a74
@L0218a85c:
    ldr r0, [r10, #0xebc]
    add r1, r4, #0x6000
    ldr r2, [r0, #0x10]
    mov r0, #0x0
    mov r2, r2, lsr #0x2
    str r2, [r1, #0x474]
    bl func_ov017_021a9ff0
    add r0, r10, #0x18
    mov r1, #0x1
    bl func_0205d6a0
    mov r0, #0x2
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a890:
    cmp r2, #0x6
    bne @L0218a8cc
    add r0, r7, #0x3000
    ldr r0, [r0, #0xb4c]
    ldrb r0, [r0, #0x2]
    cmp r0, #0x0
    bne @L0218aa04
    ldr r0, =0x8
    bl func_020a1940
    ldrb r1, [r10, #0xec0]
    mov r0, #0x7
    bic r1, r1, #0x1
    strb r1, [r10, #0xec0]
    strb r0, [r10, #0xe9a]
    b @L0218aa04
@L0218a8cc:
    cmp r2, #0x7
    bne @L0218aa04
    mov r0, r4
    bl _ZN9GameState20GetUnknownGameObjectEv
    cmp r0, #0x0
    beq @L0218a8ec
    mov r1, #0x1
    bl func_020397cc
@L0218a8ec:
    add r0, r4, #0x6000
    ldrb r0, [r0, #0x46e]
    cmp r0, #0x0
    beq @L0218a9fc
    ldr r0, [r10, #0xebc]
    add r2, sp, #0x68
    add r3, r0, #0x50
    mov r1, #0xe
@L0218a90c:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L0218a90c
    bl func_020a3720
    mov r2, #0x0
    add r0, sp, #0x68
    add r1, sp, #0x15c
    mov r3, r2
    bl ExportDetailedTreasureMapData
    bl func_020a395c
    ldrb r0, [sp, #0x15d]
    cmp r0, #0x1
    bne @L0218a95c
    add r2, sp, #0x200
    add r2, r2, #0xb
    mov r0, r6
    mov r1, #0x2
    bl func_020464e8
    b @L0218a974
@L0218a95c:
    cmp r0, #0x2
    bne @L0218a974
    add r2, sp, #0x2a0
    mov r0, r6
    mov r1, #0x2
    bl func_020464e8
@L0218a974:
    add r0, sp, #0x38
    mov r1, #0x30
    bl __clear
    ldr r0, [r10, #0xebc]
    add r1, sp, #0x38
    mov r2, #0x1
    bl func_02042764
    add r2, sp, #0x38
    mov r0, r6
    mov r1, #0x0
    bl func_02046574
    mov r0, r4
    bl _ZN9GameState20GetUnknownGameObjectEv
    ldr r2, [r0, #0x134]
    mov r0, r6
    mov r1, #0x1
    bl func_02046574
    add r0, r10, #0x278
    mov r1, #0xca
    bl func_02072a68
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r0, #0x1
    str r0, [r6, #0x998]
    add r0, r6, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x9b2]
    ldr r1, [r10, #0xebc]
    ldrb r0, [r1, #0xb]
    bic r0, r0, #0x80
    strb r0, [r1, #0xb]
@L0218a9fc:
    mov r0, #0x2
    strb r0, [r10, #0xe9a]
@L0218aa04:
    add sp, sp, #0x1700
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 93.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void VisitorTalk::WriteCard()
{
    MessageSystem* messages = func_020421a0();
    GameState* gameState = GameState::GetInstance();
    char line[0x40];
    __clear(line, sizeof(line));
    func_02046380(messages);
    func_02046574(messages, 0, STRING(0xc8, "BBB"));
    func_020465c0(messages, 2, 0x21);
    func_02046608(messages, 10, func_02072a68(&texts_, 0x1f8), line, 0x100, 0, 0);
    int width = (func_020420e8(line, 0) + 0x17) & ~7;
    if (width < 0x58)
        width = 0x58;
    func_0205de24(&window_, 0, 2);
    int tiles = width >> 3;
    window_.unk_b1 = 0;
    window_.unk_a4 = 0x20 - tiles;
    window_.unk_a6 = 0;
    window_.unk_a8 = 8;
    window_.unk_aa = 3;
    window_.width_ = tiles;
    window_.height_ = 7;
    window_.unk_ac = 10;
    window_.unk_ae = 0xc;
    window_.unk_b5 = 1;
    memset(text_, 0, 0x960);
    char name[0x30];
    __clear(name, sizeof(name));
    const void* codes = guest_;
    unsigned int vocation;
    unsigned char color;
    unsigned int female;
    unsigned char rank;
    unsigned int level;
    if (codes == NULL)
    {
        int abort = 0;
        GameObject* member = gameState->GetPartyMemberByIndex(member_);
        PartyMemberData* data = NULL;
        if (member == NULL)
        {
            abort = 1;
        }
        else
        {
            data = func_02053c6c(member);
            if (data == NULL)
                abort = 1;
        }
        if (abort)
        {
            Abort();
            return;
        }
        PartyMemberData* partyData = member->partyData_;
        vocation = partyData->vocation_;
        rank = partyData->unk_186[vocation];
        codes = entry_.name_;
        female = partyData->appearance_.female_;
        level = partyData->levels_[vocation];
        color = data->unk_56a;
    }
    else
    {
        GuestData* guest = (GuestData*)codes;
        color = guest->records_.unk_17;
        vocation = guest->vocation_;
        level = guest->level_;
        female = guest->female_;
        rank = guest->records_.unk_16_1;
    }
    func_02042764(codes, name, 1);
    func_0205d81c(&window_, 0);
    func_02041a90(text_, (width - func_020420e8(name, 0)) / 2, 3);
    func_02042058(text_, name);
    func_02041cf4(text_, 0x7fff, 2, width - 2, 0xf);
    const char* vocationName;
    if (female)
        vocationName = func_02072a68(&texts_, (short)(vocation + 0x46));
    else
        vocationName = func_02072a68(&texts_, (short)vocation);
    int x = (width - func_020420e8(vocationName, 0)) / 2;
    if (rank != 0)
        x -= 5;
    func_02041a90(text_, x, 0x12);
    func_02042058(text_, vocationName);
    if (rank != 0)
    {
        if (rank >= 10)
        {
            rank = 10;
            func_02041e70(text_, 0xd);
        }
        else
        {
            func_02041e70(text_, 5);
        }
        int rankX = x + func_020420e8(vocationName, 0);
        const char* stars = func_02072a68(&texts_, (short)(rank + 300));
        func_02041a90(text_, rankX + 2, 0x12);
        func_02042058(text_, stars);
        func_02041e70(text_, 0xf);
    }
    func_02046380(messages);
    char buffer[0x80];
    func_020465c0(messages, 0, level);
    func_020465d8(messages, 0, 0);
    func_020465f0(messages, 0, 3);
    func_02046608(messages, 10, func_02072a68(&texts_, 0x1f6), buffer, 0x100, 0, 0);
    func_02041a90(text_, (width >> 1) - 0xd, 0x1e);
    func_02042058(text_, buffer);
    func_02041cf4(text_, 0x7fff, 2, width - 2, 0x28);
    memset(buffer, 0, sizeof(buffer));
    func_02046574(messages, 0, func_02072a68(&texts_, (short)(profile_.month_ + 0x1f9)));
    func_020465c0(messages, 2, profile_.day_);
    func_02046608(messages, 10, func_02072a68(&texts_, 0x1f8), buffer, 0x100, 0, 0);
    func_02041a90(text_, 0xc, 0x2a);
    func_02042058(text_, buffer);
    func_0205d304(&window_, text_, 0, 0, 0, 1, 0, 0);
    // The color of the corners
    signed char corners = color;
    sprites_[6].unk_25 = corners;
    sprites_[7].unk_25 = corners;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN11VisitorTalk5AbortEv(); // VisitorTalk::Abort
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState21GetPartyMemberByIndexEi(); // GameState::GetPartyMemberByIndex
}

asm void VisitorTalk::WriteCard()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x100
    mov r4, r0
    bl func_020421a0
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    mov r7, r0
    add r0, sp, #0x40
    mov r1, #0x40
    bl __clear
    mov r0, r5
    bl func_02046380
    ldr r2, =sStrings+0xc8
    mov r0, r5
    mov r1, #0x0
    bl func_02046574
    mov r0, r5
    mov r1, #0x2
    mov r2, #0x21
    bl func_020465c0
    add r0, r4, #0x278
    mov r1, #0x1f8
    bl func_02072a68
    mov r2, r0
    mov r0, #0x100
    str r0, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    mov r0, r5
    mov r1, #0xa
    add r3, sp, #0x40
    bl func_02046608
    add r0, sp, #0x40
    mov r1, #0x0
    bl func_020420e8
    add r0, r0, #0x17
    bic r6, r0, #0x7
    cmp r6, #0x58
    movlt r6, #0x58
    add r0, r4, #0x18
    mov r1, #0x0
    mov r2, #0x2
    bl func_0205de24
    mov r2, r6, asr #0x3
    mov r1, #0x0
    strb r1, [r4, #0xc9]
    rsb r0, r2, #0x20
    strh r0, [r4, #0xbc]
    strh r1, [r4, #0xbe]
    mov r0, #0x8
    strh r0, [r4, #0xc0]
    mov r0, #0x3
    strh r0, [r4, #0xc2]
    strh r2, [r4, #0xb8]
    mov r0, #0x7
    strh r0, [r4, #0xba]
    mov r0, #0xa
    strh r0, [r4, #0xc4]
    mov r0, #0xc
    strh r0, [r4, #0xc6]
    mov r0, #0x1
    strb r0, [r4, #0xcd]
    ldr r0, [r4, #0x2a0]
    mov r2, #0x960
    bl memset
    add r0, sp, #0x10
    mov r1, #0x30
    bl __clear
    ldr r0, [r4, #0xebc]
    cmp r0, #0x0
    bne @L0218abc0
    add r0, r4, #0xe00
    ldrsb r1, [r0, #0xb9]
    mov r0, r7
    mov r7, #0x0
    bl _ZN9GameState21GetPartyMemberByIndexEi
    movs r8, r0
    mov r1, r7
    moveq r7, #0x1
    beq @L0218ab74
    bl func_02053c6c
    movs r1, r0
    moveq r7, #0x1
@L0218ab74:
    cmp r7, #0x0
    beq @L0218ab88
    mov r0, r4
    bl _ZN11VisitorTalk5AbortEv
    b @L0218aed0
@L0218ab88:
    ldr r8, [r8, #0x150]
    add r0, r4, #0xf6
    ldr r7, [r8, #0x950]
    ldrb r3, [r8, #0x49c]
    add r2, r8, r7
    ldrb r10, [r2, #0x186]
    add r2, r8, r7, lsl #0x1
    add r2, r2, #0x100
    mov r3, r3, lsl #0x1f
    add r0, r0, #0xd00
    mov r9, r3, lsr #0x1f
    ldrh r11, [r2, #0x6c]
    ldrb r8, [r1, #0x56a]
    b @L0218abf0
@L0218abc0:
    ldrb r2, [r0, #0x2e]
    ldr r3, [r0, #0xc]
    ldrb r1, [r0, #0x4e]
    mov r7, r3, lsl #0x1c
    mov r3, r3, lsl #0x11
    mov r2, r2, lsl #0x1f
    mov r1, r1, lsl #0x1b
    ldrb r8, [r0, #0x4f]
    mov r7, r7, lsr #0x1c
    mov r11, r3, lsr #0x19
    mov r9, r2, lsr #0x1f
    mov r10, r1, lsr #0x1c
@L0218abf0:
    add r1, sp, #0x10
    mov r2, #0x1
    bl func_02042764
    add r0, r4, #0x18
    mov r1, #0x0
    bl func_0205d81c
    add r0, sp, #0x10
    mov r1, #0x0
    bl func_020420e8
    sub r0, r6, r0
    add r0, r0, r0, lsr #0x1f
    mov r1, r0, asr #0x1
    ldr r0, [r4, #0x2a0]
    mov r2, #0x3
    bl func_02041a90
    ldr r0, [r4, #0x2a0]
    add r1, sp, #0x10
    bl func_02042058
    mov r0, #0xf
    str r0, [sp, #0x0]
    ldr r0, [r4, #0x2a0]
    ldr r1, =0x7fff
    mov r2, #0x2
    sub r3, r6, #0x2
    bl func_02041cf4
    cmp r9, #0x0
    beq @L0218ac74
    add r0, r7, #0x46
    mov r1, r0, lsl #0x10
    add r0, r4, #0x278
    mov r1, r1, asr #0x10
    bl func_02072a68
    b @L0218ac84
@L0218ac74:
    mov r1, r7, lsl #0x10
    add r0, r4, #0x278
    mov r1, r1, asr #0x10
    bl func_02072a68
@L0218ac84:
    mov r9, r0
    mov r0, r9
    mov r1, #0x0
    bl func_020420e8
    sub r0, r6, r0
    add r0, r0, r0, lsr #0x1f
    mov r7, r0, asr #0x1
    cmp r10, #0x0
    subne r7, r7, #0x5
    ldr r0, [r4, #0x2a0]
    mov r1, r7
    mov r2, #0x12
    bl func_02041a90
    ldr r0, [r4, #0x2a0]
    mov r1, r9
    bl func_02042058
    cmp r10, #0x0
    beq @L0218ad40
    cmp r10, #0xa
    ldr r0, [r4, #0x2a0]
    blo @L0218ace8
    mov r1, #0xd
    mov r10, #0xa
    bl func_02041e70
    b @L0218acf0
@L0218ace8:
    mov r1, #0x5
    bl func_02041e70
@L0218acf0:
    mov r0, r9
    mov r1, #0x0
    bl func_020420e8
    add r1, r10, #0x12c
    mov r1, r1, lsl #0x10
    add r7, r7, r0
    add r0, r4, #0x278
    mov r1, r1, asr #0x10
    bl func_02072a68
    mov r9, r0
    ldr r0, [r4, #0x2a0]
    add r1, r7, #0x2
    mov r2, #0x12
    bl func_02041a90
    mov r1, r9
    ldr r0, [r4, #0x2a0]
    bl func_02042058
    ldr r0, [r4, #0x2a0]
    mov r1, #0xf
    bl func_02041e70
@L0218ad40:
    mov r0, r5
    bl func_02046380
    mov r0, r5
    mov r2, r11
    mov r1, #0x0
    bl func_020465c0
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl func_020465d8
    mov r0, r5
    mov r1, #0x0
    mov r2, #0x3
    bl func_020465f0
    ldr r1, =0x1f6
    add r0, r4, #0x278
    bl func_02072a68
    mov r2, r0
    mov r0, #0x100
    str r0, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    mov r0, r5
    mov r1, #0xa
    add r3, sp, #0x80
    bl func_02046608
    mov r1, r6, asr #0x1
    ldr r0, [r4, #0x2a0]
    sub r1, r1, #0xd
    mov r2, #0x1e
    bl func_02041a90
    ldr r0, [r4, #0x2a0]
    add r1, sp, #0x80
    bl func_02042058
    mov r0, #0x28
    str r0, [sp, #0x0]
    ldr r0, [r4, #0x2a0]
    ldr r1, =0x7fff
    sub r3, r6, #0x2
    mov r2, #0x2
    bl func_02041cf4
    add r0, sp, #0x80
    mov r1, #0x0
    mov r2, #0x80
    bl memset
    ldr r1, [r4, #0xe1c]
    add r0, r4, #0x278
    mov r1, r1, lsl #0x10
    mov r1, r1, lsr #0x1c
    add r1, r1, #0xf9
    add r1, r1, #0x100
    mov r1, r1, lsl #0x10
    mov r1, r1, asr #0x10
    bl func_02072a68
    mov r2, r0
    mov r0, r5
    mov r1, #0x0
    bl func_02046574
    ldr r2, [r4, #0xe1c]
    mov r0, r5
    mov r2, r2, lsl #0xb
    mov r1, #0x2
    mov r2, r2, lsr #0x1b
    bl func_020465c0
    add r0, r4, #0x278
    mov r1, #0x1f8
    bl func_02072a68
    mov r2, r0
    mov r0, #0x100
    str r0, [sp, #0x0]
    mov r1, #0x0
    str r1, [sp, #0x4]
    str r1, [sp, #0x8]
    add r3, sp, #0x80
    mov r0, r5
    mov r1, #0xa
    bl func_02046608
    ldr r0, [r4, #0x2a0]
    mov r1, #0xc
    mov r2, #0x2a
    bl func_02041a90
    ldr r0, [r4, #0x2a0]
    add r1, sp, #0x80
    bl func_02042058
    mov r2, #0x0
    str r2, [sp, #0x0]
    mov r0, #0x1
    stmib sp, {r0, r2}
    str r2, [sp, #0xc]
    ldr r1, [r4, #0x2a0]
    add r0, r4, #0x18
    mov r3, r2
    bl func_0205d304
    mov r0, r8, lsl #0x18
    mov r1, r0, asr #0x18
    ldr r0, [r4, #0x1f8]
    strb r1, [r0, #0x115]
    ldr r0, [r4, #0x1f8]
    strb r1, [r0, #0x13d]
@L0218aed0:
    add sp, sp, #0x100
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 94.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and instruction order
#ifdef NONMATCHING
void VisitorTalk::DrawCorners()
{
    if (state_ != 1)
        return;
    Canvas* canvas = func_0205d81c(&window_, 0);
    if (canvas == NULL)
        return;
    short left = canvas->x_ * 8;
    short top = canvas->y_ * 8;
    Sprite* sprites = sprites_;
    short width = canvas->width_;
    int x = (left - 1) << 12;
    sprites[6].x_ = x;
    unsigned int y = (top - 1) << 12;
    sprites[6].y_ = y;
    func_0205ac40(renderer_, &sprites[6]);
    sprites = sprites_;
    sprites[7].x_ = ((left + (short)(width * 8)) - 8) << 12;
    sprites[7].y_ = y;
    func_0205ac40(renderer_, &sprites[7]);
}
#else
asm void VisitorTalk::DrawCorners()
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r7, r0
    add r0, r7, #0xe00
    ldrsb r0, [r0, #0x99]
    cmp r0, #0x1
    ldmneia sp!, {r3, r4, r5, r6, r7, pc}
    add r0, r7, #0x18
    mov r1, #0x0
    bl func_0205d81c
    cmp r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
    ldrsh r1, [r0, #0xac]
    ldrsh r2, [r0, #0xae]
    ldr r3, [r7, #0x1f8]
    mov r1, r1, lsl #0x13
    mov r5, r1, asr #0x10
    mov r1, r2, lsl #0x13
    sub r2, r5, #0x1
    mov r1, r1, asr #0x10
    sub r1, r1, #0x1
    ldrsh r4, [r0, #0xa8]
    mov r0, r2, lsl #0xc
    mov r6, r1, lsl #0xc
    str r0, [r3, #0x104]
    str r6, [r3, #0x108]
    ldr r0, [r7, #0x1f4]
    add r1, r3, #0xf0
    bl func_0205ac40
    mov r0, r4, lsl #0x13
    add r0, r5, r0, asr #0x10
    sub r0, r0, #0x8
    ldr r1, [r7, #0x1f8]
    mov r0, r0, lsl #0xc
    str r0, [r1, #0x12c]
    str r6, [r1, #0x130]
    ldr r0, [r7, #0x1f4]
    add r1, r1, #0x118
    bl func_0205ac40
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

void VisitorTalk::OpenRecords()
{
    GameResources* resources = func_ov017_0218b5b0();
    if (recordsStep_ == 0 && profileLoaded_ && !IsBrightnessTransitionActive(resources))
    {
        func_020a1940((unsigned int)OVERLAY_8_ID);
        records_.Initialize();
        records_.mode_ = 1;
        records_.CreateAllocators(&recordsAllocator_);
        records_.SetState(1);
        records_.guestTitles_ = &titles_;
        const void* name;
        GuestRecords* guestRecords;
        if (guest_ == NULL)
        {
            name = entry_.name_;
            guestRecords = &entry_.records_;
        }
        else
        {
            name = guest_;
            guestRecords = &guest_->records_;
        }
        records_.guest_ = name;
        records_.guestRecords_ = guestRecords;
        recordsStep_++;
        return;
    }
    if (recordsStep_ != 1)
        return;
    if (!profileLoaded_)
        return;
    if (!titlesLoaded_)
        return;
    func_020dc2bc();
    SetSubBrightness(resources, -0x10, 0xf);
    recordsState_ = 1;
    recordsStep_ = 0;
}

void VisitorTalk::CloseRecords()
{
    signed char step = recordsStep_;
    if (step == 0)
    {
        if (!profileLoaded_)
        {
            recordsStep_ = 2;
            return;
        }
        records_.SetState(13);
        recordsStep_++;
    }
    else if (step == 1)
    {
        records_.Update();
        if ((unsigned char)records_.state_ != 14)
            return;
        records_.Finish();
        recordsStep_++;
    }
    else if (step == 2)
    {
        GameResources* resources = func_ov017_0218b5b0();
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->RemoveTask(profileTask_);
        loader->RemoveTask(sentencesTask_);
        profileTask_ = -1;
        sentencesTask_ = -1;
        REG_BG0CNT_SUB = (REG_BG0CNT_SUB & ~3) | 1;
        REG_BG1CNT_SUB = (REG_BG1CNT_SUB & ~3) | 2;
        REG_BG2CNT_SUB = REG_BG2CNT_SUB & ~3;
        func_020dc2d0(0);
        if (saved_ != 0)
        {
            void* unk;
            void* script = RESOURCE(resources, 0x3b4c, void*);
            unk = RESOURCE(resources, 0x36fc, void*);
            func_ov017_021b2174(script);
            func_ov017_021b2ba0(script, STRING(0xcc, "mmate.stb"));
            func_ov017_021b2bd0(script, func_ov004_0216aa70, (unsigned int)OVERLAY_4_ID);
            func_020469b4(unk, script);
        }
        done_ = 1;
    }
}

void VisitorTalk::AddVisitor()
{
    GameState* gameState = GameState::GetInstance();
    GuestEntry* entry = GetVisitors(gameState)->entries_;
    for (int i = 0; i < 16; i++)
    {
        if (!entry->used_)
        {
            memcpy(entry, &entry_, sizeof(GuestEntry));
            GetVisitors(gameState)->count_++;
            return;
        }
        entry++;
    }
}

void VisitorTalk::Abort()
{
    if (aborted_)
        return;
    GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    active_ = 0;
    func_0205d6a0(&window_, 1);
    state_ = 2;
    step_ = 0;
    recordsState_ = 2;
    recordsStep_ = 0;
    func_020466f4(func_020d6c00(), 0x2f);
    func_0203b4b0(func_ov017_0218b5b0(), 0x10);
    loader->RemoveTask(textTask_);
    loader->RemoveTask(titleTask_);
    loader->RemoveTask(backgroundTask_);
    loader->RemoveTask(spriteTask_);
    textTask_ = -1;
    titleTask_ = -1;
    backgroundTask_ = -1;
    spriteTask_ = -1;
    aborted_ = 1;
}
