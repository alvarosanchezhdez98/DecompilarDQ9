#include <m2c.h>


s32 func_ov025_021dfbd4(s32 arg0) {
    s32 var_r1;

    if ((arg0 >= 0) && (arg0 <= 3)) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    if (var_r1 != 0) {
        return arg0 + 0xF2;
    }
    return arg0 + 0x36;
}
