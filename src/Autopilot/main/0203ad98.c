#include <m2c.h>

M2C_UNK func_020bd42c(void *);
M2C_UNK func_020bec58(void *, M2C_UNK);
s32 func_020bec98(void *);

s32 func_0203ad88(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 var_r4;

    if (M2C_FIELD(arg0, s32 *, 0) == 0) {
        return 0;
    }
    func_020bd42c(arg0 + 4);
    if (arg1 != NULL) {
        var_r4 = func_020bec98(arg1);
        func_020bec58(arg1, arg2);
    } else {
        var_r4 = func_020bec98(arg0 + 0x9C);
        func_020bec58(arg0 + 0x9C, arg2);
    }
    M2C_FIELD(arg0, s16 *, 0xA4) = -1;
    return var_r4;
}
