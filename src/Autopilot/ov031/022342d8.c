#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_02237DD0;

void ov13_02238658(void) {
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_02240EFC(0, 0x14);
    ov13_0222B8F8(0, 1);
    func_ov031_022274c0(&ov13_02237DD0);
}
