#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02240EA8(M2C_UNK, M2C_UNK);
extern M2C_UNK func_ov031_02228a58;

void func_ov031_02228a24(void) {
    ov13_022403B8(2, 0, 0x15, 8);
    ov13_02240EA8(0, 0x15);
    func_ov031_022274c0(&func_ov031_02228a58);
}
