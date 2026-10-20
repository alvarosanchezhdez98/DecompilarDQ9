#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();

void func_ov017_021aa50c(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x1A;
    M2C_FIELD(arg0, u32 *, 0xC) = (u32) ((u32) (*(s32 *)0x04000000 & 0x1F00) >> 8);
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x24);
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s16 *, 0x48) = -1;
    M2C_FIELD(arg0, s16 *, 0x4A) = -1;
    M2C_FIELD(arg0, s16 *, 0x4C) = -0xB;
    M2C_FIELD(arg0, s32 *, 0x50) = -1;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg0, s8 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
}
