#include <m2c.h>

s32 func_ov031_022115a4();
s32 func_ov031_02211720(void *);

s32 func_ov031_0221156c(void *arg0) {
    s32 var_r0;

    if (func_ov031_022115a4() != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x3C) == func_ov031_02211720(arg0)) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
