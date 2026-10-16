#include <m2c.h>


void func_ov025_021e8a40(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
    M2C_FIELD(arg0, s32 *, 0x20) = arg2;
}
