#include <m2c.h>


s32 func_0205c6e4(void *arg0) {
    s32 var_r2;

    var_r2 = 0;
    if ((M2C_FIELD(arg0, u8 *, 0x94) != 0) && (M2C_FIELD(arg0, u8 *, 0x50) != 0)) {
        var_r2 = M2C_FIELD(arg0, s32 *, 8);
    }
    if (M2C_FIELD(arg0, u8 *, 0x95) != 0) {
        var_r2 = M2C_FIELD(arg0, s32 *, 0x58);
    }
    return var_r2;
}
