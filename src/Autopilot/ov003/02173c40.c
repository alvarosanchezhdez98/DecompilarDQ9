#include <m2c.h>

M2C_UNK VectorizedMemset(void *, M2C_UNK, M2C_UNK);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0205a444(void *);
M2C_UNK func_020727d8(void *);
M2C_UNK func_020a64bc(void *);
M2C_UNK func_ov003_0217bcb8(void *);

void func_ov003_02173c40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0) = 0;
    M2C_FIELD(arg0, s8 *, 1) = 0;
    M2C_FIELD(arg0, s16 *, 2) = -1;
    VectorizedMemset(arg0 + 4, 0, 0x40);
    VectorizedMemset(arg0 + 0x44, 0, 0x80);
    M2C_FIELD(arg0, s8 *, 0xC4) = 0;
    M2C_FIELD(arg0, s8 *, 0xCA) = 0;
    M2C_FIELD(arg0, s8 *, 0xCB) = 0;
    M2C_FIELD(arg0, s8 *, 0xCC) = 0;
    M2C_FIELD(arg0, s16 *, 0xC6) = 0;
    M2C_FIELD(arg0, s16 *, 0xC8) = 0;
    M2C_FIELD(arg0, s32 *, 0xD0) = 0;
    M2C_FIELD(arg0, s8 *, 0xD4) = 0;
    M2C_FIELD(arg0, s8 *, 0xD5) = 0;
    func_020a64bc(arg0 + 0xD8);
    M2C_FIELD(arg0, s8 *, 0xEC) = 0;
    M2C_FIELD(arg0, s8 *, 0xED) = 0;
    M2C_FIELD(arg0, s8 *, 0xEE) = 0;
    M2C_FIELD(arg0, s8 *, 0xEF) = 0;
    M2C_FIELD(arg0, s32 *, 0xF0) = -1;
    M2C_FIELD(arg0, s32 *, 0xF4) = -1;
    M2C_FIELD(arg0, s8 *, 0x10A) = 0;
    M2C_FIELD(arg0, s8 *, 0x10B) = 0;
    M2C_FIELD(arg0, s8 *, 0x11C) = 0;
    M2C_FIELD(arg0, s8 *, 0x11D) = 0;
    M2C_FIELD(arg0, s32 *, 0x120) = 0;
    M2C_FIELD(arg0, s32 *, 0x124) = 0;
    M2C_FIELD(arg0, s32 *, 0x128) = 0;
    M2C_FIELD(arg0, s32 *, 0x12C) = 0;
    func_0205a444(arg0 + 0x130);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x184);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x198);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x1AC);
    M2C_FIELD(arg0, s32 *, 0x1C0) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C4) = 0;
    func_020727d8(arg0 + 0x1C8);
    func_020727d8(arg0 + 0x1D0);
    func_020727d8(arg0 + 0x1D8);
    func_ov003_0217bcb8(arg0 + 0x1E0);
    M2C_FIELD(arg0, s8 *, 0x344) = 0;
}
