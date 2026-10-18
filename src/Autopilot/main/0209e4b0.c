#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0209e4a0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
    memset(arg0 + 0x9C, 0, 0x400);
}
