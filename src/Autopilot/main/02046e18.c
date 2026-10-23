#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK _ZN8Object3D10InitializeEv(void *);

void func_02046e08(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0x41700000;
    M2C_FIELD(arg0, s32 *, 0xEC) = -1;
    M2C_FIELD(arg0, s8 *, 0x1C) = 1;
    M2C_FIELD(arg0, s8 *, 0x1D) = 1;
    _ZN8Object3D10InitializeEv(arg0 + 0x3C);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x24);
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0xE8) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
}
