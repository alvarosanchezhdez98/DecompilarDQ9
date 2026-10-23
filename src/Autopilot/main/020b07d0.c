#include <m2c.h>

M2C_UNK LoadToMainObjExtendedPalette(s32, M2C_UNK, s32);
M2C_UNK LoadToMainObjStandardPalette(s32, M2C_UNK, s32);
M2C_UNK LoadToSubObjExtendedPalette(s32, M2C_UNK, s32);
M2C_UNK LoadToSubObjStandardPalette(s32, M2C_UNK, s32);
M2C_UNK LoadToTexturePalette(s32, M2C_UNK, s32);
M2C_UNK MemoryMapMainObjExtendedPalette();
M2C_UNK MemoryMapSubObjExtendedPalette();
M2C_UNK MemoryMapTexturePalette();
M2C_UNK MemoryUnmapMainObjExtendedPalette();
M2C_UNK MemoryUnmapSubObjExtendedPalette();
M2C_UNK MemoryUnmapTexturePalette();
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, s32);
M2C_UNK func_020b035c(void *, s32, M2C_UNK);

void func_020b07c0(void *arg0, M2C_UNK arg1, s32 arg2, void *arg3) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r4 = M2C_FIELD(arg0, s32 *, 0xC);
    temp_r5 = M2C_FIELD(arg0, s32 *, 8);
    _Z25CleanInvalidateCacheRangePKvj(temp_r4, temp_r5);
    switch (arg2) {                                 /* irregular */
    case 1:
        if (M2C_FIELD(arg0, s32 *, 4) != 0) {
            MemoryMapMainObjExtendedPalette();
            LoadToMainObjExtendedPalette(temp_r4, arg1, temp_r5);
            MemoryUnmapMainObjExtendedPalette();
        } else {
            LoadToMainObjStandardPalette(temp_r4, arg1, temp_r5);
        }
        break;
    case 2:
        if (M2C_FIELD(arg0, s32 *, 4) != 0) {
            MemoryMapSubObjExtendedPalette();
            LoadToSubObjExtendedPalette(temp_r4, arg1, temp_r5);
            MemoryUnmapSubObjExtendedPalette();
        } else {
            LoadToSubObjStandardPalette(temp_r4, arg1, temp_r5);
        }
        break;
    case 0:
        MemoryMapTexturePalette();
        LoadToTexturePalette(temp_r4, arg1, temp_r5);
        MemoryUnmapTexturePalette();
        break;
    }
    M2C_FIELD(arg3, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(arg3, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
    func_020b035c(arg3, arg2, arg1);
}
