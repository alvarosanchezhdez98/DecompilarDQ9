#include <m2c.h>

M2C_UNK LoadToMainObjStandardPalette(s32, s32, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, M2C_UNK);
s32 func_020a6084();
M2C_UNK memcpy(s32, s32, M2C_UNK);

void func_ov002_0215af64(void *arg0) {
    s32 temp_r4;
    u8 temp_r5;

    temp_r4 = M2C_FIELD(arg0, s32 *, 0x1BD8);
    temp_r5 = (u8) M2C_FIELD(arg0, s16 *, 0x1C06);
    memcpy(temp_r4, func_020a6084() + (temp_r5 << 5) + 0x1E, 2);
    _Z25CleanInvalidateCacheRangePKvj(temp_r4, 2);
    LoadToMainObjStandardPalette(temp_r4, 0x11E, 2);
}
