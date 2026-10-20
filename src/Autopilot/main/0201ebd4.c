#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);
s32 _ZNK6Script9Parameter5ToIntEv();
extern M2C_UNK data_020fdc40;

s32 func_0201ebc4(void) {
    s32 temp_r0;
    void *temp_r5;

    temp_r0 = _ZNK6Script9Parameter5ToIntEv();
    temp_r5 = M2C_FIELD(&data_020fdc40, void **, 8);
    M2C_FIELD(temp_r5, s32 *, 0) = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_020fdc40, s32 *, 4), temp_r0 * 0xC);
    M2C_FIELD(temp_r5, s32 *, 8) = temp_r0;
    return 1;
}
