#include <m2c.h>

M2C_UNK func_020a0d6c(s32, s32, M2C_UNK, M2C_UNK, s32, s32);

void func_0202edb4(void *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3, s32 arg4) {
    func_020a0d6c(arg0 + 0x194, arg0 + 0x10, arg1, arg2, arg3, arg4);
    M2C_FIELD(arg0, s32 *, 0x168) = (s32) (M2C_FIELD(arg0, s32 *, 0x168) & ~2);
}
