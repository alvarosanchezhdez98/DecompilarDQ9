#include <m2c.h>


void func_ov017_021a55a4(void *arg0, s8 arg1, s8 arg2) {
    M2C_FIELD(arg0, s8 *, 0x20) = arg1;
    M2C_FIELD(arg0, s8 *, 0x21) = arg2;
}
