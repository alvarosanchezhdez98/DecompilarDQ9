#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_mtx22.c: 2x2 matrices. Its other functions aren't in the ROM.

// The NitroSDK's mul64: a 64-bit value times a fixed-point number
static inline long MultiplyFx64(int64_t x, long y)
{
    return (long)((x * y) >> 12);
}

extern "C"
{
#ifdef __MWERKS__
#pragma thumb on
    // usa: func_020c111c
    // MTX_Rot22_
    asm void func_020c111c(Matrix2x2* out, fix32_t sine, fix32_t cosine)
    {
        str r2, [r0, #0]
        str r1, [r0, #4]
        neg r1, r1
        str r1, [r0, #8]
        str r2, [r0, #12]
        bx lr
    }
#pragma thumb off
#endif

    // usa: func_020c1128
    // MTX_ScaleApply22
    void func_020c1128(const Matrix2x2* in, Matrix2x2* out, fix32_t x, fix32_t y)
    {
        int64_t v;

        v = x;
        out->entries[0] = MultiplyFx64(v, in->entries[0]);
        out->entries[1] = MultiplyFx64(v, in->entries[1]);

        v = y;
        out->entries[2] = MultiplyFx64(v, in->entries[2]);
        out->entries[3] = MultiplyFx64(v, in->entries[3]);
    }
}
