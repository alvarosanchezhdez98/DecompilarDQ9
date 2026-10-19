#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222B948(M2C_UNK, s32 *);
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK ov13_02240EA8(M2C_UNK, M2C_UNK);
extern M2C_UNK func_ov031_02233c40;

void ov13_02237F9C(void) {
    s32 sp0;

    ov13_022403B8(2, 0, 0x15, 8);
    ov13_02240EA8(0, 0x15);
    ov13_0222B948(0, &sp0);
    if (sp0 == 0) {
        ov13_022403B8(2, 1, 1, 8);
        ov13_02240EA8(1, 1);
    }
    func_ov031_022274c0(&func_ov031_02233c40);
}
