#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222788C();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_022368D8;

void ov13_02235494(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_0222788C();
    ov13_02240EFC(1, 1);
    ov13_02240EFC(0, 0x14);
    ov13_0222B8F8(2, 1);
    func_ov031_022274c0(&ov13_022368D8);
}
