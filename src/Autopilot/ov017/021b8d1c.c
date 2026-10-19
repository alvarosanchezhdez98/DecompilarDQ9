#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK func_0204693c();
M2C_UNK func_0208b9a0(s32, M2C_UNK);
M2C_UNK func_ov017_021b994c(void *);

void func_ov017_021b8d1c(void *arg0) {
    func_0204693c();
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x1C);
    func_0208b9a0(arg0 + 0x30, 0);
    M2C_FIELD(arg0, s8 *, 0) = 5;
    M2C_FIELD(arg0, s32 *, 0x11C) = 0;
    M2C_FIELD(arg0, s32 *, 0x124) = 0;
    M2C_FIELD(arg0, s32 *, 0x114) = 0;
    M2C_FIELD(arg0, s32 *, 0x118) = 0;
    M2C_FIELD(arg0, s8 *, 0x128) = 0;
    M2C_FIELD(arg0, s8 *, 0x129) = 0;
    M2C_FIELD(arg0, s8 *, 0x137) = 0;
    M2C_FIELD(arg0, s8 *, 0x138) = 0;
    M2C_FIELD(arg0, s8 *, 0x139) = 0;
    func_ov017_021b994c(arg0);
}
