#include <m2c.h>


s32 func_ov002_02168c00(void *arg0) {
    s32 var_r0;
    s32 var_r2;

    if (M2C_FIELD(arg0, s32 *, 0x60) == -1) {
        var_r2 = 1;
    } else {
        var_r2 = 0;
    }
    if (M2C_FIELD(arg0, s32 *, 0x64) == -1) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r2 & var_r0) {
        return 1;
    }
    return 0;
}
