#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();

void func_ov017_021c0334(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x28;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x24) = 0;
}
