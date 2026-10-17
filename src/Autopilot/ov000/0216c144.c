#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, s32);
s8 _ZNK6Script9Parameter5ToIntEv(s32);
s32 _ZNK6Script9Parameter8ToStringEv(s32);
M2C_UNK func_ov000_02169b78(void *);
M2C_UNK strcpy(void *, s32);
s32 strlen();
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216c144(s32 arg0, s32 arg1) {
    s32 temp_r4;
    void *temp_r0;
    void *temp_r0_2;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0x10);
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 0) = 0x5B;
    M2C_FIELD(temp_r0, s8 *, 8) = _ZNK6Script9Parameter5ToIntEv(arg0);
    M2C_FIELD(temp_r0, s8 *, 9) = _ZNK6Script9Parameter5ToIntEv(arg0 + 8);
    if (arg1 >= 3) {
        temp_r4 = _ZNK6Script9Parameter8ToStringEv(arg0 + 0x10);
        temp_r0_2 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), strlen() + 1);
        M2C_FIELD(temp_r0, void **, 0xC) = temp_r0_2;
        if (temp_r0_2 != NULL) {
            strcpy(temp_r0_2, temp_r4);
        }
    } else {
        M2C_FIELD(temp_r0, void **, 0xC) = NULL;
    }
    func_ov000_02169b78(temp_r0);
    return 1;
}
