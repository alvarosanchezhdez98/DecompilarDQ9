#include <m2c.h>

s32 _Z18LoadFileIntoMemoryPKcPvPj(M2C_UNK *, M2C_UNK *, s32 *);
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK func_02070a30(M2C_UNK, M2C_UNK, s32, s32);
extern M2C_UNK data_0211e33c;
extern M2C_UNK data_020f0b64;

void func_020709ec(M2C_UNK arg0, M2C_UNK arg1) {
    s32 sp0;

    _ZN16BackgroundLoader13AddLockGlobalEv();
    func_02070a30(arg0, arg1, _Z18LoadFileIntoMemoryPKcPvPj(&data_020f0b64, &data_0211e33c, &sp0), sp0);
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
}
