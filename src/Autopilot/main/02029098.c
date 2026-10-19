#include <m2c.h>

M2C_UNK _Z25CleanInvalidateCacheRangePKvj(s32, M2C_UNK);
extern s32 data_020fe9a4;

void func_02029088(void) {
    if (data_020fe9a4 == 0) {
        return;
    }
    _Z25CleanInvalidateCacheRangePKvj(data_020fe9a4, 0x6000);
}
