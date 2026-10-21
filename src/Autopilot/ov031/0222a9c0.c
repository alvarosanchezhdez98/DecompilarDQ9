#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222788C();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
s32 ov13_0222BC68();
M2C_UNK ov13_02240B04(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern M2C_UNK data_ov031_02290c78;
extern M2C_UNK ov13_0222D454;
extern M2C_UNK ov13_0222DB6C;
extern M2C_UNK ov13_0222E754;

void ov13_0222EDB8(void) {
    if (((M2C_FIELD(&data_ov031_02290c78, u8 *, 0) != 0) || (M2C_FIELD(&data_ov031_02290c78, u8 *, 1) == 0)) && (ov13_0222BC68() == 0)) {
        return;
    }
    ov13_02240B04(0);
    ov13_02240EFC(0, 0x15);
    if (M2C_FIELD(&data_ov031_02290c78, u8 *, 1) == 0) {
        ov13_0222788C();
        ov13_02240EFC(1, 1);
    }
    ov13_0222B8F8(0, 1);
    if (M2C_FIELD(&data_ov031_02290c78, u8 *, 0) != 0) {
        func_ov031_022274c0(&ov13_0222E754);
        return;
    }
    if (M2C_FIELD(&data_ov031_02290c78, u8 *, 1) == 0) {
        ov13_02240EFC(1, 1);
        func_ov031_022274c0(&ov13_0222D454);
        return;
    }
    func_ov031_022274c0(&ov13_0222DB6C);
}
