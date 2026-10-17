#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_0201079c();
M2C_UNK func_ov017_021d6134(M2C_UNK, M2C_UNK);

s32 func_ov001_02162d3c(M2C_UNK arg0) {
    M2C_UNK var_r1;

    _ZN9GameState11GetInstanceEv();
    if (func_0201079c() >= 0x13) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    func_ov017_021d6134(arg0, var_r1);
    return 1;
}
