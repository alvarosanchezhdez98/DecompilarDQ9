#include <m2c.h>

M2C_UNK func_020426bc(s32, void *, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void *func_02052a10(void *arg0) {
    memset(arg0 + 0x141, 0, 0xC);
    func_020426bc(M2C_FIELD(arg0, s32 *, 0x134), arg0 + 0x141, 1);
    return arg0 + 0x141;
}
