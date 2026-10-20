#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();
M2C_UNK func_020727d8(void *);

void func_020d8080(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x43;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    func_020727d8(arg0 + 0xC);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x14);
}
