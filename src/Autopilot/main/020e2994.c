#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_02114e30;

s32 func_020e2984(void) {
    if (func_02012444(&data_02114e30, 2) != 0) {
        return 1;
    }
    return 0;
}
