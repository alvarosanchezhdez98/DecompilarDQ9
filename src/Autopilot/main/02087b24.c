#include <m2c.h>


void func_02087b14(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x2000);
    M2C_FIELD(arg0, s32 *, 0x58) = (s32) (M2C_FIELD(arg0, s32 *, 0x58) & ~0xE00);
    M2C_FIELD(arg0, s8 *, 0x71) = 0;
    M2C_FIELD(arg0, s8 *, 0x94) = 0;
}
