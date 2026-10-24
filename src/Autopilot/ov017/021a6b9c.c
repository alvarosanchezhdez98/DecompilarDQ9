#include <m2c.h>

M2C_UNK func_020469b4(s32, void *);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021a6be4(void *);

void func_ov017_021a6b9c(s32 arg0, s8 arg1) {
    s32 temp_r5;
    void *temp_r0;
    void *temp_r6;

    temp_r0 = func_ov017_0218b5b0();
    temp_r6 = M2C_FIELD(temp_r0, void **, 0x3B90);
    temp_r5 = M2C_FIELD(temp_r0, s32 *, 0x36FC);
    func_ov017_021a6be4(temp_r6);
    M2C_FIELD(temp_r6, s8 *, 0x10) = arg1;
    func_020469b4(temp_r5, temp_r6);
    M2C_FIELD(temp_r0, s16 *, 0x44AE) = 0;
    M2C_FIELD(temp_r0, s16 *, 0x44B0) = 0;
}
