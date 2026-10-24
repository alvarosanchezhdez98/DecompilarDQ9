#include <m2c.h>

s32 func_0202df58();

s32 func_0202c508(s32 *arg0) {
    s32 var_r0;
    u32 var_r0_2;

    if (*arg0 != 0) {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 != 0) {
        if (func_0202df58() == 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 1;
}
