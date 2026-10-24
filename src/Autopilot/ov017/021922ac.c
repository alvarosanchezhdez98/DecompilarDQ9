#include <m2c.h>

s32 func_ov017_02191b58(void *);

s32 func_ov017_021922ac(void *arg0, u32 arg1) {
    u32 var_r0;
    s32 var_r4;

    var_r4 = 0;
    if (M2C_FIELD(arg0, u8 *, 0x4489) != 0) {
        if (arg1 <= 3U) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            if (func_ov017_02191b58(arg0) & 2) {
                var_r4 = 1;
            }
        }
    } else {
        var_r4 = 1;
    }
    if (M2C_FIELD(arg0, u8 *, 0x4488) == 0) {
        var_r4 = 0;
    }
    return var_r4;
}
