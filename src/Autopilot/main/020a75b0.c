#include <m2c.h>

M2C_UNK func_02032e58();

void func_020a75a0(void *arg0) {
    func_02032e58();
    M2C_FIELD(arg0, u16 *, 0) = (u16) (M2C_FIELD(arg0, u16 *, 0) | 0x8000);
    M2C_FIELD(arg0, s32 *, 0x134) = 0;
    M2C_FIELD(arg0, s32 *, 0x138) = 0;
    M2C_FIELD(arg0, s16 *, 0x13C) = 0;
    M2C_FIELD(arg0, s32 *, 0x140) = 0;
    M2C_FIELD(arg0, s32 *, 0x150) = 0;
    M2C_FIELD(arg0, s32 *, 0x144) = 0;
    M2C_FIELD(arg0, s32 *, 0x148) = 0;
    M2C_FIELD(arg0, s32 *, 0x14C) = 0;
    M2C_FIELD(arg0, s8 *, 0x15A) = 1;
}
