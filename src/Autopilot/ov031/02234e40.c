#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02237eb0();
M2C_UNK ov13_022272CC();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223BA24(M2C_UNK *);
extern u8 data_ov031_02290ce4;
extern M2C_UNK func_ov031_02234a90;
extern M2C_UNK func_ov031_02234b2c;
extern M2C_UNK ov13_0223902C;

void ov13_022391C0(void) {
    if (func_ov031_02237eb0() != 0) {
        return;
    }
    if (data_ov031_02290ce4 == 1) {
        func_ov031_022274c0(&func_ov031_02234b2c);
        return;
    }
    ov13_0223ABB8(0xB);
    ov13_022272CC();
    data_ov031_02290ce4 = 0;
    ov13_0223BA24(&ov13_0223902C);
    func_ov031_022274c0(&func_ov031_02234a90);
}
