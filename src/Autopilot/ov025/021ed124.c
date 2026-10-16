#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov025_021ed124(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0x15E) = 0;
    M2C_FIELD(arg0, s16 *, 0x1AE) = 0;
    M2C_FIELD(arg0, s16 *, 0x160) = 0;
    M2C_FIELD(arg0, s32 *, 0x158) = 0;
    M2C_FIELD(arg0, s8 *, 0x150) = 0;
    M2C_FIELD(arg0, s8 *, 0x151) = 0;
    memset(arg0, 0, 0x20);
    memset(arg0 + 0x20, 0, 0x20);
    memset(arg0 + 0x60, 0, 0x20);
    memset(arg0 + 0xA0, 0, 0x10);
    memset(arg0 + 0xB0, 0, 0x40);
    memset(arg0 + 0x40, 0, 0x20);
    memset(arg0 + 0xF0, 0, 0x40);
    memset(arg0 + 0x130, 0, 0x10);
    M2C_FIELD(arg0, s16 *, 0x152) = 0;
    M2C_FIELD(arg0, s16 *, 0x154) = 0;
    M2C_FIELD(arg0, s8 *, 0x16C) = 0;
    M2C_FIELD(arg0, s16 *, 0x1AC) = 0;
    M2C_FIELD(arg0, s16 *, 0x162) = 0x2EE;
    M2C_FIELD(arg0, s16 *, 0x15C) = 0;
}
