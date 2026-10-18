#include <m2c.h>


void func_020488cc(void *arg0, s32 arg1) {
    s8 var_r2;

    if (arg1 != 0) {
        var_r2 = 1;
    } else {
        var_r2 = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x180) = var_r2;
    if (arg1 != 0) {
        M2C_FIELD(arg0, s8 *, 0x17F) = 0;
    }
}
