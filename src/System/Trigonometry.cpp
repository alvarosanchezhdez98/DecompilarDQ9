#include "std_library_functions.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_trig.c: sines and cosines as fx64c, with 32 fractional bits. Its other functions aren't in the
// ROM.

// 1 in fx64c
#define FX64C_ONE (1LL << 32)
// sin(pi / 4) and cos(pi / 4)
#define FX64C_SQRT1_2 0xb504f334
// 4 / pi, with 32 fractional bits
#define FX64C_4_PI 0x145f306ddLL

extern "C"
{
    // usa: func_020c30ac
    // FX_SinFx64c_internal: sin(x * pi / 4), for x from 0 to 1, with a polynomial
    uint64_t func_020c30ac(uint64_t x)
    {
        uint64_t xx;
        uint64_t t;

        if (x == FX64C_ONE)
        {
            return FX64C_SQRT1_2;
        }

        xx = (x * x) >> 32;
        t = FX64C_ONE - ((xx * 0x02317888) >> 32);
        t = FX64C_ONE - ((t * ((xx * 0x03c2857c) >> 32)) >> 32);
        t = FX64C_ONE - ((t * ((xx * 0x07e54b84) >> 32)) >> 32);
        t = 0xc90fdaa2 - ((t * ((xx * 0x14abbce6) >> 32)) >> 32);
        return (t * x) >> 32;
    }

    // usa: func_020c3194
    // FX_CosFx64c_internal: cos(x * pi / 4), for x from 0 to 1, with a polynomial
    uint64_t func_020c3194(uint64_t x)
    {
        uint64_t xx;
        uint64_t t;

        if (x == FX64C_ONE)
        {
            return FX64C_SQRT1_2;
        }

        xx = (x * x) >> 32;
        t = FX64C_ONE - ((xx * 0x02d1e41d) >> 32);
        t = FX64C_ONE - ((t * ((xx * 0x054387ad) >> 32)) >> 32);
        t = FX64C_ONE - ((t * ((xx * 0x0d28d331) >> 32)) >> 32);
        return FX64C_ONE - ((t * ((xx * 0x4ef4f327) >> 32)) >> 32);
    }

    // usa: func_020c3260
    // FX_SinFx64c: the sine of an angle in radians (fx32)
    int64_t func_020c3260(long rad)
    {
        if (rad < 0)
        {
            return -func_020c3260(-rad);
        }
        else
        {
            // The angle in eighths of a turn, and where it is in its eighth
            int64_t t = rad * FX64C_4_PI;
            long octant = (long)(t >> 44);
            uint64_t x = (t >> 12) & 0xffffffff;

            if (octant & 1)
            {
                x = FX64C_ONE - x;
            }

            if ((octant + 1) & 2)
            {
                x = func_020c3194(x);
            }
            else
            {
                x = func_020c30ac(x);
            }

            if ((octant & 7) > 3)
            {
                x = -x;
            }
            return x;
        }
    }

    // usa: func_020c32f8
    // FX_CosFx64c: the cosine of an angle in radians (fx32)
    int64_t func_020c32f8(long rad)
    {
        if (rad < 0)
        {
            return func_020c32f8(-rad);
        }
        else
        {
            // The angle in eighths of a turn, and where it is in its eighth
            int64_t t = rad * FX64C_4_PI;
            long octant = (long)(t >> 44);
            uint64_t x = (t >> 12) & 0xffffffff;

            if (octant & 1)
            {
                x = FX64C_ONE - x;
            }

            if ((octant + 1) & 2)
            {
                x = func_020c30ac(x);
            }
            else
            {
                x = func_020c3194(x);
            }

            if (((octant + 2) & 7) > 3)
            {
                x = -x;
            }
            return x;
        }
    }
}
