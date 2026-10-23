#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
s32 _ZN16BackgroundLoader13GetTaskStatusEi(s32, s32);
s32 _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(s32, s32, M2C_UNK);
M2C_UNK _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(s32, s32, s32 *, s32 *);
s32 _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(s32, s32, s32, M2C_UNK);
M2C_UNK func_020dfe88(void *);
M2C_UNK func_020dfec0(void *, s32, s32, s32);
M2C_UNK func_020e0028(void *, s32, s32, s32, s16 *, s32);

s32 func_020dfd40(void *arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    s32 spC;
    s16 sp8;
    s16 temp_r1;
    s16 temp_r1_2;
    s32 temp_r0;
    s32 var_r0;

    temp_r0 = _ZN16BackgroundLoader11GetInstanceEv();
    temp_r1 = M2C_FIELD(arg0, s16 *, 0xE);
    switch (temp_r1) {                              /* irregular */
    case 1:
        if (arg1 == 0) {
            func_020dfe88(arg0);
            return 1;
        }
        if (arg2 != 0) {
            var_r0 = _ZN16BackgroundLoader18QueueLoadFileInGP2EPKcS1_P13SafeAllocator(temp_r0, arg1, arg2, 0);
        } else {
            var_r0 = _ZN16BackgroundLoader13QueueLoadFileEPKcP13SafeAllocator(temp_r0, arg1, 0);
        }
        M2C_FIELD(arg0, s32 *, 0x10) = var_r0;
        M2C_FIELD(arg0, s16 *, 0xE) = 2;
        return func_020dfd40(arg0, 0, 0);
    case 2:
        if (_ZN16BackgroundLoader13GetTaskStatusEi(temp_r0, M2C_FIELD(arg0, s32 *, 0x10)) == 0) {
            return 0;
        }
        M2C_FIELD(arg0, s16 *, 0xE) = 3;
        return func_020dfd40(arg0, 0, 0);
    case 3:
        sp10 = 0;
        spC = 0;
        _ZN16BackgroundLoader17GetLoadedFileByIDEiPPvPj(temp_r0, M2C_FIELD(arg0, s32 *, 0x10), &sp10, &spC);
        temp_r1_2 = M2C_FIELD(arg0, s16 *, 0xC);
        if ((s32) temp_r1_2 < 0) {
            func_020dfec0(arg0, M2C_FIELD(arg0, s32 *, 0x14), sp10, spC);
        } else {
            sp8 = temp_r1_2;
            func_020e0028(arg0, M2C_FIELD(arg0, s32 *, 0x14), sp10, spC, &sp8, 1);
        }
        func_020dfe88(arg0);
        return 1;
    default:
        return 1;
    }
}
