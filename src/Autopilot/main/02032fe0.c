#include <m2c.h>


void func_02032fd0(void *arg0, s16 arg1, s16 arg2) {
    M2C_FIELD(arg0, s16 *, 0xBA) = arg1;
    M2C_FIELD(arg0, s16 *, 0xBC) = arg2;
}
