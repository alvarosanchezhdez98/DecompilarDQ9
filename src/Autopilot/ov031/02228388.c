#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02227258();
M2C_UNK ov13_0222C984();
M2C_UNK ov13_0223ABB8(M2C_UNK);
extern M2C_UNK func_ov031_022283d8;
extern M2C_UNK ov13_0222C10C;

void ov13_0222C7B0(void) {
    s32 temp_r0;

    temp_r0 = ov13_02227258();
    switch (temp_r0) {                              /* irregular */
    case 0:
        ov13_0223ABB8(7);
        func_ov031_022274c0(&ov13_0222C10C);
        return;
    case 1:
        ov13_0223ABB8(6);
        ov13_0222C984();
        func_ov031_022274c0(&func_ov031_022283d8);
        return;
    }
}
