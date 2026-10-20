#include <m2c.h>

M2C_UNK memcpy(s32, M2C_UNK, s32);
s32 strlen(M2C_UNK);

void func_020d9dc4(s32 arg0, M2C_UNK arg1) {
    memcpy(arg0 + 0x10, arg1, strlen(arg1));
}
