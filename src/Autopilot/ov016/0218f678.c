#include <m2c.h>

M2C_UNK _Z30NitroVM_AwaitCommandCompletionP7NitroVM(s32);

void func_ov016_0218f678(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x10) == 1) {
        _Z30NitroVM_AwaitCommandCompletionP7NitroVM(M2C_FIELD(arg0, s32 *, 0xC));
    }
    M2C_FIELD(arg0, u8 *, 0x10) = 0U;
}
