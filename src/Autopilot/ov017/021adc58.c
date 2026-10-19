#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();

void func_ov017_021adc58(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x21;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0xF;
    M2C_FIELD(arg0, s8 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x21) = 0;
    M2C_FIELD(arg0, s16 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0xB) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x2C);
}
