#include <m2c.h>


void func_020556cc(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0x30) = arg1;
    M2C_FIELD(arg0, s32 *, 0x2C) = arg2;
    M2C_FIELD(arg0, s32 *, 0x28) = arg3;
}
