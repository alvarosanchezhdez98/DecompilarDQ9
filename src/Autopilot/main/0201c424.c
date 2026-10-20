#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);

void func_0201c414(void *arg0, s32 arg1) {
    s32 temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(arg0, s32 *, 0x20), arg1 << 5);
    M2C_FIELD(arg0, s32 *, 0) = temp_r0;
    if (temp_r0 != 0) {
        M2C_FIELD(arg0, s32 *, 4) = arg1;
        M2C_FIELD(arg0, s32 *, 8) = 0;
    }
}
