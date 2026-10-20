#include <m2c.h>

s32 func_ov031_0223e218(M2C_UNK, M2C_UNK *, void *, M2C_UNK);
extern void *data_ov031_02290d34;
extern M2C_UNK ov13_02240610;

s32 ov13_022405B8(s16 arg0) {
    void *temp_r4;

    temp_r4 = data_ov031_02290d34;
    if (M2C_FIELD(temp_r4, u8 *, 9) != 0) {
        return 0;
    }
    M2C_FIELD(temp_r4, s32 *, 0) = func_ov031_0223e218(1, &ov13_02240610, temp_r4, 0xC8);
    M2C_FIELD(temp_r4, s16 *, 4) = 0;
    M2C_FIELD(temp_r4, s16 *, 6) = arg0;
    M2C_FIELD(temp_r4, s8 *, 9) = 1;
    return 1;
}
