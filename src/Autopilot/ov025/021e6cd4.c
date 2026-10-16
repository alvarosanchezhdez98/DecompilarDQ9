#include <m2c.h>

extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e6cd4(void *arg0) {
    M2C_FIELD((M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC) + 0x540), s16 *, 0x24) = (s16) M2C_FIELD(arg0, s32 *, 8);
    return 1;
}
