// The part of overlay 9's creation of a character that overlay 23 has: its windows, the tiles of its backgrounds, its
// sprites and its fade
#include "Scene/Overlay_9/CharacterCreation.h"
#include "GameState/GameState.h"
#include "System/ColorEffects.h"
#include <std_library_functions.h>

#define REG_BLDCNT 0x04000050
// The geometry engine's commands
#define REG_MTX_TRANS (*(volatile unsigned int*)0x04000470)
#define REG_MTX_SCALE (*(volatile unsigned int*)0x0400046c)
#define REG_MTX_PUSH (*(volatile unsigned int*)0x04000444)
#define REG_MTX_POP (*(volatile unsigned int*)0x04000448)
#define REG_COLOR (*(volatile unsigned int*)0x04000480)
#define REG_VTX_16 (*(volatile unsigned int*)0x0400048c)
#define REG_POLYGON_ATTR (*(volatile unsigned int*)0x040004a4)
#define REG_TEXIMAGE_PARAM (*(volatile unsigned int*)0x040004a8)
#define REG_BEGIN_VTXS (*(volatile unsigned int*)0x04000500)
#define REG_END_VTXS (*(volatile unsigned int*)0x04000504)

extern "C"
{
    void __clear(void* buffer, unsigned long size);
    // The runtime's signed division, for the assembly
    void _s32_div_f();

    int func_0200fb08(GameState* gameState);
    void func_02041a28(char* text, int x);
    void func_02041b70(char* text, int item, const char* itemText);
    void func_02041bac(char* text, int, int, int, int, int);
    void func_02041c08(char* text, int, int, int, int, int);
    void func_02041e70(char* text, int color);
    void func_02041ea4(char* text, int);
    void func_02042058(char* text, const char* append);
    int func_020420e8(const char* text, int large);
    // Converts a text to the codes of its characters, and returns their count
    int func_020426bc(const char* text, char* codes, int);
    void func_02042764(const char* codes, char* text, int);
    void func_0204b010(BackgroundGraphics* background, int);
    void func_0204b04c(BackgroundGraphics* background, int);
    void func_0204b8d0(BackgroundGraphics* background, int, int, int, int, int, int, int, int);
    void func_0204b9b8(BackgroundGraphics* background, int x, int y, int width, int height, int);
    int func_0204c7e0(Canvas* canvas);
    void func_0205a330(SpriteAnimationList* list, int ticks);
    void func_0205a370(SpriteAnimationList* list, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* list, int index);
    void func_0205a42c(SpriteAnimationList* list, int, int);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205ae8c(SpriteRenderer* renderer);
    int func_0205bafc(WindowCursor* cursor);
    void func_0205d304(TextWindow* window, char* text, int, int, int, int, int, int);
    void func_0205d5d0(TextWindow* window, int, char* text, int, int);
    Canvas* func_0205d81c(TextWindow* window, int canvas);
    const char* func_020e0434(TextTable* texts, short id);
    void func_020e27ec(SpriteAnimationList* list, int, int x, int y);
    void func_ov003_0215ec68(int size, short* width, short* height);

    // The touch screen
    extern TouchState data_02114e54;
}

// A window's frame (the original computes its address apart from its fields', as with an inline function like this)
static inline WindowFrame* GetFrame(TextWindow* window)
{
    return (WindowFrame*)((char*)window + 4);
}

void CharacterCreation::OpenStateWindow()
{
    GameState* gameState = GameState::GetInstance();
    short unk = 0x18;
    if (func_0200fb08(gameState) == 4)
        unk = 0x19;
    TextWindow* window = &windows_[0];
    window->width_ = 7;
    window->height_ = 0x11;
    window->unk_a4 = unk;
    window->unk_a6 = 5;
    window->unk_a8 = 6;
    window->unk_aa = 6;
    window->unk_ac = 0xa;
    window->unk_ae = 0x10;
    window->unk_b1 = 0;
    window->unk_b5 = 1;
    window->unk_b6 = 1;
    char* text = (char*)unk_f8;
    memset(text, 0, 0x960);
    sprintf(text, func_020e0434(&texts_, 0x4274));
    func_0205d304(window, text, 0, 0, 0, 0, 0, 0);
}

