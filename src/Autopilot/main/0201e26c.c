#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, s32);

void func_0201e25c(void *arg0, s32 arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, s32 *, 0) = _ZN13SafeAllocator8AllocateEj(arg2, arg1 * 0x58);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = arg1;
}
