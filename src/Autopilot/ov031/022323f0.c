#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02236094(u8);
M2C_UNK ov13_02227028();
s32 ov13_022272A0();
M2C_UNK ov13_0222788C();
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
M2C_UNK ov13_0222B934(M2C_UNK, M2C_UNK);
M2C_UNK ov13_02239B34();
s32 ov13_02239C68();
void *ov13_02239FF0();
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02240B04(M2C_UNK);
M2C_UNK ov13_02240EFC(M2C_UNK, M2C_UNK);
extern u8 data_ov031_02290cbc;
extern M2C_UNK ov13_0222FA3C;
extern M2C_UNK ov13_02237618;

void ov13_022367C0(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    if (ov13_022272A0() == 0) {
        return;
    }
    do {

    } while (ov13_02239C68() == 0);
    ov13_02227028();
    ov13_02240B04(0);
    ov13_0222788C();
    ov13_02240EFC(1, 1);
    ov13_02240EFC(0, 0x15);
    if (data_ov031_02290cbc != 1) {
        ov13_02239B34();
        func_ov031_02236094(M2C_FIELD(ov13_02239FF0(), u8 *, 0xF4));
        ov13_0222B8F8(2, 1);
        func_ov031_022274c0(&ov13_02237618);
        return;
    }
    ov13_0222B8F8(0, 1);
    ov13_0222B934(0, 0);
    func_ov031_022274c0(&ov13_0222FA3C);
}
