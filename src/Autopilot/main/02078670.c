#include <m2c.h>

M2C_UNK _ZN8Object3D10MakeHiddenEv(M2C_UNK);
s32 _ZNK8Object3D17GetInheritedAlphaEv();
M2C_UNK func_02076a8c(M2C_UNK);

void func_02078660(M2C_UNK arg0) {
    if (_ZNK8Object3D17GetInheritedAlphaEv() != 0) {
        return;
    }
    func_02076a8c(arg0);
    _ZN8Object3D10MakeHiddenEv(arg0);
}
