#include "Bestiary/MonsterInfoScreen.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "GameState/GameState.h"
#include "Graphics/LightingManager.h"
#include "Resource/GameResources.h"
#include "System/Graphics.h"
#include <globaldefs.h>
#include <std_library_functions.h>

extern "C"
{
    // Sets the camera
    void func_020100c4(GameState* gameState, void* camera);
    // Returns the camera
    void* func_020100f8(GameState* gameState);
    // Initializes a sprite
    void func_0205a198(Sprite* sprite);
    // Initializes a sprite renderer
    void func_0205a444(SpriteRenderer* renderer);
    // Draws a sprite
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    // Returns whether the buttons are held
    bool func_02012430(void* pad, int buttons);
    // Returns whether the buttons were just released
    bool func_02012468(void* pad, int buttons);
    // Adds the sprite cells of a file to a sprite renderer
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    // Returns the number of files in a .pac file
    int func_02046900(void* pac);
    // Returns a file of a .pac file
    void* func_020467f0(void* pac, int index, void** outName, unsigned int* outSize);
    // MonsterInfoTable functions
    void func_02096fb0(MonsterInfoTable* table);
    void func_02096fc4(MonsterInfoTable* table);
    void func_02097054(MonsterInfoTable* table, SafeAllocator* allocator, void* file, unsigned int size, short monsterID);
    MonsterInfo* func_02097224(MonsterInfoTable* table, short monsterID);
    MonsterRecordCount* func_02097238(MonsterInfoTable* table);

    void func_0202e0a4(void* camera);
    void func_0202e5c8(void* camera, fix32_t x, fix32_t y, fix32_t z);
    void func_0202e5d8(void* camera, fix32_t x, fix32_t y, fix32_t z);
    void func_020a2010(void* camera);
    void func_020a27a0(void* camera);
    void func_0203b4d8(void*, int);
    void func_0203b4e8(void*, int);
    void func_0203dafc(ObjectArchiveLoadInfo* info);
    void* func_020421a0();
    void func_02046608(void* font, int, const char* input, char* output, int, int, int);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b2e0(BackgroundGraphics* graphics, void* file);
    void func_0204b3a0(BackgroundGraphics* graphics, void* file);
    void func_0204b4c0(BackgroundGraphics* graphics, void* file);
    void func_0204b5b4(BackgroundGraphics* graphics, int);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0206819c(const char* input, char* output, int);
    void func_0207df50(void*);
    void func_0207df90(void*);
    void func_0207dfac(void*);
    void func_020c54a4(int, int, int, int);
    void func_020c5588(int, int, int, int, int);
    void func_020dfc2c(void*);
    void func_020dfc40(void*);
    // Returns a text of a .nat file
    const char* func_020e0434(void* texts, int id);
    // Reads the description of a monster
    void func_020e046c(char* output, void* file, unsigned int size, short infoID);
    // Converts a string
    void func_020e4864(const char* input, char* output, int, int, int, int);
    void func_020e526c(void* reader);
    void func_020e56fc(void* reader, void* file, unsigned int size);
    const char** func_020e5294(void* reader, short id);

    // Returns the layout element's position
    void func_ov023_021e2bdc(Layout* layout, short id, short* x, short* y);
    // Sets the text of a layout element
    void func_ov023_021e23d0(Layout* layout, short id, const char* text, int, int);
    // Sets the number shown by a layout element
    void func_ov023_021e24b0(Layout* layout, short id, int value, int, int, int, int, int, int);
    // Draws a layout to its canvas
    void func_ov023_021e257c(Layout* layout);
    void func_ov023_021e20c0(Layout* layout);
    void func_ov023_021e20f0(Layout* layout, SafeAllocator* allocator, void* file, unsigned int size);


    extern char data_02114e30[];
}

// These can't be inline functions, since the compiler doesn't inline functions with an if statement
#define SHOW_ELEMENT(layout, id)                                \
    {                                                           \
        LayoutElement* element = FindLayoutElement(layout, id); \
        if (element != NULL)                                    \
            element->flags_ |= LAYOUT_ELEMENT_FLAG_VISIBLE;     \
    }

#define HIDE_ELEMENT(layout, id)                                \
    {                                                           \
        LayoutElement* element = FindLayoutElement(layout, id); \
        if (element != NULL)                                    \
            element->flags_ &= ~LAYOUT_ELEMENT_FLAG_VISIBLE;    \
    }

#define PAD_BUTTON_R 0x100
#define PAD_BUTTON_L 0x200

// How fast the model rotates with the L and R buttons, per tick
#define ROTATION_SPEED 0xcc
// 2 pi in fixed point
#define FULL_TURN 0x6487

// The day lengths and thresholds come from a header that many files include (see src/Graphics/LightingInfo.cpp).
// In the original they're separate variables, and so is the guard of s_states, a static local of Update(). The
// compiler places separate variables in another order, so they're grouped in structs here, and declared in the order
// that gives the original layout.
static float s_nightLength = 180.0f;
static float s_eveningLength = 30.0f;
static float s_morningLength = 30.0f;
static float s_dayLength = 180.0f;

static struct
{
    float dayThreshold2;
    // The camera before the screen was opened
    void* previousCamera;
} s_statics1;

// What Update() runs in each state. The last entry is NULL, which is set when Update() first runs.
static void (MonsterInfoScreen::*s_states[MonsterInfoScreen::State_Count + 1])() = {
    &MonsterInfoScreen::Setup,
    &MonsterInfoScreen::Run,
};

// dayThreshold1 has to start its struct: when it's further into one, the compiler doesn't load s_dayLength before
// storing it, unlike the original
static struct
{
    float dayThreshold1;
    float dayThreshold3;
    float dayThreshold4;
} s_statics2 = {
    (s_statics2.dayThreshold4 = s_eveningLength + (s_dayLength + (s_nightLength + s_morningLength)),
     s_statics1.dayThreshold2 = s_statics2.dayThreshold3 + s_nightLength,
     s_statics1.dayThreshold2 + s_morningLength),
};

static struct
{
    float dayThreshold0;
    // Originally the guard of s_states
    unsigned int statesInitialized;
} s_statics0 = { s_statics2.dayThreshold1 + s_dayLength };

static LayoutElement* FindLayoutElement(Layout* layout, short id)
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

// These are declared after the first function, so that the compiler keeps them in this order.
// Unused, but the last values match the rotation in Update()
static const struct
{
    unsigned char unk_0[3];
    fix32_t unk_4;
    fix32_t unk_8;
    fix32_t unk_c;
} s_unused0 = { { 15, 10, 8 }, 0xcc, 0xcc, 0x6487 };

// Layout elements of the L, R and page buttons
static const short s_buttonIDs[3] = { 0x1a, 0x1b, 0x14 };

// Sizes of the buffers in buffers_
static const unsigned int s_bufferSizes[3] = { 0x6400, 0x280, 0x8cc };

// How far the L, R and page buttons move while they're pressed
static const struct
{
    short x;
    short y;
} s_pressedOffsets[3] = { { -1, 1 }, { 1, 1 }, { 1, 1 } };

