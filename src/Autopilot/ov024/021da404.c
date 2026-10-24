#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, u32);
void *func_02053c6c();

u32 func_ov024_021da404(s32 arg0, u32 arg1, s32 arg2, s32 arg3, s32 arg4, u32 arg5) {
    s32 var_r0;
    u32 var_r4;
    void *temp_r0;

    if (arg1 <= 3U) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    var_r4 = arg5;
    if (var_r0 == 0) {
        return var_r4;
    }
    if (func_0200ff1c(_ZN9GameState11GetInstanceEv(), arg1) == 0) {
        return var_r4;
    }
    temp_r0 = func_02053c6c();
    if (temp_r0 != NULL) {
        var_r4 = (s32) (0.25f * (f32) ((u32) (M2C_FIELD(temp_r0, s32 *, 4) << 0x16) >> 0x16)) + ((s32) (var_r4 + (var_r4 >> 0x1F)) >> 1);
    }
    return var_r4;
}
