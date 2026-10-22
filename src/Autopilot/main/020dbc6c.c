#include <m2c.h>

M2C_UNK func_020469b4(s32, s32);
M2C_UNK func_020dbc9c(s32);

void func_020dbc5c(void *arg0, s8 arg1) {
    s32 temp_r4;

    temp_r4 = ((arg1 - 1) * 0x14) + (arg0 + 0x3BC8);
    func_020dbc9c(temp_r4);
    M2C_FIELD(temp_r4, s8 *, 8) = arg1;
    func_020469b4(M2C_FIELD(arg0, s32 *, 0x3704), temp_r4);
}
