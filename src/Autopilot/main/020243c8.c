#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK8Object3D17GetInheritedAlphaEv();
s32 _ZNK8Object3D19GetAlphaScaleFactorEv(s32);
s32 _ZNK8Object3D9IsVisibleEv(s32);
s32 func_0200ff1c(s32, s32);

s32 func_020243b8(s32 arg0, s32 arg1) {
    s32 temp_r0;

    if (arg1 < 0) {
        return 1;
    }
    temp_r0 = func_0200ff1c(_ZN9GameState11GetInstanceEv(), arg1);
    if (temp_r0 == 0) {
        return 1;
    }
    if (_ZNK8Object3D17GetInheritedAlphaEv() == 0) {
        return 0;
    }
    if (_ZNK8Object3D19GetAlphaScaleFactorEv(temp_r0) == 0) {
        return 0;
    }
    if (_ZNK8Object3D9IsVisibleEv(temp_r0) != 0) {
        return 1;
    }
    return 0;
}
