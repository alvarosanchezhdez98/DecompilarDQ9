#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();
M2C_UNK func_020727d8(void *);

void func_ov017_021a6be4(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x3E;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = -1;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    func_020727d8(arg0 + 0x14);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x1C);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x30);
}
