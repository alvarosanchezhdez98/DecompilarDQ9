#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02240EA8(M2C_UNK, M2C_UNK);
extern M2C_UNK func_ov031_0222bae0;

void func_ov031_0222ba8c(void) {
    ov13_022403B8(2, 1, 1, 8);
    ov13_022403B8(2, 0, 0x1D, 8);
    ov13_02240EA8(1, 1);
    ov13_02240EA8(0, 0x1D);
    func_ov031_022274c0(&func_ov031_0222bae0);
}
