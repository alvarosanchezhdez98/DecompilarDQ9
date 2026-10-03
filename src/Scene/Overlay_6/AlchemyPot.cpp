// The alchemy pot of overlay 6: the 3D scene of the pot with the protagonist (the ingredients' sprites go into it and
// the made item comes out), and the window of the recipe's item with the names of its ingredients on the sub screen

#include "Scene/Overlay_6/AlchemyPot.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "GameState/Party.h"
#include "Graphics/NSBXX/Animation.h"
#include "Graphics/NSBXX/GeometryFifo.h"
#include "Graphics/NSBXX/RenderCommands.h"
#include "Graphics/NSBXX/RenderConfig.h"
#include "Graphics/Vector.h"
#include "Resource/GameResources.h"
#include "System/ColorEffects.h"
#include "System/Graphics.h"
#include <std_library_functions.h>

extern "C"
{
    GameResources* func_0200fb8c(GameState* gameState);
    void* func_0200ff1c(GameState* gameState, unsigned char member);
    void func_020100c4(GameState* gameState, void* camera);
    void* func_020100f8(GameState* gameState);
    Party* func_02010828(GameState* gameState);
    void* func_02012fe4();
    void* func_020100bc(GameState* gameState);
    void func_0202e0a4(void* camera);
    void func_0202e5c8(void* camera, int x, int y, int z);
    void func_0202e5d8(void* camera, int x, int y, int z);
    void func_0202ec84(void* camera, const Vector3fix* position, int* x, int* y);
    void func_0203b4d8(void* resources, int);
    void func_0203b4e8(void* resources, int);
    void* func_0203bd08();
    unsigned int func_0203be40(void* vram);
    void func_020407b4(Object3D* object, int x, int y, int z);
    int func_02046900(void* pac);
    void* func_020467f0(void* pac, int index, void** name, unsigned int* size);
    void func_0204af64(BackgroundGraphics* graphics);
    void func_0204b010(BackgroundGraphics* graphics, int);
    void func_0204b11c(BackgroundGraphics* graphics, int);
    void func_0204b12c(BackgroundGraphics* graphics, SafeAllocator* allocator);
    void func_0204b174(BackgroundGraphics* graphics, void* file, SafeAllocator* allocator, unsigned int size);
    void func_0204b2e0(BackgroundGraphics* graphics, void* file);
    void func_0204b3a0(BackgroundGraphics* graphics, void* file);
    void func_0204b5b4(BackgroundGraphics* graphics, int);
    void func_0204b5e8(BackgroundGraphics* graphics, int, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* buffer, unsigned int size);
    void func_02059f38(Object3D* object, Vector3fix* position);
    void func_0205a198(Sprite* sprite);
    void func_0205a444(SpriteRenderer* renderer);
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ebc0(void* sound, int, int);
    void func_0205ebec(void* sound);
    void func_0205ebfc(void* sound, int, int);
    void func_02075cdc(Unknown_02075cdc* graphics);
    void func_02075db0(Unknown_02075cdc* graphics, int x, int y);
    void func_02076080(Unknown_02075cdc* graphics, SafeAllocator* allocator, void* file, unsigned int size);
    void func_02076988(Unknown_02075cdc* graphics, int width, int height);
    void func_02078484(void* params);
    void func_0207df50(void* state);
    void func_0207df90(void* state);
    void func_0207dfac(void* state);
    void func_0207f7f0(Menu* menu, Canvas* canvases, int numCanvases);
    void func_0207f84c(Menu* menu);
    void func_0207f914(Menu* menu, SafeAllocator* allocator, const char* archive, const char* file);
    int func_0207f9f4(Menu* menu);
    void func_0207fc6c(Menu* menu, int ticks);
    void func_0207fcb8(Menu* menu);
    void func_0207fd44(Menu* menu);
    void func_0207fd88(Menu* menu);
    void func_020a2010(void* camera);
    void func_020a27a0(void* camera);
    void func_020c5414();
    void func_020dbd9c(Unknown_020dbd9c* effect);
    void func_020dbdc0(Unknown_020dbd9c* effect);
    void func_020dbebc(Unknown_020dbd9c* effect);
    void func_020dbf18(Unknown_020dbd9c* effect, const char* file, SafeAllocator* allocator, void* vram, int);
    void func_020dbfa4(Unknown_020dbd9c* effect, void* params);
    int func_020de234(PartEntry* item, int);
    void func_020de848(PartNameTable* names);
    void func_020de980(PartNameTable* names, SafeAllocator* allocator, void* file, unsigned int size, int id);
    PartEntry* func_020dedd0(PartNameTable* names, short id);
    const char* func_020e0434(void* texts, int id);
    void func_020e4864(const char* input, char* output, int, int, int, int);
    const char** func_020e5294(void* reader, short id);
    void Mat4x3_Multiply(const Matrix4x3* a, const Matrix4x3* b, Matrix4x3* out);
    void Vector3fix_Add(const Vector3fix* a, const Vector3fix* b, Vector3fix* out);
    GameResources* func_ov017_0218b5b0();
    void __clear(void* buffer, unsigned long size);
}

extern int data_0210a00c;
extern char data_02108760[];

// The priorities of the backgrounds of the main screen
static const struct BackgroundPriorities
{
    unsigned char priorities_[3];
} sBackgroundPriorities = {{0, 1, 3}};

// The size of the canvas' buffer
extern const unsigned int sCanvasBufferSize = 0x1c0;

// The slots of the equipment that the party members can have ingredients in
static const unsigned char sEquipmentSlots[8] = {0, 1, 5, 6, 7, 8, 9, 10};

// The letter of the protagonist's file for each body size (s224<letter>.chr)
static const struct SizeLetters
{
    char letters_[8];
} sSizeLetters = {" aabbcd"};

// For each number of ingredients, the bone of the pot (pos1, pos2 or pos3) that each of them goes to
static const struct IngredientBones
{
    unsigned char bones_[4][4];
} sIngredientBones = {{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 2, 0}, {0, 0, 1, 2}}};

// The sizes of the allocators of the scene's files
static const unsigned int sAllocatorSizes[6] = {0x800, 0xc00, 0x1200, 0x200, 0x600, 0xa000};

// The matrices of the pot's bones pos1, pos2 and pos3, which the render hook computes
static Matrix4x3* sMatrices[3];
static int sBones[3];

static inline int GetCurrentBone(RenderCommandHandler* handler)
{
    return (handler->flags_ & 0x10) ? handler->currentBoneMatrix_ : -1;
}

// A product of fixed-point numbers, rounded
static inline int Multiply(int a, int b)
{
    return FIX32_MULTIPLY(a, b);
}

// Saves the matrices of the pot's bones when they're computed (a hook of the render commands)
static void SaveBones(RenderCommandHandler* handler)
{
    if (!(handler->flags_ & 0x10))
        return;
    for (int i = 0; i < 3; i++)
    {
        if (sBones[i] == GetCurrentBone(handler) && sMatrices[i] != 0)
        {
            GetCurrentPositionAndDirectionMatrices(sMatrices[i], 0);
            Mat4x3_Multiply(sMatrices[i], RenderConfig::GetInverseViewMatrix(), sMatrices[i]);
        }
    }
}

// Places the camera of the scene
#pragma dont_inline on
static void SetUpCamera(void* camera)
{
    if (camera == 0)
        return;
    func_020a2010(camera);
    func_0202e5c8(camera, 0, -0x1e8f, 0);
    func_0202e5d8(camera, 0, 0x2eb8, 0xa000);
    func_0202e0a4(camera);
    func_020a27a0(camera);
}
#pragma dont_inline reset

// The strings of the file, which the compiler pools in this order. A function is in assembly for now
// (NONMATCHING), which can't reference the compiler's pool, so they're in an array for it
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] =
    "ren_in\0"
    "0\0"
    "1\0"
    "renkin\0"
    "2\0"
    "3\0"
    "ren_out\0"
    "4\0"
    "yorokobi\0"
    "stand\0"
    "data/ani/obj_rri.pac\0"
    "data/ani/bg_tm.pac\0"
    "data/bin/menu/bm_rri.gp2\0"
    "bm_rri\0"
    "data/ani/lay_rb.lia\0"
    "data/chara_sub/s224%c.chr\0"
    "data/chara_sub/s065.chr\0"
    "data/chara_sub/s065a.chr\0"
    "data/effect/ev999992500.chr\0"
    "data/chara_sub/s065b.chr\0"
    "pos1\0"
    "pos2\0"
    "pos3\0"
    "data/effect/ev209300000.chr\0"
    "data/ani/bg_rri_t.pac\0"
    "data/ani/bg_rri_kari.pac\0"
    "data/ani/d_%c%03d.spr";
#define STRING(offset, text) (sStrings + (offset))
#endif

void AlchemyPot::Allocate(SafeAllocator* allocator, void* buffer)
{
    allocators_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator) * 6);
    itemAllocator_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator));
    nextItemAllocator_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator));
    unk_1c4 = (unsigned char*)allocator->Allocate(0x80);
    layout_ = (Layout*)allocator->Allocate(sizeof(Layout));
    backgrounds_ = (BackgroundGraphics*)allocator->Allocate(sizeof(BackgroundGraphics) * 2);
    canvases_ = (Canvas*)allocator->Allocate(sizeof(Canvas));
    menu_ = (Menu*)allocator->Allocate(sizeof(Menu));
    sprites_ = (Sprite*)allocator->Allocate(sizeof(Sprite) * 17);
    itemAllocator_->CreateTypeA(allocator->Allocate(0x258), 0x258);
    nextItemAllocator_->CreateTypeA(allocator->Allocate(0x258), 0x258);
    itemAllocator_->Reset();
    nextItemAllocator_->Reset();
    windowAllocator_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator));
    windowSpriteAllocator_ = (SafeAllocator*)allocator->Allocate(sizeof(SafeAllocator));
    windowAllocator_->CreateTypeA(allocator->Allocate(0x1e00), 0x1e00);
    windowAllocator_->Reset();
    windowSpriteAllocator_->CreateTypeA(allocator->Allocate(0x80), 0x80);
    windowSpriteAllocator_->Reset();
    window_.CreateAllocators(windowAllocator_);
    window_.SetBuffer(buffer);
    for (unsigned char i = 0; i < 6; i++)
    {
        unsigned int size = sAllocatorSizes[i];
        allocators_[i].CreateTypeA(allocator->Allocate(size), size);
        allocators_[i].Reset();
    }
    for (unsigned char j = 0; j < 4; j++)
    {
        ingredientAllocators_[j].CreateTypeA(allocator->Allocate(0x280), 0x280);
        ingredientAllocators_[j].Reset();
    }
    *unk_1c4 = 0;
    layout_->Initialize();
    for (unsigned char k = 0; k < 2; k++)
        func_0204af64(&backgrounds_[k]);
    for (unsigned char l = 0; l < 1; l++)
        func_0204c684(&canvases_[l]);
    func_0207f84c(menu_);
    for (unsigned char m = 0; m < 17; m++)
        func_0205a198(&sprites_[m]);
}

void AlchemyPot::Initialize()
{
    memset(names_, 0, sizeof(names_));
    allocators_ = 0;
    itemAllocator_ = 0;
    nextItemAllocator_ = 0;
    previousCamera_ = 0;
    amounts_ = 0;
    itemNames_ = 0;
    texts_ = 0;
    recipe_ = 0;
    nextRecipe_ = 0;
    unk_1bc = 0;
    record_ = 0;
    unk_1c4 = 0;
    layout_ = 0;
    backgrounds_ = 0;
    canvases_ = 0;
    menu_ = 0;
    item_ = 0;
    nextItem_ = 0;
    sprites_ = 0;
    windowSpriteAllocator_ = 0;
    windowAllocator_ = 0;
    window_.Initialize(-1, 1);
    window_.flags_ |= ITEM_INFO_WINDOW_KEEP_MUSIC | ITEM_INFO_WINDOW_KEEP_BRIGHTNESS;
    func_0205a444(&renderer_);
    protagonist_.Initialize();
    pot_.Initialize();
    lid_.Initialize();
    effect_.Initialize();
    steam_.Initialize();
    memset(unk_594, 0, sizeof(unk_594));
    effectAllocator_.ResetAllocatorPointer();
    for (unsigned char i = 0; i < 4; i++)
    {
        ingredients_[i].Initialize();
        ingredientAllocators_[i].ResetAllocatorPointer();
    }
    task_ = -1;
    backgroundTask_ = -1;
    state_ = 0;
    loadStep_ = 0;
    itemStep_ = 0;
    backgroundStep_ = 0;
    unk_ae0 = 0;
    flags_ = 0;
    numIngredients_ = 0;
    itemId_ = 0;
    itemSprites_ = 0;
    effectMode_ = 0;
    func_020dbd9c(&subEffect_);
    resetBlend_ = 0;
}

