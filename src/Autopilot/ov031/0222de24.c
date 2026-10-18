#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222A03C();
M2C_UNK ov13_0223ABB8(M2C_UNK);
s32 ov13_02240394(M2C_UNK);
extern M2C_UNK ov13_0223224C;

void func_ov031_0222de24(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    ov13_0222A03C();
    ov13_0223ABB8(0x15);
    func_ov031_022274c0(&ov13_0223224C);
}
