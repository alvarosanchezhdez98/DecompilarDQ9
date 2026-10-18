#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();

void func_ov017_021c2b28(void *arg0, s8 arg1, s8 arg2) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x46;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    M2C_FIELD(arg0, s8 *, 0x8C) = 0;
    M2C_FIELD(arg0, s8 *, 0x8D) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, s8 *, 0x96) = 0;
    M2C_FIELD(arg0, s8 *, 0x94) = arg1;
    M2C_FIELD(arg0, s8 *, 0x95) = arg2;
}
