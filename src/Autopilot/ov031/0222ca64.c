#include <m2c.h>

s32 func_ov031_0223e218(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern M2C_UNK data_ov031_02290c8c;
extern M2C_UNK ov13_02230B14;

void ov13_02230E5C(void) {
    if (M2C_FIELD(&data_ov031_02290c8c, u16 *, 2) == 0) {
        if (M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), u8 *, 0x59) != 0) {
            return;
        }
        ov13_0223ABB8(9);
        M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), u8 *, 0x59) = 1U;
        return;
    }
    ov13_0223ABB8(0x13);
    M2C_FIELD(M2C_FIELD(&data_ov031_02290c8c, void **, 4), s32 *, 0x38) = func_ov031_0223e218(0, &ov13_02230B14, 0, 0x78);
}
