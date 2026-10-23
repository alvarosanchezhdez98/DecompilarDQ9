#include <m2c.h>

M2C_UNK func_0205d304(void *, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
void *func_0205d81c(void *, M2C_UNK);
M2C_UNK func_0205de24(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_ov003_02169d10(void *, s32, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov003_02169c3c(void *arg0) {
    func_0205de24(arg0 + 0xE4, 0, 2);
    M2C_FIELD(arg0, s16 *, 0x184) = 0xE;
    M2C_FIELD(arg0, s16 *, 0x186) = 7;
    M2C_FIELD(arg0, s16 *, 0x188) = 0x11;
    M2C_FIELD(arg0, s16 *, 0x18A) = 7;
    M2C_FIELD(arg0, s16 *, 0x18C) = 8;
    M2C_FIELD(arg0, s16 *, 0x18E) = 0x10;
    M2C_FIELD(arg0, s16 *, 0x190) = 0xC;
    M2C_FIELD(arg0, s16 *, 0x192) = 0xE;
    M2C_FIELD(arg0, s8 *, 0x195) = 2;
    M2C_FIELD(arg0, s8 *, 0x199) = 1;
    M2C_FIELD(arg0, s8 *, 0x4EE) = 3;
    memset(M2C_FIELD(arg0, s32 *, 0x7C), 0, 0x960);
    func_ov003_02169d10(arg0, M2C_FIELD(arg0, s32 *, 0x7C), 0);
    func_0205d304(arg0 + 0xE4, M2C_FIELD(arg0, s32 *, 0x7C), 0, 0, 0, 0, 0, 1);
    M2C_FIELD(func_0205d81c(arg0 + 0xE4, 2), s8 *, 0xC6) = 0;
}
