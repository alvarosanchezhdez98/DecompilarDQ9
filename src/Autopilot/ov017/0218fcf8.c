#include <m2c.h>

M2C_UNK func_ov017_0218fd34(M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_ov017_02191fec();

void func_ov017_0218fcf8(M2C_UNK arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_r0;

    if (func_ov017_02191fec() != 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        return;
    }
    func_ov017_0218fd34(arg0, arg1, arg2);
}
