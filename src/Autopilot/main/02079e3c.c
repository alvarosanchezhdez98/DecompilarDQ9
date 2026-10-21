#include <m2c.h>

M2C_UNK func_020797e8();
s32 func_02079e60(s32, M2C_UNK, M2C_UNK (*)());

void func_02079e2c(s32 arg0, M2C_UNK arg1) {
    if (func_02079e60(arg0, arg1, func_020797e8) != 0) {
        return;
    }
    func_02079e60(arg0 + 0xC, arg1, func_020797e8);
}
