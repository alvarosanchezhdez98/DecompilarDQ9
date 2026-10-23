#include <m2c.h>


void func_0203cec4(void *arg0, s32 arg1) {
    s32 temp_r1;
    s32 var_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x5C);
    if (arg1 != 0) {
        var_r1 = temp_r1 | 8;
    } else {
        var_r1 = temp_r1 & ~8;
    }
    M2C_FIELD(arg0, s32 *, 0x5C) = var_r1;
}
