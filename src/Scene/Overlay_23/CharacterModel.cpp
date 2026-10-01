// The original sorts all the variables of the file by size, as the compiler does with this pragma, which has to come
// before the declarations (see Decompiling.md)
#pragma ipa file
#include "Scene/Overlay_23/CharacterModel.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Graphics/NSBXX/GeometryFifo.h"
#include "Graphics/VRAMStaging.h"
#include <std_library_functions.h>

// The NitroSDK's FX_Mul
static inline fix32_t FX_Mul(fix32_t a, fix32_t b)
{
    return (fix32_t)(((int64_t)a * b + 0x800) >> 12);
}

// The colors of the characters' parts (func_02099cac returns them)
struct CharacterColors
{
    unsigned short hair_[10][2];
    unsigned short colors2_[8][2];
    unsigned short colors4_[8][4];
    unsigned short colors8_[8][8];
    unsigned short skin_[8][2];
    // The color of the models' edges
    unsigned short edge_;
};

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    // The runtime's unsigned division, for the assembly
    void _u32_div_f();

    int func_020100a8(GameState* gameState);
    void func_02031234(int);
    CharacterColors* func_02099cac();
    void func_0207de48(VRAMManagerState* state, int textureSize, int paletteSize);
    void func_0207df50(VRAMManagerState* state);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);
    // G3X_SetEdgeColorTable
    void func_020c555c(unsigned short* colors);
    // The number of a part's model file, for a man or a woman
    unsigned int func_020de234(const PartEntry* entry, int female);
    // The number of colors of a part's palette
    int func_020de2a4(const PartEntry* entry, int, int female);
    PartEntry* func_020dedd0(PartNameTable* names, short id);
}

// The strings of the functions, which the compiler pools in this order. Some functions are in assembly for now
// (NONMATCHING), which can't reference the compiler's pool, so they're in an array for them
#ifdef NONMATCHING
#define STRING(offset, text) text
#else
static char sStrings[] = "stand_cm\0stand\0head\0arm2R\0arm2L\0weaponR\0weaponL\0chest\0nsbtx\0d_%c%03d%s.%s\0data/pack_lv5/chara_pd.gp2\0md%02d%02d%c.nsbca\0md%02d%02d%c.bcfg";
#define STRING(offset, text) (sStrings + (offset))
#endif

// The sizes of the parts' allocators, and of their textures and palettes in VRAM
static const unsigned int sAllocatorSizes[CharacterModel::Part_Count] = {
    0x5400, 0x2000, 0x1400, 0x1c00, 0xc00, 0x1c00, 0x1c00, 0x23e8, 0x1b58, 0x1400};
static const int sTextureSizes[CharacterModel::Part_Count] = {
    0x4400, 0x1000, 0x1000, 0, 0x1000, 0x800, 0x800, 0x800, 0x800, 0x800};
static const int sPaletteSizes[CharacterModel::Part_Count] = {0x220, 0x40, 0x40, 0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};

static void SetRotation(Object3D* object, const Vector3fix& rotation);

void CharacterModel::Initialize()
{
    unk_c11 = 0;
    for (int i = 0; i < Part_Count; i++)
    {
        parts_[i].Initialize();
        allocators_[i].ResetAllocatorPointer();
    }
    animationAllocator_.ResetAllocatorPointer();
    holdsWithArms_ = 0;
    for (int i = 0; i < Part_Count + 2; i++)
        tasks_[i] = -1;
    loading_ = 0;
    vocation_ = 0;
    member_ = NULL;
    visible_ = 1;
}

void CharacterModel::Finish()
{
    CancelTasks();
    for (int i = 0; i < Part_Count; i++)
    {
        parts_[i].Initialize();
        allocators_[i].Destroy();
    }
    animationAllocator_.Destroy();
}

void CharacterModel::CreateAllocators(SafeAllocator* allocator)
{
    for (int i = 0; i < Part_Count; i++)
    {
        unsigned int size = sAllocatorSizes[i];
        allocators_[i].CreateTypeA(allocator->Allocate(size), size);
    }
    animationAllocator_.CreateTypeA(allocator->Allocate(0x1000), 0x1000);
}

void CharacterModel::InitializeVRAMStates()
{
    for (int i = 0; i < Part_Count; i++)
        func_0207de48(&vramStates_[i], sTextureSizes[i], sPaletteSizes[i]);
}

