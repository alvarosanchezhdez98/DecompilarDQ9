#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, M2C_UNK);

void func_0204c7a8(void *arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3) {
    M2C_FIELD(arg0, s32 *, 0xD4) = _ZN13SafeAllocator8AllocateEj(arg1, arg3);
    M2C_FIELD(arg0, s32 *, 8) = arg2;
}
