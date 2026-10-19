#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022279B4(M2C_UNK);
s32 ov13_02240394(M2C_UNK);
extern M2C_UNK func_ov031_022346a8;

void ov13_022389EC(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_022279B4(6);
    func_ov031_022274c0(&func_ov031_022346a8);
}
