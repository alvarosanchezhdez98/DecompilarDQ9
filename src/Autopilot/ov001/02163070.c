#include <m2c.h>

M2C_UNK func_020466e4(s32, M2C_UNK);
M2C_UNK func_020466f4(s32, M2C_UNK);
s32 func_020aad1c(s32, s32, M2C_UNK, M2C_UNK);
s32 func_020d6c00();
M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov001_021658b8;

s32 func_ov001_02163070(M2C_UNK arg0) {
    M2C_UNK var_r1;
    s32 temp_r0;
    s32 var_r5;

    if (M2C_FIELD(&data_ov001_021658b8, s32 *, 0x4B4) == 0) {
        return 0;
    }
    temp_r0 = func_020d6c00();
    func_020466e4(temp_r0, 0x80);
    if (func_020aad1c(M2C_FIELD(&data_ov001_021658b8, s32 *, 0x4B4), M2C_FIELD(&data_ov001_021658b8, s32 *, 0x4B8), 0xA, 0) != 0) {
        var_r5 = 1;
    } else {
        var_r5 = 0;
    }
    if (var_r5 == 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov017_021d6134(arg0, var_r1);
    if (var_r5 != 0) {
        func_020466f4(temp_r0, 0x80);
    }
    return 1;
}
