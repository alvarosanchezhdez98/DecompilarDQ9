#include <m2c.h>

void *func_ov017_0218b5b0();
void *func_ov017_021bbbe4(s32);
M2C_UNK func_ov017_021d6134(s32, u8);
M2C_UNK func_ov017_021d6148(s32, s32);

s32 func_ov001_0216089c(s32 arg0) {
    void *temp_r0;

    temp_r0 = func_ov017_021bbbe4(M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x3734));
    if ((s32) M2C_FIELD(temp_r0, s8 *, 0) < 0) {
        return 0;
    }
    func_ov017_021d6134(arg0, M2C_FIELD(temp_r0, u8 *, 0x14));
    func_ov017_021d6148(arg0 + 8, M2C_FIELD(temp_r0, s32 *, 0x18));
    return 1;
}
