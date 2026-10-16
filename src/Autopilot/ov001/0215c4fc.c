#include <m2c.h>

s32 func_ov017_021d60f4();
M2C_UNK func_ov001_0215a42c();
s32 func_ov001_0215ab20();

s32 func_ov001_0215c4fc(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r1;

    func_ov017_021d60f4();
    temp_r0 = func_ov001_0215ab20();
    if (temp_r0 == 0) {
        return 0;
    }
    var_r1 = 0;
    if (arg1 >= 2) {
        var_r1 = func_ov017_021d60f4(arg0 + 8);
    }
    func_ov001_0215a42c(temp_r0, var_r1);
    return 1;
}
