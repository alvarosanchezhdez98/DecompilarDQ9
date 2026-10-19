#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02227964(M2C_UNK);
M2C_UNK ov13_02227DE4(M2C_UNK);
M2C_UNK ov13_02236938();
M2C_UNK ov13_02236A48();
M2C_UNK ov13_022370B8();
void *ov13_0224128C(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290cc0;
extern M2C_UNK func_ov031_02232780;

void ov13_022368D8(void) {
    void *temp_r0;

    temp_r0 = ov13_0224128C(0x20, 4);
    M2C_FIELD(&data_ov031_02290cc0, void **, 4) = temp_r0;
    M2C_FIELD(temp_r0, s8 *, 0x1D) = 0;
    ov13_02236938();
    ov13_02227DE4(1);
    ov13_022277B8(0x2F, -1, 0);
    ov13_02227964(0);
    ov13_02236A48();
    ov13_022370B8();
    func_ov031_022274c0(&func_ov031_02232780);
}
