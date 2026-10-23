#include <m2c.h>

M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;
void * _ZN13SafeAllocator8AllocateEj(void *, u32);
s32 _ZNK6Script9Parameter5ToIntEv(void *);

s32 func_ov000_0216a1a4(void *arg0, s32 arg1) {
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, void **, 8), 0x10U);
    M2C_FIELD(temp_r0, s32 *, 0) = 8;
    M2C_FIELD(temp_r0, s32 *, 8) = _ZNK6Script9Parameter5ToIntEv(arg0);
    M2C_FIELD(temp_r0, s8 *, 0xC) = 0;
    if (arg1 >= 2) {
        M2C_FIELD(temp_r0, s8 *, 0xC) = (s8) _ZNK6Script9Parameter5ToIntEv(arg0 + 8);
    }
    func_ov000_02169b78(temp_r0);
    return 1;
}
