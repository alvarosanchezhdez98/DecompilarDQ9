#pragma optimize_for_size off
#pragma optimization_level 4

// The NitroSDK's math.c

extern "C"
{
    // usa: func_020d1ae4
    // MATH_CountPopulation: the number of bits set
    unsigned char func_020d1ae4(unsigned long x)
    {
        x -= (x >> 1) & 0x55555555;
        x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
        x += x >> 4;
        x &= 0x0f0f0f0f;
        x += x >> 8;
        x += x >> 16;
        return (unsigned char)x;
    }
}
