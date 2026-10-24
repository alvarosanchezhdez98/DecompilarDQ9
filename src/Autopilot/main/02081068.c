#include <m2c.h>

void *func_0207f6ac(s32);

void func_02081058(s32 arg0, s32 arg1, s8 arg2) {
    void *temp_r0;

    temp_r0 = func_0207f6ac(arg0 + 4);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s8 *, 0x2B) = arg2;
    M2C_FIELD(temp_r0, s8 *, 0x2C) = 8;
    M2C_FIELD(temp_r0, u8 *, 0x2A) = (u8) (M2C_FIELD(temp_r0, u8 *, 0x2A) | 0x20);
}
