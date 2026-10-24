#include <m2c.h>

void *func_0207f6ac(s32);

void func_02080798(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_r0;

    temp_r0 = func_0207f6ac(arg0 + 4);
    if (temp_r0 != NULL) {
        M2C_FIELD(temp_r0, u8 *, 0x14) = (u8) ((M2C_FIELD(temp_r0, u8 *, 0x14) & ~3) | (arg2 & 3));
    }
}
