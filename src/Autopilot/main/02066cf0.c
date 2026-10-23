#include <m2c.h>


void func_02066ce0(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = arg2;
    M2C_FIELD(arg0, s16 *, 0x14) = arg3;
}
