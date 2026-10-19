#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02234354();
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227DE4(M2C_UNK);
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern s8 data_ov031_02290cdc;
extern M2C_UNK func_ov031_022343d4;

void ov13_02238694(void) {
    data_ov031_02290cdc = 0;
    func_ov031_02234354();
    ov13_02227DE4(8);
    ov13_022279EC(0x29);
    ov13_0223ABB8(0x10);
    func_ov031_022274c0(&func_ov031_022343d4);
}
