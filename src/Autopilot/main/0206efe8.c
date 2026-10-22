#include <m2c.h>

s32 ExtractFileFromGP2(M2C_UNK *, M2C_UNK *, s32 *);
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader16RemoveLockGlobalEv();
M2C_UNK func_0206f01c(M2C_UNK, M2C_UNK, s32, s32);
extern M2C_UNK data_020f0a64;
extern M2C_UNK data_020f0a7a;

void func_0206efd8(M2C_UNK arg0, M2C_UNK arg1) {
    s32 sp0;

    _ZN16BackgroundLoader13AddLockGlobalEv();
    func_0206f01c(arg0, arg1, ExtractFileFromGP2(&data_020f0a64, &data_020f0a7a, &sp0), sp0);
    _ZN16BackgroundLoader16RemoveLockGlobalEv();
}
