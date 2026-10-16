#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_022283EC();
extern M2C_UNK func_ov031_0222cec0;

void ov13_02231298(void) {
    if (ov13_022283EC() == 0xFF) {
        return;
    }
    func_ov031_022274c0(&func_ov031_0222cec0);
}
