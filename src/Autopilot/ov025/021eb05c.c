#include <m2c.h>


void func_ov025_021eb05c(void *arg0, s32 arg1) {
    u8 temp_r2;

    if (arg1 < 0) {
        return;
    }
    temp_r2 = M2C_FIELD(arg0, u8 *, 0x582);
    if ((u32) temp_r2 < 8U) {
        M2C_FIELD(arg0, u8 *, 0x582) = (u8) (temp_r2 + 1);
        M2C_FIELD((arg0 + (temp_r2 * 2)), s16 *, 0x584) = (s16) arg1;
    }
}
