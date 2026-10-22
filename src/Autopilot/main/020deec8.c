#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_020de6c8(M2C_UNK, M2C_UNK, s32);

s32 func_020deeb8(M2C_UNK arg0, void *arg1, s32 arg2, M2C_UNK arg3, s32 arg4) {
    func_020de6c8(arg0, arg3, arg4);
    memset(arg1, 0, 0xC);
    M2C_FIELD(arg1, s32 *, 0xC) = arg2;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    return 1;
}
