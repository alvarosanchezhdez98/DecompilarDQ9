#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();
extern s32 data_ov017_021d83ec;

void func_ov017_021b14a0(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x2B;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    data_ov017_021d83ec = 0;
    M2C_FIELD(arg0, s8 *, 0x30) = 0;
    M2C_FIELD(arg0, s8 *, 0x31) = 0;
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    M2C_FIELD(arg0, s8 *, 0x49) = 1;
    M2C_FIELD(arg0, s8 *, 0x4A) = 0;
}
