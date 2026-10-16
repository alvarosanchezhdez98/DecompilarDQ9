#include <m2c.h>

M2C_UNK _ZN8Object3D10MakeHiddenEv();

void func_020406b0(void *arg0) {
    s32 temp_r1_2;
    void *temp_r1;

    temp_r1 = M2C_FIELD(arg0, void **, 0x14);
    if (temp_r1 != NULL) {
        M2C_FIELD(temp_r1, s32 *, 0x50) = (s32) (M2C_FIELD(temp_r1, s32 *, 0x50) | 1);
        return;
    }
    temp_r1_2 = M2C_FIELD(arg0, s32 *, 0x18);
    if (temp_r1_2 != 0) {
        _ZN8Object3D10MakeHiddenEv(temp_r1_2);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 0x1C) == 0) {
        return;
    }
    _ZN8Object3D10MakeHiddenEv();
}
