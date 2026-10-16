#include <m2c.h>

void *func_ov017_0218b5b0();

void func_ov002_0215a878(void *arg0) {
    void *temp_r3;

    M2C_FIELD(arg0, s32 *, 0x2540) = (s32) M2C_FIELD(arg0, s16 *, 0x1BE0);
    M2C_FIELD(arg0, s32 *, 0x2544) = (s32) M2C_FIELD(arg0, s16 *, 0x1BFE);
    M2C_FIELD(arg0, u8 *, 0x253C) = 1U;
    temp_r3 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x371C);
    M2C_FIELD(temp_r3, u8 *, 0x24) = (u8) M2C_FIELD(arg0, u8 *, 0x253C);
    M2C_FIELD(temp_r3, s32 *, 0x28) = (s32) M2C_FIELD(arg0, s32 *, 0x2540);
    M2C_FIELD(temp_r3, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 0x2544);
}
