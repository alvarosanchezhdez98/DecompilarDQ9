#include <m2c.h>

M2C_UNK func_020c9be0();
M2C_UNK memcpy(s32, M2C_UNK, s32);

void func_ov025_021e2114(void *arg0, M2C_UNK arg1, s32 arg2) {
    if (arg2 > 0xC) {
        func_020c9be0();
    }
    memcpy(arg0 + 8, arg1, arg2);
    M2C_FIELD(arg0, s8 *, 0x14) = (s8) arg2;
}
