#include <m2c.h>

M2C_UNK func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290ce8;
extern M2C_UNK ov13_022393B4;

void ov13_02239378(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(&data_ov031_02290ce8, s32 *, 4) = (s32) (arg0 + (arg1 << 5));
    M2C_FIELD(&data_ov031_02290ce8, s32 *, 8) = (s32) ((arg2 << 5) + 0x05000000);
    func_ov031_0223e218(1, &ov13_022393B4, 0, 0x78);
}
