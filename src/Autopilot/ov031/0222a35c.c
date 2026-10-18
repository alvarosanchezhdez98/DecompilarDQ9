#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0222a398();
s8 ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_022279EC(M2C_UNK);
extern s8 data_ov031_02290c74;
extern M2C_UNK ov13_0222E810;

void ov13_0222E754(void) {
    func_ov031_0222a398();
    ov13_022279EC(0x20);
    data_ov031_02290c74 = ov13_022277B8(0x3C, -1, 0);
    func_ov031_022274c0(&ov13_0222E810);
}
