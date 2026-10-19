#include <m2c.h>

u16 *func_02012fe4();
M2C_UNK func_02017098(u16 *, M2C_UNK);
s32 func_02027ca4();
s32 func_02028bd0(s32, s32);
M2C_UNK func_02028c14(s32, M2C_UNK);
s32 func_0205ec34();
M2C_UNK func_0206df6c(s32, s32, s32, M2C_UNK);

void func_ov017_021b6174(s32 arg0, M2C_UNK arg1, s32 arg2) {
    s32 temp_r0;
    s32 temp_r5;
    u16 *temp_r4;

    temp_r4 = func_02012fe4();
    temp_r5 = func_0205ec34();
    if (arg0 == *temp_r4) {
        func_02017098(temp_r4, arg1);
    }
    temp_r0 = func_02028bd0(func_02027ca4(), arg0);
    if (temp_r0 != 0) {
        func_02028c14(temp_r0, arg1);
    }
    func_0206df6c(temp_r5, temp_r5 + 0x8C, arg2 + 0x79E, 1);
}
