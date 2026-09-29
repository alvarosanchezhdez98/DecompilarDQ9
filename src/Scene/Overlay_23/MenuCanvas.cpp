// The objects of type 6 of the menus (see MenuObjects.h): a canvas on a background that the texts (type 8), numbers
// (type 15) and boxes (type 19) are drawn on
#pragma ipa file
#pragma dont_inline on
#include "Scene/Overlay_23/MenuObjects.h"
#include "GameState/GameState.h"
#include "Scene/Overlay_11/MenuScript.h"
#include "System/TouchScreen.h"
#include "Text/MessageSystem.h"

// A glyph of a font
struct MenuGlyph
{
    char unk_0[4];
    signed char width_;
};

extern "C"
{
    extern TouchState data_02114e54;

    void __clear(void* buffer, unsigned long size);

    void func_02012a84(TouchState* touch, int* x, int* y);
    int func_020420e8(const char* text, int font);
    int func_02042190(int font);
    MessageSystem* func_020421a0();
    MenuGlyph* func_0204254c(const char* text, int);
    void func_02046608(MessageSystem* messages, int, const char* input, char* output, int, int, int);
    void func_0204bc74(BackgroundGraphics* background, int tile, short x, short y, short width, short height, int);
    void func_0204c684(Canvas* canvas);
    void func_0204c754(Canvas* canvas);
    void func_0204c7a8(Canvas* canvas, SafeAllocator* allocator, void* pixels, int size);
    int func_0204c7e0(Canvas* canvas);
    void func_0204c804(Canvas* canvas);
    void func_0204c87c(Canvas* canvas, int ticks);
    void func_0204c8f0(Canvas* canvas);
    void func_0204f160(Canvas* canvas, int, short id);
    void func_0204f174(Canvas* canvas, short x, short y, short width, int height, unsigned char, unsigned char,
                       unsigned char, int);
    void func_0204f41c(Canvas* canvas, short x, short y, const char* text, unsigned char font, unsigned char color,
                       unsigned short* width, unsigned short* height, int);
    void func_0204f7e8(Canvas* canvas, short x, short y, int value, unsigned char font, unsigned char color,
                       unsigned short* width, unsigned short* height, int, int, int, int);
    void func_0204f914(Canvas* canvas, unsigned char color, short x, short y, short right, short bottom);
    void func_0204fae8(Canvas* canvas);
    void func_0204fbf8(Canvas* canvas);
    int func_0204fd00(Canvas* canvas, int corner);
    const char* func_02072a68(TextTable* texts, short id);
    void func_0206819c(const char* text, char* output, int font);
}

// The separator of the pages
static const char sSeparator[] = "/";

// NONMATCHING: the C matches 97.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original sets the 0 of the flags before storing the heap
#ifdef NONMATCHING
int MenuObjectClass6::Initialize(MenuScript* script, int id, int heap, int background, int width, int height,
                                 int frame, int parent)
{
    MenuObjectClass::Initialize();
    type_ = 6;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = NULL;
    state_ = 2;
    pages_ = 0;
    page_ = 0;
    color_ = 15;
    unk_10c = 0;
    unk_10e = 1;
    func_0204c684(&canvas_);
    MenuHeap* menuHeap = script->FindHeap(heap_);
    if (menuHeap == NULL)
        return 0;
    void* buffer = script->GetBuffer();
    if (buffer == NULL)
        return 0;
    int tiles = width * height;
    if (menuHeap->allocator_.GetMaxPossibleAllocation() < tiles * 2)
        return 0;
    func_0204c7a8(&canvas_, &menuHeap->allocator_, buffer, tiles * 2);
    MenuObjectList* objects = script->GetObjects();
    MenuObjectClass2* owner = (MenuObjectClass2*)objects->Find(background);
    if (owner == NULL)
        return 0;
    canvas_.background_ = owner->GetBackground();
    frame_ = frame;
    MenuObjectClass6* other = (MenuObjectClass6*)objects->Find(parent);
    if (other != NULL)
        canvas_.unk_0 = &other->canvas_;
    return 1;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript8FindHeapEi(); // MenuScript::FindHeap
    void _ZN10MenuScript9GetBufferEv(); // MenuScript::GetBuffer
    void _ZN14MenuObjectList4FindEi(); // MenuObjectList::Find
    void _ZN15MenuObjectClass10InitializeEv(); // MenuObjectClass::Initialize
    void _ZN16MenuObjectClass213GetBackgroundEv(); // MenuObjectClass2::GetBackground
    void _ZNK13SafeAllocator24GetMaxPossibleAllocationEv(); // SafeAllocator::GetMaxPossibleAllocation
}

