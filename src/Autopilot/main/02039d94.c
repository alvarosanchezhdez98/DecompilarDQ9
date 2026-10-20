#include <m2c.h>

M2C_UNK _ZN8Object3D11DisableFlagEi(void *, s32);
M2C_UNK func_02033b88(void *, M2C_UNK);
M2C_UNK func_02038508(void *);

void func_02039d84(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0xE0) = (u8) (M2C_FIELD(arg0, u8 *, 0xE0) & ~1);
    _ZN8Object3D11DisableFlagEi(arg0, 0x1190);
    func_02038508(arg0 + 0x26C);
    func_02033b88(arg0, 0);
}
