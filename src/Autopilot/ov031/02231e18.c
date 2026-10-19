#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02227228();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern u8 data_ov031_02290cb8;
extern M2C_UNK func_ov031_02231e8c;

void ov13_022361E8(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (data_ov031_02290cb8 == 0) {
        ov13_02227228();
    }
    if (data_ov031_02290cb8 == 0) {
        ov13_022403B8(3, 1, 1, 8);
    }
    ov13_022403B8(3, 0, 0x14, 8);
    func_ov031_022274c0(&func_ov031_02231e8c);
}
