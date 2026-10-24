#include <m2c.h>


void func_0202630c(s32 arg0, void *arg1, s32 arg2) {
    s32 temp_r2;
    s32 temp_r3;

    temp_r3 = 0x100000 - arg2;
    if ((s32) M2C_FIELD(arg1, s32 *, 0) <= arg2) {
        M2C_FIELD(arg1, s32 *, 0) = arg2;
    }
    if ((s32) M2C_FIELD(arg1, s32 *, 0) >= temp_r3) {
        M2C_FIELD(arg1, s32 *, 0) = temp_r3;
    }
    if ((s32) M2C_FIELD(arg1, s32 *, 8) <= arg2) {
        M2C_FIELD(arg1, s32 *, 8) = arg2;
    }
    temp_r2 = 0xC0000 - arg2;
    if ((s32) M2C_FIELD(arg1, s32 *, 8) >= temp_r2) {
        M2C_FIELD(arg1, s32 *, 8) = temp_r2;
    }
}
