#include <m2c.h>


s32 func_0204aa48(void *arg0) {
    s32 var_r2;

    var_r2 = 5;
    if (M2C_FIELD(arg0, u8 *, 0xA) != 0) {
        var_r2 = 6;
    }
    return M2C_FIELD(arg0, s16 *, 4) << var_r2;
}
