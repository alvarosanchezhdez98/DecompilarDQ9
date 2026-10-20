#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(s32, M2C_UNK *, M2C_UNK);
extern M2C_UNK data_020f00cc;

void func_02046c98(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xE8) != 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0xEC) = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(_ZN16BackgroundLoader11GetInstanceEv(), &data_020f00cc, 0);
}
