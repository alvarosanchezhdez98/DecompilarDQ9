#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);

void func_0201c444(void *arg0, s32 arg1) {
    s32 temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(arg0, s32 *, 0x20), arg1 * 0x2C);
    M2C_FIELD(arg0, s32 *, 0xC) = temp_r0;
    if (temp_r0 != 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = arg1;
    }
}
