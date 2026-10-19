#include <m2c.h>

void *func_0205ec34();

void func_020107dc(void *arg0, s32 arg1) {
    void *temp_r0;

    M2C_FIELD(arg0, s32 *, 0x5CB8) = arg1;
    temp_r0 = func_0205ec34();
    M2C_FIELD(((M2C_FIELD(temp_r0, u8 *, 0x332) * 0x1C) + (s32) temp_r0), s8 *, 2) = (s8) arg1;
}
