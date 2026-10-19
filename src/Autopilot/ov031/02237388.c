#include <m2c.h>

extern M2C_UNK data_ov031_02290d04;

s32 ov13_0223B6C8(void) {
    if (M2C_FIELD(&data_ov031_02290d04, void **, 4) == NULL) {
        return 1;
    }
    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290d04, void **, 4), u8 *, 0x18) == 0) {
        return 1;
    }
    return 0;
}
