#include <m2c.h>

M2C_UNK func_02042058(s32, s32);
s32 func_020e0434(void *, s16);

void func_ov003_02159290(void *arg0, s32 arg1, s32 arg2) {
    func_02042058(M2C_FIELD(arg0, s32 *, 0x7C), func_020e0434(arg0 + 0x64, arg1));
    func_02042058(M2C_FIELD(arg0, s32 *, 0x7C), func_020e0434(arg0 + 0x64, arg2));
}
