#include <m2c.h>

s32 func_020d5204(M2C_UNK *);
M2C_UNK ov13_0223D724();
extern M2C_UNK data_ov031_02290d18;
extern M2C_UNK ov13_0223D8F4;

s32 ov13_0223D890(void) {
    if ((u32) (M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x40) - 4) <= 2U) {
        return 1;
    }
    if (func_020d5204(&ov13_0223D8F4) != 2) {
        ov13_0223D724();
        return 0;
    }
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s16 *, 0x50) = 0;
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s16 *, 0x52) = 1;
    return 1;
}
