#include <m2c.h>

s32 func_0205ec34();
s32 func_0206eb98(s32, s32);
s32 func_ov017_021d60f4(s32);
M2C_UNK func_ov017_021d6134(s32, M2C_UNK);

s32 func_ov001_021633ec(s32 arg0) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r4 = func_0205ec34();
    temp_r0 = arg0 + 8;
    if (func_0206eb98(temp_r4, func_ov017_021d60f4(arg0)) != 0) {
        func_ov017_021d6134(temp_r0, 1);
    } else {
        func_ov017_021d6134(temp_r0, 0);
    }
    return 1;
}
