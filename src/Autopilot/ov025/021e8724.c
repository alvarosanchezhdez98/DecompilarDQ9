#include <m2c.h>

extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e8724(void *arg0) {
    M2C_FIELD(M2C_FIELD(&data_ov025_021ef988, void **, 0xC), u8 *, 0x5D0) = (u8) M2C_FIELD(arg0, u8 *, 8);
    return 1;
}
