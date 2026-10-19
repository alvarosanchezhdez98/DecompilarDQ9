#include <m2c.h>

s32 func_020d507c(M2C_UNK *, s32);
M2C_UNK ov13_0223D6A8(M2C_UNK);
M2C_UNK ov13_0223D724();
extern M2C_UNK data_ov031_02290d18;
extern M2C_UNK ov13_0223D788;

s32 ov13_0223D744(void) {
    ov13_0223D6A8(3);
    if (func_020d507c(&ov13_0223D788, M2C_FIELD(&data_ov031_02290d18, s32 *, 4)) == 2) {
        return 1;
    }
    ov13_0223D724();
    ov13_0223D6A8(9);
    return 0;
}
