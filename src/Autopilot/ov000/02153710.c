#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, s32);
s32 func_02053c6c();

s32 func_ov000_02153710(s32 arg0, s32 arg1) {
    s32 var_r0;

    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 == 0) {
        return 0;
    }
    if (func_0200ff1c(_ZN9GameState11GetInstanceEv(), arg1) == 0) {
        return 0;
    }
    return func_02053c6c();
}
