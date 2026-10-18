#include <m2c.h>


s32 func_ov017_0219219c(s32 arg0, s32 arg1) {
    s32 var_r2;
    s32 var_r2_2;

    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r2 = 1;
    } else {
        var_r2 = 0;
    }
    if (var_r2 != 0) {
        return arg0 + 0x36DC + arg1;
    }
    if ((arg1 >= 0xC0) && (arg1 <= 0xC7)) {
        var_r2_2 = 1;
    } else {
        var_r2_2 = 0;
    }
    if (var_r2_2 != 0) {
        return arg0 + 0x36E1 + (arg1 - 0xC0);
    }
    return 0;
}
