#include <m2c.h>

M2C_UNK _ZN8Object3D24MaybeSetRegularAnimationEPKci(void *, s32, s32);

void func_020415b0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0xCC) = arg1;
    _ZN8Object3D24MaybeSetRegularAnimationEPKci(arg0, arg1, M2C_FIELD(arg0, s32 *, 0xD0));
}
