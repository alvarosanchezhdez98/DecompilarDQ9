#include <m2c.h>

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);

void func_0209e3dc(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = -1;
    M2C_FIELD(arg0, s32 *, 0x68) = -1;
    M2C_FIELD(arg0, s32 *, 0x6C) = -1;
    memset(arg0 + 0x70, 0, 0x10);
    M2C_FIELD(arg0, s32 *, 0x90) = -1;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
    memset(arg0 + 0x9C, 0, 0x400);
    M2C_FIELD(arg0, s32 *, 0x49C) = 0;
    memset(arg0 + 0x4A0, 0, 0x400);
    memset(arg0 + 0x10, 0, 0x54);
    M2C_FIELD(arg0, s32 *, 0x84) = 0;
    M2C_FIELD(arg0, s32 *, 0x88) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
}
