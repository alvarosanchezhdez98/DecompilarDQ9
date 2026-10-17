#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02237eb0();
M2C_UNK ov13_022272CC();
M2C_UNK ov13_02239584();
extern M2C_UNK func_ov031_0222bb44;

void ov13_02230FB0(void) {
    if (func_ov031_02237eb0() != 0) {
        return;
    }
    ov13_022272CC();
    ov13_02239584();
    func_ov031_022274c0(&func_ov031_0222bb44);
}
