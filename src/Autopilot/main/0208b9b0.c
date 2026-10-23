#include <m2c.h>

M2C_UNK func_0204af64(void *);
M2C_UNK func_0205a444(void *);
M2C_UNK func_020dfc40(s32);
M2C_UNK func_0208d82c(void *);

void func_0208b9a0(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    func_020dfc40(arg0 + 4);
    func_0208d82c(arg0 + 0x1C);
    M2C_FIELD(arg0, s8 *, 0x3C) = 0;
    M2C_FIELD(arg0, s8 *, 0x3D) = 0;
    func_0204af64(arg0 + 0x40);
    func_0205a444(arg0 + 0x60);
    M2C_FIELD(arg0, s32 *, 0xB4) = 0;
    M2C_FIELD(arg0, u32 *, 0xB8) = (u32) ((u32) (*(s32 *)0x04001000 & 0x1F00) >> 8);
    M2C_FIELD(arg0, s32 *, 0xBC) = -1;
    M2C_FIELD(arg0, s32 *, 0xC0) = -1;
    M2C_FIELD(arg0, s32 *, 0xCC) = 0x3F800000;
    M2C_FIELD(arg0, s32 *, 0xC8) = 0;
    M2C_FIELD(arg0, s16 *, 0xD2) = -1;
    M2C_FIELD(arg0, s8 *, 0xD4) = 0;
    M2C_FIELD(arg0, s8 *, 0xD5) = 0;
    M2C_FIELD(arg0, s8 *, 0xD6) = 0;
    M2C_FIELD(arg0, s8 *, 0xD7) = 0;
    M2C_FIELD(arg0, s8 *, 0xD8) = 1;
    M2C_FIELD(arg0, s8 *, 0xD9) = 0;
    M2C_FIELD(arg0, s16 *, 0xDA) = 0;
    M2C_FIELD(arg0, s8 *, 0xDC) = 1;
    M2C_FIELD(arg0, s8 *, 0xDD) = 0;
    M2C_FIELD(arg0, s8 *, 0xDE) = 0;
    M2C_FIELD(arg0, s8 *, 0xDF) = arg1;
    M2C_FIELD(arg0, s8 *, 0xE0) = 0;
}
