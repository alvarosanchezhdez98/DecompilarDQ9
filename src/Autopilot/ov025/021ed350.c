#include <m2c.h>


void func_ov025_021ed350(s32 arg0, s32 arg1, s16 arg2) {
    M2C_FIELD((arg0 + (arg1 * 2)), s16 *, 0x80) = arg2;
}
