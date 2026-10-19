#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK func_ov031_02234118();
M2C_UNK ov13_022277B8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02227E40();
M2C_UNK ov13_0222B948(M2C_UNK, s32 *);
M2C_UNK ov13_02239B34();
M2C_UNK ov13_0223A4F4();
extern M2C_UNK func_ov031_02234184;

void ov13_02238440(void) {
    s32 sp0;

    ov13_02239B34();
    ov13_0222B948(0, &sp0);
    func_ov031_02234118();
    ov13_022277B8(0x31, -1, 0);
    if (sp0 != 2) {
        ov13_02227E40();
    }
    if (sp0 == 1) {
        ov13_0223A4F4();
    }
    func_ov031_022274c0(&func_ov031_02234184);
}
