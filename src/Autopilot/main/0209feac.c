#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0209fe9c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = -1;
    M2C_FIELD(arg0, s32 *, 0x64) = -1;
    M2C_FIELD(arg0, s16 *, 0x68) = 0;
    memset(arg0 + 0xC, 0, 0x54);
    memset(arg0 + 0x6A, 0, 0x64);
}
