#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZN9GameState20GetGameObjectByIndexEi(s32, M2C_UNK);
s32 _ZNK8Object3D9GetHeightEv();
s32 _ZNK8Object3D9GetRadiusEv(s32);

s16 func_ov000_021635e4(M2C_UNK arg0, u32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 var_r5;
    s32 var_r6;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    if (temp_r0 == 0) {
        return 0x10A;
    }
    temp_r0_2 = _ZN9GameState20GetGameObjectByIndexEi(temp_r0, arg0);
    if (temp_r0_2 == 0) {
        return 0x10A;
    }
    var_r5 = 0x1000;
    var_r6 = _ZNK8Object3D9GetHeightEv();
    temp_r0_3 = _ZNK8Object3D9GetRadiusEv(temp_r0_2);
    switch (arg1) {
    default:
        break;
    case 0:
        if (var_r6 > temp_r0_3) {
            var_r6 = temp_r0_3;
        }
        var_r5 = var_r6;
        break;
    case 1:
        if (var_r6 < temp_r0_3) {
            var_r6 = temp_r0_3;
        }
        var_r5 = var_r6;
        break;
    case 2:
        var_r5 = (s32) (var_r6 + temp_r0_3) >> 1;
        break;
    case 3:
        var_r5 = temp_r0_3;
        break;
    case 4:
        var_r5 = var_r6;
        break;
    }
    return (s16) var_r5;
}
