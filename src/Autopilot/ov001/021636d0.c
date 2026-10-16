#include <m2c.h>

M2C_UNK func_0209c2e0();
s32 func_ov017_021d60f4();
extern M2C_UNK data_02109bf4;

s32 func_ov001_021636d0(s32 arg0, s32 arg1) {
    s32 var_r2;
    s32 var_r4;

    var_r4 = func_ov017_021d60f4();
    if (var_r4 < 0) {
        var_r4 = 0;
    } else if (var_r4 > 0x7F) {
        var_r4 = 0x7F;
    }
    var_r2 = 0;
    if (arg1 >= 2) {
        var_r2 = func_ov017_021d60f4(arg0 + 8);
    }
    func_0209c2e0(&data_02109bf4, var_r4, var_r2);
    return 1;
}
