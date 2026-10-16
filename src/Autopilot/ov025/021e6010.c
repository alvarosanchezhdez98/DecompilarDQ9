#include <m2c.h>

extern M2C_UNK data_ov025_021ef988;

s32 func_ov025_021e6010(void *arg0) {
    M2C_FIELD(M2C_FIELD(&data_ov025_021ef988, void **, 0xC), u16 *, 0x21C) = (u16) M2C_FIELD(arg0, u16 *, 8);
    return 1;
}
