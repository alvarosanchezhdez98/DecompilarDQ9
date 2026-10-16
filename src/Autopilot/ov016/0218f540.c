#include <m2c.h>

s32 _Z12NitroVM_SeekP7NitroVMii(s32, s32, M2C_UNK);
M2C_UNK _Z30NitroVM_AwaitCommandCompletionP7NitroVM(s32);

s32 func_ov016_0218f540(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, u8 *, 0x10) == 1) {
        _Z30NitroVM_AwaitCommandCompletionP7NitroVM(M2C_FIELD(arg0, s32 *, 0xC));
        M2C_FIELD(arg0, u8 *, 0x10) = 0U;
    }
    if (_Z12NitroVM_SeekP7NitroVMii(M2C_FIELD(arg0, s32 *, 0xC), arg1, 0) == 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    return 1;
}
