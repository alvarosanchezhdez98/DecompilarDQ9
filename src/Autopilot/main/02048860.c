#include <m2c.h>

M2C_UNK _ZN8Object3D9SetHeightEi(void *, s16);
M2C_UNK _ZN8Object3D9SetRadiusEi(void *, s32);

void func_02048850(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x144) = arg1;
    _ZN8Object3D9SetRadiusEi(arg0, M2C_FIELD(arg1, s16 *, 0xC) * 4);
    _ZN8Object3D9SetHeightEi(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0x144), s16 *, 0xE));
}
