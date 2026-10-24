#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(s32, void *);
void *_ZN9GameState19GetCombatantByIndexEi(M2C_UNK, s16);
s32 func_ov017_021b8468(s32);
s32 func_ov017_021b8470(s32);
void *func_ov017_021b8478(s32);

void func_ov017_021c88cc(s32 arg0, void *arg1, M2C_UNK arg2, void *arg3) {
    s32 temp_r0_3;
    s32 temp_r5;
    void *temp_r0;
    void *temp_r0_2;

    temp_r5 = M2C_FIELD(arg3, s32 *, 0x3718);
    temp_r0 = func_ov017_021b8478(temp_r5);
    if (temp_r0 == NULL) {
        return;
    }
    if (func_ov017_021b8468(temp_r5) == 0) {
        return;
    }
    if (func_ov017_021b8470(temp_r5) == 0) {
        return;
    }
    if (M2C_FIELD(temp_r0, u16 *, 8) != M2C_FIELD(arg1, u16 *, 0x12)) {
        return;
    }
    temp_r0_2 = _ZN9GameState19GetCombatantByIndexEi(arg2, M2C_FIELD(arg1, s16 *, 0x10));
    if (temp_r0_2 != NULL) {
        temp_r0_3 = M2C_FIELD(temp_r0_2, s32 *, 0x13C);
        if (temp_r0_3 != 0) {
            _ZN8Vector3iaSERKS_(temp_r0_3 + 0x10, arg1 + 4);
        }
    }
}
