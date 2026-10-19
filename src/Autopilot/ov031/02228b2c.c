#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK func_ov031_02228b78;

void func_ov031_02228b2c(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    ov13_022403B8(3, 1, 0x3F, 0x40);
    ov13_022403B8(3, 0, 0x3F, 0x40);
    func_ov031_022274c0(&func_ov031_02228b78);
}
