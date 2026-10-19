#include <m2c.h>

M2C_UNK ov13_022400F0(M2C_UNK, M2C_UNK, s32);
s32 ov13_02241D78();

s32 ov13_02240184(M2C_UNK arg0, M2C_UNK arg1) {
    s32 temp_r0;

    temp_r0 = ov13_02241D78();
    ov13_022400F0(arg0, arg1, temp_r0);
    return temp_r0;
}
