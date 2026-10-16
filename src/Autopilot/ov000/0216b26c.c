#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
M2C_UNK _ZN6Script9Parameter9ToVec3fixEP8Vector3i(M2C_UNK, void *);
M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216b26c(M2C_UNK arg0) {
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0x14);
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 0) = 0x30;
    _ZN6Script9Parameter9ToVec3fixEP8Vector3i(arg0, temp_r0 + 8);
    func_ov000_02169b78(temp_r0);
    return 1;
}
