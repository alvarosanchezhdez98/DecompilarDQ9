#include <m2c.h>


void func_020e1374(void *arg0, s32 arg1, s32 arg2, s8 arg3) {
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = arg2;
    M2C_FIELD(arg0, s8 *, 0x14) = arg3;
}
