#include <m2c.h>

M2C_UNK func_020401e4();
M2C_UNK func_02064e20(s32);
M2C_UNK func_0206da74(s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_0203cfb4(void *arg0) {
    func_020401e4();
    func_02064e20(arg0 + 0x90);
    func_0206da74(arg0 + 0x94);
    memset(arg0 + 0xC, 0, 0x80);
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg0, s8 *, 0x9C) = 0;
}
