#include <m2c.h>

extern M2C_UNK data_02107800;

s32 func_020429bc(s32 arg0) {
    s32 var_r0;

    var_r0 = 0;
    if (arg0 == 8) {
        var_r0 = M2C_FIELD(&data_02107800, s32 *, 0x10);
    }
    return var_r0;
}
