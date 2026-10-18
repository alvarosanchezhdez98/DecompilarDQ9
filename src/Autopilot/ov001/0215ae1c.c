#include <m2c.h>

M2C_UNK func_0201229c(M2C_UNK *);
s32 func_020123e0(M2C_UNK *);
s32 func_020123f4(M2C_UNK *);
s32 func_02012408(M2C_UNK *);
s32 func_0201241c(M2C_UNK *);
M2C_UNK func_ov017_021d6134(M2C_UNK, s32);
extern M2C_UNK data_02114e30;

s32 func_ov001_0215ae1c(M2C_UNK arg0, s32 arg1) {
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;

    if (arg1 < 1) {
        return 0;
    }
    func_0201229c(&data_02114e30);
    temp_r6 = func_0201241c(&data_02114e30);
    temp_r5 = func_02012408(&data_02114e30);
    temp_r4 = func_020123e0(&data_02114e30);
    func_ov017_021d6134(arg0, temp_r6 + (temp_r5 + (temp_r4 + func_020123f4(&data_02114e30))));
    return 1;
}
