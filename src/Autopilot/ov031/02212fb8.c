#include <m2c.h>

u32 ov00_021FAECC();
s32 ov00_021FBD5C();

s32 ov00_021FA9D4(void) {
    u32 temp_r0;

    temp_r0 = ov00_021FAECC();
    if (temp_r0 <= 1U) {
        return 0;
    }
    if (temp_r0 < 7U) {
        return 1;
    }
    if (temp_r0 == 9) {
        return 4;
    }
    if (temp_r0 < 0xAU) {
        return 2;
    }
    if (temp_r0 == 0xB) {
        return 4;
    }
    if (temp_r0 < 0x10U) {
        return 3;
    }
    if (temp_r0 == 0x10) {
        return 5;
    }
    if (temp_r0 == 0x11) {
        return 4;
    }
    return ov00_021FBD5C();
}
