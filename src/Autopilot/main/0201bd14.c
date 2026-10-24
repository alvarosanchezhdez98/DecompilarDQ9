#include <m2c.h>

M2C_UNK func_02013380(s32, u8, M2C_UNK);
s32 func_0201b600(M2C_UNK, s32, u16);

void func_0201bd04(M2C_UNK arg0, s32 arg1, s32 arg2) {
    s32 temp_r0;
    u8 var_r1;

    temp_r0 = func_0201b600(arg0, arg2, arg1);
    var_r1 = 0;
    if (arg2 >= 0) {
        var_r1 = (u8) arg2;
    }
    if (temp_r0 == 0) {
        return;
    }
    func_02013380(temp_r0, var_r1, 1);
}
