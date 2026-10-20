#include <m2c.h>

s32 func_0205bea0(void *);

s32 func_0205c6bc(void *arg0) {
    s32 var_r2;

    var_r2 = 0;
    if (M2C_FIELD(arg0, u8 *, 0x94) != 0) {
        var_r2 = func_0205bea0(arg0 + 4);
    }
    return var_r2;
}
