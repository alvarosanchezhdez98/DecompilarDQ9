#include <m2c.h>


s32 func_ov000_021761ec(s32 arg0, s32 arg1) {
    s32 var_r1;

    var_r1 = arg1;
    if ((var_r1 < 0) || (var_r1 >= 8)) {
        var_r1 = 0;
    }
    return M2C_FIELD((arg0 + (var_r1 * 4)), s32 *, 0x1D3C);
}
