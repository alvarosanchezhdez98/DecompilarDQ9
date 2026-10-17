#include <m2c.h>

M2C_UNK func_0203c108(void *, s32);
s32 func_020e0434(s32, s32);
s32 func_ov000_021719f8(void *);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_ov000_0217f480(void *arg0) {
    void *temp_r4;

    temp_r4 = arg0 + 8;
    memset(temp_r4 + 8, 0, 8);
    M2C_FIELD(temp_r4, s8 *, 0x10) = 0;
    M2C_FIELD((temp_r4 + M2C_FIELD(arg0, s8 *, 0x18)), s8 *, 8) = 0xD;
    M2C_FIELD(temp_r4, s8 *, 0x10) = (s8) (M2C_FIELD(temp_r4, s8 *, 0x10) + 1);
    M2C_FIELD((temp_r4 + M2C_FIELD(arg0, s8 *, 0x18)), s8 *, 8) = 0x64;
    M2C_FIELD(temp_r4, s8 *, 0x14) = 6;
    M2C_FIELD(temp_r4, s16 *, 0x1E) = 0;
    if (func_ov000_021719f8(arg0) == 0) {
        func_0203c108(arg0 + 0x50, func_020e0434(M2C_FIELD(arg0, s32 *, 4), 0x7531));
    }
    M2C_FIELD(arg0, u8 *, 0x24) = (u8) (M2C_FIELD(arg0, u8 *, 0x24) & ~4);
}
