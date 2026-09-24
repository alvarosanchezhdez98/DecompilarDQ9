#include "Scene/Overlay_21/CharacterCreationScene.h"
#include "Filesystem/BackgroundLoader.h"
#include "GameState/GameState.h"
#include "Graphics/NSBXX/GeometryFifo.h"
#include "Graphics/NSBXX/RenderConfig.h"
#include "Graphics/VRAMStaging.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/Graphics.h"
#include "System/VRAM.h"
#include <globaldefs.h>

#define REG_MASTER_BRIGHT ((volatile unsigned short*)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((volatile unsigned short*)0x0400106c)

// The text system: it formats texts and shows them in the message window
struct MessageSystem
{
    char unk_0[0x1e28];
    void* unk_1e28;
};

struct Unknown_0203bd08
{
    int unk_0;
};

struct Unknown_0203bd14
{
    int unk_0;
    char unk_4[0x504];
    int unk_508;
};

extern "C"
{
    // The IDs of the overlays, which the linker script defines: the code references them like the NitroSDK's
    // FS_OVERLAY_ID(), but not every time
    extern unsigned int OVERLAY_9_ID[];
    extern unsigned int OVERLAY_23_ID[];

    // The game's heap
    extern AllocatorUnion data_02114e20;
    // The sound player
    extern char data_02108760[];
    extern char data_02109bf4[];
    // Counts the frames
    extern int data_02114e50;

    // Sets the game's resources
    void func_0200fb84(GameState* gameState, GameResources* resources);
    // Whether the game keeps running
    bool func_0200fb9c(GameState* gameState);
    void func_020100a0(GameState* gameState, int);
    int func_020100a8(GameState* gameState);
    void* func_020100bc(GameState* gameState);
    void func_02010124(GameState* gameState);
    CreatedCharacter* func_02010954(GameState* gameState);
    void* func_02012d88(AllocatorUnion* allocator, unsigned int size);
    void func_02012da4(AllocatorUnion* allocator, void* data);
    void func_02012efc();
    void func_0202e0a4(void* camera);
    void func_0203aa08(void*);
    void func_0203ad88(void*, int, int);
    Unknown_0203bd08* func_0203bd08();
    Unknown_0203bd14* func_0203bd14();
    void func_0203bd24();
    void func_0203bd88(Unknown_0203bd08*);
    void func_0203bdb0(Unknown_0203bd08*);
    int func_0203be4c(Unknown_0203bd08*);
    void func_0203c35c(Unknown_0203bd14*);
    MessageSystem* func_020421a0();
    void func_02042c68();
    void func_02043000(MessageSystem* messages);
    void func_02043124(MessageSystem* messages);
    void func_020432c4(MessageSystem* messages);
    void func_020440a4(MessageSystem* messages);
    void func_0207de48(void*, int, int);
    void func_0207df50(void*);
    void func_0207df90(void*);
    void func_0207dfac(void*);
    void func_0209c20c(void*);
    void func_0209c3b4(void*, int);
    void func_0209c678(void*, int);
    // Loads an overlay
    void func_020a1940(unsigned int id);
    // Unloads an overlay
    void func_020a1df8(unsigned int id);
    void func_020a1e54(unsigned int);
    void func_020bb48c(int, int);
    void func_020bb780(int, int);
    void func_020bbcb4();
    // NNS_SndMain
    void func_020bbd9c();
    // GX_DispOn
    void func_020c38d4();
    // GX_SetGraphicsMode
    void func_020c391c(int mode, int bgMode, int bg0Is3D);
    // GXS_SetGraphicsMode
    void func_020c3984(int bgMode);
    // GXx_SetMasterBrightness_
    void func_020c39a0(volatile unsigned short* reg, int brightness);
    // G3X_Init
    void func_020c51dc();
    // G3X_Reset
    void func_020c52e8();
    // G3X_InitMtxStack
    void func_020c537c();
    // G3X_ResetMtxStack
    void func_020c5414();
    // G3X_SetEdgeColorTable
    void func_020c555c(const unsigned short* colors);
    // G3X_SetClearColor
    void func_020c5588(int color, int alpha, int depth, int polygonID, int fog);
    // OS_WaitVBlankIntr
    void func_020c9820();
    // MIi_CpuClearFast
    void func_020ca458(int value, void* dst, unsigned int len);
    void func_020d86d0(int, int);

    void func_ov009_021842a0(CharacterCreation* creation, SafeAllocator* allocator);
    void func_ov009_0218454c(CharacterCreation* creation, int, int);
    void func_ov009_02184848(CharacterCreation* creation);
    // Whether the character creation is done
    bool func_ov009_02184a18(CharacterCreation* creation);
    void func_ov009_02184bbc(CharacterCreation* creation);
    void func_ov009_02184c30(CharacterCreation* creation);
    void func_ov009_02184ca4(CharacterCreation* creation);
}

