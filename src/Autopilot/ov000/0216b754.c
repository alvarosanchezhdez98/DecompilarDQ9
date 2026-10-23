#include <m2c.h>

M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;
void * _ZN13SafeAllocator8AllocateEj(void *, u32);
s32 _ZNK6Script9Parameter5ToIntEv(void *);

s32 func_ov000_0216b754(void *arg0, s32 arg1) {
    s32 var_r0;
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, void **, 8), 0xCU);
    if (temp_r0 == NULL) {
        return 0;
    }
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 0) = 0x3A;
    if (arg1 == 0) {
        var_r0 = 1;
    } else {
        var_r0 = _ZNK6Script9Parameter5ToIntEv(arg0);
    }
    M2C_FIELD(temp_r0, s32 *, 8) = var_r0;
    func_ov000_02169b78(temp_r0);
    return 1;
}
