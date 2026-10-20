#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222788C();
M2C_UNK ov13_02227D18();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
M2C_UNK ov13_0223FA50(s32);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290c50;
extern M2C_UNK ov13_0222D454;
extern M2C_UNK ov13_022368D8;

void ov13_0222C86C(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_02227D18();
    ov13_0222788C();
    ov13_0223FA50(M2C_FIELD(&data_ov031_02290c50, s32 *, 4));
    ov13_02240EFC(1, 1);
    ov13_02240EFC(0, 0x14);
    switch (M2C_FIELD(&data_ov031_02290c50, u8 *, 0)) { /* irregular */
    case 0:
        ov13_0222B8F8(1, 0);
        func_ov031_022274c0(&ov13_022368D8);
        return;
    case 1:
        ov13_0222B8F8(0, 0);
        func_ov031_022274c0(&ov13_0222D454);
        return;
    }
}
