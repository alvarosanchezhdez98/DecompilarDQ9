#include <m2c.h>

s32 func_02053c6c();
s32 func_02083b00(s32, s32);

u32 func_020dd290(s32 arg0, u32 arg1) {
    s32 temp_r0;
    u32 var_r4;

    var_r4 = arg1;
    if (arg0 == 0) {
        return 0U;
    }
    if (var_r4 == 0) {
        return 0U;
    }
    temp_r0 = func_02053c6c();
    if ((temp_r0 != 0) && (func_02083b00(temp_r0, 0x106) != 0)) {
        var_r4 = (u32) (0.75f + (0.75f * (f32) var_r4));
    }
    return var_r4;
}
