#include <m2c.h>

M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_0206e080(s32 arg0, s32 arg1) {
    s32 temp_r4;

    temp_r4 = (arg1 * 0x1C) + arg0;
    memset(temp_r4 + 3, 0, 4);
    memset(temp_r4 + 8, 0, 8);
    memset(temp_r4 + 0x10, 0, 4);
    memset(temp_r4 + 0x14, 0, 8);
}
