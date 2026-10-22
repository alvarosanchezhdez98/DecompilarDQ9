#include <m2c.h>

s32 func_0205bb84(void *);
s32 func_0205bd04(void *);

s32 func_0205c570(void *arg0) {
    s32 var_r0;

    var_r0 = -1;
    if ((M2C_FIELD(arg0, u8 *, 0x94) != 0) && (M2C_FIELD(arg0, u8 *, 0x50) != 0)) {
        var_r0 = func_0205bd04(arg0 + 4);
    }
    if (M2C_FIELD(arg0, u8 *, 0x95) == 0) {
        return var_r0;
    }
    return func_0205bb84(arg0 + 0x54);
}
