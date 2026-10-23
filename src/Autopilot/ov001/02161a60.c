#include <m2c.h>

M2C_UNK _ZN9StaffRoll6FinishEv(s32);
M2C_UNK func_020a1f4c(M2C_UNK);
void *func_ov017_0218b5b0();

s32 func_ov001_02161a60(void) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3734);
    _ZN9StaffRoll6FinishEv(M2C_FIELD(temp_r4, s32 *, 0x160));
    M2C_FIELD(temp_r4, s32 *, 0x160) = 0;
    func_020a1f4c(1);
    return 1;
}
