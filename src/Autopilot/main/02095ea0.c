#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(M2C_UNK, M2C_UNK);
s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(s32, M2C_UNK *, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);
extern M2C_UNK data_020f1474;

s32 func_02095e90(void *arg0, M2C_UNK arg1) {
    s32 temp_r0;

    temp_r0 = _ZN13SafeAllocator8AllocateEj(arg1, 0x198);
    M2C_FIELD(arg0, s32 *, 0xA8) = temp_r0;
    if (temp_r0 == 0) {
        return 0;
    }
    memset(temp_r0, 0, 0x198);
    M2C_FIELD(arg0, s32 *, 0x4C4) = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(_ZN16BackgroundLoader11GetInstanceEv(), &data_020f1474, 0);
    return 1;
}
