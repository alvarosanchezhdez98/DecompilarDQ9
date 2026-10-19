#include <m2c.h>

s32 ov13_0224128C(s32, M2C_UNK);
extern s32 data_ov031_02290cf8;

void ov13_02239B00(void) {
    if (data_ov031_02290cf8 != 0) {
        return;
    }
    data_ov031_02290cf8 = ov13_0224128C(0x1E60, 0x20);
}
