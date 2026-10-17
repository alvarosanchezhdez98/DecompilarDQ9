#include <m2c.h>
#pragma optimization_level 4

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();
M2C_UNK func_020727d8(void *);

void func_ov017_021befe4(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x35;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    func_020727d8(arg0 + 0xC);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x14);
}
