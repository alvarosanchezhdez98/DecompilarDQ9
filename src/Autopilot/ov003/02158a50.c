#include <m2c.h>

M2C_UNK _ZN8Object3D11DisableFlagEi(s32, M2C_UNK);
M2C_UNK _ZN8Object3D24MaybeSetRegularAnimationEPKci(s32, M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov003_0217fe16;

void func_ov003_02158a50(void *arg0) {
    _ZN8Object3D24MaybeSetRegularAnimationEPKci(arg0 + 0x280, &data_ov003_0217fe16, 9);
    _ZN8Object3D11DisableFlagEi(arg0 + 0x280, 0x40000);
    M2C_FIELD(arg0, s32 *, 0x32C) = 1;
}
