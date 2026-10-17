#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02237eb0();
M2C_UNK ov13_022272CC();
extern M2C_UNK func_ov031_02232844;

void ov13_02237524(void) {
    if (func_ov031_02237eb0() != 0) {
        return;
    }
    ov13_022272CC();
    func_ov031_022274c0(&func_ov031_02232844);
}
