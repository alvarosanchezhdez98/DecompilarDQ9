#include <m2c.h>

M2C_UNK func_ov031_02222b0c(M2C_UNK);
M2C_UNK func_ov031_02223a64(M2C_UNK);
M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02233a8c();
M2C_UNK func_ov031_02233b34();
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02227964(M2C_UNK);
M2C_UNK ov13_022279EC(M2C_UNK);
M2C_UNK ov13_02227E40();
M2C_UNK ov13_0222B948(M2C_UNK, s32 *);
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern s8 data_ov031_02290cd0;
extern M2C_UNK ov13_02237F9C;

void ov13_02237DD0(void) {
    s32 sp0;

    data_ov031_02290cd0 = 0;
    func_ov031_02233a8c();
    ov13_0222B948(0, &sp0);
    if (sp0 == 0) {
        ov13_022277B8(0x31, -1, 0);
    }
    ov13_02227964(2);
    if (sp0 == 0) {
        ov13_02227E40();
    }
    ov13_022279EC(0x2C);
    func_ov031_02222b0c(0);
    func_ov031_02233b34();
    func_ov031_02223a64(0);
    ov13_0223ABB8(0xC);
    func_ov031_022274c0(&ov13_02237F9C);
}
