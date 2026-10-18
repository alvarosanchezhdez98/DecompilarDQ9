#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0209af34(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x1C8) = -1;
    M2C_FIELD(arg0, s32 *, 0x1CC) = 0;
    M2C_FIELD(arg0, s32 *, 0x1D0) = 0;
    memset(arg0, 0, 0x1C8);
}
