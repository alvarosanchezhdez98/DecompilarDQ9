#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader19GetLoadedFileByNameEPKcPPvPj(s32, M2C_UNK *, s32 *, s32 *);
M2C_UNK _ZN8Object3D39LoadType0AnimationPackageFromBCFGScriptEP13SafeAllocatorPKvj(s32, s32, s32, s32);
M2C_UNK _ZN8Object3D39LoadType0AnimationPackageFromBCFGScriptEPKcP13SafeAllocator(s32, M2C_UNK *, s32);
s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, s32);
M2C_UNK func_ov017_021d60f4(s32);
s32 func_ov017_021d612c();
M2C_UNK sprintf(M2C_UNK *, M2C_UNK *, s32);
s32 func_ov001_0215ad2c();
extern M2C_UNK data_ov001_02165745;
extern s32 data_ov001_021658b8[8];

s32 func_ov001_0215f344(s32 arg0) {
    M2C_UNK sp8[8];
    s32 sp4;
    s32 sp0;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r5;
    s32 temp_r5_2;

    temp_r5 = func_ov017_021d612c();
    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (temp_r0 == 0) {
        return 0;
    }
    sprintf(sp8, &data_ov001_02165745, temp_r5);
    func_ov017_021d60f4(arg0 + 8);
    temp_r0_2 = _ZN9GameState20GetGameObjectByIndexEi(temp_r0, func_ov001_0215ad2c());
    if (temp_r0_2 == 0) {
        return 0;
    }
    temp_r5_2 = *data_ov001_021658b8;
    _ZN16BackgroundLoader19GetLoadedFileByNameEPKcPPvPj(_ZN16BackgroundLoader11GetInstanceEv(), sp8, &sp4, &sp0);
    if (sp4 != 0) {
        _ZN8Object3D39LoadType0AnimationPackageFromBCFGScriptEP13SafeAllocatorPKvj(temp_r0_2, temp_r5_2, sp4, sp0);
    } else {
        _ZN8Object3D39LoadType0AnimationPackageFromBCFGScriptEPKcP13SafeAllocator(temp_r0_2, sp8, temp_r5_2);
    }
    return 1;
}
