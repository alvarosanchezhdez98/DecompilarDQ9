#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
s32 func_0205d97c(s32);
extern M2C_UNK data_02114e30;

s32 func_ov003_0215dd00(s32 arg0) {
    if (func_02012444(&data_02114e30, 2) != 0) {
        return 1;
    }
    if (func_0205d97c(arg0 + 0x98) == 2) {
        return 1;
    }
    return 0;
}
