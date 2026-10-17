#include <m2c.h>

void *func_020421a0();
M2C_UNK func_0204500c(void *, s32, M2C_UNK, M2C_UNK);

void func_ov003_0215cab0(void *arg0, s32 arg1) {
    void *temp_r0;

    if (arg1 == 0) {
        return;
    }
    temp_r0 = func_020421a0();
    func_0204500c(temp_r0, arg1, 0, 0xE3);
    M2C_FIELD(temp_r0, u8 *, 0x19B2) = (u8) M2C_FIELD(arg0, u8 *, 0x3EF);
    M2C_FIELD(temp_r0, s32 *, 0x99C) = (s32) M2C_FIELD(arg0, u8 *, 0x3EE);
}
