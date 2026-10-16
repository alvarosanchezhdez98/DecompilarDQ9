#include <m2c.h>

extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e6374(void *arg0) {
    M2C_FIELD((M2C_FIELD(&data_ov025_021ef988, s32 *, 0xC) + 0x540), u16 *, 0x1C) = (u16) M2C_FIELD(arg0, u16 *, 8);
    return 1;
}
