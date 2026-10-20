#include <m2c.h>


void func_02087838(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x400);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~7);
    M2C_FIELD(arg0, s8 *, 0x6E) = 0;
    M2C_FIELD(arg0, s8 *, 0x91) = 0;
}
