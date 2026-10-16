#include <m2c.h>


void func_ov000_02162c90(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r3;

    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r3 = 1;
    } else {
        var_r3 = 0;
    }
    if (var_r3 != 0) {
        M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0x54F4) = arg2;
    }
}
