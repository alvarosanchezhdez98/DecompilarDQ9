#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02227bc8();
M2C_UNK ov13_022272E4();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223AC20();
M2C_UNK ov13_0223BE6C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern s8 data_ov031_02290cb8;
extern M2C_UNK func_ov031_02231df8;
extern M2C_UNK func_ov031_02231fd8;

void ov13_02236324(void) {
    s32 temp_r0;

    temp_r0 = func_ov031_02227bc8();
    switch (temp_r0) {                              /* irregular */
    case 1:
        data_ov031_02290cb8 = 1;
        func_ov031_022274c0(&func_ov031_02231df8);
        return;
    case 4:
        data_ov031_02290cb8 = 0;
        ov13_0223AC20();
        ov13_0223ABB8(9);
        ov13_0223BE6C(0xD, 1, 1, -1, 0);
        ov13_022272E4();
        func_ov031_022274c0(&func_ov031_02231fd8);
        return;
    }
}
