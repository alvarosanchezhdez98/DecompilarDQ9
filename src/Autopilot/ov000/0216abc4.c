#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
s32 _ZNK6Script9Parameter5ToIntEv(s32);
M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216abc4(s32 arg0, s32 arg1) {
    void *temp_r5;

    temp_r5 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0x10);
    if (arg1 == 1) {
        M2C_FIELD(temp_r5, s32 *, 0) = 0;
        M2C_FIELD(temp_r5, s32 *, 4) = 0;
        M2C_FIELD(temp_r5, s32 *, 0) = 0x1E;
        M2C_FIELD(temp_r5, s32 *, 0xC) = _ZNK6Script9Parameter5ToIntEv(arg0);
        M2C_FIELD(temp_r5, s8 *, 8) = -1;
        func_ov000_02169b78(temp_r5);
    } else if (arg1 == 2) {
        M2C_FIELD(temp_r5, s32 *, 0) = 0;
        M2C_FIELD(temp_r5, s32 *, 4) = 0;
        M2C_FIELD(temp_r5, s32 *, 0) = 0x1E;
        M2C_FIELD(temp_r5, s8 *, 8) = (s8) _ZNK6Script9Parameter5ToIntEv(arg0);
        M2C_FIELD(temp_r5, s32 *, 0xC) = _ZNK6Script9Parameter5ToIntEv(arg0 + 8);
        func_ov000_02169b78(temp_r5);
    }
    return 1;
}
