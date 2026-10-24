#include <m2c.h>

void *_ZN13SafeAllocator8AllocateEj(s32, M2C_UNK);
M2C_UNK _ZN6Script9Parameter9ToVec3fixEP8Vector3i(M2C_UNK, M2C_UNK *);
M2C_UNK _ZN8Vector3iaSERKS_(void *, M2C_UNK *);
M2C_UNK __clear(M2C_UNK *, M2C_UNK);
M2C_UNK func_ov000_02169b78(void *);
extern M2C_UNK data_ov000_02184264;

s32 func_ov000_0216d038(M2C_UNK arg0) {
    M2C_UNK sp0[3];
    void *temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(M2C_FIELD(&data_ov000_02184264, s32 *, 8), 0x14);
    M2C_FIELD(temp_r0, s32 *, 0) = 0;
    M2C_FIELD(temp_r0, s32 *, 4) = 0;
    M2C_FIELD(temp_r0, s32 *, 0) = 0x8A;
    __clear(sp0, 0xC);
    _ZN6Script9Parameter9ToVec3fixEP8Vector3i(arg0, sp0);
    _ZN8Vector3iaSERKS_(temp_r0 + 8, sp0);
    func_ov000_02169b78(temp_r0);
    return 1;
}
