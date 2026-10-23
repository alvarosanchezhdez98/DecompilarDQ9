#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_ov017_021c07d0();

void func_ov017_021c0820(void *arg0) {
    func_ov017_021c07d0();
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    M2C_FIELD(arg0, s8 *, 0xBC) = 0;
}
