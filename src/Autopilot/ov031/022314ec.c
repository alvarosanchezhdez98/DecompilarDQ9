#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223C198();
s32 ov13_0223C1DC();
extern M2C_UNK func_ov031_02231518;

void func_ov031_022314ec(void) {
    if (ov13_0223C1DC() != 0) {
        return;
    }
    ov13_0223ABB8(6);
    ov13_0223C198();
    func_ov031_022274c0(&func_ov031_02231518);
}
