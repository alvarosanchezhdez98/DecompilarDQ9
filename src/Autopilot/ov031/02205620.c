#include <m2c.h>

s32 SOCLi_RoundUp4(s32);

s32 SOCLi_InitSocketBuffer(s32 arg0, void *arg1, s32 arg2) {
    s32 temp_r4;
    s32 var_r0;

    var_r0 = arg0;
    temp_r4 = var_r0;
    if (arg2 == 0) {
        var_r0 = 0;
    }
    M2C_FIELD(arg1, s32 *, 4) = var_r0;
    M2C_FIELD(arg1, s32 *, 0) = arg2;
    return temp_r4 + SOCLi_RoundUp4(arg2);
}
