#include <m2c.h>

M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);
s32 func_ov001_02158ab8(s32);
extern M2C_UNK data_ov001_02165880;

s32 func_ov001_0215d168(M2C_UNK arg0) {
    M2C_UNK var_r1;

    if (func_ov001_02158ab8(M2C_FIELD(&data_ov001_02165880, s32 *, 0x24)) == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov017_021d6134(arg0, var_r1);
    return 1;
}
