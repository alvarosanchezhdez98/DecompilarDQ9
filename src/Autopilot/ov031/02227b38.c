#include <m2c.h>

M2C_UNK _Z19SleepCurrentContextj(M2C_UNK);
M2C_UNK func_020c9be0();
s32 func_ov031_02222928(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK *, M2C_UNK *, s32);
s32 ov13_0224128C(M2C_UNK, M2C_UNK);
extern s32 data_ov031_02290c48;
extern M2C_UNK func_ov031_02227cc8;
extern M2C_UNK func_ov031_02227cd8;
extern M2C_UNK ov13_0222C0D8;

void func_ov031_02227b38(void) {
    data_ov031_02290c48 = ov13_0224128C(0xC, -4);
    if (func_ov031_02222928(0xF, 0x40, &ov13_0222C0D8, &func_ov031_02227cc8, &func_ov031_02227cd8, 0x800) != 1) {
        func_020c9be0();
    }
    _Z19SleepCurrentContextj(0xA);
}
