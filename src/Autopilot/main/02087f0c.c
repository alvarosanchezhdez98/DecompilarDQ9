#include <m2c.h>


void func_02087efc(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x20000);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0xE00000);
    M2C_FIELD(arg0, s8 *, 0x75) = 0;
    M2C_FIELD(arg0, s8 *, 0x98) = 0;
}
