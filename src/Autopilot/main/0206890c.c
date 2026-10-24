#include <m2c.h>


s32 func_020688fc(s32 arg0, void *arg1) {
    s32 temp_r0;
    s32 temp_r2;
    s32 var_r0;

    temp_r2 = M2C_FIELD(arg1, s32 *, 0);
    temp_r0 = M2C_FIELD(arg1, s32 *, 0x10);
    if ((temp_r2 != 0) && (temp_r0 != 0)) {
        if (temp_r2 != temp_r0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
