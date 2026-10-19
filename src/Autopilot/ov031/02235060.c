#include <m2c.h>

M2C_UNK func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290ce8;
extern M2C_UNK ov13_0223940C;

void ov13_022393E0(s32 arg0) {
    M2C_FIELD(&data_ov031_02290ce8, s32 *, 4) = arg0;
    func_ov031_0223e218(1, &ov13_0223940C, 0, 0x78);
}
