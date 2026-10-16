#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov025_021dcd98(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x6F00) = 0;
    M2C_FIELD(arg0, s8 *, 0x6EFF) = 0;
    memset(arg0 + 0x6FBA, -1, 8);
    M2C_FIELD(arg0, s16 *, 0x6FC2) = 0;
    M2C_FIELD(arg0, s32 *, 0x6FC4) = 0;
    M2C_FIELD(arg0, s32 *, 0x6FC8) = 0;
    M2C_FIELD(arg0, s32 *, 0x6FCC) = 0;
    M2C_FIELD(arg0, s32 *, 0x6FD0) = 0;
}
