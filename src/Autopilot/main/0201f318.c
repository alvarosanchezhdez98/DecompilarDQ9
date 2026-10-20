#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, s32);
M2C_UNK strcpy(s32, M2C_UNK);
s32 strlen(M2C_UNK);

void func_0201f308(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_r0;

    M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x38) * 4)), s32 *, 0x18) = _ZN13SafeAllocator8AllocateEj(arg2, strlen(arg1) + 1);
    temp_r0 = M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x38) * 4)), s32 *, 0x18);
    if (temp_r0 == 0) {
        return;
    }
    strcpy(temp_r0, arg1);
    M2C_FIELD(arg0, u8 *, 0x38) = (u8) (M2C_FIELD(arg0, u8 *, 0x38) + 1);
}
