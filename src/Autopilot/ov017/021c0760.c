#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(void *);
M2C_UNK func_0204693c();

void func_ov017_021c0760(void *arg0, u8 arg1) {
    func_0204693c();
    M2C_FIELD(arg0, s8 *, 0) = 0x29;
    M2C_FIELD(arg0, u8 *, 0xBC) = arg1;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 8);
    if (M2C_FIELD(arg0, u8 *, 0xBC) == 0) {
        return;
    }
    M2C_FIELD(arg0, s8 *, 0x25) = 0;
    M2C_FIELD(arg0, s8 *, 0x26) = 0;
    M2C_FIELD(arg0, s16 *, 0x28) = -1;
    M2C_FIELD(arg0, s16 *, 0x2A) = -1;
    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
    M2C_FIELD(arg0, s32 *, 0xAC) = 0;
    M2C_FIELD(arg0, s32 *, 0xB0) = 0;
    M2C_FIELD(arg0, s32 *, 0xB4) = 0;
    M2C_FIELD(arg0, s32 *, 0xB8) = 0;
}
