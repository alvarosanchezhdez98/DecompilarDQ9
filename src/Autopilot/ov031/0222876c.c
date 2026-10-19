#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 ov13_02227258();
M2C_UNK ov13_022272E4();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223BE6C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern M2C_UNK func_ov031_022287d4;
extern M2C_UNK ov13_0222CD38;

void ov13_0222CB94(void) {
    s32 temp_r0;

    temp_r0 = ov13_02227258();
    switch (temp_r0) {                              /* irregular */
    case 0:
        ov13_0223ABB8(7);
        func_ov031_022274c0(&func_ov031_022287d4);
        return;
    case 1:
        ov13_0223ABB8(6);
        ov13_0223BE6C(0x18, 0, 1, -1, 0);
        ov13_022272E4();
        func_ov031_022274c0(&ov13_0222CD38);
        return;
    }
}