asm int MenuObjectClass6::Initialize(MenuScript* script, int id, int heap, int background, int width, int height,
                                 int frame, int parent)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    mov r5, r0
    mov r4, r1
    mov r7, r2
    mov r6, r3
    bl _ZN15MenuObjectClass10InitializeEv
    mov r0, #0x6
    strh r0, [r5, #0x4]
    strh r7, [r5, #0x6]
    mov r2, #0x0
    strh r6, [r5, #0x8]
    strh r2, [r5, #0xa]
    str r2, [r5, #0x10]
    mov r0, #0x2
    str r0, [r5, #0x1c]
    add r0, r5, #0x100
    strh r2, [r0, #0x6]
    strh r2, [r0, #0x4]
    mov r1, #0xf
    strb r1, [r5, #0x10a]
    strh r2, [r0, #0xc]
    mov r1, #0x1
    strh r1, [r0, #0xe]
    add r0, r5, #0x20
    bl func_0204c684
    ldrh r1, [r5, #0x8]
    mov r0, r4
    bl _ZN10MenuScript8FindHeapEi
    movs r8, r0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    mov r0, r4
    bl _ZN10MenuScript9GetBufferEv
    movs r7, r0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    ldr r2, [sp, #0x24]
    ldr r1, [sp, #0x28]
    add r0, r8, #0x4
    mul r6, r2, r1
    mov r9, r6, lsl #0x1
    bl _ZNK13SafeAllocator24GetMaxPossibleAllocationEv
    cmp r0, r6, lsl #0x1
    movlo r0, #0x0
    ldmloia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    mov r2, r7
    mov r3, r9
    add r0, r5, #0x20
    add r1, r8, #0x4
    bl func_0204c7a8
    mov r0, r4
    bl _ZN10MenuScript10GetObjectsEv
    ldr r1, [sp, #0x20]
    mov r4, r0
    bl _ZN14MenuObjectList4FindEi
    cmp r0, #0x0
    moveq r0, #0x0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    bl _ZN16MenuObjectClass213GetBackgroundEv
    str r0, [r5, #0x24]
    ldr r2, [sp, #0x2c]
    ldr r1, [sp, #0x30]
    mov r0, r4
    strb r2, [r5, #0x108]
    bl _ZN14MenuObjectList4FindEi
    cmp r0, #0x0
    addne r0, r0, #0x20
    strne r0, [r5, #0x20]
    mov r0, #0x1
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
}
#endif

// NONMATCHING: the C matches 86.9 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original keeps the height in a saved register between the first calls instead of reading it from the stack
#ifdef NONMATCHING
void MenuObjectClass6::Setup(MenuScript* script, int unk, short x, short y, short width, int height,
                             unsigned char unk2, unsigned char unk3, bool unk4)
{
    func_0204f160(&canvas_, unk, id_);
    func_0204f174(&canvas_, x, y, width, height, unk2, unk3, unk4, 0);
    if (flags_ & 4)
    {
        if (pages_ > 1)
            func_0204fae8(&canvas_);
        unsigned char color;
        int separator;
        short top;
        top = (short)(height * 8) - 13;
        separator = 0;
        color = color_;
        MenuGlyph* glyph = func_0204254c(sSeparator, 0);
        if (glyph != NULL)
            separator = glyph->width_;
        unsigned short textWidth;
        unsigned short textHeight;
        short center = width * 4;
        func_0204f7e8(&canvas_, center - separator, top, page_ + 1, 8, color, &textWidth, &textHeight, 1, 3, 0, 0);
        func_0204f7e8(&canvas_, center + separator + 1, top, pages_, 8, color, &textWidth, &textHeight, 0, 3, 0, 0);
        func_0204f41c(&canvas_, center - (separator >> 1), top, sSeparator, 8, color, &textWidth, &textHeight, 0);
    }
    DrawObjects(script);
    func_0204fbf8(&canvas_);
    x_ = x * 8;
    y_ = y * 8;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN16MenuObjectClass611DrawObjectsEP10MenuScript(); // MenuObjectClass6::DrawObjects
}

asm void MenuObjectClass6::Setup(MenuScript* script, int unk, short x, short y, short width, int height,
                             unsigned char unk2, unsigned char unk3, bool unk4)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, lr}
    sub sp, sp, #0x24
    mov r9, r0
    mov r8, r1
    mov r1, r2
    ldrsh r2, [r9, #0x6]
    add r0, r9, #0x20
    mov r7, r3
    ldr r6, [sp, #0x50]
    bl func_0204f160
    ldrb r0, [sp, #0x54]
    str r6, [sp, #0x0]
    ldrb r1, [sp, #0x58]
    str r0, [sp, #0x4]
    ldrb r0, [sp, #0x5c]
    str r1, [sp, #0x8]
    ldrsh r2, [sp, #0x48]
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    ldrsh r3, [sp, #0x4c]
    add r0, r9, #0x20
    mov r1, r7
    bl func_0204f174
    ldrb r0, [r9, #0xc]
    tst r0, #0x4
    beq @L021f8064
    add r0, r9, #0x100
    ldrsh r0, [r0, #0x6]
    cmp r0, #0x1
    ble @L021f7f3c
    add r0, r9, #0x20
    bl func_0204fae8
@L021f7f3c:
    mov r0, r6, lsl #0x13
    mov r0, r0, asr #0x10
    sub r0, r0, #0xd
    mov r2, r0, lsl #0x10
    mov r5, #0x0
    ldr r0, =sSeparator
    mov r1, r5
    mov r6, r2, asr #0x10
    ldrb r4, [r9, #0x10a]
    bl func_0204254c
    cmp r0, #0x0
    ldrnesb r5, [r0, #0x4]
    mov r0, #0x8
    add r1, sp, #0x22
    stmia sp, {r0, r4}
    str r1, [sp, #0x8]
    ldrsh r1, [sp, #0x4c]
    add r0, sp, #0x20
    str r0, [sp, #0xc]
    mov r10, r1, lsl #0x12
    mov r2, #0x1
    rsb r0, r5, r10, asr #0x10
    mov r1, r0, lsl #0x10
    str r2, [sp, #0x10]
    mov r0, #0x3
    str r0, [sp, #0x14]
    mov r0, #0x0
    str r0, [sp, #0x18]
    str r0, [sp, #0x1c]
    add r0, r9, #0x100
    ldrsh r3, [r0, #0x4]
    mov r2, r6
    add r0, r9, #0x20
    mov r1, r1, asr #0x10
    add r3, r3, #0x1
    bl func_0204f7e8
    mov r0, #0x8
    str r0, [sp, #0x0]
    add r0, r5, r10, asr #0x10
    add r0, r0, #0x1
    add r2, sp, #0x22
    str r4, [sp, #0x4]
    str r2, [sp, #0x8]
    add r1, sp, #0x20
    str r1, [sp, #0xc]
    mov r2, #0x0
    str r2, [sp, #0x10]
    mov r1, #0x3
    str r1, [sp, #0x14]
    str r2, [sp, #0x18]
    str r2, [sp, #0x1c]
    add r1, r9, #0x100
    ldrsh r3, [r1, #0x6]
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    mov r2, r6
    add r0, r9, #0x20
    bl func_0204f7e8
    mov r0, r5, asr #0x1
    rsb r0, r0, r10, asr #0x10
    mov r0, r0, lsl #0x10
    mov r1, r0, asr #0x10
    mov r0, #0x8
    stmia sp, {r0, r4}
    add r3, sp, #0x22
    str r3, [sp, #0x8]
    add r0, sp, #0x20
    str r0, [sp, #0xc]
    mov r0, #0x0
    str r0, [sp, #0x10]
    ldr r3, =sSeparator
    mov r2, r6
    add r0, r9, #0x20
    bl func_0204f41c
@L021f8064:
    mov r0, r9
    mov r1, r8
    bl _ZN16MenuObjectClass611DrawObjectsEP10MenuScript
    add r0, r9, #0x20
    bl func_0204fbf8
    ldrsh r1, [sp, #0x48]
    mov r2, r7, lsl #0x3
    add r0, r9, #0x100
    strh r2, [r0, #0x0]
    mov r1, r1, lsl #0x3
    strh r1, [r0, #0x2]
    add sp, sp, #0x24
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif

// NONMATCHING: the C matches 0.0 %, so the build uses the original's instructions after #else (see Decompiling.md). The
// original computes the two flags first and uses one more saved register (r6)
#ifdef NONMATCHING
void MenuObjectClass6::Refresh(MenuScript* script)
{
    if (!func_0204c7e0(&canvas_))
        return;
    Setup(script, 0, canvas_.x_, canvas_.y_, canvas_.width_, canvas_.height_, canvas_.unk_c2,
          (canvas_.flags_ & 4) != 0, (canvas_.flags_ & 0x10) != 0);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb(); // MenuObjectClass6::Setup
}

asm void MenuObjectClass6::Refresh(MenuScript* script)
{
    stmdb sp!, {r4, r5, r6, lr}
    sub sp, sp, #0x18
    mov r5, r0
    add r0, r5, #0x20
    mov r4, r1
    bl func_0204c7e0
    cmp r0, #0x0
    beq @L021f8118
    ldrb r1, [r5, #0xe5]
    ldrh r0, [r5, #0xe2]
    mov r2, #0x0
    tst r1, #0x4
    movne lr, #0x1
    moveq lr, #0x0
    tst r1, #0x10
    ldrsh r1, [r5, #0xce]
    and r3, r0, #0xff
    movne r6, #0x1
    str r1, [sp, #0x0]
    ldrsh r12, [r5, #0xc8]
    mov r1, r4
    moveq r6, #0x0
    str r12, [sp, #0x4]
    ldrsh r4, [r5, #0xca]
    mov r0, r5
    str r4, [sp, #0x8]
    str r3, [sp, #0xc]
    str lr, [sp, #0x10]
    str r6, [sp, #0x14]
    ldrsh r3, [r5, #0xcc]
    bl _ZN16MenuObjectClass65SetupEP10MenuScriptisssihhb
@L021f8118:
    add sp, sp, #0x18
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void MenuObjectClass6::Clear()
{
    func_0204c804(&canvas_);
}

void MenuObjectClass6::Finish(MenuObjectList* list)
{
    func_0204c754(&canvas_);
}

void MenuObjectClass6::Update(MenuScript* script)
{
    if (flags_ & 8)
        return;
    func_0204c87c(&canvas_, GameState::GetInstance()->GetTickCount());
    func_0204c8f0(&canvas_);
    if (!(canvas_.flags_ & 4))
        return;
    DrawFrame(script);
}

void MenuObjectClass6::Draw1()
{
}

void MenuObjectClass6::Draw2()
{
}

void MenuObjectClass6::SetPosition(Vector3fix* position)
{
    x_ = position->x / 4096.0f;
    y_ = position->y / 4096.0f;
    unsigned short y = y_;
    canvas_.x_ = x_;
    canvas_.y_ = y;
}

Vector3fix MenuObjectClass6::GetPosition()
{
    Vector3fix position = {0};
    position.x = x_ << 12;
    position.y = y_ << 12;
    return position;
}

void MenuObjectClass6::DrawObjects(MenuScript* script)
{
    MenuObjectList* objects = script->GetObjects();
    for (MenuObjectClass* object = objects->GetAt(0); object != NULL; object = object->GetNext())
    {
        int kind = 0;
        if (!(object->flags_ & 8))
        {
            switch (object->GetType())
            {
            case 8:
                kind = 1;
                break;
            case 15:
                kind = 2;
                break;
            case 19:
                kind = 3;
                break;
            }
        }
        if (kind == 1)
        {
            MenuObjectClass8* text = (MenuObjectClass8*)object;
            int size;
            const char* string;
            int formatted;
            unsigned char font;
            if (text->canvas_ != id_)
                continue;
            string = text->text_;
            if (string == NULL)
            {
                MenuObjectClass4* texts = (MenuObjectClass4*)objects->Find(text->texts_);
                if (texts != NULL && texts->GetType() == 4)
                    string = func_02072a68(texts->GetTexts(), text->textId_);
            }
            if (string == NULL)
                continue;
            Vector3fix position = text->GetPosition();
            font = text->font_;
            unsigned char color = text->GetColor();
            short left = unk_10c + font;
            short right = unk_10e + font;
            canvas_.unk_b4 = left;
            canvas_.unk_b6 = right;
            formatted = text->formatted_;
            size = func_02042190(text->font_);
            char codes[0x100] = {0};
            char formattedText[0x100] = {0};
            if (formatted)
            {
                func_0206819c(string, codes, size);
                func_02046608(func_020421a0(), 10, codes, formattedText, 0x400, 0, 0);
                string = formattedText;
            }
            int width = func_020420e8(string, size);
            int x = position.x / 4096.0f;
            int y = position.y / 4096.0f;
            switch (text->alignment_)
            {
            case 1:
                break;
            case 3:
                x -= width >> 1;
                break;
            case 2:
                x -= width;
                break;
            }
            unsigned short textWidth;
            unsigned short textHeight;
            func_0204f41c(&canvas_, x, y, string, font, color, &textWidth, &textHeight, 0);
            text->SetWidth(textWidth);
            text->SetHeight(textHeight);
        }
        else if (kind == 2)
        {
            MenuObjectClassF* number = (MenuObjectClassF*)object;
            if (number->canvas_ != id_)
                continue;
            unsigned char font = number->font_;
            int value = number->GetValue();
            unsigned char unk3b = number->unk_3b;
            unsigned char unk3c = number->unk_3c;
            unsigned char color = number->GetColor();
            Vector3fix position = number->GetPosition();
            unsigned char unk3d = number->unk_3d;
            canvas_.unk_b4 = font;
            canvas_.unk_b6 = font + 1;
            int x = position.x / 4096.0f;
            int y = position.y / 4096.0f;
            unsigned short textWidth;
            unsigned short textHeight;
            func_0204f7e8(&canvas_, x, y, value, font, color, &textWidth, &textHeight, unk3b, unk3c, 0, unk3d);
            number->SetWidth(textWidth);
            number->SetHeight(textHeight);
        }
        else if (kind == 3)
        {
            MenuObjectClass13* box = (MenuObjectClass13*)object;
            if (box->canvas_ != id_)
                continue;
            unsigned char color = box->GetColor();
            Vector3fix position = box->GetPosition();
            unsigned short x = position.x / 4096.0f;
            unsigned short y = position.y / 4096.0f;
            unsigned short right = box->GetWidth() + x;
            unsigned short bottom = box->GetHeight() + y;
            func_0204f914(&canvas_, color, x, y, right, bottom);
        }
    }
}

void MenuObjectClass6::DrawFrame(MenuScript* script)
{
    MenuObjectClass2* owner = (MenuObjectClass2*)script->GetObjects()->Find(frame_);
    if (owner == NULL)
        return;
    BackgroundGraphics* background = owner->GetBackground();
    if (!func_0204c7e0(&canvas_))
        return;
    if (canvas_.flags_ & 0x20)
        return;
    if (canvas_.flags_ & 0x80)
        return;
    short x = canvas_.x_;
    short y = canvas_.y_;
    short width = canvas_.width_;
    short height = canvas_.unk_c0;
    func_0204bc74(background, 1, x, y, width, height, 0);
    if (height == 0)
        return;
    if (!func_0204fd00(&canvas_, 1))
        func_0204bc74(background, 2, x, y, 1, 1, 0);
    if (!func_0204fd00(&canvas_, 2))
        func_0204bc74(background, 0x402, x + width - 1, y, 1, 1, 0);
    if (!func_0204fd00(&canvas_, 4))
        func_0204bc74(background, 0x802, x, y + height - 1, 1, 1, 0);
    if (!func_0204fd00(&canvas_, 8))
        func_0204bc74(background, 0xc02, x + width - 1, y + height - 1, 1, 1, 0);
}

void MenuObjectClass6::Select(MenuScript* script, int id)
{
    for (MenuObjectClass* object = script->GetObjects()->GetAt(0); object != NULL; object = object->GetNext())
    {
        if (object->GetType() == 8 && ((MenuObjectClass8*)object)->canvas_ == id_)
        {
            if (id == object->GetId())
                ((MenuObjectClass8*)object)->selected_ = 1;
            else
                ((MenuObjectClass8*)object)->selected_ = 0;
        }
    }
    Refresh(script);
}

void MenuObjectClass6::SetUnkC2(MenuScript* script, unsigned char value, int refresh)
{
    canvas_.unk_c2 = value & 0xf;
    if (refresh)
        Refresh(script);
}

void MenuObjectClass6::SetUnk10c(short a, short b)
{
    unk_10c = a;
    unk_10e = b;
}

// NONMATCHING: the C matches 63.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The four sizes of the canvas get other registers and the comparisons are in another order
#ifdef NONMATCHING
int MenuObjectClass6::ContainsTouch()
{
    short x = canvas_.x_;
    short y = canvas_.y_;
    short width = canvas_.width_;
    short height = canvas_.height_;
    int touchX;
    int touchY;
    func_02012a84(&data_02114e54, &touchX, &touchY);
    if (touchX >= (short)(x * 8) && touchX < (short)(x * 8) + (short)(width * 8) && touchY >= (short)(y * 8) &&
        touchY < (short)(y * 8) + (short)(height * 8))
        return 1;
    return 0;
}
#else
asm int MenuObjectClass6::ContainsTouch()
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x8
    ldrsh r6, [r0, #0xcc]
    ldrsh r4, [r0, #0xce]
    ldrsh r7, [r0, #0xc8]
    ldrsh r5, [r0, #0xca]
    ldr r0, =data_02114e54
    add r1, sp, #0x4
    add r2, sp, #0x0
    bl func_02012a84
    mov r0, r6, lsl #0x13
    ldr r2, [sp, #0x4]
    mov r1, r0, asr #0x10
    cmp r2, r0, asr #0x10
    blt @L021f89e4
    mov r0, r7, lsl #0x13
    add r0, r1, r0, asr #0x10
    cmp r2, r0
    bge @L021f89e4
    ldr r2, [sp, #0x0]
    mov r0, r4, lsl #0x13
    cmp r2, r0, asr #0x10
    mov r1, r0, asr #0x10
    blt @L021f89e4
    mov r0, r5, lsl #0x13
    add r0, r1, r0, asr #0x10
    cmp r2, r0
    movlt r0, #0x1
    blt @L021f89e8
@L021f89e4:
    mov r0, #0x0
@L021f89e8:
    add sp, sp, #0x8
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif
