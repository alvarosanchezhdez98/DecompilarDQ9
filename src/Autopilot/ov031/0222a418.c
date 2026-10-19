#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02240EA8(M2C_UNK, M2C_UNK);
extern u8 data_ov031_02290c74;
extern M2C_UNK func_ov031_0222a480;

void ov13_0222E810(void) {
    ov13_022403B8(2, 0, 0x15, 8);
    ov13_02240EA8(0, 0x15);
    if (data_ov031_02290c74 != 0) {
        ov13_022403B8(2, 1, 1, 8);
        ov13_02240EA8(1, 1);
    }
    func_ov031_022274c0(&func_ov031_0222a480);
}