void IngredientSprite::Initialize()
{
    func_02075cdc(&graphics_);
    task_ = -1;
    item_ = -1;
    x_ = y_ = 0;
    loading_ = 0;
}

void AlchemyPot::Finish()
{
    window_.Finish();
    ResetIngredients();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    if (backgroundTask_ >= 0)
    {
        loader->RemoveTask(backgroundTask_);
        backgroundTask_ = -1;
    }
    if (effectAllocator_.GetSignedAllocator() != 0)
        effectAllocator_.Destroy();
    SafeAllocator* allocators[7] = {0};
    allocators[0] = itemAllocator_;
    allocators[1] = nextItemAllocator_;
    allocators[2] = itemAllocator_;
    allocators[3] = nextItemAllocator_;
    allocators[4] = windowAllocator_;
    allocators[5] = windowSpriteAllocator_;
    for (unsigned char i = 0; allocators[i] != 0; i++)
    {
        if (allocators[i]->GetSignedAllocator() != 0)
            allocators[i]->Destroy();
    }
    for (unsigned char j = 0; j < 6; j++)
    {
        if (allocators_[j].GetSignedAllocator() != 0)
            allocators_[j].Destroy();
    }
    for (unsigned char k = 0; k < 4; k++)
    {
        if (ingredientAllocators_[k].GetSignedAllocator() != 0)
            ingredientAllocators_[k].Destroy();
    }
    if (previousCamera_ != 0)
    {
        GameState* gameState = GameState::GetInstance();
        func_020100c4(gameState, previousCamera_);
        previousCamera_ = 0;
    }
    if (!(flags_ & ALCHEMY_POT_NO_3D))
    {
        protagonist_.Destroy();
        pot_.Destroy();
        lid_.Destroy();
        effect_.Destroy();
        steam_.Destroy();
    }
    func_020dbebc(&subEffect_);
    Initialize();
}

void AlchemyPot::Update(int ticks)
{
    UpdateBackground();
    Menu* menu = menu_;
    if (menu != 0)
        func_0207fc6c(menu, ticks);
    UpdateIngredients();
    UpdateEffect();
    void (AlchemyPot::*updates[3])() = {&AlchemyPot::UpdateLoad, &AlchemyPot::UpdateLoaded, 0};
    if (updates[state_] != 0)
    {
        (this->*updates[state_])();
        UpdateAnimation();
    }
}

