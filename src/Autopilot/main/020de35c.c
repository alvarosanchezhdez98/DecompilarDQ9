#include <m2c.h>


s32 func_020de34c(void *arg0, s32 arg1, s32 arg2) {
    s32 var_r0;
    u32 temp_r3;

    var_r0 = 0;
    temp_r3 = M2C_FIELD(arg0, s32 *, 8) << 0x1C;
    if ((arg1 <= (s32) (temp_r3 >> 0x1C)) && ((s32) (temp_r3 >> 0x1C) <= arg2)) {
        var_r0 = 1;
    }
    return var_r0;
}