void MonsterInfoScreen::Allocate(SafeAllocator* allocator)
{
    if (allocator == NULL)
        return;

    const unsigned int allocatorSizes[6] = { 0x200, 0x100, 0x23000, 0x800, 0x2800, 0x400 };
    allocators_ = (SafeAllocator*)allocator->Allocate(6 * sizeof(SafeAllocator));
    buffers_ = (void**)allocator->Allocate(3 * sizeof(void*));
    for (int i = 0; i < 3; i++)
        buffers_[i] = allocator->Allocate(s_bufferSizes[i]);
    model_ = (Object3D*)allocator->Allocate(sizeof(Object3D));
    camera_ = allocator->Allocate(0x2c8);
    layout_ = (Layout*)allocator->Allocate(sizeof(Layout));
    dropNames_[0] = (char*)allocator->Allocate(0x48);
    dropNames_[1] = (char*)allocator->Allocate(0x48);
    description_ = (char*)allocator->Allocate(0x200);
    spriteRenderer_ = (SpriteRenderer*)allocator->Allocate(sizeof(SpriteRenderer));
    sprites_ = (Sprite*)allocator->Allocate(3 * sizeof(Sprite));
    for (unsigned char i = 0; i < 3; i++)
        func_0205a198(&sprites_[i]);
    func_0205a444(spriteRenderer_);
    spriteRenderer_->unk_50 = 0;
    spriteRenderer_->SetSprites(sprites_, 3);
    for (int i = 0; i < 6; i++)
    {
        unsigned int size = allocatorSizes[i];
        allocators_[i].CreateTypeA(allocator->Allocate(size), size);
        allocators_[i].Reset();
    }
    model_->Initialize();
    model_->EnableFlag(4);
    loadModel_ = true;
}

// Unused
static const short s_unused1[4] = { 0x1e, 0x10, 0x10, 0x10 };

void MonsterInfoScreen::Init()
{
    s_statics1.previousCamera = NULL;
    buffers_ = NULL;
    spriteRenderer_ = NULL;
    sprites_ = NULL;
    func_02096fb0(&infos_);
    habitats_.Init();
    allocators_ = NULL;
    model_ = NULL;
    camera_ = NULL;
    monster_ = NULL;
    prevMonster_ = NULL;
    record_ = NULL;
    prevRecord_ = NULL;
    layout_ = NULL;
    texts_ = NULL;
    dropNames_[0] = NULL;
    dropNames_[1] = NULL;
    description_ = NULL;
    taskID_ = -1;
    backgroundTaskID_ = -1;
    unk_78 = -1;
    animationIndex_ = 0;
    state_ = State_Setup;
    initStep_ = 0;
    backgroundStep_ = 0;
    loadStep_ = 0;
    page_ = 0;
    flags_ = 0;
    rotating_ = false;
    unk_82_1_ = false;
    loadModel_ = false;
    unk_82_4_ = 0;
    unk_82_3_ = false;
    for (int i = 0; i < 5; i++)
        taskIDs_[i] = -1;
    variants_ = NULL;
    best_.Init();
    memset(buttonPressed_, 0, sizeof(buttonPressed_));
    unk_93 = 0;
    unk_94 = 0;
}

void MonsterBest::Init()
{
    value_ = 0;
    monsterID_ = -1;
    count_ = 0;
}

void MonsterInfoScreen::Release()
{
    if (taskID_ >= 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->RemoveTask(taskID_);
        taskID_ = -1;
    }
    if (backgroundTaskID_ >= 0)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loader->RemoveTask(backgroundTaskID_);
        backgroundTaskID_ = -1;
    }
    for (int i = 0; i < 5; i++)
    {
        short taskID = taskIDs_[i];
        if (taskID >= 0)
        {
            BackgroundLoader::GetInstance()->RemoveTask(taskID);
            taskIDs_[i] = -1;
        }
    }
    habitats_.Unload();
    func_02096fc4(&infos_);
    habitats_.Init();
    func_020100c4(GameState::GetInstance(), s_statics1.previousCamera);
    s_statics1.previousCamera = NULL;
    LightingManager::GetInstance()->fogEnabled_ = true;
    if (allocators_ == NULL)
        return;
    for (int i = 0; i < 6; i++)
    {
        if (allocators_[i].GetSignedAllocator() != NULL)
            allocators_[i].Destroy();
    }
}

void MonsterInfoScreen::Update()
{
    UpdateBackground();
    if (model_ != NULL)
    {
        model_->AdvanceEffects();
        fix32_t baseAngle = 0;
        if (monster_ != NULL)
        {
            MonsterInfo* info = func_02097224(&infos_, monster_->monsterID_);
            if (info != NULL)
                baseAngle = 4096.0f * info->rotationY_;
        }

        Vector3fix newRotation;
        Vector3fix rotation;
        Object3D* model = model_;
        unsigned char rotating = rotating_;
        fix32_t speed;
        unsigned char keepRotating;
        bool pressed;
        if (model == NULL)
        {
            keepRotating = false;
        }
        else
        {
            pressed = false;
            buttonPressed_[0] = false;
            keepRotating = rotating;
            speed = 0;
            buttonPressed_[1] = false;
            if (func_02012430(data_02114e30, PAD_BUTTON_L) && func_02012430(data_02114e30, PAD_BUTTON_R))
            {
                if (!rotating)
                {
                    keepRotating = true;
                    buttonPressed_[0] = true;
                    buttonPressed_[1] = true;
                }
            }
            else if (func_02012430(data_02114e30, PAD_BUTTON_L) && !func_02012468(data_02114e30, PAD_BUTTON_R))
            {
                pressed = true;
                buttonPressed_[0] = true;
                speed = ROTATION_SPEED;
            }
            else if (func_02012430(data_02114e30, PAD_BUTTON_R) && !func_02012468(data_02114e30, PAD_BUTTON_L))
            {
                pressed = true;
                buttonPressed_[1] = true;
                speed = -ROTATION_SPEED;
            }

            if (rotating)
            {
                rotation = model->rotation_;
                fix32_t distance = baseAngle - rotation.y;
                if (rotation.y >= baseAngle + FULL_TURN / 2)
                    distance = baseAngle + FULL_TURN - rotation.y;
                speed = distance / 5;
                if (!func_02012430(data_02114e30, PAD_BUTTON_R) && !func_02012430(data_02114e30, PAD_BUTTON_L)
                    && rotation.y == baseAngle)
                    keepRotating = false;
            }

            if (pressed || rotating)
            {
                speed *= GameState::GetInstance()->GetTickCount();
                newRotation = model->rotation_;
                newRotation.y += speed;
                if (rotating)
                {
                    if (newRotation.y < baseAngle + ROTATION_SPEED
                        || newRotation.y > baseAngle + FULL_TURN - ROTATION_SPEED)
                        newRotation.y = baseAngle;
                    if (!buttonPressed_[0] || !buttonPressed_[1] || newRotation.y == baseAngle)
                    {
                        buttonPressed_[0] = false;
                        buttonPressed_[1] = false;
                    }
                }
                if (newRotation.y < 0)
                    newRotation.y += FULL_TURN;
                if (newRotation.y >= FULL_TURN)
                    newRotation.y -= FULL_TURN;
                model->rotation_ = newRotation;
            }
        }
        rotating_ = keepRotating;

        if (model_->HasAnimationStopped() || model_->HasAnimationReachedEnd())
        {
            model = model_;
            BCFG::AnimationRecord* animation = model->activeAnimationRecord_;
            if (animation != NULL && strcmp("stand", animation->name) != 0 && strcmp("run", animation->name) != 0)
                model->MaybeSetRegularAnimation("stand", 0);
        }
    }

    buttonPressed_[2] = false;
    if (!(s_statics0.statesInitialized & 1))
    {
        s_states[State_Count] = NULL;
        s_statics0.statesInitialized |= 1;
    }
    if (s_states[state_] != NULL)
        (this->*s_states[state_])();
}

