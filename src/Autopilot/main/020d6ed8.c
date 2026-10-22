#include <m2c.h>

M2C_UNK _ZN13SafeAllocator11CreateTypeAEPvj(s32, s32, M2C_UNK);
M2C_UNK _ZN13SafeAllocator21ResetAllocatorPointerEv(s32);
s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, M2C_UNK);
M2C_UNK func_020d6f44(s32);

void func_020d6ec8(s32 arg0, M2C_UNK arg1) {
    _ZN13SafeAllocator21ResetAllocatorPointerEv(arg0 + 0xA28);
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0 + 0xA28, _ZN13SafeAllocator8AllocateEj(arg1, 0x6000), 0x6000);
    func_020d6f44(arg0);
}
