#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
s32 _ZNK6Script9Parameter5ToIntEv(M2C_UNK);
M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216ccd8(M2C_UNK arg0) {
    s8 var_r1;
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0xC);
    M2C_FIELD(temp_r0, s32 *, 0) = 0x78;
    if (_ZNK6Script9Parameter5ToIntEv(arg0) != 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    M2C_FIELD(temp_r0, s8 *, 8) = var_r1;
    func_ov000_02169b78(temp_r0);
    return 1;
}
