#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0222a1a4();
M2C_UNK ov13_022279EC(M2C_UNK);
extern s8 data_ov031_02290c70;
extern M2C_UNK func_ov031_0222a210;

void ov13_0222E56C(void) {
    data_ov031_02290c70 = 0;
    func_ov031_0222a1a4();
    ov13_022279EC(0x21);
    func_ov031_022274c0(&func_ov031_0222a210);
}
