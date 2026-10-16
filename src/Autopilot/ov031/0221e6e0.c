#include <m2c.h>


#pragma thumb on
void func_ov031_0221e6e0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = arg0;
    M2C_FIELD(arg1, s16 *, 4) = 1;
}
#pragma thumb off
