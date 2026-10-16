#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_02056b48();

void func_02056d10(void *arg0) {
    func_02056b48();
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
    M2C_FIELD(arg0, s8 *, 0x39) = 0;
    M2C_FIELD(arg0, s8 *, 0x3A) = 0;
    M2C_FIELD(arg0, s8 *, 0x3B) = 0;
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x154) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    memset(arg0 + 0xC4, 0, 0xC);
    memset(arg0 + 0xD0, 0, 0xC);
    memset(arg0 + 0xDC, 0, 0xC);
}
