#include <m2c.h>

M2C_UNK Mat3x3_WriteIdentity(void *);
M2C_UNK func_020a0d58(void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
M2C_UNK func_0202e5d8(void *, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_0202e9a4(void *, M2C_UNK);
M2C_UNK func_0202eab8(void *);

void func_0202df68(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 1;
    M2C_FIELD(arg0, s32 *, 0x64) = 0x1555;
    M2C_FIELD(arg0, s32 *, 0x68) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0x6C) = 0x190000;
    func_0202e9a4(arg0, 0xF000);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0x4000;
    M2C_FIELD(arg0, s32 *, 0xC) = 0x8000;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0x800;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0x1000;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    func_0202eab8(arg0);
    func_0202e5d8(arg0, 0, 0x6000, 0xB000);
    memset(arg0 + 0xF0, 0, 0x30);
    M2C_FIELD(arg0, s16 *, 0x7C) = 0;
    M2C_FIELD(arg0, s32 *, 0x1E4) = 0;
    M2C_FIELD(arg0, s32 *, 0x1E8) = 0;
    M2C_FIELD(arg0, s32 *, 0x168) = 0;
    Mat3x3_WriteIdentity(arg0 + 0x144);
    func_020a0d58(arg0 + 0x16C);
    func_020a0d58(arg0 + 0x194);
    func_020a0d58(arg0 + 0x1BC);
    M2C_FIELD(arg0, s32 *, 0x1F0) = (s32) M2C_FIELD(arg0, s32 *, 0x58);
    M2C_FIELD(arg0, s32 *, 0x1F4) = 0;
    M2C_FIELD(arg0, s8 *, 0x1F8) = 0;
    M2C_FIELD(arg0, s16 *, 0x1FA) = 0;
    M2C_FIELD(arg0, s32 *, 0x1FC) = 0;
    M2C_FIELD(arg0, s32 *, 0x200) = 0x3F800000;
    M2C_FIELD(arg0, s32 *, 0x204) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0x1EC) = 0;
    M2C_FIELD(arg0, s16 *, 0x1EE) = 0;
    M2C_FIELD(arg0, s8 *, 0x20C) = 0;
    M2C_FIELD(arg0, s16 *, 0x20E) = 0;
    M2C_FIELD(arg0, s16 *, 0x210) = 0;
    M2C_FIELD(arg0, s16 *, 0x212) = 0;
    M2C_FIELD(arg0, s16 *, 0x214) = 0;
    M2C_FIELD(arg0, s16 *, 0x216) = 0;
}
