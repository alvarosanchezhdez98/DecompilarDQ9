#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0205a444(void *);
M2C_UNK func_020dfc40(void *);

void func_ov003_0217daf0(void *arg0) {
    M2C_FIELD(arg0, u32 *, 0) = (u32) ((u32) (*(s32 *)0x04000000 & 0x1F00) >> 8);
    M2C_FIELD(arg0, s8 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 5) = 0;
    M2C_FIELD(arg0, s8 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 1;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s8 *, 0x30) = 0;
    M2C_FIELD(arg0, s8 *, 0x31) = 0;
    VectorizedMemset(arg0 + 0x18, 0, 0x18);
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    func_0205a444(arg0 + 0x3C);
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0xA4);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0xB8);
    func_020dfc40(arg0 + 0xCC);
}