// NONMATCHING: the C matches 94.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The registers of the last loop's ingredient pointer and of the animation time are swapped.
#ifdef NONMATCHING
void AlchemyPot::Draw()
{
    if (window_.inMenu_)
        return;
    if (state_ == 0)
        return;
    Menu* menu = menu_;
    func_0207fcb8(menu);
    func_0207fd44(menu);
    if (flags_ & ALCHEMY_POT_NO_3D)
        return;
    Matrix4x3 matrices[3];
    for (int i = 0; i < 3; i++)
        sMatrices[i] = &matrices[i];
    func_020c5414();
    RenderConfig::SubmitToFifo();
    steam_.MaybeUpdateBonePositions();
    for (int j = 0; j < 3; j++)
        sMatrices[j] = 0;
    Vector3fix positions[3];
    int widths[3];
    int heights[3];
    positions[0].x = matrices[0].translation.x;
    positions[0].y = matrices[0].translation.y;
    positions[0].z = matrices[0].translation.z;
    positions[1].x = matrices[1].translation.x;
    positions[1].y = matrices[1].translation.y;
    positions[1].z = matrices[1].translation.z;
    positions[2].x = matrices[2].translation.x;
    positions[2].y = matrices[2].translation.y;
    positions[2].z = matrices[2].translation.z;
    widths[0] = matrices[0].entries[0];
    widths[1] = matrices[1].entries[0];
    widths[2] = matrices[2].entries[0];
    heights[0] = matrices[0].entries[4];
    heights[1] = matrices[1].entries[4];
    heights[2] = matrices[2].entries[4];
    for (int k = 0; k < 3; k++)
    {
        if (widths[k] < 0x28)
            widths[k] = 0x28;
        if (heights[k] < 0x28)
            heights[k] = 0x28;
    }
    unsigned char count = numIngredients_;
    IngredientBones bones = sIngredientBones;
    void* camera = func_020100bc(GameState::GetInstance());
    if (camera != 0)
    {
        IngredientSprite* ingredient = ingredients_;
        for (unsigned char j = 0; j < 4; j++)
        {
            Vector3fix position = positions[bones.bones_[count][j]];
            position.x = Multiply(position.x, pot_.GetScale().x);
            position.y = Multiply(position.y, pot_.GetScale().y);
            position.z = Multiply(position.z, pot_.GetScale().z);
            Vector3fix screen;
            Vector3fix potPosition = pot_.position_;
            Vector3fix_Add(&position, &potPosition, &screen);
            int x;
            int y;
            func_0202ec84(camera, &screen, &x, &y);
            ingredient->x_ = x - 0x12;
            ingredient->y_ = y - 0xc;
            ingredient++;
        }
    }
    unsigned int vram = func_0203be40(func_0203bd08());
    unsigned short flags = flags_;
    int time = pot_.normalizedAnimationTime_;
    if (((flags & ALCHEMY_POT_ANIMATION_OPEN) || (flags & ALCHEMY_POT_ANIMATION_IN)) && !steam_.HasAnimationStopped())
    {
        unsigned char k;
        IngredientSprite* ingredient = &ingredients_[1];
        for (k = 1; k < 4; k++)
        {
            unsigned char bone = bones.bones_[count][k];
            int offset = k * 4 + 0x20;
            ingredient->graphics_.unk_4c = 0x300;
            ingredient->graphics_.unk_14 = vram + offset * 8;
            ingredient->graphics_.unk_44 = offset / 4;
            func_02076988(&ingredient->graphics_, widths[bone], heights[bone]);
            func_02075db0(&ingredient->graphics_, ingredient->x_, ingredient->y_);
            ingredient++;
        }
    }
    if (flags_ & ALCHEMY_POT_ANIMATION_OUT)
    {
        IngredientSprite* ingredient = &ingredients_[0];
        data_0210a00c = 0;
        if (time > 0x3d7 && ingredient->y_ < 0xc0)
        {
            ingredient->graphics_.unk_4c = 0x300;
            ingredient->graphics_.unk_14 = vram + 0x120;
            ingredient->graphics_.unk_44 = 9;
            func_02076988(&ingredient->graphics_, widths[0], heights[0]);
            func_02075db0(&ingredient->graphics_, ingredient->x_, ingredient->y_);
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN12RenderConfig12SubmitToFifoEv(); // RenderConfig::SubmitToFifo
    void _ZN8Object3D24MaybeUpdateBonePositionsEv(); // Object3D::MaybeUpdateBonePositions
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK8Object3D19HasAnimationStoppedEv(); // Object3D::HasAnimationStopped
    void _ZNK8Object3D8GetScaleEv(); // Object3D::GetScale
}

asm void AlchemyPot::Draw()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x12c
    mov r4, r0
    add r0, r4, #0x1000
    ldrb r0, [r0, #0x27f]
    mov r0, r0, lsl #0x1e
    movs r0, r0, lsr #0x1f
    bne @L02154e40
    ldrb r0, [r4, #0xadc]
    cmp r0, #0x0
    beq @L02154e40
    ldr r5, [r4, #0x1d4]
    mov r0, r5
    bl func_0207fcb8
    mov r0, r5
    bl func_0207fd44
    add r0, r4, #0xa00
    ldrh r0, [r0, #0xe2]
    tst r0, #0x8
    bne @L02154e40
    mov r5, #0x0
    add r2, sp, #0x9c
    ldr r1, =sMatrices
    mov r0, #0x30
    b @L02154ad0
@L02154ac4:
    mla r3, r5, r0, r2
    str r3, [r1, r5, lsl #0x2]
    add r5, r5, #0x1
@L02154ad0:
    cmp r5, #0x3
    blt @L02154ac4
    bl func_020c5414
    bl _ZN12RenderConfig12SubmitToFifoEv
    add r0, r4, #0xe8
    add r0, r0, #0x400
    bl _ZN8Object3D24MaybeUpdateBonePositionsEv
    mov r2, #0x0
    mov r1, r2
    ldr r0, =sMatrices
    b @L02154b04
@L02154afc:
    str r1, [r0, r2, lsl #0x2]
    add r2, r2, #0x1
@L02154b04:
    cmp r2, #0x3
    blt @L02154afc
    ldr r1, [sp, #0xc0]
    ldr r0, [sp, #0xc4]
    ldr r3, [sp, #0xcc]
    ldr r10, [sp, #0xc8]
    ldr r9, [sp, #0xf0]
    ldr r8, [sp, #0xf4]
    ldr r7, [sp, #0xf8]
    ldr r6, [sp, #0x120]
    ldr r5, [sp, #0x124]
    ldr lr, [sp, #0x128]
    ldr r12, [sp, #0x9c]
    ldr r2, [sp, #0xfc]
    ldr r11, [sp, #0xac]
    str r1, [sp, #0x78]
    ldr r1, [sp, #0xdc]
    str r0, [sp, #0x7c]
    ldr r0, [sp, #0x10c]
    str r3, [sp, #0x70]
    str r6, [sp, #0x90]
    str r5, [sp, #0x94]
    str r2, [sp, #0x74]
    mov r3, #0x28
    str r0, [sp, #0x68]
    str r10, [sp, #0x80]
    str r9, [sp, #0x84]
    str r8, [sp, #0x88]
    str r7, [sp, #0x8c]
    str lr, [sp, #0x98]
    str r12, [sp, #0x6c]
    str r11, [sp, #0x60]
    str r1, [sp, #0x64]
    mov r6, #0x0
    add r5, sp, #0x6c
    mov r0, r3
    add r2, sp, #0x60
    b @L02154bb8
@L02154b9c:
    ldr r1, [r5, r6, lsl #0x2]
    cmp r1, #0x28
    ldr r1, [r2, r6, lsl #0x2]
    strlt r3, [r5, r6, lsl #0x2]
    cmp r1, #0x28
    strlt r0, [r2, r6, lsl #0x2]
    add r6, r6, #0x1
@L02154bb8:
    cmp r6, #0x3
    blt @L02154b9c
    add r0, r4, #0x1000
    ldrb r7, [r0, #0x2bb]
    ldr r3, =sIngredientBones
    add r2, sp, #0x50
    mov r1, #0x10
@L02154bd4:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L02154bd4
    bl _ZN9GameState11GetInstanceEv
    bl func_020100bc
    movs r8, r0
    beq @L02154d14
    add r0, r4, #0x94
    add r9, r0, #0x800
    add r0, sp, #0x50
    mov r10, #0x0
    add r5, r4, #0x328
    add r6, r0, r7, lsl #0x2
    add r11, sp, #0x78
    b @L02154d0c
@L02154c14:
    ldrb r1, [r10, r6]
    mov r0, #0xc
    add r3, sp, #0x44
    mla r0, r1, r0, r11
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x20
    add r1, r4, #0x2e4
    bl _ZNK8Object3D8GetScaleEv
    ldr r2, [sp, #0x20]
    ldr r1, [sp, #0x44]
    add r0, sp, #0x14
    smull r3, r2, r1, r2
    adds r3, r3, #0x800
    adc r1, r2, #0x0
    mov r2, r3, lsr #0xc
    orr r2, r2, r1, lsl #0x14
    add r1, r4, #0x2e4
    str r2, [sp, #0x44]
    bl _ZNK8Object3D8GetScaleEv
    ldr r2, [sp, #0x18]
    ldr r1, [sp, #0x48]
    add r0, sp, #0x8
    smull r3, r2, r1, r2
    adds r3, r3, #0x800
    adc r1, r2, #0x0
    mov r2, r3, lsr #0xc
    orr r2, r2, r1, lsl #0x14
    add r1, r4, #0x2e4
    str r2, [sp, #0x48]
    bl _ZNK8Object3D8GetScaleEv
    ldr r1, [sp, #0x10]
    ldr r0, [sp, #0x4c]
    add r3, sp, #0x2c
    smull r2, r1, r0, r1
    mov r0, #0x800
    adds r2, r2, r0
    mov r0, #0x0
    adc r0, r1, r0
    mov r1, r2, lsr #0xc
    orr r1, r1, r0, lsl #0x14
    str r1, [sp, #0x4c]
    ldmia r5, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x44
    mov r1, r3
    add r2, sp, #0x38
    bl Vector3fix_Add
    mov r0, r8
    add r1, sp, #0x38
    add r2, sp, #0x4
    add r3, sp, #0x0
    bl func_0202ec84
    ldr r1, [sp, #0x4]
    add r0, r10, #0x1
    sub r1, r1, #0x12
    strh r1, [r9, #0x76]
    and r10, r0, #0xff
    ldr r0, [sp, #0x0]
    sub r0, r0, #0xc
    strh r0, [r9, #0x78]
    add r9, r9, #0x7c
@L02154d0c:
    cmp r10, #0x4
    blo @L02154c14
@L02154d14:
    bl func_0203bd08
    bl func_0203be40
    add r1, r4, #0xa00
    ldrh r1, [r1, #0xe2]
    mov r5, r0
    ldr r9, [r4, #0x308]
    tst r1, #0x2000
    bne @L02154d3c
    tst r1, #0x80
    beq @L02154dcc
@L02154d3c:
    add r0, r4, #0xe8
    add r0, r0, #0x400
    bl _ZNK8Object3D19HasAnimationStoppedEv
    cmp r0, #0x0
    bne @L02154dcc
    add r0, sp, #0x50
    add r6, r4, #0x910
    mov r8, #0x1
    mov r10, #0x300
    add r7, r0, r7, lsl #0x2
    add r11, sp, #0x6c
    b @L02154dc4
@L02154d6c:
    ldrb r0, [r8, r7]
    mov r1, r8, lsl #0x2
    add r2, r1, #0x20
    mov r1, r2, asr #0x1
    add r1, r2, r1, lsr #0x1e
    mov r3, r1, asr #0x2
    str r10, [r6, #0x4c]
    add r2, r5, r2, lsl #0x3
    str r2, [r6, #0x14]
    add r2, sp, #0x60
    ldr r1, [r11, r0, lsl #0x2]
    ldr r2, [r2, r0, lsl #0x2]
    mov r0, r6
    str r3, [r6, #0x44]
    bl func_02076988
    ldrsh r1, [r6, #0x76]
    ldrsh r2, [r6, #0x78]
    mov r0, r6
    bl func_02075db0
    add r0, r8, #0x1
    add r6, r6, #0x7c
    and r8, r0, #0xff
@L02154dc4:
    cmp r8, #0x4
    blo @L02154d6c
@L02154dcc:
    add r0, r4, #0xa00
    ldrh r0, [r0, #0xe2]
    tst r0, #0x200
    beq @L02154e40
    ldr r1, =0x3d7
    add r0, r4, #0x94
    ldr r2, =data_0210a00c
    mov r3, #0x0
    str r3, [r2, #0x0]
    cmp r9, r1
    add r4, r0, #0x800
    ble @L02154e40
    ldrsh r0, [r4, #0x78]
    cmp r0, #0xc0
    bge @L02154e40
    mov r0, #0x300
    str r0, [r4, #0x4c]
    add r0, r5, #0x120
    str r0, [r4, #0x14]
    mov r3, #0x9
    ldr r1, [sp, #0x6c]
    ldr r2, [sp, #0x60]
    mov r0, r4
    str r3, [r4, #0x44]
    bl func_02076988
    ldrsh r1, [r4, #0x76]
    ldrsh r2, [r4, #0x78]
    mov r0, r4
    bl func_02075db0
@L02154e40:
    add sp, sp, #0x12c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void AlchemyPot::Draw3D()
{
    if (!(flags_ & ALCHEMY_POT_LOADED))
        return;
    if ((flags_ & (ALCHEMY_POT_ITEM_SHOWN | ALCHEMY_POT_NO_3D)) &&
        ((flags_ & ALCHEMY_POT_NO_3D) || (window_.flags_ & ITEM_INFO_WINDOW_CHANGE)))
    {
        if (window_.windowSprites_ != 2)
            return;
        if (!window_.inMenu_)
            return;
    }
    if (window_.windowSprites_ == 2 && window_.inMenu_ && (window_.flags_ & ITEM_INFO_WINDOW_CHANGE))
    {
        data_0210a010.viewportArg = 0x46501313;
        void* camera = camera_;
        BG0CNT = BG0CNT & ~3;
        BG1CNT = (BG1CNT & ~3) | 1;
        BG2CNT = (BG2CNT & ~3) | 2;
        if (camera != 0)
        {
            func_020a2010(camera);
            func_0202e5c8(camera_, 0, -0x1e8f, 0);
            func_0202e5d8(camera_, 0, 0x2bae, 0x9199);
            func_0202e0a4(camera_);
            func_020a27a0(camera_);
        }
        resetBlend_ = 0;
    }
    else
    {
        SetUpCamera(camera_);
    }
    protagonist_.Draw(true);
    pot_.Draw(true);
    lid_.Draw(true);
    effect_.Draw(true);
}

void AlchemyPot::DrawSub()
{
    if (state_ == 0)
        return;
    if (resetBlend_ != 0)
    {
        unsigned int layers = (DISPCNT & 0x1f00) >> 8;
        DISPCNT = (DISPCNT & ~0x1f00) | ((layers | 1) << 8);
        resetBlend_ = 0;
    }
    window_.Draw();
    if (window_.inMenu_)
        return;
    if (menu_ == 0)
        return;
    func_0207fd88(menu_);
}

void AlchemyPot::UpdateAnimation()
{
    GameResources* resources = func_0200fb8c(GameState::GetInstance());
    unsigned short flags = flags_;
    if (flags & ALCHEMY_POT_ANIMATION_OPEN)
    {
        func_0203b4d8(resources, 0x2000);
        steam_.MaybeSetRegularAnimation(STRING(0x0, "ren_in"), 9);
        steam_.EnableFlag(0x1000);
        return;
    }
    if (flags & ALCHEMY_POT_ANIMATION_IN)
    {
        if (animationStep_ == 0)
        {
            func_0205ebc0(data_02108760, 0x7a, 0x7a);
            func_0205ebfc(data_02108760, 0, 0);
            pot_.MaybeSetRegularAnimation(STRING(0x0, "ren_in"), 1);
            effect_.MaybeSetRegularAnimation(STRING(0x7, "0"), 1);
            steam_.MaybeSetRegularAnimation(STRING(0x0, "ren_in"), 9);
            steam_.DisableFlag(0x1000);
        }
        else if (animationStep_ >= 1 && pot_.HasAnimationStopped())
        {
            animationStep_ = 0;
            flags_ &= ~ALCHEMY_POT_ANIMATION_IN;
            effect_.MaybeSetRegularAnimation(STRING(0x9, "1"), 1);
            pot_.MaybeSetRegularAnimation(STRING(0xb, "renkin"), 0);
            steam_.StopCurrentAnimation();
            return;
        }
        animationStep_++;
        return;
    }
    if (flags & ALCHEMY_POT_ANIMATION_WORK)
    {
        if (!pot_.HasAnimationReachedEnd())
            return;
        if (animationStep_ == 0)
        {
            effect_.MaybeSetRegularAnimation(STRING(0x12, "2"), 0);
        }
        else if (animationStep_ == 1)
        {
            effect_.MaybeSetRegularAnimation(STRING(0x14, "3"), 1);
        }
        else if (animationStep_ == 2)
        {
            animationStep_ = 0;
            pot_.StopCurrentAnimation();
            pot_.MaybeSetRegularAnimation(STRING(0x16, "ren_out"), 1);
            effect_.MaybeSetRegularAnimation(STRING(0x1e, "4"), 0);
            steam_.MaybeSetRegularAnimation(STRING(0x16, "ren_out"), 1);
            flags_ &= ~ALCHEMY_POT_ANIMATION_WORK;
            return;
        }
        animationStep_++;
        return;
    }
    if (flags & ALCHEMY_POT_ANIMATION_OUT)
    {
        flags_ = flags | ALCHEMY_POT_ANIMATION_DONE;
        if (!pot_.HasAnimationStopped())
        {
            animationStep_++;
            return;
        }
        func_0203b4e8(resources, 0x2000);
        func_0205ebec(data_02108760);
        animationStep_ = 0;
        pot_.MaybeSetRegularAnimation(STRING(0x20, "yorokobi"), 1);
        effect_.StopCurrentAnimation();
        flags_ &= ~ALCHEMY_POT_ANIMATION_OUT;
        return;
    }
    if (flags & ALCHEMY_POT_ANIMATION_END)
    {
        if (pot_.HasAnimationStopped())
        {
            animationStep_ = 0;
            pot_.MaybeSetRegularAnimation(STRING(0x29, "stand"), 0);
            effect_.StopCurrentAnimation();
            flags_ &= ~ALCHEMY_POT_ANIMATION_END;
            return;
        }
        pot_.MaybeSetRegularAnimation(STRING(0x20, "yorokobi"), 1);
        return;
    }
    animationStep_ = 0;
    pot_.MaybeSetRegularAnimation(STRING(0x29, "stand"), 0);
    effect_.StopCurrentAnimation();
}

void AlchemyPot::SetNo3D()
{
    flags_ |= ALCHEMY_POT_NO_3D;
}

void AlchemyPot::SetIngredients(short* items, unsigned char* amounts)
{
    const char* names[3] = {0};
    for (unsigned char i = 0; i < 3; i++)
    {
        if (itemNames_ != 0)
        {
            const char** name = func_020e5294(itemNames_, items[i]);
            if (name != 0)
            {
                func_020e4864(*name, names_[i], 1, 0, 0, 0);
                names[i] = names_[i];
            }
            window_.SetName(i, names[i], amounts[i], amounts[i], 0);
        }
    }
    window_.SetMultiplier(1);
    DrawNames();
}

void AlchemyPot::OpenWindow()
{
    resetBlend_ = 1;
    data_0210a010.viewportArg = 0xbfff0000;
    BG0CNT = (BG0CNT & ~3) | 2;
    BG1CNT = BG1CNT & ~3;
    BG2CNT = (BG2CNT & ~3) | 1;
    flags_ &= ~ALCHEMY_POT_ITEM_SHOWN;
    window_.SetInMenu(0);
    ResetItem();
}

void AlchemyPot::ResetItem()
{
    if (flags_ & ALCHEMY_POT_LOAD_BACKGROUND)
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    task_ = -1;
    itemStep_ = 0;
    flags_ &= ~ALCHEMY_POT_LOAD_ITEM;
    if (backgroundTask_ >= 0)
    {
        loader->RemoveTask(backgroundTask_);
        backgroundTask_ = -1;
    }
    backgroundTask_ = -1;
    backgroundStep_ = 0;
    recipe_ = 0;
    nextRecipe_ = 0;
    record_ = 0;
    flags_ = (flags_ | ALCHEMY_POT_LOAD_BACKGROUND) & ~ALCHEMY_POT_RECIPE;
}

void AlchemyPot::ShowRecipe(Recipe* recipe, RecipeRecord* record, unsigned char* amounts)
{
    if (recipe == 0 || record == 0)
    {
        if (record_ == record)
            return;
        ResetItem();
        return;
    }
    if (record != 0 && !record->made_)
    {
        ResetItem();
        return;
    }
    if (recipe_ != 0 && recipe_->id_ == recipe->id_)
        return;
    if (nextRecipe_ != 0 && nextRecipe_->id_ == recipe->id_)
        return;
    LoadRecipe(recipe, record, amounts);
}

void AlchemyPot::LoadRecipe(Recipe* recipe, RecipeRecord* record, unsigned char* amounts)
{
    if (recipe == 0 || record == 0)
    {
        ResetItem();
        return;
    }
    if (record != 0 && !record->made_)
    {
        ResetItem();
        return;
    }
    window_.LoadWindowSprites(1);
    itemId_ = 0;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    task_ = -1;
    itemStep_ = 0;
    nextRecipe_ = recipe;
    record_ = record;
    amounts_ = amounts;
    flags_ = (flags_ | ALCHEMY_POT_LOAD_ITEM) & ~ALCHEMY_POT_LOAD_BACKGROUND;
    if (backgroundTask_ >= 0)
    {
        loader->RemoveTask(backgroundTask_);
        backgroundTask_ = -1;
    }
    backgroundTask_ = -1;
    backgroundStep_ = 0;
}

void AlchemyPot::ShowItem(short item, signed char sprites)
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (task_ >= 0)
    {
        loader->RemoveTask(task_);
        task_ = -1;
    }
    task_ = -1;
    itemStep_ = 0;
    flags_ |= ALCHEMY_POT_LOAD_ITEM;
    window_.LoadWindowSprites(2);
    itemId_ = item;
    itemSprites_ = sprites;
    flags_ &= ~ALCHEMY_POT_LOAD_BACKGROUND;
    if (backgroundTask_ >= 0)
    {
        loader->RemoveTask(backgroundTask_);
        backgroundTask_ = -1;
    }
    backgroundTask_ = -1;
    backgroundStep_ = 0;
}

// NONMATCHING: the C matches 93.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The two text IDs are computed before the first func_020e0434 call in the original, and the registers differ.
#ifdef NONMATCHING
void AlchemyPot::UpdateItem()
{
    if (!(flags_ & ALCHEMY_POT_LOAD_ITEM) || window_.state_ == 0)
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    short item = itemId_;
    if (item > 0)
    {
        if (itemStep_ == 0)
        {
            signed char sprites = itemSprites_;
            short file = sprites + 0x26;
            short archive = sprites + 0x64;
            const char* name = func_020e0434(texts_, file);
            task_ = loader->QueueLoadFileInGP2(func_020e0434(texts_, archive), name, 0);
            itemStep_++;
        }
        if (itemStep_ == 1)
        {
            if (loader->GetTaskStatus(task_))
            {
                void* data;
                unsigned int size;
                loader->GetLoadedFileByID(task_, &data, &size);
                nextItemAllocator_->Reset();
                short id = itemId_;
                func_020de848(&partNames_);
                func_020de980(&partNames_, nextItemAllocator_, data, size, id);
                window_.flags_ &= ~ITEM_INFO_WINDOW_QUEST;
                window_.names_ = &partNames_;
                window_.SetInMenu(1);
                loader->RemoveTask(task_);
                nextItem_ = func_020dedd0(&partNames_, id);
                flags_ &= ~ALCHEMY_POT_LOAD_ITEM;
                flags_ |= ALCHEMY_POT_ITEM_SHOWN;
                window_.SetItem(itemId_);
            }
            return;
        }
    }
    else if (item == -1)
    {
        flags_ &= ~ALCHEMY_POT_LOAD_ITEM;
        flags_ |= ALCHEMY_POT_ITEM_SHOWN;
        window_.flags_ &= ~ITEM_INFO_WINDOW_QUEST;
        window_.SetInMenu(1);
        window_.SetItem(itemId_);
        return;
    }
    if (itemStep_ == 0)
    {
        unsigned int kind = nextRecipe_->kind_;
        short file = kind + 0x26;
        short archive = kind + 0x64;
        const char* name = func_020e0434(texts_, file);
        task_ = loader->QueueLoadFileInGP2(func_020e0434(texts_, archive), name, 0);
        itemStep_++;
    }
    else if (itemStep_ == 1)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                nextItemAllocator_->Reset();
                func_020de848(&partNames_);
                func_020de980(&partNames_, nextItemAllocator_, data, size, nextRecipe_->item_);
                nextItem_ = func_020dedd0(&partNames_, nextRecipe_->item_);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            itemStep_ = 3;
        }
    }
    else if (itemStep_ == 3)
    {
        recipe_ = nextRecipe_;
        SafeAllocator* allocator = itemAllocator_;
        itemAllocator_ = nextItemAllocator_;
        nextItemAllocator_ = allocator;
        window_.names_ = &partNames_;
        window_.SetInMenu(1);
        const char* names[3] = {0};
        if (itemNames_ != 0)
        {
            memset(names_, 0, sizeof(names_));
            const char** name = func_020e5294(itemNames_, nextRecipe_->ingredients_[0]);
            if (name != 0)
            {
                func_020e4864(*name, names_[0], 1, 0, 0, 0);
                names[0] = names_[0];
            }
            name = func_020e5294(itemNames_, nextRecipe_->ingredients_[1]);
            if (name != 0)
            {
                func_020e4864(*name, names_[1], 1, 0, 0, 0);
                names[1] = names_[1];
            }
            name = func_020e5294(itemNames_, nextRecipe_->ingredients_[2]);
            if (name != 0)
            {
                func_020e4864(*name, names_[2], 1, 0, 0, 0);
                names[2] = names_[2];
            }
        }
        unsigned char equipped[3] = {0};
        GameState* gameState = GameState::GetInstance();
        Party* party = func_02010828(gameState);
        for (int i = 0; i < party->count_; i++)
        {
            GameObject* member = (GameObject*)func_0200ff1c(gameState, party->members_[i]);
            if (member != 0)
            {
                for (int j = 0; j < 8; j++)
                {
                    PartEntry* equipment = &member->partyData_->equipment_[sEquipmentSlots[j]];
                    if (equipment == 0)
                        continue;
                    int isItem;
                    if (equipment->category_ <= 7)
                        isItem = 1;
                    else
                        isItem = 0;
                    if (isItem)
                    {
                        if (nextRecipe_->ingredients_[0] == equipment->unk_18)
                            equipped[0]++;
                        if (nextRecipe_->ingredients_[1] == equipment->unk_18)
                            equipped[1]++;
                        if (nextRecipe_->ingredients_[2] == equipment->unk_18)
                            equipped[2]++;
                    }
                }
            }
        }
        window_.SetName(0, names[0], nextRecipe_->amount0_, amounts_[0], equipped[0]);
        window_.SetName(1, names[1], nextRecipe_->amount1_, amounts_[1], equipped[1]);
        window_.SetName(2, names[2], nextRecipe_->amount2_, amounts_[2], equipped[2]);
        window_.SetMultiplier(1);
        int known = 0;
        if (record_ != 0 && record_->known_)
            known = 1;
        if (known)
            window_.flags_ &= ~ITEM_INFO_WINDOW_QUEST;
        else
            window_.flags_ |= ITEM_INFO_WINDOW_QUEST;
        window_.SetItem(nextRecipe_->item_);
        item_ = nextItem_;
        nextItem_ = 0;
        itemStep_ = 0;
        flags_ &= ~ALCHEMY_POT_LOAD_ITEM;
        flags_ |= ALCHEMY_POT_ITEM_SHOWN | ALCHEMY_POT_RECIPE;
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN14ItemInfoWindow13SetMultiplierEh(); // ItemInfoWindow::SetMultiplier
    void _ZN14ItemInfoWindow7SetItemEs(); // ItemInfoWindow::SetItem
    void _ZN14ItemInfoWindow7SetNameEiPKchhh(); // ItemInfoWindow::SetName
    void _ZN14ItemInfoWindow9SetInMenuEh(); // ItemInfoWindow::SetInMenu
    void _ZN16BackgroundLoader10RemoveTaskEi(); // BackgroundLoader::RemoveTask
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13GetTaskStatusEi(); // BackgroundLoader::GetTaskStatus
    void _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(); // BackgroundLoader::GetLoadedFileByID
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
}

asm void AlchemyPot::UpdateItem()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x28
    mov r4, r0
    add r0, r4, #0xa00
    ldrh r0, [r0, #0xe2]
    tst r0, #0x2
    addne r0, r4, #0x1000
    ldrneb r0, [r0, #0x25a]
    cmpne r0, #0x0
    beq @L02155e1c
    bl _ZN16BackgroundLoader11GetInstanceEv
    add r3, r4, #0x1200
    ldrsh r1, [r3, #0xb8]
    mov r5, r0
    cmp r1, #0x0
    ble @L02155950
    ldrb r0, [r4, #0xade]
    cmp r0, #0x0
    bne @L02155864
    ldrsb r2, [r3, #0xba]
    ldr r0, [r4, #0x1b0]
    add r1, r2, #0x26
    add r2, r2, #0x64
    mov r1, r1, lsl #0x10
    mov r2, r2, lsl #0x10
    mov r1, r1, asr #0x10
    mov r7, r2, asr #0x10
    bl func_020e0434
    mov r6, r0
    ldr r0, [r4, #0x1b0]
    mov r1, r7
    bl func_020e0434
    mov r1, r0
    mov r0, r5
    mov r2, r6
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r4, #0xad4]
    ldrb r0, [r4, #0xade]
    add r0, r0, #0x1
    strb r0, [r4, #0xade]
@L02155864:
    ldrb r0, [r4, #0xade]
    cmp r0, #0x1
    bne @L021559ac
    ldr r1, [r4, #0xad4]
    mov r0, r5
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02155e1c
    ldr r1, [r4, #0xad4]
    add r2, sp, #0x18
    add r3, sp, #0x14
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [r4, #0x188]
    bl _ZN13SafeAllocator5ResetEv
    add r0, r4, #0x1200
    ldrsh r6, [r0, #0xb8]
    add r1, r4, #0x288
    add r0, r1, #0x1000
    bl func_020de848
    str r6, [sp, #0x0]
    add r0, r4, #0x288
    ldr r1, [r4, #0x188]
    ldr r2, [sp, #0x18]
    ldr r3, [sp, #0x14]
    add r0, r0, #0x1000
    bl func_020de980
    add r0, r4, #0x1200
    ldrh r2, [r0, #0x58]
    add r1, r4, #0x288
    add r1, r1, #0x1000
    bic r2, r2, #0x1000
    strh r2, [r0, #0x58]
    add r0, r4, #0x2e4
    str r1, [r4, #0xb2c]
    add r0, r0, #0x800
    mov r1, #0x1
    bl _ZN14ItemInfoWindow9SetInMenuEh
    ldr r1, [r4, #0xad4]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    add r0, r4, #0x288
    mov r1, r6
    add r0, r0, #0x1000
    bl func_020dedd0
    str r0, [r4, #0x1dc]
    add r1, r4, #0xa00
    ldrh r2, [r1, #0xe2]
    add r0, r4, #0x2e4
    add r0, r0, #0x800
    bic r2, r2, #0x2
    strh r2, [r1, #0xe2]
    ldrh r3, [r1, #0xe2]
    add r2, r4, #0x1200
    orr r3, r3, #0x40
    strh r3, [r1, #0xe2]
    ldrsh r1, [r2, #0xb8]
    bl _ZN14ItemInfoWindow7SetItemEs
    b @L02155e1c
@L02155950:
    mvn r0, #0x0
    cmp r1, r0
    bne @L021559ac
    add r2, r4, #0xa00
    ldrh r1, [r2, #0xe2]
    add r0, r4, #0x2e4
    add r0, r0, #0x800
    bic r1, r1, #0x2
    strh r1, [r2, #0xe2]
    ldrh r5, [r2, #0xe2]
    mov r1, #0x1
    orr r5, r5, #0x40
    strh r5, [r2, #0xe2]
    ldrh r2, [r3, #0x58]
    bic r2, r2, #0x1000
    strh r2, [r3, #0x58]
    bl _ZN14ItemInfoWindow9SetInMenuEh
    add r1, r4, #0x1200
    add r0, r4, #0x2e4
    ldrsh r1, [r1, #0xb8]
    add r0, r0, #0x800
    bl _ZN14ItemInfoWindow7SetItemEs
    b @L02155e1c
@L021559ac:
    ldrb r0, [r4, #0xade]
    cmp r0, #0x0
    bne @L02155a24
    ldr r0, [r4, #0x1b8]
    mov r2, #0x26
    ldr r0, [r0, #0xc]
    mov r3, #0x64
    mov r1, r0, lsl #0x4
    add r0, r2, r1, lsr #0x18
    add r2, r3, r1, lsr #0x18
    mov r1, r0, lsl #0x10
    mov r2, r2, lsl #0x10
    ldr r0, [r4, #0x1b0]
    mov r1, r1, asr #0x10
    mov r7, r2, asr #0x10
    bl func_020e0434
    mov r6, r0
    ldr r0, [r4, #0x1b0]
    mov r1, r7
    bl func_020e0434
    mov r1, r0
    mov r0, r5
    mov r2, r6
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    str r0, [r4, #0xad4]
    ldrb r0, [r4, #0xade]
    add r0, r0, #0x1
    strb r0, [r4, #0xade]
    b @L02155e1c
@L02155a24:
    cmp r0, #0x1
    bne @L02155ad0
    ldr r1, [r4, #0xad4]
    mov r0, r5
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02155e1c
    ldr r1, [r4, #0xad4]
    add r2, sp, #0x10
    add r3, sp, #0xc
    mov r0, r5
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x10]
    cmp r0, #0x0
    beq @L02155ab0
    ldr r0, [r4, #0x188]
    bl _ZN13SafeAllocator5ResetEv
    add r0, r4, #0x288
    add r0, r0, #0x1000
    bl func_020de848
    ldr r1, [r4, #0x1b8]
    add r0, r4, #0x288
    ldrsh r1, [r1, #0x2]
    add r0, r0, #0x1000
    str r1, [sp, #0x0]
    ldr r1, [r4, #0x188]
    ldr r2, [sp, #0x10]
    ldr r3, [sp, #0xc]
    bl func_020de980
    ldr r1, [r4, #0x1b8]
    add r0, r4, #0x288
    add r0, r0, #0x1000
    ldrsh r1, [r1, #0x2]
    bl func_020dedd0
    str r0, [r4, #0x1dc]
@L02155ab0:
    ldr r1, [r4, #0xad4]
    mov r0, r5
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r4, #0xad4]
    mov r0, #0x3
    strb r0, [r4, #0xade]
    b @L02155e1c
@L02155ad0:
    cmp r0, #0x3
    bne @L02155e1c
    ldr r1, [r4, #0x1b8]
    add r0, r4, #0x288
    str r1, [r4, #0x1b4]
    ldr r3, [r4, #0x184]
    ldr r2, [r4, #0x188]
    add r1, r4, #0x2e4
    str r2, [r4, #0x184]
    add r2, r0, #0x1000
    str r3, [r4, #0x188]
    add r0, r1, #0x800
    mov r1, #0x1
    str r2, [r4, #0xb2c]
    bl _ZN14ItemInfoWindow9SetInMenuEh
    add r0, sp, #0x1c
    mov r1, #0xc
    bl __clear
    ldr r0, [r4, #0x1ac]
    cmp r0, #0x0
    beq @L02155be4
    mov r0, r4
    mov r1, #0x0
    mov r2, #0x180
    bl memset
    ldr r1, [r4, #0x1b8]
    ldr r0, [r4, #0x1ac]
    ldrsh r1, [r1, #0x4]
    bl func_020e5294
    cmp r0, #0x0
    beq @L02155b6c
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r0, [r0, #0x0]
    mov r1, r4
    mov r2, #0x1
    bl func_020e4864
    str r4, [sp, #0x1c]
@L02155b6c:
    ldr r1, [r4, #0x1b8]
    ldr r0, [r4, #0x1ac]
    ldrsh r1, [r1, #0x6]
    bl func_020e5294
    cmp r0, #0x0
    beq @L02155ba8
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r0, [r0, #0x0]
    add r1, r4, #0x80
    mov r2, #0x1
    bl func_020e4864
    add r0, r4, #0x80
    str r0, [sp, #0x20]
@L02155ba8:
    ldr r1, [r4, #0x1b8]
    ldr r0, [r4, #0x1ac]
    ldrsh r1, [r1, #0x8]
    bl func_020e5294
    cmp r0, #0x0
    beq @L02155be4
    mov r3, #0x0
    str r3, [sp, #0x0]
    str r3, [sp, #0x4]
    ldr r0, [r0, #0x0]
    add r1, r4, #0x100
    mov r2, #0x1
    bl func_020e4864
    add r0, r4, #0x100
    str r0, [sp, #0x24]
@L02155be4:
    add r0, sp, #0x8
    mov r1, #0x3
    bl __clear
    bl _ZN9GameState11GetInstanceEv
    mov r5, r0
    bl func_02010828
    mov r6, r0
    mov r7, #0x0
    b @L02155ccc
@L02155c08:
    add r0, r6, r7
    ldrb r1, [r0, #0xf78]
    mov r0, r5
    bl func_0200ff1c
    cmp r0, #0x0
    beq @L02155cc8
    mov r12, #0x0
    mov r1, r12
    mov r2, #0x1
    ldr r3, =sEquipmentSlots
    b @L02155cc0
@L02155c34:
    ldr r9, [r0, #0x150]
    ldrb r8, [r3, r12]
    add r9, r9, #0x194
    adds lr, r9, r8, lsl #0x5
    beq @L02155cbc
    ldr r8, [lr, #0x8]
    mov r8, r8, lsl #0x1c
    mov r8, r8, lsr #0x1c
    cmp r8, #0x7
    movls r8, r2
    movhi r8, r1
    cmp r8, #0x0
    beq @L02155cbc
    ldr r9, [r4, #0x1b8]
    ldrsh r8, [lr, #0x18]
    ldrsh r9, [r9, #0x4]
    cmp r9, r8
    ldreqb r8, [sp, #0x8]
    addeq r8, r8, #0x1
    streqb r8, [sp, #0x8]
    ldr r9, [r4, #0x1b8]
    ldrsh r8, [lr, #0x18]
    ldrsh r9, [r9, #0x6]
    cmp r9, r8
    ldreqb r8, [sp, #0x9]
    addeq r8, r8, #0x1
    streqb r8, [sp, #0x9]
    ldr r8, [r4, #0x1b8]
    ldrsh lr, [lr, #0x18]
    ldrsh r8, [r8, #0x8]
    cmp r8, lr
    ldreqb lr, [sp, #0xa]
    addeq lr, lr, #0x1
    streqb lr, [sp, #0xa]
@L02155cbc:
    add r12, r12, #0x1
@L02155cc0:
    cmp r12, #0x8
    blt @L02155c34
@L02155cc8:
    add r7, r7, #0x1
@L02155ccc:
    ldrb r0, [r6, #0xf7c]
    cmp r7, r0
    blt @L02155c08
    ldr r1, [r4, #0x1a8]
    add r0, r4, #0x2e4
    ldrb r2, [r1, #0x0]
    add r0, r0, #0x800
    mov r1, #0x0
    str r2, [sp, #0x0]
    ldrb r2, [sp, #0x8]
    str r2, [sp, #0x4]
    ldr r3, [r4, #0x1b8]
    ldr r2, [sp, #0x1c]
    ldrh r3, [r3, #0xa]
    mov r3, r3, lsl #0x1c
    mov r3, r3, lsr #0x1c
    and r3, r3, #0xff
    bl _ZN14ItemInfoWindow7SetNameEiPKchhh
    ldr r1, [r4, #0x1a8]
    add r0, r4, #0x2e4
    ldrb r2, [r1, #0x1]
    add r0, r0, #0x800
    mov r1, #0x1
    str r2, [sp, #0x0]
    ldrb r2, [sp, #0x9]
    str r2, [sp, #0x4]
    ldr r3, [r4, #0x1b8]
    ldr r2, [sp, #0x20]
    ldrh r3, [r3, #0xa]
    mov r3, r3, lsl #0x18
    mov r3, r3, lsr #0x1c
    and r3, r3, #0xff
    bl _ZN14ItemInfoWindow7SetNameEiPKchhh
    ldr r1, [r4, #0x1a8]
    add r0, r4, #0x2e4
    ldrb r2, [r1, #0x2]
    add r0, r0, #0x800
    mov r1, #0x2
    str r2, [sp, #0x0]
    ldrb r2, [sp, #0xa]
    str r2, [sp, #0x4]
    ldr r3, [r4, #0x1b8]
    ldr r2, [sp, #0x24]
    ldrh r3, [r3, #0xa]
    mov r3, r3, lsl #0x14
    mov r3, r3, lsr #0x1c
    and r3, r3, #0xff
    bl _ZN14ItemInfoWindow7SetNameEiPKchhh
    add r0, r4, #0x2e4
    add r0, r0, #0x800
    mov r1, #0x1
    bl _ZN14ItemInfoWindow13SetMultiplierEh
    ldr r0, [r4, #0x1c0]
    mov r1, #0x0
    cmp r0, #0x0
    beq @L02155dbc
    ldrh r0, [r0, #0x2]
    mov r0, r0, lsl #0x1f
    movs r0, r0, lsr #0x1f
    movne r1, #0x1
@L02155dbc:
    add r0, r4, #0x1200
    cmp r1, #0x0
    ldrneh r1, [r0, #0x58]
    bicne r1, r1, #0x1000
    ldreqh r1, [r0, #0x58]
    orreq r1, r1, #0x1000
    strh r1, [r0, #0x58]
    ldr r1, [r4, #0x1b8]
    add r0, r4, #0x2e4
    ldrsh r1, [r1, #0x2]
    add r0, r0, #0x800
    bl _ZN14ItemInfoWindow7SetItemEs
    ldr r1, [r4, #0x1dc]
    mov r0, #0x0
    str r1, [r4, #0x1d8]
    str r0, [r4, #0x1dc]
    strb r0, [r4, #0xade]
    add r0, r4, #0xa00
    ldrh r1, [r0, #0xe2]
    bic r1, r1, #0x2
    strh r1, [r0, #0xe2]
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x44
    strh r1, [r0, #0xe2]
@L02155e1c:
    add sp, sp, #0x28
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

static inline LayoutElement* FindLayoutElement(Layout* layout, short id)
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

static inline char* GetZoneInfo()
{
    return (char*)func_02012fe4() + 0x1840;
}
// NONMATCHING: the C matches 85.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The loader and several locals are in other registers, and the original computes the models' allocator before
// func_0207df90. The assembly loads sBones from two words of the pool like the original, so the second is written
// as sMatrices - 0xc (the assembler merges equal words).
#ifdef NONMATCHING
#pragma always_inline on
void AlchemyPot::UpdateLoad()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (loadStep_ == 0)
    {
        func_0205a444(&renderer_);
        renderer_.unk_50 = 0;
        renderer_.SetSprites(sprites_, 17);
        task_ = loader->QueueLoadFile(STRING(0x2f, "data/ani/obj_rri.pac"), 0);
        loadStep_++;
    }
    else if (loadStep_ == 1)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* name;
            void* pac;
            unsigned int pacSize;
            loader->GetLoadedFileByID(task_, &pac, &pacSize);
            int count = func_02046900(pac);
            SafeAllocator* allocator = allocators_;
            allocator->Reset();
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(pac, i, &name, &size);
                if (file != 0)
                    func_0205a528(&renderer_, file, size, allocator);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
        }
    }
    else if (loadStep_ == 2)
    {
        BG1CNT = (BG1CNT & 0x43) | 0x1d00;
        BG2CNT = (BG2CNT & 0x43) | 0x1e00;
        BG3CNT = (BG3CNT & 0x43) | 0x1f08;
        SafeAllocator* allocators = allocators_;
        allocators[2].Reset();
        BackgroundPriorities priorities = sBackgroundPriorities;
        for (unsigned char i = 0; i < 2; i++)
        {
            BackgroundGraphics* background = &backgrounds_[i];
            func_0204af64(background);
            background->unk_1c_0_ = 0;
            background->unk_1c_4_ = i + 1;
            func_0204b11c(background, 0);
            func_0204b5b4(background, priorities.priorities_[i]);
            func_0204b12c(background, &allocators[2]);
            func_0204b5e8(background, 0, 0);
        }
        func_0204b010(&backgrounds_[0], 0);
        func_0204b010(&backgrounds_[1], 0);
        SafeAllocator* canvasAllocators = allocators_;
        canvasAllocators[3].Reset();
        for (unsigned char j = 0; j < 1; j++)
        {
            Canvas* canvas = &canvases_[j];
            func_0204c684(canvas);
            func_0204c7a8(canvas, &canvasAllocators[3], canvasBuffer_, sCanvasBufferSize);
            canvas->background_ = backgrounds_;
        }
        task_ = loader->QueueLoadFile(STRING(0x44, "data/ani/bg_tm.pac"), 0);
        loadStep_++;
    }
    else if (loadStep_ == 3)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* name;
            void* pac;
            unsigned int pacSize;
            loader->GetLoadedFileByID(task_, &pac, &pacSize);
            int count = func_02046900(pac);
            SafeAllocator* allocators = allocators_;
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(pac, i, &name, &size);
                if (file != 0)
                    func_0204b174(backgrounds_, file, &allocators[2], size);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
            flags_ |= ALCHEMY_POT_LOAD_BACKGROUND;
        }
    }
    else if (loadStep_ == 4)
    {
        BG0CNT = (BG0CNT & ~3) | 2;
        BG1CNT = BG1CNT & ~3;
        BG2CNT = (BG2CNT & ~3) | 1;
        BG3CNT = (BG3CNT & ~3) | 3;
        SafeAllocator* allocators = allocators_;
        allocators[4].Reset();
        func_0207f84c(menu_);
        func_0207f914(menu_, &allocators[4], STRING(0x57, "data/bin/menu/bm_rri.gp2"), STRING(0x70, "bm_rri"));
        loadStep_++;
    }
    else if (loadStep_ == 5)
    {
        int result = func_0207f9f4(menu_);
        if (result == 0)
            loadStep_++;
        if (result < 0)
            state_ = 2;
    }
    else if (loadStep_ == 6)
    {
        task_ = loader->QueueLoadFile(STRING(0x77, "data/ani/lay_rb.lia"), 0);
        loadStep_++;
    }
    else if (loadStep_ == 7)
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
                layout_->Initialize();
                layout_->Load(&allocators[1], data, size);
                LayoutElement* element = FindLayoutElement(layout_, 1);
                if (element != 0)
                    element->flags_ &= ~LAYOUT_ELEMENT_FLAG_VISIBLE;
            }
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
            if (flags_ & ALCHEMY_POT_NO_3D)
                loadStep_ = 18;
        }
    }
    else if (loadStep_ == 8)
    {
        signed char size = *(int*)(GetZoneInfo() + 0xb3c);
        char path[0x20] = {0};
        if (size < 1)
            size = 1;
        if (size > 6)
            size = 6;
        SizeLetters letters = sSizeLetters;
        sprintf(path, STRING(0x8b, "data/chara_sub/s224%c.chr"), letters.letters_[size]);
        task_ = loader->QueueLoadFile(path, 0);
        loadStep_++;
    }
    else if (loadStep_ == 9)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                GameResources* resources = func_0200fb8c(GameState::GetInstance());
                SafeAllocator* allocator = &resources->allocators_[0];
                allocator->Reset();
                func_0207df50(resources->unknown_2cc);
                func_0207df90(resources->unknown_2cc);
                ObjectArchiveLoadInfo info;
                info.fileData = data;
                info.unk_8 = size;
                info.allocator = allocator;
                info.unk_10 = 1;
                protagonist_.LoadFromCHRArchive(&info);
                protagonist_.MaybeSetBCFGAnimation(0, 0);
                func_0207dfac(resources->unknown_2cc);
                func_020407b4(&protagonist_, -0x3800, -0xb3b, 0x60a3);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
        }
    }
    else if (loadStep_ == 10)
    {
        task_ = loader->QueueLoadFile(STRING(0xa5, "data/chara_sub/s065.chr"), 0);
        loadStep_++;
    }
    else if (loadStep_ == 11)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                GameResources* resources = func_0200fb8c(GameState::GetInstance());
                SafeAllocator* allocator = &resources->allocators_[0];
                func_0207df90(resources->unknown_2cc);
                ObjectArchiveLoadInfo info;
                info.fileData = data;
                info.unk_8 = size;
                info.allocator = allocator;
                info.unk_10 = 1;
                pot_.LoadFromCCHROrCMOTArchive(&info, 0);
                pot_.MaybeSetBCFGAnimation(0, 0);
                func_0207dfac(resources->unknown_2cc);
                pot_.SetScale(0x10a, 0x10a, 0x10a);
                func_020407b4(&pot_, -0x41, -0xaac, 0x61f3);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
        }
    }
    else if (loadStep_ == 12)
    {
        task_ = loader->QueueLoadFile(STRING(0xbd, "data/chara_sub/s065a.chr"), 0);
        loadStep_++;
    }
    else if (loadStep_ == 13)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                GameResources* resources = func_0200fb8c(GameState::GetInstance());
                SafeAllocator* allocator = &resources->allocators_[0];
                func_0207df90(resources->unknown_2cc);
                ObjectArchiveLoadInfo info;
                info.fileData = data;
                info.unk_8 = size;
                info.allocator = allocator;
                info.unk_10 = 1;
                lid_.LoadFromCCHROrCMOTArchive(&info, 0);
                lid_.MaybeSetBCFGAnimation(0, 0);
                func_0207dfac(resources->unknown_2cc);
                lid_.SetScale(0x10a, 0x10a, 0x10a);
                func_02059f38(&lid_, &pot_.position_);
            }
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
        }
    }
    else if (loadStep_ == 14)
    {
        task_ = loader->QueueLoadFile(STRING(0xd6, "data/effect/ev999992500.chr"), 0);
        loadStep_++;
    }
    else if (loadStep_ == 15)
    {
        if (loader->GetTaskStatus(task_))
        {
            GameResources* resources = func_ov017_0218b5b0();
            effectAllocator_.CreateTypeA(resources->allocators_[0].Allocate(0x8000), 0x8000);
            effectAllocator_.Reset();
            func_0207df90(resources->unknown_2cc);
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0 && effectAllocator_.GetSignedAllocator() != 0)
            {
                effect_.Initialize();
                ObjectArchiveLoadInfo info;
                info.fileData = data;
                info.unk_8 = size;
                info.allocator = &effectAllocator_;
                info.unk_10 = 1;
                effect_.LoadFromCHRArchive(&info);
                effect_.SetScale(&pot_.GetScale());
                func_02059f38(&effect_, &pot_.position_);
                effect_.StopCurrentAnimation();
            }
            func_0207dfac(resources->unknown_2cc);
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
        }
    }
    else if (loadStep_ == 16)
    {
        task_ = loader->QueueLoadFile(STRING(0xf2, "data/chara_sub/s065b.chr"), 0);
        loadStep_++;
    }
    else if (loadStep_ == 17)
    {
        if (loader->GetTaskStatus(task_))
        {
            void* data;
            unsigned int size;
            loader->GetLoadedFileByID(task_, &data, &size);
            if (data != 0)
            {
                GameResources* resources = func_0200fb8c(GameState::GetInstance());
                SafeAllocator* allocator = &resources->allocators_[0];
                func_0207df90(resources->unknown_2cc);
                ObjectArchiveLoadInfo info;
                info.fileData = data;
                info.unk_8 = size;
                info.allocator = allocator;
                info.unk_10 = 1;
                Object3D* steam = &steam_;
                steam->LoadFromCCHROrCMOTArchive(&info, 0);
                steam->MaybeSetBCFGAnimation(0, 0);
                func_0207dfac(resources->unknown_2cc);
                steam->SetScale(0x10a, 0x10a, 0x10a);
                func_02059f38(steam, &pot_.position_);
                steam->StopCurrentAnimation();
                steam->MaybeSetRegularAnimation(STRING(0x0, "ren_in"), 9);
                steam->DisableFlag(0x1000);
                for (int i = 0; i < 3; i++)
                    sBones[i] = -1;
                Model3D* model = steam_.pModel_;
                if (model != 0)
                {
                    sBones[0] = model->GetBoneIndex(STRING(0x10b, "pos1"));
                    sBones[1] = model->GetBoneIndex(STRING(0x110, "pos2"));
                    sBones[2] = model->GetBoneIndex(STRING(0x115, "pos3"));
                    if (!model->unknown_flags_a8_0_)
                        model = 0;
                    if (model != 0)
                        SetModelRenderContextRenderCommandHook(&model->renderContext_, SaveBones, 0, 6, 3);
                }
            }
            loader->RemoveTask(task_);
            task_ = -1;
            loadStep_++;
        }
    }
    else if (loadStep_ == 18)
    {
        pot_.StopCurrentAnimation();
        lid_.StopCurrentAnimation();
        pot_.MaybeSetBCFGAnimation(0, 0);
        lid_.MaybeSetBCFGAnimation(0, 0);
        GameState* gameState = GameState::GetInstance();
        previousCamera_ = func_020100f8(gameState);
        SetUpCamera(camera_);
        func_020100c4(gameState, camera_);
        menu_->SetBackgrounds(backgrounds_);
        func_0207f7f0(menu_, canvases_, 1);
        menu_->unk_3a = 1;
        DISPCNT = (DISPCNT & ~0x1f00) | 0x1f00;
        ColorEffect_ConfigureAlphaBlend(0x04000050, 4, 1, 10, 6);
        flags_ |= ALCHEMY_POT_LOADED;
        flags_ &= ~ALCHEMY_POT_ITEM_SHOWN;
        func_020dbf18(&subEffect_, STRING(0x11a, "data/effect/ev209300000.chr"), &allocators_[5],
                      func_0200fb8c(gameState)->unknown_2cc, 0x18);
        loadStep_++;
    }
    else if (loadStep_ == 19)
    {
        if (subEffect_.state_ == 2)
        {
            state_ = 1;
            loadStep_ = 0;
        }
    }
}
#pragma always_inline reset
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(); // BackgroundLoader::QueueLoadFile
    void _ZN6Layout10InitializeEv(); // Layout::Initialize
    void _ZN6Layout4LoadEP13SafeAllocatorPvj(); // Layout::Load
    void _ZN7Model3D12GetBoneIndexEPKc(); // Model3D::GetBoneIndex
    void _ZN8Object3D10InitializeEv(); // Object3D::Initialize
    void _ZN8Object3D11DisableFlagEi(); // Object3D::DisableFlag
    void _ZN8Object3D18LoadFromCHRArchiveEP21ObjectArchiveLoadInfo(); // Object3D::LoadFromCHRArchive
    void _ZN8Object3D20StopCurrentAnimationEv(); // Object3D::StopCurrentAnimation
    void _ZN8Object3D21MaybeSetBCFGAnimationEii(); // Object3D::MaybeSetBCFGAnimation
    void _ZN8Object3D24MaybeSetRegularAnimationEPKci(); // Object3D::MaybeSetRegularAnimation
    void _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE(); // Object3D::LoadFromCCHROrCMOTArchive
    void _ZN8Object3D8SetScaleEPK8Vector3i(); // Object3D::SetScale
    void _ZN8Object3D8SetScaleEiii(); // Object3D::SetScale
    void _ZNK13SafeAllocator18GetSignedAllocatorEv(); // SafeAllocator::GetSignedAllocator
}

asm void AlchemyPot::UpdateLoad()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x12c
    mov r10, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    ldrb r1, [r10, #0xadd]
    mov r7, r0
    cmp r1, #0x0
    bne @L02155e8c
    add r0, r10, #0x1e4
    bl func_0205a444
    mov r2, #0x0
    strb r2, [r10, #0x234]
    ldr r0, [r10, #0x1e0]
    add r3, r10, #0x200
    str r0, [r10, #0x224]
    mov r4, #0x11
    ldr r1, =sStrings+0x2f
    mov r0, r7
    strh r4, [r3, #0x30]
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L02155e8c:
    cmp r1, #0x1
    bne @L02155f3c
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    ldr r1, [r10, #0xad4]
    add r2, sp, #0x58
    add r3, sp, #0x54
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x58]
    bl func_02046900
    ldr r8, [r10, #0x180]
    mov r6, r0
    mov r0, r8
    bl _ZN13SafeAllocator5ResetEv
    mov r9, #0x0
    add r5, sp, #0x5c
    add r4, sp, #0x50
    b @L02155f10
@L02155ee0:
    ldr r0, [sp, #0x58]
    mov r1, r9
    mov r2, r5
    mov r3, r4
    bl func_020467f0
    movs r1, r0
    beq @L02155f0c
    ldr r2, [sp, #0x50]
    mov r3, r8
    add r0, r10, #0x1e4
    bl func_0205a528
@L02155f0c:
    add r9, r9, #0x1
@L02155f10:
    cmp r9, r6
    blt @L02155ee0
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L02155f3c:
    cmp r1, #0x2
    bne @L021560c8
    ldr r1, =0x400000a
    ldrh r0, [r1, #0x0]
    and r0, r0, #0x43
    orr r0, r0, #0x1d00
    strh r0, [r1, #0x0]
    ldrh r0, [r1, #0x2]
    and r0, r0, #0x43
    orr r0, r0, #0x1e00
    strh r0, [r1, #0x2]
    ldrh r0, [r1, #0x4]
    and r0, r0, #0x43
    orr r0, r0, #0x308
    orr r0, r0, #0x1c00
    strh r0, [r1, #0x4]
    ldr r6, [r10, #0x180]
    add r0, r6, #0x28
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, =sBackgroundPriorities
    mov r8, #0x0
    ldrb r2, [r0, #0x0]
    ldrb r1, [r0, #0x1]
    ldrb r0, [r0, #0x2]
    add r5, sp, #0x4c
    strb r2, [sp, #0x4c]
    strb r1, [sp, #0x4d]
    strb r0, [sp, #0x4e]
    mov r4, r8
    mov r11, r8
    b @L02156028
@L02155fb8:
    ldr r0, [r10, #0x1cc]
    add r9, r0, r8, lsl #0x5
    mov r0, r9
    bl func_0204af64
    ldrb r1, [r9, #0x1c]
    add r0, r8, #0x1
    and r0, r0, #0xff
    bic r2, r1, #0xf
    and r1, r2, #0xff
    bic r1, r1, #0xf0
    mov r0, r0, lsl #0x1c
    orr r2, r1, r0, lsr #0x18
    mov r0, r9
    mov r1, r4
    strb r2, [r9, #0x1c]
    bl func_0204b11c
    ldrb r1, [r5, r8]
    mov r0, r9
    bl func_0204b5b4
    mov r0, r9
    add r1, r6, #0x28
    bl func_0204b12c
    mov r0, r9
    mov r1, r11
    mov r2, r11
    bl func_0204b5e8
    add r0, r8, #0x1
    and r8, r0, #0xff
@L02156028:
    cmp r8, #0x2
    blo @L02155fb8
    ldr r0, [r10, #0x1cc]
    mov r1, #0x0
    bl func_0204b010
    ldr r0, [r10, #0x1cc]
    mov r1, #0x0
    add r0, r0, #0x20
    bl func_0204b010
    ldr r5, [r10, #0x180]
    add r0, r5, #0x3c
    bl _ZN13SafeAllocator5ResetEv
    mov r6, #0x0
    mov r4, #0x1c0
    mov r9, #0xe0
    b @L0215609c
@L02156068:
    ldr r0, [r10, #0x1d0]
    mla r8, r6, r9, r0
    mov r0, r8
    bl func_0204c684
    ldr r2, [r10, #0x1a4]
    mov r0, r8
    mov r3, r4
    add r1, r5, #0x3c
    bl func_0204c7a8
    ldr r1, [r10, #0x1cc]
    add r0, r6, #0x1
    str r1, [r8, #0x4]
    and r6, r0, #0xff
@L0215609c:
    cmp r6, #0x1
    blo @L02156068
    ldr r1, =sStrings+0x44
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021560c8:
    cmp r1, #0x3
    bne @L02156180
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    ldr r1, [r10, #0xad4]
    add r2, sp, #0x44
    add r3, sp, #0x40
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x44]
    bl func_02046900
    mov r8, r0
    ldr r6, [r10, #0x180]
    mov r9, #0x0
    add r5, sp, #0x48
    add r4, sp, #0x3c
    b @L02156144
@L02156114:
    ldr r0, [sp, #0x44]
    mov r1, r9
    mov r2, r5
    mov r3, r4
    bl func_020467f0
    movs r1, r0
    beq @L02156140
    ldr r0, [r10, #0x1cc]
    ldr r3, [sp, #0x3c]
    add r2, r6, #0x28
    bl func_0204b174
@L02156140:
    add r9, r9, #0x1
@L02156144:
    cmp r9, r8
    blt @L02156114
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r1, [r10, #0xadd]
    add r0, r10, #0xa00
    add r1, r1, #0x1
    strb r1, [r10, #0xadd]
    ldrh r1, [r0, #0xe2]
    orr r1, r1, #0x1
    strh r1, [r0, #0xe2]
    b @L02156b0c
@L02156180:
    cmp r1, #0x4
    bne @L02156200
    ldr r1, =0x4000008
    ldrh r0, [r1, #0x0]
    bic r0, r0, #0x3
    orr r0, r0, #0x2
    strh r0, [r1, #0x0]
    ldrh r0, [r1, #0x2]
    bic r0, r0, #0x3
    strh r0, [r1, #0x2]
    ldrh r0, [r1, #0x4]
    bic r0, r0, #0x3
    orr r0, r0, #0x1
    strh r0, [r1, #0x4]
    ldrh r0, [r1, #0x6]
    bic r0, r0, #0x3
    orr r0, r0, #0x3
    strh r0, [r1, #0x6]
    ldr r4, [r10, #0x180]
    add r0, r4, #0x50
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r10, #0x1d4]
    bl func_0207f84c
    ldr r0, [r10, #0x1d4]
    ldr r2, =sStrings+0x57
    ldr r3, =sStrings+0x70
    add r1, r4, #0x50
    bl func_0207f914
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L02156200:
    cmp r1, #0x5
    bne @L02156230
    ldr r0, [r10, #0x1d4]
    bl func_0207f9f4
    cmp r0, #0x0
    ldreqb r1, [r10, #0xadd]
    addeq r1, r1, #0x1
    streqb r1, [r10, #0xadd]
    cmp r0, #0x0
    movlt r0, #0x2
    strltb r0, [r10, #0xadc]
    b @L02156b0c
@L02156230:
    cmp r1, #0x6
    bne @L02156258
    ldr r1, =sStrings+0x77
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L02156258:
    cmp r1, #0x7
    bne @L0215635c
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    ldr r1, [r10, #0xad4]
    add r2, sp, #0x38
    add r3, sp, #0x34
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x38]
    cmp r0, #0x0
    beq @L02156324
    ldr r4, [r10, #0x180]
    add r0, r4, #0x14
    bl _ZN13SafeAllocator5ResetEv
    ldr r0, [r10, #0x1c8]
    bl _ZN6Layout10InitializeEv
    ldr r0, [r10, #0x1c8]
    ldr r2, [sp, #0x38]
    ldr r3, [sp, #0x34]
    add r1, r4, #0x14
    bl _ZN6Layout4LoadEP13SafeAllocatorPvj
    ldr r0, [r10, #0x1c8]
    ldr r3, [r0, #0x8]
    cmp r3, #0x0
    moveq r2, #0x0
    beq @L02156314
    ldrh r4, [r0, #0x14]
    cmp r4, #0x0
    moveq r2, #0x0
    beq @L02156314
    mov r5, #0x0
    mov r1, #0x18
    b @L02156308
@L021562e8:
    mul r2, r5, r1
    ldrsh r0, [r3, r2]
    add r2, r3, r2
    cmp r0, #0x1
    beq @L02156314
    add r0, r5, #0x1
    mov r0, r0, lsl #0x10
    mov r5, r0, lsr #0x10
@L02156308:
    cmp r5, r4
    blo @L021562e8
    mov r2, #0x0
@L02156314:
    cmp r2, #0x0
    ldrneb r0, [r2, #0x16]
    bicne r0, r0, #0x1
    strneb r0, [r2, #0x16]
@L02156324:
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r1, [r10, #0xadd]
    add r0, r10, #0xa00
    add r1, r1, #0x1
    strb r1, [r10, #0xadd]
    ldrh r0, [r0, #0xe2]
    tst r0, #0x8
    movne r0, #0x12
    strneb r0, [r10, #0xadd]
    b @L02156b0c
@L0215635c:
    cmp r1, #0x8
    bne @L021563e8
    bl func_02012fe4
    add r0, r0, #0x1840
    ldr r1, [r0, #0xb3c]
    add r0, sp, #0x10c
    mov r1, r1, lsl #0x18
    mov r4, r1, asr #0x18
    mov r1, #0x20
    bl __clear
    cmp r4, #0x1
    movlt r4, #0x1
    cmp r4, #0x6
    ldr r3, =sSizeLetters
    movgt r4, #0x6
    add r2, sp, #0x2c
    mov r1, #0x8
@L021563a0:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021563a0
    add r1, sp, #0x2c
    ldrsb r2, [r1, r4]
    ldr r1, =sStrings+0x8b
    add r0, sp, #0x10c
    bl sprintf
    add r1, sp, #0x10c
    mov r0, r7
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021563e8:
    cmp r1, #0x9
    bne @L021564c4
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    ldr r1, [r10, #0xad4]
    add r2, sp, #0x28
    add r3, sp, #0x24
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x28]
    cmp r0, #0x0
    beq @L021564a0
    bl _ZN9GameState11GetInstanceEv
    bl func_0200fb8c
    mov r4, r0
    add r5, r4, #0x38
    mov r0, r5
    bl _ZN13SafeAllocator5ResetEv
    add r0, r4, #0x2cc
    bl func_0207df50
    add r0, r4, #0x2cc
    bl func_0207df90
    ldr r0, [sp, #0x24]
    ldr r1, [sp, #0x28]
    str r0, [sp, #0xf4]
    mov r0, #0x1
    str r1, [sp, #0xf0]
    str r0, [sp, #0xfc]
    add r0, r10, #0x238
    add r1, sp, #0xec
    str r5, [sp, #0xf8]
    bl _ZN8Object3D18LoadFromCHRArchiveEP21ObjectArchiveLoadInfo
    mov r1, #0x0
    add r0, r10, #0x238
    mov r2, r1
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    add r0, r4, #0x2cc
    bl func_0207dfac
    mov r1, #0x3800
    ldr r2, =0xfffff4c5
    ldr r3, =0x60a3
    add r0, r10, #0x238
    rsb r1, r1, #0x0
    bl func_020407b4
@L021564a0:
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021564c4:
    cmp r1, #0xa
    bne @L021564ec
    ldr r1, =sStrings+0xa5
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021564ec:
    cmp r1, #0xb
    bne @L021565cc
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    ldr r1, [r10, #0xad4]
    add r2, sp, #0x20
    add r3, sp, #0x1c
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x20]
    cmp r0, #0x0
    beq @L021565a8
    bl _ZN9GameState11GetInstanceEv
    bl func_0200fb8c
    mov r4, r0
    add r0, r4, #0x2cc
    add r5, r4, #0x38
    bl func_0207df90
    ldr r0, [sp, #0x1c]
    ldr r1, [sp, #0x20]
    str r0, [sp, #0xd4]
    mov r0, #0x1
    str r1, [sp, #0xd0]
    str r0, [sp, #0xdc]
    add r0, r10, #0x2e4
    add r1, sp, #0xcc
    mov r2, #0x0
    str r5, [sp, #0xd8]
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    mov r1, #0x0
    add r0, r10, #0x2e4
    mov r2, r1
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    add r0, r4, #0x2cc
    bl func_0207dfac
    ldr r1, =0x10a
    add r0, r10, #0x2e4
    mov r2, r1
    mov r3, r1
    bl _ZN8Object3D8SetScaleEiii
    ldr r2, =0xfffff554
    ldr r3, =0x61f3
    add r0, r10, #0x2e4
    mvn r1, #0x40
    bl func_020407b4
@L021565a8:
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021565cc:
    cmp r1, #0xc
    bne @L021565f4
    ldr r1, =sStrings+0xbd
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021565f4:
    cmp r1, #0xd
    bne @L021566cc
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    ldr r1, [r10, #0xad4]
    add r2, sp, #0x18
    add r3, sp, #0x14
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x18]
    cmp r0, #0x0
    beq @L021566a8
    bl _ZN9GameState11GetInstanceEv
    bl func_0200fb8c
    mov r4, r0
    add r0, r4, #0x2cc
    add r5, r4, #0x38
    bl func_0207df90
    ldr r0, [sp, #0x14]
    ldr r1, [sp, #0x18]
    str r0, [sp, #0xb4]
    mov r0, #0x1
    str r1, [sp, #0xb0]
    str r0, [sp, #0xbc]
    add r0, r10, #0x390
    add r1, sp, #0xac
    mov r2, #0x0
    str r5, [sp, #0xb8]
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    mov r1, #0x0
    add r0, r10, #0x390
    mov r2, r1
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    add r0, r4, #0x2cc
    bl func_0207dfac
    ldr r1, =0x10a
    add r0, r10, #0x390
    mov r2, r1
    mov r3, r1
    bl _ZN8Object3D8SetScaleEiii
    add r0, r10, #0x390
    add r1, r10, #0x328
    bl func_02059f38
@L021566a8:
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021566cc:
    cmp r1, #0xe
    bne @L021566f4
    ldr r1, =sStrings+0xd6
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021566f4:
    cmp r1, #0xf
    bne @L02156810
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    bl func_ov017_0218b5b0
    mov r4, r0
    add r0, r4, #0x38
    mov r1, #0x8000
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, r0
    add r0, r10, #0x18c
    mov r2, #0x8000
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, r10, #0x18c
    bl _ZN13SafeAllocator5ResetEv
    add r0, r4, #0x2cc
    bl func_0207df90
    ldr r1, [r10, #0xad4]
    mov r0, r7
    add r2, sp, #0x10
    add r3, sp, #0xc
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x10]
    cmp r0, #0x0
    beq @L021567e4
    add r0, r10, #0x18c
    bl _ZNK13SafeAllocator18GetSignedAllocatorEv
    cmp r0, #0x0
    beq @L021567e4
    add r0, r10, #0x3c
    add r0, r0, #0x400
    bl _ZN8Object3D10InitializeEv
    add r0, r10, #0x3c
    ldr r6, [sp, #0x10]
    ldr r5, [sp, #0xc]
    add r3, r10, #0x18c
    mov r2, #0x1
    add r1, sp, #0x8c
    add r0, r0, #0x400
    str r6, [sp, #0x90]
    str r5, [sp, #0x94]
    str r3, [sp, #0x98]
    str r2, [sp, #0x9c]
    bl _ZN8Object3D18LoadFromCHRArchiveEP21ObjectArchiveLoadInfo
    add r0, sp, #0x60
    add r1, r10, #0x2e4
    bl _ZNK8Object3D8GetScaleEv
    add r0, r10, #0x3c
    add r1, sp, #0x60
    add r0, r0, #0x400
    bl _ZN8Object3D8SetScaleEPK8Vector3i
    add r0, r10, #0x3c
    add r0, r0, #0x400
    add r1, r10, #0x328
    bl func_02059f38
    add r0, r10, #0x3c
    add r0, r0, #0x400
    bl _ZN8Object3D20StopCurrentAnimationEv
@L021567e4:
    add r0, r4, #0x2cc
    bl func_0207dfac
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L02156810:
    cmp r1, #0x10
    bne @L02156838
    ldr r1, =sStrings+0xf2
    mov r2, #0x0
    bl _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L02156838:
    cmp r1, #0x11
    bne @L021569d4
    ldr r1, [r10, #0xad4]
    bl _ZN16BackgroundLoader13GetTaskStatusEi
    cmp r0, #0x0
    beq @L02156b0c
    ldr r1, [r10, #0xad4]
    add r2, sp, #0x8
    add r3, sp, #0x4
    mov r0, r7
    bl _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj
    ldr r0, [sp, #0x8]
    cmp r0, #0x0
    beq @L021569b0
    bl _ZN9GameState11GetInstanceEv
    bl func_0200fb8c
    mov r5, r0
    add r0, r5, #0x2cc
    add r4, r5, #0x38
    bl func_0207df90
    ldr r0, [sp, #0x4]
    ldr r1, [sp, #0x8]
    str r4, [sp, #0x78]
    str r0, [sp, #0x74]
    mov r0, #0x1
    str r1, [sp, #0x70]
    add r4, r10, #0xe8
    str r0, [sp, #0x7c]
    add r0, r4, #0x400
    add r1, sp, #0x6c
    mov r2, #0x0
    bl _ZN8Object3D25LoadFromCCHROrCMOTArchiveEP21ObjectArchiveLoadInfoPFiPN4BCFG15AnimationRecordEE
    mov r1, #0x0
    add r0, r4, #0x400
    mov r2, r1
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    add r0, r5, #0x2cc
    bl func_0207dfac
    ldr r1, =0x10a
    add r0, r4, #0x400
    mov r2, r1
    mov r3, r1
    bl _ZN8Object3D8SetScaleEiii
    add r0, r4, #0x400
    add r1, r10, #0x328
    bl func_02059f38
    add r0, r4, #0x400
    bl _ZN8Object3D20StopCurrentAnimationEv
    ldr r1, =sStrings
    add r0, r4, #0x400
    mov r2, #0x9
    bl _ZN8Object3D24MaybeSetRegularAnimationEPKci
    add r0, r4, #0x400
    mov r1, #0x1000
    bl _ZN8Object3D11DisableFlagEi
    mov r2, #0x0
    mvn r1, #0x0
    ldr r0, =sBones
    b @L0215692c
@L02156924:
    str r1, [r0, r2, lsl #0x2]
    add r2, r2, #0x1
@L0215692c:
    cmp r2, #0x3
    blt @L02156924
    ldr r4, [r10, #0x4f0]
    cmp r4, #0x0
    beq @L021569b0
    ldr r1, =sStrings+0x10b
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r2, =sMatrices-0xc
    ldr r1, =sStrings+0x110
    str r0, [r2, #0x0]
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r2, =sMatrices-0xc
    ldr r1, =sStrings+0x115
    str r0, [r2, #0x4]
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    ldr r1, =sMatrices-0xc
    str r0, [r1, #0x8]
    ldr r0, [r4, #0xa8]
    mov r0, r0, lsl #0x1f
    movs r0, r0, asr #0x1f
    moveq r4, #0x0
    cmp r4, #0x0
    beq @L021569b0
    ldr r1, =SaveBones
    mov r5, #0x3
    mov r0, r4
    mov r2, #0x0
    mov r3, #0x6
    str r5, [sp, #0x0]
    bl SetModelRenderContextRenderCommandHook
@L021569b0:
    ldr r1, [r10, #0xad4]
    mov r0, r7
    bl _ZN16BackgroundLoader10RemoveTaskEi
    mvn r0, #0x0
    str r0, [r10, #0xad4]
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L021569d4:
    cmp r1, #0x12
    bne @L02156aec
    add r0, r10, #0x2e4
    bl _ZN8Object3D20StopCurrentAnimationEv
    add r0, r10, #0x390
    bl _ZN8Object3D20StopCurrentAnimationEv
    mov r1, #0x0
    mov r2, r1
    add r0, r10, #0x2e4
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    mov r1, #0x0
    add r0, r10, #0x390
    mov r2, r1
    bl _ZN8Object3D21MaybeSetBCFGAnimationEii
    bl _ZN9GameState11GetInstanceEv
    mov r4, r0
    bl func_020100f8
    str r0, [r10, #0x1a0]
    add r0, r10, #0x1cc
    add r0, r0, #0x400
    bl SetUpCamera
    add r1, r10, #0x1cc
    mov r0, r4
    add r1, r1, #0x400
    bl func_020100c4
    ldr r2, [r10, #0x1d4]
    ldr r1, [r10, #0x1cc]
    mov r0, #0x2
    str r1, [r2, #0x2c]
    strb r0, [r2, #0x38]
    ldr r0, [r10, #0x1d4]
    ldr r1, [r10, #0x1d0]
    mov r2, #0x1
    bl func_0207f7f0
    ldr r0, [r10, #0x1d4]
    mov r2, #0x1
    strb r2, [r0, #0x3a]
    mov r3, #0x4000000
    ldr r1, [r3, #0x0]
    mov r0, #0x6
    bic r1, r1, #0x1f00
    orr r1, r1, #0x1f00
    str r1, [r3, #0x0]
    str r0, [sp, #0x0]
    add r0, r3, #0x50
    mov r1, #0x4
    mov r3, #0xa
    bl ColorEffect_ConfigureAlphaBlend
    add r1, r10, #0xa00
    ldrh r2, [r1, #0xe2]
    mov r0, r4
    orr r2, r2, #0x1000
    strh r2, [r1, #0xe2]
    ldrh r2, [r1, #0xe2]
    bic r2, r2, #0x40
    strh r2, [r1, #0xe2]
    bl func_0200fb8c
    add r3, r0, #0x2cc
    mov r0, #0x18
    str r0, [sp, #0x0]
    ldr r2, [r10, #0x180]
    add r0, r10, #0x2a0
    ldr r1, =sStrings+0x11a
    add r0, r0, #0x1000
    add r2, r2, #0x64
    bl func_020dbf18
    ldrb r0, [r10, #0xadd]
    add r0, r0, #0x1
    strb r0, [r10, #0xadd]
    b @L02156b0c
@L02156aec:
    cmp r1, #0x13
    addeq r0, r10, #0x1000
    ldreq r0, [r0, #0x2b0]
    cmpeq r0, #0x2
    moveq r0, #0x1
    streqb r0, [r10, #0xadc]
    moveq r0, #0x0
    streqb r0, [r10, #0xadd]
@L02156b0c:
    add sp, sp, #0x12c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void AlchemyPot::UpdateLoaded()
{
    if (!(flags_ & ALCHEMY_POT_NO_3D))
    {
        protagonist_.AdvanceEffects();
        pot_.AdvanceEffects();
        lid_.AdvanceEffects();
        effect_.SetNormalizedAnimationTime(pot_.normalizedAnimationTime_);
    }
    UpdateItem();
    window_.Update();
}

void AlchemyPot::UpdateBackground()
{
    if (!(flags_ & ALCHEMY_POT_LOAD_BACKGROUND))
        return;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    if (backgroundStep_ == 0)
    {
        if (flags_ & ALCHEMY_POT_NO_3D)
            backgroundTask_ = loader->QueueLoadFile(STRING(0x136, "data/ani/bg_rri_t.pac"), 0);
        else
            backgroundTask_ = loader->QueueLoadFile(STRING(0x14c, "data/ani/bg_rri_kari.pac"), 0);
        window_.SetInMenu(0);
        backgroundStep_++;
    }
    else if (backgroundStep_ == 1)
    {
        if (loader->GetTaskStatus(backgroundTask_))
        {
            void* name;
            void* pac;
            unsigned int pacSize;
            loader->GetLoadedFileByID(backgroundTask_, &pac, &pacSize);
            int count = func_02046900(pac);
            BackgroundGraphics background;
            func_0204af64(&background);
            func_0204b11c(&background, 0);
            background.unk_1c_0_ = 0;
            background.unk_1c_4_ = 3;
            func_0204b5b4(&background, 3);
            func_0204b5e8(&background, 0, 0);
            for (int i = 0; i < count; i++)
            {
                unsigned int size;
                void* file = func_020467f0(pac, i, &name, &size);
                if (file != 0)
                {
                    func_0204b2e0(&background, file);
                    func_0204b3a0(&background, file);
                }
            }
            loader->RemoveTask(backgroundTask_);
            backgroundTask_ = -1;
            backgroundStep_ = 0;
            flags_ &= ~ALCHEMY_POT_LOAD_BACKGROUND;
            flags_ &= ~ALCHEMY_POT_RECIPE;
        }
    }
}

// The parameters of an effect of the sub screen, which func_02078484 initializes (0x58 bytes)
struct EffectParams
{
    char name_[0x11];
    unsigned char unk_11;
    short unk_12;
    char unk_14[0x2c - 0x14];
    Vector3fix position_;
    char unk_38[0x44 - 0x38];
    Vector3fix scale_;
};

void AlchemyPot::UpdateEffect()
{
    func_020dbdc0(&subEffect_);
    if (subEffect_.unk_14 == 0 && effectMode_ != 0)
    {
        EffectParams params;
        func_02078484(&params);
        params.unk_11 &= ~4;
        params.unk_12 = 0;
        if (effectMode_ == 1 || effectMode_ == 2)
        {
            strcpy(params.name_, STRING(0x9, "1"));
            effectMode_ = 2;
        }
        else
        {
            strcpy(params.name_, STRING(0x12, "2"));
            effectMode_ = 0;
        }
        params.scale_.x = 0x10a;
        params.scale_.y = 0x10a;
        params.scale_.z = 0x10a;
        params.position_.x = -0x41;
        params.position_.y = -0xaac;
        params.position_.z = 0x4526;
        func_020dbfa4(&subEffect_, &params);
    }
}

void AlchemyPot::ResetIngredients()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    IngredientSprite* ingredient = ingredients_;
    for (unsigned char i = 0; i < 4; i++)
    {
        if (ingredient->task_ > 0)
            loader->RemoveTask(ingredient->task_);
        ingredient->task_ = -1;
        ingredient->Initialize();
        ingredient->graphics_.unk_5e = 0;
        ingredient->graphics_.unk_14 = func_0203be40(func_0203bd08()) + (i << 6) + 0x100;
        ingredient->graphics_.unk_38 = i * 0x120 + 0x240;
        ingredient->graphics_.unk_3c = (i + 10) & 0xf;
        ingredient->graphics_.unk_40 = 0;
        ingredient->x_ = (i << 5) + 0x20;
        ingredient->y_ = 0x80;
        ingredient++;
    }
}

void AlchemyPot::LoadIngredients(PotIngredient* ingredients)
{
    ResetIngredients();
    IngredientSprite* ingredient = ingredients_;
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    numIngredients_ = 0;
    for (unsigned char i = 0; i < 4; i++)
    {
        short item = ingredients->item_;
        ingredient->item_ = item;
        if (item > 0)
        {
            ingredient->loading_ = 1;
            int number = func_020de234(&ingredients->entry_, 0);
            char path[0x40] = {0};
            sprintf(path, STRING(0x165, "data/ani/d_%c%03d.spr"), ingredients->entry_.letter_, number);
            ingredient->task_ = loader->QueueLoadFile(path, 0);
            if (i != 0)
                numIngredients_++;
        }
        ingredients++;
        ingredient++;
    }
}

void AlchemyPot::UpdateIngredients()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    IngredientSprite* ingredient = ingredients_;
    for (unsigned char i = 0; i < 4; i++)
    {
        if (ingredient->loading_)
        {
            if (loader->GetTaskStatus(ingredient->task_))
            {
                void* data;
                unsigned int size;
                loader->GetLoadedFileByID(ingredient->task_, &data, &size);
                if (data != 0)
                {
                    ingredientAllocators_[i].Reset();
                    func_02076080(&ingredient->graphics_, &ingredientAllocators_[i], data, size);
                }
                loader->RemoveTask(ingredient->task_);
                ingredient->task_ = -1;
                ingredient->loading_ = 0;
            }
            ingredient->x_ = 0x6f;
            ingredient->y_ = -0x1a;
        }
        ingredient++;
    }
}

int AlchemyPot::IsLoadingIngredients()
{
    int loading = 0;
    IngredientSprite* ingredient = ingredients_;
    for (unsigned char i = 0; i < 4; i++)
    {
        loading = (loading | ingredient->loading_) ? 1 : 0;
        ingredient++;
    }
    return loading;
}

int AlchemyPot::ShowNames(int show)
{
    int shown = (window_.flags_ & ITEM_INFO_WINDOW_NAMES) ? 1 : 0;
    if (show)
        window_.flags_ |= ITEM_INFO_WINDOW_NAMES;
    else
        window_.flags_ &= ~ITEM_INFO_WINDOW_NAMES;
    if (!shown && show)
    {
        window_.DrawArrow();
        window_.DrawNameBox();
    }
    if (shown && !show)
        window_.ClearBackground();
    return shown;
}

void AlchemyPot::CloseWindow()
{
    flags_ &= ~ALCHEMY_POT_ITEM_SHOWN;
    window_.SetInMenu(0);
    ResetItem();
}

void AlchemyPot::SetMultiplier(unsigned char multiplier)
{
    window_.SetMultiplier(multiplier);
}

void AlchemyPot::DrawNames()
{
    int shown = (window_.flags_ & ITEM_INFO_WINDOW_NAMES) ? 1 : 0;
    if (!shown)
        return;
    window_.DrawNameBox();
}

void AlchemyPot::StartEffect()
{
    EffectParams params;
    func_02078484(&params);
    params.unk_11 &= ~4;
    params.unk_12 = 0;
    strcpy(params.name_, STRING(0x7, "0"));
    params.scale_.x = 0x10a;
    params.scale_.y = 0x10a;
    params.scale_.z = 0x10a;
    params.position_.x = -0x41;
    params.position_.y = -0xaac;
    params.position_.z = 0x4526;
    func_020dbfa4(&subEffect_, &params);
    effectMode_ = 1;
}

void AlchemyPot::StopEffect()
{
    effectMode_ = 3;
}

// Some bytes that nothing uses
extern const unsigned char data_ov006_0215ffac[8] = {8, 9, 9, 0, 0xf0, 0, 3, 7};
