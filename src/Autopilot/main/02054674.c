#include <m2c.h>

M2C_UNK _ZN8Object3D10EnableFlagEi(void *, M2C_UNK);
M2C_UNK func_02037d10();

void func_02054664(void *arg0) {
    func_02037d10();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x1000);
    M2C_FIELD(arg0, s8 *, 0x2D0) = -1;
    M2C_FIELD(arg0, s8 *, 0x2D1) = -1;
    M2C_FIELD(arg0, s8 *, 0x2D2) = 0;
    _ZN8Object3D10EnableFlagEi(arg0, 0x80);
}
