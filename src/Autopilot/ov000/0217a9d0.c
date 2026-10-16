#include <m2c.h>

M2C_UNK func_02050400(s32, M2C_UNK);
s32 func_0205d81c(M2C_UNK, M2C_UNK);

void func_ov000_0217a9d0(M2C_UNK arg0, s32 arg1, s32 arg2, M2C_UNK arg3) {
    M2C_UNK var_r1;
    s32 temp_r0;

    temp_r0 = func_0205d81c(arg3, arg0);
    if (temp_r0 == 0) {
        return;
    }
    var_r1 = 0;
    if (arg2 < arg1) {
        var_r1 = 1;
    }
    func_02050400(temp_r0, var_r1);
}
