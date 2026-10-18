#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_020d784c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    memset(arg0 + 4, -1, 0x10);
}
