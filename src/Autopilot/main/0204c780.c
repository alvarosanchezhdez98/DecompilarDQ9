#include <m2c.h>

M2C_UNK memcpy(s32, s32, M2C_UNK);
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);

void func_0204c770(s32 arg0, s32 arg1) {
    memset(arg0 + 0xDB, 0, 4);
    if (arg1 == 0) {
        return;
    }
    memcpy(arg0 + 0xDB, arg1, 4);
}
