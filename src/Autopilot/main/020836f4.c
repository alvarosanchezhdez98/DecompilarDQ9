#include <m2c.h>


void func_020836e4(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg0, u16 *, 0x14) = (u16) M2C_FIELD(arg1, u16 *, 0x14);
    M2C_FIELD(arg0, u16 *, 0x16) = (u16) M2C_FIELD(arg1, u16 *, 0x16);
    M2C_FIELD(arg0, s16 *, 0x18) = (s16) M2C_FIELD(arg1, s16 *, 0x18);
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) M2C_FIELD(arg1, u16 *, 0x1A);
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16) M2C_FIELD(arg1, u16 *, 0x1C);
}
