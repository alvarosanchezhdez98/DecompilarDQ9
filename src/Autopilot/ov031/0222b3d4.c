#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_0222b168();
M2C_UNK func_ov031_0222b1a0();
M2C_UNK ov13_0222F59C();
M2C_UNK ov13_0223AC20();
extern M2C_UNK data_ov031_02290c80;
extern M2C_UNK ov13_0222F5E8;

void ov13_0222F7CC(void) {
    func_ov031_0222b168();
    func_ov031_0222b1a0();
    ov13_0222F59C();
    M2C_FIELD(&data_ov031_02290c80, u16 *, 2) = (u16) (M2C_FIELD(&data_ov031_02290c80, u16 *, 2) + 1);
    if ((u32) M2C_FIELD(&data_ov031_02290c80, u16 *, 2) < 0x438U) {
        return;
    }
    ov13_0223AC20();
    func_ov031_022274c0(&ov13_0222F5E8);
}
