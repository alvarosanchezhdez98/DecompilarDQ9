#include <m2c.h>

extern M2C_UNK data_ov031_02290c8c;

void func_ov031_0222c5d4(s32 arg0, s32 arg1) {
    s32 temp_r2;
    void *temp_r3;
    void *temp_r4;

    if (arg0 >= (s32) M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), u8 *, 0x51)) {
        return;
    }
    temp_r2 = arg0 * 0x2A;
    temp_r4 = M2C_FIELD((M2C_FIELD(&data_ov031_02290c8c, void **, 4) + (arg1 * 4)), void **, 0x10);
    M2C_FIELD(temp_r4, u16 *, 4) = (u16) ((M2C_FIELD(temp_r4, u16 *, 4) & ~0x3FF) | M2C_FIELD((M2C_FIELD(&data_ov031_02290c8c, void **, 4) + (M2C_FIELD((M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), s32 *, 0) + temp_r2), u8 *, 0x28) * 2)), u16 *, 0x42));
    temp_r3 = M2C_FIELD((M2C_FIELD(&data_ov031_02290c8c, void **, 4) + (arg1 * 4)), void **, 0x24);
    M2C_FIELD(temp_r3, u16 *, 4) = (u16) ((M2C_FIELD(temp_r3, u16 *, 4) & ~0x3FF) | M2C_FIELD((M2C_FIELD(&data_ov031_02290c8c, void **, 4) + (M2C_FIELD((M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), s32 *, 0) + temp_r2), u16 *, 0x26) * 2)), u16 *, 0x48));
}
