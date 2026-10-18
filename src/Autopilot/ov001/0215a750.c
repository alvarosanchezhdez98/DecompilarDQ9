#include <m2c.h>

s32 _Z18LoadFileIntoMemoryPKcPvPj(M2C_UNK, M2C_UNK *, s32 *);
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
extern M2C_UNK data_0211e33c;

s32 func_ov001_0215a750(M2C_UNK arg0, M2C_UNK **arg1) {
    s32 sp0;

    _ZN16BackgroundLoader13AddLockGlobalEv();
    sp0 = 0;
    if (_Z18LoadFileIntoMemoryPKcPvPj(arg0, &data_0211e33c, &sp0) == 0) {
        return 0;
    }
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
    *arg1 = &data_0211e33c;
    return sp0;
}
