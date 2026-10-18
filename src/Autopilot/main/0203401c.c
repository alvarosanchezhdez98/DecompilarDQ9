#include <m2c.h>

M2C_UNK _ZN8Object3D11DisableFlagEi(void *, M2C_UNK);

void func_0203400c(void *arg0) {
    _ZN8Object3D11DisableFlagEi(arg0, 0x40000);
    M2C_FIELD(arg0, u8 *, 0xE0) = (u8) (M2C_FIELD(arg0, u8 *, 0xE0) & ~2);
}
