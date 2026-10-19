#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_0222C86C;

void ov13_0222C820(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    ov13_022403B8(3, 1, 1, 8);
    ov13_022403B8(3, 0, 0x16, 8);
    func_ov031_022274c0(&ov13_0222C86C);
}
