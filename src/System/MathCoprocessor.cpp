#include "System/MathCoprocessor.h"
#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_cp.c: fixed-point division and square roots with the hardware divider and square root unit. Its
// other functions aren't in the ROM.

extern "C"
{
    // usa: func_020c2bf4
    // FX_Div
    fix32_t fix32_Divide(fix32_t num, fix32_t denom)
    {
        fix32_QueueComputeQuotient(num, denom);
        return fix32_GetDivisionResult();
    }

    // usa: func_020c2c04
    // FX_Sqrt
    fix32_t fix32_Sqrt(fix32_t x)
    {
        if (x > 0)
        {
            StartSquareRoot64((uint64_t)x << 32);
            return fix32_GetSqrtResult();
        }
        else
        {
            return 0;
        }
    }

    // usa: func_020c2c38
    // FX_GetDivResultFx64c
    int64_t GetHardwareDividerResult()
    {
        return GetDivisionResult64();
    }

    // usa: func_020c2c5c
    // FX_GetDivResult
    fix32_t fix32_GetDivisionResult()
    {
        return (long)((GetDivisionResult64() + (1 << 19)) >> 20);
    }

    // usa: func_020c2c94
    // FX_InvAsync
    void fix32_QueueComputeReciprocal(fix32_t x)
    {
        StartDivision64_32((uint64_t)0x1000 << 32, (unsigned long)x);
    }

    // usa: func_020c2cc4
    // FX_GetSqrtResult
    fix32_t fix32_GetSqrtResult()
    {
        return (long)((GetSquareRootResult32() + (1 << 9)) >> 10);
    }

    // usa: func_020c2cf0
    // FX_DivAsync
    void fix32_QueueComputeQuotient(fix32_t num, fix32_t denom)
    {
        StartDivision64_32((uint64_t)num << 32, (unsigned long)denom);
    }

    // usa: func_020c2d18
    // FX_DivS32
    int32_t FastIntDivide(int32_t a, int32_t b)
    {
        StartDivision32_32((unsigned long)a, (unsigned long)b);
        return GetDivisionResult32();
    }

    // usa: func_020c2d54
    // FX_ModS32
    int32_t FastIntModulus(int32_t a, int32_t b)
    {
        StartDivision32_32((unsigned long)a, (unsigned long)b);
        return GetDivisionRemainder32();
    }
}
