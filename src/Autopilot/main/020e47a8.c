#include <m2c.h>

s32 sprintf();

s32 func_020e4798(s32 arg0, void *arg1) {
    s32 var_r4;

    var_r4 = arg0;
    if (M2C_FIELD(arg1, s32 *, 4) != 0) {
        var_r4 += sprintf();
    }
    return var_r4;
}
