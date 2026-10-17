#include <m2c.h>

M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK func_0205de24(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov003_0215de6c(void *, s32);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov003_0215ddc0(void *arg0) {
    func_0205de24(arg0 + 0x98, 0, 2);
    M2C_FIELD(arg0, s16 *, 0x138) = 0xB;
    M2C_FIELD(arg0, s16 *, 0x13A) = 2;
    M2C_FIELD(arg0, s16 *, 0x13C) = 0x14;
    M2C_FIELD(arg0, s16 *, 0x13E) = 0;
    M2C_FIELD(arg0, s16 *, 0x140) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x142) = 2;
    M2C_FIELD(arg0, s16 *, 0x144) = 8;
    M2C_FIELD(arg0, s16 *, 0x146) = 8;
    M2C_FIELD(arg0, s8 *, 0x14F) = 8;
    M2C_FIELD(arg0, s8 *, 0x149) = 0;
    M2C_FIELD(arg0, s8 *, 0x14D) = 1;
    memset(M2C_FIELD(arg0, s32 *, 0x7C), 0, 0x960);
    func_ov003_0215de6c(arg0, M2C_FIELD(arg0, s32 *, 0x7C));
    func_0205d304(arg0 + 0x98, M2C_FIELD(arg0, s32 *, 0x7C), 0, 0, 0, 1, 0, 0);
}
