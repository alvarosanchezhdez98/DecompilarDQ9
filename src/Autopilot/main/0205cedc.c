#include <m2c.h>

s32 func_0205bd20(s32, M2C_UNK);
s32 func_0205c570(s32);

s32 func_0205cecc(s32 arg0) {
    if (func_0205bd20(arg0 + 0x20, 1) == 0) {
        return -1;
    }
    return func_0205c570(arg0 + 0x1C);
}
