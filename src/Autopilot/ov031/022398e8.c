#include <m2c.h>

s32 func_020d68b4(s32, M2C_UNK);
M2C_UNK ov13_0223D6A8(M2C_UNK);
M2C_UNK ov13_0223D724();
extern M2C_UNK data_ov031_02290d18;

s32 ov13_0223DC28(void) {
    ov13_0223D6A8(6);
    if (func_020d68b4(M2C_FIELD(&data_ov031_02290d18, s32 *, 4) + 0x1E00, 0xD) == 2) {
        return 1;
    }
    ov13_0223D724();
    return 0;
}
