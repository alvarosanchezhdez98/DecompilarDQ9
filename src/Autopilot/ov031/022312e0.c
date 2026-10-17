#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02227258();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223AC20();
extern M2C_UNK func_ov031_0223130c;

void func_ov031_022312e0(void) {
    if (ov13_02227258() != 0) {
        return;
    }
    ov13_0223AC20();
    ov13_0223ABB8(7);
    func_ov031_022274c0(&func_ov031_0223130c);
}
