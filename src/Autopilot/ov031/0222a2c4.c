#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222788C();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240B04(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_0222D454;

void ov13_0222E6BC(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_02240B04(0);
    ov13_0222788C();
    ov13_02240EFC(1, 1);
    ov13_02240EFC(0, 0x15);
    ov13_0222B8F8(0, 1);
    func_ov031_022274c0(&ov13_0222D454);
}
