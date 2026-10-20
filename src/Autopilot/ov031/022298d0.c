#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02227028();
M2C_UNK ov13_02227F68();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
s32 ov13_0222BC68();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240B04(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern u8 data_ov031_02290c68;
extern M2C_UNK ov13_0222DDE4;
extern M2C_UNK ov13_0222E56C;
extern M2C_UNK ov13_0222E754;

void ov13_0222DCC8(void) {
    if (ov13_02240394(0) != 0) {
        return;
    }
    if (ov13_0222BC68() == 0) {
        return;
    }
    ov13_02227F68();
    ov13_02227028();
    ov13_02240B04(0);
    ov13_02240EFC(0, 0x15);
    ov13_0222B8F8(0, 1);
    if (data_ov031_02290c68 == 0) {
        func_ov031_022274c0(&ov13_0222E754);
        return;
    }
    if (data_ov031_02290c68 == 2) {
        func_ov031_022274c0(&ov13_0222E56C);
        return;
    }
    func_ov031_022274c0(&ov13_0222DDE4);
}
