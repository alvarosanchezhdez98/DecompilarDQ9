#include <m2c.h>

s32 func_020420e8(s32);
s32 func_020421a0();
M2C_UNK func_02046380(s32);
M2C_UNK func_020465c0(s32, s16, s32);
M2C_UNK func_02046608(s32, u32, s32, s32, s32, s32, s32);
M2C_UNK func_0204f41c(void *, s16, s16, s32, u32, u32, void *, void *, s32);
s32 func_02072a68(s32, s16);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_02081a14(void *arg0, void *arg1, void *arg2) {
    s32 temp_r8;
    s32 var_r1;
    u32 temp_r0;
    u32 var_r4;

    var_r4 = (u32) (M2C_FIELD(arg2, u8 *, 0x13) << 0x18) >> 0x1C;
    if (M2C_FIELD(arg2, u8 *, 0x2A) & 4) {
        var_r4 = 5;
    }
    temp_r8 = func_020421a0();
    memset(M2C_FIELD(arg0, s32 *, 0x18), 0, 0x960);
    func_02046380(temp_r8);
    func_020465c0(temp_r8, M2C_FIELD(arg2, s16 *, 0x10), M2C_FIELD(arg2, s32 *, 0));
    func_02046608(temp_r8, (u32) (M2C_FIELD(arg2, u8 *, 0x13) << 0x1C) >> 0x1C, func_02072a68(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg2, s16 *, 0xE)), M2C_FIELD(arg0, s32 *, 0x18), 0x100, 0, 0);
    var_r1 = 0;
    if (((u32) (M2C_FIELD(arg2, u8 *, 0x14) << 0x1E) >> 0x1E) != 0) {
        var_r1 = func_020420e8(M2C_FIELD(arg0, s32 *, 0x18));
    }
    temp_r0 = (u32) (M2C_FIELD(arg2, u8 *, 0x13) << 0x1C) >> 0x1C;
    M2C_FIELD(arg1, s16 *, 0xB4) = (s16) temp_r0;
    M2C_FIELD(arg1, s16 *, 0xB6) = (s16) (temp_r0 + 1);
    func_0204f41c(arg1, (s16) ((M2C_FIELD(arg2, s16 *, 6) + M2C_FIELD(arg2, s16 *, 0x28)) - var_r1), M2C_FIELD(arg2, s16 *, 8), M2C_FIELD(arg0, s32 *, 0x18), (u32) (M2C_FIELD(arg2, u8 *, 0x13) << 0x1C) >> 0x1C, var_r4, arg2 + 0xA, arg2 + 0xC, 0);
}
