#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0222b48c();
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227E40();
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern s8 data_ov031_02290c88;
extern M2C_UNK func_ov031_0222b4f8;

void ov13_0222F848(void) {
    data_ov031_02290c88 = 0;
    func_ov031_0222b48c();
    ov13_02227E40();
    ov13_022279EC(0x23);
    ov13_0223ABB8(0x10);
    func_ov031_022274c0(&func_ov031_0222b4f8);
}
