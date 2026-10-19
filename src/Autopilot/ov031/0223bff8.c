#include <m2c.h>

M2C_UNK ColorEffect_ConfigureBrightnessAdjust(s32, M2C_UNK, M2C_UNK);
s32 ov13_0224128C(M2C_UNK, M2C_UNK);
extern s32 data_ov031_02290d34;

void ov13_02240338(void) {
    data_ov031_02290d34 = ov13_0224128C(0x18, 4);
    ColorEffect_ConfigureBrightnessAdjust(0x04000050, 0x3F, 0x10);
    ColorEffect_ConfigureBrightnessAdjust(0x04001050, 0x3F, 0x10);
}
