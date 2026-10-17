#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK _ZN8Object3D10InitializeEv(void *);
M2C_UNK func_0204af64(void *);

void func_ov003_0217bcb8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 4);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x18);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x2C);
    func_0204af64(arg0 + 0x40);
    func_0204af64(arg0 + 0x60);
    _ZN8Object3D10InitializeEv(arg0 + 0x80);
    M2C_FIELD(arg0, s8 *, 0x12C) = 0;
    M2C_FIELD(arg0, s8 *, 0x12D) = -1;
    M2C_FIELD(arg0, s32 *, 0x130) = -1;
    M2C_FIELD(arg0, s32 *, 0x134) = -1;
    M2C_FIELD(arg0, s32 *, 0x138) = -1;
    M2C_FIELD(arg0, s32 *, 0x13C) = -1;
    M2C_FIELD(arg0, s8 *, 0x140) = 0;
    M2C_FIELD(arg0, s8 *, 0x141) = 0;
    M2C_FIELD(arg0, s8 *, 0x143) = 0;
    M2C_FIELD(arg0, s8 *, 0x142) = 0;
    M2C_FIELD(arg0, s32 *, 0x160) = 0;
    M2C_FIELD(arg0, s16 *, 0x15C) = 0;
}
