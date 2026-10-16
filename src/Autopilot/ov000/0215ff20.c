#include <m2c.h>


void func_ov000_0215ff20(void *arg0, s16 arg1, s8 arg2) {
    u8 temp_r3;

    temp_r3 = M2C_FIELD(arg0, u8 *, 0x17);
    if ((u32) temp_r3 >= 3U) {
        return;
    }
    M2C_FIELD((arg0 + (temp_r3 * 2)), s16 *, 0xE) = arg1;
    M2C_FIELD((arg0 + M2C_FIELD(arg0, u8 *, 0x17)), s8 *, 0x14) = arg2;
    M2C_FIELD(arg0, u8 *, 0x17) = (u8) (M2C_FIELD(arg0, u8 *, 0x17) + 1);
}
