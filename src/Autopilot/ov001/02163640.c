#include <m2c.h>

M2C_UNK func_0209c3b4();
M2C_UNK func_0209c678();
s32 func_ov017_021d60f4();
extern M2C_UNK data_02109bf4;

s32 func_ov001_02163640(s32 arg0, s32 arg1) {
    s32 var_r2;

    var_r2 = -1;
    if (arg1 == 2) {
        func_ov017_021d60f4();
        var_r2 = func_ov017_021d60f4(arg0 + 8);
    } else if (arg1 == 1) {
        var_r2 = func_ov017_021d60f4();
    }
    if (var_r2 < 0) {
        return 0;
    }
    func_0209c3b4(&data_02109bf4, var_r2);
    func_0209c678(&data_02109bf4, 0);
    return 1;
}
