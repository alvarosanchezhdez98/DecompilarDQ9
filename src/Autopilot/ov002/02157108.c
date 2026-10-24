#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c();
s32 func_02010828();
M2C_UNK func_02053c6c();
s32 func_02083960();
s32 func_020a0b8c();

s32 func_ov002_02157108(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r4;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    var_r4 = 0;
    if (arg1 == 5) {
        var_r4 = func_020a0b8c(func_02010828() + 0xE04);
    } else if (arg1 == 4) {
        func_02010828();
        var_r4 = func_020a0b8c();
    } else if (func_0200ff1c(temp_r0, arg1) != 0) {
        func_02053c6c();
        var_r4 = func_02083960();
    }
    return var_r4;
}
