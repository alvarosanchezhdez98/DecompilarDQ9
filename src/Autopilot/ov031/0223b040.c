#include <m2c.h>

s32 ov13_0223D590();
s32 ov13_0223D5C4(s32);
extern s32 data_ov031_02290d20;

s32 ov13_0223F380(s32 arg0) {
    s32 temp_r0;

    temp_r0 = ov13_0223D5C4(arg0 + 0xA);
    if (temp_r0 == 0) {
        return 0;
    }
    M2C_FIELD((data_ov031_02290d20 + ((temp_r0 - 1) * 4)), s32 *, 0xAA0) = ov13_0223D590();
    return 1;
}
