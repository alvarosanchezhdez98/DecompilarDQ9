#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
M2C_UNK _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN8Object3D10InitializeEv();
M2C_UNK _ZN8Object3D14ShallowCloneToEPS_(s32, s32);
M2C_UNK _ZN8Object3D21MaybeSetBCFGAnimationEii(s32, M2C_UNK, M2C_UNK);
M2C_UNK _ZN8Object3D8SetScaleEiii(s32, s32, s32, s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
M2C_UNK func_0200fd38(s32, s32, s32);
s32 func_ov017_021d60f4(s32);
s32 func_ov001_0215ad2c();
extern s32 data_ov001_021658b8[8];

s32 func_ov001_0215ba64(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r6;
    s32 temp_r7;
    s32 var_r0;

    temp_r6 = _ZN9GameState11GetInstanceEv();
    _ZN16BackgroundLoader11GetInstanceEv();
    func_ov017_021d60f4(arg0);
    temp_r4 = func_ov001_0215ad2c();
    func_ov017_021d60f4(arg0 + 8);
    temp_r7 = func_ov001_0215ad2c();
    var_r0 = 0;
    if (arg1 >= 3) {
        var_r0 = func_ov017_021d60f4(arg0 + 0x10);
    }
    temp_r4_2 = data_ov001_021658b8[var_r0];
    temp_r0 = _ZN9GameState20GetGameObjectByIndexEi(temp_r6, temp_r4);
    if (temp_r0 == 0) {
        return 0;
    }
    temp_r0_2 = _ZN13SafeAllocator8AllocateEj(temp_r4_2, 0xAC);
    if (temp_r0_2 == 0) {
        return 0;
    }
    _ZN8Object3D10InitializeEv();
    _ZN8Object3D14ShallowCloneToEPS_(temp_r0, temp_r0_2);
    func_0200fd38(temp_r6, temp_r7, temp_r0_2);
    _ZN8Object3D8SetScaleEiii(temp_r0_2, 0x10A, 0x10A, 0x10A);
    _ZN8Object3D21MaybeSetBCFGAnimationEii(temp_r0_2, 0, 0);
    return 1;
}
