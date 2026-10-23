#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, s16);
s32 func_02053c6c();
s32 func_02083b00(s32, s32);

s32 func_02048448(void *arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r4;

    var_r4 = arg1;
    if (func_0200ff1c(_ZN9GameState11GetInstanceEv(), M2C_FIELD(arg0, s16 *, 4)) != 0) {
        temp_r0 = func_02053c6c();
        if ((temp_r0 != 0) && (func_02083b00(temp_r0, 0x106) != 0)) {
            var_r4 = (s32) (0.75f + (0.75f * (f32) var_r4));
            if (var_r4 <= 0) {
                var_r4 = 0;
            }
        }
    }
    if (var_r4 <= (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 6)) {
        return 1;
    }
    return 0;
}
