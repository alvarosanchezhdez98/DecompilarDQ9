#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022393E0(s32);
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223C198();
s32 ov13_0223C1DC();
extern M2C_UNK data_ov031_02290ca0;
extern M2C_UNK func_ov031_02230ed0;

void ov13_02235260(void) {
    if (ov13_0223C1DC() != 0) {
        return;
    }
    ov13_0223ABB8(6);
    ov13_0223C198();
    ov13_022393E0(M2C_FIELD(M2C_FIELD(&data_ov031_02290ca0, void **, 8), s32 *, 0xC));
    func_ov031_022274c0(&func_ov031_02230ed0);
}
