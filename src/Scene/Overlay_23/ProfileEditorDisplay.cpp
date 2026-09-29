// The part of overlay 12's profile editor that overlay 23 has: the arrows of the birthday, the accolade and title
// texts, the sprites of the windows, the key of the keyboard and the grid of the items
#include "Scene/Overlay_12/ProfileEditor.h"
#include "GameState/GameState.h"
#include "GameState/PartyMemberData.h"
#include "System/Cache.h"
#include "System/LoadToVRAM.h"
#include "System/TouchScreen.h"
#include <std_library_functions.h>

// A part of the text drawn on a key's sprite (func_0205b890 fills them)
struct KeyTextPart
{
    int unk_0;
    short unk_4;
    short unk_6;
    short unk_8;
    short unk_a;
};

// What draws a text in the tiles of a sprite (func_0205b20c initializes it)
struct SpriteTextWriter
{
    char unk_0[0xc];
};

extern "C"
{
    // The runtime's signed division, for the assembly
    void _s32_div_f();
    extern char data_02114e30[];
    // The touch screen
    extern TouchState data_02114e54;

    int func_0201079c(GameState* gameState);
    int func_02012444(void* pad, int buttons);
    void func_02012a84(TouchState* touch, int* x, int* y);
    void func_0202ae18();
    int func_020420e8(const char* text, int large);
    int func_0204c7e0(Canvas* canvas);
    const char* func_02072a68(BinTextTable* table, short id);
    void func_0205a330(SpriteAnimationList* list, int ticks);
    void func_0205a370(SpriteAnimationList* list, int);
    SpriteAnimation* func_0205a3d0(SpriteAnimationList* list, int index);
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205ae8c(SpriteRenderer* renderer);
    void func_0205b20c(SpriteTextWriter* writer);
    void func_0205b220(SpriteTextWriter* writer, void* pixels);
    void func_0205b228(SpriteTextWriter* writer, KeyTextPart* parts, int count);
    void func_0205b234(SpriteTextWriter* writer, int x, int y, const char* text, int, int);
    void func_0205b734(SpriteTextWriter* writer, int, int, int width, int height, int);
    void func_0205b890(KeyTextPart* parts, int count, Sprite* sprite);
    unsigned char func_0205bb84(WindowCursor* cursor);
    void func_0205c4a8(WindowCursor* cursor, int);
    void func_0205c53c(TextWindow* window);
    int func_0205c6e4(TextWindow* window);
    void func_0205cf10(TextWindow* window);
    void func_0205cf1c(TextWindow* window);
    Canvas* func_0205d81c(TextWindow* window, unsigned char canvas);
    Canvas* func_0205d8c4(TextWindow* window);
    int func_0205d97c(TextWindow* window);
    int func_0205da38(TextWindow* window, int);
    void func_0205deb4(TextWindow* window, int, int);
    // Compares a date to the range of the birthdays
    int func_02098f20(int year, int month, int day);
    void func_ov003_0215ec68(int size, short* width, short* height);
}

// Unused: nothing reads it (external, so the compiler keeps it), *maybe* the size of the date arrows' sprites
extern const int data_ov023_021fd724[2] = {0x10, 8};

void ProfileEditor::UpdateDateArrows()
{
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    unk_13ab = 0;
    GameState::GetInstance();
    int date = func_02098f20(year_, month_, day_);
    if (date < 0x82)
        unk_13ab |= 2;
    if (date > 0)
        unk_13ab |= 1;
    if (month_ < 12 && func_02098f20(year_, month_ + 1, day_) >= 0)
        unk_13ab |= 4;
    if (month_ > 1 && func_02098f20(year_, month_ - 1, day_) <= 0x82)
        unk_13ab |= 8;
    if (year_ % 4 == 0)
        days[1] = 29;
    if (day_ < days[month_ - 1] && func_02098f20(year_, month_, day_ + 1) >= 0)
        unk_13ab |= 0x10;
    if (day_ > 1 && func_02098f20(year_, month_, day_ - 1) <= 0x82)
        unk_13ab |= 0x20;
}

void ProfileEditor::ShowDateItems(unsigned char state, unsigned char year, unsigned char month, unsigned char day)
{
    state_ = state;
    func_0205deb4(&window_, 7, year);
    func_0205deb4(&window_, 8, month);
    func_0205deb4(&window_, 9, day);
}

