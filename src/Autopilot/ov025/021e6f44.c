#include <m2c.h>

void *_ZN9GameState11GetInstanceEv();
void *_ZN9GameState20GetGameObjectByIndexEi(void *, s32);
s32 _ZNK8Object3D19HasAnimationStoppedEv(void *);
s32 _ZNK8Object3D22HasAnimationReachedEndEv(void *);
M2C_UNK func_ov000_021820bc(s32, s32, M2C_UNK, s32 *);

s32 func_ov025_021e6f44(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp0[12];
    s32 var_r0;
    s32 var_r5;
    s32 var_r6;
    void *var_r4;

    var_r6 = arg1;
    var_r5 = arg3;
    var_r4 = _ZN9GameState11GetInstanceEv();
    func_ov000_021820bc(var_r5, var_r6, 0x17, sp0);
    var_r5 = sp0[0];
    var_r4 = _ZN9GameState20GetGameObjectByIndexEi(var_r4, var_r5);
    if (var_r4 == NULL) {
        return 1;
    }
    if ((var_r5 >= 0) && (var_r5 <= 3)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        if ((s32) M2C_FIELD(var_r4, s32 *, 0x24) < 0xB33) {
            return 0;
        }
        goto block_12;
    }
    if ((_ZNK8Object3D19HasAnimationStoppedEv(var_r4) == 0) && (_ZNK8Object3D22HasAnimationReachedEndEv(var_r4) == 0)) {
        return 0;
    }
block_12:
    return 1;
}
