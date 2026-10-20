#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02227228();
void *ov13_02239FF0();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290cc0;
extern M2C_UNK ov13_02236F14;

void ov13_02236E90(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if ((M2C_FIELD(M2C_FIELD(&data_ov031_02290cc0, void **, 4), u8 *, 0x1D) == 1) && ((M2C_FIELD(&data_ov031_02290cc0, u8 *, 0) == 3) || (M2C_FIELD(ov13_02239FF0(), u8 *, 0xE7) != 0xFF))) {
        ov13_02227228();
    }
    ov13_022403B8(3, 1, 1, 8);
    ov13_022403B8(3, 0, 0x14, 8);
    func_ov031_022274c0(&ov13_02236F14);
}
