#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222BC0C();
M2C_UNK ov13_0222BC84(M2C_UNK);
M2C_UNK ov13_0223A840();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223AC20();
extern s8 data_ov031_02290c68;
extern M2C_UNK func_ov031_022298a8;

void ov13_0222DD5C(s32 arg0) {
    if (arg0 == 2) {
        ov13_0223A840();
        data_ov031_02290c68 = 1;
        ov13_0223AC20();
        ov13_0223ABB8(0x10);
    } else if (arg0 == 3) {
        data_ov031_02290c68 = 2;
        ov13_0223AC20();
        ov13_0223ABB8(0x12);
    } else {
        data_ov031_02290c68 = 0;
        ov13_0223AC20();
        ov13_0223ABB8(0x12);
    }
    ov13_0222BC84(0);
    ov13_0222BC0C();
    func_ov031_022274c0(&func_ov031_022298a8);
}
