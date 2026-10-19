#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();
M2C_UNK func_0205c790(void *);

void func_ov017_021acd7c(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 1;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 0;
    M2C_FIELD(arg0, s8 *, 0x27C) = 0;
    M2C_FIELD(arg0, s8 *, 0x27D) = 0;
    M2C_FIELD(arg0, s8 *, 0x27E) = 0;
    M2C_FIELD(arg0, s8 *, 0x1E) = 0;
    M2C_FIELD(arg0, s8 *, 0x1F) = 0;
    M2C_FIELD(arg0, s8 *, 0x280) = 0;
    M2C_FIELD(arg0, s8 *, 0x27F) = 0;
    M2C_FIELD(arg0, s16 *, 0x40) = -1;
    M2C_FIELD(arg0, s8 *, 0x281) = 0;
    M2C_FIELD(arg0, s8 *, 0x282) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    VectorizedMemset(arg0 + 0x2C, 0, 0x14);
    func_0205c790(arg0 + 0x44);
}
