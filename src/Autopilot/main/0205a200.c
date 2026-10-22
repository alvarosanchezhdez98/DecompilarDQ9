#include <m2c.h>

s32 func_020b01a4(s32, s32);

s32 func_0205a1f0(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == 0) {
        return 1;
    }
    if (arg1 == 0) {
        return 1;
    }
    if (arg2 == 0) {
        return 1;
    }
    if (func_020b01a4(arg1, arg0) == 0) {
        return 1;
    }
    return 0;
}
