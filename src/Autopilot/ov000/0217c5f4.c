#include <m2c.h>

s32 func_02012444(M2C_UNK *, s32);
s32 func_0205d97c(s32);
extern M2C_UNK data_02114e30;

s32 func_ov000_0217c5f4(s32 arg0) {
    s32 temp_r4;
    s32 var_r0;

    temp_r4 = func_02012444(&data_02114e30, 0x802);
    if (func_0205d97c(arg0 + 0x188) == 2) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if ((temp_r4 | var_r0) != 0) {
        return 1;
    }
    return 0;
}
