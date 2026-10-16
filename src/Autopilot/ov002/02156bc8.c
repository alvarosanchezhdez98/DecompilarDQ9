#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(s32, M2C_UNK *, M2C_UNK);
s32 _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(s32, s32, s32, M2C_UNK);
M2C_UNK _ZN16BackgroundLoader8AddFenceEv();
M2C_UNK func_0209a338(void *);
M2C_UNK func_0209a804(void *);
extern s32 data_020f2a0c;
extern s32 data_020f2a18;
extern M2C_UNK data_ov002_0216cf21;
extern M2C_UNK data_ov002_0216cf39;

void func_ov002_02156bc8(void *arg0) {
    s32 temp_r5;

    if (M2C_FIELD(arg0, s32 *, 0x247C) & 0x10) {
        return;
    }
    temp_r5 = _ZN16BackgroundLoader11GetInstanceEv();
    _ZN16BackgroundLoader8AddFenceEv();
    M2C_FIELD(arg0, s32 *, 0x1BA4) = _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(temp_r5, data_020f2a18, data_020f2a0c, 0);
    M2C_FIELD(arg0, s32 *, 0x1BA8) = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(temp_r5, &data_ov002_0216cf21, 0);
    M2C_FIELD(arg0, s32 *, 0x1BAC) = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(temp_r5, &data_ov002_0216cf39, 0);
    func_0209a804(arg0 + 0x2444);
    func_0209a338(arg0 + 0x243C);
    M2C_FIELD(arg0, s32 *, 0x247C) = (s32) (M2C_FIELD(arg0, s32 *, 0x247C) | 0x10);
}