// NONMATCHING: the C matches 82.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
int ProfileEditor::GetTouchedDateArrow()
{
    Canvas* canvas = func_0205d81c(&window_, state_);
    int x = (short)(canvas->x_ * 8) + 10;
    int y = (short)(canvas->y_ * 8) + 0x10;
    int touchX = data_02114e54.x_;
    int touchY = data_02114e54.y_;
    if (x <= touchX && touchX <= x + 0x10 && y <= touchY && touchY <= y + 8)
        return 1;
    if (x <= touchX && touchX <= x + 0x10 && y + 0xc <= touchY && touchY <= y + 0x14)
        return -1;
    return 0;
}
#else
asm int ProfileEditor::GetTouchedDateArrow()
{
    stmdb sp!, {r3, lr}
    add r1, r0, #0x1000
    ldrb r1, [r1, #0x371]
    add r0, r0, #0xac
    bl func_0205d81c
    ldr r1, =data_02114e54
    ldrsh r2, [r0, #0xac]
    ldrsh r3, [r0, #0xae]
    ldr r12, [r1, #0x38]
    mov r0, r2, lsl #0x13
    mov r2, r0, asr #0x10
    mov r0, r3, lsl #0x13
    add r2, r2, #0xa
    mov r0, r0, asr #0x10
    ldr r1, [r1, #0x3c]
    cmp r2, r12
    add r3, r0, #0x10
    addle r0, r2, #0x10
    cmple r12, r0
    cmple r3, r1
    addle r0, r3, #0x8
    cmple r1, r0
    movle r0, #0x1
    ldmleia sp!, {r3, pc}
    cmp r2, r12
    addle r0, r2, #0x10
    cmple r12, r0
    addle r0, r3, #0xc
    cmple r0, r1
    addle r0, r3, #0x14
    cmple r1, r0
    mvnle r0, #0x0
    movgt r0, #0x0
    ldmia sp!, {r3, pc}
}
#endif

// The cursor of a window's items (the original computes its address apart from its fields', as with an inline function
// like this)
static inline WindowCursor* GetCursor(TextWindow* window)
{
    return (WindowCursor*)((char*)window + 0x54);
}

// NONMATCHING: the C matches 83.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
int ProfileEditor::UpdateTouchedPage()
{
    if (func_0205c6e4(&window_) <= 1)
        return 0;
    if (data_02114e54.touching_ != 0)
    {
        int x, y;
        func_02012a84(&data_02114e54, &x, &y);
        Canvas* canvas = func_0205d81c(&window_, state_);
        if (canvas != NULL)
        {
            short right = canvas->x_ + canvas->width_;
            short bottom = (short)(canvas->y_ + canvas->height_) * 8;
            if (bottom - 0x10 <= y && y < bottom)
            {
                WindowCursor* cursor = GetCursor(&window_);
                if (x >= (short)(canvas->x_ * 8) && x < (short)(canvas->x_ * 8) + 0x10)
                {
                    func_0205c4a8(cursor, -1);
                    unk_1398 = 1;
                }
                short rightEdge = right * 8;
                if (rightEdge - 0x10 <= x && x < rightEdge)
                {
                    func_0205c4a8(cursor, 1);
                    unk_1398 = 1;
                }
                unsigned char selection = func_0205bb84(cursor);
                func_0205bcdc(&window_.base_.frame_, selection);
                func_0205bb04(&window_.base_.cursor_, selection);
            }
            return 1;
        }
    }
    return 0;
}
#else
asm int ProfileEditor::UpdateTouchedPage()
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x8
    mov r6, r0
    add r0, r6, #0xac
    bl func_0205c6e4
    cmp r0, #0x1
    movle r0, #0x0
    ble @L021e6588
    ldr r0, =data_02114e54
    ldrb r1, [r0, #0x55]
    cmp r1, #0x0
    beq @L021e6584
    add r1, sp, #0x4
    add r2, sp, #0x0
    bl func_02012a84
    add r0, r6, #0x1000
    ldrb r1, [r0, #0x371]
    add r0, r6, #0xac
    bl func_0205d81c
    cmp r0, #0x0
    beq @L021e6584
    ldrsh r4, [r0, #0xae]
    ldrsh r2, [r0, #0xaa]
    ldrsh r1, [r0, #0xac]
    ldrsh r3, [r0, #0xa8]
    add r0, r4, r2
    mov r0, r0, lsl #0x10
    mov r0, r0, asr #0x10
    mov r0, r0, lsl #0x13
    add r2, r1, r3
    mov r3, r0, asr #0x10
    mov r0, r2, lsl #0x10
    ldr r5, [sp, #0x0]
    sub r2, r3, #0x10
    cmp r2, r5
    mov r4, r0, asr #0x10
    bgt @L021e657c
    cmp r5, r3
    bge @L021e657c
    ldr r2, [sp, #0x4]
    mov r0, r1, lsl #0x13
    cmp r2, r0, asr #0x10
    add r5, r6, #0x100
    mov r0, r0, asr #0x10
    blt @L021e6520
    add r0, r0, #0x10
    cmp r2, r0
    bge @L021e6520
    mov r0, r5
    mvn r1, #0x0
    bl func_0205c4a8
    add r0, r6, #0x1000
    mov r1, #0x1
    str r1, [r0, #0x398]
@L021e6520:
    mov r0, r4, lsl #0x13
    mov r1, r0, asr #0x10
    ldr r2, [sp, #0x4]
    sub r0, r1, #0x10
    cmp r0, r2
    bgt @L021e6558
    cmp r2, r1
    bge @L021e6558
    mov r0, r5
    mov r1, #0x1
    bl func_0205c4a8
    add r0, r6, #0x1000
    mov r1, #0x1
    str r1, [r0, #0x398]
@L021e6558:
    mov r0, r5
    bl func_0205bb84
    mov r4, r0
    mov r1, r4
    add r0, r6, #0xb0
    bl func_0205bcdc
    mov r1, r4
    add r0, r6, #0x100
    bl func_0205bb04
@L021e657c:
    mov r0, #0x1
    b @L021e6588
@L021e6584:
    mov r0, #0x0
@L021e6588:
    add sp, sp, #0x8
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void ProfileEditor::RefreshAccoladeTexts()
{
    GameState* gameState = GameState::GetInstance();
    ProfileData* profile = GetProfile(gameState);
    if (!profile->accoladeChosen_)
    {
        const char* text;
        if (func_0201079c(gameState) == 1)
        {
            text = func_02072a68(&strings_, 0x50e9);
        }
        else
        {
            func_0202ae18();
            PartyMemberData* data = gameState->GetProtagonist()->partyData_;
            int accolade = 0x50dc;
            if (data->details_.appearance_.female_ == 1)
                accolade = 0x510e;
            text = func_02072a68(&strings_, accolade + data->vocation_);
        }
        memset(accoladeText_, 0, sizeof(accoladeText_));
        memcpy(accoladeText_, text, strlen(text));
    }
    if (profile->title_ != 300)
        return;
    memset(titleText_, 0, sizeof(titleText_));
    const char* title = func_02072a68(&strings_, 0x283c);
    memcpy(titleText_, title, strlen(title));
}

void ProfileEditor::ResetAccoladeTexts()
{
    GameState* gameState = GameState::GetInstance();
    ProfileData* profile = GetProfile(gameState);
    if (!profile->accoladeChosen_)
    {
        memset(accoladeText_, 0, sizeof(accoladeText_));
        memcpy(accoladeText_, func_02072a68(&strings_, 0x6d), 7);
    }
    else if (profile->vocationAccolade_)
    {
        func_0202ae18();
        GameObject* protagonist = gameState->GetProtagonist();
        int vocation = protagonist->partyData_->vocation_;
        if (func_0201079c(gameState) == 1)
            vocation = 0xd;
        int accolade = 0x50dc;
        if (protagonist->partyData_->details_.appearance_.female_ == 1)
            accolade = 0x510e;
        const char* text = func_02072a68(&strings_, accolade + vocation);
        memset(accoladeText_, 0, sizeof(accoladeText_));
        memcpy(accoladeText_, text, strlen(text));
    }
    if (profile->title_ != 300)
        return;
    memset(titleText_, 0, sizeof(titleText_));
    const char* title = func_02072a68(&strings_, 0x6d);
    memcpy(titleText_, title, strlen(title));
}

void ProfileEditor::DrawCursorAnimation()
{
    if (unk_13a0 == 0)
        return;
    Canvas* canvas = func_0205d8c4(&window_);
    if (canvas == NULL)
        return;
    if (!func_0204c7e0(canvas))
        return;
    short x = canvas->x_ * 8;
    short y = canvas->y_ * 8;
    x += canvas->unk_bc;
    y += canvas->unk_be;
    func_0205a370((SpriteAnimationList*)unk_1360, 0);
    SpriteAnimation* animation = func_0205a3d0((SpriteAnimationList*)unk_1360, 0);
    if (animation != NULL)
        animation->flags_ |= 8;
    func_0205a330((SpriteAnimationList*)unk_1360, unk_13a4);
    animation = func_0205a3d0((SpriteAnimationList*)unk_1360, 0);
    if (animation != NULL)
    {
        animation->x_ = x - 8;
        animation->y_ = y - 2;
    }
    func_0205ae8c(renderer_);
}

// NONMATCHING: the C matches 51.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void ProfileEditor::DrawDateArrows()
{
    unsigned char tile;
    signed char arrow;
    unsigned char state;
    int x;
    state = state_;
    if (state != 7 && state != 8 && state != 9)
        return;
    if (step_ != 4)
        return;

    tile = 0x13;
    arrow = 0;
    for (int i = 0; i < 3; i++)
    {
        Canvas* canvas;
        canvas = func_0205d81c(&window_, i + 7);
        Sprite* sprite;
        int offset;
        int index;
        x = ((short)(canvas->x_ * 8) + 10) << 12;
        short top = canvas->y_ * 8;
        for (int j = 0; j < 2; j++)
        {
            int offset = 0x10;
            int index = 0xd;
            if (j == 1)
            {
                offset = 0x1c;
                index = 0xe;
            }
            int y = offset + top;
            Sprite* sprite = &sprites_[index];
            sprite->x_ = x;
            sprite->y_ = y << 12;
            int push = 1;
            sprite->unk_22 = tile;
            sprite->unk_25 = 7;
            tile++;
            if (j == 1)
                push = -1;
            if (arrow == unk_13a8)
            {
                sprite->x_ = x;
                sprite->y_ = (y - push) << 12;
            }
            if (!(unk_13ab & (1 << arrow)))
                sprite->unk_25 = 0xd;
            func_0205ac40(renderer_, sprite);
            arrow++;
        }
    }
    unk_13a8 = -1;
}
#else
asm void ProfileEditor::DrawDateArrows()
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x8
    mov r5, r0
    add r0, r5, #0x1000
    ldrb r0, [r0, #0x371]
    cmp r0, #0x7
    cmpne r0, #0x8
    cmpne r0, #0x9
    bne @L021e6a0c
    add r0, r5, #0x1000
    ldrb r0, [r0, #0x370]
    cmp r0, #0x4
    bne @L021e6a0c
    mov r8, #0x0
    mov r9, r8
    mov r4, #0x13
    b @L021e69f8
@L021e6910:
    add r1, r9, #0x7
    add r0, r5, #0xac
    and r1, r1, #0xff
    bl func_0205d81c
    ldrsh r1, [r0, #0xae]
    ldrsh r2, [r0, #0xac]
    mov r10, #0x0
    mov r11, r1, lsl #0x13
    mov r0, r2, lsl #0x13
    mov r0, r0, asr #0x10
    add r0, r0, #0xa
    mov r7, r0, lsl #0xc
    add r0, r5, #0x1300
    str r0, [sp, #0x4]
    mvn r0, #0x0
    add r6, r5, #0x1000
    str r0, [sp, #0x0]
    b @L021e69ec
@L021e6958:
    mov r1, #0x10
    cmp r10, #0x1
    mov r0, #0xd
    moveq r1, #0x1c
    add r12, r1, r11, asr #0x10
    ldr lr, [r6, #0x364]
    moveq r0, #0xe
    mov r1, #0x28
    mla r1, r0, r1, lr
    mov r3, r12, lsl #0xc
    str r7, [r1, #0x14]
    str r3, [r1, #0x18]
    mov r2, #0x1
    strb r4, [r1, #0x22]
    mov r0, #0x7
    strb r0, [r1, #0x25]
    add r0, r4, #0x1
    and r4, r0, #0xff
    ldr r0, [sp, #0x4]
    ldreq r2, [sp, #0x0]
    ldrsb r0, [r0, #0xa8]
    cmp r8, r0
    subeq r0, r12, r2
    moveq r0, r0, lsl #0xc
    streq r7, [r1, #0x14]
    streq r0, [r1, #0x18]
    ldrb r2, [r6, #0x3ab]
    mov r0, #0x1
    tst r2, r0, lsl r8
    moveq r0, #0xd
    streqb r0, [r1, #0x25]
    ldr r0, [r6, #0x35c]
    bl func_0205ac40
    add r0, r8, #0x1
    mov r0, r0, lsl #0x18
    mov r8, r0, asr #0x18
    add r10, r10, #0x1
@L021e69ec:
    cmp r10, #0x2
    blt @L021e6958
    add r9, r9, #0x1
@L021e69f8:
    cmp r9, #0x3
    blt @L021e6910
    add r0, r5, #0x1000
    mvn r1, #0x0
    strb r1, [r0, #0x3a8]
@L021e6a0c:
    add sp, sp, #0x8
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 54.8 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void ProfileEditor::DrawDateMarker()
{
    unsigned char state = state_;
    if (state != 7 && state != 8 && state != 9)
        return;
    Canvas* canvas = func_0205d81c(&window_, 0x10);
    if (canvas == NULL)
        return;
    short x = canvas->x_ * 8;
    short y = canvas->y_ * 8;
    Sprite* sprites = sprites_;
    sprites[11].x_ = (x + 5) << 12;
    sprites[11].y_ = (y + 3) << 12;
    func_0205ac40(renderer_, &sprites[11]);
}
#else
asm void ProfileEditor::DrawDateMarker()
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    add r0, r4, #0x1000
    ldrb r0, [r0, #0x371]
    cmp r0, #0x7
    cmpne r0, #0x8
    cmpne r0, #0x9
    ldmneia sp!, {r4, pc}
    add r0, r4, #0xac
    mov r1, #0x10
    bl func_0205d81c
    cmp r0, #0x0
    ldmeqia sp!, {r4, pc}
    ldrsh r2, [r0, #0xac]
    ldrsh r3, [r0, #0xae]
    add r1, r4, #0x1000
    mov r0, r2, lsl #0x13
    mov r2, r0, asr #0x10
    mov r0, r3, lsl #0x13
    add r2, r2, #0x5
    mov r0, r0, asr #0x10
    ldr r3, [r1, #0x364]
    mov r2, r2, lsl #0xc
    add r0, r0, #0x3
    str r2, [r3, #0x1cc]
    mov r0, r0, lsl #0xc
    str r0, [r3, #0x1d0]
    ldr r0, [r1, #0x35c]
    add r1, r3, #0x1b8
    bl func_0205ac40
    ldmia sp!, {r4, pc}
}
#endif

// NONMATCHING: the C matches 51.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void ProfileEditor::DrawMarker()
{
    if (state_ == 6)
        return;
    Canvas* canvas = func_0205d81c(&window_, 0x11);
    if (canvas == NULL)
        return;
    short x = canvas->x_ * 8;
    short y = canvas->y_ * 8;
    Sprite* sprites = sprites_;
    sprites[12].x_ = (x + 10) << 12;
    sprites[12].y_ = (y + 3) << 12;
    func_0205ac40(renderer_, &sprites[12]);
}
#else
asm void ProfileEditor::DrawMarker()
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    add r0, r4, #0x1000
    ldrb r0, [r0, #0x371]
    cmp r0, #0x6
    ldmeqia sp!, {r4, pc}
    add r0, r4, #0xac
    mov r1, #0x11
    bl func_0205d81c
    cmp r0, #0x0
    ldmeqia sp!, {r4, pc}
    ldrsh r2, [r0, #0xac]
    ldrsh r3, [r0, #0xae]
    add r1, r4, #0x1000
    mov r0, r2, lsl #0x13
    mov r2, r0, asr #0x10
    mov r0, r3, lsl #0x13
    add r2, r2, #0xa
    mov r0, r0, asr #0x10
    ldr r3, [r1, #0x364]
    mov r2, r2, lsl #0xc
    add r0, r0, #0x3
    str r2, [r3, #0x1f4]
    mov r0, r0, lsl #0xc
    str r0, [r3, #0x1f8]
    ldr r0, [r1, #0x35c]
    add r1, r3, #0x1e0
    bl func_0205ac40
    ldmia sp!, {r4, pc}
}
#endif

void ProfileEditor::DrawKey()
{
    if (state_ != 0xe)
        return;
    if (step_ >= 10)
        return;
    KeyboardKey* key;
    if (func_0205d81c(&window_, 0xe) != NULL && (key = ((Keyboard*)unk_0)->key_) != NULL)
    {
        Sprite* sprite = &sprites_[key->size_ + 0xf];
        short x = key->x_;
        short y = key->y_;
        sprite->x_ = x << 12;
        sprite->y_ = y << 12;
        sprite->unk_26 = 0;
        func_0205ac40(renderer_, sprite);
    }
}

// NONMATCHING: the C matches 88.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void ProfileEditor::DrawKeyText()
{
    if (state_ == 0xe && step_ > 1 && step_ < 10)
    {
        KeyboardKey* key = ((Keyboard*)unk_0)->key_;
        if (key != NULL && key->size_ != 3)
        {
            Sprite* sprite = &sprites_[key->size_ + 0xf];
            short width, height;
            func_ov003_0215ec68(key->size_, &width, &height);
            KeyTextPart parts[3];
            for (int i = 0; i < 3; i++)
            {
                parts[i].unk_0 = 0;
                parts[i].unk_4 = 0;
                parts[i].unk_6 = 0;
                parts[i].unk_8 = 0;
                parts[i].unk_a = 0;
            }
            func_0205b890(parts, 3, sprite);
            int offset = 0;
            int size = 0;
            for (int i = 0; i < 3; i++)
            {
                parts[i].unk_4 = offset;
                offset += parts[i].unk_8;
                size += (parts[i].unk_8 * parts[i].unk_a) >> 1;
            }
            SpriteImage image = sprite->image_;
            unsigned short tiles = (unsigned short)(image.cell_->unk_4 & 0x3ff) << 5;
            memcpy(pixels_, (void*)(tiles + 0x06400000), size);

            Keyboard* keyboard = (Keyboard*)unk_0;
            unsigned char unk = key->unk_d;
            unsigned char mode = keyboard->unk_1e;
            unsigned char shift = keyboard->unk_20;
            const char* text = key->text_;
            if (unk == 0 && (shift != 0 || (mode & 2)))
                text = key->shiftedText_;
            int x = (width - func_020420e8(text, 1)) >> 1;
            SpriteTextWriter writer;
            func_0205b20c(&writer);
            func_0205b220(&writer, pixels_);
            func_0205b228(&writer, parts, 3);
            func_0205b734(&writer, 9, 9, (short)(width + 7), (short)(height + 7), 9);
            func_0205b234(&writer, (short)(x + 8), 10, text, 2, 1);
            CleanInvalidateCacheRange(pixels_, size);
            LoadToMainObjVRAM(pixels_, tiles, size);
            CleanCacheRange(pixels_, size);
        }
    }
}
#else
asm void ProfileEditor::DrawKeyText()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, lr}
    sub sp, sp, #0x44
    mov r7, r0
    add r1, r7, #0x1000
    ldrb r0, [r1, #0x371]
    cmp r0, #0xe
    bne @L021e6dd8
    ldrb r0, [r1, #0x370]
    cmp r0, #0x1
    bls @L021e6dd8
    cmp r0, #0xa
    bhs @L021e6dd8
    ldr r0, [r7, #0x0]
    ldr r5, [r0, #0x0]
    cmp r5, #0x0
    ldrneb r0, [r5, #0xe]
    cmpne r0, #0x3
    beq @L021e6dd8
    ldr r3, [r1, #0x364]
    add r2, r0, #0xf
    mov r1, #0x28
    mla r6, r2, r1, r3
    add r1, sp, #0xa
    add r2, sp, #0x8
    bl func_ov003_0215ec68
    mov lr, #0x0
    mov r9, lr
    add r8, sp, #0x20
    add r4, sp, #0x24
    add r3, sp, #0x26
    add r2, sp, #0x28
    add r1, sp, #0x2a
    mov r0, #0xc
    b @L021e6c30
@L021e6c14:
    mul r12, lr, r0
    str r9, [r8, r12]
    strh r9, [r4, r12]
    strh r9, [r3, r12]
    strh r9, [r2, r12]
    strh r9, [r1, r12]
    add lr, lr, #0x1
@L021e6c30:
    cmp lr, #0x3
    blt @L021e6c14
    add r0, sp, #0x20
    mov r2, r6
    mov r1, #0x3
    bl func_0205b890
    mov r0, #0x0
    mov r4, r0
    mov r1, r0
    add r9, sp, #0x24
    add lr, sp, #0x28
    add r8, sp, #0x2a
    mov r2, #0xc
    b @L021e6c88
@L021e6c68:
    mul r3, r1, r2
    strh r0, [r9, r3]
    ldrsh r12, [lr, r3]
    ldrsh r3, [r8, r3]
    add r1, r1, #0x1
    add r0, r0, r12
    smulbb r3, r12, r3
    add r4, r4, r3, asr #0x1
@L021e6c88:
    cmp r1, #0x3
    blt @L021e6c68
    ldr r3, [r6, #0x4]
    add r1, r7, #0x1000
    ldrh r2, [r3, #0x4]
    ldr r0, =0x3ff
    ldr r12, [r6, #0x0]
    and r0, r2, r0
    mov r0, r0, lsl #0x10
    mov r0, r0, lsr #0x10
    mov r0, r0, lsl #0x15
    mov r6, r0, lsr #0x10
    ldr r0, [r1, #0x37c]
    mov r2, r4
    add r1, r6, #0x6400000
    str r12, [sp, #0xc]
    str r3, [sp, #0x10]
    bl memcpy
    ldr r1, [r7, #0x0]
    ldrb r0, [r5, #0xd]
    ldrb r2, [r1, #0x1e]
    ldrb r1, [r1, #0x20]
    cmp r0, #0x0
    ldr r8, [r5, #0x4]
    bne @L021e6d00
    cmp r1, #0x0
    bne @L021e6cfc
    tst r2, #0x2
    beq @L021e6d00
@L021e6cfc:
    ldr r8, [r5, #0x8]
@L021e6d00:
    mov r0, r8
    mov r1, #0x1
    bl func_020420e8
    ldrsh r1, [sp, #0xa]
    sub r1, r1, r0
    add r0, sp, #0x14
    mov r5, r1, asr #0x1
    bl func_0205b20c
    add r0, r7, #0x1000
    ldr r1, [r0, #0x37c]
    add r0, sp, #0x14
    bl func_0205b220
    add r0, sp, #0x14
    add r1, sp, #0x20
    mov r2, #0x3
    bl func_0205b228
    ldrsh r2, [sp, #0x8]
    mov r1, #0x9
    add r0, sp, #0x14
    add r2, r2, #0x7
    mov r2, r2, lsl #0x10
    mov r2, r2, asr #0x10
    str r2, [sp, #0x0]
    str r1, [sp, #0x4]
    ldrsh r3, [sp, #0xa]
    mov r2, r1
    add r3, r3, #0x7
    mov r3, r3, lsl #0x10
    mov r3, r3, asr #0x10
    bl func_0205b734
    add r0, r5, #0x8
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    mov r0, #0x2
    str r0, [sp, #0x0]
    mov r0, #0x1
    str r0, [sp, #0x4]
    mov r3, r8
    add r0, sp, #0x14
    mov r2, #0xa
    bl func_0205b234
    add r0, r7, #0x1000
    ldr r0, [r0, #0x37c]
    mov r1, r4
    bl CleanInvalidateCacheRange
    add r0, r7, #0x1000
    ldr r0, [r0, #0x37c]
    mov r1, r6
    mov r2, r4
    bl LoadToMainObjVRAM
    add r0, r7, #0x1000
    ldr r0, [r0, #0x37c]
    mov r1, r4
    bl CleanCacheRange
@L021e6dd8:
    add sp, sp, #0x44
    ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
}
#endif

int ProfileEditor::IsConfirmed()
{
    int pressed = func_02012444(data_02114e30, 0x601);
    if (pressed | func_0205da38(&window_, 0x14))
        return 1;
    return 0;
}

int ProfileEditor::IsCancelled()
{
    int pressed = func_02012444(data_02114e30, 2);
    if (pressed | (func_0205d97c(&window_) == 2))
        return 1;
    return 0;
}

// NONMATCHING: the C matches 82.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// registers
#ifdef NONMATCHING
void ProfileEditor::SetItemGrid()
{
    int columns, rows, pages, count, selection;
    int unk = 0;
    GameState::GetInstance();
    switch (state_)
    {
    case 1:
        pages = 1;
        count = 6;
        columns = 1;
        rows = 6;
        selection = selection_;
        break;
    case 2:
        pages = 1;
        count = 4;
        columns = 1;
        rows = 4;
        selection = selections_[0];
        break;
    case 3:
        selection = selections_[1];
        columns = 2;
        rows = 8;
        pages = 0xc;
        count = 0xc0;
        break;
    case 4:
        pages = 1;
        rows = 8;
        columns = 1;
        count = 8;
        selection = selections_[2];
        break;
    case 5:
        count = unk_13c4_0;
        columns = 1;
        pages = (count - 1) / 9 + 1;
        rows = 9;
        if ((unsigned int)count < 9)
            rows = count;
        selection = selections_[3];
        break;
    case 6:
        pages = 1;
        count = 2;
        columns = 1;
        rows = 2;
        selection = unk_13f8;
        break;
    case 10:
        pages = 1;
        count = 2;
        columns = 1;
        rows = 2;
        selection = selections_[4];
        break;
    case 11:
        selection = selections_[5];
        pages = 6;
        columns = 1;
        rows = 10;
        count = 0x3c;
        break;
    case 12:
        columns = 2;
        unk = 1;
        count = unk_13c4_5;
        pages = (count - 1) / 16 + 1;
        rows = (count - 1) / 2 + 1;
        if (rows > 8)
            rows = 8;
        selection = unk_13f0;
        break;
    case 13:
        columns = 1;
        rows = 8;
        pages = 1;
        count = 8;
        selection = design_;
        break;
    default:
        func_0205cf10(&window_);
        func_0205cf1c(&window_);
        return;
    }
    func_0205c53c(&window_);
    func_0205ba68(&window_.base_.frame_, columns, rows, unk);
    func_0205ba68(&window_.base_.cursor_, columns, rows, unk);
    func_0205bacc(&window_.base_.frame_, count);
    func_0205bacc(&window_.base_.cursor_, count);
    window_.base_.frame_.unk_4 = pages;
    window_.base_.cursor_.unk_4 = pages;
    func_0205bcdc(&window_.base_.frame_, selection);
    func_0205bb04(&window_.base_.cursor_, selection);
    window_.base_.unk_94 = 1;
    window_.base_.unk_95 = 1;
    unk_13a0 = 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
}

asm void ProfileEditor::SetItemGrid()
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    mov r9, r0
    bl _ZN9GameState11GetInstanceEv
    add r0, r9, #0x1000
    ldrb r1, [r0, #0x371]
    mov r7, #0x0
    cmp r1, #0xd
    addls pc, pc, r1, lsl #0x2
    b @L021e7004
@L021e6e84:
    b @L021e7004
    b @L021e6ebc
    b @L021e6ed4
    b @L021e6eec
    b @L021e6f04
    b @L021e6f1c
    b @L021e6f58
    b @L021e7004
    b @L021e7004
    b @L021e7004
    b @L021e6f70
    b @L021e6f88
    b @L021e6fa0
    b @L021e6fec
@L021e6ebc:
    mov r6, #0x1
    mov r8, #0x6
    mov r4, r6
    mov r5, r8
    ldr r10, [r0, #0x3d4]
    b @L021e7018
@L021e6ed4:
    mov r6, #0x1
    mov r8, #0x4
    mov r4, r6
    mov r5, r8
    ldr r10, [r0, #0x3d8]
    b @L021e7018
@L021e6eec:
    ldr r10, [r0, #0x3dc]
    mov r4, #0x2
    mov r5, #0x8
    mov r6, #0xc
    mov r8, #0xc0
    b @L021e7018
@L021e6f04:
    mov r6, #0x1
    mov r5, #0x8
    mov r4, r6
    mov r8, r5
    ldr r10, [r0, #0x3e0]
    b @L021e7018
@L021e6f1c:
    add r0, r9, #0x1300
    ldrh r0, [r0, #0xc4]
    mov r1, #0x9
    mov r4, #0x1
    mov r0, r0, lsl #0x1b
    mov r8, r0, lsr #0x1b
    sub r0, r8, #0x1
    bl _s32_div_f
    add r6, r0, #0x1
    add r0, r9, #0x1000
    mov r5, #0x9
    cmp r8, #0x9
    movlo r5, r8
    ldr r10, [r0, #0x3e4]
    b @L021e7018
@L021e6f58:
    mov r6, #0x1
    mov r8, #0x2
    mov r4, r6
    mov r5, r8
    ldr r10, [r0, #0x3f8]
    b @L021e7018
@L021e6f70:
    mov r6, #0x1
    mov r8, #0x2
    mov r4, r6
    mov r5, r8
    ldr r10, [r0, #0x3e8]
    b @L021e7018
@L021e6f88:
    ldr r10, [r0, #0x3ec]
    mov r6, #0x6
    mov r4, #0x1
    mov r5, #0xa
    mov r8, #0x3c
    b @L021e7018
@L021e6fa0:
    add r0, r9, #0x1300
    ldrh r0, [r0, #0xc4]
    mov r4, #0x2
    mov r7, #0x1
    mov r0, r0, lsl #0x10
    mov r8, r0, lsr #0x15
    sub r2, r8, #0x1
    mov r0, r2, asr #0x3
    add r1, r2, r2, lsr #0x1f
    add r0, r2, r0, lsr #0x1c
    mov r1, r1, asr #0x1
    mov r0, r0, asr #0x4
    add r5, r1, #0x1
    add r6, r0, #0x1
    add r0, r9, #0x1000
    cmp r5, #0x8
    movgt r5, #0x8
    ldr r10, [r0, #0x3f0]
    b @L021e7018
@L021e6fec:
    mov r4, #0x1
    mov r5, #0x8
    mov r6, r4
    mov r8, r5
    ldr r10, [r0, #0x3f4]
    b @L021e7018
@L021e7004:
    add r0, r9, #0xac
    bl func_0205cf10
    add r0, r9, #0xac
    bl func_0205cf1c
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
@L021e7018:
    add r0, r9, #0xac
    bl func_0205c53c
    mov r1, r4
    mov r2, r5
    mov r3, r7
    add r0, r9, #0xb0
    bl func_0205ba68
    mov r1, r4
    mov r2, r5
    mov r3, r7
    add r0, r9, #0x100
    bl func_0205ba68
    add r0, r9, #0xb0
    mov r1, r8
    bl func_0205bacc
    mov r1, r8
    add r0, r9, #0x100
    bl func_0205bacc
    str r6, [r9, #0xb4]
    str r6, [r9, #0x104]
    add r0, r9, #0xb0
    mov r1, r10
    bl func_0205bcdc
    mov r1, r10
    add r0, r9, #0x100
    bl func_0205bb04
    mov r0, #0x1
    strb r0, [r9, #0x140]
    strb r0, [r9, #0x141]
    add r0, r9, #0x1000
    mov r1, #0x0
    strb r1, [r0, #0x3a0]
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif
