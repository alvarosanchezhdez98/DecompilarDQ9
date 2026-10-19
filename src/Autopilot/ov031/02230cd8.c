#include <m2c.h>

M2C_UNK ov13_02233DCC();
extern M2C_UNK data_ov031_02290ca0;

void ov13_022350A8(void) {
    s32 var_r4;
    u8 temp_r0;
    void *temp_r1;

    var_r4 = 0;
    do {
        temp_r1 = M2C_FIELD(&data_ov031_02290ca0, s32 *, 8) + var_r4;
        temp_r0 = M2C_FIELD(temp_r1, u8 *, 4);
        if (temp_r0 != 0) {
            M2C_FIELD(temp_r1, u8 *, 4) = (u8) (temp_r0 - 1);
            if (M2C_FIELD((M2C_FIELD(&data_ov031_02290ca0, s32 *, 8) + var_r4), u8 *, 4) == 0) {
                ov13_02233DCC();
            }
        }
        var_r4 += 1;
    } while (var_r4 < 4);
}
