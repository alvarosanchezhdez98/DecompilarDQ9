#include <m2c.h>

s32 func_0205ec34();
M2C_UNK func_02064b98(s32, s32);
M2C_UNK memcpy(s32, M2C_UNK);

void func_ov017_021cdccc(s32 arg0, s32 arg1, M2C_UNK arg2) {
    s32 temp_r0;
    s32 var_r2;
    s32 var_r4;
    u32 temp_r1;

    temp_r0 = func_0205ec34();
    temp_r1 = arg1 + 0xE;
    var_r2 = 0xE;
    var_r4 = 0;
    if (temp_r1 > 0xFDU) {
        var_r2 = 0xFD - arg1;
        var_r4 = 1;
    } else if (temp_r1 == 0xFD) {
        var_r4 = 1;
    }
    if (var_r2 < 0) {
        return;
    }
    memcpy(temp_r0 + arg1, arg2);
    if (var_r4 == 0) {
        return;
    }
    func_02064b98(func_0205ec34(), 0xC3B5);
}
