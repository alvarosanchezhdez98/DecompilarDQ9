#include <m2c.h>

M2C_UNK func_020469b4(s32, s32);
s32 func_02046b24(s32);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021a7adc(s32);
M2C_UNK func_ov017_021a7c28(s32, M2C_UNK);

void func_ov017_021a7a74(s32 arg0, M2C_UNK arg1) {
    s32 temp_r5;
    s32 temp_r6;
    void *temp_r0;

    temp_r0 = func_ov017_0218b5b0();
    temp_r6 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    if ((func_02046b24(temp_r6) == 0x1A) && (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x3B0C), s32 *, 0x64) != 0)) {
        return;
    }
    temp_r5 = M2C_FIELD(temp_r0, s32 *, 0x3B98);
    func_ov017_021a7adc(temp_r5);
    func_ov017_021a7c28(temp_r5, arg1);
    func_020469b4(temp_r6, temp_r5);
}
