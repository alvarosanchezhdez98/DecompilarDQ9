#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);

void func_ov003_0215e750(void *arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        return;
    }
    if (arg2 < 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0) = _ZN13SafeAllocator8AllocateEj(arg1, arg2 * 0x14);
    M2C_FIELD(arg0, s16 *, 4) = (s16) arg2;
    M2C_FIELD(arg0, s16 *, 6) = 0;
}
