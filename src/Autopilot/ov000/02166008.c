#include <m2c.h>

M2C_UNK _Z42LoadAndDecompressGPCHeaderAndInnerFileInfoPP7GPCFileR15ExtendedNitroVMPKcPvRjjbPb(s32, s32, M2C_UNK *, M2C_UNK *, s32 *, s32, s32, s32);
M2C_UNK _ZN11GPCReadPair14ZeroInitializeEv(s32);
M2C_UNK _ZN16BackgroundLoader13AddLockGlobalEv();
M2C_UNK _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
extern M2C_UNK data_0211e33c;
extern M2C_UNK data_ov000_02183a2f;

s32 func_ov000_02166008(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;

    if (arg2 != 0) {
        _ZN16BackgroundLoader13AddLockGlobalEv();
        _ZN16BackgroundLoader21FreeAllocationsGlobalEv();
    }
    _ZN11GPCReadPair14ZeroInitializeEv(arg1);
    _Z42LoadAndDecompressGPCHeaderAndInnerFileInfoPP7GPCFileR15ExtendedNitroVMPKcPvRjjbPb(arg1, arg1 + 4, &data_ov000_02183a2f, &data_0211e33c, &sp10, 0x30000, 0, 0);
    return sp10;
}
