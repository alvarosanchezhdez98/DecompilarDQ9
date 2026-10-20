#include <m2c.h>

extern M2C_UNK data_021015a0;

s32 func_0202d0b4(void) {
    if (M2C_FIELD(&data_021015a0, s32 *, 0x10) != 2) {
        return 0;
    }
    M2C_FIELD(&data_021015a0, s16 *, 4) = 0;
    M2C_FIELD(&data_021015a0, s32 *, 0x10) = 3;
    return 1;
}
