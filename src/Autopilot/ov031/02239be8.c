#include <m2c.h>

extern M2C_UNK data_ov031_02290d18;

s32 ov13_0223DF28(void) {
    return M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x40);
}
