#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02227028();
s32 ov13_022272A0();
M2C_UNK ov13_0222788C();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
M2C_UNK ov13_0223B940();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240B04(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern u8 data_ov031_02290ce4;
extern M2C_UNK ov13_022368D8;
extern M2C_UNK ov13_02238694;
extern M2C_UNK ov13_022388A0;

void ov13_02238F38(void) {
    if (ov13_02240394(0) != 0) {
        return;
    }
    if ((data_ov031_02290ce4 == 2) && (ov13_02240394(1) != 0)) {
        return;
    }
    if (ov13_022272A0() == 0) {
        return;
    }
    ov13_0223B940();
    ov13_02227028();
    ov13_02240B04(0);
    if ((u32) (u8) (data_ov031_02290ce4 + 0xFE) <= 1U) {
        ov13_0222788C();
        ov13_02240EFC(1, 1);
    }
    ov13_02240EFC(0, 0x15);
    if (data_ov031_02290ce4 == 2) {
        ov13_0222B8F8(2, 1);
        func_ov031_022274c0(&ov13_022368D8);
        return;
    }
    if (data_ov031_02290ce4 == 3) {
        ov13_0222B8F8(2, 1);
        func_ov031_022274c0(&ov13_022388A0);
        return;
    }
    ov13_0222B8F8(0, 0);
    func_ov031_022274c0(&ov13_02238694);
}
