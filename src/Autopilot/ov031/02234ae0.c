#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02227258();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223AC20();
extern u8 data_ov031_02290ce4;
extern M2C_UNK func_ov031_02234b2c;

void ov13_02238E60(void) {
    if (data_ov031_02290ce4 != 0) {
        return;
    }
    if (ov13_02227258() != 0) {
        return;
    }
    data_ov031_02290ce4 = 2;
    ov13_0223AC20();
    ov13_0223ABB8(7);
    func_ov031_022274c0(&func_ov031_02234b2c);
}
