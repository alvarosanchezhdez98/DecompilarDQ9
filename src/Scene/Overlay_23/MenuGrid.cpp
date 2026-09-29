// The objects of type 7 of the menus (see MenuObjects.h): a grid of objects with a cursor that the pad and the touch
// screen move
// Unlike the other objects' files, without `#pragma dont_inline on`: the copy of a text's position in Update() is
// inline, member by member
#pragma ipa file
#include "Scene/Overlay_23/MenuObjects.h"
#include "GameState/GameState.h"
#include "Scene/Overlay_11/MenuScript.h"
#include "System/Matrix.h"
#include "System/TouchScreen.h"
#include <std_library_functions.h>

#define REG_MASTER_BRIGHT ((volatile unsigned short*)0x0400006c)
#define REG_MASTER_BRIGHT_SUB ((volatile unsigned short*)0x0400106c)

#define PAD_BUTTON_A 1
#define PAD_BUTTON_B 2
#define PAD_BUTTON_SELECT 4
#define PAD_KEY_RIGHT 0x10
#define PAD_KEY_LEFT 0x20
#define PAD_KEY_UP 0x40
#define PAD_KEY_DOWN 0x80
#define PAD_BUTTON_R 0x100
#define PAD_BUTTON_L 0x200
#define PAD_BUTTON_X 0x400
#define PAD_BUTTON_Y 0x800

extern "C"
{
    extern char data_02108760[];
    extern char data_02114e30[];
    extern TouchState data_02114e54;

    void __clear(void* buffer, unsigned long size);

    bool func_02012430(void* pad, int buttons);
    bool func_02012444(void* pad, int buttons);
    void func_02012a84(TouchState* touch, int* x, int* y);
    int func_02047a3c(void* model, int);
    int func_02047a5c(void* model, int);
    void func_0205eaa0(void* sound, int id, int);
    int func_020c39c8(volatile unsigned short* reg);

    // The floating point functions that the compiler calls, for the assembly
    void _fdiv();
    void _ffix();
    void _fflt();
}

// The keys whose entries and callbacks the grid has
static const struct
{
    unsigned short count;
    unsigned short keys[5];
} sKeys = {5, {PAD_BUTTON_SELECT, PAD_BUTTON_Y, PAD_BUTTON_X, PAD_BUTTON_L, PAD_BUTTON_R}};

// In milliseconds, until a held key moves the cursor again
static unsigned int sRepeatTime;

int MenuObjectClass7::Initialize(MenuScript* script, int id, int heap, int rows, int columns)
{
    MenuObjectClass::Initialize();
    type_ = 7;
    id_ = id;
    heap_ = heap;
    vramState_ = 0;
    file_ = NULL;
    rows_ = rows;
    columns_ = columns;
    row_ = 0;
    column_ = 0;
    offset_.x = 0;
    offset_.y = 0;
    offset_.z = 0;
    moved_ = 1;
    state_ = 2;
    MenuHeap* menuHeap = script->FindHeap(heap_);
    if (menuHeap == NULL)
        return 0;
    int size = rows * 2 * columns;
    items_ = (unsigned short*)menuHeap->allocator_.Allocate(size);
    if (items_ == NULL)
        return 0;
    memset(items_, 0, size);
    xEntry_ = 0;
    yEntry_ = 0;
    aCallback_ = 0;
    aEntry_ = 0;
    bEntry_ = 0;
    bCallback_ = 0;
    pageCallback_ = 0;
    selectCallback_ = 0;
    upCallback_ = 0;
    downCallback_ = 0;
    yCallback_ = 0;
    xCallback_ = 0;
    rightCallback_ = 0;
    leftCallback_ = 0;
    lCallback_ = 0;
    rCallback_ = 0;
    sRepeatTime = 500;
    page_ = 0;
    pages_ = 1;
    wrap_ = 1;
    sound_ = 1;
    xConfirms_ = 0;
    return 1;
}

