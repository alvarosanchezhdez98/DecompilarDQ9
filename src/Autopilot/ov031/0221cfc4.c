#include <m2c.h>


#pragma thumb on
u32 func_ov031_0221cfc4(s32 arg0, s32 arg1) {
    s32 temp_r1;
    s32 temp_r2;
    u32 var_r0;

    temp_r2 = arg0 & arg1;
    temp_r1 = ~arg1;
    var_r0 = ((arg0 & temp_r1) + 1) | temp_r2;
    if (var_r0 >= (u32) (temp_r1 | temp_r2)) {
        var_r0 = 1 | temp_r2;
    }
    return var_r0;
}
#pragma thumb off
