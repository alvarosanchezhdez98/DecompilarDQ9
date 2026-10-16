#include <m2c.h>


void func_ov000_0216341c(void *arg0, s8 arg1, s8 arg2, s16 arg3) {
    M2C_FIELD(arg0, s32 *, 0x6E24) = 1;
    M2C_FIELD(arg0, s8 *, 0x6E2A) = arg1;
    M2C_FIELD(arg0, s8 *, 0x6E2B) = arg2;
    M2C_FIELD(arg0, s16 *, 0x6E2C) = arg3;
}
