#include <m2c.h>

M2C_UNK func_0205d5d0(void *, M2C_UNK, s32, M2C_UNK, s32);
M2C_UNK func_ov003_0215b964(void *, s32, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov003_0215be20(void *arg0) {
    memset(M2C_FIELD(arg0, s32 *, 0x7C), 0, 0x960);
    func_ov003_0215b964(arg0, M2C_FIELD(arg0, s32 *, 0x7C), 0);
    func_0205d5d0(arg0 + 0xF4, 2, M2C_FIELD(arg0, s32 *, 0x7C), 1, 0);
}
