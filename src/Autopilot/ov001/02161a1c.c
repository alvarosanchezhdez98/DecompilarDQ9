#include <m2c.h>

void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021d6134(M2C_UNK, u8);

s32 func_ov001_02161a1c(M2C_UNK arg0) {
    void *temp_r1;

    temp_r1 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3734);
    if (M2C_FIELD(temp_r1, s32 *, 0x160) == 0) {
        func_ov017_021d6134(arg0, 1U);
    } else {
        func_ov017_021d6134(arg0, M2C_FIELD(temp_r1, u8 *, 0x164));
    }
    return 1;
}
