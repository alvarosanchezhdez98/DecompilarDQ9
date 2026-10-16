#include <m2c.h>


void func_ov017_021b2bd0(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x30) = arg1;
    M2C_FIELD(arg0, s32 *, 0x34) = arg2;
}
