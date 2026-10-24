#include <m2c.h>

M2C_UNK _ZN8Object3D17SetInheritedAlphaEi(s32, u8);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState21GetPartyMemberByIndexEi(s32, u8);
M2C_UNK func_02039d48(s32);

void func_ov017_021d2c78(s32 arg0, void *arg1) {
    s32 temp_r0;

    temp_r0 = _ZN9GameState21GetPartyMemberByIndexEi(_ZN9GameState11GetInstanceEv(), M2C_FIELD(arg1, u8 *, 4));
    if (temp_r0 == 0) {
        return;
    }
    _ZN8Object3D17SetInheritedAlphaEi(temp_r0, M2C_FIELD(arg1, u8 *, 5));
    if (M2C_FIELD(arg1, u8 *, 5) != 0) {
        return;
    }
    if (M2C_FIELD(arg1, u8 *, 6) == 0) {
        return;
    }
    func_02039d48(temp_r0);
}
