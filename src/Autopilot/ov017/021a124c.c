#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();

void func_ov017_021a124c(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 2;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x20) = 2;
    M2C_FIELD(arg0, s8 *, 0x21) = 0;
    M2C_FIELD(arg0, s8 *, 0x22) = 0;
}
