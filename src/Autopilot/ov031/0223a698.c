#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32, void *, M2C_UNK);
u16 func_020d4dd4();
M2C_UNK ov13_0223DF00(s32);
extern void *data_ov031_02290d20;

void ov13_0223E9D8(void) {
    ov13_0223DF00(M2C_FIELD(data_ov031_02290d20, s32 *, 0xAC8));
    M2C_FIELD(data_ov031_02290d20, s8 *, 0xA90) = 1;
    M2C_FIELD(data_ov031_02290d20, u16 *, 0x648) = func_020d4dd4();
    VectorizedInvertedMemcpy(M2C_FIELD(data_ov031_02290d20, s32 *, 0xAA4), data_ov031_02290d20 + 0xA50, 0x40);
    M2C_FIELD(data_ov031_02290d20, s8 *, 0xA93) = 0;
    M2C_FIELD(data_ov031_02290d20, s32 *, 0x204) = 0;
    M2C_FIELD(data_ov031_02290d20, u16 *, 0x648) = (u16) (M2C_FIELD(data_ov031_02290d20, u16 *, 0x648) + 1);
}
