#include <m2c.h>


void func_0203dd10(s32 arg0, u32 arg1, s32 arg2) {
    if (arg1 < 0x20U) {
        M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0xC) = arg2;
    }
}
