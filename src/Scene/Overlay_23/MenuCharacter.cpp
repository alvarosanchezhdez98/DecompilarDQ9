// The objects of type 5 of the menus (see MenuObjects.h): a party member's 3D model, which L and R turn
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "GameState/GameState.h"
#include "Resource/GameResources.h"
#include "Scene/Overlay_11/MenuScript.h"

#define PAD_BUTTON_R 0x100
#define PAD_BUTTON_L 0x200
#define PAD_BUTTON_UP 0x40
#define PAD_BUTTON_DOWN 0x80

extern "C"
{
    extern char data_02114e30[];

    void* func_0200ff1c(GameState* gameState, int member);
    void* func_020100f8(GameState* gameState);
    bool func_02012430(void* pad, int buttons);
    void func_0202e5c0(void* camera, int x, int y, int z);
    void func_0202e5c8(void* camera, int x, int y, int z);
    void func_0202e9a4(void* camera, int perspective);
    int func_0202e9ec(void* camera);
    void func_0202ee38(void* camera, const Vector3fix* position, int);
    void func_0202ee58(void* camera, const Vector3fix* target, int);
    PartyMemberData* func_02053c6c(void* member);
    void func_0207df50(VRAMManagerState* state);
    void func_0207df90(VRAMManagerState* state);
    void func_0207dfac(VRAMManagerState* state);
    void func_020a2794();
    void func_020a27a0(void* camera);
    void func_020a28a0(void* camera, int);
    void func_020a28b0(void* camera, int);
    void func_020c54a4(int, int, int, int);

    GameResources* func_ov017_0218b5b0();
    Object3D* func_ov017_021bdbd8(GameResources* resources);
    Object3D* func_ov017_021bdbe4();
}

