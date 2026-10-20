#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02229D00();
M2C_UNK ov13_0222A084(M2C_UNK);
M2C_UNK ov13_0222A098(M2C_UNK);
M2C_UNK ov13_0222A0AC(M2C_UNK);
s32 ov13_02232168(M2C_UNK);
M2C_UNK ov13_0223ABB8(M2C_UNK);
s32 ov13_02240394(M2C_UNK);
extern void *data_ov031_02290c98;
extern M2C_UNK ov13_02231E28;

void ov13_02231D9C(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_02229D00();
    ov13_0223ABB8(0x14);
    if (M2C_FIELD(data_ov031_02290c98, u8 *, 0x14) == 0) {
        ov13_0222A084(0);
        ov13_0222A0AC(0);
    } else {
        if (ov13_02232168(0x1A) != 0) {
            ov13_0222A098(0);
        }
        ov13_0222A0AC(0);
    }
    func_ov031_022274c0(&ov13_02231E28);
}
