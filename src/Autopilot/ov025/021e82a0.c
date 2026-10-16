#include <m2c.h>

extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e82a0(void *arg0) {
    void *temp_r2;

    temp_r2 = M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC) + 0x540;
    M2C_FIELD(temp_r2, u16 *, 0x28) = (u16) (M2C_FIELD(temp_r2, u16 *, 0x28) | 2);
    M2C_FIELD(temp_r2, u8 *, 0x35) = (u8) M2C_FIELD(arg0, u8 *, 0xE);
    M2C_FIELD(temp_r2, s16 *, 0x2E) = (s16) M2C_FIELD(arg0, s16 *, 8);
    M2C_FIELD(temp_r2, s16 *, 0x30) = (s16) M2C_FIELD(arg0, s16 *, 0xA);
    M2C_FIELD(temp_r2, s16 *, 0x32) = (s16) M2C_FIELD(arg0, s16 *, 0xC);
    return 1;
}
