#include <m2c.h>

M2C_UNK func_020bd42c(void *);
s32 func_020be7a8(void *, s16, s16);
s32 func_020d84ec();

s32 func_0203ac40(void *arg0, s16 arg1, s16 arg2, void *arg3) {
    s32 var_r4;

    if (func_020d84ec() != 0) {
        M2C_FIELD(arg0, s16 *, 0xAC) = arg1;
        M2C_FIELD(arg0, s16 *, 0xAE) = arg2;
        return 1;
    }
    var_r4 = 0;
    if (M2C_FIELD(arg0, s32 *, 0) != 0) {
        func_020bd42c(arg0 + 4);
        if (arg3 != NULL) {
            if (func_020be7a8(arg3, arg1, arg2) != 0) {
                var_r4 = 1;
            }
        } else if (func_020be7a8(arg0 + 0x98, arg1, arg2) != 0) {
            var_r4 = 1;
        }
    }
    return var_r4;
}
