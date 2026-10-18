#include <m2c.h>


void func_020889e4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x63) = 4;
    M2C_FIELD(arg0, s8 *, 0x86) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x10000000);
}
