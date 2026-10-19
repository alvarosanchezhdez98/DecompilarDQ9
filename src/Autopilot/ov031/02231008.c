#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0223BE6C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
s32 ov13_02240394(M2C_UNK);
extern M2C_UNK ov13_02235428;

void ov13_022353D8(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_0223BE6C(0x44, 5, 1, -1, 0);
    func_ov031_022274c0(&ov13_02235428);
}
