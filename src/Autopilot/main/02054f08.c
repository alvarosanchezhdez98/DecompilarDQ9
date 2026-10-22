#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);

s32 func_02054ef8(void **arg0, s32 arg1) {
    void *temp_r0;

    if (arg1 == 0) {
        return 0;
    }
    temp_r0 = _ZN13SafeAllocator8AllocateEj(arg1, 0xC);
    *arg0 = temp_r0;
    if (temp_r0 == NULL) {
        return 0;
    }
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 8) = 0;
    return 1;
}
