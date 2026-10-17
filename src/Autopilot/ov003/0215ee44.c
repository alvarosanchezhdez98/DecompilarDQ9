#include <m2c.h>


s32 func_ov003_0215ee44(void *arg0) {
    u8 var_r1;

    if (M2C_FIELD(arg0, u8 *, 0x1E) == 2) {
        var_r1 = 1;
    } else {
        var_r1 = 2;
    }
    M2C_FIELD(arg0, u8 *, 0x1E) = var_r1;
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
    return 4;
}
