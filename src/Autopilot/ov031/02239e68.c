#include <m2c.h>

M2C_UNK func_020c9be0();
M2C_UNK ov13_0223D6A8(M2C_UNK);
u16 ov13_0223E220(u16);
extern M2C_UNK data_ov031_0224c464;
extern M2C_UNK data_ov031_02290d18;

u16 ov13_0223E1A8(void) {
    if (M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), s32 *, 0x40) != 7) {
        func_020c9be0();
    }
    ov13_0223D6A8(1);
    M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), u16 *, 0x5C) = ov13_0223E220(M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), u16 *, 0x60));
    if (M2C_FIELD(&data_ov031_02290d18, M2C_UNK (**)(M2C_UNK, M2C_UNK *, u16), 0) != NULL) {
        M2C_FIELD(&data_ov031_02290d18, M2C_UNK (**)(M2C_UNK, M2C_UNK *, u16), 0)(0x08000000, &data_ov031_0224c464, M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), u16 *, 0x5C));
    }
    return M2C_FIELD(M2C_FIELD(&data_ov031_02290d18, void **, 4), u16 *, 0x5C);
}
