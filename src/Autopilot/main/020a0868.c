#include <m2c.h>


void func_020a0858(void *arg0, s32 arg1) {
    u32 temp_r2;
    u32 var_r1;

    temp_r2 = M2C_FIELD(arg0, u32 *, 0x48);
    var_r1 = arg1 + temp_r2;
    if (var_r1 < temp_r2) {
        var_r1 = -1U;
    }
    M2C_FIELD(arg0, u32 *, 0x48) = var_r1;
}
