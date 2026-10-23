#include <m2c.h>

s32 func_0205ec34();
M2C_UNK func_0206df6c(s32, s32, s32, M2C_UNK);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021cdb00(M2C_UNK, s32, M2C_UNK, M2C_UNK);

void func_020ae4ec(s32 arg0, M2C_UNK arg1) {
    s32 temp_r0;

    temp_r0 = func_0205ec34();
    func_0206df6c(temp_r0, temp_r0 + 0x8C, arg0 + 0x33E, arg1);
    if (M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x4458) == 0) {
        return;
    }
    func_ov017_021cdb00(7, arg0, arg1, -1);
}
