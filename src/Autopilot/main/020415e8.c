#include <m2c.h>

M2C_UNK func_02037d10();

void func_020415d8(void *arg0) {
    func_02037d10();
    M2C_FIELD(arg0, s16 *, 0x2D0) = 0;
    M2C_FIELD(arg0, s32 *, 0x2D4) = 0;
    M2C_FIELD(arg0, s32 *, 0x2E4) = 0;
    M2C_FIELD(arg0, s8 *, 0x2E8) = 0;
    M2C_FIELD(arg0, s32 *, 0x2F4) = 0;
    M2C_FIELD(arg0, s32 *, 0x2EC) = 0x7A;
    M2C_FIELD(arg0, s8 *, 0x2F0) = 0;
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x4000);
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) & ~0x80);
}
