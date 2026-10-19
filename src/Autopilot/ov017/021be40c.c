#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();

void func_ov017_021be40c(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x4E;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = -1;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x38) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x24);
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s8 *, 0x39) = 0;
    VectorizedMemset(arg0 + 0x3A, 0, 0x10);
}
