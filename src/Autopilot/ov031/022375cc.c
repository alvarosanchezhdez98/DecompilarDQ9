#include <m2c.h>

s32 func_020d5340(M2C_UNK *, s32);
extern s32 data_ov031_02290d0c;
extern M2C_UNK ov13_0223BA3C;

s32 ov13_0223B90C(void) {
    if (func_020d5340(&ov13_0223BA3C, data_ov031_02290d0c + 0x1374) == 2) {
        return 1;
    }
    return 0;
}
