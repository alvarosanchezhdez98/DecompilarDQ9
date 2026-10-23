#include <m2c.h>

s32 _Z18LoadFileIntoMemoryPKcPvPj(M2C_UNK *, M2C_UNK *, s32 *);
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK func_0207416c(M2C_UNK, M2C_UNK, s32, s32);
extern M2C_UNK data_0211e33c;
extern M2C_UNK data_020f0d40;

s32 func_02074114(M2C_UNK arg0, M2C_UNK arg1) {
    s32 sp0;
    s32 temp_r0;

    _ZN16BackgroundLoader13AddLockGlobalEv();
    temp_r0 = _Z18LoadFileIntoMemoryPKcPvPj(&data_020f0d40, &data_0211e33c, &sp0);
    if (temp_r0 != 0) {
        func_0207416c(arg0, arg1, temp_r0, sp0);
        _ZN16BackgroundLoader16RemoveLockGlobalEv();
        return 1;
    }
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
    return 0;
}