void MonsterInfoScreen::Draw()
{
    if (state_ == State_Setup)
        return;
    if (monster_ == NULL || record_ == NULL)
        return;
    if (!monster_->known_)
        return;

    bool showArrows = false;
    bool showPageButton = false;
    if (flags_ & 0x20)
    {
        if (prevMonster_ != NULL && prevMonster_->known_)
            showArrows = true;
        if (prevRecord_ != NULL && prevRecord_->complete_)
            showPageButton = true;
    }
    else
    {
        if (monster_->known_)
            showArrows = true;
        if (record_->complete_)
            showPageButton = true;
    }

    if (showArrows || showPageButton)
    {
        for (int i = 0; i < 3; i++)
        {
            short x = 0;
            short y = 0;
            if (i == 2 ? showPageButton : showArrows)
            {
                func_ov023_021e2bdc(layout_, s_buttonIDs[i], &x, &y);
                if (buttonPressed_[i])
                {
                    x += s_pressedOffsets[i].x;
                    y += s_pressedOffsets[i].y;
                }
                Sprite* sprite = &sprites_[i];
                sprite->x_ = x << 12;
                sprite->y_ = y << 12;
                if (unk_94)
                    func_0205ac40(spriteRenderer_, &sprites_[i]);
            }
        }
    }

    if ((flags_ & 4) && model_ != NULL)
        model_->Draw(true);
}

void MonsterInfoScreen::PlaceModel()
{
    if (monster_ == NULL)
        return;
    MonsterInfo* info = func_02097224(&infos_, monster_->monsterID_);
    if (info == NULL)
        return;

    Vector3fix position;
    position.x = 4096.0f * info->position_[0];
    position.y = 4096.0f * info->position_[1];
    position.z = 4096.0f * info->position_[2];
    Vector3fix rotation;
    rotation.x = 0;
    rotation.y = 4096.0f * info->rotationY_;
    rotation.z = 0;
    Vector3fix scale;
    scale.x = 4096.0f * info->scale_[0];
    scale.y = 4096.0f * info->scale_[1];
    scale.z = 4096.0f * info->scale_[2];
    model_->position_ = position;
    model_->rotation_ = rotation;
    model_->SetScale(&scale);
}

void MonsterInfoScreen::CancelLoading()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (flags_ & 1)
    {
        flags_ &= ~1;
        if (taskID_ >= 0)
        {
            loader->RemoveTask(taskID_);
            taskID_ = -1;
        }
        for (int i = 0; i < 5; i++)
        {
            short taskID = taskIDs_[i];
            if (taskID >= 0)
            {
                BackgroundLoader::GetInstance()->RemoveTask(taskID);
                taskIDs_[i] = -1;
            }
        }
        habitats_.Unload();
        loadStep_ = 0;
    }
    if (flags_ & 0x10)
        return;
    flags_ |= 0x10;
    if (backgroundTaskID_ >= 0)
    {
        loader->RemoveTask(backgroundTaskID_);
        backgroundTaskID_ = -1;
    }
    backgroundStep_ = 0;
}

void MonsterInfoScreen::TogglePage()
{
    if (flags_ & 1)
        return;
    if (flags_ & 8)
        return;
    if (record_ == NULL || !record_->complete_)
        return;
    unsigned char page = page_;
    LoadMonster(monster_, record_, false);
    page_ = page + 1;
    page_ %= 2;
    buttonPressed_[2] = true;
    flags_ |= 8;
}

void MonsterInfoScreen::NextAnimation()
{
    if (model_ == NULL || model_->loadedAnimationPackageList_ == NULL || monster_ == NULL)
        return;
    MonsterInfo* info = func_02097224(&infos_, monster_->monsterID_);
    if (info == NULL)
        return;
    BCFG::AnimationRecord* animation = model_->activeAnimationRecord_;
    if (animation != NULL && strcmp("stand", animation->name) != 0 && strcmp("run", animation->name) != 0)
        return;

    animationIndex_++;
    if (info->numAnimations_ <= animationIndex_)
    {
        animationIndex_ = 0;
        if (info->numAnimations_ > 1)
            animationIndex_ = 1;
    }
    const char* name = info->animations_[animationIndex_];
    if (name == NULL || name[0] == '\0')
        return;
    model_->MaybeSetRegularAnimation(name, 0);
}

// A function here used the string "%s", which is still in the data after "run", but the linker removed the function
// since nothing called it. This stands in for it.
void MonsterInfoScreen_Unused(char* output, const char* text)
{
    sprintf(output, "%s", text);
}

void MonsterInfoScreen::SetMonster(MonsterListEntry* monster, MonsterRecord* record)
{
    if (state_ == State_Setup)
        return;
    if (prevMonster_ != monster_)
    {
        prevMonster_ = monster_;
        prevRecord_ = record_;
        flags_ |= 0x20;
    }
    if (monster == NULL || record == NULL)
    {
        monster_ = monster;
        return;
    }
    if (monster_ == monster || record_ == record)
        return;
    LoadMonster(monster, record, true);
}

void MonsterInfoScreen::LoadMonster(MonsterListEntry* monster, MonsterRecord* record, bool loadModel)
{
    if (state_ == State_Setup)
        return;
    if (monster == NULL || record == NULL)
    {
        monster_ = monster;
        return;
    }

    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (taskID_ >= 0)
    {
        loader->RemoveTask(taskID_);
        taskID_ = -1;
    }
    for (int i = 0; i < 5; i++)
    {
        short taskID = taskIDs_[i];
        if (taskID >= 0)
        {
            BackgroundLoader::GetInstance()->RemoveTask(taskID);
            taskIDs_[i] = -1;
        }
    }
    habitats_.Unload();
    loadStep_ = 0;
    page_ = 0;
    monster_ = monster;
    record_ = record;
    dropNames_[0][0] = '\0';
    dropNames_[1][0] = '\0';
    description_[0] = '\0';
    flags_ |= 1;
    flags_ &= ~8;
    loadModel_ = loadModel;
    if (!monster_->known_)
    {
        flags_ &= ~1;
        flags_ |= 0x10;
        flags_ &= ~4;
        unk_93 = false;
        return;
    }

    flags_ &= ~0x10;
    if (backgroundTaskID_ >= 0)
    {
        loader->RemoveTask(backgroundTaskID_);
        backgroundTaskID_ = -1;
    }
    backgroundStep_ = 0;
    unk_93 = true;
}

