#include <m2c.h>


void func_020de1d4(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0x14) = 0;
    M2C_FIELD(arg0, s16 *, 0x16) = 0;
    M2C_FIELD(arg0, s16 *, 0x18) = -1;
    M2C_FIELD(arg0, s16 *, 0x1A) = 0;
    M2C_FIELD(arg0, s16 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) ((((M2C_FIELD(arg0, s32 *, 0x10) & ~0x3FF) | 0x3E7) & 0xFFF003FF) | 0xF9C00);
}