void CharacterCreation::UpdateStateWindow()
{
    if (flags_ & 0x100)
    {
        if (state_ >= 11)
        {
            flags_ &= ~0x100;
            return;
        }

        short ids[7];
        char* text = (char*)unk_f8;
        unsigned char sex = sex_;
        short base = sex * 100;
        ids[0] = base + 10000;
        ids[1] = bodyType_[sex] + 11000;
        ids[2] = base + 15000 + face_[sex];
        ids[3] = hairColor_[sex] + 16000;
        ids[4] = base + 12000 + hairStyle_[sex];
        ids[5] = eyeColor_[sex] + 14000;
        ids[6] = skinColor_[sex] + 13000;
        memset(text, 0, 0x960);
        for (int i = 0; i < lastStates_[sex_]; i++)
        {
            int color = 0xf;
            if (i == state_ - 1)
                color = 0xe;
            func_02041e70(text, color);
            if (i < 7)
            {
                short id = ids[i];
                func_02041a28(text, 0x32 - func_020420e8(func_020e0434(&texts_, id), 0));
                func_02042058(text, func_020e0434(&texts_, id));
                func_02042058(text, func_020e0434(&texts_, 0x4273));
            }
            else if (i == 7)
            {
                char* name = names_[sex_];
                if (*name != 0)
                {
                    func_02041a28(text, 0x32 - func_020420e8(name, 0));
                    func_02042058(text, name);
                }
                else
                {
                    func_02042058(text, func_020e0434(&texts_, 0x4274));
                }
            }
        }
        func_0205d5d0(&windows_[0], 0, text, 0, 0);
        flags_ &= ~0x100;
    }
}

void CharacterCreation::OpenChoiceWindow()
{
    TextWindow* window = &windows_[1];
    window->width_ = 0xd;
    window->height_ = 2;
    window->unk_a4 = 2;
    window->unk_a6 = 0x13;
    window->unk_a8 = 2;
    window->unk_aa = 2;
    window->unk_ac = 0xa;
    window->unk_ae = 0xc;
    window->unk_b1 = 2;
    window->unk_b7 = 0xa;
    window->unk_b5 = 1;
    window->unk_b6 = 1;
    char* text = (char*)unk_f8;
    memset(text, 0, 0x960);
    sprintf(text, func_020e0434(&texts_, 0x4274));
    func_0205d304(window, text, 0, 0, 0, 1, 0, 0);
}

void CharacterCreation::ClearChoiceWindow()
{
    if (!(flags_ & 0x4000))
        return;
    char* text = (char*)unk_f8;
    memset(text, 0, 0x960);
    func_02042058(text, func_020e0434(&texts_, 0x4274));
    func_0205d5d0(&windows_[1], 2, text, 1, 0);
    flags_ &= ~0x4000;
}

void CharacterCreation::OpenNameWindow()
{
    TextWindow* window = &windows_[1];
    window->width_ = 0xa;
    window->height_ = 2;
    window->unk_a4 = 0xb;
    window->unk_a6 = 4;
    window->unk_a8 = 0;
    window->unk_aa = 2;
    window->unk_ac = 0x11;
    window->unk_ae = 0x10;
    window->unk_b1 = 3;
    window->unk_b7 = 0xa;
    window->unk_b5 = 1;
    window->unk_b6 = 1;
    char* text = (char*)unk_f8;
    memset(text, 0, 0x960);
    sprintf(text, func_020e0434(&texts_, 0x4274));
    func_0205d304(window, text, 0, 0, 0, 0, 0, 0);
}

void CharacterCreation::UpdateNameWindow()
{
    if (flags_ & 0x8000)
    {
        char* text = (char*)unk_f8;
        memset(text, 0, 0x960);
        if (state_ == 8)
        {
            Canvas* canvas = func_0205d81c(&windows_[1], 3);
            canvas->unk_b8 = 0x11;
            canvas->unk_ba = 0x10;
            // The name, filled up to 8 characters with the placeholder
            char codes[0x80] = {0};
            char name[0x80] = {0};
            int length = func_020426bc(names_[sex_], codes, 0);
            for (; length < 8; length++)
                codes[length] = unk_db4;
            func_02042764(codes, name, 0);
            func_02041a28(text, (0x50 - func_020420e8(name, 0)) >> 1);
            func_02042058(text, name);
        }
        else
        {
            func_02042058(text, func_020e0434(&texts_, 0x4274));
        }
        func_0205d5d0(&windows_[1], 3, text, 0, 0);
        flags_ &= ~0x8000;
    }
}

