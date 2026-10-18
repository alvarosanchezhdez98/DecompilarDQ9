#include <m2c.h>


void func_020888a4(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x60) = 6;
    M2C_FIELD(arg0, s8 *, 0x83) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 0x100);
}
