#include <m2c.h>


s32 func_ov000_02160f20(void *arg0) {
    s32 temp_r2;
    s32 var_r3;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0x29C);
    if (temp_r2 == 0) {
        return 0;
    }
    var_r3 = M2C_FIELD(arg0, s32 *, 0x770C);
    if (var_r3 == 0) {
        var_r3 = (M2C_FIELD(arg0, s32 *, 0x55D8) * 0x28) + (temp_r2 + 0x821C);
    }
    return var_r3;
}
