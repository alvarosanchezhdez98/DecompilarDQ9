#include <m2c.h>

M2C_UNK _ZN8Object3D10InitializeEv(s32);
M2C_UNK func_02054f80(s32);

s32 func_02055558(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    _ZN8Object3D10InitializeEv(arg0 + 0x14);
    func_02054f80(arg0 + 0xC0);
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = arg5;
    M2C_FIELD(arg0, s32 *, 0xC) = arg3;
    M2C_FIELD(arg0, s32 *, 0x10) = arg4;
    return 1;
}
