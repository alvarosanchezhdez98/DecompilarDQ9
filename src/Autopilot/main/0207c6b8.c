#include <m2c.h>


void func_0207c6a8(s32 arg0, u32 arg1, s8 arg2) {
    if (arg1 <= 7U) {
        M2C_FIELD((arg0 + arg1), s8 *, 0xC28) = arg2;
    }
}
