#include <m2c.h>

M2C_UNK memcpy(s32, M2C_UNK, s8);

void func_02011468(void *arg0, s8 arg1, M2C_UNK arg2) {
    memcpy(arg0 + 0x5718, arg2, arg1);
    M2C_FIELD(arg0, s8 *, 0x571C) = arg1;
}
