// The screen of the party members (clmm, lay_mm.lia), which overlay 17 runs: a member's 3D model, their name, vocation
// and level, and overlay 5's equipment menu when it's opened from it
// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_23/MemberScreen.h"
#include "Scene/Overlay_5/EquipmentMenu.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Resource/Brightness.h"
#include "System/Cache.h"
#include "System/LoadToVRAM.h"
#include "System/TouchScreen.h"
#include "Text/MessageSystem.h"
#include <std_library_functions.h>

#define GXFIFO_MATRIX_PUSH (*(volatile unsigned int*)0x04000444)
#define GXFIFO_MATRIX_POP (*(volatile unsigned int*)0x04000448)
#define GXFIFO_MATRIX_MODE (*(volatile unsigned int*)0x04000440)
#define GXFIFO_MATRIX_IDENTITY (*(volatile unsigned int*)0x04000454)
#define GXFIFO_MATRIX_TRANSLATE (*(volatile unsigned int*)0x04000470)
#define GXFIFO_SWAP_BUFFERS (*(volatile unsigned int*)0x04000540)
#define GXFIFO_BEGIN_VTXS (*(volatile unsigned int*)0x04000500)
#define GXFIFO_END_VTXS (*(volatile unsigned int*)0x04000504)

#define PAD_BUTTON_B 2
#define PAD_BUTTON_R 0x100
#define PAD_BUTTON_L 0x200
#define PAD_BUTTON_X 0x400
#define PAD_BUTTON_Y 0x800

// A vocation's text of the texts of the equipment menu, and what func_020e46c4 initializes
struct MemberScreenVocation
{
    char unk_0[8];
    unsigned int unk_8_0 : 24;
    unsigned int sex_ : 2;
    unsigned int unk_8_26 : 6;
    char unk_c[4];
};

extern "C"
{
    void __clear(void* buffer, unsigned long size);

    // The files of the names of the items
    extern const char* data_020f2a30;
    extern const char* data_020f2a38;
    // The sprites of the screen
    extern const char* data_020f2a40;
    extern char data_02108760[];
    extern char data_02109bf4[];
    extern char data_02114e30[];
    // The touch screen
    extern TouchState data_02114e54;

    int func_0200fb08(GameState* gameState);
    GameResources* func_0200fb8c(GameState* gameState);
    PartyMember* func_0200ff1c(GameState* gameState, int index);
    int func_020100a8(GameState* gameState);
    void* func_020100bc(GameState* gameState);
    void func_020100c4(GameState* gameState, void* camera);
    int func_02012430(void* pad, int buttons);
    int func_02012444(void* pad, int buttons);
    void func_02012fe4();
    void func_02017d68();
    void func_0202e5c0(void* camera, int x, int y, int z);
    void func_0202e5c8(void* camera, int x, int y, int z);
    void func_0203b4d8(GameResources* resources, int);
    int func_020420e8(const char* text, int large);
    MessageSystem* func_020421a0();
    int func_020421b0(unsigned char icon);
    void func_02042b30(MessageSystem* messages, VRAMManagerState* state);
    void func_02043124(MessageSystem* messages);
    void func_02043204(MessageSystem* messages);
    void func_020432c4(MessageSystem* messages);
    void func_020439b0(MessageSystem* messages, int);
    void func_02045cac(MessageSystem* messages);
    void func_02045d14(MessageSystem* messages, const char* text, unsigned short* codes, int);
    void func_02045f3c(MessageSystem* messages, unsigned short* codes, int x, int y, int color, int, int, int, int, int);
    void func_02046380(MessageSystem* messages);
    void func_02046608(MessageSystem* messages, int, const char* format, char* output, int size, int, int);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    // The count of the files of an archive, and a file of it
    int func_02046900(void* archive);
    void* func_020467f0(void* archive, int index, char* name, unsigned int* size);
    int func_0204af14(void* background, int);
    PartyMemberData* func_02053c6c(PartyMember* member);
    void func_0205a198(Sprite* sprite);
    void func_0205a330(SpriteAnimationList* list, int ticks);
    void func_0205a370(SpriteAnimationList* list, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* list, int index);
    void func_0205a42c(SpriteAnimationList* list, int, int);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a494(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205ae8c(SpriteRenderer* renderer);
    void func_0205eaa0(void* sound, int effect, int);
    void func_0207de48(VRAMManagerState* state, int textureSize, int paletteSize);
    void func_0207df50(VRAMManagerState* state);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);
    void* func_02094a00();
    void func_02094ab0(void* fade);
    void func_02094b34(void* fade, int, int, int);
    void func_02094b40();
    int func_02094b4c();
    int func_0209ca2c(void* sound);
    void func_020a2010(void* camera);
    void func_020a27a0(void* camera);
    void func_020c54a4(int, int, int, int);
    // G3X_SetEdgeColorTable
    void func_020c555c(const unsigned short* colors);
    void* func_020d6c00();
    // The members in the party, and their count
    void func_020dc4d0(signed char* members, signed char* count);
    void func_020dc7e8(int, signed char member);
    void func_020de848(PartNameTable* items);
    void func_020dea40(PartNameTable* items, SafeAllocator* allocator, void* file, unsigned int size, int);
    void func_020dea64(PartNameTable* items, SafeAllocator* allocator, void* file, unsigned int size,
                       const unsigned char* categories, int count);
    unsigned short func_020deb08(PartNameTable* items);
    void func_020deb24(PartNameTable* items, short index);
    const char* func_020e0434(void* texts, short id);
    void func_020e46c4(MemberScreenVocation* vocation);
    void func_020e4bf4(MemberScreenVocation* vocation, int);
    const char* func_020e51cc(int id);

    GameResources* func_ov017_0218b5b0();
    void func_ov017_0219ba0c(GameResources* resources, int);
    int func_ov017_021bdbcc();
    Object3D* func_ov017_021bdbd8(GameResources* resources);
    Object3D* func_ov017_021bdbe4();
}

// The categories of the items whose names the screen loads
static const unsigned char sCategories[] = {0, 1, 2, 3, 4, 5, 6, 7, 11};

// The colors of the models' edges
static unsigned short sEdgeColors[8] = {0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086};

// The strings of the functions, which the compiler pools in this order. Some functions are in assembly for now
// (NONMATCHING), which can't reference the compiler's pool, so they're in an array for them
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] = "data/ani/clmm.gp2\0clmm_<LG>.pac\0data/ani/lay_mm.lia\0<tc%d>";
#define STRING(offset, text) (sStrings + (offset))
#endif

void MemberScreen::LoadVocationIcon(int member, SpriteRenderer* renderer)
{
    if (member < 0)
        return;
    GameObject* partyMember = GameState::GetInstance()->GetPartyMemberByIndex(member);
    if (renderer == NULL || partyMember == NULL)
        return;
    Sprite* sprite = NULL;
    if (renderer->sprites_ != NULL && renderer->capacity_ > 15)
        sprite = &renderer->sprites_[15];
    SpriteCell* cell;
    if (sprite == NULL || (cell = (SpriteCell*)sprite->unk_8) == NULL)
        return;
    int vocation = partyMember->partyData_->vocation_;
    func_ov017_0218b5b0();
    if (func_ov017_021bdbcc())
        vocation = 0;
    unsigned char icon = vocation * 4 + 0x28;
    unsigned int tiles = (unsigned short)(cell->unk_4 & 0x3ff) << 5;
    for (int i = 0; i < 4; i++)
    {
        void* pixels = (void*)func_020421b0(icon);
        CleanInvalidateCacheRange(pixels, 0x20);
        LoadToMainObjVRAM(pixels, tiles, 0x20);
        CleanCacheRange(pixels, 0x20);
        icon++;
        tiles += 0x20;
    }
}

void MemberScreen::Initialize()
{
    signed char count;
    signed char members[4];
    func_020466e4(func_020d6c00(), 0xf);
    equipment_ = NULL;
    allocator_ = NULL;
    unk_c = 0;
    allocator2_ = NULL;
    allocator3_ = NULL;
    allocators_[0].ResetAllocatorPointer();
    allocators_[1].ResetAllocatorPointer();
    allocators_[2].ResetAllocatorPointer();
    allocators_[3].ResetAllocatorPointer();
    allocators_[4].ResetAllocatorPointer();
    allocators_[5].ResetAllocatorPointer();
    func_020de848(&items_);
    itemCount_ = 0;
    itemCount2_ = 0;
    spritesFile_ = NULL;
    spritesFileSize_ = 0;
    renderer_ = NULL;
    sprites_ = NULL;
    animations_ = NULL;
    layout_.Initialize();
    model_ = NULL;
    nextModel_ = NULL;
    timer_ = 0;
    state_ = 0;
    previousState_ = 0;
    models_[0] = NULL;
    models_[1] = NULL;
    memberCount_ = 0;
    GameState* gameState = GameState::GetInstance();
    count = 0;
    for (int i = 0; i < 4; i++)
        members[i] = -1;
    func_020dc4d0(members, &count);
    for (int i = 0; i < 4; i++)
    {
        int member = members[i];
        members_[i] = member;
        func_0200ff1c(gameState, member);
    }
    memberCount_ = count;
    step_ = 1;
    task_ = 0;
    memset(&flags_, 0, sizeof(flags_));
    closed_ = 0;
    buffer_ = NULL;
    buffer2_ = NULL;
    downTexts_[0] = NULL;
    downTexts_[1] = NULL;
}

