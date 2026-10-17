#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();

void func_ov003_0217e630(void *arg0, s8 arg1) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x18;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0xB4) = arg1;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    M2C_FIELD(arg0, s16 *, 0xA0) = 0;
    M2C_FIELD(arg0, s32 *, 0xA4) = 0;
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
}