// NONMATCHING: the C matches 97.5 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Where the original sets fading to 0, and the registers of the two indexes of the selected cell
#ifdef NONMATCHING
void MenuObjectClass7::Update(MenuScript* script)
{
    if (id_ != script->GetUnk1b0() || (flags_ & 0x10))
        return;
    GetIndex();
    int fading = 0;
    if (func_020c39c8(REG_MASTER_BRIGHT) != 0 && func_020c39c8(REG_MASTER_BRIGHT_SUB) != 0)
        fading = 1;
    MenuObjectList* objects = script->GetObjects();
    int row = row_;
    int column = column_;
    int confirmed = 0;
    unsigned short entries[5] = {0, yEntry_, xEntry_};
    unsigned short callbacks[5] = {selectCallback_, yCallback_, xCallback_, lCallback_, rCallback_};
    if (!fading)
    {
        for (int i = 0; i < sKeys.count; i++)
        {
            if (func_02012444(data_02114e30, sKeys.keys[i]))
            {
                int done = 0;
                if (entries[i] != 0)
                {
                    script->StartEntry(entries[i]);
                    done = 1;
                }
                if (callbacks[i] != 0)
                {
                    script->RunCallback(callbacks[i]);
                    done = 1;
                }
                if (done)
                    return;
            }
        }
    }
    int x = 0;
    if (xConfirms_ && func_02012444(data_02114e30, PAD_BUTTON_X))
        x = 1;
    if (func_02012444(data_02114e30, PAD_BUTTON_A) || x)
        confirmed = 1;
    int up = func_02012444(data_02114e30, PAD_KEY_UP);
    int down = func_02012444(data_02114e30, PAD_KEY_DOWN);
    int left = func_02012444(data_02114e30, PAD_KEY_LEFT);
    int right = func_02012444(data_02114e30, PAD_KEY_RIGHT);
    if (!confirmed)
    {
        unsigned int delta = GameState::GetInstance()->GetEffectiveDeltaTime();
        if (func_02012430(data_02114e30, PAD_KEY_UP))
        {
            if (sRepeatTime < delta)
                up = 1;
            else
                sRepeatTime -= delta;
        }
        else if (func_02012430(data_02114e30, PAD_KEY_DOWN))
        {
            if (sRepeatTime < delta)
                down = 1;
            else
                sRepeatTime -= delta;
        }
        else if (func_02012430(data_02114e30, PAD_KEY_LEFT))
        {
            if (sRepeatTime < delta)
                left = 1;
            else
                sRepeatTime -= delta;
        }
        else if (func_02012430(data_02114e30, PAD_KEY_RIGHT))
        {
            if (sRepeatTime < delta)
                right = 1;
            else
                sRepeatTime -= delta;
        }
        else
            sRepeatTime = 500;
    }
    int moved = 0;
    if (up)
    {
        row--;
        if (upCallback_ != 0)
        {
            script->RunCallback(upCallback_);
            return;
        }
    }
    else if (down)
    {
        row++;
        if (downCallback_ != 0)
        {
            script->RunCallback(downCallback_);
            return;
        }
    }
    else if (left)
    {
        column--;
        if (leftCallback_ != 0)
        {
            script->RunCallback(leftCallback_);
            return;
        }
    }
    else if (right)
    {
        column++;
        if (rightCallback_ != 0)
        {
            script->RunCallback(rightCallback_);
            return;
        }
    }
    int page = 0;
    if (wrap_)
    {
        int first;
        for (first = 0; first < rows_; first++)
        {
            if (items_[first * columns_ + column_] != 0)
                break;
        }
        int last;
        for (last = rows_ - 1; last >= 0; last--)
        {
            if (items_[last * columns_ + column_] != 0)
                break;
        }
        int firstColumn;
        for (firstColumn = 0; firstColumn < columns_; firstColumn++)
        {
            if (items_[row_ * columns_ + firstColumn] != 0)
                break;
        }
        int lastColumn;
        for (lastColumn = columns_ - 1; lastColumn >= 0; lastColumn--)
        {
            if (items_[row_ * columns_ + lastColumn] != 0)
                break;
        }
        if (row < first)
            row = last;
        else if (last < row)
            row = first;
        else if (column < firstColumn)
        {
            column = firstColumn;
            page = -1;
            if (pages_ == 1)
                column = lastColumn;
        }
        else if (lastColumn < column)
        {
            column = lastColumn;
            page = 1;
            if (pages_ == 1)
                column = firstColumn;
        }
    }
    else if (row < 0)
        row = 0;
    else if (rows_ <= row)
        row = rows_ - 1;
    else if (column < 0)
    {
        column = 0;
        page = -1;
    }
    else if (columns_ <= column)
    {
        column = columns_ - 1;
        page = 1;
    }
    int index = row * columns_ + column;
    if (pages_ == 1)
        page = 0;
    if (items_[index] == 0)
    {
        row = row_;
        column = column_;
    }
    if (row != row_ || column != column_)
    {
        moved = 1;
        MenuObjectClass6* canvas = GetCanvas(script, objects->Find(items_[GetIndex()]));
        if (canvas != NULL)
            canvas->Select(script, 0x8000);
    }
    if (!moved && data_02114e54.touching_)
    {
        int touchX;
        int touchY;
        func_02012a84(&data_02114e54, &touchX, &touchY);
        page = GetTouchedArrow(script, touchX, touchY);
        if (page == 0)
        {
            int left;
            int top;
            int width;
            int height;
            int count = columns_ * rows_;
            for (int i = 0; i < count; i++)
            {
                height = 0;
                width = 0;
                top = 0;
                left = 0;
                if (items_[i] == 0)
                    continue;
                MenuObjectClass* item = objects->Find(items_[i]);
                if (item == NULL)
                    continue;
                Vector3fix position = item->GetPosition();
                if (item->GetType() == 0)
                {
                    left = position.x / 4096.0f;
                    top = position.y / 4096.0f;
                    void* model = ((MenuObjectClass0*)item)->GetModel();
                    width = func_02047a5c(model, 0);
                    height = func_02047a3c(model, 0);
                }
                else if (item->GetType() == 8)
                {
                    MenuObjectClass8* text = (MenuObjectClass8*)item;
                    position = text->GetScreenPosition(script);
                    left = (int)(position.x / 4096.0f) + text->unk_30;
                    top = (int)(position.y / 4096.0f) + text->unk_32;
                    width = text->GetWidth();
                    height = text->GetHeight();
                }
                if (left >= touchX || touchX > left + width || top >= touchY || touchY > top + height)
                    continue;
                column = i % columns_;
                row = i / columns_;
                MenuObjectClass* selected = objects->Find(items_[row * columns_ + column]);
                if (selected != NULL && selected->GetType() == 8 && !selected->ContainsTouch())
                {
                    MenuObjectClass6* canvas = GetCanvas(script, selected);
                    if (canvas != NULL)
                        canvas->Select(script, selected->GetId());
                }
                else if (row == row_ && column == column_)
                    confirmed = 1;
                break;
            }
        }
    }
    if (row != row_ || column != column_)
    {
        row_ = row;
        column_ = column;
        moved_ = 1;
    }
    if (script->GetUnk1c8())
    {
        moved_ = 1;
        script->ClearUnk1c8();
    }
    if (moved_)
        MoveCursor(script);
    if (page != 0)
    {
        page_ += page;
        if (pages_ <= page_)
            page_ = 0;
        else if (page_ < 0)
            page_ = pages_ - 1;
        if (pageCallback_ != 0)
            script->RunCallback(pageCallback_);
    }
    else if (!up && !down && !left && !right)
    {
        if (confirmed)
        {
            if (fading)
                return;
            MenuObjectClass* item = objects->Find(items_[row_ * columns_ + column_]);
            int done = 0;
            if (item != NULL)
            {
                int entry = item->V40();
                if (entry > 0)
                {
                    script->StartEntry(entry);
                    done = 1;
                }
                int callback = item->V48();
                if (callback > 0)
                {
                    script->RunCallback(callback);
                    done = 1;
                }
            }
            if (aEntry_ != 0)
                script->StartEntry(aEntry_);
            if (aCallback_ != 0)
                script->RunCallback(aCallback_);
            if (done && sound_)
                func_0205eaa0(data_02108760, 1, 0);
        }
        if (func_02012444(data_02114e30, PAD_BUTTON_B))
        {
            if (fading)
                return;
            if (bEntry_ != 0)
                script->StartEntry(bEntry_);
            if (bCallback_ != 0)
                script->RunCallback(bCallback_);
        }
        if (func_02012444(data_02114e30, PAD_BUTTON_X))
        {
            if (xConfirms_ || fading)
                return;
            MenuObjectClass* item = objects->Find(items_[row_ * columns_ + column_]);
            int done = 0;
            if (item != NULL)
            {
                int callback = item->V80();
                if (callback > 0)
                {
                    script->RunCallback(callback);
                    done = 1;
                }
            }
            if (done && sound_)
                func_0205eaa0(data_02108760, 1, 0);
        }
    }
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript10StartEntryEi(); // MenuScript::StartEntry
    void _ZN10MenuScript11ClearUnk1c8Ev(); // MenuScript::ClearUnk1c8
    void _ZN10MenuScript11RunCallbackEj(); // MenuScript::RunCallback
    void _ZN10MenuScript9GetUnk1b0Ev(); // MenuScript::GetUnk1b0
    void _ZN10MenuScript9GetUnk1c8Ev(); // MenuScript::GetUnk1c8
    void _ZN14MenuObjectList4FindEi(); // MenuObjectList::Find
    void _ZN15MenuObjectClass5GetIdEv(); // MenuObjectClass::GetId
    void _ZN15MenuObjectClass7GetTypeEv(); // MenuObjectClass::GetType
    void _ZN16MenuObjectClass08GetModelEv(); // MenuObjectClass0::GetModel
    void _ZN16MenuObjectClass66SelectEP10MenuScriptt(); // MenuObjectClass6::Select
    void _ZN16MenuObjectClass710MoveCursorEP10MenuScript(); // MenuObjectClass7::MoveCursor
    void _ZN16MenuObjectClass715GetTouchedArrowEP10MenuScriptii(); // MenuObjectClass7::GetTouchedArrow
    void _ZN16MenuObjectClass78GetIndexEv(); // MenuObjectClass7::GetIndex
    void _ZN16MenuObjectClass79GetCanvasEP10MenuScriptP15MenuObjectClass(); // MenuObjectClass7::GetCanvas
    void _ZN16MenuObjectClass817GetScreenPositionEP10MenuScript(); // MenuObjectClass8::GetScreenPosition
    void _ZN16MenuObjectClass88GetWidthEv(); // MenuObjectClass8::GetWidth
    void _ZN16MenuObjectClass89GetHeightEv(); // MenuObjectClass8::GetHeight
    void _ZN9GameState11GetInstanceEv(); // GameState::GetInstance
    void _ZNK9GameState21GetEffectiveDeltaTimeEv(); // GameState::GetEffectiveDeltaTime
    void _s32_div_f();
}

