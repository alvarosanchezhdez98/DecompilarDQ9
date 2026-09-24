#include "Scene/Overlay_19/SaveErrorScreen.h"
#include "Filesystem/BackgroundLoader.h"
#include "Filesystem/FileIO.h"
#include "Filesystem/NarcHandle.h"
#include "GameState/GameState.h"
#include "Graphics/NSBXX/GeometryFifo.h"
#include "Graphics/NSBXX/RenderConfig.h"
#include "Graphics/VRAMStaging.h"
#include "Resource/Brightness.h"
#include "Resource/GameResources.h"
#include "System/Graphics.h"
#include "System/Timing.h"
#include "System/VRAM.h"
#include "Text/MessageSystem.h"
#include <globaldefs.h>

#define REG_MASTER_BRIGHT ((volatile unsigned short*)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((volatile unsigned short*)0x0400106c)
#define GXFIFO_VIEWPORT (*(volatile unsigned int*)0x04000580)

// The buttons that close a message: A, B, the + Control Pad, R, L and X
#define ANY_BUTTON 0x7f3

extern "C"
{
    // The game's heap
    extern AllocatorUnion data_02114e20;
    // The buttons
    extern char data_02114e30[];
    // *Likely* the touch screen
    extern unsigned char data_02114e54[];
    // The sound player
    extern char data_02108760[];
    extern char data_02109bf4[];

    // Sets the game's resources
    void func_0200fb84(GameState* gameState, GameResources* resources);
    void func_0200fb94(GameState* gameState, int);
    void func_02012010(GameState* gameState, int);
    // Returns whether one of the buttons was just pressed
    bool func_02012444(void* pad, int buttons);
    void* func_02012d88(AllocatorUnion* allocator, unsigned int size);
    void func_02012da4(AllocatorUnion* allocator, void* data);
    void func_02012efc();
    void func_0202ad30();
    void func_0202adf0();
    void func_0203b628();
    void func_0203b634();
    void* func_0203bd08();
    void func_0203bd24();
    void func_0203bd88(void*);
    void func_0203bdb0(void*);
    MessageSystem* func_020421a0();
    void func_02042b30(MessageSystem* messages, void*);
    void func_02042c68();
    void func_02043124(MessageSystem* messages);
    void func_020432c4(MessageSystem* messages);
    void func_02043368(MessageSystem* messages);
    void func_0204359c(MessageSystem* messages, int);
    void func_020439b0(MessageSystem* messages, int);
    void func_020440b8(MessageSystem* messages, SafeAllocator* allocator, void* file);
    void func_020444d4(MessageSystem* messages, int);
    void func_020444e0(MessageSystem* messages);
    // Shows a message
    void func_0204500c(MessageSystem* messages, const char* text, int, int);
    // The answer to the question of the message
    int func_020457e0(MessageSystem* messages);
    void func_020466e4(void*, int);
    void func_020466f4(void*, int);
    // Returns a file of a .pac file
    void* func_020467f0(void* pac, int index, void** outName, unsigned int* outSize);
    // Returns the number of files in a .pac file
    int func_02046900(void* pac);
    // Initializes a sprite
    void func_0205a198(Sprite* sprite);
    void func_0205a234(SpriteAnimationList* list);
    void func_0205a330(SpriteAnimationList* list, int ticks);
    void func_0205a370(SpriteAnimationList* list, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* list, int index);
    void func_0205a42c(SpriteAnimationList* list, int, int);
    // Initializes a sprite renderer
    void func_0205a444(SpriteRenderer* renderer);
    // Adds the sprite cells of a file to a sprite renderer
    void func_0205a528(SpriteRenderer* renderer, void* file, unsigned int size, SafeAllocator* allocator);
    void func_0205ae8c(SpriteRenderer* renderer);
    // Plays a sound effect
    void func_0205eaa0(void* player, int, int);
    void func_0207de48(void*, int, int);
    void func_0207df50(void*);
    void func_0207df90(void*);
    void func_0207dfac(void*);
    void func_0209c6d8(void*, int);
    void func_020a9ea4(void*);
    int func_020ab7a8(void*, int);
    int func_020aba5c(int);
    void func_020bb48c(int, int);
    void func_020bb780(int, int);
    void func_020bbcb4();
    // NNS_SndMain
    void func_020bbd9c();
    // GX_DispOn
    void func_020c38d4();
    // GX_SetGraphicsMode
    void func_020c391c(int mode, int bgMode, int bg0Is3D);
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
    // G3X_SetClearColor
    void func_020c5588(int color, int alpha, int depth, int polygonID, int fog);
    // G3i_OrthoW_
    void func_020c5770(fix32_t top, fix32_t bottom, fix32_t left, fix32_t right, fix32_t near, fix32_t far,
                       fix32_t scaleW, int draw, void* matrix);
    // G3i_LookAt_
    void func_020c57d4(const Vector3fix* camera, const Vector3fix* up, const Vector3fix* target, int draw,
                       void* matrix);
    // OS_WaitVBlankIntr
    void func_020c9820();
    void* func_020d6c00();
    void func_020d86d0(int, int);
    void func_020daf9c(int, int, int, int);
    void func_020dfc40(TextTable* texts);
    void func_020dfec0(TextTable* texts, SafeAllocator* allocator, void* file, unsigned int size);
    const char* func_020e0434(TextTable* texts, int id);
}

