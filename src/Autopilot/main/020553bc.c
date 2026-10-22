#include <m2c.h>

M2C_UNK _ZN8Object3D10InitializeEv(void *);
M2C_UNK func_02054f80(void *);

void func_020553ac(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = -1;
    M2C_FIELD(arg0, s32 *, 0x1EC) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x1E8) = 0;
    _ZN8Object3D10InitializeEv(arg0 + 0x14);
    func_02054f80(arg0 + 0xC0);
}
