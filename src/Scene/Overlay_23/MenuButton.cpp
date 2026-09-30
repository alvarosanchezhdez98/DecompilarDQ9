// The objects of type 1 of the menus (see MenuObjects.h): a button, a sprite that runs callbacks when it's touched
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "GameState/GameState.h"
#include "Scene/Overlay_11/MenuScript.h"
#include "System/TouchScreen.h"
#include "Text/MessageSystem.h"

extern "C"
{
    extern char data_02108760[];
    extern TouchState data_02114e54;

    void __clear(void* buffer, unsigned long size);

    void func_02012a84(TouchState* touch, int* x, int* y);
    MessageSystem* func_020421a0();
    void func_0205ac40(SpriteRenderer* renderer, Sprite* sprite);
    void func_0205eaa0(void* sound, int id, int);
}

// NONMATCHING: the C matches 92.3 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original stores the slots and reads them again before moving the other arguments of SetSlots
#ifdef NONMATCHING
int MenuObjectClass1::Initialize(MenuScript* script, int id, int heap, int sprites, int sprite)
{
    MenuObjectClass::Initialize();
    type_ = 1;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = NULL;
    state_ = 2;
    sprites_ = sprites;
    unk_3a = 1;
    cell_ = 0;
    cell2_ = 0;
    MenuObjectList* objects = script->GetObjects();
    MenuObjectClassA* object = (MenuObjectClassA*)objects->Find(sprites_);
    if (object == NULL)
        return 0;
    SpriteRenderer* renderer = object->GetRenderer();
    unsigned char screen = renderer->unk_50;
    sprite_ = sprite;
    unsigned short count = renderer->GetSprite(sprite_)->image_.unk_0;
    slots_ = objects->FindSlots(screen, count);
    objects->SetSlots(screen, slots_, count);
    unk_26 = 0;
    x_ = 0;
    y_ = 0;
    touchHeight_ = 0;
    touchWidth_ = 0;
    touchY_ = 0;
    touchX_ = 0;
    palette_ = -1;
    priority_ = -1;
    touchCallback_ = 0;
    holdCallback_ = 0;
    releaseCallback_ = 0;
    repeatCallback_ = 0;
    holdTime_ = 0;
    pressedRight_ = 0;
    pressedLeft_ = 0;
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN14MenuObjectList4FindEi(); // MenuObjectList::Find
    void _ZN14MenuObjectList8SetSlotsEijj(); // MenuObjectList::SetSlots
    void _ZN14MenuObjectList9FindSlotsEij(); // MenuObjectList::FindSlots
    void _ZN14SpriteRenderer9GetSpriteEt(); // SpriteRenderer::GetSprite
    void _ZN15MenuObjectClass10InitializeEv(); // MenuObjectClass::Initialize
    void _ZN16MenuObjectClassA11GetRendererEv(); // MenuObjectClassA::GetRenderer
}

