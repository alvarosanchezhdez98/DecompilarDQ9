#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov025_021dcd5c(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x6E4D) = 0;
    M2C_FIELD(arg0, s8 *, 0x6E4C) = 0;
    memset(arg0 + 0x6EF0, -1, 0xA);
    M2C_FIELD(arg0, s16 *, 0x6EFA) = 0;
}
