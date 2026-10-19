#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
M2C_UNK ov13_0222B8F8(M2C_UNK, M2C_UNK);
s32 ov13_0222B980();
s32 ov13_02240394(M2C_UNK);
extern M2C_UNK ov13_0222C44C;
extern M2C_UNK ov13_022368D8;

void ov13_0222C3D8(void) {
    s32 temp_r0;

    if (ov13_02240394(1) != 0) {
        return;
    }
    if (ov13_02240394(0) != 0) {
        return;
    }
    temp_r0 = ov13_0222B980();
    switch (temp_r0) {                              /* irregular */
    case 0:
        ov13_0222B8F8(0, 1);
        func_ov031_022274c0(&ov13_0222C44C);
        return;
    case 1:
        ov13_0222B8F8(1, 1);
        func_ov031_022274c0(&ov13_022368D8);
        return;
    }
}
