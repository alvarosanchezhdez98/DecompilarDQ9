#include <m2c.h>

M2C_UNK _ZN8Vector3iaSERKS_(void *, void *);
M2C_UNK func_02076ccc(void *, M2C_UNK);
void _ZN8Object3D24TransitionInheritedAlphaEii(void *, s32, s32);
s32 _ZNK8Object3D17GetInheritedAlphaEv(void *);

void func_02077630(void *arg0) {
    if ((_ZNK8Object3D17GetInheritedAlphaEv(arg0) != 0) && (_ZNK8Object3D17GetInheritedAlphaEv(arg0) != 0x1F)) {
        return;
    }
    if (_ZNK8Object3D17GetInheritedAlphaEv(arg0) == 0) {
        _ZN8Vector3iaSERKS_(arg0 + 0x44, arg0 + 0x158);
        _ZN8Object3D24TransitionInheritedAlphaEii(arg0, 0x1F, 0xFA);
    }
    if (_ZNK8Object3D17GetInheritedAlphaEv(arg0) != 0x1F) {
        return;
    }
    func_02076ccc(arg0, 1);
}
