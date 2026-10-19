#include <m2c.h>


void func_020e2d2c(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
    M2C_FIELD(arg0, s32 *, 0x18) = arg2;
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (arg1 + arg3);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (arg2 + arg4);
}
