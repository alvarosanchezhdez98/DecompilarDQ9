#include <m2c.h>

M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
M2C_UNK _ZN13SafeAllocator7DestroyEv(s32);
s32 _ZNK13SafeAllocator18GetSignedAllocatorEv(s32);

void func_020d6f0c(s32 arg0) {
    if (_ZNK13SafeAllocator18GetSignedAllocatorEv(arg0 + 0xA28) == 0) {
        return;
    }
    _ZN13SafeAllocator7DestroyEv(arg0 + 0xA28);
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0xA28);
}
