#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02227228();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern u8 data_ov031_02290ce4;
extern M2C_UNK ov13_02238F38;

void ov13_02238ECC(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    ov13_02227228();
    if ((u32) (u8) (data_ov031_02290ce4 + 0xFE) <= 1U) {
        ov13_022403B8(3, 1, 1, 8);
    }
    ov13_022403B8(3, 0, 0x15, 8);
    func_ov031_022274c0(&ov13_02238F38);
}
