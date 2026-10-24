#include <m2c.h>


s32 ov00_021FD040(s32 arg0) {
    s32 var_r0;
    s32 temp_r1;
    u32 var_r3;

    temp_r1 = 0x20 - arg0;
    var_r3 = -1U;
    var_r0 = 0;
    if (temp_r1 > 0) {
        do {
            var_r0 += 1;
            var_r3 *= 2;
        } while (var_r0 < temp_r1);
    }
    return ((var_r3 << 0x18) & 0xFF000000) | (((var_r3 << 8) & 0xFF0000) | ((u8) (var_r3 >> 0x18) | ((var_r3 >> 8) & 0xFF00)));
}
