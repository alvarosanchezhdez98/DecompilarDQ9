#include <m2c.h>

s32 func_020a10a8(s32);

s32 func_0202eeb4(s32 arg0) {
    s32 var_r4;
    s32 var_r5;

    var_r4 = 1;
    var_r5 = 1;
    if ((func_020a10a8(arg0 + 0x16C) == 0) && (func_020a10a8(arg0 + 0x194) == 0)) {
        var_r5 = 0;
    }
    if ((var_r5 == 0) && (func_020a10a8(arg0 + 0x1BC) == 0)) {
        var_r4 = 0;
    }
    return var_r4;
}
