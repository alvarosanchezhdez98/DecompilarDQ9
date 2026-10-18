#include <m2c.h>

s32 func_0202ae18();
s32 func_0202b7d8();
s32 func_0202c1a4(s32);
M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);

s32 func_ov001_02160a00(M2C_UNK arg0) {
    M2C_UNK var_r1;
    s32 temp_r4;

    temp_r4 = func_0202ae18();
    if ((func_0202b7d8() == 0) || (func_0202c1a4(temp_r4) == 0)) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov017_021d6134(arg0, var_r1);
    return 1;
}
