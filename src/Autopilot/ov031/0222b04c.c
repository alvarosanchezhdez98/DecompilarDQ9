#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
s32 ov13_02227258();
extern M2C_UNK data_ov031_02290c80;
extern M2C_UNK ov13_0222F48C;
extern M2C_UNK ov13_0222F764;

void ov13_0222F444(void) {
    if (ov13_02227258() == -2) {
        return;
    }
    M2C_FIELD(&data_ov031_02290c80, s32 *, 4) = func_ov031_0223e218(1, &ov13_0222F764, 0, 0x78);
    func_ov031_022274c0(&ov13_0222F48C);
}
