#include <m2c.h>

s32 func_02094a00();
M2C_UNK func_02094b30(s32, s32, M2C_UNK);
M2C_UNK func_02094b3c(s32, M2C_UNK);
s32 func_02094b4c();

void func_ov003_0215dc20(void *arg0) {
    s32 temp_r0_2;
    u8 temp_r0;

    if (M2C_FIELD(arg0, u8 *, 0x3EC) == 0) {
        return;
    }
    temp_r0 = M2C_FIELD(arg0, u8 *, 0x3ED);
    if (temp_r0 == 0) {
        temp_r0_2 = func_02094a00();
        func_02094b3c(temp_r0_2, 0xA);
        if (M2C_FIELD(arg0, u8 *, 0x3F0) != 0) {
            func_02094b30(temp_r0_2, 0x1F5, 0);
        } else {
            func_02094b30(temp_r0_2, 0x200, 1);
        }
        M2C_FIELD(arg0, u8 *, 0x3ED) = (u8) (M2C_FIELD(arg0, u8 *, 0x3ED) + 1);
        return;
    }
    if (temp_r0 != 1) {
        return;
    }
    func_02094a00();
    if (func_02094b4c() != 0) {
        M2C_FIELD(arg0, u8 *, 0x3EC) = 0U;
        M2C_FIELD(arg0, u8 *, 0x3ED) = 0U;
    }
}
