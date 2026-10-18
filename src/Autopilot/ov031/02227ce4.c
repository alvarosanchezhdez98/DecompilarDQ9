#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_0222C148;

void ov13_0222C10C(void) {
    ov13_022403B8(3, 1, 0x3F, 0x14);
    ov13_022403B8(3, 0, 0x3F, 0x14);
    func_ov031_022274c0(&ov13_0222C148);
}
