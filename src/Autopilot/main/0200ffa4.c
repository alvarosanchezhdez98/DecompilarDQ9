#include <m2c.h>


s32 func_0200ff94(s32 arg0, s32 arg1) {
    s32 var_r0;

    if (arg1 < 0) {
        return 0;
    }
    if (arg1 >= 0xE9) {
        return 0;
    }
    var_r0 = M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 8);
    if (var_r0 == 0) {
        var_r0 = 0;
    }
    return var_r0;
}
