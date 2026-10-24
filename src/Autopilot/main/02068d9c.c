#include <m2c.h>

s32 func_020680cc(s32);

s32 func_02068d8c(s32 arg0, void *arg1) {
    s32 *temp_r0;
    s32 var_r0;

    temp_r0 = M2C_FIELD(arg1, s32 **, 0x20);
    if (temp_r0 != NULL) {
        if (func_020680cc(*temp_r0) == 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
