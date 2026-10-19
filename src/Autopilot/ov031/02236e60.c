#include <m2c.h>

s32 func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290d04;
extern M2C_UNK ov13_0223B2C8;

void ov13_0223B1A0(void) {
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d04, void **, 4), s8 *, 0x18) = 1;
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d04, void **, 4), s32 *, 0x14) = func_ov031_0223e218(0, &ov13_0223B2C8, 0, 0x78);
}
