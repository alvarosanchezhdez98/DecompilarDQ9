#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, M2C_UNK);
s32 func_ov017_021920dc(M2C_UNK, M2C_UNK);
u8 *func_ov017_0219219c(M2C_UNK, M2C_UNK);

s32 func_ov017_02191fec(M2C_UNK arg0, M2C_UNK arg1) {
    s32 var_r6;
    u8 *temp_r0_2;
    u8 *temp_r0_3;
    u8 *temp_r0_4;
    u8 *temp_r0_5;
    void *temp_r0;

    var_r6 = 1;
    temp_r0 = _ZN9GameState19GetCombatantByIndexEi(_ZN9GameState11GetInstanceEv(), arg1);
    if ((temp_r0 != NULL) && (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), s32 *, 0x14) & 0x01000000)) {
        if (func_ov017_0219219c(arg0, arg1) != NULL) {
            temp_r0_2 = func_ov017_0219219c(arg0, arg1);
            if (temp_r0_2 != NULL) {
                *temp_r0_2 |= 1;
            }
            temp_r0_3 = func_ov017_0219219c(arg0, arg1);
            if (temp_r0_3 != NULL) {
                *temp_r0_3 |= 4;
            }
        }
        var_r6 = 0;
    }
    if (func_ov017_021920dc(arg0, arg1) != 0) {
        if (func_ov017_0219219c(arg0, arg1) != NULL) {
            temp_r0_4 = func_ov017_0219219c(arg0, arg1);
            if (temp_r0_4 != NULL) {
                *temp_r0_4 |= 1;
            }
            temp_r0_5 = func_ov017_0219219c(arg0, arg1);
            if (temp_r0_5 != NULL) {
                *temp_r0_5 |= 2;
            }
        }
        var_r6 = 0;
    }
    return var_r6;
}
