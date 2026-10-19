#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02229e70();
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227DE4(M2C_UNK);
extern s8 data_ov031_02290c6c;
extern M2C_UNK func_ov031_02229ef0;

void ov13_0222E220(void) {
    data_ov031_02290c6c = 0;
    func_ov031_02229e70();
    ov13_02227DE4(0x13);
    ov13_022277B8(0x3C, -1, 0);
    ov13_022279EC(0x1B);
    func_ov031_022274c0(&func_ov031_02229ef0);
}
