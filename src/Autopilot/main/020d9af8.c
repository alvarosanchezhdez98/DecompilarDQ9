#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();
M2C_UNK func_020dfc40(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_020d9ae8(void *arg0, s8 arg1) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x4A;
    M2C_FIELD(arg0, s8 *, 8) = arg1;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = -1;
    memset(arg0 + 0x10, 0, 0x30);
    func_020dfc40(arg0 + 0x40);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x58);
}