void MonsterInfoScreen::UpdateLoading()
{
    if (!(flags_ & 1))
        return;

    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loadStep_ == 0)
    {
        char archive[0x40] = {};
        char file[0x40] = {};
        if (loadModel_)
            taskIDs_[0] = loader->QueueLoadFile("data/prm/mons_info2.nat", NULL);
        allocators_[1].Reset();
        habitats_.Load(&allocators_[1], monster_->number_);
        taskIDs_[1] = loader->QueueLoadFileInGP2("data/prm/itemname.gp2", "itemname_<LG>.nat", NULL);
        sprintf(archive, "data/prm/mon_trv%d.gp2", page_ + 1);
        sprintf(file, "mon_trv%d_<LG>.nat", page_ + 1);
        taskIDs_[2] = loader->QueueLoadFileInGP2(archive, file, NULL);
        taskIDs_[3] = loader->QueueLoadFileInGP2("data/ani/bg_si.gp2", "bg_si_<LG>.pac", NULL);
        if (loadModel_ && monster_ != NULL && record_ != NULL && monster_->known_ && monster_->modelName_ != NULL)
        {
            sprintf(file, "%s.mon", monster_->modelName_);
            taskIDs_[4] = loader->QueueLoadFileInGP2("data/pack_lv5/enemy.gp2", file, NULL);
        }
        loadStep_++;
    }
    else if (loadStep_ == 1)
    {
        if (loadModel_)
        {
            if (loader->GetTaskStatus(taskIDs_[0]))
            {
                void* file;
                unsigned int size;
                loader->GetLoadedFileByID(taskIDs_[0], &file, &size);
                if (file != NULL)
                {
                    short* variant = variants_;
                    best_.Init();
                    SafeAllocator* allocator = &allocators_[0];
                    for (; *variant != 0; variant++)
                    {
                        allocator->Reset();
                        short monsterID = *variant;
                        func_02096fb0(&infos_);
                        func_02097054(&infos_, allocator, file, size, monsterID);
                        MonsterRecordCount* count = func_02097238(&infos_);
                        if (best_.monsterID_ < 0
                            || (count != NULL && (count->value_ > best_.value_ || count->count_ > best_.count_)))
                        {
                            best_.monsterID_ = monsterID;
                            best_.value_ = count->value_;
                            best_.count_ = count->count_;
                        }
                    }
                    allocator->Reset();
                    short monsterID = monster_->monsterID_;
                    func_02096fb0(&infos_);
                    func_02097054(&infos_, allocator, file, size, monsterID);
                    func_02097238(&infos_);
                }
                loader->RemoveTask(taskIDs_[0]);
                taskIDs_[0] = -1;
                loadStep_++;
            }
        }
        else
        {
            loadStep_++;
        }
    }

    if (loadStep_ == 2)
    {
        if (habitats_.Update())
            loadStep_++;
    }

    if (loadStep_ == 3 && loader->GetTaskStatus(taskIDs_[1]))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(taskIDs_[1], &file, &size);
        if (file != NULL)
        {
            MonsterInfo* info = func_02097224(&infos_, monster_->monsterID_);
            if (info != NULL)
            {
                char reader[0xc];
                func_020e526c(reader);
                func_020e56fc(reader, file, size);
                const char** name = func_020e5294(reader, info->dropItemIDs_[0]);
                if (name != NULL)
                {
                    memset(dropNames_[0], 0, 0x48);
                    func_020e4864(*name, dropNames_[0], 1, 0, 0, 0);
                }
                name = func_020e5294(reader, info->dropItemIDs_[1]);
                if (name != NULL)
                {
                    memset(dropNames_[1], 0, 0x48);
                    func_020e4864(*name, dropNames_[1], 1, 0, 0, 0);
                }
            }
        }
        loader->RemoveTask(taskIDs_[1]);
        taskIDs_[1] = -1;
        loadStep_++;
    }

    if (loadStep_ == 4 && loader->GetTaskStatus(taskIDs_[2]))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(taskIDs_[2], &file, &size);
        if (file != NULL)
        {
            char text[0x18];
            func_020dfc2c(text);
            func_020dfc40(text);
            func_020e046c(description_, file, size, monster_->number_);
        }
        loader->RemoveTask(taskIDs_[2]);
        taskIDs_[2] = -1;
        loadStep_++;
    }

    if (loadStep_ == 6)
    {
        if (!(flags_ & 8) && taskIDs_[4] == -1)
        {
            loadStep_ = 0;
            flags_ &= ~9;
        }
        loadStep_++;
    }

    if (loadStep_ == 7)
    {
        if (loadModel_)
        {
            if (loader->GetTaskStatus(taskIDs_[4]))
            {
                flags_ &= ~4;
                loadStep_++;
            }
        }
        else
        {
            loadStep_++;
        }
    }
    else if (loadStep_ == 8)
    {
        if (loadModel_)
        {
            SafeAllocator* allocator = &allocators_[2];
            allocator->Reset();
            void* file;
            unsigned int size;
            loader->GetLoadedFileByID(taskIDs_[4], &file, &size);
            if (file != NULL)
            {
                GameResources* resources = func_ov017_0218b5b0();
                const void* found;
                unsigned int foundSize;
                if (FindFilesInNarcBySubstring(file, ".cchr", &found, &foundSize, 1))
                {
                    unsigned int characterSize;
                    void* character = DecompressLZ77FileIntoAllocatedSpace(*allocator, found, characterSize);
                    if (FindFilesInNarcBySubstring(file, ".cmot", &found, &foundSize, 1))
                    {
                        unsigned int motionSize;
                        void* motion = DecompressLZ77FileIntoAllocatedSpace(*allocator, found, motionSize);
                        const void* actions;
                        unsigned int actionsSize;
                        if (FindFilesInNarcBySubstring(file, ".bact", &actions, &actionsSize, 1))
                        {
                            model_->Initialize();
                            model_->unknown_2_ = monster_->monsterID_;
                            model_->EnableFlag(4);
                            func_0207df50(resources->unknown_2cc);
                            func_0207df90(resources->unknown_2cc);
                            ObjectArchiveLoadInfo loadInfo;
                            func_0203dafc(&loadInfo);
                            loadInfo.fileData = character;
                            loadInfo.allocator = allocator;
                            loadInfo.unk_8 = characterSize;
                            model_->LoadFromCCHROrCMOTArchive(&loadInfo, NULL);
                            func_0207dfac(resources->unknown_2cc);
                            func_0203dafc(&loadInfo);
                            loadInfo.allocator = allocator;
                            loadInfo.fileData = motion;
                            loadInfo.unk_8 = motionSize;
                            model_->LoadFromCCHROrCMOTArchive(&loadInfo, NULL);
                            PlaceModel();
                            animationIndex_ = 0;
                            MonsterInfo* info = func_02097224(&infos_, monster_->monsterID_);
                            if (info != NULL)
                                model_->MaybeSetRegularAnimation(info->animations_[0], 0);
                            flags_ |= 4;
                        }
                    }
                }
            }
            loader->RemoveTask(taskIDs_[4]);
            taskIDs_[4] = -1;
        }
        loadStep_ = 0;
        flags_ &= ~9;
        if (unk_82_3_)
            unk_82_3_ = false;
        unk_94 = unk_93;
        unk_93 = false;
    }
}

