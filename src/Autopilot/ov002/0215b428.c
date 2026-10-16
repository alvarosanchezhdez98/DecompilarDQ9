#include <m2c.h>

M2C_UNK _ZN12ItemSortList6FinishEv(s32);
M2C_UNK _ZN13SafeAllocator5ResetEv(s32);

void func_ov002_0215b428(void *arg0) {
    _ZN12ItemSortList6FinishEv(arg0 + 0x804);
    _ZN13SafeAllocator5ResetEv(arg0 + 0x850);
    M2C_FIELD(arg0, s32 *, 0x2534) = 0;
    M2C_FIELD(arg0, s32 *, 0x2538) = 0;
}
