#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, M2C_UNK);

s32 func_ov024_021d923c(void **arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_r0;
    void *temp_r4;
    void *temp_r5;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    temp_r5 = _ZN9GameState19GetCombatantByIndexEi(temp_r0, arg1);
    temp_r4 = _ZN9GameState19GetCombatantByIndexEi(temp_r0, arg2);
    if ((temp_r5 != NULL) && (temp_r4 != NULL)) {
        M2C_FIELD(*arg0, s32 *, 0x8E38) = (s32) ((s32) (0.8f * (f32) *M2C_FIELD(temp_r5, u16 **, 0x138)) + 2);
        return (s32) (0.8f * (f32) *M2C_FIELD(temp_r4, u16 **, 0x138));
    }
    return arg5;
}
