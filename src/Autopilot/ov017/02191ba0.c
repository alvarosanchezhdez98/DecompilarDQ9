#include <m2c.h>
#pragma optimization_level 4


void func_ov017_02191ba0(s32 arg0, s32 arg1, s16 arg2) {
    s32 var_r3;
    void *temp_r1;

    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r3 = 1;
    } else {
        var_r3 = 0;
    }
    if (var_r3 == 0) {
        return;
    }
    temp_r1 = arg0 + (arg1 * 4);
    M2C_FIELD(temp_r1, s16 *, 0x449E) = arg2;
    M2C_FIELD(temp_r1, s8 *, 0x449C) = 1;
}
