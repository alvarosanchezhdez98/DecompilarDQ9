#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222BC84(M2C_UNK);
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223AC20();
extern s8 data_ov031_02290c7c;
extern M2C_UNK ov13_0222F080;

void ov13_0222F230(s32 arg0) {
    ov13_0223AC20();
    if (arg0 == 0) {
        data_ov031_02290c7c = 1;
        ov13_0223ABB8(0x10);
    } else {
        data_ov031_02290c7c = 2;
        ov13_0223ABB8(0x12);
    }
    ov13_0222BC84(0);
    func_ov031_022274c0(&ov13_0222F080);
}
