#include <m2c.h>

s32 func_020d68d0(s32);
M2C_UNK ov13_0223D724();
extern M2C_UNK data_ov031_02290d18;

s32 ov13_0223DC64(void) {
    if (func_020d68d0(M2C_FIELD(&data_ov031_02290d18, s32 *, 4) + 0x1E00) == 2) {
        return 1;
    }
    ov13_0223D724();
    return 0;
}
