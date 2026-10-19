#include <m2c.h>

M2C_UNK LoadToSubBG1ScreenData(s32, M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, M2C_UNK);
M2C_UNK ov13_0223FA50(s32);
M2C_UNK ov13_022425D0(M2C_UNK, M2C_UNK);
extern s32 data_ov031_02290d04;

void ov13_0223B73C(M2C_UNK arg0) {
    _Z25CleanInvalidateCacheRangePKvj(data_ov031_02290d04, 0x600);
    LoadToSubBG1ScreenData(data_ov031_02290d04, 0, 0x600);
    ov13_0223FA50(data_ov031_02290d04);
    ov13_022425D0(1, arg0);
}