void MonsterInfoScreen::Setup()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (initStep_ == 0)
    {
        BG1CNT = (BG1CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | (0x1f << 8);
        flags_ |= 0x10;
        initStep_++;
    }

    if (initStep_ == 1)
    {
        func_ov023_021e20c0(layout_);
        taskID_ = loader->QueueLoadFile("data/ani/lay_sml.lia", NULL);
        initStep_++;
    }

    if (initStep_ == 2 && loader->GetTaskStatus(taskID_))
    {
        void* file;
        unsigned int size;
        loader->GetLoadedFileByID(taskID_, &file, &size);
        if (file != NULL)
        {
            SafeAllocator* allocators = allocators_;
            allocators[3].Reset();
            func_ov023_021e20f0(layout_, &allocators[3], file, size);
            HIDE_ELEMENT(layout_, 1);
        }
        loader->RemoveTask(taskID_);
        taskID_ = -1;
        taskID_ = loader->QueueLoadFile("data/ani/obj_smi.pac", NULL);
        initStep_++;
    }

    if (initStep_ == 3 && loader->GetTaskStatus(taskID_))
    {
        void* name;
        void* file;
        unsigned int size;
        unsigned int cellsSize;
        loader->GetLoadedFileByID(taskID_, &file, &size);
        int numFiles = func_02046900(file);
        allocators_[5].Reset();
        for (int i = 0; i < numFiles; i++)
        {
            void* cells = func_020467f0(file, i, &name, &cellsSize);
            if (cells != NULL)
                func_0205a528(spriteRenderer_, cells, cellsSize, &allocators_[5]);
        }

        short x = 0;
        short y = 0;
        Sprite* sprite;
        HIDE_ELEMENT(layout_, 0x1a);
        func_ov023_021e2bdc(layout_, 0x1a, &x, &y);
        sprite = &sprites_[0];
        sprite->x_ = x << 12;
        sprite->y_ = y << 12;
        sprite->unk_22 = 0x21;
        sprite->unk_26 = 0;
        HIDE_ELEMENT(layout_, 0x1b);
        func_ov023_021e2bdc(layout_, 0x1b, &x, &y);
        sprite = &sprites_[1];
        sprite->x_ = x << 12;
        sprite->y_ = y << 12;
        sprite->unk_22 = 0x22;
        sprite->unk_26 = 0;
        func_ov023_021e2bdc(layout_, 0x14, &x, &y);
        sprite = &sprites_[2];
        sprite->x_ = x << 12;
        sprite->y_ = y << 12;
        sprite->unk_22 = 0x20;
        sprite->unk_26 = 0;
        loader->RemoveTask(taskID_);
        taskID_ = -1;
        initStep_++;
    }

    if (initStep_ == 4)
    {
        BG0CNT = (BG0CNT & ~BGCNT_MASK_PRIORITY);
        BG1CNT = (BG1CNT & ~BGCNT_MASK_PRIORITY) | 1;
        BG2CNT = (BG2CNT & ~BGCNT_MASK_PRIORITY) | 2;
        BG3CNT = (BG3CNT & ~BGCNT_MASK_PRIORITY) | 3;
        DISPCNT = (DISPCNT & ~0x1f00) | (0x13 << 8);
        GameState* gameState = GameState::GetInstance();
        s_statics1.previousCamera = func_020100f8(gameState);
        func_020a2010(camera_);
        func_0202e5c8(camera_, 0, 0, 0);
        func_0202e5d8(camera_, 0, 0, 0xa000);
        func_0202e0a4(camera_);
        func_020a27a0(camera_);
        func_020100c4(gameState, camera_);
        GameResources* resources = func_ov017_0218b5b0();
        func_0203b4d8(resources, 0x6093e);
        func_0203b4e8(resources, 0x20);
        func_020c54a4(0, 0, 0, 0);
        func_020c5588(0, 0, 0x7fff, 0, 0);
        LightingManager::GetInstance()->fogEnabled_ = false;
        state_ = State_Run;
        initStep_ = 0;
    }
}

void MonsterInfoScreen::Run()
{
    UpdateLoading();
}

void MonsterInfoScreen::UpdateBackground()
{
    if (!(flags_ & 0x10))
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (backgroundStep_ != 0)
        return;
    backgroundTaskID_ = loader->QueueLoadFile("data/ani/bg_smitop.pac", NULL);
    backgroundStep_++;
}

