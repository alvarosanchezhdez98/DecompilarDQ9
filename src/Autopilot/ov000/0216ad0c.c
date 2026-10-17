#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, s32);
s32 _ZNK6Script9Parameter8ToStringEv(M2C_UNK);
M2C_UNK func_ov000_02169b78(void *);
M2C_UNK strcpy(void *, s32);
s32 strlen();
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216ad0c(M2C_UNK arg0) {
    s32 temp_r4;
    void *temp_r0;
    void *temp_r0_2;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0xC);
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 0) = 0x22;
    temp_r4 = _ZNK6Script9Parameter8ToStringEv(arg0);
    temp_r0_2 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), strlen() + 1);
    M2C_FIELD(temp_r0, void **, 8) = temp_r0_2;
    strcpy(temp_r0_2, temp_r4);
    func_ov000_02169b78(temp_r0);
    return 1;
}
