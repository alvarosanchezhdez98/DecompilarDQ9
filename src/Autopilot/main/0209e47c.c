#include <m2c.h>

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_0209e46c(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x6C) = -1;
    memset(arg0 + 0x70, 0, 0x10);
    M2C_FIELD(arg0, s32 *, 0x90) = -1;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
}