void CharacterModel::Update()
{
    void* file;
    unsigned int size;

    if (loading_)
    {
        BackgroundLoader* loader = BackgroundLoader::GetInstance();
        loading_ = 0;
        for (int i = 0; i < Part_Count; i++)
        {
            if (tasks_[i] > -1)
            {
                if (loader->GetTaskStatus(tasks_[i]))
                {
                    parts_[i].Destroy();
                    allocators_[i].Reset();
                    loader->GetLoadedFileByID(tasks_[i], &file, &size);
                    if (size != 0)
                    {
                        func_0207df50(&vramStates_[i]);
                        func_0207df90(&vramStates_[i]);
                        parts_[i].SetModelFromFileCopy(&allocators_[i], file, size, Model3D::TextureStagingMode_Normal);
                        func_0207dfac(&vramStates_[i]);
                        if (i == Part_4 && parts_[Part_3].pModel_ != NULL)
                            parts_[Part_3].pModel_->ApplyTexturesFromModel(parts_[i].pModel_);
                    }
                    loader->RemoveTask(tasks_[i]);
                    tasks_[i] = -1;
                }
                else
                {
                    loading_ = 1;
                }
            }
        }

        short task = tasks_[Part_Count];
        if (task > -1)
        {
            if (loader->GetTaskStatus(task))
            {
                loader->GetLoadedFileByID(task, &file, &size);
                if (size != 0)
                {
                    loader->GetLoadedFileByID(task, &file, &size);
                    if (size != 0)
                        parts_[Part_Body].LoadType0AnimationFromFileInMemory(0, &animationAllocator_, file, size);
                }
                loader->RemoveTask(task);
                tasks_[Part_Count] = -1;
            }
            else
            {
                loading_ = 1;
            }
        }

        task = tasks_[Part_Count + 1];
        if (task > -1)
        {
            if (loader->GetTaskStatus(task))
            {
                loader->GetLoadedFileByID(task, &file, &size);
                if (size != 0)
                {
                    loader->GetLoadedFileByID(task, &file, &size);
                    if (size != 0)
                        parts_[Part_Body].LoadType0AnimationPackageFromBCFGScript(&animationAllocator_, file, size);
                }
                loader->RemoveTask(task);
                tasks_[Part_Count + 1] = -1;
            }
            else
            {
                loading_ = 1;
            }
        }

        if (!loading_ && !colored_)
        {
            UpdateColors();
            colored_ = 1;
            loading_ = 1;
        }

        if (!loading_)
        {
            PartyMemberAppearance* appearance = &member_->appearance_;
            if (bodyChanged_)
            {
                if (appearance->female_ == 1 && unk_c11 == 0)
                {
                    if (parts_[Part_Body].unknown_2_ >= 0)
                    {
                        parts_[Part_Body].StopCurrentAnimation();
                        parts_[Part_Body].MaybeSetRegularAnimation(STRING(0x0, "stand_cm"), 0);
                    }
                }
                else if (parts_[Part_Body].unknown_2_ >= 0)
                {
                    parts_[Part_Body].StopCurrentAnimation();
                    parts_[Part_Body].MaybeSetRegularAnimation(STRING(0x9, "stand"), 0);
                }
                Vector3fix rotation = {0};
                rotation.y = angle_;
                ::SetRotation(&parts_[Part_Body], rotation);
                ::SetRotation(&parts_[Part_6], rotation);
                ::SetRotation(&parts_[Part_1], rotation);
                ::SetRotation(&parts_[Part_5], rotation);
                SetScale(appearance->width_, appearance->height_);
            }

            short models[Part_Count];
            GetModels(vocation_, models, appearance);
            PartEntry* entry = func_020dedd0(names_, models[Part_8]);
            if (entry != NULL && entry->type_ == 6)
                holdsWithArms_ = 1;
            else
                holdsWithArms_ = 0;
        }
    }
}

// The parts whose colors are the eyes' color, until -1
static const short sColoredParts[] = {0, 1, 5, 4, 6, 7, -1};

