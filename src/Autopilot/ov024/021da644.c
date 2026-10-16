#include <m2c.h>


u32 func_ov024_021da644(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r0_2;
    u32 var_r0;

    if ((arg0 >= 0) && (arg0 <= 3)) {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 != 0) {
        var_r0 = arg1 << 0x10;
    } else {
        var_r0 = arg2 << 0x10;
    }
    return var_r0 >> 0x10;
}
