#include <m2c.h>

M2C_UNK ColorEffect_ChangeBrightness(s32, s8);
M2C_UNK func_ov031_0223e2b8(M2C_UNK, M2C_UNK *);
extern void *data_ov031_02290d10;
extern M2C_UNK ov13_0223C26C;

void ov13_0223C20C(M2C_UNK arg0) {
    M2C_FIELD(data_ov031_02290d10, s8 *, 0x1A) = (s8) (M2C_FIELD(data_ov031_02290d10, s8 *, 0x1A) - 1);
    ColorEffect_ChangeBrightness(0x04000050, M2C_FIELD(data_ov031_02290d10, s8 *, 0x1A));
    if ((s32) M2C_FIELD(data_ov031_02290d10, s8 *, 0x1A) > -0xC) {
        return;
    }
    func_ov031_0223e2b8(arg0, &ov13_0223C26C);
}