void CharacterCreationScene::Initialize()
{
    InitializeBrightnessState((GameResources*)this);
    allocator_.ResetAllocatorPointer();
    creation_ = NULL;
    done_ = 0;
}

void CharacterCreationScene::Finish()
{
    SignedAllocatorHeader* buffer = allocator_.GetSignedAllocator();
    allocator_.Destroy();
    func_02012da4(&data_02114e20, buffer);
    creation_ = NULL;
}

// NONMATCHING: the C matches 89.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The compiler schedules the constant arguments of three calls differently around the register writes before them
// (after the OBJ VRAM modes, the visible planes and the priorities of the sub engine's BGs), which changes the
// registers of those writes. Neither the declarations' order, the SDK's inline functions, other types nor other
// compiler versions change it.
#ifdef NONMATCHING
void CharacterCreationScene::Run()
{
    func_020a1df8(3);
    func_020a1940((unsigned int)OVERLAY_9_ID);
    func_020a1940((unsigned int)OVERLAY_23_ID);
    GameState* gameState = GameState::GetInstance();
    func_0200fb84(gameState, (GameResources*)this);
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    BackgroundLoader::GetInstance()->MaybeReset();
    Unknown_0203bd08* unknown = func_0203bd08();
    func_0203bd24();
    unknown->unk_0 = 0;
    Unknown_0203bd14* unknown2 = func_0203bd14();
    unknown2->unk_0 = func_0203be4c(unknown) + 0x200;
    func_0203c35c(unknown2);
    unknown2->unk_508 = 0x7000;

    MapVRAMBanksToLCDC(0x1ff);
    func_020ca458(0, (void*)0x06800000, 0xa4000);
    DisableLCDCMappedVRAMBanks();
    Finish3DRendering();
    func_020c51dc();
    func_020c537c();
    LockStagedTextureVRAMCopying();
    MapVRAMBanksToTextureImage(1);
    func_020bb48c(1, 1);
    MapVRAMBanksToTexturePalette(0x40);
    func_020bb780(0x4000, 1);
    MapVRAMBanksToMainBG(0x10);
    MapVRAMBanksToSubBG(4);
    MapVRAMBanksToMainObj(0x20);
    DISPCNT = (DISPCNT & ~0x300010) | 0x10;
    MapVRAMBanksToSubObj(8);
    DISPCNTSUB = (DISPCNTSUB & ~0x300010) | 0x10;
    UpdateVRAMStagingVRAMBanks();
    UnlockStagedTextureVRAMCopying();

    DISPCNT = (DISPCNT & ~0x1f00) | 0x1f00;
    func_020c391c(1, 0, 1);
    BG1CNT = (BG1CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 0x1d00;
    BG2CNT = (BG2CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 0x1e08;
    BG3CNT = (BG3CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 0x1f0c;
    BG0CNT = (BG0CNT & ~BGCNT_MASK_PRIORITY) | 2;
    BG1CNT = (BG1CNT & ~BGCNT_MASK_PRIORITY) | 3;
    BG2CNT = (BG2CNT & ~BGCNT_MASK_PRIORITY) | 1;
    BG3CNT = (BG3CNT & ~BGCNT_MASK_PRIORITY) | 0;
    DISPCNTSUB = (DISPCNTSUB & ~0x1f00) | 0x1700;
    func_020c3984(0);
    BG0CNTSUB = (BG0CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 0x1d00;
    BG1CNTSUB = (BG1CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 0x1e10;
    BG2CNTSUB = (BG2CNTSUB & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 0x1f18;
    BG0CNTSUB = (BG0CNTSUB & ~BGCNT_MASK_PRIORITY) | 2;
    BG1CNTSUB = (BG1CNTSUB & ~BGCNT_MASK_PRIORITY) | 1;
    BG2CNTSUB = (BG2CNTSUB & ~BGCNT_MASK_PRIORITY) | 0;
    BG3CNTSUB = (BG3CNTSUB & ~BGCNT_MASK_PRIORITY) | 3;
    POWCNT |= 0x8000;
    func_020c5588(0, 0, 0x7fff, 0, 0);
    unsigned short edgeColors[8] = { 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086 };
    func_020c555c(edgeColors);

    func_0207de48(unk_44, 0x4000, 0x40);
    MessageSystem* messages = func_020421a0();
    func_02042c68();
    func_02043124(messages);
    func_020440a4(messages);
    messages->unk_1e28 = unk_44;
    func_0207df50(unk_44);
    func_0207df90(unk_44);
    func_020432c4(messages);
    func_0207dfac(unk_44);
    func_020100a0(gameState, 0);

    void* buffer = func_02012d88(&data_02114e20, 0x4b238);
    allocator_.CreateTypeA(buffer, 0x4b238);
    allocator_.Reset();
    creation_ = (CharacterCreation*)allocator_.Allocate(sizeof(CharacterCreation));
    func_ov009_0218454c(creation_, 0, 0);
    character_ = func_02010954(gameState);
    character_->unk_568 = func_020100a8(gameState);
    creation_->character_ = character_;
    func_ov009_021842a0(creation_, &allocator_);
    func_0209c3b4(data_02109bf4, 2);
    func_020c9820();
    func_020c38d4();
    DISPCNTSUB |= 0x10000;
    func_02010124(gameState);

    while (true)
    {
        if (!func_0200fb9c(gameState) || done_ != 0)
        {
            break;
        }
        func_02012efc();
        Update();
        Draw();
        allowBrightnessApply = true;
        func_020c9820();
        func_020bbcb4();
        func_ov009_02184ca4(creation_);
        func_0203bdb0(func_0203bd08());
        UpdateAndApplyBrightness((GameResources*)this);
        data_02114e50++;
        gameState->CalculateDeltaTime(16667);
    }

    func_ov009_02184848(creation_);
    func_0209c678(data_02109bf4, 0);
    func_0203ad88(data_02109bf4, 0, 0);
    func_0203aa08(data_02109bf4);
    func_0209c20c(data_02109bf4);
    func_02043000(messages);
    func_0207df50(unk_44);
    func_0200fb84(gameState, NULL);
    func_020a1e54(1);
}
#else
static const unsigned short sEdgeColors[8] = { 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086, 0x1086 };

extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN13SafeAllocator5ResetEv(); // SafeAllocator::Reset
    void _ZN13SafeAllocator8AllocateEj(); // SafeAllocator::Allocate
    void _ZN16BackgroundLoader10MaybeResetEv(); // BackgroundLoader::MaybeReset
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState18CalculateDeltaTimeEy(); // GameState::CalculateDeltaTime
    void _ZN22CharacterCreationScene6UpdateEv(); // CharacterCreationScene::Update
    void _ZN22CharacterCreationScene4DrawEv(); // CharacterCreationScene::Draw
}

asm void CharacterCreationScene::Run()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, lr}
    sub sp, sp, #0x14
    mov r7, r0
    mov r0, #0x3
    bl func_020a1df8
    ldr r0, =0x9
    bl func_020a1940
    ldr r0, =0x17
    bl func_020a1940
    bl _ZN9GameState11GetInstanceEv
    mov r5, r0
    mov r1, r7
    bl func_0200fb84
    ldr r0, =0x400006c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    bl _ZN16BackgroundLoader11GetInstanceEv
    bl _ZN16BackgroundLoader10MaybeResetEv
    bl func_0203bd08
    mov r6, r0
    bl func_0203bd24
    mov r0, #0x0
    str r0, [r6, #0x0]
    bl func_0203bd14
    mov r4, r0
    mov r0, r6
    bl func_0203be4c
    add r0, r0, #0x200
    str r0, [r4, #0x0]
    mov r0, r4
    bl func_0203c35c
    mov r0, #0x7000
    str r0, [r4, #0x508]
    ldr r0, =0x1ff
    bl MapVRAMBanksToLCDC
    mov r0, #0x0
    mov r1, #0x6800000
    mov r2, #0xa4000
    bl func_020ca458
    bl DisableLCDCMappedVRAMBanks
    bl Finish3DRendering
    bl func_020c51dc
    bl func_020c537c
    bl LockStagedTextureVRAMCopying
    mov r0, #0x1
    bl MapVRAMBanksToTextureImage
    mov r0, #0x1
    mov r1, r0
    bl func_020bb48c
    mov r0, #0x40
    bl MapVRAMBanksToTexturePalette
    mov r0, #0x4000
    mov r1, #0x1
    bl func_020bb780
    mov r0, #0x10
    bl MapVRAMBanksToMainBG
    mov r0, #0x4
    bl MapVRAMBanksToSubBG
    mov r0, #0x20
    bl MapVRAMBanksToMainObj
    mov r2, #0x4000000
    ldr r1, [r2, #0x0]
    ldr r0, =0xffcfffef
    and r0, r1, r0
    orr r0, r0, #0x10
    str r0, [r2, #0x0]
    mov r0, #0x8
    bl MapVRAMBanksToSubObj
    ldr r2, =0x4001000
    ldr r0, =0xffcfffef
    ldr r1, [r2, #0x0]
    and r0, r1, r0
    orr r0, r0, #0x10
    str r0, [r2, #0x0]
    bl UpdateVRAMStagingVRAMBanks
    bl UnlockStagedTextureVRAMCopying
    mov r2, #0x4000000
    ldr r1, [r2, #0x0]
    mov r0, #0x1
    bic r1, r1, #0x1f00
    orr r1, r1, #0x1f00
    str r1, [r2, #0x0]
    mov r2, r0
    mov r1, #0x0
    bl func_020c391c
    ldr r1, =0x400000a
    ldr r0, =0x1e08
    ldrh r3, [r1, #0x0]
    add r2, r0, #0x104
    sub r4, r1, #0x2
    and r0, r3, #0x43
    orr r0, r0, #0x1d00
    strh r0, [r1, #0x0]
    ldrh r6, [r1, #0x2]
    ldr r3, =0x4001000
    mov r0, #0x0
    and r6, r6, #0x43
    orr r6, r6, #0x208
    orr r6, r6, #0x1c00
    strh r6, [r1, #0x2]
    ldrh r6, [r1, #0x4]
    and r6, r6, #0x43
    orr r2, r6, r2
    strh r2, [r1, #0x4]
    ldrh r2, [r4, #0x0]
    bic r2, r2, #0x3
    orr r2, r2, #0x2
    strh r2, [r4, #0x0]
    ldrh r2, [r1, #0x0]
    bic r2, r2, #0x3
    orr r2, r2, #0x3
    strh r2, [r1, #0x0]
    ldrh r2, [r1, #0x2]
    bic r2, r2, #0x3
    orr r2, r2, #0x1
    strh r2, [r1, #0x2]
    ldrh r2, [r1, #0x4]
    bic r2, r2, #0x3
    strh r2, [r1, #0x4]
    ldr r1, [r3, #0x0]
    bic r1, r1, #0x1f00
    orr r1, r1, #0x1700
    str r1, [r3, #0x0]
    bl func_020c3984
    ldr r4, =0x4001008
    ldr r0, =0x1e10
    ldrh r1, [r4, #0x0]
    add r0, r0, #0x108
    and r1, r1, #0x43
    orr r1, r1, #0x1d00
    strh r1, [r4, #0x0]
    ldrh r1, [r4, #0x2]
    and r1, r1, #0x43
    orr r1, r1, #0xe10
    orr r1, r1, #0x1000
    strh r1, [r4, #0x2]
    ldrh r1, [r4, #0x4]
    and r1, r1, #0x43
    orr r0, r1, r0
    strh r0, [r4, #0x4]
    ldrh r1, [r4, #0x0]
    ldr r6, =0x4000304
    mov r0, #0x0
    bic r1, r1, #0x3
    orr r1, r1, #0x2
    strh r1, [r4, #0x0]
    ldrh r3, [r4, #0x2]
    ldr r2, =0x7fff
    mov r1, r0
    bic r3, r3, #0x3
    orr r3, r3, #0x1
    strh r3, [r4, #0x2]
    ldrh r8, [r4, #0x4]
    mov r3, r0
    bic r8, r8, #0x3
    strh r8, [r4, #0x4]
    ldrh r8, [r4, #0x6]
    bic r8, r8, #0x3
    orr r8, r8, #0x3
    strh r8, [r4, #0x6]
    ldrh r4, [r6, #0x0]
    orr r4, r4, #0x8000
    strh r4, [r6, #0x0]
    str r0, [sp, #0x0]
    bl func_020c5588
    ldr r3, =sEdgeColors
    add r2, sp, #0x4
    mov r1, #0x8
@L0218b8a8:
    ldrh r0, [r3], #0x2
    subs r1, r1, #0x1
    strh r0, [r2], #0x2
    bne @L0218b8a8
    add r0, sp, #0x4
    bl func_020c555c
    add r0, r7, #0x44
    mov r1, #0x4000
    mov r2, #0x40
    bl func_0207de48
    bl func_020421a0
    mov r6, r0
    bl func_02042c68
    mov r0, r6
    bl func_02043124
    mov r0, r6
    bl func_020440a4
    add r0, r7, #0x44
    add r1, r6, #0x1000
    str r0, [r1, #0xe28]
    bl func_0207df50
    add r0, r7, #0x44
    bl func_0207df90
    mov r0, r6
    bl func_020432c4
    add r0, r7, #0x44
    bl func_0207dfac
    mov r0, r5
    mov r1, #0x0
    bl func_020100a0
    ldr r0, =data_02114e20
    ldr r1, =0x4b238
    bl func_02012d88
    mov r1, r0
    ldr r2, =0x4b238
    add r0, r7, #0x2c
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    add r0, r7, #0x2c
    bl _ZN13SafeAllocator5ResetEv
    ldr r1, =0xdb8
    add r0, r7, #0x2c
    bl _ZN13SafeAllocator8AllocateEj
    mov r1, #0x0
    mov r2, r1
    str r0, [r7, #0x40]
    bl func_ov009_0218454c
    mov r0, r5
    bl func_02010954
    str r0, [r7, #0xb4]
    mov r0, r5
    bl func_020100a8
    ldr r2, [r7, #0xb4]
    add r1, r7, #0x2c
    add r2, r2, #0x500
    strh r0, [r2, #0x68]
    ldr r2, [r7, #0xb4]
    ldr r0, [r7, #0x40]
    str r2, [r0, #0xd88]
    ldr r0, [r7, #0x40]
    bl func_ov009_021842a0
    ldr r0, =data_02109bf4
    mov r1, #0x2
    bl func_0209c3b4
    bl func_020c9820
    bl func_020c38d4
    ldr r2, =0x4001000
    mov r0, r5
    ldr r1, [r2, #0x0]
    orr r1, r1, #0x10000
    str r1, [r2, #0x0]
    bl func_02010124
    ldr r10, =0x411b
    ldr r8, =data_02114e50
    mov r4, #0x1
    mov r9, #0x0
@L0218b9d4:
    mov r0, r5
    bl func_0200fb9c
    cmp r0, #0x0
    beq @L0218ba48
    ldr r0, [r7, #0xb8]
    cmp r0, #0x0
    bne @L0218ba48
    bl func_02012efc
    mov r0, r7
    bl _ZN22CharacterCreationScene6UpdateEv
    mov r0, r7
    bl _ZN22CharacterCreationScene4DrawEv
    strb r4, [r7, #0x28]
    bl func_020c9820
    bl func_020bbcb4
    ldr r0, [r7, #0x40]
    bl func_ov009_02184ca4
    bl func_0203bd08
    bl func_0203bdb0
    mov r0, r7
    bl UpdateAndApplyBrightness
    ldr r1, [r8, #0x0]
    mov r0, r5
    add r1, r1, #0x1
    str r1, [r8, #0x0]
    mov r1, r10
    mov r2, r9
    bl _ZN9GameState18CalculateDeltaTimeEy
    b @L0218b9d4
@L0218ba48:
    ldr r0, [r7, #0x40]
    bl func_ov009_02184848
    ldr r0, =data_02109bf4
    mov r1, #0x0
    bl func_0209c678
    mov r1, #0x0
    ldr r0, =data_02109bf4
    mov r2, r1
    bl func_0203ad88
    ldr r0, =data_02109bf4
    bl func_0203aa08
    ldr r0, =data_02109bf4
    bl func_0209c20c
    mov r0, r6
    bl func_02043000
    add r0, r7, #0x44
    bl func_0207df50
    mov r0, r5
    mov r1, #0x0
    bl func_0200fb84
    mov r0, #0x1
    bl func_020a1e54
    add sp, sp, #0x14
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif

void CharacterCreationScene::Update()
{
    BackgroundLoader::GetInstance()->RemoveAllLocks();
    if (func_ov009_02184a18(creation_))
    {
        done_ = 1;
    }
    func_0203aa08(data_02108760);
    func_020bbd9c();
}

void CharacterCreationScene::Draw()
{
    void* camera = func_020100bc(GameState::GetInstance());
    func_020c52e8();
    func_020c5414();
    DISP3DCNT = (DISP3DCNT & ~0x3000) | 0x8;
    DISP3DCNT = (DISP3DCNT & ~0x3000) | 0x10;
    DISP3DCNT = (DISP3DCNT & ~0x3000) | 0x20;
    if (camera != NULL)
    {
        func_0202e0a4(camera);
    }
    RenderConfig::SubmitToFifo();
    SendQueuedDataToGeometryFifo();
    func_ov009_02184c30(creation_);
    func_ov009_02184bbc(creation_);
    func_0203bd88(func_0203bd08());
    func_020d86d0(1, 0);
}
