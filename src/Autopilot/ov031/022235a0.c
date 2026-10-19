#include <m2c.h>

s32 ov13_02227B1C();
s32 ov13_0222BADC(s32, M2C_UNK);
s32 ov13_022408A0(M2C_UNK, M2C_UNK);
M2C_UNK ov13_02240CC0(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK ov13_02240E2C(s32);
extern s32 data_ov031_02290c4c;

void ov13_022279EC(M2C_UNK arg0) {
    s32 temp_r4;
    s32 temp_r5;

    temp_r5 = ov13_022408A0(0, 0);
    temp_r4 = ov13_0222BADC(data_ov031_02290c4c, arg0);
    ov13_02240CC0(temp_r5, 0xD, 0x28, 0xE6, 0x70, 2, ov13_02227B1C(), temp_r4);
    ov13_02240E2C(temp_r5);
}
