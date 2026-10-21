#include <m2c.h>

M2C_UNK memcpy(s32 *, s32, M2C_UNK);

void func_0204a984(s32 *arg0, M2C_UNK (*arg1)(s32, s32, s32), s32 arg2) {
    s32 sp0;

    if (arg2 != 0) {
        memcpy(&sp0, arg2 + 0xC, 4);
        arg1(arg2 + 0x10, *arg0, sp0);
    }
}
