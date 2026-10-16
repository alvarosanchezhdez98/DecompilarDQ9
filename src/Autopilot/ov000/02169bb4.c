#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
M2C_UNK func_ov000_02169b78();
extern M2C_UNK data_ov000_02184264;

void func_ov000_02169bb4(s32 arg0) {
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 8);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 0) = arg0;
    func_ov000_02169b78();
}
