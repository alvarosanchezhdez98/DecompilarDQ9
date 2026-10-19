#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222B948(M2C_UNK, s32 *);
M2C_UNK ov13_0223B1A0();
M2C_UNK ov13_022403B8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK ov13_0223832C;

void ov13_022382D4(void) {
    s32 sp0;

    ov13_0222B948(0, &sp0);
    if (sp0 != 0) {
        ov13_0223B1A0();
    }
    ov13_022403B8(3, 1, 1, 8);
    ov13_022403B8(3, 0, 0x15, 8);
    func_ov031_022274c0(&ov13_0223832C);
}
