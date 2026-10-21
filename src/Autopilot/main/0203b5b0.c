#include <m2c.h>


s32 func_0203b5a0(void *arg0, s32 arg1) {
    s32 var_r0;

    if (arg1 == 0) {
        var_r0 = (s32) M2C_FIELD(arg0, f32 *, 0xC);
    } else {
        var_r0 = (s32) M2C_FIELD(arg0, f32 *, 0x18);
    }
    if ((var_r0 > -0x10) && (var_r0 < 0x10)) {
        return 1;
    }
    return 0;
}
