#include <m2c.h>

s32 _ZN16BackgroundLoader11GetInstanceEv();
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader19GetLoadedFileByNameEPKcPPvPj(s32, M2C_UNK *, s32 *, s32 *);
s32 func_ov017_021d612c();
M2C_UNK sprintf(M2C_UNK *, M2C_UNK *, s32);
M2C_UNK func_ov001_021537b0(M2C_UNK *, s32, s32, s32);
s32 func_ov001_0215a750(M2C_UNK *, s32 *);
extern M2C_UNK data_ov001_02165745;
extern M2C_UNK data_ov001_021658b8;
extern M2C_UNK data_ov001_021658d8;

s32 func_ov001_0215e1cc(void) {
    M2C_UNK sp8[10];
    s32 sp4;
    s32 sp0;
    s32 var_r4;

    sprintf(sp8, &data_ov001_02165745, func_ov017_021d612c());
    var_r4 = 0;
    _ZN16BackgroundLoader19GetLoadedFileByNameEPKcPPvPj(_ZN16BackgroundLoader11GetInstanceEv(), sp8, &sp4, &sp0);
    if (sp4 == 0) {
        _ZN16BackgroundLoader13AddLockGlobalEv();
        var_r4 = 1;
        if (func_ov001_0215a750(sp8, &sp4) == 0) {
            _ZN16BackgroundLoader16RemoveLockGlobalEv();
            return 0;
        }
    }
    func_ov001_021537b0(&data_ov001_021658d8, M2C_FIELD(&data_ov001_021658b8, s32 *, 0), sp4, sp0);
    if (var_r4 != 0) {
        _ZN16BackgroundLoader16RemoveLockGlobalEv();
    }
    M2C_FIELD(&data_ov001_021658b8, s8 *, 0x8C) = 0;
    return 1;
}
