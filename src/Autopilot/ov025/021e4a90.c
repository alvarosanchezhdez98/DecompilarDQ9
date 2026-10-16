#include <m2c.h>

extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e4a90(void) {
    M2C_FIELD(&data_ov025_021ef988, s32 *, 0x1C) = (s32) (M2C_FIELD(&data_ov025_021ef988, s32 *, 0x1C) | 0x100);
    return 1;
}
