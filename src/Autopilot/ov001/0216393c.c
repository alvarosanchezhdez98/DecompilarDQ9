#include <m2c.h>
#pragma optimization_level 4

M2C_UNK func_0209c678(M2C_UNK *, s32);
s32 func_ov017_021d60f4();
extern M2C_UNK data_02109bf4;

s32 func_ov001_0216393c(s32 arg0, s32 arg1) {
    s32 var_r1;

    var_r1 = 0x1E;
    if (arg1 > 0) {
        var_r1 = func_ov017_021d60f4();
    }
    func_0209c678(&data_02109bf4, var_r1);
    return 1;
}
