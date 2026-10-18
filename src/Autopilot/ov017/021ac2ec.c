#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();

void func_ov017_021ac2ec(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x1E;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x10);
    M2C_FIELD(arg0, s32 *, 0x24) = -1;
    M2C_FIELD(arg0, s8 *, 0x28) = 0;
    M2C_FIELD(arg0, s8 *, 0x29) = 0;
}
