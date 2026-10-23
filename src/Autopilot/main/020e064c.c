#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(s32, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_02022b90(void *, void *);

void func_020e063c(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_r4;

    temp_r4 = _ZN16BackgroundLoader11GetInstanceEv();
    M2C_FIELD(arg0, s8 *, 0x9C5) = 1;
    func_02022b90(arg0, arg0 + 0xA0C);
    M2C_FIELD(arg0, s32 *, 0xA0C) = _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(temp_r4, arg1, arg2, 0);
}
