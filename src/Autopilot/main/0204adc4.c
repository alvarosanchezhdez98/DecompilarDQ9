#include <m2c.h>

M2C_UNK memcpy(s32, s32, M2C_UNK);

void func_0204adb4(void *arg0, M2C_UNK (*arg1)(s32, M2C_UNK, s32), s32 arg2) {
    memcpy(arg0 + 8, arg2 + 0xC, 4);
    arg1(arg2 + 0x10, 0, M2C_FIELD(arg0, s32 *, 8));
}
