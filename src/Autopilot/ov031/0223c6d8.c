#include <m2c.h>

M2C_UNK LoadToMainBG0CharacterData(s32, M2C_UNK, M2C_UNK);
M2C_UNK LoadToSubBG0CharacterData(s32, M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, M2C_UNK);
extern void *data_ov031_02290d38;

void ov13_02240A18(s32 arg0, u8 *arg1) {
    if (*arg1 == 0) {
        return;
    }
    if (arg1 == (data_ov031_02290d38 + 0x67C)) {
        _Z25CleanInvalidateCacheRangePKvj(M2C_FIELD(data_ov031_02290d38, s32 *, 0x638), 0x6000);
        LoadToMainBG0CharacterData(M2C_FIELD(data_ov031_02290d38, s32 *, 0x638), 0, 0x6000);
    } else {
        _Z25CleanInvalidateCacheRangePKvj(M2C_FIELD(data_ov031_02290d38, s32 *, 0x668), 0x3000);
        LoadToSubBG0CharacterData(M2C_FIELD(data_ov031_02290d38, s32 *, 0x668), 0x3000, 0x3000);
    }
    *arg1 = 0;
}
