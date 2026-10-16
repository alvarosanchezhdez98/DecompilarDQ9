#include <m2c.h>

void *func_020421a0();
M2C_UNK func_02042b98(void *, M2C_UNK, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_0204500c(void *, s32, M2C_UNK, M2C_UNK);

void func_ov025_021e5e1c(void *arg0) {
    void *temp_r0;

    temp_r0 = func_020421a0();
    func_0204500c(temp_r0, M2C_FIELD(arg0, s32 *, 8), 0, 0xE3);
    M2C_FIELD(temp_r0, s8 *, 0x19B1) = 0;
    func_02042b98(temp_r0, 2, 0x92, 0xFC, 0x4A);
    M2C_FIELD(temp_r0, s8 *, 0x19B2) = 0;
    M2C_FIELD(temp_r0, s32 *, 0x998) = 1;
}
