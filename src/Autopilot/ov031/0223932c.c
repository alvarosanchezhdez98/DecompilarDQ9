#include <m2c.h>

extern M2C_UNK data_ov031_02290d18;

void ov13_0223D66C(void *arg0) {
    M2C_FIELD(&data_ov031_02290d18, void **, 4) = arg0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x13A8) = 0;
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x13AC) = 0;
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x13B0) = 0;
}
