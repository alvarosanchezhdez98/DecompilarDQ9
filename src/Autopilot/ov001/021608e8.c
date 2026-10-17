#include <m2c.h>
#pragma optimization_level 4

void *func_020421a0();
s32 func_ov017_021d60f4();

s32 func_ov001_021608e8(void) {
    s32 temp_r4;

    temp_r4 = func_ov017_021d60f4();
    M2C_FIELD(func_020421a0(), s32 *, 0x99C) = temp_r4;
    return 1;
}
