#include <m2c.h>


void func_02072e34(s32 arg0, void *arg1) {
    s32 temp_r3;

    temp_r3 = arg0 * 0xC;
    M2C_FIELD(arg1, s32 *, 0) = arg0;
    M2C_FIELD(arg1, s32 *, 4) = (s32) (temp_r3 + 0x13);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (temp_r3 + 0x14);
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_r3 + 0x15);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_r3 + 0x16);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (temp_r3 + 0x17);
    M2C_FIELD(arg1, s32 *, 0x18) = (s32) (temp_r3 + 0x19);
    M2C_FIELD(arg1, s32 *, 0x1C) = (s32) (temp_r3 + 0x1B);
    M2C_FIELD(arg1, s32 *, 0x20) = (s32) (temp_r3 + 0x1C);
    M2C_FIELD(arg1, s32 *, 0x24) = (s32) (temp_r3 + 0x1D);
    M2C_FIELD(arg1, s32 *, 0x28) = -1;
}