void MemberScreen::Finish()
{
    func_020466f4(func_020d6c00(), 0xf);
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ > 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    void* fade = func_02094a00();
    func_02094b40();
    func_02094ab0(fade);
    if (equipment_ != NULL)
    {
        equipment_->Finish();
        equipment_ = NULL;
        func_02012fe4();
        func_02017d68();
    }
    models_[1]->Finish();
    if (models_[0] != NULL)
        models_[0]->Finish();
    if (renderer_ != NULL)
        func_0205a494(renderer_);
    allocators_[5].Destroy();
    allocators_[4].Destroy();
    allocators_[3].Destroy();
    allocators_[2].Destroy();
    allocators_[1].Destroy();
    allocators_[0].Destroy();
    spritesFile_ = NULL;
    spritesFileSize_ = 0;
    MessageSystem* messages = func_020421a0();
    func_02045cac(messages);
    func_02043204(messages);
    func_02043124(messages);
    messages->unk_2d8 = 0;
    messages->unk_2dc = 0;
    messages->unk_2e0 = 0;
}

void MemberScreen::Update()
{
    UpdateClose();
    switch (state_)
    {
    case 0:
        State_Load();
        break;
    case 3:
        State_Main();
        break;
    case 1:
        State_Exit();
        break;
    }
}

void MemberScreen::Draw3D()
{
    GameState::GetInstance();
    int timer = timer_;
    if (timer > 0 && (timer_ = timer - 1) == 0)
        flags_ |= MEMBER_SCREEN_SWAP_MODELS;
    if (flags_ & MEMBER_SCREEN_DRAW_MODEL)
    {
        CharacterModelExtras extras;
        GameResources* resources = func_ov017_0218b5b0();
        if (resources == NULL)
        {
            extras.head_ = NULL;
            extras.chest_ = NULL;
        }
        else
        {
            extras.head_ = func_ov017_021bdbe4();
            extras.chest_ = func_ov017_021bdbd8(resources);
        }
        if (model_ != NULL)
        {
            GXFIFO_MATRIX_PUSH = 0;
            model_->Draw(&extras);
            GXFIFO_MATRIX_POP = 1;
        }
    }
}

void MemberScreen::Draw2D()
{
    signed char state = state_;
    if (state != 0 && state != -1)
    {
        DrawTexts();
        DrawLeftRight();
        DrawNext();
        DrawBack();
        if (equipment_ != NULL)
            equipment_->Draw2D();
    }
}

void MemberScreen::DrawSub()
{
    signed char state = state_;
    if (state != 0 && state != -1 && equipment_ != NULL)
        equipment_->DrawSub();
}

void MemberScreen::SetMembers(const unsigned char* members, int count)
{
    if (members != NULL && count != 0)
    {
        memberCount_ = count;
        for (int i = 0; i < 4; i++)
            members_[i] = members[i];
    }
}

void MemberScreen::DrawArrows1(int x, int y, int x2, short y2)
{
    Sprite* sprite = &sprites_[4];
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x78;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
    sprite = &sprites_[5];
    sprite->x_ = x2 << 12;
    sprite->y_ = y2 << 12;
    sprite->unk_22 = 0x77;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
}

void MemberScreen::DrawArrows2(int x, int y, int x2, short y2)
{
    Sprite* sprite = &sprites_[6];
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x76;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
    sprite = &sprites_[7];
    sprite->x_ = x2 << 12;
    sprite->y_ = y2 << 12;
    sprite->unk_22 = 0x75;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
}

void MemberScreen::DrawArrow3(int x, int y)
{
    Sprite* sprite = &sprites_[8];
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x72;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
}

void MemberScreen::DrawCursor(short x, short y)
{
    GameState* gameState = GameState::GetInstance();
    func_0205a42c(animations_, 0, 0);
    func_0205a370(animations_, 0);
    SpriteAnimation* animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
        animation->flags_ |= 8;
    func_0205a330(animations_, gameState->GetTickCount());
    animation = func_0205a3d0(animations_, 0);
    if (animation != NULL)
    {
        animation->x_ = x;
        animation->y_ = y;
    }
    func_0205ae8c(renderer_);
}

void MemberScreen::Close()
{
    flags_ |= MEMBER_SCREEN_CLOSE;
}

void MemberScreen::SetState(signed char state)
{
    previousState_ = state_;
    state_ = state;
}

