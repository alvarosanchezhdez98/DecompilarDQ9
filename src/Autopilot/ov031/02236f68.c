#include <m2c.h>

extern M2C_UNK data_ov031_02290d04;

s32 ov13_0223B2A8(void) {
    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290d04, void **, 4), s32 *, 0x14) != 0) {
        return 1;
    }
    return 0;
}
