#include <m2c.h>

s32 _ZN9GameState11GetInstanceEv();
s32 _ZNK8Object3D10GetField06Ev(s32);
s32 func_0200ff1c(s32, M2C_UNK);

s32 func_ov002_02154a6c(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r6;

    temp_r0 = _ZN9GameState11GetInstanceEv();
    temp_r0_2 = func_0200ff1c(temp_r0, arg1);
    if (temp_r0_2 == 0) {
        return 0;
    }
    temp_r0_3 = func_0200ff1c(temp_r0, arg2);
    if (temp_r0_3 == 0) {
        return 0;
    }
    temp_r6 = _ZNK8Object3D10GetField06Ev(temp_r0_2);
    if (temp_r6 == _ZNK8Object3D10GetField06Ev(temp_r0_3)) {
        return 1;
    }
    if (((_ZNK8Object3D10GetField06Ev(temp_r0_2) == 0x2710) && (_ZNK8Object3D10GetField06Ev(temp_r0_3) == 0x170C)) || ((_ZNK8Object3D10GetField06Ev(temp_r0_2) == 0x170C) && (_ZNK8Object3D10GetField06Ev(temp_r0_3) == 0x2710))) {
        return 1;
    }
    if (((_ZNK8Object3D10GetField06Ev(temp_r0_2) == 0x2774) && (_ZNK8Object3D10GetField06Ev(temp_r0_3) == 0x1901)) || ((_ZNK8Object3D10GetField06Ev(temp_r0_2) == 0x1901) && (_ZNK8Object3D10GetField06Ev(temp_r0_3) == 0x2774))) {
        return 1;
    }
    return 0;
}