void CharacterCreation::OpenConfirmWindow()
{
    selection_ = 0;
    func_0205ba68(&windows_[1].base_.frame_, 1, 2, 0);
    func_0205ba68(&windows_[1].base_.cursor_, 1, 2, 0);
    func_0205bacc(&windows_[1].base_.frame_, 2);
    func_0205bacc(&windows_[1].base_.cursor_, 2);
    windows_[1].base_.frame_.unk_4 = 1;
    windows_[1].base_.cursor_.unk_4 = 1;
    signed char selection = selection_;
    func_0205bcdc(&windows_[1].base_.frame_, selection);
    func_0205bb04(&windows_[1].base_.cursor_, selection);
    windows_[1].base_.unk_94 = 1;
    windows_[1].base_.unk_95 = 1;

    short unk = 0x10;
    switch (func_0200fb08(GameState::GetInstance()))
    {
    case 2:
        unk = 0xe;
        break;
    case 4:
        unk = 0x15;
        break;
    case 3:
        unk = 0xa;
        break;
    case 5:
        unk = 0x15;
        break;
    }
    TextWindow* window = &windows_[1];
    window->width_ = 6;
    window->height_ = 5;
    window->unk_a4 = 0x1a;
    window->unk_a6 = 0xa;
    window->unk_a8 = unk;
    window->unk_aa = 0;
    window->unk_ac = 0xc;
    window->unk_ae = 0x10;
    window->unk_b1 = 1;
    window->unk_b7 = 0xc;
    window->unk_b5 = 1;
    window->unk_b6 = 0;
    char* text = (char*)unk_f8;
    memset(text, 0, 0x960);
    WriteConfirmText(text, 0);
    func_0205d304(window, text, 0, 0, 0, 0, 0, 1);
}

void CharacterCreation::WriteConfirmText(char* text, int highlighted)
{
    if (text != NULL)
    {
        signed char selection = selection_;
        if (highlighted)
            func_02041c08(text, selection, 8, 5, 5, 5);
        func_02041ea4(text, selection);
        func_02041bac(text, 0, 0, 0, 0x30, 0x28);
        for (int i = 0; i < 2; i++)
        {
            func_02041b70(text, i, func_020e0434(&texts_, i + 0x465a));
            if (i != 1)
                func_02042058(text, func_020e0434(&texts_, 0x4273));
        }
    }
}

void CharacterCreation::UpdateConfirmWindow()
{
    unsigned char unk = unk_d85;
    if (unk != 0)
    {
        int highlighted = 0;
        if (unk == 2 && data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0)
        {
            WindowFrame* frame = GetFrame(&windows_[1]);
            if (frame->unk_30 < 0)
                return;
            highlighted = 1;
        }
        char* text = (char*)unk_f8;
        memset(text, 0, 0x960);
        WriteConfirmText(text, highlighted);
        func_0205d5d0(&windows_[1], 1, text, 0, 1);
    }
}

// The keyboard's backgrounds for its modes
struct KeyboardBackground
{
    // Without and with shift
    unsigned char backgrounds_[2];
    // The mode of the keyboard, until 0
    unsigned char mode_;
};

static const KeyboardBackground sKeyboardBackgrounds[] = {{{0, 1}, 1}, {{1, 0}, 2}, {{2, 0}, 4}, {{3, 0}, 8}, {{0, 0}, 0}};

// The choices of a state for each sex (the original computes their address apart, as with an inline function like this)
static inline unsigned char* GetChoices(unsigned char* choices)
{
    return (unsigned char*)((char*)choices + 0);
}

