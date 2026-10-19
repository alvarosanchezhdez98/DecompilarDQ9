#include <m2c.h>

M2C_UNK func_ov031_02222b0c(M2C_UNK);
M2C_UNK func_ov031_02226e08();
M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0222af14();
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02227964(M2C_UNK);
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227E40();
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern M2C_UNK data_ov031_02290c80;
extern M2C_UNK func_ov031_0222afbc;

void ov13_0222F2AC(void) {
    M2C_FIELD(&data_ov031_02290c80, s16 *, 2) = 0;
    func_ov031_0222af14();
    ov13_02227E40();
    ov13_022277B8(0x36, -1, 0);
    ov13_02227964(2);
    ov13_022279EC(0x22);
    func_ov031_02222b0c(0);
    func_ov031_02226e08();
    ov13_0223ABB8(0xB);
    func_ov031_022274c0(&func_ov031_0222afbc);
}
