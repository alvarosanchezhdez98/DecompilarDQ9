#include <m2c.h>

s32 func_020421a0();
M2C_UNK func_02043124(s32);
s32 func_ov000_02160f20(s32);
M2C_UNK func_ov000_021626a0(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov000_02163524(s32);
M2C_UNK func_ov000_0216dbf0(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_ov017_0218b5b0();
M2C_UNK func_ov025_021d8a40(s32, s32);
M2C_UNK func_ov025_021def30(s32);
extern M2C_UNK data_ov025_021ef974;

void func_ov025_021dc880(s32 arg0) {
    s32 temp_r1;
    s32 temp_r5;

    func_ov017_0218b5b0();
    func_ov000_02163524(arg0);
    temp_r5 = func_020421a0();
    if (M2C_FIELD(&data_ov025_021ef974, s32 *, 8) == 0) {
        func_ov000_0216dbf0(arg0 + 0xC18, 0, 0, 0);
        func_ov000_021626a0(arg0, 4, 1);
        func_02043124(temp_r5);
        M2C_FIELD(&data_ov025_021ef974, s32 *, 8) = 1;
    }
    if (M2C_FIELD(&data_ov025_021ef974, s32 *, 8) != 1) {
        return;
    }
    temp_r1 = M2C_FIELD(&data_ov025_021ef974, s32 *, 0x10) + 1;
    M2C_FIELD(&data_ov025_021ef974, s32 *, 0x10) = temp_r1;
    if (temp_r1 == 0xF) {
        func_ov025_021d8a40(arg0, func_ov000_02160f20(arg0));
    }
    if (M2C_FIELD(&data_ov025_021ef974, s32 *, 0x10) != 0x3C) {
        return;
    }
    func_ov025_021def30(arg0);
}
