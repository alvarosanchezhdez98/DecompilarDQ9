#include <m2c.h>
#pragma optimization_level 4


void func_0204f160(void *arg0, s32 arg1, s8 arg2) {
    if (!(M2C_FIELD(arg0, u8 *, 0xC5) & 1)) {
        M2C_FIELD(arg0, s32 *, 0xA0) = arg1;
        M2C_FIELD(arg0, s8 *, 0xC4) = arg2;
    }
}
