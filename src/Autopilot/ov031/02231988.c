#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_022319c4();
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227E40();
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern s8 data_ov031_02290cb4;
extern M2C_UNK func_ov031_02231a44;

void ov13_02235D58(void) {
    data_ov031_02290cb4 = 0;
    func_ov031_022319c4();
    ov13_02227E40();
    ov13_022279EC(0x26);
    ov13_0223ABB8(0x10);
    func_ov031_022274c0(&func_ov031_02231a44);
}
