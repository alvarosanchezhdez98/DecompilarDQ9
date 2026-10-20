#include <m2c.h>

M2C_UNK VectorizedInvertedMemcpy(s32, s32 *, M2C_UNK);
M2C_UNK VectorizedMemset(s32 *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_0224e5e8;

void ov00_021E7EA8(s32 *arg0) {
    s32 temp_r1;
    s32 temp_r1_2;

    if (M2C_FIELD(&data_ov031_0224e5e8, s32 *, 8) == 0) {
        VectorizedMemset(arg0, 0, 0x1C4);
    }
    VectorizedInvertedMemcpy(M2C_FIELD(&data_ov031_0224e5e8, s32 *, 8) + 0x1008, arg0, 0x1C4);
    temp_r1 = *arg0;
    if ((temp_r1 < 0x4E20) || (temp_r1 >= 0x7530)) {
        *arg0 = 0x5206;
    }
    temp_r1_2 = *arg0;
    if (temp_r1_2 >= 0x4E84) {
        *arg0 = 0 - temp_r1_2;
    }
}
