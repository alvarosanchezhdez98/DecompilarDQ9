#include <m2c.h>

s32 func_0206e120();

s32 func_02095ae0(M2C_UNK arg0, M2C_UNK arg1) {
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r4;

    var_r4 = 1;
    if (func_0206e120() == 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        if (func_0206e120(arg0, arg1) == 1) {
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 == 0) {
            var_r4 = 0;
        }
    }
    return var_r4;
}
