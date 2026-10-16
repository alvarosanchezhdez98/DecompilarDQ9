#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov025_021df9b0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x158) = 0;
    M2C_FIELD(arg0, s32 *, 0x15C) = 0;
    M2C_FIELD(arg0, s32 *, 0x160) = 0;
    M2C_FIELD(arg0, s32 *, 0x164) = 0;
    M2C_FIELD(arg0, s32 *, 0x168) = 0;
    M2C_FIELD(arg0, s32 *, 0x16C) = 0;
    M2C_FIELD(arg0, s8 *, 0x18A) = 0;
    M2C_FIELD(arg0, s8 *, 0x18B) = 0;
    M2C_FIELD(arg0, s32 *, 0x170) = 1;
    memset(arg0 + 0x176, 0, 0x14);
}
