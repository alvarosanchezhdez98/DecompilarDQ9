#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 func_0200ff1c(s32, s8);
s8 func_020100b0(s32);
void *func_ov017_0218b5b0();
M2C_UNK func_ov017_021d6134(M2C_UNK, s8);

s32 func_ov001_02161930(M2C_UNK arg0) {
    s32 temp_r4;
    s8 var_r5;

    temp_r4 = _ZN9GameState11GetInstanceEv();
    var_r5 = M2C_FIELD(M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3734), s8 *, 0x116);
    if (func_0200ff1c(temp_r4, var_r5) == 0) {
        var_r5 = func_020100b0(temp_r4);
    }
    func_ov017_021d6134(arg0, var_r5);
    return 1;
}
