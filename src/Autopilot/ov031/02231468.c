#include <m2c.h>

M2C_UNK func_ov031_022274c0(M2C_UNK *);
s32 func_ov031_02227bc8();
M2C_UNK ov13_022272E4();
M2C_UNK ov13_0223ABB8(M2C_UNK);
M2C_UNK ov13_0223AC20();
M2C_UNK ov13_0223BE6C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32);
extern s8 data_ov031_02290cac;
extern M2C_UNK func_ov031_0223130c;
extern M2C_UNK func_ov031_022314ec;

void ov13_02235838(void) {
    s32 temp_r0;

    temp_r0 = func_ov031_02227bc8();
    switch (temp_r0) {                              /* irregular */
    case 2:
        data_ov031_02290cac = 1;
        func_ov031_022274c0(&func_ov031_0223130c);
        return;
    case 4:
        data_ov031_02290cac = 0;
        ov13_0223AC20();
        ov13_0223ABB8(9);
        ov13_0223BE6C(0xD, 1, 1, -1, 0);
        ov13_022272E4();
        func_ov031_022274c0(&func_ov031_022314ec);
        return;
    }
}
