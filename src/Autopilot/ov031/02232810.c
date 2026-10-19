#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02227258();
M2C_UNK ov13_022272CC();
s32 ov13_0223B2A8();
extern M2C_UNK func_ov031_02232844;

void ov13_02236BE0(void) {
    if (ov13_02227258() == -2) {
        return;
    }
    if (ov13_0223B2A8() == 1) {
        return;
    }
    ov13_022272CC();
    func_ov031_022274c0(&func_ov031_02232844);
}
