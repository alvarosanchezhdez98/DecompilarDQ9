#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022272E4();
M2C_UNK ov13_0223B1A0();
M2C_UNK ov13_022405B8(M2C_UNK);
extern M2C_UNK data_ov031_02290cc0;
extern M2C_UNK ov13_02236E90;

void ov13_02236E54(void) {
    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290cc0, void **, 4), u8 *, 0x1D) == 2) {
        ov13_0223B1A0();
    }
    ov13_022272E4();
    ov13_022405B8(8);
    func_ov031_022274c0(&ov13_02236E90);
}
