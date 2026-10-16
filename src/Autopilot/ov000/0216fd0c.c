#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(s32, M2C_UNK *, M2C_UNK *, M2C_UNK);
extern M2C_UNK data_ov000_02183fcc;
extern M2C_UNK data_ov000_02183fe0;

void func_ov000_0216fd0c(s32 *arg0) {
    *arg0 = _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(_ZN16BackgroundLoader11GetInstanceEv(), &data_ov000_02183fcc, &data_ov000_02183fe0, 0);
}
