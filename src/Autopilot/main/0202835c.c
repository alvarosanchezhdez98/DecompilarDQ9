#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, s32);

void func_0202834c(void *arg0, M2C_UNK arg1, s8 arg2) {
    M2C_FIELD(arg0, s32 *, 0x28) = _ZN13SafeAllocator8AllocateEj(arg1, arg2 * 4);
    M2C_FIELD(arg0, s8 *, 0x25) = 0;
    M2C_FIELD(arg0, s8 *, 0x24) = arg2;
}
