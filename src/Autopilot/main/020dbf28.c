#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_020dbf70(void *);

s32 func_020dbf18(void *arg0, M2C_UNK arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r4;

    temp_r4 = _ZN16BackgroundLoader11GetInstanceEv();
    func_020dbf70(arg0);
    M2C_FIELD(arg0, s32 *, 0) = arg2;
    M2C_FIELD(arg0, s32 *, 4) = arg3;
    M2C_FIELD(arg0, s32 *, 8) = arg4;
    M2C_FIELD(arg0, s32 *, 0xC) = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(temp_r4, arg1, 0);
    M2C_FIELD(arg0, s32 *, 0x10) = 1;
    return 0;
}
