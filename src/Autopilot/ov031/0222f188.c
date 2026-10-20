#include <m2c.h>

M2C_UNK ov13_022335EC(u32);
s32 ov13_0223417C();
u32 ov13_02234700();
M2C_UNK ov13_02234D54(u32);
M2C_UNK ov13_022350FC();
M2C_UNK ov13_02239FF0();
M2C_UNK ov13_0223ABB8(M2C_UNK);

s32 ov13_02233568(void) {
    u32 temp_r0;

    ov13_02239FF0();
    temp_r0 = ov13_02234700();
    if (temp_r0 == 0xE) {
        return 0;
    }
    if (ov13_0223417C() == 0) {
        ov13_0223ABB8(9);
        return 1;
    }
    ov13_02234D54(temp_r0);
    switch (temp_r0) {
    default:
        break;
    case 2:
    case 3:
    case 7:
    case 8:
        ov13_022350FC();
        break;
    }
    ov13_022335EC(temp_r0);
    return 1;
}
