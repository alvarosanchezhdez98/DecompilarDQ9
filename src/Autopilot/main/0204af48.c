#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);

void func_0204af38(void *arg0, s8 arg1, s32 arg2) {
    if (arg2 == 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x10) = _ZN13SafeAllocator8AllocateEj(arg2, arg1 * 0x10);
    M2C_FIELD(arg0, s8 *, 0x1E) = arg1;
}
