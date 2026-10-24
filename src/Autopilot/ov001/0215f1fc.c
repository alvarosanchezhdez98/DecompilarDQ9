#include <m2c.h>

s32 _ZN13SafeAllocator8AllocateEj(s32, s32);
s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader19GetLoadedFileByNameEPKcPPvPj(s32, M2C_UNK *, s32 *, s32 *);
s32 _ZN9GameState11GetInstanceEv();
s32 func_ov017_021d612c();
M2C_UNK memcpy(s32, s32, s32);
M2C_UNK sprintf(M2C_UNK *, M2C_UNK *, s32);
M2C_UNK func_ov001_021538c8();
M2C_UNK func_ov001_021538d4(s32, M2C_UNK, s32);
s32 func_ov001_0215a750(M2C_UNK *, s32 *);
extern M2C_UNK data_ov001_02165745;
extern s32 data_ov001_021658b8[8];

s32 func_ov001_0215f1fc(void) {
    M2C_UNK sp8[8];
    s32 sp4;
    s32 sp0;
    u32 temp_r0;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 var_r5;

    temp_r4 = func_ov017_021d612c();
    if (_ZN9GameState11GetInstanceEv() == 0) {
        return 0;
    }
    sprintf(sp8, &data_ov001_02165745, temp_r4);
    var_r5 = 0;
    temp_r4_2 = *data_ov001_021658b8;
    _ZN16BackgroundLoader19GetLoadedFileByNameEPKcPPvPj(_ZN16BackgroundLoader11GetInstanceEv(), sp8, &sp4, &sp0);
    if (sp4 == 0) {
        _ZN16BackgroundLoader13AddLockGlobalEv();
        var_r5 = 1;
        if (func_ov001_0215a750(sp8, &sp4) == 0) {
            _ZN16BackgroundLoader16RemoveLockGlobalEv();
            return 0;
        }
    }
    temp_r0 = _ZN13SafeAllocator8AllocateEj(temp_r4_2, sp0);
    if (temp_r0 == 0) {
        if (var_r5 != 0) {
            _ZN16BackgroundLoader16RemoveLockGlobalEv();
        }
        return 0;
    }
    memcpy(temp_r0, sp4, sp0);
    if (var_r5 != 0) {
        _ZN16BackgroundLoader16RemoveLockGlobalEv();
    }
    func_ov001_021538c8();
    func_ov001_021538d4(temp_r0, 0, temp_r4_2);
    return 1;
}