// NONMATCHING: the C matches 97.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// In the block of the first drop, the compiler keeps 0xf in r8, which dropNameID doesn't use there, while the original
// loads it again for each call.
#ifdef NONMATCHING
void MonsterInfoScreen::UpdateText()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if ((flags_ & 1) && loadStep_ == 5 && loader->GetTaskStatus(taskIDs_[3]))
    {
        void* name;
        void* file;
        unsigned int size;
        unsigned int dataSize;
        loader->GetLoadedFileByID(taskIDs_[3], &file, &size);
        int numFiles = func_02046900(file);
        if (numFiles != 0)
        {
            void* data = func_020467f0(file, 0, &name, &dataSize);
            if (data != NULL)
            {
                Canvas canvas;
                func_0204c684(&canvas);
                canvas.width_ = 0x20;
                canvas.height_ = 0x18;
                canvas.unk_b4 = 0xa;
                canvas.unk_b6 = 0xb;
                canvas.pixels_ = (char*)data + 0x10;
                func_02097224(&infos_, monster_->monsterID_);

                char dropName0[0x48] = {};
                char dropName1[0x48] = {};
                char description[0x200] = {};
                char dropText0[0x48] = {};
                char dropText1[0x48] = {};
                func_0206819c(dropNames_[0], dropName0, 0);
                func_0206819c(dropNames_[1], dropName1, 0);
                void* font = func_020421a0();
                func_02046608(font, 10, dropName0, dropText0, 0x400, 0, 0);
                func_02046608(font, 10, dropName1, dropText1, 0x400, 0, 0);
                func_02046608(font, 10, description_, description, 0x8c, 0, 0);

                unsigned char page;
                Layout* layout;
                void* texts;
                MonsterRecord* record;
                MonsterListEntry* monster;
                page = page_;
                layout = layout_;
                record = record_;
                texts = texts_;
                monster = monster_;
                if (layout != NULL && monster != NULL && texts != NULL && record != NULL && record->defeatCount_ != 0)
                {
                    func_ov023_021e24b0(layout, 2, monster->number_, 8, 0xf, 1, 3, 0, 1);
                    func_ov023_021e23d0(layout, 3, monster->name_, 10, 0xf);
                    func_ov023_021e23d0(layout, 4, func_020e0434(texts, monster->familyTextID_), 10, 0xf);
                    LayoutElement* element = FindLayoutElement(layout, 4);
                    if (element != NULL)
                        element->flags_ |= LAYOUT_ELEMENT_FLAG_4;

                    if (&best_ != NULL && best_.monsterID_ > 0)
                    {
                        func_ov023_021e24b0(layout, 5, best_.value_, 8, 0xf, 1, 6, 0, 0);
                        func_ov023_021e24b0(layout, 6, best_.count_, 8, 0xf, 1, 6, 0, 0);
                    }
                    func_ov023_021e24b0(layout, 7, record->defeatCount_, 8, 0xf, 1, 6, 0, 0);

                    HIDE_ELEMENT(layout, 8);
                    HIDE_ELEMENT(layout, 0xa);
                    HIDE_ELEMENT(layout, 0xc);
                    HIDE_ELEMENT(layout, 9);
                    HIDE_ELEMENT(layout, 0xb);
                    HIDE_ELEMENT(layout, 0xd);
                    HIDE_ELEMENT(layout, 0x16);
                    HIDE_ELEMENT(layout, 0x14);
                    HIDE_ELEMENT(layout, 0x1a);
                    HIDE_ELEMENT(layout, 0x1b);
                    HIDE_ELEMENT(layout, 0x17);
                    HIDE_ELEMENT(layout, 0x18);
                    HIDE_ELEMENT(layout, 0x19);
                    SHOW_ELEMENT(layout, 0x15);

                    short dropTextID;
                    short dropCountID;
                    short dropNameID;
                    bool shownDrops;
                    shownDrops = false;
                    dropNameID = 8;
                    dropCountID = 0xa;
                    dropTextID = 0xc;
                    if (record->complete_ || record->defeatCount_ != 0)
                    {
                        shownDrops = true;
                        // TODO: the original computes the address of the text first, like this cast does
                        if (*(char*)((int)dropText0) != '\0')
                        {
                            SHOW_ELEMENT(layout, 8);
                            SHOW_ELEMENT(layout, 0xa);
                            SHOW_ELEMENT(layout, 0xc);
                            func_ov023_021e23d0(layout, 8, dropText0, 10, 0xf);
                            func_ov023_021e24b0(layout, 0xa, record->dropCount0_, 8, 0xf, 1, 3, 0, 0);
                            func_ov023_021e23d0(layout, 0xc, func_020e0434(texts, 0xf), 10, 0xf);
                            dropNameID = 9;
                            dropCountID = 0xb;
                            dropTextID = 0xd;
                        }
                    }
                    if (record->dropCount1_ != 0 || record->complete_)
                    {
                        if (*(char*)((int)dropText1) != '\0')
                        {
                            shownDrops = true;
                            SHOW_ELEMENT(layout, dropNameID);
                            SHOW_ELEMENT(layout, dropCountID);
                            SHOW_ELEMENT(layout, dropTextID);
                            func_ov023_021e23d0(layout, dropNameID, dropText1, 10, 0xf);
                            func_ov023_021e24b0(layout, dropCountID, record->dropCount1_, 8, 0xf, 1, 3, 0, 0);
                            func_ov023_021e23d0(layout, dropTextID, func_020e0434(texts, 0xf), 10, 0xf);
                        }
                    }
                    if (!shownDrops)
                    {
                        SHOW_ELEMENT(layout, 0x16);
                        func_ov023_021e23d0(layout, 0x16, func_020e0434(texts, 0xe), 10, 0xf);
                    }

                    func_ov023_021e23d0(layout, 0x13, description, 10, 0xf);
                    if (record->complete_)
                    {
                        HIDE_ELEMENT(layout, 0x14);
                        SHOW_ELEMENT(layout, 0x17);
                        func_ov023_021e23d0(layout, 0x17, func_020e0434(texts, 0x1c), 8, 0xf);
                        SHOW_ELEMENT(layout, 0x18);
                        func_ov023_021e24b0(layout, 0x18, page + 1, 8, 0xf, 0, 1, 0, 0);
                        SHOW_ELEMENT(layout, 0x19);
                        func_ov023_021e24b0(layout, 0x19, 2, 8, 0xf, 0, 1, 0, 0);
                    }

                    HIDE_ELEMENT(layout, 0xe);
                    HIDE_ELEMENT(layout, 0xf);
                    HIDE_ELEMENT(layout, 0x10);
                    int i;
                    short areaID;
                    NatEntry* habitat = habitats_.FindEntry(-1);
                    if (habitat != NULL)
                    {
                        areaID = 0xe;
                        for (i = 0; i < 2; i++)
                        {
                            if (i < habitat->numGroups_)
                            {
                                SHOW_ELEMENT(layout, areaID);
                                NatGroup* area = habitats_.GetGroup(i, habitat);
                                char** areaName = habitats_.GetGroupPointer(i, habitat);
                                if (area->flag_)
                                    func_ov023_021e23d0(layout, areaID, *areaName, 10, 0xf);
                                else
                                    func_ov023_021e23d0(layout, areaID, func_020e0434(texts, 0x15), 10, 0xf);
                                areaID++;
                            }
                        }
                        if (habitat->numGroups_ >= 3 && habitats_.GetGroup(2, habitat)->flag_)
                        {
                            SHOW_ELEMENT(layout, 0x10);
                            func_ov023_021e23d0(layout, 0x10, func_020e0434(texts, 0x10), 10, 0xf);
                        }
                    }
                }

                layout_->SetCanvas(&canvas);
                func_ov023_021e257c(layout_);
                BackgroundGraphics graphics;
                func_0204af64(&graphics);
                func_0204b11c(&graphics, 0);
                graphics.unk_1c_0_ = 0;
                graphics.unk_1c_4_ = 1;
                func_0204b5b4(&graphics, 1);
                func_0204b5e8(&graphics, 0, 0);
                for (int i = 0; i < numFiles; i++)
                {
                    void* data = func_020467f0(file, i, &name, &dataSize);
                    if (data != NULL)
                    {
                        memcpy(buffers_[i], data, dataSize);
                        func_0204b4c0(&graphics, buffers_[i]);
                    }
                }
                flags_ &= ~0x20;
            }
        }
        loader->RemoveTask(taskIDs_[3]);
        taskIDs_[3] = -1;
        loadStep_++;
    }

    if ((flags_ & 0x10) && backgroundStep_ == 1 && loader->GetTaskStatus(backgroundTaskID_))
    {
        void* name;
        void* file;
        unsigned int size;
        unsigned int dataSize;
        loader->GetLoadedFileByID(backgroundTaskID_, &file, &size);
        int numFiles = func_02046900(file);
        BackgroundGraphics graphics;
        func_0204af64(&graphics);
        func_0204b11c(&graphics, 0);
        graphics.unk_1c_0_ = 0;
        graphics.unk_1c_4_ = 1;
        func_0204b5b4(&graphics, 1);
        func_0204b5e8(&graphics, 0, 0);
        for (int i = 0; i < numFiles; i++)
        {
            void* data = func_020467f0(file, i, &name, &dataSize);
            if (data != NULL)
            {
                func_0204b2e0(&graphics, data);
                func_0204b3a0(&graphics, data);
            }
        }
        loader->RemoveTask(backgroundTaskID_);
        backgroundTaskID_ = -1;
        backgroundStep_ = 0;
        flags_ &= ~0x10;
        unk_94 = unk_93;
        unk_93 = false;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN8NatTable15GetGroupPointerEiP8NatEntry(); // NatTable::GetGroupPointer
    void _ZN8NatTable8GetGroupEiP8NatEntry(); // NatTable::GetGroup
    void _ZN8NatTable9FindEntryEi(); // NatTable::FindEntry
    // The compiler's function that zeroes memory, e.g. the arrays initialized with = {}
    void __clear(void* dst, unsigned int size);
}

