#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_022272A0();
M2C_UNK ov13_0222788C();
M2C_UNK ov13_02227D18();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
M2C_UNK ov13_0223FA50(s32);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
M2C_UNK ov13_02241D98(s32);
extern M2C_UNK data_ov031_02290c5c;
extern M2C_UNK ov13_0222C44C;
extern M2C_UNK ov13_0222C9C4;
extern M2C_UNK ov13_0222CFD4;
extern M2C_UNK ov13_0222E220;

void ov13_0222D9A4(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    if (ov13_022272A0() == 0) {
        return;
    }
    ov13_02241D98(M2C_FIELD(&data_ov031_02290c5c, s32 *, 8));
    ov13_02227D18();
    ov13_0222788C();
    ov13_0223FA50(M2C_FIELD(&data_ov031_02290c5c, s32 *, 4));
    ov13_02240EFC(1, 1);
    ov13_02240EFC(0, 0x14);
    if (M2C_FIELD(&data_ov031_02290c5c, u8 *, 1) == 0) {
        ov13_0222B8F8(0, 0);
        func_ov031_022274c0(&ov13_0222C44C);
        return;
    }
    switch (M2C_FIELD(&data_ov031_02290c5c, u8 *, 0)) { /* irregular */
    case 0:
        ov13_0222B8F8(0, 1);
        func_ov031_022274c0(&ov13_0222CFD4);
        return;
    case 1:
        ov13_0222B8F8(0, 1);
        func_ov031_022274c0(&ov13_0222C9C4);
        return;
    case 2:
        ov13_0222B8F8(0, 1);
        func_ov031_022274c0(&ov13_0222E220);
        return;
    }
}
