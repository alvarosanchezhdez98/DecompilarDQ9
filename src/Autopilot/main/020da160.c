#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, s32);
s32 strlen(s32);
M2C_UNK strncpy(s32, s32, s32);

s32 func_020da150(M2C_UNK arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r6;

    if (arg1 == 0) {
        return 0;
    }
    temp_r0_2 = strlen(arg1);
    temp_r6 = temp_r0_2 + 1;
    temp_r0 = _ZN13SafeAllocator8AllocateEj(arg0, temp_r6);
    if (temp_r0 == 0) {
        return 0;
    }
    strncpy(temp_r0, arg1, temp_r0_2);
    M2C_FIELD((temp_r0 + temp_r6), s8 *, -1) = 0;
    return temp_r0;
}
