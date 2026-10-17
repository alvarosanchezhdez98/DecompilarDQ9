#include <m2c.h>

M2C_UNK ov13_02242478(M2C_UNK);
extern M2C_UNK data_027e0000;

void ov13_02241B70(void) {
    ov13_02242478(1);
    M2C_FIELD(&data_027e0000, s32 *, 0x3FF8) = (s32) (M2C_FIELD(&data_027e0000, s32 *, 0x3FF8) | 1);
}
