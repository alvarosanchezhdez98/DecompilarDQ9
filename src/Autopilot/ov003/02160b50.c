#include <m2c.h>

M2C_UNK _ZN9GameState11GetInstanceEv();
s32 func_020100a8();
M2C_UNK func_0202ae18();
s32 func_0202ba00();

s32 func_ov003_02160b50(void) {
    s32 var_r4;

    var_r4 = 0;
    func_0202ae18();
    if (func_0202ba00() != 0) {
        _ZN9GameState11GetInstanceEv();
        if (func_020100a8() == 0) {
            var_r4 = 1;
        } else {
            var_r4 = 2;
        }
    }
    return var_r4;
}
