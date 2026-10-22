#include <m2c.h>

M2C_UNK _ZN8Object3D10EnableFlagEi(void *, M2C_UNK);
M2C_UNK _ZN8Object3D27UseRenderConfigDiffuseColorEv(void *);
M2C_UNK _ZN8Object3D8SetScaleEiii(void *, s32, s32, s32);
M2C_UNK _ZN8Object3D9SetHeightEi(void *, s16);
M2C_UNK _ZN8Object3D9SetRadiusEi(void *, s32);
s32 _ZNK8Object3D8GetFlagsEv(void *);

void func_020484f8(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, void **, 0xAC) = (void *) M2C_FIELD(arg1, void **, 0);
    M2C_FIELD(arg0, s32 *, 0xB4) = (s32) M2C_FIELD(arg1, s32 *, 8);
    _ZN8Object3D8SetScaleEiii(arg0, 0x10A, 0x10A, 0x10A);
    _ZN8Object3D9SetRadiusEi(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0xAC), s16 *, 0xC) * 4);
    _ZN8Object3D9SetHeightEi(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0xAC), s16 *, 0xE));
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xAC), s16 *, 8) == 0x140) {
        _ZN8Object3D10EnableFlagEi(arg0, 0x20000000);
    }
    if (_ZNK8Object3D8GetFlagsEv(arg0) & 0x20000000) {
        return;
    }
    _ZN8Object3D27UseRenderConfigDiffuseColorEv(arg0);
}
