#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_02228054();
M2C_UNK ov13_02228400(M2C_UNK);
M2C_UNK ov13_02228414(M2C_UNK);
M2C_UNK ov13_0223ABB8(M2C_UNK);
s32 ov13_02240394(M2C_UNK);
extern void *data_ov031_02290c94;
extern M2C_UNK ov13_02231298;

void ov13_0223121C(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_02228054();
    ov13_0223ABB8(0x14);
    if (M2C_FIELD(data_ov031_02290c94, u8 *, 0x29) == 0) {
        ov13_02228400(0);
    }
    if (M2C_FIELD(data_ov031_02290c94, u8 *, 0x29) == 0x20) {
        ov13_02228414(0);
    }
    func_ov031_022274c0(&ov13_02231298);
}
