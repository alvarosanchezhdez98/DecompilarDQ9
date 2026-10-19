#include <m2c.h>


void func_ov017_021a7c28(void *arg0, void *arg1) {
    M2C_FIELD(arg0, u8 *, 0xC) = (u8) M2C_FIELD(arg1, u8 *, 0);
    M2C_FIELD(arg0, u8 *, 0xD) = (u8) M2C_FIELD(arg1, u8 *, 1);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) M2C_FIELD(arg1, u16 *, 4);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(arg0, u8 *, 0x18) = (u8) M2C_FIELD(arg1, u8 *, 0xC);
    M2C_FIELD(arg0, u8 *, 0x19) = (u8) M2C_FIELD(arg1, u8 *, 0xD);
    M2C_FIELD(arg0, u8 *, 0x1A) = (u8) M2C_FIELD(arg1, u8 *, 0xE);
    M2C_FIELD(arg0, u8 *, 0x1B) = (u8) M2C_FIELD(arg1, u8 *, 0xF);
    M2C_FIELD(arg0, s16 *, 0x1C) = (s16) M2C_FIELD(arg1, s16 *, 0x10);
    M2C_FIELD(arg0, u8 *, 0x1E) = (u8) M2C_FIELD(arg1, u8 *, 0x12);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
}
