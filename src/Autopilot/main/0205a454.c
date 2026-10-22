#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0205a444(void *arg0) {
    memset(arg0, 0, 0x24);
    memset(arg0 + 0x24, 0, 0x14);
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s16 *, 0x4C) = 0;
    M2C_FIELD(arg0, s16 *, 0x4E) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s8 *, 0x50) = 1;
}
