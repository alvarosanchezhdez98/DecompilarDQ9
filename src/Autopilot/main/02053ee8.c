#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(void *, void *);
s32 _ZNK8Object3D10GetField06Ev();

void func_02053ed8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x15C) = _ZNK8Object3D10GetField06Ev();
    _ZN8Vector3iaSERKS_(arg0 + 0x160, arg0 + 0x44);
    _ZN8Vector3iaSERKS_(arg0 + 0x16C, arg0 + 0x50);
}
