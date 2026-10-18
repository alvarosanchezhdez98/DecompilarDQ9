#include <m2c.h>

M2C_UNK func_ov031_02222b0c(M2C_UNK);
M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02231594();
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227E40();
extern s8 data_ov031_02290cb0;
extern M2C_UNK func_ov031_02231614;

void ov13_02235928(void) {
    data_ov031_02290cb0 = 0;
    func_ov031_02231594();
    ov13_02227E40();
    ov13_022279EC(0x2A);
    func_ov031_02222b0c(2);
    func_ov031_022274c0(&func_ov031_02231614);
}
