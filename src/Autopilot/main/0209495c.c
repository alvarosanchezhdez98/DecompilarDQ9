#include <m2c.h>


s32 func_0209494c(void *arg0) {
    s32 var_r0;

    if (((u32) (M2C_FIELD(arg0, u8 *, 0x3C9) << 0x1F) >> 0x1F) != 0) {
        if ((s32) M2C_FIELD(arg0, s8 *, 0x3CB) <= 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 1;
}
