#include <m2c.h>


void func_02021410(void *arg0, s32 arg1, s8 arg2) {
    s8 var_r1;

    if (arg1 != 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x9C4) = var_r1;
    M2C_FIELD(arg0, s8 *, 0x9C8) = arg2;
}
