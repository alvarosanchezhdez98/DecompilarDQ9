#include <m2c.h>

s32 func_020e2ff8();
M2C_UNK func_020e3468(s32, M2C_UNK);
s32 func_020e34bc(s32, M2C_UNK);

s32 func_ov002_0215b7d0(void) {
    s32 temp_r0;
    s32 temp_r0_2;

    temp_r0 = func_020e2ff8();
    temp_r0_2 = func_020e34bc(temp_r0, 1);
    if (temp_r0_2 == 1) {
        return 1;
    }
    if ((u32) (temp_r0_2 - 3) > 2U) {
        return 0;
    }
    func_020e3468(temp_r0, 1);
    return -1;
}
