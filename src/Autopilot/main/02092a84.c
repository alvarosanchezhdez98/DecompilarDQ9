#include <m2c.h>

M2C_UNK _ZN13SafeAllocator11CreateTypeAEPvj(M2C_UNK, s32, M2C_UNK);
s32 _ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);

void func_02092a74(M2C_UNK arg0, s32 arg1) {
    if (arg1 == 0) {
        return;
    }
    _ZN13SafeAllocator11CreateTypeAEPvj(arg0, _ZN13SafeAllocator8AllocateEj(arg1, 0x800), 0x800);
}
