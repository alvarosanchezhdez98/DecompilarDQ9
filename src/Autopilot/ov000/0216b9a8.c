#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
s32 _ZNK6Script9Parameter5ToIntEv();
M2C_UNK func_ov000_02169b78();
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216b9a8(void) {
    s32 temp_r0;
    void *temp_r0_2;

    temp_r0 = _ZNK6Script9Parameter5ToIntEv();
    if (temp_r0 < 0) {
        return 1;
    }
    temp_r0_2 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0xC);
    if (temp_r0_2 == NULL) {
        return 0;
    }
    M2C_FIELD(temp_r0_2, s32 *, 0) = 0;
    M2C_FIELD(temp_r0_2, s32 *, 4) = 0;
    M2C_FIELD(temp_r0_2, s32 *, 0) = 0x42;
    M2C_FIELD(temp_r0_2, s16 *, 8) = (s16) temp_r0;
    func_ov000_02169b78();
    return 1;
}
