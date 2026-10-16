#include <m2c.h>


void func_ov024_021f6820(void *arg0, s16 arg1, s8 arg2, s8 arg3) {
    M2C_FIELD(arg0, s16 *, 0) = arg1;
    M2C_FIELD(arg0, s8 *, 2) = arg2;
    M2C_FIELD(arg0, s8 *, 3) = arg3;
}
