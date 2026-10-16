#include <m2c.h>

extern M2C_UNK data_ov016_0219d0c0;

void func_ov016_0218c024(void) {
    M2C_FIELD(&data_ov016_0219d0c0, s32 *, 4) = 1;
    if (M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x38) == 0) {
        M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x3C) = (s32) (M2C_FIELD(&data_ov016_0219d0c0, s32 *, 0x3C) + 1);
    }
}