// NONMATCHING: the C matches 92.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler swaps the registers of the object that has the names and of the heap
#ifdef NONMATCHING
int MenuObjectClass5::Initialize(MenuScript* script, int id, int heap, int names, int member)
{
    MenuObjectClass::Initialize();
    type_ = 5;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = NULL;
    current_ = 0;
    perspective_ = 0;
    swap_ = 0;
    turnBack_ = 0;
    unk_1864_2 = 0;
    leftCallback_ = NULL;
    rightCallback_ = NULL;
    GameResources* resources;
    PartNameTable* table;
    MenuHeap* menuHeap;
    MenuObjectClass* object = script->GetObjects()->Find(names);
    menuHeap = script->FindHeap(heap);
    table = (PartNameTable*)object->Ve8();
    resources = func_ov017_0218b5b0();
    func_0207df50((VRAMManagerState*)resources->unknown_2cc);
    func_0207df90((VRAMManagerState*)resources->unknown_2cc);
    for (int i = 0; i < 2; i++)
    {
        models_[i].Initialize();
        models_[i].CreateAllocators(&menuHeap->allocator_);
        models_[i].InitializeVRAMStates();
        models_[i].SetNames(table);
        models_[i].SetUnk_c11(1);
    }
    func_0207dfac((VRAMManagerState*)resources->unknown_2cc);
    models_[0].SetAngle(0x1eb);
    models_[1].SetAngle(0x1eb);
    if (member >= 0)
        Load(member, 0);
    void* camera = func_020100f8(GameState::GetInstance());
    func_0202e5c0(camera, 0xb666, 0xb800, 0x42ccc);
    func_0202e5c8(camera, 0xb666, 0xb800, 0);
    perspective_ = func_0202e9ec(camera);
    func_0202e9a4(camera, 0xf000);
    func_020a27a0(camera);
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript8FindHeapEi(); // MenuScript::FindHeap
    void _ZN14CharacterModel10InitializeEv(); // CharacterModel::Initialize
    void _ZN14CharacterModel10SetUnk_c11Eh(); // CharacterModel::SetUnk_c11
    void _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator(); // CharacterModel::CreateAllocators
    void _ZN14CharacterModel20InitializeVRAMStatesEv(); // CharacterModel::InitializeVRAMStates
    void _ZN14CharacterModel8SetAngleEi(); // CharacterModel::SetAngle
    void _ZN14CharacterModel8SetNamesEP13PartNameTable(); // CharacterModel::SetNames
    void _ZN14MenuObjectList4FindEi(); // MenuObjectList::Find
    void _ZN15MenuObjectClass10InitializeEv(); // MenuObjectClass::Initialize
    void _ZN16MenuObjectClass54LoadEii(); // MenuObjectClass5::Load
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm int MenuObjectClass5::Initialize(MenuScript* script, int id, int heap, int names, int member)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov r10, r0
    mov r5, r1
    mov r6, r2
    mov r4, r3
    bl _ZN15MenuObjectClass10InitializeEv
    mov r0, #0x5
    strh r0, [r10, #0x4]
    strh r6, [r10, #0x6]
    strh r4, [r10, #0x8]
    mov r1, #0x0
    strh r1, [r10, #0xa]
    str r1, [r10, #0x10]
    add r2, r10, #0x1000
    ldrb r3, [r2, #0x864]
    mov r0, r5
    bic r3, r3, #0x1
    strb r3, [r2, #0x864]
    str r1, [r2, #0x860]
    ldrb r3, [r2, #0x864]
    bic r7, r3, #0x8
    and r3, r7, #0xff
    bic r6, r3, #0x2
    and r3, r6, #0xff
    strb r7, [r2, #0x864]
    bic r3, r3, #0x4
    strb r3, [r2, #0x864]
    str r1, [r2, #0x868]
    str r1, [r2, #0x86c]
    bl _ZN10MenuScript10GetObjectsEv
    ldr r1, [sp, #0x28]
    bl _ZN14MenuObjectList4FindEi
    mov r6, r0
    mov r0, r5
    mov r1, r4
    bl _ZN10MenuScript8FindHeapEi
    mov r7, r0
    mov r0, r6
    ldr r1, [r0, #0x0]
    ldr r1, [r1, #0xe8]
    blx r1
    mov r8, r0
    bl func_ov017_0218b5b0
    mov r6, r0
    add r0, r6, #0x2cc
    bl func_0207df50
    add r0, r6, #0x2cc
    bl func_0207df90
    mov r9, #0x0
    add r4, r10, #0x20
    mov r11, #0xc20
    b @L021fc624
@L021fc5e8:
    mul r5, r9, r11
    add r0, r4, r5
    bl _ZN14CharacterModel10InitializeEv
    add r0, r4, r5
    add r1, r7, #0x4
    bl _ZN14CharacterModel16CreateAllocatorsEP13SafeAllocator
    add r0, r4, r5
    bl _ZN14CharacterModel20InitializeVRAMStatesEv
    add r0, r4, r5
    mov r1, r8
    bl _ZN14CharacterModel8SetNamesEP13PartNameTable
    add r0, r4, r5
    mov r1, #0x1
    bl _ZN14CharacterModel10SetUnk_c11Eh
    add r9, r9, #0x1
@L021fc624:
    cmp r9, #0x2
    blt @L021fc5e8
    add r0, r6, #0x2cc
    bl func_0207dfac
    ldr r1, =0x1eb
    add r0, r10, #0x20
    bl _ZN14CharacterModel8SetAngleEi
    ldr r1, =0x1eb
    add r0, r10, #0xc40
    bl _ZN14CharacterModel8SetAngleEi
    ldr r1, [sp, #0x2c]
    cmp r1, #0x0
    blt @L021fc664
    mov r0, r10
    mov r2, #0x0
    bl _ZN16MenuObjectClass54LoadEii
@L021fc664:
    bl _ZN9GameState11GetInstanceEv
    bl func_020100f8
    ldr r1, =0xb666
    ldr r3, =0x42ccc
    mov r2, #0xb800
    mov r4, r0
    bl func_0202e5c0
    ldr r1, =0xb666
    mov r0, r4
    mov r2, #0xb800
    mov r3, #0x0
    bl func_0202e5c8
    mov r0, r4
    bl func_0202e9ec
    add r1, r10, #0x1000
    str r0, [r1, #0x860]
    mov r0, r4
    mov r1, #0xf000
    bl func_0202e9a4
    mov r0, r4
    bl func_020a27a0
    mov r0, #0x1
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void MenuObjectClass5::Finish(MenuObjectList* list)
{
    for (int i = 0; i < 2; i++)
        models_[i].Finish();
    void* camera = func_020100f8(GameState::GetInstance());
    func_020a2794();
    func_0202e9a4(camera, perspective_);
}

void MenuObjectClass5::Load(int member, int turn)
{
    void* partyMember = func_0200ff1c(GameState::GetInstance(), member);
    int next = (current_ + 1) % 2;
    CharacterModel* model = &models_[next];
    if (turn)
        model->SetAngle(0x1eb);
    model->HideAll();
    model->Load(func_02053c6c(partyMember), member, 1, 0);
    swap_ = 1;
}

void MenuObjectClass5::Update(MenuScript* script)
{
    func_020c54a4(0, 0, 0, 0);
    GameState* gameState = GameState::GetInstance();
    unsigned int ticks = gameState->GetTickCount();
    if (ticks == 0)
        ticks = 1;
    models_[0].Update();
    models_[1].Update();
    if (swap_)
    {
        int next = (current_ + 1) % 2;
        if (!models_[next].loading_)
        {
            current_ = next;
            swap_ = 0;
        }
    }
    CharacterModel* model = &models_[current_];
    Vector3fix rotation = model->GetRotation();
    int difference = fix32ReduceAngle0To2Pi(0x1eb - rotation.y);
    int angle = 0;
    if (func_02012430(data_02114e30, PAD_BUTTON_L) && func_02012430(data_02114e30, PAD_BUTTON_R))
    {
        if (!turnBack_)
            turnBack_ = 1;
    }
    if (func_02012430(data_02114e30, PAD_BUTTON_UP))
    {
        const Vector3fix position = {0x7800, 0xf000, 0x28000};
        const Vector3fix target = {0x7800, 0xf000, 0};
        void* camera = func_020100f8(gameState);
        func_020a28a0(camera, 2);
        func_0202ee38(camera, &position, 0xa000);
        func_0202ee58(camera, &target, 0xa000);
    }
    else if (func_02012430(data_02114e30, PAD_BUTTON_DOWN))
    {
        const Vector3fix position = {0xb666, 0xb800, 0x42ccc};
        const Vector3fix target = {0xb666, 0xb800, 0};
        void* camera = func_020100f8(gameState);
        func_020a28b0(camera, 2);
        func_0202ee38(camera, &position, 0xa000);
        func_0202ee58(camera, &target, 0xa000);
    }
    if (turnBack_)
    {
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
        rotation.y = fix32ReduceAngle0To2Pi(angle);
        int left = fix32ReduceAngle0To2Pi(0x1eb - angle);
        int distance = left < 0 ? -left : left;
        if (distance < 0x28)
        {
            turnBack_ = 0;
        }
        else
        {
            distance = 0x6488 - left;
            if (distance < 0)
                distance = -distance;
            if (distance < 0x28)
                turnBack_ = 0;
        }
        if (!turnBack_)
            rotation.y = 0x1eb;
    }
    else if (func_02012430(data_02114e30, PAD_BUTTON_L))
    {
        if (leftCallback_ != NULL)
        {
            (*leftCallback_)(script);
            rotation = model->GetRotation();
        }
        else
        {
            rotation.y += (int)(4096.0f * (0.08f * ticks));
            rotation.y = fix32ReduceAngle0To2Pi(rotation.y);
        }
    }
    else if (func_02012430(data_02114e30, PAD_BUTTON_R))
    {
        if (rightCallback_ != NULL)
        {
            (*rightCallback_)(script);
            rotation = model->GetRotation();
        }
        else
        {
            rotation.y += (int)(4096.0f * (-0.08f * ticks));
            rotation.y = fix32ReduceAngle0To2Pi(rotation.y);
        }
    }
    model->SetRotation(rotation);
}

void MenuObjectClass5::TurnLeft()
{
    func_020c54a4(0, 0, 0, 0);
    CharacterModel* model = &models_[current_];
    Vector3fix rotation = model->GetRotation();
    rotation.y += 0x199;
    rotation.y = fix32ReduceAngle0To2Pi(rotation.y);
    model->SetRotation(rotation);
}

void MenuObjectClass5::TurnRight()
{
    func_020c54a4(0, 0, 0, 0);
    CharacterModel* model = &models_[current_];
    Vector3fix rotation = model->GetRotation();
    rotation.y += -0x199;
    rotation.y = fix32ReduceAngle0To2Pi(rotation.y);
    model->SetRotation(rotation);
}

void MenuObjectClass5::Draw1()
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
    models_[current_].Draw(&extras);
}
