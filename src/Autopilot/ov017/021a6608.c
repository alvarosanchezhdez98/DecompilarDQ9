#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();

void func_ov017_021a6608(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x3D;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = -1;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
    M2C_FIELD(arg0, s8 *, 0xB) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x10);
}
