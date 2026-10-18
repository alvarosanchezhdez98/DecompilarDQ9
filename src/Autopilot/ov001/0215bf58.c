#include <m2c.h>

M2C_UNK func_ov017_021d60f4();
M2C_UNK func_ov017_021d6134(s32, M2C_UNK);
s32 func_ov001_0215a094();
s32 func_ov001_0215ab20();

s32 func_ov001_0215bf58(s32 arg0) {
    M2C_UNK var_r1;

    func_ov017_021d60f4();
    if (func_ov001_0215ab20() == 0) {
        return 0;
    }
    if (func_ov001_0215a094() == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov017_021d6134(arg0 + 8, var_r1);
    return 1;
}
