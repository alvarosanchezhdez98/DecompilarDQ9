#include <m2c.h>

M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);
extern M2C_UNK data_02114e54;

s32 func_ov001_0215aeb8(M2C_UNK arg0) {
    M2C_UNK var_r1;

    if ((M2C_FIELD(&data_02114e54, u8 *, 0x54) != 0) && ((u32) M2C_FIELD(&data_02114e54, u32 *, 0x44) < 0xAU)) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov017_021d6134(arg0, var_r1);
    return 1;
}
