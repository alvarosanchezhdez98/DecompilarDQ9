#include <m2c.h>
#pragma optimize_for_size off

M2C_UNK _Z12NitroVM_SeekP7NitroVMii(s32, s32, M2C_UNK);
s32 _Z16NitroVM_ReadSyncP7NitroVMPvi(s32, M2C_UNK, s32);
M2C_UNK _Z30NitroVM_AwaitCommandCompletionP7NitroVM(s32);

s32 func_ov016_0218f58c(void *arg0, M2C_UNK arg1, s32 arg2) {
    if (M2C_FIELD(arg0, u8 *, 0x10) == 1) {
        _Z30NitroVM_AwaitCommandCompletionP7NitroVM(M2C_FIELD(arg0, s32 *, 0xC));
        _Z12NitroVM_SeekP7NitroVMii(M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 8), 0);
        M2C_FIELD(arg0, u8 *, 0x10) = 0U;
    }
    if (_Z16NitroVM_ReadSyncP7NitroVMPvi(M2C_FIELD(arg0, s32 *, 0xC), arg1, arg2) == -1) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + arg2);
    return 1;
}
