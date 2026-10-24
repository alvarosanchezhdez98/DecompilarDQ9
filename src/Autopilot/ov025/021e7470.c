#include <m2c.h>

M2C_UNK _ZN8Object3D11MakeVisibleEv();
M2C_UNK _ZN8Object3D6DetachEv();
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
M2C_UNK func_0200fd48(s32, M2C_UNK);

s32 func_ov025_021e7470(s32 arg0, void *arg1) {
    s32 temp_r0;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (_ZN9GameState20GetGameObjectByIndexEi(temp_r0, 0xC8) != 0) {
        _ZN8Object3D6DetachEv();
        func_0200fd48(temp_r0, 0xC8);
    }
    if (_ZN9GameState20GetGameObjectByIndexEi(temp_r0, (M2C_FIELD(M2C_FIELD(arg1, void **, 0x10), u16 *, 0x20) * 0xC) + 0x1C) != 0) {
        _ZN8Object3D11MakeVisibleEv();
    }
    return 1;
}
