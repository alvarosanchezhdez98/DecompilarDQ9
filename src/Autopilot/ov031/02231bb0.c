#include <m2c.h>

M2C_UNK func_ov031_02222b0c(M2C_UNK);
M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02231c0c();
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02227964(M2C_UNK);
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227E40();
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern s8 data_ov031_02290cb8;
extern M2C_UNK func_ov031_02231cb4;

void ov13_02235F80(void) {
    data_ov031_02290cb8 = 0;
    func_ov031_02231c0c();
    ov13_02227E40();
    ov13_022277B8(0x37, -1, 0);
    ov13_02227964(2);
    ov13_022279EC(0x24);
    func_ov031_02222b0c(0);
    ov13_0223ABB8(0xB);
    func_ov031_022274c0(&func_ov031_02231cb4);
}
