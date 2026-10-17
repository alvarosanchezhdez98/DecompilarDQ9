#include <m2c.h>
#pragma optimization_level 4

s32 func_020704fc();
M2C_UNK func_020708c8(s32, s32);
s32 func_ov017_021d60f4();

s32 func_ov001_0215b384(void) {
    s32 temp_r0;
    s32 temp_r4;

    temp_r4 = func_ov017_021d60f4();
    temp_r0 = func_020704fc();
    if (temp_r0 != 0) {
        func_020708c8(temp_r0, temp_r4);
    }
    return 1;
}
