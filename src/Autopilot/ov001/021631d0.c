#include <m2c.h>

void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021d6134(M2C_UNK, u8);

s32 func_ov001_021631d0(M2C_UNK arg0) {
    u8 temp_r1;
    void *temp_r3;

    temp_r3 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3734);
    temp_r1 = M2C_FIELD(temp_r3, u8 *, 0x105);
    M2C_FIELD(temp_r3, u8 *, 0x105) = 0U;
    func_ov017_021d6134(arg0, temp_r1);
    return 1;
}
