#include <m2c.h>

M2C_UNK func_ov031_02222b0c(M2C_UNK);
M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0223208c();
M2C_UNK func_ov031_022357e8();
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02227964(M2C_UNK);
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227E40();
M2C_UNK ov13_02239B00();
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern M2C_UNK data_ov031_02290cbc;
extern M2C_UNK func_ov031_02232134;

void ov13_022363F4(void) {
    M2C_FIELD(&data_ov031_02290cbc, s16 *, 2) = 0;
    M2C_FIELD(&data_ov031_02290cbc, s8 *, 0) = 0;
    func_ov031_0223208c();
    ov13_022277B8(0x33, -1, 0);
    ov13_02227E40();
    ov13_02227964(2);
    ov13_022279EC(0x33);
    func_ov031_02222b0c(0);
    ov13_02239B00();
    func_ov031_022357e8();
    ov13_0223ABB8(0xA);
    func_ov031_022274c0(&func_ov031_02232134);
}
