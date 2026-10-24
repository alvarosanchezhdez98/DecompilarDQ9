#include <m2c.h>

void *func_0207f0ac(s32);

void func_02081130(s32 arg0, s32 arg1, s32 arg2) {
    u8 temp_r1;
    void *temp_r0;

    temp_r0 = func_0207f0ac(arg0 + 0xC);
    if (temp_r0 == NULL) {
        return;
    }
    temp_r1 = M2C_FIELD(temp_r0, u8 *, 0x15);
    if (arg2 != 0) {
        M2C_FIELD(temp_r0, u8 *, 0x15) = (u8) (temp_r1 | 1);
        return;
    }
    M2C_FIELD(temp_r0, u8 *, 0x15) = (u8) (temp_r1 & ~1);
}