// NONMATCHING: the C matches 92.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void CharacterCreation::UpdateBackgrounds()
{
    if (flags_ & 0x1000)
    {
        func_0204b010(&backgrounds_[1], 0);
        signed char state = state_;
        if (state >= 1 && state <= 8)
        {
            short y;
            int width;
            short bottom;
            int height;
            y = (state - 1) * 2 + 1;
            width = 0xf;
            height = 0xa;
            bottom = y + 5;
            if (func_0200fb08(GameState::GetInstance()) == 4)
            {
                width = 0xe;
                height = 0xd;
            }
            func_0204b8d0(&backgrounds_[1], 0, 0, y, width, bottom, height, 2, 0xffff);
        }
        func_0204b04c(&backgrounds_[1], 0);
    }

    if (flags_ & 0x2000)
    {
        Keyboard* keyboard;
        func_0204b010(&backgrounds_[4], 0);
        signed char state = state_;
        if (state == 1)
        {
            int x, y;
            unsigned char sex = sex_;
            int flip = 0;
            if (sex == 0)
            {
                x = 7;
                y = 5;
            }
            else if (sex == 1)
            {
                flip = 1;
                x = 7;
                y = 0xb;
            }
            func_0204b8d0(&backgrounds_[4], flip, 0, 0, x, y, 0x12, 6, 0xffff);
        }
        else if (state == 2)
        {
            unsigned char* choices = GetChoices(bodyType_);
            unsigned char choice = choices[sex_];
            func_0204b8d0(&backgrounds_[4], choice, 0, 0, (short)(choice * 5 + 4), 5, 4, 9, 0xffff);
        }
        else if (state == 5)
        {
            func_0204b8d0(&backgrounds_[4], 0, 0, 0, 4, 5, 0x18, 9, 0xffff);
            unsigned char* choices = GetChoices(hairStyle_);
            unsigned char choice = choices[sex_];
            func_0204b9b8(&backgrounds_[4], (short)(choice % 5 * 5 + 4), (short)((choice / 5 + 1) * 5), 4, 4, 2);
        }
        else if (state == 3)
        {
            func_0204b8d0(&backgrounds_[4], 0, 0, 0, 4, 5, 0x18, 9, 0xffff);
            unsigned char* choices = GetChoices(face_);
            unsigned char choice = choices[sex_];
            func_0204b9b8(&backgrounds_[4], (short)(choice % 5 * 5 + 4), (short)((choice / 5 + 1) * 5), 4, 4, 2);
        }
        else if (state == 8)
        {
            if (flags_ & 0x400000)
            {
                func_0204b8d0(&backgrounds_[4], 3, 0, 0, 0, 0xe, 0x20, 0xa, 0xffff);
            }
            else
            {
                int i = 0;
                keyboard = keyboard_;
                unsigned char mode = keyboard->unk_1e;
                unsigned char shift = keyboard->unk_20;
                while (true)
                {
                    if (sKeyboardBackgrounds[i].mode_ == 0)
                        break;
                    if (mode & sKeyboardBackgrounds[i].mode_)
                    {
                        func_0204b8d0(&backgrounds_[3], sKeyboardBackgrounds[i].backgrounds_[shift], 0, 0, 0, 0, 0x20, 0x18,
                                      0xffff);
                        break;
                    }
                    i++;
                }
                func_0204b9b8(&backgrounds_[3], 2, 7, 0x1c, 0xc, 1);
                KeyboardKey* key = keyboard_->key_;
                if (key != NULL)
                {
                    short x = key->x_;
                    short y = key->y_;
                    short height, width;
                    func_ov003_0215ec68(key->size_, &width, &height);
                    func_0204b9b8(&backgrounds_[3], x >> 3, y >> 3, width >> 3, height >> 3, 0);
                }
            }
            func_0204b04c(&backgrounds_[3], 0);
        }
        else if (state == 9)
        {
            int unk = 0;
            if (mode_ == 0)
                unk = 1;
            func_0204b8d0(&backgrounds_[4], unk, 0, 0, 0, 0xe, 0x20, 0xa, 0xffff);
            func_0204b8d0(&backgrounds_[4], 2, 0, 0, 0x18, 9, 8, 7, 0xffff);
            func_0204b9b8(&backgrounds_[3], 2, 7, 0x1c, 0xc, 1);
            func_0204b04c(&backgrounds_[3], 0);
        }
        func_0204b04c(&backgrounds_[4], 0);
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void CharacterCreation::UpdateBackgrounds()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    sub sp, sp, #0x18
    mov r7, r0
    ldr r0, [r7, #0xd9c]
    tst r0, #0x1000
    beq @L021da320
    add r0, r7, #0x158
    mov r1, #0x0
    bl func_0204b010
    add r0, r7, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r0, #0x1
    blt @L021da314
    cmp r0, #0x8
    bgt @L021da314
    sub r0, r0, #0x1
    mov r0, r0, lsl #0x1
    add r0, r0, #0x1
    mov r0, r0, lsl #0x10
    mov r4, r0, asr #0x10
    add r0, r4, #0x5
    mov r0, r0, lsl #0x10
    mov r8, #0xf
    mov r10, #0xa
    mov r9, r0, asr #0x10
    bl _ZN9GameState11GetInstanceEv
    bl func_0200fb08
    cmp r0, #0x4
    mov r1, #0x0
    moveq r8, #0xe
    moveq r10, #0xd
    stmia sp, {r8, r9, r10}
    mov r0, #0x2
    str r0, [sp, #0xc]
    ldr r12, =0xffff
    mov r2, r1
    mov r3, r4
    add r0, r7, #0x158
    str r12, [sp, #0x10]
    bl func_0204b8d0
@L021da314:
    add r0, r7, #0x158
    mov r1, #0x0
    bl func_0204b04c
@L021da320:
    ldr r0, [r7, #0xd9c]
    tst r0, #0x2000
    beq @L021da75c
    add r0, r7, #0x1b8
    mov r1, #0x0
    bl func_0204b010
    add r0, r7, #0xc00
    ldrsb r0, [r0, #0x58]
    cmp r0, #0x1
    bne @L021da3a0
    ldrb r0, [r7, #0xda3]
    mov r1, #0x0
    cmp r0, #0x0
    moveq r5, #0x7
    moveq r6, #0x5
    beq @L021da370
    cmp r0, #0x1
    moveq r1, #0x1
    moveq r5, #0x7
    moveq r6, #0xb
@L021da370:
    stmia sp, {r5, r6}
    mov r0, #0x12
    mov r2, #0x0
    str r0, [sp, #0x8]
    mov r0, #0x6
    str r0, [sp, #0xc]
    ldr r4, =0xffff
    mov r3, r2
    add r0, r7, #0x1b8
    str r4, [sp, #0x10]
    bl func_0204b8d0
    b @L021da750
@L021da3a0:
    cmp r0, #0x2
    bne @L021da3fc
    ldrb r1, [r7, #0xda3]
    add r0, r7, #0x1a4
    add r0, r0, #0xc00
    ldrb r1, [r0, r1]
    mov r3, #0x5
    mov r2, #0x0
    add r0, r1, r1, lsl #0x2
    add r0, r0, #0x4
    mov r0, r0, lsl #0x10
    mov r0, r0, asr #0x10
    stmia sp, {r0, r3}
    mov r0, #0x4
    str r0, [sp, #0x8]
    mov r0, #0x9
    str r0, [sp, #0xc]
    ldr r4, =0xffff
    mov r3, r2
    add r0, r7, #0x1b8
    str r4, [sp, #0x10]
    bl func_0204b8d0
    b @L021da750
@L021da3fc:
    cmp r0, #0x5
    bne @L021da4a8
    mov r0, #0x4
    str r0, [sp, #0x0]
    mov r0, #0x5
    str r0, [sp, #0x4]
    mov r0, #0x18
    str r0, [sp, #0x8]
    mov r2, #0x9
    mov r1, #0x0
    str r2, [sp, #0xc]
    ldr r0, =0xffff
    mov r2, r1
    str r0, [sp, #0x10]
    mov r3, r1
    add r0, r7, #0x1b8
    bl func_0204b8d0
    add r0, r7, #0xa6
    ldrb r2, [r7, #0xda3]
    add r0, r0, #0xd00
    mov r1, #0x5
    ldrb r4, [r0, r2]
    mov r0, r4
    bl _s32_div_f
    mov r5, r1
    mov r0, r4
    mov r1, #0x5
    bl _s32_div_f
    add r0, r0, #0x1
    add r1, r5, r5, lsl #0x2
    add r0, r0, r0, lsl #0x2
    add r1, r1, #0x4
    mov r0, r0, lsl #0x10
    mov r3, #0x4
    mov r1, r1, lsl #0x10
    mov r2, r0, asr #0x10
    str r3, [sp, #0x0]
    mov r0, #0x2
    str r0, [sp, #0x4]
    mov r1, r1, asr #0x10
    add r0, r7, #0x1b8
    bl func_0204b9b8
    b @L021da750
@L021da4a8:
    cmp r0, #0x3
    bne @L021da554
    mov r0, #0x4
    str r0, [sp, #0x0]
    mov r0, #0x5
    str r0, [sp, #0x4]
    mov r0, #0x18
    str r0, [sp, #0x8]
    mov r2, #0x9
    mov r1, #0x0
    str r2, [sp, #0xc]
    ldr r0, =0xffff
    mov r2, r1
    str r0, [sp, #0x10]
    mov r3, r1
    add r0, r7, #0x1b8
    bl func_0204b8d0
    add r0, r7, #0x1ac
    ldrb r2, [r7, #0xda3]
    add r0, r0, #0xc00
    mov r1, #0x5
    ldrb r4, [r0, r2]
    mov r0, r4
    bl _s32_div_f
    mov r5, r1
    mov r0, r4
    mov r1, #0x5
    bl _s32_div_f
    add r0, r0, #0x1
    add r1, r5, r5, lsl #0x2
    add r0, r0, r0, lsl #0x2
    add r1, r1, #0x4
    mov r0, r0, lsl #0x10
    mov r3, #0x4
    mov r1, r1, lsl #0x10
    mov r2, r0, asr #0x10
    str r3, [sp, #0x0]
    mov r0, #0x2
    str r0, [sp, #0x4]
    mov r1, r1, asr #0x10
    add r0, r7, #0x1b8
    bl func_0204b9b8
    b @L021da750
@L021da554:
    cmp r0, #0x8
    bne @L021da69c
    ldr r0, [r7, #0xd9c]
    mov r2, #0x0
    tst r0, #0x400000
    beq @L021da5a4
    str r2, [sp, #0x0]
    mov r0, #0xe
    str r0, [sp, #0x4]
    mov r0, #0x20
    str r0, [sp, #0x8]
    mov r0, #0xa
    str r0, [sp, #0xc]
    ldr r4, =0xffff
    mov r3, r2
    add r0, r7, #0x1b8
    mov r1, #0x3
    str r4, [sp, #0x10]
    bl func_0204b8d0
    b @L021da68c
@L021da5a4:
    ldr r0, [r7, #0xc0]
    ldr r1, =sKeyboardBackgrounds+0x2
    ldrb r4, [r0, #0x1e]
    ldrb r5, [r0, #0x20]
@L021da5b4:
    add r3, r2, r2, lsl #0x1
    ldrb r0, [r1, r3]
    cmp r0, #0x0
    beq @L021da614
    tst r4, r0
    beq @L021da60c
    ldr r0, =sKeyboardBackgrounds
    mov r2, #0x0
    str r2, [sp, #0x0]
    add r0, r0, r3
    str r2, [sp, #0x4]
    mov r3, #0x20
    ldrb r1, [r5, r0]
    str r3, [sp, #0x8]
    mov r0, #0x18
    ldr r4, =0xffff
    str r0, [sp, #0xc]
    mov r3, r2
    add r0, r7, #0x198
    str r4, [sp, #0x10]
    bl func_0204b8d0
    b @L021da614
@L021da60c:
    add r2, r2, #0x1
    b @L021da5b4
@L021da614:
    mov r0, #0xc
    str r0, [sp, #0x0]
    mov r0, #0x1
    str r0, [sp, #0x4]
    add r0, r7, #0x198
    mov r1, #0x2
    mov r2, #0x7
    mov r3, #0x1c
    bl func_0204b9b8
    ldr r0, [r7, #0xc0]
    ldr r3, [r0, #0x0]
    cmp r3, #0x0
    beq @L021da68c
    ldrb r0, [r3, #0xe]
    add r1, sp, #0x14
    add r2, sp, #0x16
    ldrsh r4, [r3, #0x0]
    ldrsh r5, [r3, #0x2]
    bl func_ov003_0215ec68
    ldrsh r2, [sp, #0x16]
    mov r1, #0x0
    add r0, r7, #0x198
    mov r2, r2, asr #0x3
    str r2, [sp, #0x0]
    str r1, [sp, #0x4]
    ldrsh r3, [sp, #0x14]
    mov r1, r4, asr #0x3
    mov r2, r5, asr #0x3
    mov r3, r3, asr #0x3
    bl func_0204b9b8
@L021da68c:
    add r0, r7, #0x198
    mov r1, #0x0
    bl func_0204b04c
    b @L021da750
@L021da69c:
    cmp r0, #0x9
    bne @L021da750
    ldrb r0, [r7, #0xd95]
    mov r2, #0x0
    mov r1, #0x0
    cmp r0, #0x0
    str r2, [sp, #0x0]
    mov r0, #0xe
    str r0, [sp, #0x4]
    mov r0, #0x20
    str r0, [sp, #0x8]
    mov r0, #0xa
    str r0, [sp, #0xc]
    ldr r4, =0xffff
    moveq r1, #0x1
    mov r3, r2
    add r0, r7, #0x1b8
    str r4, [sp, #0x10]
    bl func_0204b8d0
    mov r0, #0x18
    str r0, [sp, #0x0]
    mov r0, #0x9
    str r0, [sp, #0x4]
    mov r0, #0x8
    mov r2, #0x0
    str r0, [sp, #0x8]
    mov r0, #0x7
    str r0, [sp, #0xc]
    mov r3, r2
    add r0, r7, #0x1b8
    mov r1, #0x2
    str r4, [sp, #0x10]
    bl func_0204b8d0
    mov r0, #0xc
    str r0, [sp, #0x0]
    mov r4, #0x1
    add r0, r7, #0x198
    mov r1, #0x2
    mov r2, #0x7
    mov r3, #0x1c
    str r4, [sp, #0x4]
    bl func_0204b9b8
    add r0, r7, #0x198
    mov r1, #0x0
    bl func_0204b04c
@L021da750:
    add r0, r7, #0x1b8
    mov r1, #0x0
    bl func_0204b04c
@L021da75c:
    add sp, sp, #0x18
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif

void CharacterCreation::UpdateSprites()
{
    SpriteRenderer* renderer = renderer2_;
    Sprite* sprites = sprites2_;
    if (!(flags_ & 0x1000000) && (state_ != 9 || step_ < 1) && state_ != 11 && !(flags_ & 0x400000))
    {
        sprites[7].x_ = 0xe000;
        sprites[7].y_ = 0xa9000;
        func_0205ac40(renderer, &sprites[7]);
        sprites[6].x_ = 0x15000;
        sprites[6].y_ = 0xa9000;
        func_0205ac40(renderer, &sprites[6]);
        sprites[8].x_ = 0x3b000;
        sprites[8].y_ = 0xa9000;
        func_0205ac40(renderer, &sprites[8]);
        sprites[9].x_ = 0x8e000;
        sprites[9].y_ = 0xa9000;
        func_0205ac40(renderer, &sprites[9]);
        sprites[10].x_ = 0xc8000;
        sprites[10].y_ = 0xa9000;
        func_0205ac40(renderer, &sprites[10]);
    }

    // The markers of the states
    for (int i = 0; i < 8; i++)
    {
        int x;
        if (i > lastStates_[sex_] - 1)
            break;
        unsigned char palette = 10;
        x = (i * 16 + 0x78) << 12;
        Sprite* sprite = &sprites[i + 11];
        signed char state = state_;
        if (state == 9)
        {
            if (step_ >= 1 && step_ != 0xff)
                palette = 11;
        }
        else if (state == 11)
        {
            palette = 11;
        }
        else if (i == state - 1)
        {
            palette = 9;
        }
        sprite->unk_25 = palette;
        sprite->x_ = x;
        sprite->y_ = 0x8000;
        func_0205ac40(renderer, sprite);
    }

    if (loadStep_ == 1)
        return;

    int marker = -1;
    int cursor = 0;
    switch (state_)
    {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        marker = 0x14;
        if (state_ == 2)
            marker = 0x13;
    case 1:
    case 8:
        cursor = 1;
        break;
    }
    if (marker >= 0)
    {
        short x = lastX_;
        short y = lastY_;
        sprites[marker].x_ = x << 12;
        sprites[marker].y_ = y << 12;
        func_0205ac40(renderer, &sprites[marker]);
    }
    if (cursor == 0)
        return;
    if (flags_ & 0x400000)
        return;
    SetCursorSprites(cursorX_, cursorY_, cursorWidth_, cursorHeight_);
}

void CharacterCreation::UpdateAnimations()
{
    GameState* gameState = GameState::GetInstance();
    if (renderer_ != NULL)
    {
        signed char state = state_;
        if (state >= 1 && state <= 8)
        {
            short x = 0x6c;
            short y = (state - 1) * 16 + 0x2b;
            GameState* gameState2 = GameState::GetInstance();
            if (func_0200fb08(gameState2) == 4)
                x = 0x64;
            SpriteAnimationList* animations = (SpriteAnimationList*)unk_7e0;
            func_0205a42c(animations, 0, 0x78);
            func_0205a370(animations, 0);
            SpriteAnimation* animation = func_0205a3d0(animations, 0);
            if (animation != NULL)
                animation->flags_ |= 8;
            func_0205a330(animations, gameState2->GetTickCount());
            func_020e27ec(animations, 0, x, y);
            func_0205ae8c(renderer_);
        }
    }

    if (renderer2_ == NULL)
        return;
    Canvas* canvas = func_0205d81c(&windows_[1], 1);
    if (canvas == NULL)
        return;
    if (!func_0204c7e0(canvas))
        return;
    short x = canvas->x_ * 8;
    short y = canvas->y_ * 8;
    x += canvas->unk_bc;
    y += canvas->unk_be;
    SpriteAnimationList* animations = (SpriteAnimationList*)unk_7ec;
    func_0205a42c(animations, 0, 0x78);
    func_0205a370(animations, 0);
    SpriteAnimation* animation = func_0205a3d0(animations, 0);
    if (animation != NULL)
        animation->flags_ |= 8;
    func_0205a330(animations, gameState->GetTickCount());
    func_020e27ec(animations, 0, (short)(x - 8), (short)(y - 2));
    func_0205ae8c(renderer2_);
}

// NONMATCHING: the C matches 93.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void CharacterCreation::SetCursorSprites(int x, int y, int width, int height)
{
    int x1 = x << 12;
    int y1 = y << 12;
    int left, top, right, bottom;
    if (state_ == 1)
    {
        unsigned int rightEdge = x1 + (width << 12);
        long bottomEdge;
        bottomEdge = y1 + (height << 12);
        left = x1 - 0x7000;
        top = y1 - 0x7000;
        right = rightEdge - 0x1000;
        bottom = bottomEdge - 0x1000;
        if (func_0205bafc(&cursor_) == 8 && cursor_.unk_c == 1)
        {
            left = x1 - 0x4000;
            top = y1 - 0x4000;
            right = rightEdge - 0x4000;
            bottom = bottomEdge - 0x4000;
        }
    }
    else
    {
        left = x1 - 0x4000;
        top = y1 - 0x4000;
        right = x1 + (width << 12) - 0x4000;
        bottom = y1 + (height << 12) - 0x4000;
    }
    Sprite* sprites = sprites2_;
    sprites[0x15].x_ = left;
    sprites[0x15].y_ = top;
    sprites[0x16].x_ = right;
    sprites[0x16].y_ = top;
    sprites[0x17].x_ = left;
    sprites[0x17].y_ = bottom;
    sprites[0x18].x_ = right;
    sprites[0x18].y_ = bottom;
    for (int i = 0; i < 4; i++)
        func_0205ac40(renderer2_, &sprites[i + 0x15]);
}
#else
asm void CharacterCreation::SetCursorSprites(int x, int y, int width, int height)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    mov r10, r0
    add r0, r10, #0xc00
    ldrsb r0, [r0, #0x58]
    mov r4, r1, lsl #0xc
    mov r5, r2, lsl #0xc
    cmp r0, #0x1
    ldr r1, [sp, #0x28]
    bne @L021dabd0
    add r0, r10, #0x3ec
    add r9, r5, r1, lsl #0xc
    add r11, r4, r3, lsl #0xc
    sub r1, r5, #0x7000
    add r0, r0, #0x800
    sub r6, r4, #0x7000
    str r1, [sp, #0x0]
    sub r7, r11, #0x1000
    sub r8, r9, #0x1000
    bl func_0205bafc
    cmp r0, #0x8
    ldreq r0, [r10, #0xbf8]
    cmpeq r0, #0x1
    bne @L021dabec
    sub r0, r5, #0x4000
    sub r6, r4, #0x4000
    str r0, [sp, #0x0]
    sub r7, r11, #0x4000
    sub r8, r9, #0x4000
    b @L021dabec
@L021dabd0:
    add r2, r4, r3, lsl #0xc
    add r1, r5, r1, lsl #0xc
    sub r0, r5, #0x4000
    sub r6, r4, #0x4000
    str r0, [sp, #0x0]
    sub r7, r2, #0x4000
    sub r8, r1, #0x4000
@L021dabec:
    ldr r4, [r10, #0x7e8]
    ldr r0, [sp, #0x0]
    str r6, [r4, #0x35c]
    str r0, [r4, #0x360]
    str r7, [r4, #0x384]
    str r0, [r4, #0x388]
    str r6, [r4, #0x3ac]
    str r8, [r4, #0x3b0]
    str r7, [r4, #0x3d4]
    mov r5, #0x0
    str r8, [r4, #0x3d8]
    mov r6, #0x28
    b @L021dac34
@L021dac20:
    add r0, r5, #0x15
    mla r1, r0, r6, r4
    ldr r0, [r10, #0x7e4]
    bl func_0205ac40
    add r5, r5, #0x1
@L021dac34:
    cmp r5, #0x4
    blt @L021dac20
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

void CharacterCreation::UpdateFade(unsigned int ticks)
{
    if (!(flags_ & 0x10000))
        return;
    unk_d98 -= ticks;
    if (unk_d98 < 0)
        unk_d98 = 0;
    if (flags_ & 0x800000)
        DrawFade(0, 0x1f - unk_d98 * 0x1f / 90);
    else
        ColorEffect_ConfigureBrightnessAdjust(REG_BLDCNT, 0x16, -((90 - unk_d98) * 16) / 90);
}

// Draws a quad of a color over the screen
void CharacterCreation::DrawFade(int color, int alpha)
{
    REG_TEXIMAGE_PARAM = 0x900000;
    REG_POLYGON_ATTR = (alpha << 16) | 0xc0;
    REG_MTX_PUSH = 0;
    REG_MTX_TRANS = 0;
    REG_MTX_TRANS = 0;
    REG_MTX_TRANS = -0x80000;
    REG_MTX_SCALE = 0x100000;
    REG_MTX_SCALE = 0xc0000;
    REG_MTX_SCALE = 0;
    REG_BEGIN_VTXS = 1;
    REG_COLOR = color;
    REG_VTX_16 = 0x10001000;
    REG_VTX_16 = 0;
    REG_VTX_16 = 0x1000f000;
    REG_VTX_16 = 0;
    REG_VTX_16 = 0xf000f000;
    REG_VTX_16 = 0;
    REG_VTX_16 = 0xf0001000;
    REG_VTX_16 = 0;
    REG_END_VTXS = 0;
    REG_MTX_POP = 1;
}
