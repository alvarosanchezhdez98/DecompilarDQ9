#include <m2c.h>

extern M2C_UNK data_ov016_0219d144;

void func_ov016_0218d294(void) {
    M2C_FIELD(&data_ov016_0219d144, s32 *, 0) = 1;
    if (M2C_FIELD(&data_ov016_0219d144, s32 *, 0x14) == 0) {
        M2C_FIELD(&data_ov016_0219d144, s32 *, 0x18) = (s32) (M2C_FIELD(&data_ov016_0219d144, s32 *, 0x18) + 1);
    }
}
