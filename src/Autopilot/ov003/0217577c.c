#include <m2c.h>
#pragma optimization_level 4

s32 func_0204c7cc();
M2C_UNK func_020809c4(s32, M2C_UNK, M2C_UNK, s16 *, s16 *);
s32 func_02081da8(s32, M2C_UNK);
M2C_UNK func_ov003_0217585c(void *, s32, s32, M2C_UNK, s32);

void func_ov003_0217577c(void *arg0) {
    s16 sp6;
    s16 sp4;
    s32 temp_r4;
    s32 var_r5;
    s32 var_r5_2;

    temp_r4 = M2C_FIELD(arg0, s32 *, 0x89C);
    if ((func_02081da8(temp_r4, 9) != 0) && (func_0204c7cc() != 0)) {
        var_r5 = 0;
        if (M2C_FIELD(arg0, u8 *, 0x104B) != 0) {
            var_r5 = 1;
        }
        func_020809c4(temp_r4, 9, 0x58, &sp6, &sp4);
        func_ov003_0217585c(arg0, sp6 + var_r5, sp4 + var_r5, 0x1D, 0x1E);
        var_r5_2 = 0;
        if (M2C_FIELD(arg0, u8 *, 0x104C) != 0) {
            var_r5_2 = 1;
        }
        func_020809c4(temp_r4, 9, 0x59, &sp6, &sp4);
        func_ov003_0217585c(arg0, sp6 + var_r5_2, sp4 + var_r5_2, 0x1E, 0x1F);
    }
}
