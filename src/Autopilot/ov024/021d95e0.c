#include <m2c.h>

s32 _Z13NextRandomMaxP6Randomi(void *, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
void *_ZN9GameState19GetCombatantByIndexEi(s32, M2C_UNK);

s32 func_ov024_021d95e0(void **arg0, s32 arg1, M2C_UNK arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *temp_r0;

    temp_r0 = _ZN9GameState19GetCombatantByIndexEi(_ZN9GameState11GetInstanceEv(), arg2);
    if (temp_r0 == NULL) {
        return arg5;
    }
    if (_Z13NextRandomMaxP6Randomi(*arg0, 2) > 0) {
        M2C_FIELD(*arg0, s8 *, 0x8E94) = 1;
        return 0xFFFF;
    }
    return (s32) (0.99f * (f32) *M2C_FIELD(temp_r0, u16 **, 0x138));
}
