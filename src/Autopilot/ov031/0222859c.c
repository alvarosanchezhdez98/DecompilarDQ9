#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_022285e4();
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227DE4(M2C_UNK);
extern s8 data_ov031_02290c58;
extern M2C_UNK func_ov031_02228664;

void ov13_0222C9C4(void) {
    data_ov031_02290c58 = 0;
    func_ov031_022285e4();
    ov13_02227DE4(0x12);
    ov13_022277B8(0x3B, -1, 0);
    ov13_022279EC(0x17);
    func_ov031_022274c0(&func_ov031_02228664);
}
