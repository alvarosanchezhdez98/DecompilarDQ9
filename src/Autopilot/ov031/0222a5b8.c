#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02227228();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290c74;
extern M2C_UNK ov13_0222EA14;

void ov13_0222E9B0(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    ov13_02227228();
    if (M2C_FIELD(&data_ov031_02290c74, u8 *, 1) == 0) {
        ov13_022403B8(3, 1, 1, 8);
    }
    ov13_022403B8(3, 0, 0x15, 8);
    func_ov031_022274c0(&ov13_0222EA14);
}
