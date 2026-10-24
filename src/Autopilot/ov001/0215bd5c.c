#include <m2c.h>

M2C_UNK _ZN8Object3D10MakeHiddenEv();
M2C_UNK _ZN8Object3D11MakeVisibleEv();
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
s32 func_ov017_021d60f4(s32);

s32 func_ov001_0215bd5c(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 var_r5;
    s32 temp_r6;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (temp_r0 == 0) {
        return 0;
    }
    var_r5 = 1;
    temp_r6 = func_ov017_021d60f4(arg0);
    if (arg1 >= 2) {
        var_r5 = func_ov017_021d60f4(arg0 + 8);
    }
    if (_ZN9GameState20GetGameObjectByIndexEi(temp_r0, temp_r6) == 0) {
        return 0;
    }
    if (var_r5 != 0) {
        _ZN8Object3D11MakeVisibleEv();
    } else {
        _ZN8Object3D10MakeHiddenEv();
    }
    return 1;
}