const unsigned int SaveErrorScreen::sBufferSize = 0x19000;

void SaveErrorScreen::Initialize()
{
}

void SaveErrorScreen::Finish()
{
}

// NONMATCHING: the C matches 96.4 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Like CharacterCreationScene::Run (overlay 21), the compiler gives other registers to the temporaries of some register
// writes (the OBJ VRAM mode and POWCNT, BG0CNT before G3X_SetClearColor) and of the sprite renderer's setup, so it
// schedules the instructions around them differently. It also turns the multiplication by 64 of the ticks into shifts
// (or folds it with the one by 1000, as overlay 17 has it), while the original multiplies. Neither the types, the
// expressions' forms, optimization pragmas and flags nor other compiler versions change it.
#ifdef NONMATCHING
void SaveErrorScreen::Run()
{
    char unknown0[0x70];
    char unknown1[0x70];
    NarcHandle narc;
    unsigned int size;

    GameState* gameState = GameState::GetInstance();
    BackgroundLoader* loader = BackgroundLoader::GetInstance();
    void* unknown = func_020d6c00();
    func_020daf9c(0, 0, 1, 0);
    flags_ = 0;
    penStep_ = 0;
    func_0205a444(&spriteRenderer_);
    for (int i = 0; i < 14; i++)
    {
        func_0205a198(&sprites_[i]);
    }
    func_0205a234(&animations_);
    func_020c39a0(REG_MASTER_BRIGHT, -16);
    func_020c39a0(REG_MASTER_BRIGHT_SUB, -16);
    func_0200fb84(gameState, (GameResources*)this);
    loader->MaybeReset();
    func_0203b628();
    func_0203b634();
    void* unknown2 = func_0203bd08();
    func_0203bd24();

    LockStagedTextureVRAMCopying();
    DisableTextureImageVRAMBanks();
    DisableTexturePaletteVRAMBanks();
    DisableMainBGVRAMBanks();
    DisableSubBGVRAMBanks();
    DisableMainObjVRAMBanks();
    DisableSubObjVRAMBanks();
    MapVRAMBanksToTextureImage(0xf);
    func_020bb48c(4, 1);
    MapVRAMBanksToTexturePalette(0x40);
    MapVRAMBanksToMainBG(0x10);
    DISPCNT &= ~0x7000000;
    DISPCNT &= ~0x38000000;
    BG1CNT = (BG1CNT & (BGCNT_MASK_PRIORITY | BGCNT_MASK_MOSAIC)) | 4;
    DISPCNT = (DISPCNT & ~0x1f00) | 0x1100;
    func_020c391c(1, 0, 1);
    MapVRAMBanksToMainObj(0x20);
    DISPCNT = (DISPCNT & ~0x300010) | 0x10;
    POWCNT &= ~0x8000;
    UpdateVRAMStagingVRAMBanks();
    UnlockStagedTextureVRAMCopying();

    Finish3DRendering();
    func_020c51dc();
    func_020c537c();
    BG0CNT = (BG0CNT & ~BGCNT_MASK_PRIORITY) | 0;
    func_020c5588(0, 0x1f, 0x7fff, 0, 0);
    func_020c5770(0, 0xc0000, 0, 0x100000, -0x400000, 0x400000, 0x400000, 1, NULL);
    GXFIFO_MATRIX_STORE = 0;
    GXFIFO_VIEWPORT = 0xbfff0000;
    func_020bb48c(4, 1);
    func_020bb780(0x4000, 1);

    func_0207de48(unknown0, 0x4000, 0x20);
    func_0207de48(unknown1, 0x4000, 0x20);
    MessageSystem* messages = func_020421a0();
    func_02042c68();
    func_02043124(messages);
    func_02042b30(messages, unknown0);
    func_0207df50(unknown0);
    func_0207df90(unknown0);
    func_020432c4(messages);
    func_0207dfac(unknown0);

    BackgroundLoader::AddLockGlobal();
    if (!LoadFileIntoMemory("data/bin/icon.nsarc", data_0211e33c, &size))
    {
        BackgroundLoader::RemoveLockGlobal();
        return;
    }
    void* buffer = func_02012d88(&data_02114e20, sBufferSize);
    SafeAllocator allocator;
    allocator.CreateTypeA(buffer, sBufferSize);
    if (narc.Initialize("ARC", data_0211e33c))
    {
        func_0207df90(unknown1);
        func_020440b8(messages, &allocator, data_0211e33c);
        func_0207dfac(unknown1);
        narc.Destroy();
    }
    func_0202ad30();
    func_0202adf0();
    messages->unk_2d8 = 0;
    void* file = ExtractFileFromGP2("data/bin/str_err.gp2", "str_err_<LG>.nat", &size);
    if (file == NULL)
    {
        BackgroundLoader::RemoveLockGlobal();
        return;
    }
    func_020dfc40(&texts_);
    func_020dfec0(&texts_, &allocator, file, size);
    BackgroundLoader::RemoveLockGlobal();

    int state = State_Idle;
    if (gameState->saveError_ == 0)
    {
        func_0204500c(messages, func_020e0434(&texts_, 0), 0, 0xe3);
    }
    else if (gameState->saveError_ == 1)
    {
        func_0204500c(messages, func_020e0434(&texts_, 1), 0, 0xe3);
    }
    else if (gameState->saveError_ == 2)
    {
        func_0204500c(messages, func_020e0434(&texts_, 2), 0, 0xe3);
        state = State_Ask;
    }
    else if (gameState->saveError_ == 4)
    {
        func_0204500c(messages, func_020e0434(&texts_, 10), 0, 0xe3);
    }
    else
    {
        func_0204500c(messages, func_020e0434(&texts_, 8), 0, 0xe3);
        state = State_WaitForButton;
    }
    messages->busy_ = 1;
    func_020d86d0(0, 1);
    func_020c9820();
    func_020bbcb4();
    UnlockAndSetMainBrightness((GameResources*)this, 0, 5);
    UnlockAndSetSubBrightness((GameResources*)this, -16, 1);
    UpdateAndApplyBrightness((GameResources*)this);
    func_020c38d4();
    DISPCNTSUB |= 0x10000;

    Vector3fix target = { 0, 0, -0x1000 };
    Vector3fix camera = {};
    Vector3fix up = { 0, 0x1000, 0 };
    bool running = true;
    uint64_t start = GetCurrentTimestamp();
    while (true)
    {
        func_02012efc();
        switch (state)
        {
        case State_Ask:
            if (messages->busy_ == 0)
            {
                if (func_020457e0(messages) == 0)
                {
                    func_020466e4(unknown, 0x80);
                    func_0204500c(messages, func_020e0434(&texts_, 5), 0, 0xe3);
                    func_020a9ea4(unk_2c);
                    state = State_Delete;
                }
                else if (func_020457e0(messages) == 1)
                {
                    func_0204500c(messages, func_020e0434(&texts_, 3), 0, 0xe3);
                    state = State_AskAgain;
                }
                messages->busy_ = 1;
            }
            break;
        case State_AskAgain:
            if (messages->busy_ == 0)
            {
                if (func_020457e0(messages) == 0)
                {
                    func_0204500c(messages, func_020e0434(&texts_, 4), 0, 0xe3);
                    state = State_End;
                }
                else if (func_020457e0(messages) == 1)
                {
                    func_0204500c(messages, func_020e0434(&texts_, 2), 0, 0xe3);
                    state = State_Ask;
                }
                messages->busy_ = 1;
            }
            break;
        case State_Delete:
            if (messages->unk_9a0 == 4)
            {
                BackgroundLoader::AddLockGlobal();
                BackgroundLoader::FreeAllocationsGlobal();
                if (penStep_ == 0)
                {
                    if (!LoadFileIntoMemory("data/ani/pen.pac", data_0211e33c, &size))
                    {
                        BackgroundLoader::RemoveLockGlobal();
                        return;
                    }
                    func_0205a444(&spriteRenderer_);
                    for (int i = 0; i < 14; i++)
                    {
                        func_0205a198(&sprites_[i]);
                    }
                    func_0205a234(&animations_);
                    spriteRenderer_.unk_50 = 0;
                    spriteRenderer_.SetSprites(sprites_, 14);
                    spriteRenderer_.animations_ = &animations_;
                    int numFiles = func_02046900(data_0211e33c);
                    for (int i = 0; i < numFiles; i++)
                    {
                        void* name;
                        unsigned int cellsSize;
                        void* cells = func_020467f0(data_0211e33c, i, &name, &cellsSize);
                        func_0205a528(&spriteRenderer_, cells, cellsSize, &allocator);
                    }
                    flags_ |= 1;
                    penStep_++;
                }
                else if (penStep_ == 1)
                {
                    int result = func_020ab7a8(unk_2c, 1);
                    if (result == 1)
                    {
                        func_0204500c(messages, func_020e0434(&texts_, 0), 0, 0xe3);
                        messages->busy_ = 1;
                        func_020466f4(unknown, 0x80);
                        flags_ &= ~1;
                        state = State_Idle;
                    }
                    else if (result == 2)
                    {
                        func_0204500c(messages, func_020e0434(&texts_, 1), 0, 0xe3);
                        messages->busy_ = 1;
                        func_020466f4(unknown, 0x80);
                        flags_ &= ~1;
                        state = State_Idle;
                    }
                    else if (result == 3)
                    {
                        func_020466f4(unknown, 0x80);
                        state = State_DeleteFailed;
                    }
                    else if (result == 5)
                    {
                        func_020466f4(unknown, 0x80);
                        state = State_Deleted;
                    }
                    BackgroundLoader::RemoveLockGlobal();
                }
            }
            break;
        case State_Deleted:
            flags_ &= ~1;
            if (messages->busy_ == 0)
            {
                func_0204500c(messages, func_020e0434(&texts_, 7), 0, 0xe3);
                messages->busy_ = 1;
                func_0209c6d8(data_02109bf4, 0x35);
                state = State_EndAfterMessage;
            }
            break;
        case State_EndAfterMessage:
            if (messages->busy_ == 0)
            {
                running = false;
            }
            break;
        case State_DeleteFailed:
            flags_ &= ~1;
            if (messages->busy_ == 0)
            {
                if (gameState->saveError_ == 0)
                {
                    func_0204500c(messages, func_020e0434(&texts_, 0), 0, 0xe3);
                    state = State_Idle;
                }
                else
                {
                    func_0204500c(messages, func_020e0434(&texts_, 6), 0, 0xe3);
                    func_0209c6d8(data_02109bf4, 0x3d);
                    state = State_DeleteFailedEnd;
                }
                messages->busy_ = 1;
            }
            break;
        case State_DeleteFailedEnd:
            flags_ &= ~1;
            if (messages->busy_ == 0)
            {
                func_0204500c(messages, func_020e0434(&texts_, 4), 0, 0xe3);
                state = State_End;
                messages->busy_ = 1;
            }
            break;
        case State_End:
            if (messages->busy_ == 0)
            {
                running = false;
            }
            break;
        case State_WaitForButton:
            flags_ &= ~1;
            if (messages->unk_9a0 == 3 && WasButtonPressed())
            {
                if (func_020aba5c(1) == 0)
                {
                    func_0204500c(messages, func_020e0434(&texts_, 1), 0, 0xe3);
                    state = State_Idle;
                }
                else
                {
                    func_0204500c(messages, func_020e0434(&texts_, 9), 0, 0xe3);
                    state = State_End;
                }
            }
            break;
        }
        if (!running)
        {
            break;
        }

        UpdateAndApplyBrightness((GameResources*)this);
        loader->RemoveAllLocks();
        if (!(flags_ & 1))
        {
            func_02043368(messages);
        }
        if (messages->unk_9a0 != 3 && !(state == State_Delete && messages->unk_9a0 == 4))
        {
            func_020444d4(messages, 1);
        }
        func_020bbd9c();
        func_020c52e8();
        func_020c5414();
        RenderConfig::Reset();
        DISP3DCNT = (DISP3DCNT & ~0x3000) | 8;
        DISP3DCNT = (DISP3DCNT & ~0x3000) | 0x10;
        GXFIFO_MATRIX_MODE = 0;
        func_020c57d4(&camera, &up, &target, 1, NULL);
        func_020c5770(0, 0xc0000, 0, 0x100000, -0x400000, 0x400000, 0x400000, 1, NULL);
        GXFIFO_MATRIX_MODE = 2;
        func_020444e0(messages);
        DrawPen();
        func_0203bd88(unknown2);
        func_0204359c(messages, 0x10);
        func_020d86d0(0, 1);
        allowBrightnessApply = true;
        func_020c9820();
        func_0203bdb0(unknown2);
        func_020439b0(messages, 1);
        uint64_t now = GetCurrentTimestamp();
        uint64_t ticks = (now - start) * 64;
        gameState->CalculateDeltaTime(ticks * 1000 / TIMER_TICKS_PER_MILLISECOND);
        start = GetCurrentTimestamp();
    }

    allocator.Destroy();
    func_02012da4(&data_02114e20, buffer);
    func_0200fb94(gameState, 6);
    func_02012010(gameState, 0);
}
#else
// The constants and strings of the C above, which the compiler pools
static const Vector3fix sTarget = { 0, 0, -0x1000 };
static const Vector3fix sUp = { 0, 0x1000, 0 };
static char sStrings[] = "data/bin/icon.nsarc\0ARC\0data/bin/str_err.gp2\0str_err_<LG>.nat\0data/ani/pen.pac";

extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10NarcHandle10InitializeEPKcPKh(); // NarcHandle::Initialize
    void _ZN10NarcHandle7DestroyEv(); // NarcHandle::Destroy
    void _ZN12RenderConfig5ResetEv(); // RenderConfig::Reset
    void _ZN13SafeAllocator11CreateTypeAEPvj(); // SafeAllocator::CreateTypeA
    void _ZN13SafeAllocator21ResetAllocatorPointerEv(); // SafeAllocator::ResetAllocatorPointer
    void _ZN13SafeAllocator7DestroyEv(); // SafeAllocator::Destroy
    void _ZN16BackgroundLoader10MaybeResetEv(); // BackgroundLoader::MaybeReset
    void _ZN16BackgroundLoader11GetInstanceEv(); // BackgroundLoader::GetInstance
    void _ZN16BackgroundLoader13AddLockGlobalEv(); // BackgroundLoader::AddLockGlobal
    void _ZN16BackgroundLoader14RemoveAllLocksEv(); // BackgroundLoader::RemoveAllLocks
    void _ZN16BackgroundLoader16RemoveLockGlobalEv(); // BackgroundLoader::RemoveLockGlobal
    void _ZN16BackgroundLoader21FreeAllocationsGlobalEv(); // BackgroundLoader::FreeAllocationsGlobal
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZN9GameState18CalculateDeltaTimeEy(); // GameState::CalculateDeltaTime
    void _ZN15SaveErrorScreen7DrawPenEv(); // SaveErrorScreen::DrawPen
    void _ZN15SaveErrorScreen16WasButtonPressedEv(); // SaveErrorScreen::WasButtonPressed
    // The compiler's functions: zeroing memory (the objects initialized with = {}) and 64-bit division
    void __clear(void* dst, unsigned int size);
    void _ll_udiv();
}

