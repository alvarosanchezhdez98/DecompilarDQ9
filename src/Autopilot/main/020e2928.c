#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;

s8 func_020e2918(void *arg0) {
    if ((M2C_FIELD(&data_02114e54, u8 *, 0x55) != 0) || (func_02012444(&data_02114e30, 1) != 0) || (func_02012444(&data_02114e30, 0x400) != 0) || (func_02012444(&data_02114e30, 0x200) != 0)) {
        return M2C_FIELD(arg0, s8 *, 0x15);
    }
    return -1;
}