// NONMATCHING: the C matches 48.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Register allocation and the order of the loading steps differ
#ifdef NONMATCHING
void MemberScreen::State_Load()
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_ov017_0218b5b0();
    unsigned char step = step_;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (step == 0)
        step_ = step + 1;
    if (IsMainBrightnessTransitionActive(resources))
        return;

    switch (step_)
    {
    case 1:
    {
        void* fade = func_02094a00();
        func_02094b40();
        func_02094b34(fade, 0x79, 0x1fa, 0);
        step_++;
        return;
    }
    case 2:
        func_02094a00();
        if (func_02094b4c())
        {
            func_ov017_0219ba0c(resources, 1);
            task_ = loader->QueueLoadFileInGP2(data_020f2a38, data_020f2a30, NULL);
            step_++;
            return;
        }
        break;
    case 3:
        if (loader->GetTaskStatus(task_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            func_0203b4d8(resources, 0x601fe);
            func_0207df90(vramState_);
            allocator3_->Reset();
            func_020de848(&items_);
            func_020dea40(&items_, allocator3_, file, size, 0xb);
            itemCount2_ = func_020deb08(&items_);
            itemCount_ = itemCount2_ + 0x31;
            for (int i = 0; i < itemCount_; i++)
                func_020deb24(&items_, i);
            allocator3_->Reset();
            if (mode_ == 3)
            {
                equipment_ = (EquipmentMenu*)allocator2_->Allocate(0x428c);
                equipment_->Initialize();
                equipment_->CreateAllocators(allocator2_, (SafeAllocator*)unk_c);
                equipment_->LoadModelTable(file, size);
            }
            allocators_[0].CreateTypeA(allocator2_->Allocate(0x800), 0x800);
            allocators_[1].CreateTypeA(allocator2_->Allocate(0x100), 0x100);
            for (int i = 0; i < 2; i++)
            {
                char* text = (char*)allocators_[0].Allocate(0x40);
                downTexts_[i] = text;
                memset(text, 0, 0x40);
            }
            allocators_[3].CreateTypeA(allocator_->Allocate(0x100), 0x100);
            renderer_ = (SpriteRenderer*)allocator_->Allocate(0x54);
            sprites_ = (Sprite*)allocator_->Allocate(0x280);
            animations_ = (SpriteAnimationList*)allocator_->Allocate(8);
            if (equipment_ != NULL && animations_ != NULL && renderer_ != NULL)
                equipment_->CreateChoice(animations_, renderer_);
            allocators_[4].CreateTypeA(allocator_->Allocate(0x300), 0x300);
            allocators_[5].CreateTypeA(allocator_->Allocate(0x200), 0x200);
            for (int i = 0; i < 2; i++)
            {
                CharacterModel* model = (CharacterModel*)allocator_->Allocate(sizeof(CharacterModel));
                models_[i] = model;
                model->Initialize();
                model->CreateAllocators(allocator_);
                model->InitializeVRAMStates();
                model->SetNames(&items_);
                model->SetUnk_c11(1);
            }
            allocator3_->Reset();
            func_020de848(&items_);
            func_020dea64(&items_, allocator3_, file, size, sCategories, 9);
            buffer_ = allocators_[0].Allocate(0x2a0);
            memset(buffer_, 0, 0x2a0);
            buffer2_ = allocators_[0].Allocate(0x400);
            memset(buffer2_, 0, 0x400);
            if (equipment_ != NULL)
                equipment_->items_ = &items_;
            func_0207de48(&vramStates_[1], 0x4000, 0x40);
            func_0207df50(&vramStates_[1]);
            if (mode_ == 3 && equipment_ != NULL)
                equipment_->LoadVRAM();
            func_0207de48(&vramStates_[0], 0, 0);
            func_0207df50(&vramStates_[0]);
            MessageSystem* messages = func_020421a0();
            func_02042b30(messages, &vramStates_[1]);
            func_0207df90(&vramStates_[1]);
            func_020432c4(messages);
            func_0207dfac(&vramStates_[1]);
            previousCamera_ = func_020100bc(gameState);
            func_020a2010(camera_);
            func_0202e5c0(camera_, 0xb666, 0xa800, 0x42ccc);
            func_0202e5c8(camera_, 0xb666, 0xa800, 0);
            func_020a27a0(camera_);
            func_020100c4(gameState, camera_);
            func_020c54a4(0, 0, 0, 0);
            loader->RemoveTask(task_);
            task_ = -1;
            task_ = loader->QueueLoadFile(data_020f2a40, NULL);
            step_++;
            return;
        }
        break;
    case 4:
        if (loader->GetTaskStatus(task_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            spritesFile_ = allocators_[5].Allocate(size);
            memcpy(spritesFile_, file, size);
            spritesFileSize_ = size;
            loader->RemoveTask(task_);
            task_ = -1;
            func_0205a444(renderer_);
            renderer_->unk_50 = 0;
            renderer_->SetSprites(sprites_, 0x10);
            renderer_->animations_ = animations_;
            for (int i = 0; i < 0x10; i++)
                func_0205a198(&sprites_[i]);
            task_ = loader->QueueLoadFileInGP2(STRING(0, "data/ani/clmm.gp2"), STRING(0x12, "clmm_<LG>.pac"), NULL);
            step_++;
            return;
        }
        break;
    case 5:
        if (loader->GetTaskStatus(task_))
        {
            void* archive;
            unsigned int archiveSize;
            allocators_[3].Reset();
            loader->GetLoadedFileByID(task_, &archive, &archiveSize);
            int count = func_02046900(archive);
            for (int i = 0; i < count; i++)
            {
                char name[4];
                unsigned int size;
                void* file = func_020467f0(archive, i, name, &size);
                if (file != NULL)
                    func_0205a528(renderer_, file, size, &allocators_[3]);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
            return;
        }
        break;
    case 6:
        if (equipment_ != NULL)
        {
            if (equipment_->Load())
                step_++;
            return;
        }
        break;
    case 7:
    {
        MemberScreenVocation vocation;
        func_020e46c4(&vocation);
        func_020e4bf4(&vocation, func_020100a8(gameState));
        MessageSystem* messages = func_020421a0();
        char* texts = (char*)equipment_ + 0x1f8;
        for (int i = 0; i < 2; i++)
        {
            vocation.sex_ = i;
            func_02046380(messages);
            *(MemberScreenVocation**)messages = &vocation;
            func_02046608(messages, 8, func_020e0434(texts + 0xc00, 0x226), downTexts_[i], 0x100, 0, 0);
        }
        task_ = loader->QueueLoadFile(STRING(0x20, "data/ani/lay_mm.lia"), NULL);
        step_++;
        return;
    }
    case 8:
        if (loader->GetTaskStatus(task_))
        {
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &file, &size);
            if (file != NULL)
            {
                allocators_[4].Reset();
                layout_.Initialize();
                layout_.Load(&allocators_[4], file, size);
                HideElement(&layout_, 1, LAYOUT_ELEMENT_FLAG_VISIBLE);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            step_++;
            return;
        }
        break;
    default:
    {
        PartyMember* member = func_0200ff1c(GameState::GetInstance(), member_);
        if (member != NULL)
        {
            models_[0]->SetAngle(0x1eb);
            models_[0]->Load(func_02053c6c(member), member_, 0, 0);
        }
        model_ = models_[0];
        nextModel_ = models_[1];
        flags_ |= MEMBER_SCREEN_TURNING | MEMBER_SCREEN_DRAW_MODEL | MEMBER_SCREEN_CHANGE_MEMBER;
        LoadTexts();
        if (mode_ == 3 && equipment_ != NULL)
        {
            equipment_->WriteDigits();
            equipment_->WriteNames();
        }
        func_020c555c(sEdgeColors);
        HideElement(&layout_, 0x11, LAYOUT_ELEMENT_FLAG_VISIBLE);
        HideElement(&layout_, 0x12, LAYOUT_ELEMENT_FLAG_VISIBLE);
        HideElement(&layout_, 0x1b, LAYOUT_ELEMENT_FLAG_VISIBLE);
        HideElement(&layout_, 0x20, LAYOUT_ELEMENT_FLAG_VISIBLE);
        LoadVocationIcon(member_, renderer_);
        SetState(mode_);
        step_ = 0;
        flags_ &= ~MEMBER_SCREEN_LOADING;
        break;
    }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12MemberScreen11HideElementEP6Layoutsi(); // MemberScreen::HideElement
    void _ZN12MemberScreen16LoadVocationIconEiP14SpriteRenderer(); // MemberScreen::LoadVocationIcon
    void _ZN12MemberScreen8SetStateEa(); // MemberScreen::SetState
    void _ZN12MemberScreen9LoadTextsEv(); // MemberScreen::LoadTexts
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN13EquipmentMenu10InitializeEv(); // EquipmentMenu::Initialize
    void _ZN13EquipmentMenu10WriteNamesEv(); // EquipmentMenu::WriteNames
    void _ZN13EquipmentMenu11WriteDigitsEv(); // EquipmentMenu::WriteDigits
    void _ZN13EquipmentMenu12CreateChoiceEP19SpriteAnimationListP14SpriteRenderer(); // EquipmentMenu::CreateChoice
    void _ZN13EquipmentMenu14LoadModelTableEPvj(); // EquipmentMenu::LoadModelTable
    void _ZN13EquipmentMenu16CreateAllocatorsEP13SafeAllocatorS1_(); // EquipmentMenu::CreateAllocators
    void _ZN13EquipmentMenu4LoadEv(); // EquipmentMenu::Load
    void _ZN13EquipmentMenu8LoadVRAMEv(); // EquipmentMenu::LoadVRAM
    void _ZN14CharacterModel10InitializeEv(); // CharacterModel::Initialize
    void _ZN14CharacterModel10SetUnk_c11Eh(); // CharacterModel::SetUnk_c11
    void _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator(); // CharacterModel::CreateAllocators
    void _ZN14CharacterModel20InitializeVRAMStatesEv(); // CharacterModel::InitializeVRAMStates
    void _ZN14CharacterModel4LoadEP15PartyMemberDataiii(); // CharacterModel::Load
    void _ZN14CharacterModel8SetAngleEi(); // CharacterModel::SetAngle
    void _ZN14CharacterModel8SetNamesEP13PartNameTable(); // CharacterModel::SetNames
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
    void _ZN6Layout10InitializeEv(); // Layout::Initialize
    void _ZN6Layout4LoadEP13SafeAllocatorPvj(); // Layout::Load
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void MemberScreen::State_Load()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x40
    mov r10, r0
    bl _ZN9GameState11GetInstanceEv
    mov r5, r0
    bl func_ov017_0218b5b0
    mov r4, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r1, [r10, #0x4e4]
    mov r7, r0
    cmp r1, #0x0
    addeq r0, r1, #0x1
    streqb r0, [r10, #0x4e4]
    mov r0, r4
    bl IsMainBrightnessTransitionActive
    cmp r0, #0x0
    bne @L021e3cf8
    ldrb r0, [r10, #0x4e4]
    cmp r0, #0x1
    bne @L021e3438
    bl func_02094a00
    mov r4, r0
    bl func_02094b40
    mov r3, #0x0
    ldr r2, =0x1fa
    mov r0, r4
    str r3, [sp, #0x0]
    mov r1, #0x79
    bl func_02094b34
    ldrb r0, [r10, #0x4e4]
    add r0, r0, #0x1
    strb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e3438:
    cmp r0, #0x2
    bne @L021e348c
    bl func_02094a00
    bl func_02094b4c
    cmp r0, #0x0
    beq @L021e3cf8
    mov r0, r4
    mov r1, #0x1
    bl func_ov017_0219ba0c
    ldr r1, =data_020f2a38
    ldr r0, =data_020f2a30
    ldr r1, [r1, #0x0]
    ldr r2, [r0, #0x0]
    mov r0, r7
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r10, #0x630]
    ldrb r0, [r10, #0x4e4]
    add r0, r0, #0x1
    strb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e348c:
    cmp r0, #0x3
    bne @L021e38d4
    ldr r1, [r10, #0x630]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021e3cf8
    ldr r1, [r10, #0x630]
    add r2, sp, #0x30
    add r3, sp, #0x2c
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r1, =0x601fe
    mov r0, r4
    bl func_0203b4d8
    ldr r0, [r10, #0x8]
    bl func_0207df90
    ldr r0, [r10, #0x14]
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0xa4
    bl func_020de848
    mov r0, #0xb
    str r0, [sp, #0x0]
    ldr r1, [r10, #0x14]
    ldr r2, [sp, #0x30]
    ldr r3, [sp, #0x2c]
    add r0, r10, #0xa4
    bl func_020dea40
    add r0, r10, #0xa4
    bl func_020deb08
    strh r0, [r10, #0xbe]
    ldrh r0, [r10, #0xbe]
    mov r4, #0x0
    add r0, r0, #0x31
    strh r0, [r10, #0xbc]
    b @L021e3530
@L021e351c:
    mov r1, r4, lsl #0x10
    add r0, r10, #0xa4
    mov r1, r1, asr #0x10
    bl func_020deb24
    add r4, r4, #0x1
@L021e3530:
    ldrh r0, [r10, #0xbc]
    cmp r4, r0
    blt @L021e351c
    ldr r0, [r10, #0x14]
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0x400
    ldrsb r0, [r0, #0xe5]
    cmp r0, #0x3
    bne @L021e3588
    ldr r0, [r10, #0x10]
    ldr r1, =0x428c
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x0]
    bl _ZN13EquipmentMenu10InitializeEv
    ldr r0, [r10, #0x0]
    ldr r1, [r10, #0x10]
    ldr r2, [r10, #0xc]
    bl _ZN13EquipmentMenu16CreateAllocatorsEP13SafeAllocatorS1_
    ldr r0, [r10, #0x0]
    ldr r1, [sp, #0x30]
    ldr r2, [sp, #0x2c]
    bl _ZN13EquipmentMenu14LoadModelTableEPvj
@L021e3588:
    ldr r0, [r10, #0x10]
    mov r1, #0x800
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, r0
    add r0, r10, #0x2c
    mov r2, #0x800
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    ldr r0, [r10, #0x10]
    mov r1, #0x100
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, r0
    add r0, r10, #0x40
    mov r2, #0x100
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    mov r6, #0x0
    mov r4, #0x40
    mov r9, r6
    mov r8, r4
    b @L021e35f8
@L021e35d4:
    mov r1, r4
    add r0, r10, #0x2c
    bl _ZN13SafeAllocator8AllocateEj
    add r1, r10, r6, lsl #0x2
    str r0, [r1, #0x640]
    mov r1, r9
    mov r2, r8
    bl memset
    add r6, r6, #0x1
@L021e35f8:
    cmp r6, #0x2
    blt @L021e35d4
    ldr r0, [r10, #0x4]
    mov r1, #0x100
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, r0
    add r0, r10, #0x68
    mov r2, #0x100
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    ldr r0, [r10, #0x4]
    mov r1, #0x54
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0xc8]
    ldr r0, [r10, #0x4]
    mov r1, #0x280
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0xcc]
    ldr r0, [r10, #0x4]
    mov r1, #0x8
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0xd0]
    ldr r0, [r10, #0x0]
    cmp r0, #0x0
    ldrne r1, [r10, #0xd0]
    cmpne r1, #0x0
    ldrne r2, [r10, #0xc8]
    cmpne r2, #0x0
    beq @L021e366c
    bl _ZN13EquipmentMenu12CreateChoiceEP19SpriteAnimationListP14SpriteRenderer
@L021e366c:
    ldr r0, [r10, #0x4]
    mov r1, #0x300
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, r0
    add r0, r10, #0x7c
    mov r2, #0x300
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    ldr r0, [r10, #0x4]
    mov r1, #0x200
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, r0
    add r0, r10, #0x90
    mov r2, #0x200
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    ldr r0, [r10, #0x4]
    mov r1, #0xc20
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x120]
    bl _ZN14CharacterModel10InitializeEv
    ldr r0, [r10, #0x120]
    ldr r1, [r10, #0x4]
    bl _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator
    ldr r0, [r10, #0x120]
    bl _ZN14CharacterModel20InitializeVRAMStatesEv
    ldr r0, [r10, #0x120]
    add r1, r10, #0xa4
    bl _ZN14CharacterModel8SetNamesEP13PartNameTable
    ldr r0, [r10, #0x120]
    mov r1, #0x1
    bl _ZN14CharacterModel10SetUnk_c11Eh
    ldr r0, [r10, #0x4]
    mov r1, #0xc20
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x124]
    bl _ZN14CharacterModel10InitializeEv
    ldr r0, [r10, #0x124]
    ldr r1, [r10, #0x4]
    bl _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator
    ldr r0, [r10, #0x124]
    bl _ZN14CharacterModel20InitializeVRAMStatesEv
    ldr r0, [r10, #0x124]
    add r1, r10, #0xa4
    bl _ZN14CharacterModel8SetNamesEP13PartNameTable
    ldr r0, [r10, #0x124]
    mov r1, #0x1
    bl _ZN14CharacterModel10SetUnk_c11Eh
    ldr r0, [r10, #0x14]
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0xa4
    bl func_020de848
    ldr r1, =sCategories
    mov r0, #0x9
    str r1, [sp, #0x0]
    str r0, [sp, #0x4]
    ldr r1, [r10, #0x14]
    ldr r2, [sp, #0x30]
    ldr r3, [sp, #0x2c]
    add r0, r10, #0xa4
    bl func_020dea64
    add r0, r10, #0x2c
    mov r1, #0x2a0
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, #0x0
    mov r2, #0x2a0
    str r0, [r10, #0x638]
    bl memset
    add r0, r10, #0x2c
    mov r1, #0x400
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0x63c]
    mov r1, #0x0
    mov r2, #0x400
    bl memset
    ldr r1, [r10, #0x0]
    mov r2, #0x40
    cmp r1, #0x0
    addne r0, r10, #0xa4
    strne r0, [r1, #0xdf4]
    add r0, r10, #0x74
    add r0, r0, #0x400
    mov r1, #0x4000
    bl func_0207de48
    add r0, r10, #0x74
    add r0, r0, #0x400
    bl func_0207df50
    add r0, r10, #0x400
    ldrsb r0, [r0, #0xe5]
    cmp r0, #0x3
    bne @L021e37e0
    ldr r0, [r10, #0x0]
    cmp r0, #0x0
    beq @L021e37e0
    bl _ZN13EquipmentMenu8LoadVRAMEv
@L021e37e0:
    add r0, r10, #0x4
    mov r1, #0x0
    mov r2, r1
    add r0, r0, #0x400
    bl func_0207de48
    add r0, r10, #0x4
    add r0, r0, #0x400
    bl func_0207df50
    bl func_020421a0
    mov r4, r0
    add r1, r10, #0x74
    add r1, r1, #0x400
    bl func_02042b30
    add r0, r10, #0x74
    add r0, r0, #0x400
    bl func_0207df90
    mov r0, r4
    bl func_020432c4
    add r0, r10, #0x74
    add r0, r0, #0x400
    bl func_0207dfac
    mov r0, r5
    bl func_020100bc
    str r0, [r10, #0x138]
    add r0, r10, #0x13c
    bl func_020a2010
    add r0, r10, #0x13c
    ldr r1, =0xb666
    mov r2, #0xa800
    ldr r3, =0x42ccc
    bl func_0202e5c0
    add r0, r10, #0x13c
    ldr r1, =0xb666
    mov r2, #0xa800
    mov r3, #0x0
    bl func_0202e5c8
    add r0, r10, #0x13c
    bl func_020a27a0
    mov r0, r5
    add r1, r10, #0x13c
    bl func_020100c4
    mov r0, #0x0
    mov r1, r0
    mov r2, r0
    mov r3, r0
    bl func_020c54a4
    mov r0, r7
    ldr r1, [r10, #0x630]
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mov r0, r7
    mvn r1, #0x0
    str r1, [r10, #0x630]
    ldr r1, =data_020f2a40
    mov r2, #0x0
    ldr r1, [r1, #0x0]
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0x630]
    ldrb r0, [r10, #0x4e4]
    add r0, r0, #0x1
    strb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e38d4:
    cmp r0, #0x4
    bne @L021e39b8
    ldr r1, [r10, #0x630]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021e3cf8
    ldr r1, [r10, #0x630]
    add r2, sp, #0x28
    add r3, sp, #0x24
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r1, [sp, #0x24]
    add r0, r10, #0x90
    bl _ZN13SafeAllocator8AllocateEj
    str r0, [r10, #0xc0]
    ldr r1, [sp, #0x28]
    ldr r2, [sp, #0x24]
    bl memcpy
    ldr r1, [sp, #0x24]
    mov r0, r7
    str r1, [r10, #0xc4]
    ldr r1, [r10, #0x630]
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x630]
    ldr r0, [r10, #0xc8]
    bl func_0205a444
    ldr r0, [r10, #0xc8]
    mov r4, #0x0
    strb r4, [r0, #0x50]
    ldr r2, [r10, #0xc8]
    ldr r1, [r10, #0xcc]
    mov r0, #0x10
    str r1, [r2, #0x40]
    strh r0, [r2, #0x4c]
    ldr r1, [r10, #0xd0]
    ldr r0, [r10, #0xc8]
    mov r5, #0x28
    str r1, [r0, #0x3c]
    b @L021e3988
@L021e3978:
    ldr r0, [r10, #0xcc]
    mla r0, r4, r5, r0
    bl func_0205a198
    add r4, r4, #0x1
@L021e3988:
    cmp r4, #0x10
    blt @L021e3978
    ldr r1, =sStrings
    ldr r2, =sStrings+0x12
    mov r0, r7
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r10, #0x630]
    ldrb r0, [r10, #0x4e4]
    add r0, r0, #0x1
    strb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e39b8:
    cmp r0, #0x5
    bne @L021e3a68
    ldr r1, [r10, #0x630]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021e3cf8
    add r0, r10, #0x68
    bl _ZN13SafeAllocator5ResetEv
    ldr r1, [r10, #0x630]
    add r2, sp, #0x1c
    add r3, sp, #0x18
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x1c]
    bl func_02046900
    mov r6, r0
    mov r8, #0x0
    add r5, sp, #0x20
    add r4, sp, #0x14
    b @L021e3a3c
@L021e3a0c:
    ldr r0, [sp, #0x1c]
    mov r1, r8
    mov r2, r5
    mov r3, r4
    bl func_020467f0
    movs r1, r0
    beq @L021e3a38
    ldr r0, [r10, #0xc8]
    ldr r2, [sp, #0x14]
    add r3, r10, #0x68
    bl func_0205a528
@L021e3a38:
    add r8, r8, #0x1
@L021e3a3c:
    cmp r8, r6
    blt @L021e3a0c
    ldr r1, [r10, #0x630]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x630]
    ldrb r0, [r10, #0x4e4]
    add r0, r0, #0x1
    strb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e3a68:
    cmp r0, #0x6
    bne @L021e3a94
    ldr r0, [r10, #0x0]
    cmp r0, #0x0
    beq @L021e3cf8
    bl _ZN13EquipmentMenu4LoadEv
    cmp r0, #0x0
    ldrneb r0, [r10, #0x4e4]
    addne r0, r0, #0x1
    strneb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e3a94:
    cmp r0, #0x7
    bne @L021e3b58
    add r0, sp, #0x34
    bl func_020e46c4
    mov r0, r5
    bl func_020100a8
    mov r1, r0
    add r0, sp, #0x34
    bl func_020e4bf4
    bl func_020421a0
    ldr r1, [r10, #0x0]
    mov r9, #0x0
    mov r8, r0
    add r4, r1, #0x1f8
    add r6, sp, #0x34
    mov r5, #0x100
    mov r11, r9
    b @L021e3b2c
@L021e3adc:
    ldr r1, [sp, #0x3c]
    mov r0, r9, lsl #0x1e
    bic r1, r1, #0x3000000
    orr r1, r1, r0, lsr #0x6
    mov r0, r8
    str r1, [sp, #0x3c]
    bl func_02046380
    ldr r1, =0x226
    str r6, [r8, #0x0]
    add r0, r4, #0xc00
    bl func_020e0434
    stmia sp, {r5, r11}
    mov r2, r0
    str r11, [sp, #0x8]
    add r3, r10, r9, lsl #0x2
    ldr r3, [r3, #0x640]
    mov r0, r8
    mov r1, #0x8
    bl func_02046608
    add r9, r9, #0x1
@L021e3b2c:
    cmp r9, #0x2
    blt @L021e3adc
    ldr r1, =sStrings+0x20
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0x630]
    ldrb r0, [r10, #0x4e4]
    add r0, r0, #0x1
    strb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e3b58:
    cmp r0, #0x8
    bne @L021e3bec
    ldr r1, [r10, #0x630]
    mov r0, r7
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021e3cf8
    ldr r1, [r10, #0x630]
    add r2, sp, #0x10
    add r3, sp, #0xc
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x10]
    cmp r0, #0x0
    beq @L021e3bc8
    add r0, r10, #0x7c
    bl _ZN13SafeAllocator5ResetEv
    add r0, r10, #0xd4
    bl _ZN6Layout10InitializeEv
    ldr r2, [sp, #0x10]
    ldr r3, [sp, #0xc]
    add r0, r10, #0xd4
    add r1, r10, #0x7c
    bl _ZN6Layout4LoadEP13SafeAllocatorPvj
    mov r1, #0x1
    add r0, r10, #0xd4
    mov r2, r1
    bl _ZN12MemberScreen11HideElementEP6Layoutsi
@L021e3bc8:
    ldr r1, [r10, #0x630]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x630]
    ldrb r0, [r10, #0x4e4]
    add r0, r0, #0x1
    strb r0, [r10, #0x4e4]
    b @L021e3cf8
@L021e3bec:
    bl _ZN9GameState11GetInstanceEv
    ldr r1, [r10, #0x4fc]
    bl func_0200ff1c
    movs r4, r0
    beq @L021e3c2c
    ldr r0, [r10, #0x120]
    ldr r1, =0x1eb
    bl _ZN14CharacterModel8SetAngleEi
    mov r0, r4
    bl func_02053c6c
    mov r3, #0x0
    str r3, [sp, #0x0]
    mov r1, r0
    ldr r0, [r10, #0x120]
    ldr r2, [r10, #0x4fc]
    bl _ZN14CharacterModel4LoadEP15PartyMemberDataiii
@L021e3c2c:
    ldr r0, [r10, #0x120]
    add r1, r10, #0x600
    str r0, [r10, #0x128]
    ldr r2, [r10, #0x124]
    mov r0, r10
    str r2, [r10, #0x12c]
    ldrh r2, [r1, #0x34]
    orr r2, r2, #0xa1
    strh r2, [r1, #0x34]
    bl _ZN12MemberScreen9LoadTextsEv
    add r0, r10, #0x400
    ldrsb r0, [r0, #0xe5]
    cmp r0, #0x3
    bne @L021e3c7c
    ldr r0, [r10, #0x0]
    cmp r0, #0x0
    beq @L021e3c7c
    bl _ZN13EquipmentMenu11WriteDigitsEv
    ldr r0, [r10, #0x0]
    bl _ZN13EquipmentMenu10WriteNamesEv
@L021e3c7c:
    ldr r0, =sEdgeColors
    bl func_020c555c
    add r0, r10, #0xd4
    mov r1, #0x11
    mov r2, #0x1
    bl _ZN12MemberScreen11HideElementEP6Layoutsi
    add r0, r10, #0xd4
    mov r1, #0x12
    mov r2, #0x1
    bl _ZN12MemberScreen11HideElementEP6Layoutsi
    add r0, r10, #0xd4
    mov r1, #0x1b
    mov r2, #0x1
    bl _ZN12MemberScreen11HideElementEP6Layoutsi
    add r0, r10, #0xd4
    mov r1, #0x20
    mov r2, #0x1
    bl _ZN12MemberScreen11HideElementEP6Layoutsi
    ldr r0, [r10, #0x4fc]
    ldr r1, [r10, #0xc8]
    bl _ZN12MemberScreen16LoadVocationIconEiP14SpriteRenderer
    mov r0, r10
    add r1, r10, #0x400
    ldrsb r1, [r1, #0xe5]
    bl _ZN12MemberScreen8SetStateEa
    mov r0, #0x0
    strb r0, [r10, #0x4e4]
    add r0, r10, #0x600
    ldrh r1, [r0, #0x34]
    bic r1, r1, #0x2000
    strh r1, [r0, #0x34]
@L021e3cf8:
    add sp, sp, #0x40
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

static LayoutElement* FindElement(Layout* layout, short id)
{
    LayoutElement* elements = layout->elements_;
    if (elements == NULL)
        return NULL;
    unsigned short count = layout->numElements_;
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

void MemberScreen::HideElement(Layout* layout, short id, int flags)
{
    LayoutElement* element = FindElement(layout, id);
    if (element != NULL)
        element->flags_ &= ~flags;
}

void MemberScreen::State_Main()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    if (model_ != NULL)
        model_->Update();
    if (nextModel_ != NULL)
        nextModel_->Update();
    unsigned char step = step_;
    if (step == 0)
    {
        if (model_ != NULL && model_->loading_)
            return;
        SetBrightness(resources, 0, 0xf);
        step_++;
    }
    else if (step == 1)
    {
        if (!IsBrightnessTransitionActive(resources))
            step_++;
    }
    else if (step == 2)
    {
        UpdateMember();
        UpdateTurn(GameState::GetInstance()->GetTickCount());
        UpdateModels();
        UpdateModelLoad();
        UpdateBack();
    }
    if (equipment_ != NULL)
        equipment_->Update();
}

void MemberScreen::UpdateBack()
{
    int back;
    if (layout_.GetTouchedElement() == 0x1f)
        back = 1;
    else
        back = 0;
    if (back)
        flags_ |= MEMBER_SCREEN_BACK_PRESSED;
    if (equipment_ != NULL && !(equipment_->flags_ & 0x400))
        return;
    if (func_02012444(data_02114e30, PAD_BUTTON_B))
        back = 1;
    if (!back)
        return;
    flags_ |= MEMBER_SCREEN_BACK_PRESSED;
    previousState_ = state_;
    state_ = 1;
    step_ = 0;
}

void MemberScreen::State_Exit()
{
    GameState* gameState = GameState::GetInstance();
    GameResources* resources = func_0200fb8c(gameState);
    if (step_ == 0)
    {
        SetBrightness(resources, -0x10, 0xf);
        step_++;
    }
    if (IsBrightnessTransitionActive(resources))
        return;
    if (func_0209ca2c(data_02109bf4))
        return;
    func_020100c4(gameState, previousCamera_);
    step_ = 0;
    previousState_ = state_;
    state_ = -1;
}

// NONMATCHING: the C matches 80.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The HP test (> 0 on an unsigned short) stays a signed bgt in the original; ours becomes bne, and the registers differ
#ifdef NONMATCHING
void MemberScreen::DrawTexts()
{
    GameState* gameState = GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    int color = 0x7fff;
    PartyMember* member = func_0200ff1c(gameState, member_);
    int hp = member->unk_130[2];
    GXFIFO_MATRIX_PUSH = 0;
    GXFIFO_BEGIN_VTXS = 1;
    GXFIFO_MATRIX_TRANSLATE = 0;
    GXFIFO_MATRIX_TRANSLATE = 0;
    GXFIFO_MATRIX_TRANSLATE = 0xffc01000;
    if (hp <= 0)
        color = 0x1f;
    func_02045f3c(messages, names_[member_], nameX_[member_], 0xa1, color, 0xa, 0, 0, 0, 0x11);
    if ((int)member->unk_130[2] <= 0)
    {
        short x = ((0x3b - func_020420e8(downTexts_[member->data_->appearance_.female_], 0)) >> 1) + 0x40;
        func_02045f3c(messages, vocations_[member_], x, 0xa1, color, 0xa, 0, 0, 0, 0x11);
    }
    else
    {
        Sprite* sprite = &sprites_[15];
        sprite->x_ = 0x44000;
        sprite->y_ = 0xa2000;
        sprite->unk_22 = 0x70;
        sprite->unk_26 = 2;
        func_0205ac40(renderer_, sprite);
        if (GetStars(member))
        {
            int starsColor = 0xf0a;
            if (GetStars(member) >= 10)
                starsColor = 0x31f;
            func_02045f3c(messages, levels_[member_], 0x50, 0xa1, starsColor, 0xa, 0, 0, 0, 0x11);
        }
        func_02045f3c(messages, levelLabel_, 0x5c, 0xa1, color, 0xa, 0, 0, 0, 0x11);
        short x = func_020420e8(func_020e51cc(0x3f3), 0) + 0x5e;
        if (func_0200fb08(gameState) == 1)
            x += 2;
        PartyMemberData* data = member->data_;
        equipment_->DrawLevel((short)data->levels_[data->vocation_], x, 0xa1, color);
    }
    GXFIFO_END_VTXS = 0;
    GXFIFO_MATRIX_POP = 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12MemberScreen8GetStarsEP11PartyMember(); // MemberScreen::GetStars
    void _ZN13EquipmentMenu9DrawLevelEisit(); // EquipmentMenu::DrawLevel
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void MemberScreen::DrawTexts()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x18
    mov r8, r0
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_020421a0
    mov r5, r0
    ldr r1, [r8, #0x4fc]
    mov r0, r4
    ldr r6, =0x7fff
    bl func_0200ff1c
    mov r7, r0
    ldr r0, [r7, #0x130]
    ldr r1, =0x4000444
    ldrh r0, [r0, #0x4]
    mov r2, #0x0
    cmp r0, #0x0
    str r2, [r1, #0x0]
    mov r0, #0x1
    str r0, [r1, #0xbc]
    str r2, [r1, #0x2c]
    ldr r0, =0xffc01000
    str r2, [r1, #0x2c]
    str r0, [r1, #0x2c]
    ldr r3, [r8, #0x4fc]
    movle r6, #0x1f
    add r1, r8, #0x500
    mov r0, #0xa
    str r6, [sp, #0x0]
    stmib sp, {r0, r2}
    str r2, [sp, #0xc]
    str r2, [sp, #0x10]
    mov r0, #0x11
    str r0, [sp, #0x14]
    add r0, r8, r3, lsl #0x2
    ldr r2, [r0, #0x580]
    add r1, r1, r3, lsl #0x5
    mov r0, r5
    mov r3, #0xa1
    bl func_02045f3c
    ldr r0, [r7, #0x130]
    ldrh r0, [r0, #0x4]
    cmp r0, #0x0
    bgt @L021e40f0
    ldr r0, [r7, #0x150]
    mov r1, #0x0
    ldrb r0, [r0, #0x49c]
    mov r0, r0, lsl #0x1f
    mov r0, r0, lsr #0x1f
    add r0, r8, r0, lsl #0x2
    ldr r0, [r0, #0x640]
    bl func_020420e8
    str r6, [sp, #0x0]
    mov r1, #0xa
    str r1, [sp, #0x4]
    mov r1, #0x0
    mov r0, r0, lsl #0x10
    str r1, [sp, #0x8]
    str r1, [sp, #0xc]
    mov r0, r0, asr #0x10
    rsb r0, r0, #0x3b
    mov r0, r0, asr #0x1
    add r0, r0, #0x40
    mov r2, r0, lsl #0x10
    str r1, [sp, #0x10]
    mov r0, #0x11
    str r0, [sp, #0x14]
    ldr r3, [r8, #0x4fc]
    add r1, r8, #0x590
    mov r0, #0x14
    mla r1, r3, r0, r1
    mov r0, r5
    mov r2, r2, asr #0x10
    mov r3, #0xa1
    bl func_02045f3c
    b @L021e4218
@L021e40f0:
    ldr r1, [r8, #0xcc]
    mov r0, #0x44000
    str r0, [r1, #0x26c]
    mov r0, #0xa2000
    str r0, [r1, #0x270]
    mov r0, #0x70
    strb r0, [r1, #0x27a]
    mov r0, #0x2
    strb r0, [r1, #0x27e]
    ldr r0, [r8, #0xc8]
    add r1, r1, #0x258
    bl func_0205ac40
    mov r0, r7
    bl _ZN12MemberScreen8GetStarsEP11PartyMember
    cmp r0, #0x0
    beq @L021e4184
    ldr r9, =0xf0a
    mov r0, r7
    bl _ZN12MemberScreen8GetStarsEP11PartyMember
    cmp r0, #0xa
    ldrhs r9, =0x31f
    mov r0, #0xa
    str r9, [sp, #0x0]
    str r0, [sp, #0x4]
    mov r0, #0x0
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    mov r0, #0x11
    str r0, [sp, #0x14]
    ldr r1, [r8, #0x4fc]
    add r2, r8, #0x5f0
    add r1, r2, r1, lsl #0x4
    mov r0, r5
    mov r2, #0x50
    mov r3, #0xa1
    bl func_02045f3c
@L021e4184:
    str r6, [sp, #0x0]
    mov r0, #0xa
    str r0, [sp, #0x4]
    mov r1, #0x0
    str r1, [sp, #0x8]
    str r1, [sp, #0xc]
    mov r0, r5
    str r1, [sp, #0x10]
    mov r5, #0x11
    add r1, r8, #0x5e0
    mov r2, #0x5c
    mov r3, #0xa1
    str r5, [sp, #0x14]
    bl func_02045f3c
    ldr r0, =0x3f3
    bl func_020e51cc
    mov r1, #0x0
    bl func_020420e8
    add r0, r0, #0x5e
    mov r1, r0, lsl #0x10
    mov r0, r4
    mov r4, r1, asr #0x10
    bl func_0200fb08
    cmp r0, #0x1
    addeq r0, r4, #0x2
    moveq r0, r0, lsl #0x10
    moveq r4, r0, asr #0x10
    ldr r1, [r7, #0x150]
    mov r2, r4
    ldr r0, [r1, #0x950]
    mov r3, #0xa1
    add r0, r1, r0, lsl #0x1
    add r0, r0, #0x100
    ldrsh r1, [r0, #0x6c]
    str r6, [sp, #0x0]
    ldr r0, [r8, #0x0]
    bl _ZN13EquipmentMenu9DrawLevelEisit
@L021e4218:
    ldr r1, =0x4000504
    mov r0, #0x0
    str r0, [r1, #0x0]
    mov r0, #0x1
    str r0, [r1, #-0xbc]
    add sp, sp, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

unsigned int MemberScreen::GetStars(PartyMember* member)
{
    PartyMemberData* data = member->data_;
    return data->unk_186[data->vocation_];
}

void MemberScreen::DrawLeftRight()
{
    short x, y;
    Sprite* sprite = &sprites_[2];
    layout_.GetPosition(0x11, &x, &y);
    if (flags_ & MEMBER_SCREEN_LEFT)
    {
        x -= 1;
        y += 1;
    }
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x7f;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
    sprite = &sprites_[3];
    layout_.GetPosition(0x12, &x, &y);
    if (flags_ & MEMBER_SCREEN_RIGHT)
    {
        x += 1;
        y += 1;
    }
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x7e;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
}

void MemberScreen::DrawNext()
{
    short x, y;
    if (memberCount_ == 1)
        return;
    Sprite* sprite = &sprites_[0];
    layout_.GetPosition(0x20, &x, &y);
    if (flags_ & MEMBER_SCREEN_NEXT_PRESSED)
    {
        x += 1;
        y += 1;
        flags_ &= ~MEMBER_SCREEN_NEXT_PRESSED;
    }
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x7b;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
}

void MemberScreen::DrawBack()
{
    short x, y;
    Sprite* sprite = &sprites_[1];
    layout_.GetPosition(0x1b, &x, &y);
    if (flags_ & MEMBER_SCREEN_BACK_PRESSED)
    {
        x += 1;
        y += 1;
        flags_ &= ~MEMBER_SCREEN_BACK_PRESSED;
    }
    sprite->x_ = x << 12;
    sprite->y_ = y << 12;
    sprite->unk_22 = 0x79;
    sprite->unk_26 = 2;
    func_0205ac40(renderer_, sprite);
}

void MemberScreen::UpdateModels()
{
    unsigned short flags = flags_;
    if ((flags & MEMBER_SCREEN_SWAP_MODELS) && !nextModel_->loading_)
    {
        if (flags & MEMBER_SCREEN_KEEP_ANGLE)
        {
            model_->SetAngle(0x1eb);
            nextModel_->SetAngle(0x1eb);
        }
        else
        {
            nextModel_->SetRotation(model_->GetRotation());
        }
        CharacterModel* model = model_;
        model_ = nextModel_;
        nextModel_ = model;
        nextModel_->Hide(0);
        nextModel_->Hide(1);
        nextModel_->Hide(5);
        nextModel_->Hide(6);
        nextModel_->Hide(2);
        nextModel_->Hide(3);
        nextModel_->Hide(4);
        flags_ &= ~MEMBER_SCREEN_SWAP_MODELS;
        flags_ &= ~MEMBER_SCREEN_KEEP_ANGLE;
    }
}

void MemberScreen::UpdateModelLoad()
{
    if (flags_ & MEMBER_SCREEN_LOAD_MODEL)
    {
        PartyMember* member = func_0200ff1c(GameState::GetInstance(), member_);
        if (member != NULL)
        {
            int animations = 0;
            if (flags_ & MEMBER_SCREEN_LOAD_ANIMATIONS)
                animations = 1;
            Object3D* body = model_->GetBody();
            Object3D* nextBody = nextModel_->GetBody();
            nextBody->MaybeSetRegularAnimation((const char*)body->activeAnimationRecord_, 0);
            nextBody->SetCurrentAnimationTime(body->animationTime_);
            nextModel_->Load(func_02053c6c(member), member_, animations, 1);
            flags_ &= ~MEMBER_SCREEN_LOAD_MODEL;
            flags_ &= ~MEMBER_SCREEN_LOAD_ANIMATIONS;
            timer_ = 0;
            flags_ |= MEMBER_SCREEN_SWAP_MODELS;
        }
    }
}

void MemberScreen::UpdateTurn(unsigned int ticks)
{
    model_->GetBody();
    unsigned short flags = flags_;
    if (flags & MEMBER_SCREEN_TURN_BACK)
    {
        int done = 0;
        int angle;
        Vector3fix rotation = model_->GetRotation();
        int difference = fix32ReduceAngle0To2Pi(0x1eb - rotation.y);
        if (difference >= 0 && difference < 0x3244)
        {
            angle = rotation.y + difference / 12;
            for (unsigned int i = 0; i < ticks - 1; i++)
                angle += fix32ReduceAngle0To2Pi(0x1eb - angle) / 12;
        }
        else if (difference >= 0x3244 && difference < 0x6488)
        {
            angle = rotation.y - (0x6488 - difference) / 12;
            for (unsigned int i = 0; i < ticks - 1; i++)
                angle -= (0x6488 - fix32ReduceAngle0To2Pi(0x1eb - angle)) / 12;
        }
        model_->SetAngle(fix32ReduceAngle0To2Pi(angle));
        int left = fix32ReduceAngle0To2Pi(0x1eb - angle);
        int distance = left < 0 ? -left : left;
        if (distance < 0x28)
        {
            done = 1;
        }
        else
        {
            distance = 0x6488 - left;
            if (distance < 0)
                distance = -distance;
            if (distance < 0x28)
                done = 1;
        }
        if (done)
        {
            model_->SetAngle(fix32ReduceAngle0To2Pi(0x1eb));
            flags_ &= ~MEMBER_SCREEN_TURN_BACK;
        }
    }
    else if (flags & MEMBER_SCREEN_TURNING)
    {
        int left = 0;
        int right = 0;
        int touched = 0;
        if (data_02114e54.touching_)
        {
            short element = layout_.GetTouchedElement();
            if (element == 0x22)
                left = 1;
            if (element == 0x23)
                right = 1;
            touched = 1;
        }
        else if (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0)
        {
            if (flags & MEMBER_SCREEN_LEFT)
                left = 1;
            if (flags & MEMBER_SCREEN_RIGHT)
                right = 1;
            touched = 1;
        }
        else if (data_02114e54.unk_54 != 0)
        {
            touched = 1;
        }
        if (!touched)
        {
            if (func_02012430(data_02114e30, PAD_BUTTON_L))
                left = 1;
            if (func_02012430(data_02114e30, PAD_BUTTON_R))
                right = 1;
        }
        if (left && right)
        {
            flags_ |= MEMBER_SCREEN_TURN_BACK;
        }
        else if (left || right)
        {
            Vector3fix rotation = model_->GetRotation();
            if (left)
                rotation.y += (int)(4096.0f * (0.08f * ticks));
            if (right)
                rotation.y -= (int)(4096.0f * (0.08f * ticks));
            rotation.y = fix32ReduceAngle0To2Pi(rotation.y);
            model_->SetRotation(rotation);
        }
        if (left)
            flags_ |= MEMBER_SCREEN_LEFT;
        else
            flags_ &= ~MEMBER_SCREEN_LEFT;
        if (right)
            flags_ |= MEMBER_SCREEN_RIGHT;
        else
            flags_ &= ~MEMBER_SCREEN_RIGHT;
    }
}

// NONMATCHING: the C matches 85.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The HP test (> 0 on an unsigned short) stays a signed bgt in the original; ours becomes bne
#ifdef NONMATCHING
void MemberScreen::LoadTexts()
{
    GameState* gameState = GameState::GetInstance();
    MessageSystem* messages = func_020421a0();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 16; j++)
            names_[i][j] = 0xffff;
        for (int j = 0; j < 10; j++)
            vocations_[i][j] = 0xffff;
        for (int j = 0; j < 8; j++)
            levels_[i][j] = 0xffff;
        nameX_[i] = 0;
    }
    for (int i = 0; i < 8; i++)
        levelLabel_[i] = 0xffff;
    func_02045cac(messages);
    char* texts = (char*)equipment_ + 0x1f8;
    func_02045d14(messages, func_020e51cc(0x3f3), levelLabel_, 0);
    for (int i = 0; i < 4; i++)
    {
        PartyMember* member = func_0200ff1c(gameState, i);
        if (member == NULL)
            continue;
        const char* name = member->status_->name_;
        func_02045d14(messages, name, names_[i], 0);
        nameX_[i] = 0x23 - func_020420e8(name, 0) / 2;
        short vocation = member->data_->vocation_ + 0x1f4;
        func_ov017_0218b5b0();
        if (func_ov017_021bdbcc())
            vocation = 0x1f4;
        if ((int)member->unk_130[2] <= 0)
            func_02045d14(messages, downTexts_[member->data_->appearance_.female_], vocations_[i], 0);
        else
            func_02045d14(messages, func_020e0434(texts + 0xc00, vocation), vocations_[i], 0);
        unsigned char stars = GetStars(member);
        char text[0x10] = {0};
        if (stars != 0)
            sprintf(text, STRING(0x34, "<tc%d>"), GetStars(member));
        func_02045d14(messages, text, levels_[i], 0);
        func_020439b0(messages, 0);
    }
}
#else
asm void MemberScreen::LoadTexts()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x18
    mov r5, r0
    bl _ZN9GameState11GetInstanceEv
    str r0, [sp, #0x0]
    bl func_020421a0
    mov r4, #0x0
    mov r8, r0
    ldr r2, =0xffff
    mov r3, r4
    mov r1, r4
    mov r0, r4
    mov r7, r4
    b @L021e4a58
@L021e49dc:
    mov r10, r3
    add r9, r5, r4, lsl #0x5
    b @L021e49f8
@L021e49e8:
    add r6, r9, r10, lsl #0x1
    add r6, r6, #0x500
    strh r2, [r6, #0x0]
    add r10, r10, #0x1
@L021e49f8:
    cmp r10, #0x10
    blt @L021e49e8
    mov r6, #0x14
    mla r9, r4, r6, r5
    mov r10, r1
    b @L021e4a20
@L021e4a10:
    add r6, r9, r10, lsl #0x1
    add r6, r6, #0x500
    strh r2, [r6, #0x90]
    add r10, r10, #0x1
@L021e4a20:
    cmp r10, #0xa
    blt @L021e4a10
    mov r10, r0
    add r9, r5, r4, lsl #0x4
    b @L021e4a44
@L021e4a34:
    add r6, r9, r10, lsl #0x1
    add r6, r6, #0x500
    strh r2, [r6, #0xf0]
    add r10, r10, #0x1
@L021e4a44:
    cmp r10, #0x8
    blt @L021e4a34
    add r6, r5, r4, lsl #0x2
    str r7, [r6, #0x580]
    add r4, r4, #0x1
@L021e4a58:
    cmp r4, #0x4
    blt @L021e49dc
    mov r2, #0x0
    ldr r1, =0xffff
    b @L021e4a7c
@L021e4a6c:
    add r0, r5, r2, lsl #0x1
    add r0, r0, #0x500
    strh r1, [r0, #0xe0]
    add r2, r2, #0x1
@L021e4a7c:
    cmp r2, #0x8
    blt @L021e4a6c
    mov r0, r8
    bl func_02045cac
    ldr r1, [r5, #0x0]
    ldr r0, =0x3f3
    add r1, r1, #0x1f8
    str r1, [sp, #0x4]
    bl func_020e51cc
    mov r1, r0
    mov r0, r8
    add r2, r5, #0x5e0
    mov r3, #0x0
    bl func_02045d14
    mov r4, #0x0
    add r7, r5, #0x500
    add r6, r5, #0x590
    add r11, r5, #0x5f0
    b @L021e4bfc
@L021e4ac8:
    ldr r0, [sp, #0x0]
    mov r1, r4
    bl func_0200ff1c
    movs r9, r0
    beq @L021e4bf8
    ldr r10, [r9, #0x134]
    mov r0, r8
    mov r1, r10
    add r2, r7, r4, lsl #0x5
    mov r3, #0x0
    bl func_02045d14
    mov r0, r10
    mov r1, #0x0
    bl func_020420e8
    add r0, r0, r0, lsr #0x1f
    mov r0, r0, asr #0x1
    rsb r1, r0, #0x23
    add r0, r5, r4, lsl #0x2
    str r1, [r0, #0x580]
    ldr r0, [r9, #0x150]
    ldr r0, [r0, #0x950]
    add r0, r0, #0x1f4
    mov r0, r0, lsl #0x10
    mov r10, r0, asr #0x10
    bl func_ov017_0218b5b0
    bl func_ov017_021bdbcc
    cmp r0, #0x0
    ldr r0, [r9, #0x130]
    movne r10, #0x1f4
    ldrh r0, [r0, #0x4]
    cmp r0, #0x0
    bgt @L021e4b78
    ldr r3, [r9, #0x150]
    mov r1, #0x14
    mla r2, r4, r1, r6
    ldrb r1, [r3, #0x49c]
    mov r0, r8
    mov r3, #0x0
    mov r1, r1, lsl #0x1f
    mov r1, r1, lsr #0x1f
    add r1, r5, r1, lsl #0x2
    ldr r1, [r1, #0x640]
    bl func_02045d14
    b @L021e4ba0
@L021e4b78:
    ldr r0, [sp, #0x4]
    mov r1, r10
    add r0, r0, #0xc00
    bl func_020e0434
    mov r2, #0x14
    mla r2, r4, r2, r6
    mov r1, r0
    mov r0, r8
    mov r3, #0x0
    bl func_02045d14
@L021e4ba0:
    mov r0, r9
    bl _ZN12MemberScreen8GetStarsEP11PartyMember
    and r10, r0, #0xff
    add r0, sp, #0x8
    mov r1, #0x10
    bl __clear
    cmp r10, #0x0
    beq @L021e4bd8
    mov r0, r9
    bl _ZN12MemberScreen8GetStarsEP11PartyMember
    mov r2, r0
    ldr r1, =sStrings+0x34
    add r0, sp, #0x8
    bl sprintf
@L021e4bd8:
    mov r0, r8
    add r1, sp, #0x8
    add r2, r11, r4, lsl #0x4
    mov r3, #0x0
    bl func_02045d14
    mov r0, r8
    mov r1, #0x0
    bl func_020439b0
@L021e4bf8:
    add r4, r4, #0x1
@L021e4bfc:
    cmp r4, #0x4
    blt @L021e4ac8
    add sp, sp, #0x18
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void MemberScreen::UpdateMember()
{
    unsigned short flags = flags_;
    if (flags & MEMBER_SCREEN_KEEP_ANGLE)
        return;
    if (!(flags & MEMBER_SCREEN_CHANGE_MEMBER))
        return;
    GameState* gameState = GameState::GetInstance();
    int index = -1;
    for (int i = 0; i < 4; i++)
    {
        if (member_ == members_[i])
        {
            index = i;
            break;
        }
    }
    int next = 0;
    if (data_02114e54.touching_ && layout_.GetTouchedElement() == 0x21)
        next = 1;
    if (!next && func_02012444(data_02114e30, PAD_BUTTON_Y))
        next = 1;
    if (!next)
        return;
    do
    {
        index += next;
        if (index < 0)
            index = memberCount_ - 1;
        if (index > memberCount_ - 1)
            index = 0;
    } while (gameState->GetGameObjectByIndex(members_[index]) == NULL);
    if (member_ == members_[index])
        return;
    flags_ |= MEMBER_SCREEN_NEXT_PRESSED;
    if (equipment_ != NULL)
    {
        signed char member = members_[index];
        void* background = &equipment_->backgrounds_[0];
        if (background != NULL && func_0204af14(background, 1))
            func_020dc7e8(5, member);
    }
    LoadVocationIcon(members_[index], renderer_);
    unsigned short objectFlags = gameState->GetGameObjectByIndex(members_[index])->obj3D_.unknown_0_;
    if (!(objectFlags & 0x1000) && !(objectFlags & 0x800) && !(objectFlags & 0x200))
        return;
    if (timer_ > 0)
        return;
    member_ = members_[index];
    flags_ |= MEMBER_SCREEN_LOAD_MODEL | MEMBER_SCREEN_LOAD_ANIMATIONS | MEMBER_SCREEN_KEEP_ANGLE;
    func_0205eaa0(data_02108760, 1, 0);
    if (mode_ != 3)
        return;
    if (equipment_ == NULL)
        return;
    equipment_->Reload();
    equipment_->flags_ |= 0x200;
    equipment_->SetMember(member_, 1);
}

void MemberScreen::DoNothing()
{
}

Object3D* MemberScreen::GetBody()
{
    if (model_ == NULL)
        return NULL;
    return model_->GetBody();
}

// NONMATCHING: the C matches 85.0 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original returns with bxne after the LOADING test; MWCC makes the next test conditional
#ifdef NONMATCHING
void MemberScreen::UpdateClose()
{
    unsigned short flags = flags_;
    if (!(flags & MEMBER_SCREEN_CLOSE))
        return;
    if (flags & MEMBER_SCREEN_LOADING)
        return;
    if (closed_ != 0)
        return;
    previousState_ = state_;
    state_ = 1;
    step_ = 0;
    closed_++;
}
#else
asm void MemberScreen::UpdateClose()
{
    add r1, r0, #0x600
    ldrh r1, [r1, #0x34]
    tst r1, #0x1000
    bxeq lr
    tst r1, #0x2000
    bxne lr
    ldrb r1, [r0, #0x636]
    cmp r1, #0x0
    bxne lr
    add r1, r0, #0x400
    ldrsb r3, [r1, #0xe6]
    mov r2, #0x1
    mov r1, #0x0
    strb r3, [r0, #0x4e7]
    strb r2, [r0, #0x4e6]
    strb r1, [r0, #0x4e4]
    ldrb r1, [r0, #0x636]
    add r1, r1, #0x1
    strb r1, [r0, #0x636]
    bx lr
}
#endif
