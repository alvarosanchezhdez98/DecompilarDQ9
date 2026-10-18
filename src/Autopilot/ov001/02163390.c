#include <m2c.h>

void *func_0205ec34();
s32 func_0206dfb0(void *, s32, s32);
s32 func_ov017_021d60f4(s32);
M2C_UNK func_ov017_021d6134(s32, M2C_UNK);

s32 func_ov001_02163390(s32 arg0) {
    s32 temp_r0;
    void *temp_r4;

    temp_r4 = func_0205ec34();
    temp_r0 = arg0 + 8;
    if (func_0206dfb0(temp_r4, (M2C_FIELD(temp_r4, u8 *, 0x332) * 0x1C) + (s32) temp_r4 + 0x10, func_ov017_021d60f4(arg0)) != 0) {
        func_ov017_021d6134(temp_r0, 1);
    } else {
        func_ov017_021d6134(temp_r0, 0);
    }
    return 1;
}
