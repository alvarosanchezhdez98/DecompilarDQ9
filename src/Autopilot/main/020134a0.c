#include <m2c.h>

M2C_UNK Mat3x3_WriteIdentity(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_02013490(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s16 *, 4) = 0;
    memset(arg0 + 6, 0, 9);
    memset(arg0 + 0xF, 0, 5);
    Mat3x3_WriteIdentity(arg0 + 0x14);
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
}
