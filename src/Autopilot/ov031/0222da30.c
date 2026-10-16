#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_0222A070();
extern M2C_UNK func_ov031_0222da50;

void ov13_02231E28(void) {
    if (ov13_0222A070() == 0x1F) {
        return;
    }
    func_ov031_022274c0(&func_ov031_0222da50);
}
