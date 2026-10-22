#include <m2c.h>

M2C_UNK strncpy(s32, s32, M2C_UNK);

void func_02046574(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0) {
        return;
    }
    if (arg1 < 0) {
        return;
    }
    if (arg1 >= 0x10) {
        return;
    }
    strncpy(arg0 + 0x4AC + (arg1 << 6), arg2, 0x3F);
    M2C_FIELD((arg0 + (arg1 << 6)), s8 *, 0x4EB) = 0;
}
