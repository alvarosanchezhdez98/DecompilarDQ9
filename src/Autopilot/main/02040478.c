#include <m2c.h>


s32 func_02040468(void *arg0, s32 arg1) {
    s32 temp_r2;
    s32 var_r0;

    temp_r2 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_r2 == 0) {
        return 0;
    }
    if ((arg1 < 0) || ((u32) M2C_FIELD(arg0, u32 *, 0) <= (u32) arg1)) {
        return 0;
    }
    var_r0 = (arg1 * 0x3C) + temp_r2;
    if ((s32) M2C_FIELD(var_r0, s32 *, 0x38) < 0) {
        var_r0 = 0;
    }
    return var_r0;
}
