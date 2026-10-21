#include <m2c.h>

extern M2C_UNK data_02114e54;

s32 func_0205bd20(void *arg0) {
    s32 var_r2;

    var_r2 = 0;
    if ((M2C_FIELD(&data_02114e54, u8 *, 0x55) != 0) && (M2C_FIELD(arg0, u8 *, 0x4E) == 1) && (M2C_FIELD(arg0, u8 *, 0x4C) != 0)) {
        var_r2 = 1;
    }
    return var_r2;
}
