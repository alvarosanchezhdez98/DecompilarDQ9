#include <m2c.h>

M2C_UNK LoadToMainOAM(s32, M2C_UNK, M2C_UNK);
M2C_UNK LoadToSubOAM(s32, M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, M2C_UNK);
extern s32 data_ov031_02290d60;

void ov13_02241D04(void) {
    _Z25CleanInvalidateCacheRangePKvj(data_ov031_02290d60, 0x800);
    LoadToMainOAM(data_ov031_02290d60, 0, 0x400);
    LoadToSubOAM(data_ov031_02290d60 + 0x400, 0, 0x400);
}
