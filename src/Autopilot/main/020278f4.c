#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, s32);

void func_020278e4(void *arg0, s32 arg1, M2C_UNK arg2) {
    M2C_FIELD(arg0, s32 *, 0x2C) = _ZN13SafeAllocator8AllocateEj(arg2, arg1 * 0x10);
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = arg1;
}
