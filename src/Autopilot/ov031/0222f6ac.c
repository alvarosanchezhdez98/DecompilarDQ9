#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_02233AD8;

void ov13_02233A8C(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    ov13_022403B8(3, 1, 1, 8);
    ov13_022403B8(3, 0, 0x1D, 8);
    func_ov031_022274c0(&ov13_02233AD8);
}
