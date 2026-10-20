#include <m2c.h>


s32 func_0207959c(void *arg0, s32 arg1) {
    s32 var_r0;
    u8 temp_r0;

    temp_r0 = M2C_FIELD(arg0, u8 *, 0x17D);
    if (temp_r0 & 8) {
        if (((u8) ((s32) temp_r0 >> 4) & 3) == arg1) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