// NONMATCHING: the C matches 94.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void CharacterModel::UpdateColors()
{
    PartyMemberAppearance* appearance;
    int skin;
    unsigned int offset;
    appearance = &member_->appearance_;
    CharacterColors* colors = func_02099cac();
    int eyes = appearance->eyeColor_;
    offset = (0xffff & vramStates_[Part_2].unk_68) << 3;
    skin = appearance->skinColor_;
    StageMemoryToVRAM(VRAMSubregion_TexturePalette, colors->hair_[appearance->hairColor_], offset + 0x24, 4,
                      false, true);
    StageMemoryToVRAM(VRAMSubregion_TexturePalette, colors->skin_[skin], offset + 0x28, 4, false, true);
    StageMemoryToVRAM(VRAMSubregion_TexturePalette, colors->colors8_[eyes], offset + 0x30, 0x10, false, true);

    short models[Part_Count];
    GetModels(vocation_, models, appearance);
    int i;
    int part;
    for (i = 0; (part = sColoredParts[i]) >= 0; i++)
    {
        int model = models[part];
        int female = appearance->female_;
        if (names_ != NULL && &vramStates_[part] != NULL)
        {
            PartEntry* entry = func_020dedd0(names_, model);
            if (entry != NULL && entry->model_ != NULL)
            {
                int count = func_020de2a4(entry, 0, female);
                Model3D* model;
                if (count != 0 && (count *= 2, (model = parts_[part].pModel_) != NULL))
                {
                    {
                        NSBXXTex* texture = model->GetTEX0();
                        if (texture != NULL)
                        {
                            int position = 0x30;
                            unsigned short size = ((unsigned short)(texture->block4NumEightBytes_ << 3) + 0x1f) & ~0x1f;
                            int start = 0x20;
                            if (part == 0)
                                start = 0x200;
                            position -= size - start;
                            CharacterColors* table = func_02099cac();
                            if (table != NULL)
                            {
                                const void* source = NULL;
                                int length = count * 2;
                                switch (count)
                                {
                                case 2:
                                    source = table->colors2_[eyes];
                                    break;
                                case 4:
                                    source = table->colors4_[eyes];
                                    break;
                                case 8:
                                    source = table->colors8_[eyes];
                                    break;
                                }
                                if (source != NULL)
                                {
                                    position += (vramStates_[part].unk_68 & 0xffff) << 3;
                                    StageMemoryToVRAM(VRAMSubregion_TexturePalette, source, position, length, false, true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN14CharacterModel9GetModelsEiPsPK21PartyMemberAppearance(); // CharacterModel::GetModels
    void _ZN7Model3D7GetTEX0Ev(); // Model3D::GetTEX0
}

asm void CharacterModel::UpdateColors()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x1c
    mov r5, r0
    ldr r0, [r5, #0xc18]
    add r6, r0, #0x88
    bl func_02099cac
    ldrb r2, [r6, #0x414]
    ldr r1, [r5, #0x8dc]
    mov r4, r0
    mov r0, #0x0
    mov r1, r1, lsl #0x10
    mov r9, r1, lsr #0xd
    mov r3, r2, lsl #0x18
    mov r7, r2, lsl #0x1c
    mov r8, r3, lsr #0x1c
    str r0, [sp, #0x0]
    mov r1, #0x1
    str r1, [sp, #0x4]
    ldrb r1, [r6, #0x415]
    add r2, r9, #0x24
    mov r3, #0x4
    mov r1, r1, lsl #0x1c
    add r1, r4, r1, lsr #0x1a
    mov r7, r7, lsr #0x1d
    bl StageMemoryToVRAM
    mov r0, #0x0
    str r0, [sp, #0x0]
    mov r1, #0x1
    str r1, [sp, #0x4]
    add r1, r4, #0x108
    add r1, r1, r8, lsl #0x2
    add r2, r9, #0x28
    mov r3, #0x4
    bl StageMemoryToVRAM
    add r0, r4, #0x88
    add r1, r0, r7, lsl #0x4
    mov r0, #0x0
    str r0, [sp, #0x0]
    mov r3, #0x1
    str r3, [sp, #0x4]
    add r2, r9, #0x30
    mov r3, #0x10
    bl StageMemoryToVRAM
    ldrb r0, [r5, #0xc15]
    add r1, sp, #0x8
    add r2, r6, #0x400
    bl _ZN14CharacterModel9GetModelsEiPsPK21PartyMemberAppearance
    add r0, r5, #0x394
    mov r8, #0x0
    add r11, r0, #0x400
    b @L021e5608
@L021e54d8:
    mov r2, r9, lsl #0x1
    add r1, sp, #0x8
    ldrsh r1, [r1, r2]
    ldrb r2, [r6, #0x414]
    ldr r0, [r5, #0xc0c]
    mov r2, r2, lsl #0x1f
    cmp r0, #0x0
    mov r10, r2, lsr #0x1f
    beq @L021e5604
    mov r2, #0x70
    mul r4, r9, r2
    adds r2, r11, r4
    beq @L021e5604
    mov r1, r1, lsl #0x10
    mov r1, r1, asr #0x10
    bl func_020dedd0
    cmp r0, #0x0
    ldrne r1, [r0, #0x0]
    cmpne r1, #0x0
    beq @L021e5604
    mov r2, r10
    mov r1, #0x0
    bl func_020de2a4
    cmp r0, #0x0
    movne r10, r0, lsl #0x1
    movne r0, #0xac
    mlane r0, r9, r0, r5
    ldrne r0, [r0, #0x8]
    cmpne r0, #0x0
    beq @L021e5604
    bl _ZN7Model3D7GetTEX0Ev
    cmp r0, #0x0
    beq @L021e5604
    ldrh r1, [r0, #0x30]
    cmp r9, #0x0
    mov r0, #0x20
    mov r1, r1, lsl #0x13
    mov r1, r1, lsr #0x10
    add r1, r1, #0x1f
    bic r1, r1, #0x1f
    mov r1, r1, lsl #0x10
    moveq r0, #0x200
    mov r9, #0x30
    rsb r0, r0, r1, lsr #0x10
    sub r9, r9, r0
    bl func_02099cac
    cmp r0, #0x0
    beq @L021e5604
    cmp r10, #0x2
    mov r1, #0x0
    mov r3, r10, lsl #0x1
    beq @L021e55c0
    cmp r10, #0x4
    beq @L021e55cc
    cmp r10, #0x8
    addeq r0, r0, #0x88
    addeq r1, r0, r7, lsl #0x4
    b @L021e55d4
@L021e55c0:
    add r0, r0, #0x28
    add r1, r0, r7, lsl #0x2
    b @L021e55d4
@L021e55cc:
    add r0, r0, #0x48
    add r1, r0, r7, lsl #0x3
@L021e55d4:
    cmp r1, #0x0
    beq @L021e5604
    add r0, r5, r4
    ldr r2, [r0, #0x7fc]
    mov r0, #0x0
    mov r2, r2, lsl #0x10
    mov r4, r0
    str r4, [sp, #0x0]
    mov r4, #0x1
    add r2, r9, r2, lsr #0xd
    str r4, [sp, #0x4]
    bl StageMemoryToVRAM
@L021e5604:
    add r8, r8, #0x1
@L021e5608:
    ldr r0, =sColoredParts
    mov r1, r8, lsl #0x1
    ldrsh r9, [r0, r1]
    cmp r9, #0x0
    bge @L021e54d8
    add sp, sp, #0x1c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 97.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void CharacterModel::Draw(CharacterModelExtras* extras)
{
    if (!loading_ && visible_)
    {
        CharacterColors* colors = func_02099cac();
        if (colors != NULL)
        {
            unsigned short edges[8];
            unsigned short edge = colors->edge_;
            edges[0] = edge;
            edges[1] = edge;
            edges[2] = edge;
            edges[3] = edge;
            edges[4] = edge;
            edges[5] = edge;
            edges[6] = edge;
            edges[7] = edge;
            func_020c555c(edges);

            if (parts_[Part_Body].unknown_2_ >= 0)
            {
                parts_[Part_Body].AdvanceEffects();
                fix32_t time = parts_[Part_Body].animationTime_;
                parts_[Part_6].SetCurrentAnimationTime(time);
                parts_[Part_1].SetCurrentAnimationTime(time);
                parts_[Part_5].SetCurrentAnimationTime(time);
            }

            if (parts_[Part_Body].unknown_2_ > -1)
            {
                parts_[Part_Body].Draw(true);
                Model3D* context = parts_[Part_Body].pModel_;
                if (context != NULL)
                    context = context->unknown_flags_a8_0_ ? context : NULL;
                if (context != NULL)
                {
                    Model3D* model = parts_[Part_Body].pModel_;
                    if (model == NULL)
                        return;
                    int bone = model->GetBoneIndex(STRING(0xf, "head"));
                    if (bone > -1)
                    {
                        GetModelBonePositionAndDirectionMatrices(&context->renderContext_, NULL, NULL, bone);
                        if (extras != NULL && extras->head_ != NULL)
                            extras->head_->DrawSimple2(false);
                        parts_[Part_2].SendTransformToFifo();
                        parts_[Part_2].DrawSimple2(false);
                        parts_[Part_3].DrawSimple2(false);
                        parts_[Part_7].DrawSimple2(false);
                        if (holdsWithArms_)
                        {
                            bone = model->GetBoneIndex(STRING(0x14, "arm2R"));
                            if (bone > -1 && parts_[Part_8].unknown_2_ > -1)
                            {
                                GetModelBonePositionAndDirectionMatrices(&context->renderContext_, NULL, NULL, bone);
                                parts_[Part_8].DrawSimple2(false);
                            }
                            bone = model->GetBoneIndex(STRING(0x1a, "arm2L"));
                            if (bone > -1 && parts_[Part_8].unknown_2_ > -1)
                            {
                                GetModelBonePositionAndDirectionMatrices(&context->renderContext_, NULL, NULL, bone);
                                func_02031234(0x3244);
                                parts_[Part_8].DrawSimple2(false);
                            }
                        }
                        else
                        {
                            bone = model->GetBoneIndex(STRING(0x20, "weaponR"));
                            if (bone > -1 && parts_[Part_8].unknown_2_ > -1)
                            {
                                GetModelBonePositionAndDirectionMatrices(&context->renderContext_, NULL, NULL, bone);
                                parts_[Part_8].DrawSimple2(false);
                            }
                        }
                        bone = model->GetBoneIndex(STRING(0x28, "weaponL"));
                        if (bone > -1 && parts_[Part_9].unknown_2_ > -1)
                        {
                            GetModelBonePositionAndDirectionMatrices(&context->renderContext_, NULL, NULL, bone);
                            parts_[Part_9].DrawSimple2(false);
                        }
                        if (extras != NULL && extras->chest_ != NULL)
                        {
                            bone = model->GetBoneIndex(STRING(0x30, "chest"));
                            if (bone > -1)
                            {
                                GetModelBonePositionAndDirectionMatrices(&context->renderContext_, NULL, NULL, bone);
                                extras->chest_->DrawSimple2(false);
                            }
                        }
                    }
                }
                parts_[Part_Body].ApplyAnimations(&parts_[Part_6]);
                parts_[Part_6].Draw(true);
                parts_[Part_Body].ApplyAnimations(&parts_[Part_1]);
                parts_[Part_1].Draw(true);
                parts_[Part_Body].ApplyAnimations(&parts_[Part_5]);
                parts_[Part_5].Draw(true);
            }
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN7Model3D12GetBoneIndexEPKc(); // Model3D::GetBoneIndex
    void _ZN8Object3D11DrawSimple2Eb(); // Object3D::DrawSimple2
    void _ZN8Object3D14AdvanceEffectsEv(); // Object3D::AdvanceEffects
    void _ZN8Object3D15ApplyAnimationsEPS_(); // Object3D::ApplyAnimations
    void _ZN8Object3D19SendTransformToFifoEv(); // Object3D::SendTransformToFifo
    void _ZN8Object3D23SetCurrentAnimationTimeEi(); // Object3D::SetCurrentAnimationTime
    void _ZN8Object3D4DrawEb(); // Object3D::Draw
}

asm void CharacterModel::Draw(CharacterModelExtras* extras)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x10
    mov r7, r0
    ldrb r0, [r7, #0xc12]
    mov r6, r1
    cmp r0, #0x0
    bne @L021e5950
    ldrb r0, [r7, #0xc14]
    cmp r0, #0x0
    beq @L021e5950
    bl func_02099cac
    cmp r0, #0x0
    beq @L021e5950
    add r0, r0, #0x100
    ldrh r1, [r0, #0x28]
    add r0, sp, #0x0
    strh r1, [sp, #0x0]
    strh r1, [sp, #0x2]
    strh r1, [sp, #0x4]
    strh r1, [sp, #0x6]
    strh r1, [sp, #0x8]
    strh r1, [sp, #0xa]
    strh r1, [sp, #0xc]
    strh r1, [sp, #0xe]
    bl func_020c555c
    ldrsh r0, [r7, #0x2]
    cmp r0, #0x0
    blt @L021e56cc
    mov r0, r7
    bl _ZN8Object3D14AdvanceEffectsEv
    ldr r4, [r7, #0x1c]
    add r0, r7, #0x8
    mov r1, r4
    add r0, r0, #0x400
    bl _ZN8Object3D23SetCurrentAnimationTimeEi
    mov r1, r4
    add r0, r7, #0xac
    bl _ZN8Object3D23SetCurrentAnimationTimeEi
    mov r1, r4
    add r0, r7, #0x35c
    bl _ZN8Object3D23SetCurrentAnimationTimeEi
@L021e56cc:
    ldrsh r1, [r7, #0x2]
    mvn r0, #0x0
    cmp r1, r0
    ble @L021e5950
    mov r0, r7
    mov r1, #0x1
    bl _ZN8Object3D4DrawEb
    ldr r5, [r7, #0x8]
    cmp r5, #0x0
    beq @L021e5900
    ldr r0, [r5, #0xa8]
    mov r0, r0, lsl #0x1f
    movs r0, r0, asr #0x1f
    moveq r5, #0x0
    cmp r5, #0x0
    beq @L021e5900
    ldr r4, [r7, #0x8]
    cmp r4, #0x0
    beq @L021e5950
    ldr r1, =sStrings+0xf
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r3, r0
    mvn r0, #0x0
    cmp r3, r0
    ble @L021e5900
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl GetModelBonePositionAndDirectionMatrices
    cmp r6, #0x0
    ldrne r0, [r6, #0x4]
    cmpne r0, #0x0
    beq @L021e575c
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
@L021e575c:
    add r0, r7, #0x158
    bl _ZN8Object3D19SendTransformToFifoEv
    add r0, r7, #0x158
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
    add r0, r7, #0x204
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
    add r0, r7, #0xb4
    add r0, r0, #0x400
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
    ldrb r0, [r7, #0xc10]
    cmp r0, #0x0
    beq @L021e582c
    ldr r1, =sStrings+0x14
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r3, r0
    mvn r1, #0x0
    cmp r3, r1
    addgt r0, r7, #0x500
    ldrgtsh r0, [r0, #0x62]
    cmpgt r0, r1
    ble @L021e57dc
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl GetModelBonePositionAndDirectionMatrices
    add r0, r7, #0x560
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
@L021e57dc:
    ldr r1, =sStrings+0x1a
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r3, r0
    mvn r1, #0x0
    cmp r3, r1
    addgt r0, r7, #0x500
    ldrgtsh r0, [r0, #0x62]
    cmpgt r0, r1
    ble @L021e5870
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl GetModelBonePositionAndDirectionMatrices
    ldr r0, =0x3244
    bl func_02031234
    add r0, r7, #0x560
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
    b @L021e5870
@L021e582c:
    ldr r1, =sStrings+0x20
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r3, r0
    mvn r1, #0x0
    cmp r3, r1
    addgt r0, r7, #0x500
    ldrgtsh r0, [r0, #0x62]
    cmpgt r0, r1
    ble @L021e5870
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl GetModelBonePositionAndDirectionMatrices
    add r0, r7, #0x560
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
@L021e5870:
    ldr r1, =sStrings+0x28
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r3, r0
    mvn r1, #0x0
    cmp r3, r1
    addgt r0, r7, #0x600
    ldrgtsh r0, [r0, #0xe]
    cmpgt r0, r1
    ble @L021e58b8
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl GetModelBonePositionAndDirectionMatrices
    add r0, r7, #0x20c
    add r0, r0, #0x400
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
@L021e58b8:
    cmp r6, #0x0
    ldrne r0, [r6, #0x0]
    cmpne r0, #0x0
    beq @L021e5900
    ldr r1, =sStrings+0x30
    mov r0, r4
    bl _ZN7Model3D12GetBoneIndexEPKc
    mov r3, r0
    mvn r0, #0x0
    cmp r3, r0
    ble @L021e5900
    mov r1, #0x0
    mov r0, r5
    mov r2, r1
    bl GetModelBonePositionAndDirectionMatrices
    ldr r0, [r6, #0x0]
    mov r1, #0x0
    bl _ZN8Object3D11DrawSimple2Eb
@L021e5900:
    add r1, r7, #0x8
    mov r0, r7
    add r1, r1, #0x400
    bl _ZN8Object3D15ApplyAnimationsEPS_
    add r0, r7, #0x8
    add r0, r0, #0x400
    mov r1, #0x1
    bl _ZN8Object3D4DrawEb
    mov r0, r7
    add r1, r7, #0xac
    bl _ZN8Object3D15ApplyAnimationsEPS_
    add r0, r7, #0xac
    mov r1, #0x1
    bl _ZN8Object3D4DrawEb
    mov r0, r7
    add r1, r7, #0x35c
    bl _ZN8Object3D15ApplyAnimationsEPS_
    add r0, r7, #0x35c
    mov r1, #0x1
    bl _ZN8Object3D4DrawEb
@L021e5950:
    add sp, sp, #0x10
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

// The parts that are animated with the body, whose models change the animations
static const int sAnimatedParts[] = {0, 6, 5, 1, 8};
// The letter of a face's model file, for each hundred of its number
static const char sFaceLetters[10] = {'b', 'b', 'd', 'c', 'c', 0, 'c', 'e', 'a', 0};

#ifndef NONMATCHING
// The initial extension of GetFileName(), which Load() has in assembly for now
static const char sExtension[8] = "nsbmd";
#endif

// Writes the name of a part's model file in chara_pd.gp2, and returns whether it has one
static bool GetFileName(char* path, const PartEntry* entry, PartyMemberData* member, PartyMemberAppearance* appearance,
                        int part, const PartEntry** entries)
{
    if (member == NULL)
        return false;

    const PartEntry* body = entries[0];
    int female = member->appearance_.female_;
    const PartEntry* face = entries[7];
    unsigned int number = func_020de234(entry, female);
    char extension[8] = "nsbmd";
    char suffix[2] = {0};
    if (part == 4)
    {
        strcpy(extension, STRING(0x36, "nsbtx"));
        suffix[0] = 'a';
        suffix[1] = 0;
        number += appearance->hairColor_;
    }
    if (part == 3)
    {
        suffix[0] = 'a';
        suffix[1] = 0;
        if (face != NULL && face->unk_18 > -1)
        {
            unsigned int hundreds = func_020de234(face, female) / 100;
            if (hundreds < 10)
            {
                char letter = sFaceLetters[hundreds];
                if (letter == 0)
                    return false;
                suffix[0] = letter;
                if (hundreds == 3 && female == 0 && appearance->models_[3] == 0x2329)
                    suffix[0] = 'f';
            }
            else
            {
                return false;
            }
        }
    }
    if (part == 5 && (appearance->models_[4] == 0x1f4a || appearance->models_[4] < 0))
        number = func_020de234(body, female);
    if (entry->unk_18 == 1000)
        number += member->unk_56a;
    sprintf(path, STRING(0x3c, "d_%c%03d%s.%s"), (char)entry->letter_, number, suffix, extension);
    return true;
}

// NONMATCHING: the C matches 99.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void CharacterModel::Load(PartyMemberData* member, int vocation, int, int reload)
{
    if (member == NULL)
        return;

    member_ = member;
    CancelTasks();
    GameState* gameState = GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    PartyMemberAppearance* appearance = &member->appearance_;
    if (vocation < 0)
        vocation = member->unk_568;
    if (vocation < 0)
        vocation = func_020100a8(gameState);
    vocation_ = vocation;

    short models[Part_Count];
    GetModels(vocation, models, appearance);
    parts_[Part_3].unknown_2_ = -1;
    parts_[Part_4].unknown_2_ = -1;
    func_020dedd0(names_, models[Part_7]);
    const PartEntry* entries[Part_Count] = {0};
    entries[0] = func_020dedd0(names_, models[Part_Body]);
    entries[7] = func_020dedd0(names_, models[Part_7]);
    angle_ = parts_[Part_Body].rotation_.y;

    bodyChanged_ = 0;
    for (int i = 0; i < 5; i++)
    {
        int part = sAnimatedParts[i];
        if (parts_[part].unknown_2_ == models[part] && reload == 0)
            continue;
        bodyChanged_ = 1;
        parts_[Part_Body].unknown_2_ = -1;
        parts_[Part_6].unknown_2_ = -1;
        parts_[Part_5].unknown_2_ = -1;
        parts_[Part_1].unknown_2_ = -1;
        break;
    }

    for (int i = 0; i < Part_Count; i++)
    {
        if (models[i] < 0)
        {
            parts_[i].Destroy();
            parts_[i].unknown_2_ = -1;
            if (i == 0)
                models[Part_5] = -1;
            continue;
        }

        const PartEntry* entry = func_020dedd0(names_, models[i]);
        if (entry == NULL)
        {
            parts_[i].Initialize();
            parts_[i].unknown_2_ = models[i];
            continue;
        }

        parts_[i].Destroy();
        allocators_[i].Reset();
        char path[0x80];
        if (GetFileName(path, entry, member, appearance, i, entries))
        {
            tasks_[i] = loader->QueueLoadFileInGP2(STRING(0x4a, "data/pack_lv5/chara_pd.gp2"), path, NULL);
            parts_[i].unknown_2_ = models[i];
        }
    }

    bodyChanged_ = 1;
    if (bodyChanged_)
    {
        const PartEntry* body = func_020dedd0(names_, models[Part_Body]);
        const PartEntry* item = func_020dedd0(names_, models[Part_8]);
        unsigned char animations = 0;
        if (item != NULL)
            animations = item->model_->animations_;
        if (body != NULL)
        {
            char name[0x80];
            int sex = 'm';
            if (appearance->female_ == 1)
                sex = 'w';
            sprintf(name, STRING(0x65, "md%02d%02d%c.nsbca"), body->model_->animations_, animations, sex);
            tasks_[Part_Count] = loader->QueueLoadFileInGP2(STRING(0x4a, "data/pack_lv5/chara_pd.gp2"), name, NULL);
            sprintf(name, STRING(0x78, "md%02d%02d%c.bcfg"), body->model_->animations_, animations, sex);
            tasks_[Part_Count + 1] = loader->QueueLoadFileInGP2(STRING(0x4a, "data/pack_lv5/chara_pd.gp2"), name, NULL);
            if (parts_[Part_Body].pModel_ != NULL)
                parts_[Part_Body].pModel_->RemoveAnimations();
            parts_[Part_Body].RemoveAllAnimationPackages();
            animationAllocator_.Reset();
        }
    }
    loading_ = 1;
    colored_ = 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN14CharacterModel11CancelTasksEv(); // CharacterModel::CancelTasks
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(); // BackgroundLoader::QueueLoadFileInGP2
    void _ZN7Model3D16RemoveAnimationsEv(); // Model3D::RemoveAnimations
    void _ZN8Object3D10InitializeEv(); // Object3D::Initialize
    void _ZN8Object3D26RemoveAllAnimationPackagesEv(); // Object3D::RemoveAllAnimationPackages
    void _ZN8Object3D7DestroyEv(); // Object3D::Destroy
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void CharacterModel::Load(PartyMemberData* member, int vocation, int, int reload)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x15c
    movs r9, r1
    mov r10, r0
    mov r7, r2
    ldr r5, [sp, #0x180]
    beq @L021e5e38
    str r9, [r10, #0xc18]
    bl _ZN14CharacterModel11CancelTasksEv
    bl _ZN9GameState11GetInstanceEv
    mov r6, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    add r1, r9, #0x88
    str r0, [sp, #0x10]
    cmp r7, #0x0
    addlt r0, r9, #0x500
    ldrltsh r7, [r0, #0x68]
    add r4, r1, #0x400
    cmp r7, #0x0
    bge @L021e59d0
    mov r0, r6
    bl func_020100a8
    mov r7, r0
@L021e59d0:
    add r1, sp, #0x48
    mov r0, r7
    mov r2, r4
    strb r7, [r10, #0xc15]
    bl _ZN14CharacterModel9GetModelsEiPsPK21PartyMemberAppearance
    add r0, r10, #0x200
    mvn r1, #0x0
    strh r1, [r0, #0x6]
    strh r1, [r0, #0xb2]
    ldrsh r1, [sp, #0x56]
    ldr r0, [r10, #0xc0c]
    bl func_020dedd0
    add r0, sp, #0x20
    mov r1, #0x28
    bl __clear
    ldrsh r1, [sp, #0x48]
    ldr r0, [r10, #0xc0c]
    bl func_020dedd0
    str r0, [sp, #0x20]
    ldrsh r1, [sp, #0x56]
    ldr r0, [r10, #0xc0c]
    bl func_020dedd0
    str r0, [sp, #0x3c]
    ldr r1, [r10, #0x54]
    add r0, r10, #0xc00
    strh r1, [r0, #0x1c]
    mov r7, #0x0
    strb r7, [r10, #0xc13]
    ldr r6, =sAnimatedParts
    add r2, sp, #0x48
    mov r0, #0xac
    b @L021e5a9c
@L021e5a50:
    ldr r1, [r6, r7, lsl #0x2]
    mla r3, r1, r0, r10
    mov r1, r1, lsl #0x1
    ldrsh r3, [r3, #0x2]
    ldrsh r1, [r2, r1]
    cmp r1, r3
    cmpeq r5, #0x0
    beq @L021e5a98
    mov r0, #0x1
    strb r0, [r10, #0xc13]
    sub r1, r0, #0x2
    strh r1, [r10, #0x2]
    add r0, r10, #0x400
    strh r1, [r0, #0xa]
    add r0, r10, #0x300
    strh r1, [r0, #0x5e]
    strh r1, [r10, #0xae]
    b @L021e5aa4
@L021e5a98:
    add r7, r7, #0x1
@L021e5a9c:
    cmp r7, #0x5
    blt @L021e5a50
@L021e5aa4:
    mov r5, #0x0
    b @L021e5d18
@L021e5aac:
    add r0, sp, #0x48
    mov r1, r5, lsl #0x1
    ldrsh r1, [r0, r1]
    cmp r1, #0x0
    bge @L021e5ae8
    mov r0, #0xac
    mul r6, r5, r0
    add r0, r10, r6
    bl _ZN8Object3D7DestroyEv
    add r0, r10, r6
    mvn r1, #0x0
    strh r1, [r0, #0x2]
    cmp r5, #0x0
    streqh r1, [sp, #0x52]
    b @L021e5d14
@L021e5ae8:
    ldr r0, [r10, #0xc0c]
    bl func_020dedd0
    movs r6, r0
    mov r0, #0xac
    bne @L021e5b20
    mul r6, r5, r0
    add r0, r10, r6
    bl _ZN8Object3D10InitializeEv
    add r0, sp, #0x48
    mov r1, r5, lsl #0x1
    ldrsh r1, [r0, r1]
    add r0, r10, r6
    strh r1, [r0, #0x2]
    b @L021e5d14
@L021e5b20:
    mul r0, r5, r0
    str r0, [sp, #0x8]
    add r0, r10, r0
    bl _ZN8Object3D7DestroyEv
    add r0, r10, #0x2b8
    add r1, r0, #0x400
    mov r0, #0x14
    mla r0, r5, r0, r1
    bl _ZN13SafeAllocator5ResetEv
    cmp r9, #0x0
    moveq r0, #0x0
    beq @L021e5cd4
    ldrb r2, [r9, #0x49c]
    ldr r1, [sp, #0x20]
    mov r0, r6
    str r1, [sp, #0xc]
    mov r1, r2, lsl #0x1f
    mov r11, r1, lsr #0x1f
    mov r1, r11
    ldr r8, [sp, #0x3c]
    bl func_020de234
    ldr r3, =sExtension
    add r2, sp, #0x16
    mov r7, r0
    mov r1, #0x8
@L021e5b84:
    ldrb r0, [r3], #0x1
    subs r1, r1, #0x1
    strb r0, [r2], #0x1
    bne @L021e5b84
    add r0, sp, #0x14
    mov r1, #0x2
    bl __clear
    cmp r5, #0x4
    bne @L021e5bd0
    ldr r1, =sStrings+0x36
    add r0, sp, #0x16
    bl strcpy
    mov r1, #0x61
    mov r0, #0x0
    strb r1, [sp, #0x14]
    strb r0, [sp, #0x15]
    ldrb r0, [r4, #0x15]
    mov r0, r0, lsl #0x1c
    add r7, r7, r0, lsr #0x1c
@L021e5bd0:
    cmp r5, #0x3
    bne @L021e5c5c
    mov r1, #0x61
    mov r0, #0x0
    strb r1, [sp, #0x14]
    strb r0, [sp, #0x15]
    cmp r8, #0x0
    beq @L021e5c5c
    ldrsh r1, [r8, #0x18]
    sub r0, r0, #0x1
    cmp r1, r0
    ble @L021e5c5c
    mov r0, r8
    mov r1, r11
    bl func_020de234
    mov r1, #0x64
    bl _u32_div_f
    cmp r0, #0xa
    bhs @L021e5c54
    ldr r1, =sFaceLetters
    ldrsb r1, [r1, r0]
    cmp r1, #0x0
    moveq r0, #0x0
    beq @L021e5cd4
    cmp r0, #0x3
    cmpeq r11, #0x0
    strb r1, [sp, #0x14]
    ldreqsh r1, [r4, #0x6]
    ldreq r0, =0x2329
    cmpeq r1, r0
    moveq r0, #0x66
    streqb r0, [sp, #0x14]
    b @L021e5c5c
@L021e5c54:
    mov r0, #0x0
    b @L021e5cd4
@L021e5c5c:
    cmp r5, #0x5
    bne @L021e5c8c
    ldrsh r1, [r4, #0x8]
    ldr r0, =0x1f4a
    cmp r1, r0
    beq @L021e5c7c
    cmp r1, #0x0
    bge @L021e5c8c
@L021e5c7c:
    ldr r0, [sp, #0xc]
    mov r1, r11
    bl func_020de234
    mov r7, r0
@L021e5c8c:
    ldrsh r0, [r6, #0x18]
    add r1, sp, #0x14
    cmp r0, #0x3e8
    ldreqb r0, [r9, #0x56a]
    addeq r7, r7, r0
    add r0, sp, #0x16
    str r1, [sp, #0x0]
    str r0, [sp, #0x4]
    ldr r1, [r6, #0x10]
    add r0, sp, #0xdc
    mov r1, r1, lsl #0x4
    mov r1, r1, lsr #0x18
    mov r2, r1, lsl #0x18
    ldr r1, =sStrings+0x3c
    mov r3, r7
    mov r2, r2, asr #0x18
    bl sprintf
    mov r0, #0x1
@L021e5cd4:
    cmp r0, #0x0
    beq @L021e5d14
    ldr r1, =sStrings+0x4a
    ldr r0, [sp, #0x10]
    add r2, sp, #0xdc
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    add r1, r10, r5, lsl #0x1
    add r1, r1, #0xb00
    strh r0, [r1, #0xf4]
    add r2, sp, #0x48
    mov r0, r5, lsl #0x1
    ldrsh r1, [r2, r0]
    ldr r0, [sp, #0x8]
    add r0, r10, r0
    strh r1, [r0, #0x2]
@L021e5d14:
    add r5, r5, #0x1
@L021e5d18:
    cmp r5, #0xa
    blt @L021e5aac
    mov r0, #0x1
    strb r0, [r10, #0xc13]
    tst r0, #0xff
    beq @L021e5e28
    ldrsh r1, [sp, #0x48]
    ldr r0, [r10, #0xc0c]
    bl func_020dedd0
    mov r5, r0
    ldrsh r1, [sp, #0x58]
    ldr r0, [r10, #0xc0c]
    bl func_020dedd0
    cmp r0, #0x0
    ldrne r0, [r0, #0x0]
    mov r6, #0x0
    ldrne r0, [r0, #0x4]
    movne r0, r0, lsl #0xc
    movne r0, r0, lsr #0x18
    andne r6, r0, #0xff
    cmp r5, #0x0
    beq @L021e5e28
    ldrb r0, [r4, #0x14]
    mov r4, #0x6d
    mov r3, r6
    mov r0, r0, lsl #0x1f
    mov r0, r0, lsr #0x1f
    cmp r0, #0x1
    moveq r4, #0x77
    str r4, [sp, #0x0]
    ldr r1, [r5, #0x0]
    add r0, sp, #0x5c
    ldr r2, [r1, #0x4]
    ldr r1, =sStrings+0x65
    mov r2, r2, lsl #0xc
    mov r2, r2, lsr #0x18
    bl sprintf
    ldr r1, =sStrings+0x4a
    ldr r0, [sp, #0x10]
    add r2, sp, #0x5c
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    add r1, r10, #0xc00
    strh r0, [r1, #0x8]
    str r4, [sp, #0x0]
    ldr r1, [r5, #0x0]
    add r0, sp, #0x5c
    ldr r2, [r1, #0x4]
    ldr r1, =sStrings+0x78
    mov r2, r2, lsl #0xc
    mov r2, r2, lsr #0x18
    mov r3, r6
    bl sprintf
    ldr r0, [sp, #0x10]
    ldr r1, =sStrings+0x4a
    add r2, sp, #0x5c
    mov r3, #0x0
    bl _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator
    add r1, r10, #0xc00
    strh r0, [r1, #0xa]
    ldr r0, [r10, #0x8]
    cmp r0, #0x0
    beq @L021e5e18
    bl _ZN7Model3D16RemoveAnimationsEv
@L021e5e18:
    mov r0, r10
    bl _ZN8Object3D26RemoveAllAnimationPackagesEv
    add r0, r10, #0x780
    bl _ZN13SafeAllocator5ResetEv
@L021e5e28:
    mov r0, #0x1
    strb r0, [r10, #0xc12]
    mov r0, #0x0
    strb r0, [r10, #0xc1e]
@L021e5e38:
    add sp, sp, #0x15c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void CharacterModel::SetScale(int width, int height)
{
    fix32_t scale = FX_Mul(height, width);
    parts_[Part_Body].SetScale(scale, height, scale);
    parts_[Part_6].SetScale(scale, height, scale);
    parts_[Part_1].SetScale(scale, height, scale);
    parts_[Part_5].SetScale(scale, height, scale);

    // The items keep their size
    short inverse = fix32_Divide(0x1000, scale);
    short inverseHeight = fix32_Divide(0x1000, height);
    parts_[Part_8].SetScale(inverse, inverseHeight, inverse);
    parts_[Part_9].SetScale(inverse, inverseHeight, inverse);

    short x = FX_Mul(inverse, 0x1000);
    short y = FX_Mul(inverseHeight, 0x1000);
    short z = FX_Mul(0x1000, inverse);
    parts_[Part_2].SetScale(x, y, z);
    parts_[Part_3].SetScale(x, y, z);
    parts_[Part_7].SetScale(x, y, z);
}

void CharacterModel::GetModels(int vocation, short* models, const PartyMemberAppearance* appearance)
{
    models[0] = appearance->models_[0];
    models[1] = appearance->models_[1];
    models[2] = appearance->models_[2];
    models[3] = appearance->models_[3];
    models[4] = appearance->models_[3];
    models[5] = appearance->models_[4];
    models[6] = appearance->models_[5];
    models[7] = appearance->models_[6];
    models[8] = appearance->models_[7];
    models[9] = appearance->models_[8];
    if (models[0] < 0)
        models[0] = 1000;
    if (models[6] < 0)
        models[6] = 0x3e2;
    if (models[1] < 0)
        models[1] = 0x1f41;
    if (models[5] < 0)
    {
        models[5] = appearance->unk_16;
        if (models[5] < 0)
            models[5] = 0x1f4a;
    }
}

void CharacterModel::SetRotation(const Vector3fix& rotation)
{
    ::SetRotation(&parts_[Part_Body], rotation);
    ::SetRotation(&parts_[Part_6], rotation);
    ::SetRotation(&parts_[Part_1], rotation);
    ::SetRotation(&parts_[Part_5], rotation);
}

static void SetRotation(Object3D* object, const Vector3fix& rotation)
{
    object->rotation_.x = rotation.x;
    object->rotation_.y = rotation.y;
    object->rotation_.z = rotation.z;
}

void CharacterModel::SetAngle(int angle)
{
    Vector3fix rotation = {0};
    rotation.y = angle;
    ::SetRotation(&parts_[Part_Body], rotation);
    ::SetRotation(&parts_[Part_6], rotation);
    ::SetRotation(&parts_[Part_1], rotation);
    ::SetRotation(&parts_[Part_5], rotation);
}

Vector3fix CharacterModel::GetRotation()
{
    return parts_[Part_Body].rotation_;
}

void CharacterModel::SetUnk_c11(unsigned char value)
{
    unk_c11 = value;
}

void CharacterModel::Hide(int part)
{
    parts_[part].unknown_2_ = -1;
}

void CharacterModel::HideAll()
{
    for (int i = 0; i < Part_Count; i++)
        parts_[i].unknown_2_ = -1;
}

Object3D* CharacterModel::GetBody()
{
    return parts_;
}

void CharacterModel::SetNames(PartNameTable* names)
{
    names_ = names;
}

void CharacterModel::CancelTasks()
{
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    for (int i = 0; i < Part_Count + 2; i++)
    {
        if (tasks_[i] > -1)
            loader->RemoveTask(tasks_[i]);
        tasks_[i] = -1;
    }
}
