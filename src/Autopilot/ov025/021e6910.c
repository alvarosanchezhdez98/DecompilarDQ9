#include <m2c.h>

M2C_UNK _ZN8Object3D10MakeHiddenEv();
M2C_UNK _ZN8Object3D11MakeVisibleEv();
M2C_UNK _ZN8Object3D24MaybeSetRegularAnimationEPKci(s32, M2C_UNK *, M2C_UNK);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
extern M2C_UNK data_ov025_021ef82b;

s32 func_ov025_021e6910(s32 arg0, void *arg1) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    temp_r0_2 = _ZN9GameState20GetGameObjectByIndexEi(temp_r0, 0xC8);
    if (temp_r0_2 == 0) {
        return 1;
    }
    _ZN8Object3D11MakeVisibleEv();
    _ZN8Object3D24MaybeSetRegularAnimationEPKci(temp_r0_2, &data_ov025_021ef82b, 1);
    if (_ZN9GameState20GetGameObjectByIndexEi(temp_r0, (M2C_FIELD(M2C_FIELD(arg1, void **, 0x10), u16 *, 0x20) * 0xC) + 0x1C) != 0) {
        _ZN8Object3D10MakeHiddenEv();
    }
    return 1;
}
