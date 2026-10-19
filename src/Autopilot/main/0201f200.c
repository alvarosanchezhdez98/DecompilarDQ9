#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, s32);

void func_0201f1f0(void *arg0, s32 arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, s32 *, 0xC) = _ZN13SafeAllocator8AllocateEj(arg2, arg1 << 5);
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
}
