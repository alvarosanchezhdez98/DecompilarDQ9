#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s16 _ZN9GameState19GetCombatantByIndexEi(s32, s16);
s32 func_02010088();
s32 func_ov000_02153c0c(s16);

void func_ov000_02153cc0(s32 arg0, s32 arg1, s32 *arg2) {
    s16 var_r4;
    s32 *var_r5;
    s32 var_r6;

    var_r5 = arg2;
    var_r6 = arg1;
    var_r4 = (s16) *var_r5;
    var_r4 = _ZN9GameState19GetCombatantByIndexEi(_ZN9GameState11GetInstanceEv(), var_r4);
    if ((var_r4 != 0) && (func_02010088() == 0) && (func_ov000_02153c0c(var_r4) == 0)) {
        return;
    }
    *var_r5 = var_r6;
}
