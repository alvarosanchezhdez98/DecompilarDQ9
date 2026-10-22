#include <m2c.h>

M2C_UNK func_020c9288();
M2C_UNK func_020c93bc(s32);
M2C_UNK func_020c93d0(s32, M2C_UNK, M2C_UNK, M2C_UNK (*)(), s32);
M2C_UNK func_020dbc0c();

void func_020db228(s32 arg0) {
    func_020c9288();
    func_020c93bc(arg0 + 0x14);
    func_020c93d0(arg0 + 0x14, 0xE1, 0x1E, func_020dbc0c, arg0);
}
