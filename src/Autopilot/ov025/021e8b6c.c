#include <m2c.h>

M2C_UNK _ZN13SafeAllocator5ResetEv(s32);
M2C_UNK func_0207df50(s32);
M2C_UNK func_ov025_021e8bc4(void *, u8);

void func_ov025_021e8b6c(void *arg0) {
    _ZN13SafeAllocator5ResetEv(M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x30) * 4)), s32 *, 0x10));
    func_0207df50(M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x30) * 4)), s32 *, 0x20));
    func_ov025_021e8bc4(arg0, M2C_FIELD(arg0, u8 *, 0x30));
}
