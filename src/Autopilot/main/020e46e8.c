#include <m2c.h>

s32 sprintf();

s32 func_020e46d8(s32 arg0, s32 *arg1) {
    s32 var_r4;

    var_r4 = arg0;
    if (*arg1 != 0) {
        var_r4 += sprintf();
    }
    return var_r4;
}