asm void MonsterInfoScreen::UpdateText()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x480
    mov r10, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r1, [r10, #0x81]
    mov r4, r0
    tst r1, #0x1
    beq @L02186794
    ldrb r1, [r10, #0x7f]
    cmp r1, #0x5
    bne @L02186794
    ldrsh r1, [r10, #0x8c]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02186794
    ldrsh r1, [r10, #0x8c]
    add r2, sp, #0x38
    add r3, sp, #0x34
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x38]
    bl func_02046900
    str r0, [sp, #0x1c]
    cmp r0, #0x0
    beq @L02186774
    ldr r0, [sp, #0x38]
    add r2, sp, #0x3c
    add r3, sp, #0x30
    mov r1, #0x0
    bl func_020467f0
    movs r5, r0
    beq @L02186774
    add r0, sp, #0x3a0
    bl func_0204c684
    add r1, r5, #0x10
    mov r6, #0x20
    add r0, sp, #0x420
    mov r5, #0x18
    strh r6, [r0, #0x28]
    mov r3, #0xa
    strh r5, [r0, #0x2a]
    mov r2, #0xb
    strh r3, [r0, #0x34]
    strh r2, [r0, #0x36]
    str r1, [sp, #0x3a8]
    ldr r1, [r10, #0x48]
    add r0, r10, #0xc
    ldrsh r1, [r1, #0xc]
    bl func_02097224
    add r0, sp, #0x358
    mov r1, #0x48
    bl __clear
    add r0, sp, #0x310
    mov r1, #0x48
    bl __clear
    add r0, sp, #0x110
    mov r1, #0x200
    bl __clear
    add r0, sp, #0xc8
    mov r1, #0x48
    bl __clear
    add r0, sp, #0x80
    mov r1, #0x48
    bl __clear
    ldr r0, [r10, #0x60]
    add r1, sp, #0x358
    mov r2, #0x0
    bl func_0206819c
    ldr r0, [r10, #0x64]
    add r1, sp, #0x310
    mov r2, #0x0
    bl func_0206819c
    bl func_020421a0
    mov r1, #0x400
    str r1, [sp, #0x0]
    mov r1, #0x0
    str r1, [sp, #0x4]
    str r1, [sp, #0x8]
    mov r1, #0xa
    add r2, sp, #0x358
    add r3, sp, #0xc8
    mov r5, r0
    bl func_02046608
    mov r0, #0x400
    str r0, [sp, #0x0]
    mov r0, #0x0
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    mov r0, r5
    mov r1, #0xa
    add r2, sp, #0x310
    add r3, sp, #0x80
    bl func_02046608
    mov r1, #0x8c
    str r1, [sp, #0x0]
    mov r1, #0x0
    str r1, [sp, #0x4]
    str r1, [sp, #0x8]
    ldr r2, [r10, #0x68]
    mov r0, r5
    mov r1, #0xa
    add r3, sp, #0x110
    bl func_02046608
    ldrb r0, [r10, #0x80]
    ldr r5, [r10, #0x58]
    str r0, [sp, #0x18]
    ldr r7, [r10, #0x50]
    ldr r6, [r10, #0x5c]
    ldr r8, [r10, #0x48]
    cmp r5, #0x0
    cmpne r8, #0x0
    cmpne r6, #0x0
    cmpne r7, #0x0
    beq @L021866a4
    ldr r0, [r7, #0x0]
    mov r0, r0, lsl #0x16
    movs r0, r0, lsr #0x16
    beq @L021866a4
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r1, #0x1
    str r1, [sp, #0x4]
    mov r0, #0x3
    str r0, [sp, #0x8]
    mov r0, #0x0
    str r0, [sp, #0xc]
    str r1, [sp, #0x10]
    ldrsh r2, [r8, #0x1a]
    mov r0, r5
    mov r1, #0x2
    mov r3, #0x8
    bl func_ov023_021e24b0
    mov r0, #0xf
    str r0, [sp, #0x0]
    ldr r2, [r8, #0x8]
    mov r0, r5
    mov r1, #0x3
    mov r3, #0xa
    bl func_ov023_021e23d0
    ldrsb r1, [r8, #0x12]
    mov r0, r6
    bl func_020e0434
    mov r2, r0
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, r5
    mov r1, #0x4
    mov r3, #0xa
    bl func_ov023_021e23d0
    mov r0, r5
    mov r1, #0x4
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x10
    strneb r1, [r0, #0x16]
    adds r0, r10, #0x9c
    beq @L02185f80
    ldrsh r0, [r10, #0xa0]
    cmp r0, #0x0
    ble @L02185f80
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, #0x1
    str r0, [sp, #0x4]
    mov r0, #0x6
    str r0, [sp, #0x8]
    mov r0, #0x0
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    ldr r2, [r10, #0x9c]
    mov r0, r5
    mov r1, #0x5
    mov r3, #0x8
    bl func_ov023_021e24b0
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, #0x1
    str r0, [sp, #0x4]
    mov r1, #0x6
    str r1, [sp, #0x8]
    mov r0, #0x0
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    mov r0, r5
    ldrh r2, [r10, #0xa2]
    mov r3, #0x8
    bl func_ov023_021e24b0
@L02185f80:
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, #0x1
    str r0, [sp, #0x4]
    mov r0, #0x6
    str r0, [sp, #0x8]
    mov r0, #0x0
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    ldr r1, [r7, #0x0]
    mov r0, r5
    mov r1, r1, lsl #0x16
    mov r2, r1, lsr #0x16
    mov r1, #0x7
    mov r3, #0x8
    bl func_ov023_021e24b0
    mov r0, r5
    mov r1, #0x8
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0xa
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0xc
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x9
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0xb
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0xd
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x16
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x14
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x1a
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x1b
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x17
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x18
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x19
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x15
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    mov r9, #0x0
    mov r8, #0x8
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    ldr r1, [r7, #0x0]
    mov r11, #0xa
    mov r0, r1, lsl #0x15
    movs r0, r0, lsr #0x1f
    mov r0, #0xc
    str r0, [sp, #0x14]
    bne @L02186178
    mov r0, r1, lsl #0x16
    movs r0, r0, lsr #0x16
    beq @L02186274
@L02186178:
    add r0, sp, #0xc8
    ldrsb r0, [r0, #0x0]
    mov r9, #0x1
    cmp r0, #0x0
    beq @L02186274
    mov r0, r5
    mov r1, #0x8
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0xa
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0xc
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    mov r3, #0xf
    add r2, sp, #0xc8
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    str r3, [sp, #0x0]
    mov r0, r5
    mov r1, #0x8
    mov r3, #0xa
    bl func_ov023_021e23d0
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, #0x1
    str r0, [sp, #0x4]
    mov r0, #0x3
    str r0, [sp, #0x8]
    mov r0, #0x0
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    ldr r2, [r7, #0x0]
    mov r0, r5
    mov r2, r2, lsl #0xe
    mov r1, #0xa
    mov r3, #0x8
    mov r2, r2, lsr #0x19
    bl func_ov023_021e24b0
    mov r0, r6
    mov r1, #0xf
    bl func_020e0434
    mov r2, r0
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, r5
    mov r1, #0xc
    mov r3, #0xa
    bl func_ov023_021e23d0
    mov r0, #0xd
    mov r8, #0x9
    mov r11, #0xb
    str r0, [sp, #0x14]
@L02186274:
    ldr r0, [r7, #0x0]
    mov r1, r0, lsl #0x7
    movs r1, r1, lsr #0x19
    bne @L02186290
    mov r0, r0, lsl #0x15
    movs r0, r0, lsr #0x1f
    beq @L0218637c
@L02186290:
    add r0, sp, #0x80
    ldrsb r0, [r0, #0x0]
    cmp r0, #0x0
    beq @L0218637c
    mov r0, r5
    mov r1, r8
    mov r9, #0x1
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, r11
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    ldr r1, [sp, #0x14]
    mov r0, r5
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    add r2, sp, #0x80
    mov r3, #0xa
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, r5
    mov r1, r8
    bl func_ov023_021e23d0
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, #0x1
    str r0, [sp, #0x4]
    mov r0, #0x3
    str r0, [sp, #0x8]
    mov r0, #0x0
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    ldr r2, [r7, #0x0]
    mov r1, r11
    mov r2, r2, lsl #0x7
    mov r0, r5
    mov r3, #0x8
    mov r2, r2, lsr #0x19
    bl func_ov023_021e24b0
    mov r0, r6
    mov r1, #0xf
    bl func_020e0434
    mov r2, r0
    ldr r1, [sp, #0x14]
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, r5
    mov r3, #0xa
    bl func_ov023_021e23d0
@L0218637c:
    cmp r9, #0x0
    bne @L021863c8
    mov r0, r5
    mov r1, #0x16
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r6
    mov r1, #0xe
    bl func_020e0434
    mov r2, r0
    mov r0, #0xf
    str r0, [sp, #0x0]
    mov r0, r5
    mov r1, #0x16
    mov r3, #0xa
    bl func_ov023_021e23d0
@L021863c8:
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r0, r5
    add r2, sp, #0x110
    mov r1, #0x13
    mov r3, #0xa
    bl func_ov023_021e23d0
    ldr r0, [r7, #0x0]
    mov r0, r0, lsl #0x15
    movs r0, r0, lsr #0x1f
    beq @L021864f8
    mov r0, r5
    mov r1, #0x14
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x17
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r6
    mov r1, #0x1c
    bl func_020e0434
    mov r3, #0xf
    mov r2, r0
    str r3, [sp, #0x0]
    mov r0, r5
    mov r1, #0x17
    mov r3, #0x8
    bl func_ov023_021e23d0
    mov r0, r5
    mov r1, #0x18
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    mov r7, #0x0
    mov r3, #0x8
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, #0xf
    str r0, [sp, #0x0]
    str r7, [sp, #0x4]
    mov r0, #0x1
    str r0, [sp, #0x8]
    str r7, [sp, #0xc]
    ldr r1, [sp, #0x18]
    mov r0, r5
    add r2, r1, #0x1
    mov r1, #0x18
    str r7, [sp, #0x10]
    bl func_ov023_021e24b0
    mov r0, r5
    mov r1, #0x19
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    mov r7, #0x0
    mov r2, #0x2
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, #0xf
    str r0, [sp, #0x0]
    str r7, [sp, #0x4]
    mov r0, #0x1
    str r0, [sp, #0x8]
    str r7, [sp, #0xc]
    mov r0, r5
    mov r1, #0x19
    mov r3, #0x8
    str r7, [sp, #0x10]
    bl func_ov023_021e24b0
@L021864f8:
    mov r0, r5
    mov r1, #0xe
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0xf
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r5
    mov r1, #0x10
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    bicne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    add r0, r10, #0x1c
    mvn r1, #0x0
    bl _ZN8NatTable9FindEntryEi
    movs r9, r0
    beq @L021866a4
    mov r8, #0xe
    mov r7, #0x0
    b @L02186624
@L0218656c:
    ldrh r0, [r9, #0x2]
    mov r0, r0, lsl #0x10
    cmp r7, r0, lsr #0x1c
    bge @L02186620
    mov r0, r5
    mov r1, r8
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    mov r2, r9
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r1, r7
    add r0, r10, #0x1c
    bl _ZN8NatTable8GetGroupEiP8NatEntry
    mov r11, r0
    add r0, r10, #0x1c
    mov r1, r7
    mov r2, r9
    bl _ZN8NatTable15GetGroupPointerEiP8NatEntry
    ldrh r1, [r11, #0x2]
    mov r1, r1, lsl #0x1f
    movs r1, r1, lsr #0x1f
    beq @L021865ec
    mov r1, #0xf
    str r1, [sp, #0x0]
    ldr r2, [r0, #0x0]
    mov r0, r5
    mov r1, r8
    mov r3, #0xa
    bl func_ov023_021e23d0
    b @L02186614
@L021865ec:
    mov r0, r6
    mov r1, #0x15
    bl func_020e0434
    mov r1, #0xf
    str r1, [sp, #0x0]
    mov r2, r0
    mov r0, r5
    mov r1, r8
    mov r3, #0xa
    bl func_ov023_021e23d0
@L02186614:
    add r0, r8, #0x1
    mov r0, r0, lsl #0x10
    mov r8, r0, asr #0x10
@L02186620:
    add r7, r7, #0x1
@L02186624:
    cmp r7, #0x2
    blt @L0218656c
    ldrh r0, [r9, #0x2]
    mov r0, r0, lsl #0x10
    mov r0, r0, lsr #0x1c
    cmp r0, #0x3
    blo @L021866a4
    mov r2, r9
    add r0, r10, #0x1c
    mov r1, #0x2
    bl _ZN8NatTable8GetGroupEiP8NatEntry
    ldrh r0, [r0, #0x2]
    mov r0, r0, lsl #0x1f
    movs r0, r0, lsr #0x1f
    beq @L021866a4
    mov r0, r5
    mov r1, #0x10
    bl FindLayoutElement
    cmp r0, #0x0
    ldrneb r1, [r0, #0x16]
    orrne r1, r1, #0x1
    strneb r1, [r0, #0x16]
    mov r0, r6
    mov r1, #0x10
    bl func_020e0434
    mov r2, r0
    mov r6, #0xf
    mov r0, r5
    mov r1, #0x10
    mov r3, #0xa
    str r6, [sp, #0x0]
    bl func_ov023_021e23d0
@L021866a4:
    ldr r2, [r10, #0x58]
    add r1, sp, #0x3a0
    mov r0, #0x1
    str r1, [r2, #0x4]
    strh r0, [r2, #0x12]
    ldr r0, [r10, #0x58]
    bl func_ov023_021e257c
    add r0, sp, #0x60
    bl func_0204af64
    add r0, sp, #0x60
    mov r1, #0x0
    bl func_0204b11c
    ldrb r2, [sp, #0x7c]
    add r0, sp, #0x60
    mov r1, #0x1
    bic r2, r2, #0xf
    and r2, r2, #0xff
    bic r2, r2, #0xf0
    orr r2, r2, #0x10
    strb r2, [sp, #0x7c]
    bl func_0204b5b4
    mov r1, #0x0
    add r0, sp, #0x60
    mov r2, r1
    bl func_0204b5e8
    mov r8, #0x0
    add r5, sp, #0x60
    add r7, sp, #0x3c
    add r6, sp, #0x30
    b @L0218675c
@L0218671c:
    ldr r0, [sp, #0x38]
    mov r1, r8
    mov r2, r7
    mov r3, r6
    bl func_020467f0
    movs r1, r0
    beq @L02186758
    ldr r0, [r10, #0x0]
    ldr r2, [sp, #0x30]
    ldr r0, [r0, r8, lsl #0x2]
    bl memcpy
    ldr r1, [r10, #0x0]
    mov r0, r5
    ldr r1, [r1, r8, lsl #0x2]
    bl func_0204b4c0
@L02186758:
    add r8, r8, #0x1
@L0218675c:
    ldr r0, [sp, #0x1c]
    cmp r8, r0
    blt @L0218671c
    ldrb r0, [r10, #0x81]
    bic r0, r0, #0x20
    strb r0, [r10, #0x81]
@L02186774:
    ldrsh r1, [r10, #0x8c]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    strh r0, [r10, #0x8c]
    ldrb r0, [r10, #0x7f]
    add r0, r0, #0x1
    strb r0, [r10, #0x7f]
@L02186794:
    ldrb r0, [r10, #0x81]
    tst r0, #0x10
    beq @L021868b0
    ldrb r0, [r10, #0x7e]
    cmp r0, #0x1
    bne @L021868b0
    ldr r1, [r10, #0x70]
    mov r0, r4
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L021868b0
    ldr r1, [r10, #0x70]
    add r2, sp, #0x28
    add r3, sp, #0x24
    mov r0, r4
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x28]
    bl func_02046900
    mov r8, r0
    add r0, sp, #0x40
    bl func_0204af64
    add r0, sp, #0x40
    mov r1, #0x0
    bl func_0204b11c
    ldrb r2, [sp, #0x5c]
    add r0, sp, #0x40
    mov r1, #0x1
    bic r2, r2, #0xf
    and r2, r2, #0xff
    bic r2, r2, #0xf0
    orr r2, r2, #0x10
    strb r2, [sp, #0x5c]
    bl func_0204b5b4
    mov r1, #0x0
    add r0, sp, #0x40
    mov r2, r1
    bl func_0204b5e8
    mov r9, #0x0
    add r11, sp, #0x40
    add r7, sp, #0x2c
    add r6, sp, #0x20
    b @L02186874
@L0218683c:
    ldr r0, [sp, #0x28]
    mov r1, r9
    mov r2, r7
    mov r3, r6
    bl func_020467f0
    movs r5, r0
    beq @L02186870
    mov r0, r11
    mov r1, r5
    bl func_0204b2e0
    mov r0, r11
    mov r1, r5
    bl func_0204b3a0
@L02186870:
    add r9, r9, #0x1
@L02186874:
    cmp r9, r8
    blt @L0218683c
    ldr r1, [r10, #0x70]
    mov r0, r4
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0x70]
    mov r1, #0x0
    strb r1, [r10, #0x7e]
    ldrb r0, [r10, #0x81]
    bic r0, r0, #0x10
    strb r0, [r10, #0x81]
    ldrb r0, [r10, #0x93]
    strb r0, [r10, #0x94]
    strb r1, [r10, #0x93]
@L021868b0:
    add sp, sp, #0x480
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif
