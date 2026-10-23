#include <m2c.h>

extern M2C_UNK data_ov025_021ef988;
void * _ZN16BackgroundLoader11GetInstanceEv(void *);
s32 _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(void *, void *, void *, void *);
void _ZN16BackgroundLoader8AddFenceEv(void *);

void func_ov025_021e2628(void *arg0, void *arg1) {
    void *temp_r0;

    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv(arg0);
    if (!(M2C_FIELD(&data_ov025_021ef988, s32 *, 0x1C) & 0x2000)) {
        _ZN16BackgroundLoader8AddFenceEv(temp_r0);
        M2C_FIELD(&data_ov025_021ef988, s32 *, 0x1C) = (s32) (M2C_FIELD(&data_ov025_021ef988, s32 *, 0x1C) | 0x2000);
    }
    _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(temp_r0, arg0, arg1, NULL);
}
