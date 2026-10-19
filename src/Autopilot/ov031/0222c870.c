#include <m2c.h>

s32 FastIntModulus(u16, M2C_UNK);
extern M2C_UNK data_ov031_02290c8c;

void ov13_02230C68(void) {
    s32 temp_r1;

    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), u8 *, 0x56) == 0) {
        return;
    }
    temp_r1 = 0x01FF0000 & ((FastIntModulus(M2C_FIELD(&data_ov031_02290c8c, u16 *, 2), 0x1C) - 0x32) << 0x10);
    M2C_FIELD((void *)0x04000010, s32 *, 0) = temp_r1;
    M2C_FIELD((void *)0x04000010, s32 *, 8) = temp_r1;
    M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), u8 *, 0x56) = 0U;
}
