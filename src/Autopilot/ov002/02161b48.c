#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
s32 func_0205d97c(s32);
extern M2C_UNK data_02114e30;

s32 func_ov002_02161b48(s32 arg0, s32 arg1) {
    if (func_02012444(&data_02114e30, 2) != 0) {
        return 1;
    }
    if ((arg1 != 0) && (func_0205d97c(arg0 + 0xEC8) == 2)) {
        return 1;
    }
    return 0;
}
