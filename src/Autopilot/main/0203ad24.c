#include <m2c.h>

M2C_UNK func_020bbd9c();
M2C_UNK func_020bd42c(void *);
s32 func_020bec30(void *, s16, M2C_UNK);

s32 func_0203ad14(void *arg0, s16 arg1, void *arg2, M2C_UNK arg3) {
    s32 var_r0;

    if (M2C_FIELD(arg0, s32 *, 0) == 0) {
        return 0;
    }
    func_020bd42c(arg0 + 4);
    M2C_FIELD(arg0, s16 *, 0xA4) = arg1;
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    if (arg2 != NULL) {
        var_r0 = func_020bec30(arg2, arg1, arg3);
    } else {
        var_r0 = func_020bec30(arg0 + 0x9C, arg1, arg3);
    }
    func_020bbd9c();
    return var_r0;
}
