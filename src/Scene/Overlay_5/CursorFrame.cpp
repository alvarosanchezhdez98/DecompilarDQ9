#include "Scene/Overlay_5/CursorFrame.h"
#include "Graphics/Vector.h"
#include "System/Graphics.h"

extern "C"
{
    void func_02047554(void* model, int, int);
    void func_02075db0(void* sprite, int x, int y);
}

static inline void Translate(int x, int y, int z)
{
    GXFIFO_MATRIX_TRANSLATE = x;
    GXFIFO_MATRIX_TRANSLATE = y;
    GXFIFO_MATRIX_TRANSLATE = z;
}

void CursorFrame::Initialize()
{
    corners_ = 0;
    size_ = 0x8000;
    right_ = 0;
    left_ = 0;
    bottom_ = 0;
    top_ = 0;
    target_[1] = 0;
    target_[0] = 0;
    target_[3] = 0;
    target_[2] = 0;
    current_[1] = 0;
    current_[0] = 0;
    current_[3] = 0;
    current_[2] = 0;
    z_ = 0;
}

void CursorFrame::Update(int speed)
{
    if (speed == 0)
        speed = 1;
    int rate = speed * 0xb33;
    int threshold = speed * 0xccc;
    Approach(&target_[0], &current_[0], rate, threshold);
    Approach(&target_[1], &current_[1], rate, threshold);
    Approach(&target_[2], &current_[2], rate, threshold);
    Approach(&target_[3], &current_[3], rate, threshold);
}

void CursorFrame::Draw(int kind, short alpha)
{
    if (corners_ == 0)
        return;
    int left = current_[0] & ~0xfff;
    int top = current_[1] & ~0xfff;
    int right = (current_[0] + current_[2] - size_) & ~0xfff;
    int bottom = (current_[1] + current_[3] - size_) & ~0xfff;
    int positions[4][2] = {{left, top}, {right, top}, {left, bottom}, {right, bottom}};
    for (int i = 0; i < 4; i++)
    {
        int x = positions[i][0];
        int y = positions[i][1];
        switch (kind)
        {
        case 0:
            GXFIFO_MATRIX_PUSH = 0;
            Translate(x, y, z_);
            *(short*)(corners_ + i * 0x88 + 0x80) = alpha;
            func_02047554(corners_ + i * 0x88, 0, 1);
            GXFIFO_MATRIX_POP = 1;
            break;
        case 1:
            func_02075db0(corners_ + i * 0x70, x >> 12, y >> 12);
            break;
        case 2:
        {
            char* corner = corners_ + i * 0x28;
            *(int*)(corner + 0x14) = x;
            *(int*)(corner + 0x18) = y;
            break;
        }
        }
    }
}

// NONMATCHING: the C matches 72.7 %, so the build uses the original's instructions after #else (see Decompiling.md).
// Registers of the 64-bit rounding: the original adds 0x800 into other registers than the product's
#ifdef NONMATCHING
void CursorFrame::Approach(int* target, int* current, int rate, int threshold)
{
    int distance = *target - *current;
    int value;
    if (fix32abs(distance) < threshold)
        value = *target;
    else
        value = *current + (int)(((long long)distance * rate + 0x800) >> 12);
    *current = value;
}
#else
asm void CursorFrame::Approach(int* target, int* current, int rate, int threshold)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r7, r1
    mov r4, r2
    ldr r1, [r7, #0x0]
    ldr r0, [r4, #0x0]
    mov r6, r3
    sub r5, r1, r0
    mov r0, r5
    bl fix32abs
    ldr r1, [sp, #0x18]
    cmp r0, r1
    ldrlt r0, [r7, #0x0]
    blt @L0215394c
    smull r1, r0, r5, r6
    adds r2, r1, #0x800
    adc r1, r0, #0x0
    mov r2, r2, lsr #0xc
    ldr r0, [r4, #0x0]
    orr r2, r2, r1, lsl #0x14
    add r0, r0, r2
@L0215394c:
    str r0, [r4, #0x0]
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
#endif
