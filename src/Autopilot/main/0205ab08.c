#include <m2c.h>

M2C_UNK func_020b0318();
M2C_UNK func_020b0368(s32, s32, M2C_UNK, void *);
M2C_UNK func_020b0594(s32, M2C_UNK, M2C_UNK, void *);
s32 func_0205a1f0(s32 *, M2C_UNK, M2C_UNK);

s32 func_0205aaf8(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 sp0;
    M2C_UNK var_r2;

    func_020b0318();
    if (func_0205a1f0(&sp0, arg1, arg2) != 0) {
        return 1;
    }
    if (M2C_FIELD(arg0, u8 *, 0x50) == 0) {
        var_r2 = 1;
    } else {
        var_r2 = 2;
    }
    if (M2C_FIELD(arg0, s32 *, 0x38) == 4) {
        func_020b0594(sp0, 0, var_r2, arg0);
    } else {
        func_020b0368(sp0, M2C_FIELD(arg0, s32 *, 0x44), var_r2, arg0);
    }
    return 0;
}
