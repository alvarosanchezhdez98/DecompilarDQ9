#include <m2c.h>


s32 func_02020084(void *arg0, s32 arg1) {
    s32 var_r0;
    s32 var_r2;

    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r2 = 1;
    } else {
        var_r2 = 0;
    }
    if (var_r2 != 0) {
        var_r0 = 1;
        if (!(M2C_FIELD(arg0, u8 *, 0x55D) & (1 << arg1))) {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
