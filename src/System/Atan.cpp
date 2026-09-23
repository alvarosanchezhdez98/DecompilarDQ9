#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_atan.c: arctangents in radians. FX_Atan isn't in the ROM.

// The NitroSDK's FX_AtanTable_: atan(i / 128) in radians, as fx16, for i from 0 to 128
extern const short atanTable[128 + 1] = {
    0x0000, 0x0020, 0x0040, 0x0060, 0x0080, 0x00a0, 0x00c0, 0x00e0,
    0x0100, 0x0120, 0x013f, 0x015f, 0x017f, 0x019f, 0x01be, 0x01de,
    0x01fd, 0x021d, 0x023c, 0x025c, 0x027b, 0x029a, 0x02b9, 0x02d8,
    0x02f7, 0x0316, 0x0335, 0x0354, 0x0372, 0x0391, 0x03af, 0x03cd,
    0x03eb, 0x0409, 0x0427, 0x0445, 0x0463, 0x0481, 0x049e, 0x04bb,
    0x04d9, 0x04f6, 0x0513, 0x052f, 0x054c, 0x0569, 0x0585, 0x05a1,
    0x05be, 0x05da, 0x05f5, 0x0611, 0x062d, 0x0648, 0x0663, 0x067e,
    0x0699, 0x06b4, 0x06cf, 0x06e9, 0x0703, 0x071e, 0x0738, 0x0751,
    0x076b, 0x0785, 0x079e, 0x07b7, 0x07d0, 0x07e9, 0x0802, 0x081a,
    0x0833, 0x084b, 0x0863, 0x087b, 0x0893, 0x08aa, 0x08c2, 0x08d9,
    0x08f0, 0x0907, 0x091e, 0x0934, 0x094b, 0x0961, 0x0977, 0x098d,
    0x09a3, 0x09b9, 0x09ce, 0x09e3, 0x09f9, 0x0a0e, 0x0a23, 0x0a37,
    0x0a4c, 0x0a60, 0x0a74, 0x0a89, 0x0a9c, 0x0ab0, 0x0ac4, 0x0ad7,
    0x0aeb, 0x0afe, 0x0b11, 0x0b24, 0x0b37, 0x0b49, 0x0b5c, 0x0b6e,
    0x0b80, 0x0b92, 0x0ba4, 0x0bb6, 0x0bc8, 0x0bd9, 0x0beb, 0x0bfc,
    0x0c0d, 0x0c1e, 0x0c2f, 0x0c3f, 0x0c50, 0x0c60, 0x0c71, 0x0c81,
    0x0c91,
};

extern "C"
{
    // usa: func_020c338c
    // FX_Atan2
    fix32_t fix32_Atan2(fix32_t y, fix32_t x)
    {
        long a, b, c;
        int sign;

        if (y > 0)
        {
            if (x > 0)
            {
                if (x > y)
                {
                    a = y;
                    b = x;
                    c = 0;
                    sign = 1;
                }
                else if (x < y)
                {
                    a = x;
                    b = y;
                    c = 6434;
                    sign = 0;
                }
                else
                {
                    return (short)3217;
                }
            }
            else if (x < 0)
            {
                x = -x;
                if (x < y)
                {
                    a = x;
                    b = y;
                    c = 6434;
                    sign = 1;
                }
                else if (x > y)
                {
                    a = y;
                    b = x;
                    c = 12868;
                    sign = 0;
                }
                else
                {
                    return (short)9651;
                }
            }
            else
            {
                return (short)6434;
            }
        }
        else if (y < 0)
        {
            y = -y;
            if (x < 0)
            {
                x = -x;
                if (x > y)
                {
                    a = y;
                    b = x;
                    c = -12868;
                    sign = 1;
                }
                else if (x < y)
                {
                    a = x;
                    b = y;
                    c = -6434;
                    sign = 0;
                }
                else
                {
                    return (short)-9651;
                }
            }
            else if (x > 0)
            {
                if (x < y)
                {
                    a = x;
                    b = y;
                    c = -6434;
                    sign = 1;
                }
                else if (x > y)
                {
                    a = y;
                    b = x;
                    c = 0;
                    sign = 0;
                }
                else
                {
                    return (short)-3217;
                }
            }
            else
            {
                return (short)-6434;
            }
        }
        else
        {
            if (x >= 0)
            {
                return 0;
            }
            else
            {
                return (short)12868;
            }
        }

        if (b == 0)
        {
            return 0;
        }

        if (sign)
        {
            return (short)(c + atanTable[fix32_Divide(a, b) >> 5]);
        }
        else
        {
            return (short)(c - atanTable[fix32_Divide(a, b) >> 5]);
        }
    }
}
