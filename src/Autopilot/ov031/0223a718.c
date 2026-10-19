#include <m2c.h>

M2C_UNK ov13_0223E308();
M2C_UNK ov13_0223E9D8();
extern void *data_ov031_02290d20;

s32 ov13_0223EA58(void) {
    u8 temp_r0;

    temp_r0 = M2C_FIELD(data_ov031_02290d20, u8 *, 0xA90);
    if ((temp_r0 != 1) && (temp_r0 != 0x1A) && (temp_r0 != 0x1D)) {
        return 0;
    }
    ov13_0223E9D8();
    ov13_0223E308();
    M2C_FIELD(data_ov031_02290d20, u8 *, 0xA90) = 2U;
    return 1;
}
