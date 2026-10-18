#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();
M2C_UNK func_0205c790(void *);
M2C_UNK func_020dfc40(void *);

void func_ov017_021a7328(void *arg0) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x3F;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = -1;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    func_0205c790(arg0 + 0x24);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0x25C);
    func_020dfc40(arg0 + 0x270);
}