asm void SaveErrorScreen::Run()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x1bc
    mov r4, r0
    bl _ZN9GameState11GetInstanceEv
    mov r5, r0
    bl _ZN16BackgroundLoader11GetInstanceEv
    str r0, [sp, #0x2c]
    bl func_020d6c00
    mov r10, r0
    mov r0, #0x0
    mov r1, r0
    mov r2, #0x1
    mov r3, r0
    bl func_020daf9c
    mov r0, #0x0
    str r0, [r4, #0x4c]
    str r0, [r4, #0x50]
    add r0, r4, #0x54
    bl func_0205a444
    mov r8, #0x0
    add r7, r4, #0xa8
    mov r6, #0x28
    b @L0218b610
@L0218b604:
    mla r0, r8, r6, r7
    bl func_0205a198
    add r8, r8, #0x1
@L0218b610:
    cmp r8, #0xe
    blt @L0218b604
    add r0, r4, #0x2d8
    bl func_0205a234
    ldr r0, =0x400006c
    mvn r1, #0xf
    bl func_020c39a0
    ldr r0, =0x400106c
    mvn r1, #0xf
    bl func_020c39a0
    mov r0, r5
    mov r1, r4
    bl func_0200fb84
    ldr r0, [sp, #0x2c]
    bl _ZN16BackgroundLoader10MaybeResetEv
    bl func_0203b628
    bl func_0203b634
    bl func_0203bd08
    str r0, [sp, #0x28]
    bl func_0203bd24
    bl LockStagedTextureVRAMCopying
    bl DisableTextureImageVRAMBanks
    bl DisableTexturePaletteVRAMBanks
    bl DisableMainBGVRAMBanks
    bl DisableSubBGVRAMBanks
    bl DisableMainObjVRAMBanks
    bl DisableSubObjVRAMBanks
    mov r0, #0xf
    bl MapVRAMBanksToTextureImage
    mov r0, #0x4
    mov r1, #0x1
    bl func_020bb48c
    mov r0, #0x40
    bl MapVRAMBanksToTexturePalette
    mov r0, #0x10
    bl MapVRAMBanksToMainBG
    mov r3, #0x4000000
    ldr r1, [r3, #0x0]
    mov r0, #0x1
    bic r1, r1, #0x7000000
    str r1, [r3, #0x0]
    ldr r2, [r3, #0x0]
    mov r1, #0x0
    bic r2, r2, #0x38000000
    str r2, [r3, #0x0]
    ldrh r6, [r3, #0xa]
    mov r2, r0
    and r6, r6, #0x43
    orr r6, r6, #0x4
    strh r6, [r3, #0xa]
    ldr r6, [r3, #0x0]
    bic r6, r6, #0x1f00
    orr r6, r6, #0x1100
    str r6, [r3, #0x0]
    bl func_020c391c
    mov r0, #0x20
    bl MapVRAMBanksToMainObj
    mov r2, #0x4000000
    ldr r1, [r2, #0x0]
    ldr r0, =0xffcfffef
    and r0, r1, r0
    orr r0, r0, #0x10
    str r0, [r2, #0x0]
    add r1, r2, #0x304
    ldrh r0, [r1, #0x0]
    bic r0, r0, #0x8000
    strh r0, [r1, #0x0]
    bl UpdateVRAMStagingVRAMBanks
    bl UnlockStagedTextureVRAMCopying
    bl Finish3DRendering
    bl func_020c51dc
    bl func_020c537c
    ldr r6, =0x4000008
    mov r0, #0x0
    ldrh r3, [r6, #0x0]
    ldr r2, =0x7fff
    mov r1, #0x1f
    bic r3, r3, #0x3
    strh r3, [r6, #0x0]
    mov r3, r0
    str r0, [sp, #0x0]
    bl func_020c5588
    mov r0, #0x400000
    rsb r0, r0, #0x0
    str r0, [sp, #0x0]
    mov r0, #0x400000
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    mov r0, #0x1
    str r0, [sp, #0xc]
    mov r0, #0x0
    mov r1, #0xc0000
    mov r2, r0
    mov r3, #0x100000
    str r0, [sp, #0x10]
    bl func_020c5770
    ldr r1, =0x400044c
    mov r2, #0x0
    ldr r0, =0xbfff0000
    str r2, [r1, #0x0]
    str r0, [r1, #0x134]
    mov r0, #0x4
    mov r1, #0x1
    bl func_020bb48c
    mov r0, #0x4000
    mov r1, #0x1
    bl func_020bb780
    add r0, sp, #0x14c
    mov r1, #0x4000
    mov r2, #0x20
    bl func_0207de48
    add r0, sp, #0xdc
    mov r1, #0x4000
    mov r2, #0x20
    bl func_0207de48
    bl func_020421a0
    mov r6, r0
    bl func_02042c68
    mov r0, r6
    bl func_02043124
    mov r0, r6
    add r1, sp, #0x14c
    bl func_02042b30
    add r0, sp, #0x14c
    bl func_0207df50
    add r0, sp, #0x14c
    bl func_0207df90
    mov r0, r6
    bl func_020432c4
    add r0, sp, #0x14c
    bl func_0207dfac
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    ldr r0, =sStrings
    ldr r1, =data_0211e33c
    add r2, sp, #0x38
    bl LoadFileIntoMemory
    cmp r0, #0x0
    bne @L0218b840
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    b @L0218c120
@L0218b840:
    ldr r0, =data_02114e20
    mov r1, #0x19000
    bl func_02012d88
    str r0, [sp, #0x24]
    add r0, sp, #0x60
    bl _ZN13SafeAllocator21ResetAllocatorPointerEv
    ldr r1, [sp, #0x24]
    add r0, sp, #0x60
    mov r2, #0x19000
    bl _ZN13SafeAllocator11CreateTypeAEPvj
    ldr r1, =sStrings+0x14
    ldr r2, =data_0211e33c
    add r0, sp, #0x74
    bl _ZN10NarcHandle10InitializeEPKcPKh
    cmp r0, #0x0
    beq @L0218b8a8
    add r0, sp, #0xdc
    bl func_0207df90
    ldr r2, =data_0211e33c
    add r1, sp, #0x60
    mov r0, r6
    bl func_020440b8
    add r0, sp, #0xdc
    bl func_0207dfac
    add r0, sp, #0x74
    bl _ZN10NarcHandle7DestroyEv
@L0218b8a8:
    bl func_0202ad30
    bl func_0202adf0
    mov r0, #0x0
    str r0, [r6, #0x2d8]
    ldr r0, =sStrings+0x18
    ldr r1, =sStrings+0x2d
    add r2, sp, #0x38
    bl ExtractFileFromGP2
    movs r7, r0
    bne @L0218b8d8
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    b @L0218c120
@L0218b8d8:
    add r0, r4, #0x34
    bl func_020dfc40
    ldr r3, [sp, #0x38]
    add r1, sp, #0x60
    mov r2, r7
    add r0, r4, #0x34
    bl func_020dfec0
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    add r0, r5, #0x5000
    ldrb r0, [r0, #0xcc8]
    mov r7, #0x0
    cmp r0, #0x0
    bne @L0218b930
    mov r1, r7
    add r0, r4, #0x34
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, r7
    mov r3, #0xe3
    bl func_0204500c
    b @L0218b9d8
@L0218b930:
    cmp r0, #0x1
    bne @L0218b95c
    add r0, r4, #0x34
    mov r1, #0x1
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, r7
    mov r3, #0xe3
    bl func_0204500c
    b @L0218b9d8
@L0218b95c:
    cmp r0, #0x2
    bne @L0218b98c
    add r0, r4, #0x34
    mov r1, #0x2
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, r7
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x1
    b @L0218b9d8
@L0218b98c:
    cmp r0, #0x4
    add r0, r4, #0x34
    bne @L0218b9b8
    mov r1, #0xa
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, r7
    mov r3, #0xe3
    bl func_0204500c
    b @L0218b9d8
@L0218b9b8:
    mov r1, #0x8
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, r7
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x8
@L0218b9d8:
    mov r1, #0x1
    mov r0, #0x0
    str r1, [r6, #0x998]
    bl func_020d86d0
    bl func_020c9820
    bl func_020bbcb4
    mov r0, r4
    mov r1, #0x0
    mov r2, #0x5
    bl UnlockAndSetMainBrightness
    mov r0, r4
    mvn r1, #0xf
    mov r2, #0x1
    bl UnlockAndSetSubBrightness
    mov r0, r4
    bl UpdateAndApplyBrightness
    bl func_020c38d4
    ldr r2, =0x4001000
    ldr r0, =sTarget
    ldr r1, [r2, #0x0]
    add r3, sp, #0x54
    orr r1, r1, #0x10000
    str r1, [r2, #0x0]
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x48
    mov r1, #0xc
    bl __clear
    ldr r0, =sUp
    add r3, sp, #0x3c
    ldmia r0, {r0, r1, r2}
    mov r8, #0x1
    stmia r3, {r0, r1, r2}
    bl GetCurrentTimestamp
    str r0, [sp, #0x1c]
    str r1, [sp, #0x18]
@L0218ba68:
    bl func_02012efc
    cmp r7, #0x9
    addls pc, pc, r7, lsl #0x2
    b @L0218bf68
@L0218ba78:
    b @L0218bf68
    b @L0218baa0
    b @L0218bb38
    b @L0218bbbc
    b @L0218bda4
    b @L0218bdf8
    b @L0218be08
    b @L0218be90
    b @L0218bee8
    b @L0218bed8
@L0218baa0:
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218bf68
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x0
    bne @L0218baf8
    mov r0, r10
    mov r1, #0x80
    bl func_020466e4
    add r0, r4, #0x34
    mov r1, #0x5
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    add r0, r4, #0x2c
    bl func_020a9ea4
    mov r7, #0x3
    b @L0218bb2c
@L0218baf8:
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x1
    bne @L0218bb2c
    add r0, r4, #0x34
    mov r1, #0x3
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x2
@L0218bb2c:
    mov r0, #0x1
    str r0, [r6, #0x998]
    b @L0218bf68
@L0218bb38:
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218bf68
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x0
    bne @L0218bb7c
    add r0, r4, #0x34
    mov r1, #0x4
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x9
    b @L0218bbb0
@L0218bb7c:
    mov r0, r6
    bl func_020457e0
    cmp r0, #0x1
    bne @L0218bbb0
    add r0, r4, #0x34
    mov r1, #0x2
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x1
@L0218bbb0:
    mov r0, #0x1
    str r0, [r6, #0x998]
    b @L0218bf68
@L0218bbbc:
    ldr r0, [r6, #0x9a0]
    cmp r0, #0x4
    bne @L0218bf68
    bl _ZN16BackgroundLoader13AddLockGlobalEv
    bl _ZN16BackgroundLoader21FreeAllocationsGlobalEv
    ldr r0, [r4, #0x50]
    cmp r0, #0x0
    bne @L0218bcb4
    ldr r0, =sStrings+0x3e
    ldr r1, =data_0211e33c
    add r2, sp, #0x38
    bl LoadFileIntoMemory
    cmp r0, #0x0
    bne @L0218bbfc
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    b @L0218c120
@L0218bbfc:
    add r0, r4, #0x54
    bl func_0205a444
    mov r9, #0x0
    add r11, r4, #0xa8
    b @L0218bc20
@L0218bc10:
    mov r0, #0x28
    mla r0, r9, r0, r11
    bl func_0205a198
    add r9, r9, #0x1
@L0218bc20:
    cmp r9, #0xe
    blt @L0218bc10
    add r0, r4, #0x2d8
    bl func_0205a234
    mov r0, #0x0
    strb r0, [r4, #0xa4]
    add r0, r4, #0xa8
    str r0, [r4, #0x94]
    mov r0, #0xe
    strh r0, [r4, #0xa0]
    add r0, r4, #0x2d8
    str r0, [r4, #0x90]
    ldr r0, =data_0211e33c
    bl func_02046900
    mov r11, r0
    mov r9, #0x0
    b @L0218bc90
@L0218bc64:
    ldr r0, =data_0211e33c
    mov r1, r9
    add r2, sp, #0x34
    add r3, sp, #0x30
    bl func_020467f0
    mov r1, r0
    ldr r2, [sp, #0x30]
    add r0, r4, #0x54
    add r3, sp, #0x60
    bl func_0205a528
    add r9, r9, #0x1
@L0218bc90:
    cmp r9, r11
    blt @L0218bc64
    ldr r0, [r4, #0x4c]
    orr r0, r0, #0x1
    str r0, [r4, #0x4c]
    ldr r0, [r4, #0x50]
    add r0, r0, #0x1
    str r0, [r4, #0x50]
    b @L0218bf68
@L0218bcb4:
    cmp r0, #0x1
    bne @L0218bf68
    add r0, r4, #0x2c
    mov r1, #0x1
    bl func_020ab7a8
    cmp r0, #0x1
    bne @L0218bd18
    add r0, r4, #0x34
    mov r1, #0x0
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r0, #0x1
    str r0, [r6, #0x998]
    mov r0, r10
    mov r1, #0x80
    bl func_020466f4
    ldr r0, [r4, #0x4c]
    mov r7, #0x0
    bic r0, r0, #0x1
    str r0, [r4, #0x4c]
    b @L0218bd9c
@L0218bd18:
    cmp r0, #0x2
    bne @L0218bd68
    add r0, r4, #0x34
    mov r1, #0x1
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r0, #0x1
    str r0, [r6, #0x998]
    mov r0, r10
    mov r1, #0x80
    bl func_020466f4
    ldr r0, [r4, #0x4c]
    mov r7, #0x0
    bic r0, r0, #0x1
    str r0, [r4, #0x4c]
    b @L0218bd9c
@L0218bd68:
    cmp r0, #0x3
    bne @L0218bd84
    mov r0, r10
    mov r1, #0x80
    bl func_020466f4
    mov r7, #0x6
    b @L0218bd9c
@L0218bd84:
    cmp r0, #0x5
    bne @L0218bd9c
    mov r0, r10
    mov r1, #0x80
    bl func_020466f4
    mov r7, #0x4
@L0218bd9c:
    bl _ZN16BackgroundLoader16RemoveLockGlobalEv
    b @L0218bf68
@L0218bda4:
    ldr r0, [r4, #0x4c]
    bic r0, r0, #0x1
    str r0, [r4, #0x4c]
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218bf68
    add r0, r4, #0x34
    mov r1, #0x7
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r0, #0x1
    str r0, [r6, #0x998]
    ldr r0, =data_02109bf4
    mov r1, #0x35
    bl func_0209c6d8
    mov r7, #0x5
    b @L0218bf68
@L0218bdf8:
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    moveq r8, #0x0
    b @L0218bf68
@L0218be08:
    ldr r0, [r4, #0x4c]
    bic r0, r0, #0x1
    str r0, [r4, #0x4c]
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218bf68
    add r0, r5, #0x5000
    ldrb r0, [r0, #0xcc8]
    cmp r0, #0x0
    add r0, r4, #0x34
    bne @L0218be58
    mov r1, #0x0
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x0
    b @L0218be84
@L0218be58:
    mov r1, #0x6
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    ldr r0, =data_02109bf4
    mov r1, #0x3d
    bl func_0209c6d8
    mov r7, #0x7
@L0218be84:
    mov r0, #0x1
    str r0, [r6, #0x998]
    b @L0218bf68
@L0218be90:
    ldr r0, [r4, #0x4c]
    bic r0, r0, #0x1
    str r0, [r4, #0x4c]
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    bne @L0218bf68
    add r0, r4, #0x34
    mov r1, #0x4
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x9
    mov r0, #0x1
    str r0, [r6, #0x998]
    b @L0218bf68
@L0218bed8:
    ldr r0, [r6, #0x998]
    cmp r0, #0x0
    moveq r8, #0x0
    b @L0218bf68
@L0218bee8:
    ldr r0, [r4, #0x4c]
    bic r0, r0, #0x1
    str r0, [r4, #0x4c]
    ldr r0, [r6, #0x9a0]
    cmp r0, #0x3
    bne @L0218bf68
    mov r0, r4
    bl _ZN15SaveErrorScreen16WasButtonPressedEv
    cmp r0, #0x0
    beq @L0218bf68
    mov r0, #0x1
    bl func_020aba5c
    cmp r0, #0x0
    add r0, r4, #0x34
    bne @L0218bf48
    mov r1, #0x1
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x0
    b @L0218bf68
@L0218bf48:
    mov r1, #0x9
    bl func_020e0434
    mov r1, r0
    mov r0, r6
    mov r2, #0x0
    mov r3, #0xe3
    bl func_0204500c
    mov r7, #0x9
@L0218bf68:
    cmp r8, #0x0
    beq @L0218c0f4
    mov r0, r4
    bl UpdateAndApplyBrightness
    ldr r0, [sp, #0x2c]
    bl _ZN16BackgroundLoader14RemoveAllLocksEv
    ldr r0, [r4, #0x4c]
    tst r0, #0x1
    bne @L0218bf94
    mov r0, r6
    bl func_02043368
@L0218bf94:
    ldr r0, [r6, #0x9a0]
    cmp r0, #0x3
    beq @L0218bfb8
    cmp r7, #0x3
    cmpeq r0, #0x4
    beq @L0218bfb8
    mov r0, r6
    mov r1, #0x1
    bl func_020444d4
@L0218bfb8:
    bl func_020bbd9c
    bl func_020c52e8
    bl func_020c5414
    bl _ZN12RenderConfig5ResetEv
    ldr r9, =0x4000060
    mov r12, #0x0
    ldrh r2, [r9, #0x0]
    add r0, sp, #0x48
    add r1, sp, #0x3c
    bic r2, r2, #0x3000
    orr r2, r2, #0x8
    strh r2, [r9, #0x0]
    ldrh r11, [r9, #0x0]
    add r2, sp, #0x54
    mov r3, #0x1
    bic r11, r11, #0x3000
    orr r11, r11, #0x10
    strh r11, [r9, #0x0]
    str r12, [r9, #0x3e0]
    str r12, [sp, #0x0]
    bl func_020c57d4
    mov r0, #0x400000
    rsb r0, r0, #0x0
    str r0, [sp, #0x0]
    mov r0, #0x400000
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    mov r0, #0x1
    str r0, [sp, #0xc]
    mov r0, #0x0
    mov r1, #0xc0000
    mov r2, r0
    mov r3, #0x100000
    str r0, [sp, #0x10]
    bl func_020c5770
    mov r2, #0x2
    mov r0, r6
    str r2, [r9, #0x3e0]
    bl func_020444e0
    mov r0, r4
    bl _ZN15SaveErrorScreen7DrawPenEv
    ldr r0, [sp, #0x28]
    bl func_0203bd88
    mov r0, r6
    mov r1, #0x10
    bl func_0204359c
    mov r0, #0x0
    mov r1, #0x1
    bl func_020d86d0
    mov r0, #0x1
    strb r0, [r4, #0x28]
    bl func_020c9820
    ldr r0, [sp, #0x28]
    bl func_0203bdb0
    mov r0, r6
    mov r1, #0x1
    bl func_020439b0
    bl GetCurrentTimestamp
    ldr r2, [sp, #0x1c]
    mov r3, #0x0
    subs r0, r0, r2
    ldr r2, [sp, #0x18]
    sbc r11, r1, r2
    mov r1, #0x40
    umull r9, r2, r0, r1
    mla r2, r11, r1, r2
    mov r11, #0x3e8
    umull r0, r1, r9, r11
    mla r1, r2, r11, r1
    ldr r2, =0x82ea
    bl _ll_udiv
    mov r2, r1
    mov r1, r0
    mov r0, r5
    bl _ZN9GameState18CalculateDeltaTimeEy
    bl GetCurrentTimestamp
    str r0, [sp, #0x1c]
    str r1, [sp, #0x18]
    b @L0218ba68
@L0218c0f4:
    add r0, sp, #0x60
    bl _ZN13SafeAllocator7DestroyEv
    ldr r0, =data_02114e20
    ldr r1, [sp, #0x24]
    bl func_02012da4
    mov r0, r5
    mov r1, #0x6
    bl func_0200fb94
    mov r0, r5
    mov r1, #0x0
    bl func_02012010
@L0218c120:
    add sp, sp, #0x1bc
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void SaveErrorScreen::DrawPen()
{
    GameState* gameState = GameState::GetInstance();
    if (flags_ & 1)
    {
        SpriteAnimationList* animations = spriteRenderer_.animations_;
        if (animations != NULL)
        {
            func_0205a370(animations, 1);
            SpriteAnimation* animation = func_0205a3d0(animations, 1);
            if (animation != NULL)
            {
                animation->flags_ |= 8;
            }
            func_0205a330(animations, gameState->GetTickCount());
            animation = func_0205a3d0(animations, 1);
            if (animation != NULL)
            {
                animation->x_ = 0xd7;
                animation->y_ = 0x96;
            }
            func_0205a42c(animations, 1, 0x24);
        }
        func_0205ae8c(&spriteRenderer_);
    }
    else
    {
        SpriteAnimationList* animations = spriteRenderer_.animations_;
        if (animations != NULL)
        {
            SpriteAnimation* animation = func_0205a3d0(animations, 1);
            if (animation != NULL)
            {
                animation->flags_ &= ~8;
            }
        }
    }
}

bool SaveErrorScreen::WasButtonPressed()
{
    if (!func_02012444(data_02114e30, ANY_BUTTON) && data_02114e54[0x55] == 0)
    {
        return false;
    }
    func_0205eaa0(data_02108760, 1, 0);
    return true;
}
