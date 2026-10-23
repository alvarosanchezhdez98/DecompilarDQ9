#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();
extern s32 data_ov017_021d8474;

void func_ov017_021c0124(void *arg0, s8 arg1) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x20;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    data_ov017_021d8474 = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x20) = arg1;
}
