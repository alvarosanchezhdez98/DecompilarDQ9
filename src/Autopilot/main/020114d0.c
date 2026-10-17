#include <m2c.h>

M2C_UNK memcpy(s32, M2C_UNK, s8);

void func_020114c0(void *arg0, s8 arg1, M2C_UNK arg2) {
    memcpy(arg0 + 0x571D, arg2, arg1);
    M2C_FIELD(arg0, s8 *, 0x5721) = arg1;
}
