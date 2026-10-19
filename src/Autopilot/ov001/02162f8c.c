#include <m2c.h>

M2C_UNK func_0203b4a0(void *, M2C_UNK);
s32 func_0203b4c4(void *, M2C_UNK);
s32 func_02046b24(s32);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);

s32 func_ov001_02162f8c(M2C_UNK arg0) {
    M2C_UNK var_r1;
    s32 var_r5;
    void *temp_r0;

    temp_r0 = func_ov017_0218b5b0();
    if (func_0203b4c4(temp_r0, 0x10) != 0) {
        func_ov017_021d6134(arg0, 0);
        return 1;
    }
    if (func_02046b24(M2C_FIELD(temp_r0, s32 *, 0x3700)) != 0x13) {
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
        func_0203b4a0(temp_r0, 0x10);
    }
    return 1;
}
