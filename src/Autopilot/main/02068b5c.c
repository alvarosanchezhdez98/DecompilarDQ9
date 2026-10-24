#include <m2c.h>

s32 func_02067fec(s32 *, s32);

s32 func_02068b4c(s32 arg0, void *arg1) {
    s32 *temp_r0;
    s32 var_r0;

    temp_r0 = M2C_FIELD(arg1, s32 **, 0x10);
    if (temp_r0 != NULL) {
        if (func_02067fec(temp_r0, *temp_r0) == 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
