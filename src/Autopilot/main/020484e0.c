#include <m2c.h>

M2C_UNK _ZN8Object3D10InitializeEv();

void func_020484d0(void *arg0) {
    _ZN8Object3D10InitializeEv();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x400);
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
}
