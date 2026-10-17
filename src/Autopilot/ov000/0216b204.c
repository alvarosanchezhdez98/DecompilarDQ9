#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
s8 _ZNK6Script9Parameter5ToIntEv(s32);
M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216b204(s32 arg0) {
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0xC);
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 0) = 0x2F;
    M2C_FIELD(temp_r0, s8 *, 8) = _ZNK6Script9Parameter5ToIntEv(arg0);
    M2C_FIELD(temp_r0, s8 *, 9) = _ZNK6Script9Parameter5ToIntEv(arg0 + 8);
    M2C_FIELD(temp_r0, s16 *, 0xA) = (s16) _ZNK6Script9Parameter5ToIntEv(arg0 + 0x10);
    func_ov000_02169b78(temp_r0);
    return 1;
}
