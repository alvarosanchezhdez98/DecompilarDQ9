#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02237eb0();
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_02238658;

void ov13_02238624(void) {
    if (func_ov031_02237eb0() != 0) {
        return;
    }
    ov13_022403B8(3, 0, 0x14, 8);
    func_ov031_022274c0(&ov13_02238658);
}
