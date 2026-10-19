#include <m2c.h>


void func_020465f0(s32 arg0, s32 arg1, s8 arg2) {
    if (arg1 < 0) {
        return;
    }
    if (arg1 < 0x10) {
        M2C_FIELD((arg0 + arg1), s8 *, 0x902) = arg2;
    }
}
