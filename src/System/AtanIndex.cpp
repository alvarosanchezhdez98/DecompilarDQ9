#include "System/Matrix.h"

#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's fx_atanidx.c: arctangents as angle indices, where 0x10000 is a full turn. FX_AtanIdx isn't in the
// ROM.

// The NitroSDK's FX_AtanIdxTable_: atan(i / 128) as an angle index, for i from 0 to 128 (signed, like in the NitroSDK)
extern const short atanIndexTable[128 + 1] = {
    0x0000, 0x0051, 0x00a3, 0x00f4, 0x0146, 0x0197, 0x01e9, 0x023a,
    0x028b, 0x02dc, 0x032d, 0x037e, 0x03cf, 0x0420, 0x0470, 0x04c1,
    0x0511, 0x0561, 0x05b1, 0x0601, 0x0651, 0x06a0, 0x06ef, 0x073e,
    0x078d, 0x07dc, 0x082a, 0x0878, 0x08c6, 0x0914, 0x0961, 0x09ae,
    0x09fb, 0x0a48, 0x0a94, 0x0ae0, 0x0b2c, 0x0b77, 0x0bc2, 0x0c0d,
    0x0c57, 0x0ca1, 0x0ceb, 0x0d34, 0x0d7d, 0x0dc6, 0x0e0f, 0x0e56,
    0x0e9e, 0x0ee5, 0x0f2c, 0x0f73, 0x0fb9, 0x0fff, 0x1044, 0x1089,
    0x10ce, 0x1112, 0x1156, 0x1199, 0x11dc, 0x121f, 0x1261, 0x12a3,
    0x12e4, 0x1325, 0x1366, 0x13a6, 0x13e6, 0x1425, 0x1464, 0x14a2,
    0x14e0, 0x151e, 0x155b, 0x1598, 0x15d5, 0x1611, 0x164c, 0x1688,
    0x16c2, 0x16fd, 0x1737, 0x1770, 0x17aa, 0x17e2, 0x181b, 0x1853,
    0x188a, 0x18c1, 0x18f8, 0x192e, 0x1964, 0x199a, 0x19cf, 0x1a04,
    0x1a38, 0x1a6c, 0x1a9f, 0x1ad3, 0x1b05, 0x1b38, 0x1b6a, 0x1b9c,
    0x1bcd, 0x1bfe, 0x1c2e, 0x1c5e, 0x1c8e, 0x1cbe, 0x1ced, 0x1d1b,
    0x1d4a, 0x1d78, 0x1da5, 0x1dd3, 0x1dff, 0x1e2c, 0x1e58, 0x1e84,
    0x1eb0, 0x1edb, 0x1f06, 0x1f30, 0x1f5a, 0x1f84, 0x1fae, 0x1fd7,
    0x2000,
};

extern "C"
{
    // usa: func_020c3544
    // FX_Atan2Idx
    unsigned short fix32_Atan2_Rescaled(fix32_t y, fix32_t x)
    {
        long a, b;
        int c;
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
                    c = 16384;
                    sign = 0;
                }
                else
                {
                    return (unsigned short)8192;
                }
            }
            else if (x < 0)
            {
                x = -x;
                if (x < y)
                {
                    a = x;
                    b = y;
                    c = 16384;
                    sign = 1;
                }
                else if (x > y)
                {
                    a = y;
                    b = x;
                    c = 32768;
                    sign = 0;
                }
                else
                {
                    return (unsigned short)24576;
                }
            }
            else
            {
                return (unsigned short)16384;
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
                    c = -32768;
                    sign = 1;
                }
                else if (x < y)
                {
                    a = x;
                    b = y;
                    c = -16384;
                    sign = 0;
                }
                else
                {
                    return (unsigned short)-24576;
                }
            }
            else if (x > 0)
            {
                if (x < y)
                {
                    a = x;
                    b = y;
                    c = -16384;
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
                    return (unsigned short)-8192;
                }
            }
            else
            {
                return (unsigned short)-16384;
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
                return (unsigned short)32768;
            }
        }

        if (b == 0)
        {
            return 0;
        }

        if (sign)
        {
            return (unsigned short)(c + atanIndexTable[fix32_Divide(a, b) >> 5]);
        }
        else
        {
            return (unsigned short)(c - atanIndexTable[fix32_Divide(a, b) >> 5]);
        }
    }
}
