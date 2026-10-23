#include <m2c.h>


s32 func_ov003_0215ee68(void *arg0) {
    u8 var_r2;

    var_r2 = 1;
    M2C_FIELD(arg0, s8 *, 0x1E) = 1;
    if (M2C_FIELD(arg0, u8 *, 0x20) != 0) {
        var_r2 = 0;
    }
    M2C_FIELD(arg0, u8 *, 0x20) = var_r2;
    return 5;
}
