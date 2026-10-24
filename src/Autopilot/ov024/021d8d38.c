#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, M2C_UNK);
s32 func_02088514(void *);
s32 func_020885b4(void *);

s32 func_ov024_021d8d38(s32 arg0, s32 arg1, M2C_UNK arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *temp_r0;

    temp_r0 = _ZN9GameState19GetCombatantByIndexEi(_ZN9GameState11GetInstanceEv(), arg2);
    if (temp_r0 == NULL) {
        return arg5;
    }
    if ((func_020885b4(M2C_FIELD(temp_r0, void **, 0x138)) != 0) || (func_02088514(M2C_FIELD(temp_r0, void **, 0x138)) != 0) || (M2C_FIELD(M2C_FIELD(temp_r0, void **, 0x138), s32 *, 0x14) & 8)) {
        return (s32) (1.5f * (f32) arg5);
    }
    return arg5;
}
