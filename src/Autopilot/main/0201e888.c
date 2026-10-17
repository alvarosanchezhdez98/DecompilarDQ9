#include <m2c.h>


void func_0201e878(void *arg0, s32 arg1, s16 arg2) {
    M2C_FIELD(arg0, s32 *, 0x84) = arg1;
    M2C_FIELD(arg0, s16 *, 0x82) = arg2;
    M2C_FIELD(arg0, s16 *, 0x80) = 0;
}
