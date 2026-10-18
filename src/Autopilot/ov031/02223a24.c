#include <m2c.h>

M2C_UNK LoadToMainBG1ScreenData(s32, M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, M2C_UNK);
M2C_UNK ov13_022425D0(M2C_UNK, M2C_UNK);
extern s32 data_ov031_02250bf4;

void ov13_02227E70(M2C_UNK arg0) {
    _Z25CleanInvalidateCacheRangePKvj(data_ov031_02250bf4, 0xC0);
    LoadToMainBG1ScreenData(data_ov031_02250bf4, 0, 0xC0);
    ov13_022425D0(1, arg0);
}
