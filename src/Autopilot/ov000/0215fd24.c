#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff58();
s32 func_020100a8();
s32 func_020546a8();

s32 func_ov000_0215fd24(s32 arg0, s32 arg1) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    if (arg1 == func_020100a8()) {
        return 1;
    }
    if (func_0200ff58(temp_r5, arg1) != 0) {
        temp_r4 = func_020546a8();
        if (temp_r4 == func_020100a8(temp_r5)) {
            return 1;
        }
    }
    return 0;
}
