#include <m2c.h>


void func_020883cc(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x21) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(arg0, s32 *, 0x18) & ~0x20);
    M2C_FIELD(arg0, s8 *, 0x5E) = 3;
    M2C_FIELD(arg0, s8 *, 0x81) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x20);
}
