#include <m2c.h>

void *func_0205ec34();

void func_020107a8(void *arg0, s32 arg1) {
    void *temp_r0;

    M2C_FIELD(arg0, s32 *, 0x5CB4) = arg1;
    temp_r0 = func_0205ec34();
    M2C_FIELD(((M2C_FIELD(temp_r0, u8 *, 0x332) * 0x1C) + (s32) temp_r0), s8 *, 1) = (s8) arg1;
}