asm void MenuObjectClass7::Update(MenuScript* script)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, lr}
    sub sp, sp, #0x70
    mov r9, r1
    mov r10, r0
    mov r0, r9
    bl _ZN10MenuScript9GetUnk1b0Ev
    ldrh r1, [r10, #0x6]
    cmp r1, r0
    bne @L021f98b8
    ldrb r0, [r10, #0xc]
    tst r0, #0x10
    bne @L021f98b8
    mov r0, r10
    bl _ZN16MenuObjectClass78GetIndexEv
    ldr r0, =0x400006c
    mov r7, #0x0
    bl func_020c39c8
    cmp r0, #0x0
    beq @L021f8e78
    ldr r0, =0x400106c
    bl func_020c39c8
    cmp r0, #0x0
    movne r7, #0x1
@L021f8e78:
    mov r0, r9
    bl _ZN10MenuScript10GetObjectsEv
    str r0, [sp, #0x2c]
    mov r2, #0x0
    add r0, sp, #0x66
    mov r1, #0xa
    ldrh r5, [r10, #0x28]
    ldrh r8, [r10, #0x2a]
    str r2, [sp, #0x28]
    bl __clear
    ldrh r0, [r10, #0x3e]
    cmp r7, #0x0
    strh r0, [sp, #0x68]
    ldrh r0, [r10, #0x3c]
    strh r0, [sp, #0x6a]
    ldrh r4, [r10, #0x4a]
    ldrh r3, [r10, #0x50]
    ldrh r2, [r10, #0x52]
    ldrh r1, [r10, #0x58]
    ldrh r0, [r10, #0x5a]
    strh r4, [sp, #0x5c]
    strh r3, [sp, #0x5e]
    strh r2, [sp, #0x60]
    strh r1, [sp, #0x62]
    strh r0, [sp, #0x64]
    bne @L021f8f5c
    mov r6, #0x0
    add r11, sp, #0x66
    ldr r4, =sKeys+2
    b @L021f8f54
@L021f8ef0:
    mov r1, r6, lsl #0x1
    ldrh r1, [r4, r1]
    ldr r0, =data_02114e30
    bl func_02012444
    cmp r0, #0x0
    beq @L021f8f50
    mov r0, r6, lsl #0x1
    ldrh r1, [r11, r0]
    mov r2, #0x0
    cmp r1, #0x0
    beq @L021f8f28
    mov r0, r9
    bl _ZN10MenuScript10StartEntryEi
    mov r2, #0x1
@L021f8f28:
    mov r1, r6, lsl #0x1
    add r0, sp, #0x5c
    ldrh r1, [r0, r1]
    cmp r1, #0x0
    beq @L021f8f48
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    mov r2, #0x1
@L021f8f48:
    cmp r2, #0x0
    bne @L021f98b8
@L021f8f50:
    add r6, r6, #0x1
@L021f8f54:
    cmp r6, #0x5
    blt @L021f8ef0
@L021f8f5c:
    ldrb r0, [r10, #0x62]
    mov r4, #0x0
    cmp r0, #0x0
    beq @L021f8f80
    ldr r0, =data_02114e30
    mov r1, #0x400
    bl func_02012444
    cmp r0, #0x0
    movne r4, #0x1
@L021f8f80:
    ldr r0, =data_02114e30
    mov r1, #0x1
    bl func_02012444
    cmp r0, #0x0
    cmpeq r4, #0x0
    movne r0, #0x1
    strne r0, [sp, #0x28]
    ldr r0, =data_02114e30
    mov r1, #0x40
    bl func_02012444
    str r0, [sp, #0x24]
    ldr r0, =data_02114e30
    mov r1, #0x80
    bl func_02012444
    str r0, [sp, #0x20]
    ldr r0, =data_02114e30
    mov r1, #0x20
    bl func_02012444
    str r0, [sp, #0x1c]
    ldr r0, =data_02114e30
    mov r1, #0x10
    bl func_02012444
    str r0, [sp, #0x18]
    ldr r0, [sp, #0x28]
    cmp r0, #0x0
    bne @L021f90d0
    bl _ZN9GameState11GetInstanceEv
    bl _ZNK9GameState21GetEffectiveDeltaTimeEv
    mov r4, r0
    ldr r0, =data_02114e30
    mov r1, #0x40
    bl func_02012430
    cmp r0, #0x0
    beq @L021f9028
    ldr r0, =sRepeatTime
    ldr r1, [r0, #0x0]
    cmp r1, r4
    movlo r0, #0x1
    subhs r1, r1, r4
    strlo r0, [sp, #0x24]
    strhs r1, [r0, #0x0]
    b @L021f90d0
@L021f9028:
    ldr r0, =data_02114e30
    mov r1, #0x80
    bl func_02012430
    cmp r0, #0x0
    beq @L021f905c
    ldr r0, =sRepeatTime
    ldr r1, [r0, #0x0]
    cmp r1, r4
    movlo r0, #0x1
    subhs r1, r1, r4
    strlo r0, [sp, #0x20]
    strhs r1, [r0, #0x0]
    b @L021f90d0
@L021f905c:
    ldr r0, =data_02114e30
    mov r1, #0x20
    bl func_02012430
    cmp r0, #0x0
    beq @L021f9090
    ldr r0, =sRepeatTime
    ldr r1, [r0, #0x0]
    cmp r1, r4
    movlo r0, #0x1
    subhs r1, r1, r4
    strlo r0, [sp, #0x1c]
    strhs r1, [r0, #0x0]
    b @L021f90d0
@L021f9090:
    ldr r0, =data_02114e30
    mov r1, #0x10
    bl func_02012430
    cmp r0, #0x0
    beq @L021f90c4
    ldr r0, =sRepeatTime
    ldr r1, [r0, #0x0]
    cmp r1, r4
    movlo r0, #0x1
    subhs r1, r1, r4
    strlo r0, [sp, #0x18]
    strhs r1, [r0, #0x0]
    b @L021f90d0
@L021f90c4:
    ldr r0, =sRepeatTime
    mov r1, #0x1f4
    str r1, [r0, #0x0]
@L021f90d0:
    ldr r0, [sp, #0x24]
    cmp r0, #0x0
    mov r0, #0x0
    str r0, [sp, #0x14]
    beq @L021f9100
    ldrh r1, [r10, #0x4c]
    sub r5, r5, #0x1
    cmp r1, #0x0
    beq @L021f9174
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    b @L021f98b8
@L021f9100:
    ldr r0, [sp, #0x20]
    cmp r0, #0x0
    beq @L021f9128
    ldrh r1, [r10, #0x4e]
    add r5, r5, #0x1
    cmp r1, #0x0
    beq @L021f9174
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    b @L021f98b8
@L021f9128:
    ldr r0, [sp, #0x1c]
    cmp r0, #0x0
    beq @L021f9150
    ldrh r1, [r10, #0x56]
    sub r8, r8, #0x1
    cmp r1, #0x0
    beq @L021f9174
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    b @L021f98b8
@L021f9150:
    ldr r0, [sp, #0x18]
    cmp r0, #0x0
    ldrneh r1, [r10, #0x54]
    addne r8, r8, #0x1
    cmpne r1, #0x0
    beq @L021f9174
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    b @L021f98b8
@L021f9174:
    ldrb r0, [r10, #0x60]
    mov r6, #0x0
    cmp r0, #0x0
    beq @L021f92ac
    mov r2, r6
    b @L021f91b0
@L021f918c:
    ldr r4, [r10, #0x20]
    ldrh r3, [r10, #0x2a]
    ldrh r1, [r10, #0x26]
    mla r1, r2, r1, r3
    mov r1, r1, lsl #0x1
    ldrh r1, [r4, r1]
    cmp r1, #0x0
    bne @L021f91bc
    add r2, r2, #0x1
@L021f91b0:
    ldrh r0, [r10, #0x24]
    cmp r2, r0
    blt @L021f918c
@L021f91bc:
    sub r3, r0, #0x1
    b @L021f91e8
@L021f91c4:
    ldr r4, [r10, #0x20]
    ldrh r1, [r10, #0x2a]
    ldrh r0, [r10, #0x26]
    mla r0, r3, r0, r1
    mov r0, r0, lsl #0x1
    ldrh r0, [r4, r0]
    cmp r0, #0x0
    bne @L021f91f0
    sub r3, r3, #0x1
@L021f91e8:
    cmp r3, #0x0
    bge @L021f91c4
@L021f91f0:
    mov r4, #0x0
    b @L021f9218
@L021f91f8:
    ldr r0, [r10, #0x20]
    ldrh r1, [r10, #0x28]
    mla r11, r1, r12, r4
    mov r1, r11, lsl #0x1
    ldrh r0, [r0, r1]
    cmp r0, #0x0
    bne @L021f9224
    add r4, r4, #0x1
@L021f9218:
    ldrh r12, [r10, #0x26]
    cmp r4, r12
    blt @L021f91f8
@L021f9224:
    sub r11, r12, #0x1
    b @L021f924c
@L021f922c:
    ldr lr, [r10, #0x20]
    ldrh r0, [r10, #0x28]
    mla r1, r0, r12, r11
    mov r0, r1, lsl #0x1
    ldrh r0, [lr, r0]
    cmp r0, #0x0
    bne @L021f9254
    sub r11, r11, #0x1
@L021f924c:
    cmp r11, #0x0
    bge @L021f922c
@L021f9254:
    cmp r5, r2
    movlt r5, r3
    blt @L021f92e8
    cmp r3, r5
    movlt r5, r2
    blt @L021f92e8
    cmp r8, r4
    bge @L021f928c
    ldrsh r0, [r10, #0x5e]
    mov r8, r4
    mvn r6, #0x0
    cmp r0, #0x1
    moveq r8, r11
    b @L021f92e8
@L021f928c:
    cmp r11, r8
    bge @L021f92e8
    ldrsh r0, [r10, #0x5e]
    mov r8, r11
    mov r6, #0x1
    cmp r0, #0x1
    moveq r8, r4
    b @L021f92e8
@L021f92ac:
    cmp r5, #0x0
    movlt r5, r6
    blt @L021f92e8
    ldrh r0, [r10, #0x24]
    cmp r0, r5
    suble r5, r0, #0x1
    ble @L021f92e8
    cmp r8, #0x0
    movlt r8, r6
    sublt r6, r6, #0x1
    blt @L021f92e8
    ldrh r0, [r10, #0x26]
    cmp r0, r8
    suble r8, r0, #0x1
    movle r6, #0x1
@L021f92e8:
    ldrh r1, [r10, #0x26]
    ldrsh r0, [r10, #0x5e]
    mla r1, r5, r1, r8
    cmp r0, #0x1
    mov r0, r1, lsl #0x1
    ldr r1, [r10, #0x20]
    moveq r6, #0x0
    ldrh r0, [r1, r0]
    cmp r0, #0x0
    ldreqh r5, [r10, #0x28]
    ldrh r0, [r10, #0x28]
    ldreqh r8, [r10, #0x2a]
    cmp r5, r0
    ldreqh r0, [r10, #0x2a]
    cmpeq r8, r0
    beq @L021f9370
    mov r1, #0x1
    mov r0, r10
    str r1, [sp, #0x14]
    bl _ZN16MenuObjectClass78GetIndexEv
    mov r1, r0, lsl #0x1
    ldr r2, [r10, #0x20]
    ldr r0, [sp, #0x2c]
    ldrh r1, [r2, r1]
    bl _ZN14MenuObjectList4FindEi
    mov r2, r0
    mov r0, r10
    mov r1, r9
    bl _ZN16MenuObjectClass79GetCanvasEP10MenuScriptP15MenuObjectClass
    cmp r0, #0x0
    beq @L021f9370
    mov r1, r9
    mov r2, #0x8000
    bl _ZN16MenuObjectClass66SelectEP10MenuScriptt
@L021f9370:
    ldr r0, [sp, #0x14]
    cmp r0, #0x0
    bne @L021f9638
    ldr r0, =data_02114e54
    ldrb r1, [r0, #0x55]
    cmp r1, #0x0
    beq @L021f9638
    add r1, sp, #0x34
    add r2, sp, #0x30
    bl func_02012a84
    ldr r2, [sp, #0x34]
    ldr r3, [sp, #0x30]
    mov r0, r10
    mov r1, r9
    bl _ZN16MenuObjectClass715GetTouchedArrowEP10MenuScriptii
    movs r6, r0
    bne @L021f9638
    ldrh r1, [r10, #0x26]
    ldrh r0, [r10, #0x24]
    mov r11, #0x0
    mul r0, r1, r0
    str r0, [sp, #0x0]
    b @L021f962c
@L021f93cc:
    mov r0, #0x0
    ldr r1, [r10, #0x20]
    str r0, [sp, #0x4]
    str r0, [sp, #0x8]
    str r0, [sp, #0xc]
    str r0, [sp, #0x10]
    mov r0, r11, lsl #0x1
    ldrh r1, [r1, r0]
    cmp r1, #0x0
    beq @L021f9628
    ldr r0, [sp, #0x2c]
    bl _ZN14MenuObjectList4FindEi
    movs r4, r0
    beq @L021f9628
    mov r1, r4
    ldr r2, [r1, #0x0]
    add r0, sp, #0x44
    ldr r2, [r2, #0x20]
    blx r2
    add r0, sp, #0x44
    add r3, sp, #0x50
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r0, r4
    bl _ZN15MenuObjectClass7GetTypeEv
    cmp r0, #0x0
    bne @L021f9494
    ldr r0, [sp, #0x50]
    bl _fflt
    ldr r1, =0x45800000
    bl _fdiv
    bl _ffix
    str r0, [sp, #0x10]
    ldr r0, [sp, #0x54]
    bl _fflt
    ldr r1, =0x45800000
    bl _fdiv
    bl _ffix
    str r0, [sp, #0xc]
    mov r0, r4
    bl _ZN16MenuObjectClass08GetModelEv
    mov r4, r0
    mov r1, #0x0
    bl func_02047a5c
    str r0, [sp, #0x8]
    mov r0, r4
    mov r1, #0x0
    bl func_02047a3c
    str r0, [sp, #0x4]
    b @L021f9520
@L021f9494:
    mov r0, r4
    bl _ZN15MenuObjectClass7GetTypeEv
    cmp r0, #0x8
    bne @L021f9520
    add r0, sp, #0x38
    mov r1, r4
    mov r2, r9
    bl _ZN16MenuObjectClass817GetScreenPositionEP10MenuScript
    ldr r1, [sp, #0x3c]
    ldr r0, [sp, #0x38]
    str r1, [sp, #0x54]
    ldr r1, [sp, #0x40]
    str r0, [sp, #0x50]
    str r1, [sp, #0x58]
    bl _fflt
    ldr r1, =0x45800000
    bl _fdiv
    bl _ffix
    ldrsh r1, [r4, #0x30]
    add r0, r0, r1
    str r0, [sp, #0x10]
    ldr r0, [sp, #0x54]
    bl _fflt
    ldr r1, =0x45800000
    bl _fdiv
    bl _ffix
    ldrsh r1, [r4, #0x32]
    add r0, r0, r1
    str r0, [sp, #0xc]
    mov r0, r4
    bl _ZN16MenuObjectClass88GetWidthEv
    str r0, [sp, #0x8]
    mov r0, r4
    bl _ZN16MenuObjectClass89GetHeightEv
    str r0, [sp, #0x4]
@L021f9520:
    ldr r2, [sp, #0x34]
    ldr r0, [sp, #0x10]
    cmp r0, r2
    bge @L021f9628
    mov r1, r0
    ldr r0, [sp, #0x8]
    add r0, r1, r0
    cmp r2, r0
    bgt @L021f9628
    ldr r2, [sp, #0x30]
    ldr r0, [sp, #0xc]
    cmp r0, r2
    bge @L021f9628
    mov r1, r0
    ldr r0, [sp, #0x4]
    add r0, r1, r0
    cmp r2, r0
    bgt @L021f9628
    ldrh r4, [r10, #0x26]
    mov r0, r11
    mov r1, r4
    bl _s32_div_f
    mov r8, r1
    mov r0, r11
    mov r1, r4
    bl _s32_div_f
    mov r5, r0
    mla r0, r5, r4, r8
    mov r1, r0, lsl #0x1
    ldr r2, [r10, #0x20]
    ldr r0, [sp, #0x2c]
    ldrh r1, [r2, r1]
    bl _ZN14MenuObjectList4FindEi
    movs r4, r0
    beq @L021f960c
    bl _ZN15MenuObjectClass7GetTypeEv
    cmp r0, #0x8
    bne @L021f960c
    mov r0, r4
    ldr r1, [r0, #0x0]
    ldr r1, [r1, #0xf8]
    blx r1
    cmp r0, #0x0
    bne @L021f960c
    mov r0, r10
    mov r1, r9
    mov r2, r4
    bl _ZN16MenuObjectClass79GetCanvasEP10MenuScriptP15MenuObjectClass
    movs r11, r0
    beq @L021f9638
    mov r0, r4
    bl _ZN15MenuObjectClass5GetIdEv
    mov r1, r0
    mov r0, r11
    mov r1, r1, lsl #0x10
    mov r2, r1, lsr #0x10
    mov r1, r9
    bl _ZN16MenuObjectClass66SelectEP10MenuScriptt
    b @L021f9638
@L021f960c:
    ldrh r0, [r10, #0x28]
    cmp r5, r0
    ldreqh r0, [r10, #0x2a]
    cmpeq r8, r0
    moveq r0, #0x1
    streq r0, [sp, #0x28]
    b @L021f9638
@L021f9628:
    add r11, r11, #0x1
@L021f962c:
    ldr r0, [sp, #0x0]
    cmp r11, r0
    blt @L021f93cc
@L021f9638:
    ldrh r0, [r10, #0x28]
    cmp r5, r0
    ldreqh r0, [r10, #0x2a]
    cmpeq r8, r0
    strneh r5, [r10, #0x28]
    strneh r8, [r10, #0x2a]
    movne r0, #0x1
    strne r0, [r10, #0x38]
    mov r0, r9
    bl _ZN10MenuScript9GetUnk1c8Ev
    cmp r0, #0x0
    beq @L021f9678
    mov r1, #0x1
    mov r0, r9
    str r1, [r10, #0x38]
    bl _ZN10MenuScript11ClearUnk1c8Ev
@L021f9678:
    ldr r0, [r10, #0x38]
    cmp r0, #0x0
    beq @L021f9690
    mov r0, r10
    mov r1, r9
    bl _ZN16MenuObjectClass710MoveCursorEP10MenuScript
@L021f9690:
    cmp r6, #0x0
    beq @L021f96e0
    ldrsh r0, [r10, #0x5c]
    add r0, r0, r6
    strh r0, [r10, #0x5c]
    ldrsh r1, [r10, #0x5c]
    ldrsh r0, [r10, #0x5e]
    cmp r0, r1
    movle r0, #0x0
    strleh r0, [r10, #0x5c]
    ble @L021f96c8
    cmp r1, #0x0
    sublt r0, r0, #0x1
    strlth r0, [r10, #0x5c]
@L021f96c8:
    ldrh r1, [r10, #0x48]
    cmp r1, #0x0
    beq @L021f98b8
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    b @L021f98b8
@L021f96e0:
    ldr r0, [sp, #0x24]
    cmp r0, #0x0
    ldreq r0, [sp, #0x20]
    cmpeq r0, #0x0
    ldreq r0, [sp, #0x1c]
    cmpeq r0, #0x0
    ldreq r0, [sp, #0x18]
    cmpeq r0, #0x0
    bne @L021f98b8
    ldr r0, [sp, #0x28]
    cmp r0, #0x0
    beq @L021f97dc
    cmp r7, #0x0
    bne @L021f98b8
    ldrh r4, [r10, #0x2a]
    ldrh r3, [r10, #0x28]
    ldrh r1, [r10, #0x26]
    ldr r2, [r10, #0x20]
    ldr r0, [sp, #0x2c]
    mla r1, r3, r1, r4
    mov r1, r1, lsl #0x1
    ldrh r1, [r2, r1]
    bl _ZN14MenuObjectList4FindEi
    movs r4, r0
    mov r5, #0x0
    beq @L021f9794
    ldr r1, [r0, #0x0]
    ldr r1, [r1, #0x40]
    blx r1
    mov r1, r0
    cmp r1, #0x0
    ble @L021f976c
    mov r0, r9
    bl _ZN10MenuScript10StartEntryEi
    mov r5, #0x1
@L021f976c:
    mov r0, r4
    ldr r1, [r0, #0x0]
    ldr r1, [r1, #0x48]
    blx r1
    mov r1, r0
    cmp r1, #0x0
    ble @L021f9794
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    mov r5, #0x1
@L021f9794:
    ldrh r1, [r10, #0x42]
    cmp r1, #0x0
    beq @L021f97a8
    mov r0, r9
    bl _ZN10MenuScript10StartEntryEi
@L021f97a8:
    ldrh r1, [r10, #0x40]
    cmp r1, #0x0
    beq @L021f97bc
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
@L021f97bc:
    cmp r5, #0x0
    ldrneb r0, [r10, #0x61]
    cmpne r0, #0x0
    beq @L021f97dc
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
@L021f97dc:
    ldr r0, =data_02114e30
    mov r1, #0x2
    bl func_02012444
    cmp r0, #0x0
    beq @L021f9820
    cmp r7, #0x0
    bne @L021f98b8
    ldrh r1, [r10, #0x44]
    cmp r1, #0x0
    beq @L021f980c
    mov r0, r9
    bl _ZN10MenuScript10StartEntryEi
@L021f980c:
    ldrh r1, [r10, #0x46]
    cmp r1, #0x0
    beq @L021f9820
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
@L021f9820:
    ldr r0, =data_02114e30
    mov r1, #0x400
    bl func_02012444
    cmp r0, #0x0
    beq @L021f98b8
    ldrb r0, [r10, #0x62]
    cmp r0, #0x0
    cmpeq r7, #0x0
    bne @L021f98b8
    ldrh r4, [r10, #0x2a]
    ldrh r3, [r10, #0x28]
    ldrh r1, [r10, #0x26]
    ldr r2, [r10, #0x20]
    ldr r0, [sp, #0x2c]
    mla r1, r3, r1, r4
    mov r1, r1, lsl #0x1
    ldrh r1, [r2, r1]
    bl _ZN14MenuObjectList4FindEi
    cmp r0, #0x0
    mov r4, #0x0
    beq @L021f9898
    ldr r1, [r0, #0x0]
    ldr r1, [r1, #0x80]
    blx r1
    mov r1, r0
    cmp r1, #0x0
    ble @L021f9898
    mov r0, r9
    bl _ZN10MenuScript11RunCallbackEj
    mov r4, #0x1
@L021f9898:
    cmp r4, #0x0
    ldrneb r0, [r10, #0x61]
    cmpne r0, #0x0
    beq @L021f98b8
    ldr r0, =data_02108760
    mov r1, #0x1
    mov r2, #0x0
    bl func_0205eaa0
@L021f98b8:
    add sp, sp, #0x70
    ldmia sp!, {r3, r4, r5, r6, r7, r8, r9, r10, r11, pc}
}
#endif

// NONMATCHING: the C matches 97.2 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original shifts the cell's index in the same instruction that moves it
#ifdef NONMATCHING
void MenuObjectClass7::MoveCursor(MenuScript* script)
{
    unsigned short cursorId = script->GetUnk1b2();
    MenuObjectList* objects = script->GetObjects();
    MenuObjectClass* cursor = objects->Find(cursorId);
    MenuObjectClass* item = objects->Find(items_[GetIndex()]);
    if (cursor != NULL && item != NULL)
    {
        if (item->GetType() == 0)
        {
            Vector3fix position = item->GetPosition();
            Vector3fix offset = item->Vcc();
            Vector3fix_Add(&position, &offset_, &position);
            Vector3fix_Add(&position, &offset, &position);
            cursor->SetPosition(&position);
        }
        else if (item->GetType() == 8)
        {
            Vector3fix position = ((MenuObjectClass8*)item)->GetScreenPosition(script);
            Vector3fix offset = item->Vcc();
            Vector3fix_Add(&position, &offset_, &position);
            Vector3fix_Add(&position, &offset, &position);
            cursor->SetPosition(&position);
        }
        else if (item->GetType() == 1)
        {
            Vector3fix position = item->GetPosition();
            Vector3fix offset = item->Vcc();
            Vector3fix_Add(&position, &offset_, &position);
            Vector3fix_Add(&position, &offset, &position);
            cursor->SetPosition(&position);
        }
        int callback = item->V50();
        if (callback > 0)
            script->RunCallback(callback);
    }
    moved_ = 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN10MenuScript10GetObjectsEv(); // MenuScript::GetObjects
    void _ZN10MenuScript11RunCallbackEj(); // MenuScript::RunCallback
    void _ZN14MenuObjectList4FindEi(); // MenuObjectList::Find
    void _ZN15MenuObjectClass7GetTypeEv(); // MenuObjectClass::GetType
    void _ZN16MenuObjectClass78GetIndexEv(); // MenuObjectClass7::GetIndex
    void _ZN16MenuObjectClass817GetScreenPositionEP10MenuScript(); // MenuObjectClass8::GetScreenPosition
    void _ZN17CharacterCreation6UpdateEv(); // CharacterCreation::Update
}

asm void MenuObjectClass7::MoveCursor(MenuScript* script)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    sub sp, sp, #0x90
    mov r6, r1
    mov r7, r0
    mov r0, r6
    bl _ZN17CharacterCreation6UpdateEv
    mov r4, r0
    mov r0, r6
    bl _ZN10MenuScript10GetObjectsEv
    mov r1, r4
    mov r5, r0
    bl _ZN14MenuObjectList4FindEi
    mov r4, r0
    mov r0, r7
    bl _ZN16MenuObjectClass78GetIndexEv
    mov r1, r0, lsl #0x1
    ldr r2, [r7, #0x20]
    mov r0, r5
    ldrh r1, [r2, r1]
    bl _ZN14MenuObjectList4FindEi
    mov r5, r0
    cmp r4, #0x0
    cmpne r5, #0x0
    beq @L021f9b08
    bl _ZN15MenuObjectClass7GetTypeEv
    cmp r0, #0x0
    bne @L021f99cc
    mov r1, r5
    ldr r2, [r1, #0x0]
    add r0, sp, #0x3c
    ldr r2, [r2, #0x20]
    blx r2
    add r0, sp, #0x3c
    add r3, sp, #0x84
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r1, r5
    ldr r2, [r1, #0x0]
    add r0, sp, #0x30
    ldr r2, [r2, #0xcc]
    blx r2
    add r0, sp, #0x30
    add r3, sp, #0x78
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x84
    add r1, r7, #0x2c
    mov r2, r0
    bl Vector3fix_Add
    add r0, sp, #0x84
    add r1, sp, #0x78
    mov r2, r0
    bl Vector3fix_Add
    mov r0, r4
    ldr r2, [r0, #0x0]
    add r1, sp, #0x84
    ldr r2, [r2, #0x1c]
    blx r2
    b @L021f9ae4
@L021f99cc:
    mov r0, r5
    bl _ZN15MenuObjectClass7GetTypeEv
    cmp r0, #0x8
    bne @L021f9a58
    add r0, sp, #0x24
    mov r1, r5
    mov r2, r6
    bl _ZN16MenuObjectClass817GetScreenPositionEP10MenuScript
    add r0, sp, #0x24
    add r3, sp, #0x6c
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r1, r5
    ldr r2, [r1, #0x0]
    add r0, sp, #0x18
    ldr r2, [r2, #0xcc]
    blx r2
    add r0, sp, #0x18
    add r3, sp, #0x60
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x6c
    add r1, r7, #0x2c
    mov r2, r0
    bl Vector3fix_Add
    add r0, sp, #0x6c
    add r1, sp, #0x60
    mov r2, r0
    bl Vector3fix_Add
    mov r0, r4
    ldr r2, [r0, #0x0]
    add r1, sp, #0x6c
    ldr r2, [r2, #0x1c]
    blx r2
    b @L021f9ae4
@L021f9a58:
    mov r0, r5
    bl _ZN15MenuObjectClass7GetTypeEv
    cmp r0, #0x1
    bne @L021f9ae4
    mov r1, r5
    ldr r2, [r1, #0x0]
    add r0, sp, #0xc
    ldr r2, [r2, #0x20]
    blx r2
    add r0, sp, #0xc
    add r3, sp, #0x54
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    mov r1, r5
    ldr r2, [r1, #0x0]
    add r0, sp, #0x0
    ldr r2, [r2, #0xcc]
    blx r2
    add r0, sp, #0x0
    add r3, sp, #0x48
    ldmia r0, {r0, r1, r2}
    stmia r3, {r0, r1, r2}
    add r0, sp, #0x54
    add r1, r7, #0x2c
    mov r2, r0
    bl Vector3fix_Add
    add r0, sp, #0x54
    add r1, sp, #0x48
    mov r2, r0
    bl Vector3fix_Add
    mov r0, r4
    ldr r2, [r0, #0x0]
    add r1, sp, #0x54
    ldr r2, [r2, #0x1c]
    blx r2
@L021f9ae4:
    mov r0, r5
    ldr r1, [r0, #0x0]
    ldr r1, [r1, #0x50]
    blx r1
    mov r1, r0
    cmp r1, #0x0
    ble @L021f9b08
    mov r0, r6
    bl _ZN10MenuScript11RunCallbackEj
@L021f9b08:
    mov r0, #0x0
    str r0, [r7, #0x38]
    add sp, sp, #0x90
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif

void MenuObjectClass::SetPosition(Vector3fix* position)
{
}

void MenuObjectClass7::Finish(MenuObjectList* list)
{
    rows_ = 0;
    columns_ = 0;
    items_ = NULL;
}

int MenuObjectClass7::SetItem(unsigned short id, unsigned short row, unsigned short column)
{
    if (items_ == NULL)
        return 0;
    if (rows_ <= row || columns_ <= column)
        return 0;
    items_[row * columns_ + column] = id;
    return 1;
}

unsigned short MenuObjectClass7::GetItem(unsigned short row, unsigned short column)
{
    if (items_ == NULL)
        return 0;
    if (rows_ <= row || columns_ <= column)
        return 0;
    return items_[row * columns_ + column];
}

unsigned short MenuObjectClass7::GetRows()
{
    return rows_;
}

void MenuObjectClass7::SetRow(unsigned short row)
{
    row_ = row;
}

unsigned short MenuObjectClass7::GetRow()
{
    return row_;
}

void MenuObjectClass7::SetColumn(unsigned short column)
{
    column_ = column;
}

unsigned short MenuObjectClass7::GetColumn()
{
    return column_;
}

int MenuObjectClass7::GetIndex()
{
    return row_ * columns_ + column_;
}

void MenuObjectClass7::SetIndex(unsigned short index)
{
    row_ = index / columns_;
    column_ = index % columns_;
}

void MenuObjectClass7::ClearItems()
{
    memset(items_, 0, rows_ * 2 * columns_);
}

void MenuObjectClass7::V24(int value)
{
    xConfirms_ = value;
}

void MenuObjectClass7::V2c(int value)
{
    xEntry_ = value;
}

void MenuObjectClass7::V34(int value)
{
    yEntry_ = value;
}

void MenuObjectClass7::V44(short value)
{
    aCallback_ = value;
}

void MenuObjectClass7::V3c(short value)
{
    aEntry_ = value;
}

void MenuObjectClass7::SetBEntry(unsigned short entry)
{
    bEntry_ = entry;
}

void MenuObjectClass7::SetBCallback(unsigned short callback)
{
    bCallback_ = callback;
}

void MenuObjectClass7::V54(int value)
{
    pageCallback_ = value;
}

void MenuObjectClass7::V5c(int value)
{
    selectCallback_ = value;
}

void MenuObjectClass7::V64(int value)
{
    upCallback_ = value;
}

void MenuObjectClass7::V6c(int value)
{
    downCallback_ = value;
}

void MenuObjectClass7::V74(int value)
{
    yCallback_ = value;
}

void MenuObjectClass7::V7c(int value)
{
    xCallback_ = value;
}

void MenuObjectClass7::V84(int value)
{
    rightCallback_ = value;
}

void MenuObjectClass7::V8c(int value)
{
    leftCallback_ = value;
}

void MenuObjectClass7::V94(int value)
{
    lCallback_ = value;
}

void MenuObjectClass7::V9c(int value)
{
    rCallback_ = value;
}

MenuObjectClass6* MenuObjectClass7::GetCanvas(MenuScript* script, MenuObjectClass* object)
{
    if (object == NULL)
        return NULL;
    if (object->GetType() != 8)
        return NULL;
    unsigned short id = ((MenuObjectClass8*)object)->canvas_;
    MenuObjectList* objects = script->GetObjects();
    MenuObjectClass* canvas = objects->Find(id);
    if (canvas == NULL)
        return NULL;
    if (canvas->GetType() != 6)
        canvas = NULL;
    return (MenuObjectClass6*)canvas;
}

// NONMATCHING: the C matches 68.6 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The original computes the last column after the index and loads the cell again after the loop
#ifdef NONMATCHING
void MenuObjectClass7::MoveToItem(MenuScript* script)
{
    int column = column_;
    int row = row_;
    int columns = columns_;
    int index = row * columns + column;
    int last = columns - 1;
    while (items_[index] == 0)
    {
        if (column == 0)
        {
            if (row == 0)
                break;
            column = last;
            row--;
        }
        else if (column > 0)
            column--;
        index = row * columns + column;
    }
    if (items_[index] == 0)
        index = 0;
    SetIndex(index);
    MoveCursor(script);
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN16MenuObjectClass710MoveCursorEP10MenuScript(); // MenuObjectClass7::MoveCursor
    void _ZN16MenuObjectClass78SetIndexEt(); // MenuObjectClass7::SetIndex
}

asm void MenuObjectClass7::MoveToItem(MenuScript* script)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r5, r0
    ldrh r2, [r5, #0x2a]
    ldrh r3, [r5, #0x28]
    ldrh r12, [r5, #0x26]
    mov r4, r1
    mla lr, r3, r12, r2
    sub r1, r12, #0x1
    b @L021f9d5c
@L021f9d38:
    cmp r2, #0x0
    bne @L021f9d54
    cmp r3, #0x0
    beq @L021f9d70
    mov r2, r1
    sub r3, r3, #0x1
    b @L021f9d58
@L021f9d54:
    subgt r2, r2, #0x1
@L021f9d58:
    mla lr, r3, r12, r2
@L021f9d5c:
    ldr r6, [r5, #0x20]
    mov r0, lr, lsl #0x1
    ldrh r0, [r6, r0]
    cmp r0, #0x0
    beq @L021f9d38
@L021f9d70:
    mov r0, lr, lsl #0x1
    ldrh r0, [r6, r0]
    cmp r0, #0x0
    moveq lr, #0x0
    mov r1, lr, lsl #0x10
    mov r0, r5
    mov r1, r1, lsr #0x10
    bl _ZN16MenuObjectClass78SetIndexEt
    mov r0, r5
    mov r1, r4
    bl _ZN16MenuObjectClass710MoveCursorEP10MenuScript
    ldmia sp!, {r4, r5, r6, pc}
}
#endif

void MenuObjectClass7::SetWrap(bool wrap)
{
    wrap_ = wrap;
}

// NONMATCHING: the C matches 79.1 %, so the build uses the original's instructions after #else (see Decompiling.md).
// The canvas and its left and right edges get other registers
#ifdef NONMATCHING
int MenuObjectClass7::GetTouchedArrow(MenuScript* script, int x, int y)
{
    MenuObjectList* objects = script->GetObjects();
    unsigned short count = rows_ * columns_;
    for (unsigned short i = 0; i < count; i++)
    {
        MenuObjectClass6* object = GetCanvas(script, objects->Find(items_[i]));
        if (object == NULL)
            continue;
        Canvas* canvas = &object->canvas_;
        if (canvas == NULL)
            continue;
        short left = (short)(canvas->x_ * 8);
        short right = left + (short)(canvas->width_ * 8);
        short bottom = (short)(canvas->y_ * 8) + (short)(canvas->height_ * 8);
        int arrow = 0;
        if (bottom - 16 > y)
            return arrow;
        if (y >= bottom)
            return arrow;
        if (left <= x && x < left + 16)
            arrow = -1;
        if (right - 16 > x)
            return arrow;
        if (x < right)
            arrow = 1;
        return arrow;
    }
    return 0;
}
#else
extern "C"
{
    // The assembler doesn't take qualified names, so these are the member functions' symbols
    void _ZN16MenuObjectClass79GetCanvasEP10MenuScriptP15MenuObjectClass(); // MenuObjectClass7::GetCanvas
}

asm int MenuObjectClass7::GetTouchedArrow(MenuScript* script, int x, int y)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
    mov r9, r1
    mov r10, r0
    mov r0, r9
    mov r8, r2
    mov r7, r3
    bl _ZN10MenuScript10GetObjectsEv
    ldrh r2, [r10, #0x24]
    ldrh r1, [r10, #0x26]
    mov r5, r0
    mov r6, #0x0
    mul r0, r2, r1
    mov r4, r0, lsl #0x10
    b @L021f9ea4
@L021f9de0:
    ldr r1, [r10, #0x20]
    mov r0, r6, lsl #0x1
    ldrh r1, [r1, r0]
    mov r0, r5
    bl _ZN14MenuObjectList4FindEi
    mov r2, r0
    mov r0, r10
    mov r1, r9
    bl _ZN16MenuObjectClass79GetCanvasEP10MenuScriptP15MenuObjectClass
    cmp r0, #0x0
    beq @L021f9e98
    adds r12, r0, #0x20
    beq @L021f9e98
    ldrsh r0, [r12, #0xaa]
    ldrsh r1, [r12, #0xae]
    ldrsh r3, [r12, #0xac]
    mov r2, r0, lsl #0x13
    ldrsh r4, [r12, #0xa8]
    mov r0, r3, lsl #0x13
    mov r3, r0, asr #0x10
    mov r0, r4, lsl #0x13
    add r0, r3, r0, asr #0x10
    mov r0, r0, lsl #0x10
    mov r4, r0, asr #0x10
    mov r1, r1, lsl #0x13
    mov r2, r2, asr #0x10
    add r1, r2, r1, asr #0x10
    mov r1, r1, lsl #0x10
    mov r2, r1, asr #0x10
    sub r1, r2, #0x10
    cmp r1, r7
    mov r0, #0x0
    ldmgtia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    cmp r7, r2
    ldmgeia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    cmp r3, r8
    bgt @L021f9e80
    add r1, r3, #0x10
    cmp r8, r1
    sublt r0, r0, #0x1
@L021f9e80:
    sub r1, r4, #0x10
    cmp r1, r8
    ldmgtia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
    cmp r8, r4
    movlt r0, #0x1
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
@L021f9e98:
    add r0, r6, #0x1
    mov r0, r0, lsl #0x10
    mov r6, r0, lsr #0x10
@L021f9ea4:
    cmp r6, r4, lsr #0x10
    blo @L021f9de0
    mov r0, #0x0
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
}
#endif
