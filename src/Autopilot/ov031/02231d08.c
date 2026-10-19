#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02227b38();
M2C_UNK ov13_022279B4(M2C_UNK);
s32 ov13_02240394(M2C_UNK);
extern M2C_UNK func_ov031_02231d48;

void ov13_022360D8(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    func_ov031_02227b38();
    ov13_022279B4(1);
    func_ov031_022274c0(&func_ov031_02231d48);
}
