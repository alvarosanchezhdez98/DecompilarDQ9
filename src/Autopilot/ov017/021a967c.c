#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_ov017_021a967c(void *arg0, s8 arg1) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x3A;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0xC);
    M2C_FIELD(arg0, s8 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x24) = arg1;
    M2C_FIELD(arg0, s8 *, 9) = 0;
    M2C_FIELD(arg0, s8 *, 0x25) = 0;
    M2C_FIELD(arg0, s8 *, 0x26) = 0;
    VectorizedMemset(arg0 + 0x28, 0, 6);
    memset(arg0 + 0x2E, 0, 0xB);
    M2C_FIELD(arg0, u16 *, 0x3A) = (u16) (M2C_FIELD(arg0, u16 *, 0x3A) & ~0x3FFF);
    M2C_FIELD(arg0, s8 *, 0x39) = 0;
    M2C_FIELD(arg0, u16 *, 0x3A) = (u16) (M2C_FIELD(arg0, u16 *, 0x3A) & ~0x4000);
    VectorizedMemset(arg0 + 0x3C, 0, 0x18);
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
}
