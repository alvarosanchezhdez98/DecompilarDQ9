#include <m2c.h>

M2C_UNK LoadToMainBG2ScreenData(void *, M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(void *, M2C_UNK);
extern void *data_ov031_02290ce8;

void ov13_02239324(void) {
    if (M2C_FIELD(data_ov031_02290ce8, u8 *, 0x604) == 0) {
        return;
    }
    _Z25CleanInvalidateCacheRangePKvj(data_ov031_02290ce8 + 4, 0x600);
    LoadToMainBG2ScreenData(data_ov031_02290ce8 + 4, 0, 0x600);
    M2C_FIELD(data_ov031_02290ce8, u8 *, 0x604) = 0U;
}
