#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
s32 func_0205da38(s32, M2C_UNK);
extern M2C_UNK data_02114e30;

s32 func_ov003_0215dcb8(s32 arg0) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = func_0205da38(arg0 + 0x98, 0x14);
    temp_r4 = func_02012444(&data_02114e30, 1);
    if ((temp_r5 | (temp_r4 | func_02012444(&data_02114e30, 0x400))) != 0) {
        return 1;
    }
    return 0;
}
