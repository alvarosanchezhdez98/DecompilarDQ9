#include <m2c.h>

M2C_UNK func_ov031_02223984();
M2C_UNK func_ov031_0222761c();
M2C_UNK func_ov031_02235c5c();
M2C_UNK ov13_02227B54();
M2C_UNK ov13_0222B9B4();
M2C_UNK ov13_0222BAB0(s32);
M2C_UNK ov13_022400C8(M2C_UNK);
s32 ov13_02240394(M2C_UNK);
M2C_UNK ov13_02242640(M2C_UNK, M2C_UNK);
extern s32 data_ov031_02290c4c;

void ov13_0222C148(void) {
    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    ov13_02242640(0, 0);
    ov13_02242640(1, 0);
    ov13_022400C8(1);
    ov13_022400C8(0);
    func_ov031_02223984();
    ov13_02227B54();
    ov13_0222BAB0(data_ov031_02290c4c);
    func_ov031_0222761c();
    func_ov031_02235c5c();
    ov13_0222B9B4();
}
