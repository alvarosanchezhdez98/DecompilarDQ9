#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv();
M2C_UNK func_02029568(s32);

void func_ov016_0218b5a0(void *arg0) {
    _ZN13SafeAllocator21ResetAllocatorPointerEv();
    func_02029568(arg0 + 0x14);
    M2C_FIELD(arg0, s32 *, 0x94) = 1;
}
