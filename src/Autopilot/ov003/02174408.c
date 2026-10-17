#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov003_02174408(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 0x63;
    M2C_FIELD(arg0, s8 *, 1) = 0;
    memset(arg0 + 2, 0, 0x12);
    memset(arg0 + 0x14, -1, 0x24);
    M2C_FIELD(arg0, s16 *, 0x38) = 0x64;
    M2C_FIELD(arg0, s16 *, 0x3A) = 0;
    M2C_FIELD(arg0, s8 *, 0x3C) = 0;
}
