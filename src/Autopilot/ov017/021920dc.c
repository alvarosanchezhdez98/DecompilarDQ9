#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, s32);
s32 func_0200ff1c(s32, s32);
void *func_02053c6c();

s32 func_ov017_021920dc(s32 arg0, s32 arg1) {
    s32 temp_r5;
    s32 var_r0;
    s32 var_r6;
    s32 var_r7;
    void *temp_r0;
    void *temp_r4;

    temp_r5 = _ZN9GameState11GetInstanceEv();
    var_r6 = 0;
    var_r7 = -1;
    if ((arg1 >= 0) && (arg1 <= 3)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        var_r7 = arg1;
    } else if ((arg1 >= 0x13) && (arg1 <= 0x67)) {
        var_r7 = (s32) (arg1 - 0x13) / 12;
    }
    if ((var_r7 >= 0) && (func_0200ff1c(temp_r5, var_r7) != 0)) {
        temp_r4 = func_02053c6c();
        temp_r0 = _ZN9GameState19GetCombatantByIndexEi(temp_r5, var_r7);
        if ((temp_r4 != NULL) && (M2C_FIELD(temp_r4, u8 *, 0x56C) != 0)) {
            goto block_16;
        }
        if ((temp_r0 != NULL) && (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), s32 *, 0x14) & 0x08000000)) {
block_16:
            var_r6 = 1;
        }
    }
    return var_r6;
}
