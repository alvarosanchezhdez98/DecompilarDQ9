#include <m2c.h>

M2C_UNK LoadToMainBG1ScreenData(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK _Z25CleanInvalidateCacheRangePKvj(M2C_UNK *, M2C_UNK);
extern M2C_UNK data_020fe9cc;

void func_0202adf0(void) {
    _Z25CleanInvalidateCacheRangePKvj(&data_020fe9cc, 0x600);
    LoadToMainBG1ScreenData(&data_020fe9cc, 0, 0x600);
}
