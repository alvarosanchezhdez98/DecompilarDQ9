#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, M2C_UNK);

s16 func_ov000_0215a124(s32 arg0, M2C_UNK arg1, s32 arg2) {
    s32 var_r1;
    void *temp_r0;
    void *temp_r2;

    temp_r0 = _ZN9GameState19GetCombatantByIndexEi(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 == NULL) {
        return 0;
    }
    temp_r2 = M2C_FIELD(temp_r0, void **, 0x138);
    var_r1 = M2C_FIELD(temp_r2, u16 *, 2) - arg2;
    if (var_r1 <= 0) {
        var_r1 = 0;
    }
    M2C_FIELD(temp_r2, u16 *, 2) = (u16) var_r1;
    return (s16) var_r1;
}
