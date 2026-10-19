#include <m2c.h>

s32 func_020d5340(M2C_UNK *, s32);
extern s32 data_ov031_02290cf8;
extern M2C_UNK ov13_02239D60;

s32 ov13_02239C34(void) {
    if (func_020d5340(&ov13_02239D60, data_ov031_02290cf8 + 0x1648) == 2) {
        return 1;
    }
    return 0;
}