asm int MenuObjectClass1::Initialize(MenuScript* script, int id, int heap, int sprites, int sprite)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r5, r0
    mov r4, r1
    mov r7, r2
    mov r6, r3
    bl _ZN15MenuObjectClass10InitializeEv
    mov r3, #0x1
    strh r3, [r5, #0x4]
    strh r7, [r5, #0x6]
    strh r6, [r5, #0x8]
    mov r2, #0x0
    strh r2, [r5, #0xa]
    str r2, [r5, #0x10]
    mov r1, #0x2
    ldr r0, [sp, #0x18]
    str r1, [r5, #0x1c]
    strh r0, [r5, #0x20]
    strb r3, [r5, #0x3a]
    strh r2, [r5, #0x44]
    mov r0, r4
    strh r2, [r5, #0x46]
    bl _ZN10MenuScript10GetObjectsEv
    ldrh r1, [r5, #0x20]
    mov r4, r0
    bl _ZN14MenuObjectList4FindEi
    cmp r0, #0x0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
    bl _ZN16MenuObjectClassA11GetRendererEv
    ldrb r6, [r0, #0x50]
    ldr r1, [sp, #0x1c]
    strh r1, [r5, #0x22]
    ldrh r1, [r5, #0x22]
    bl _ZN14SpriteRenderer9GetSpriteEt
    ldrh r7, [r0, #0x0]
    mov r0, r4
    mov r1, r6
    mov r2, r7
    bl _ZN14MenuObjectList9FindSlotsEij
    strh r0, [r5, #0x24]
    ldrh r2, [r5, #0x24]
    mov r1, r6
    mov r3, r7
    mov r0, r4
    bl _ZN14MenuObjectList8SetSlotsEijj
    mov r1, #0x0
    strh r1, [r5, #0x26]
    str r1, [r5, #0x28]
    str r1, [r5, #0x2c]
    strh r1, [r5, #0x36]
    strh r1, [r5, #0x34]
    strh r1, [r5, #0x32]
    strh r1, [r5, #0x30]
    sub r0, r1, #0x1
    strb r0, [r5, #0x38]
    strb r0, [r5, #0x39]
    strh r1, [r5, #0x3c]
    strh r1, [r5, #0x3e]
    strh r1, [r5, #0x40]
    strh r1, [r5, #0x42]
    strh r1, [r5, #0x48]
    strb r1, [r5, #0x4a]
    strb r1, [r5, #0x4b]
    mov r0, #0x1
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

void MenuObjectClass1::Finish(MenuObjectList* list)
{
    MenuObjectClassA* object = (MenuObjectClassA*)list->Find(sprites_);
    if (object == NULL)
        return;
    SpriteRenderer* renderer = object->GetRenderer();
    unsigned char screen = renderer->unk_50;
    list->ClearSlots(screen, slots_, renderer->GetSprite(sprite_)->image_.unk_0);
}

// NONMATCHING: the C matches 88.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The variables of the touched area get other registers
#ifdef NONMATCHING
void MenuObjectClass1::Update(MenuScript* script)
{
    if (!(flags_ & 8))
    {
        SpriteRenderer* renderer = ((MenuObjectClassA*)script->GetObjects()->Find(sprites_))->GetRenderer();
        Sprite* sprite = renderer->GetSprite(sprite_);
        MessageSystem* messages = func_020421a0();
        if (sprite != NULL)
        {
            int dx = 0;
            int dy = 0;
            if (pressedRight_)
            {
                dx = 0x1000;
                dy = 0x1000;
            }
            else if (pressedLeft_)
            {
                dx = -0x1000;
                dy = 0x1000;
            }
            signed char palette = sprite->unk_25;
            signed char priority = sprite->unk_26;
            sprite->unk_22 = slots_;
            sprite->x_ = x_ + dx;
            sprite->y_ = y_ + dy;
            if (palette_ >= 0)
                sprite->unk_25 = palette_ & 0xf;
            if (priority_ >= 0)
                sprite->unk_26 = priority_ & 3;
            unsigned short cell = cell_;
            if (cell2_ != 0 && (messages->unk_14c >= 2 ? 1 : 0))
                cell = cell2_;
            if (cell != 0)
                sprite->image_.unk_0 = cell;
            if ((messages->unk_14c >= 2 ? 1 : 0) && unk_3a)
            {
                unsigned short saved = sprite->image_.unk_0;
                if (saved > 2)
                {
                    sprite->image_.unk_0 = saved - 2;
                    func_0205ac40(renderer, sprite);
                    sprite->image_.unk_0 = saved;
                }
            }
            else
                func_0205ac40(renderer, sprite);
            sprite->x_ = x_;
            sprite->y_ = y_;
            pressedRight_ = 0;
            pressedLeft_ = 0;
            sprite->unk_25 = palette;
            sprite->unk_26 = priority;
        }
    }
    if (!(flags_ & 0x10))
    {
        unsigned char touching;
        int held = 0;
        touching = data_02114e54.touching_;
        if (data_02114e54.unk_5f != 0 && data_02114e54.unk_24 != 0)
            held = 1;
        unsigned char released = data_02114e54.unk_54;
        unsigned int delta = GameState::GetInstance()->GetEffectiveDeltaTime();
        unsigned short callback = 0;
        if (touching && !(flags_ & 0x20))
        {
            callback = touchCallback_;
            flags_ |= 0x20;
            holdTime_ = 500;
        }
        else if (held && (flags_ & 0x20))
        {
            callback = holdCallback_;
            if (holdTime_ > 0)
                holdTime_ -= delta;
            else if (repeatCallback_ != 0)
                callback = repeatCallback_;
        }
        else if (released && (flags_ & 0x20))
            callback = releaseCallback_;
        else
            flags_ &= ~0x20;
        if (callback != 0)
        {
            int x;
            int y;
            func_02012a84(&data_02114e54, &x, &y);
            int left = touchX_ + (x_ >> 12);
            int top = touchY_ + (y_ >> 12);
            int right = left + touchWidth_;
            int bottom = top + touchHeight_;
            int inside = 0;
            if (left <= x && x < right && top <= y && y < bottom)
                inside = 1;
            if (inside)
            {
                if (callback != 0)
                {
                    if (flags_ & 0x40)
                        func_0205eaa0(data_02108760, 1, 0);
                    script->RunCallback(callback);
                }
            }
            else
                flags_ &= ~0x20;
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript11RunCallbackEj(); // MenuScript::RunCallback
    void _ZN14MenuObjectList4FindEi(); // MenuObjectList::Find
    void _ZN14SpriteRenderer9GetSpriteEt(); // SpriteRenderer::GetSprite
    void _ZN16MenuObjectClassA11GetRendererEv(); // MenuObjectClassA::GetRenderer
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK9GameState21GetEffectiveDeltaTimeEv(); // GameState::GetEffectiveDeltaTime
}

asm void MenuObjectClass1::Update(MenuScript* script)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    sub sp, sp, #0x8
    mov r5, r0
    ldrb r0, [r5, #0xc]
    mov r4, r1
    tst r0, #0x8
    bne @L021fb038
    mov r0, r4
    bl _ZN10MenuScript10GetObjectsEv
    ldrh r1, [r5, #0x20]
    bl _ZN14MenuObjectList4FindEi
    bl _ZN16MenuObjectClassA11GetRendererEv
    ldrh r1, [r5, #0x22]
    mov r6, r0
    bl _ZN14SpriteRenderer9GetSpriteEt
    mov r7, r0
    bl func_020421a0
    cmp r7, #0x0
    beq @L021fb038
    ldrb r2, [r5, #0x4a]
    mov r3, #0x0
    mov r1, r3
    cmp r2, #0x0
    movne r3, #0x1000
    movne r1, r3
    bne @L021faf48
    ldrb r2, [r5, #0x4b]
    cmp r2, #0x0
    subne r3, r3, #0x1000
    movne r1, #0x1000
@L021faf48:
    ldrsb r8, [r7, #0x25]
    ldrsb r9, [r7, #0x26]
    ldrh r2, [r5, #0x24]
    strb r2, [r7, #0x22]
    ldr r2, [r5, #0x28]
    add r2, r2, r3
    str r2, [r7, #0x14]
    ldr r2, [r5, #0x2c]
    add r1, r2, r1
    str r1, [r7, #0x18]
    ldrsb r1, [r5, #0x38]
    cmp r1, #0x0
    andge r1, r1, #0xf
    strgeb r1, [r7, #0x25]
    ldrsb r1, [r5, #0x39]
    cmp r1, #0x0
    andge r1, r1, #0x3
    strgeb r1, [r7, #0x26]
    ldrh r3, [r5, #0x46]
    ldrh r2, [r5, #0x44]
    cmp r3, #0x0
    beq @L021fafb8
    ldr r1, [r0, #0x14c]
    cmp r1, #0x2
    movge r1, #0x1
    movlt r1, #0x0
    cmp r1, #0x0
    movne r2, r3
@L021fafb8:
    cmp r2, #0x0
    strneh r2, [r7, #0x0]
    ldr r0, [r0, #0x14c]
    cmp r0, #0x2
    movge r0, #0x1
    movlt r0, #0x0
    cmp r0, #0x0
    ldrneb r0, [r5, #0x3a]
    cmpne r0, #0x0
    beq @L021fb008
    ldrh r10, [r7, #0x0]
    cmp r10, #0x2
    bls @L021fb014
    sub r2, r10, #0x2
    mov r0, r6
    mov r1, r7
    strh r2, [r7, #0x0]
    bl func_0205ac40
    strh r10, [r7, #0x0]
    b @L021fb014
@L021fb008:
    mov r0, r6
    mov r1, r7
    bl func_0205ac40
@L021fb014:
    ldr r1, [r5, #0x28]
    mov r0, #0x0
    str r1, [r7, #0x14]
    ldr r1, [r5, #0x2c]
    str r1, [r7, #0x18]
    strb r0, [r5, #0x4a]
    strb r0, [r5, #0x4b]
    strb r8, [r7, #0x25]
    strb r9, [r7, #0x26]
@L021fb038:
    ldrb r0, [r5, #0xc]
    tst r0, #0x10
    bne @L021fb1b8
    ldr r0, =data_02114e54
    mov r7, #0x0
    ldrb r1, [r0, #0x5f]
    ldrb r6, [r0, #0x55]
    cmp r1, #0x0
    ldrneh r0, [r0, #0x24]
    cmpne r0, #0x0
    ldr r0, =data_02114e54
    movne r7, #0x1
    ldrb r8, [r0, #0x54]
    bl _ZN9GameState11GetInstanceEv
    bl _ZNK9GameState21GetEffectiveDeltaTimeEv
    cmp r6, #0x0
    mov r6, #0x0
    beq @L021fb0a4
    ldrb r1, [r5, #0xc]
    tst r1, #0x20
    bne @L021fb0a4
    ldrh r6, [r5, #0x3c]
    orr r1, r1, #0x20
    mov r0, #0x1f4
    strb r1, [r5, #0xc]
    strh r0, [r5, #0x48]
    b @L021fb104
@L021fb0a4:
    cmp r7, #0x0
    beq @L021fb0e0
    ldrb r1, [r5, #0xc]
    tst r1, #0x20
    beq @L021fb0e0
    ldrsh r1, [r5, #0x48]
    ldrh r6, [r5, #0x3e]
    cmp r1, #0x0
    subgt r0, r1, r0
    strgth r0, [r5, #0x48]
    bgt @L021fb104
    ldrh r0, [r5, #0x42]
    cmp r0, #0x0
    movne r6, r0
    b @L021fb104
@L021fb0e0:
    cmp r8, #0x0
    beq @L021fb0f8
    ldrb r0, [r5, #0xc]
    tst r0, #0x20
    ldrneh r6, [r5, #0x40]
    bne @L021fb104
@L021fb0f8:
    ldrb r0, [r5, #0xc]
    bic r0, r0, #0x20
    strb r0, [r5, #0xc]
@L021fb104:
    cmp r6, #0x0
    beq @L021fb1b8
    ldr r0, =data_02114e54
    add r1, sp, #0x4
    add r2, sp, #0x0
    bl func_02012a84
    ldrsh r0, [r5, #0x30]
    ldr r1, [r5, #0x28]
    ldrsh r3, [r5, #0x32]
    add r8, r0, r1, asr #0xc
    ldr r7, [r5, #0x2c]
    ldr r0, [sp, #0x4]
    ldrsh r2, [r5, #0x34]
    add r7, r3, r7, asr #0xc
    ldrsh r1, [r5, #0x36]
    add r3, r8, r2
    cmp r8, r0
    add r2, r7, r1
    ldr r1, [sp, #0x0]
    mov r8, #0x0
    bgt @L021fb170
    cmp r0, r3
    bge @L021fb170
    cmp r7, r1
    bgt @L021fb170
    cmp r1, r2
    movlt r8, #0x1
@L021fb170:
    cmp r8, #0x0
    beq @L021fb1ac
    cmp r6, #0x0
    beq @L021fb1b8
    ldrb r0, [r5, #0xc]
    tst r0, #0x40
    beq @L021fb19c
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
@L021fb19c:
    mov r0, r4
    mov r1, r6
    bl _ZN10MenuScript11RunCallbackEj
    b @L021fb1b8
@L021fb1ac:
    ldrb r0, [r5, #0xc]
    bic r0, r0, #0x20
    strb r0, [r5, #0xc]
@L021fb1b8:
    add sp, sp, #0x8
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif

void MenuObjectClass1::SetPosition(Vector3fix* position)
{
    x_ = position->x;
    y_ = position->y;
}

Vector3fix MenuObjectClass1::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_;
    // Not y: a bug of the game
    position.z = y_;
    return position;
}

void MenuObjectClass1::V3c(short value)
{
    unk_26 = value;
}

int MenuObjectClass1::V40()
{
    return unk_26;
}

void MenuObjectClass1::Va4(int callback)
{
    touchCallback_ = callback;
}

int MenuObjectClass1::GetTouchCallback()
{
    return touchCallback_;
}

void MenuObjectClass1::Vac(int touch, int hold, int release)
{
    touchCallback_ = touch;
    holdCallback_ = hold;
    releaseCallback_ = release;
}

void MenuObjectClass1::Vb0(int callback)
{
    repeatCallback_ = callback;
}

int MenuObjectClass1::Vb4()
{
    return repeatCallback_;
}

void MenuObjectClass1::SetTouchArea(int x, int y, int width, int height)
{
    touchX_ = x;
    touchY_ = y;
    touchWidth_ = width;
    touchHeight_ = height;
}

void MenuObjectClass1::SetPalette(signed char palette)
{
    palette_ = palette;
}

void MenuObjectClass1::SetSprite(unsigned short sprite)
{
    sprite_ = sprite;
}

void MenuObjectClass1::SetPriority(signed char priority)
{
    priority_ = priority;
}
