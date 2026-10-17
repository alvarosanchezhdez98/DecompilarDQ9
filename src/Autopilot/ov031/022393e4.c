#include <m2c.h>

extern M2C_UNK data_ov031_02290d18;

void ov13_0223D724(s32 arg0) {
    if ((u32) (M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x40) - 9) > 1U) {
        M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x54) = arg0;
    }
}
