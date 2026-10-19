#include <m2c.h>


void func_020465c0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 < 0) {
        return;
    }
    if (arg1 < 0x10) {
        M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0x8B0) = arg2;
    }
}
