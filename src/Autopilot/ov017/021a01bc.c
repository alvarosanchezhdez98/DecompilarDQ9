#include <m2c.h>
#pragma optimization_level 4

s32 func_0202ae18();
s32 func_0202b7d8();
s32 func_0202c508(s32);

void func_ov017_021a01bc(void *arg0) {
    s32 temp_r4;

    temp_r4 = func_0202ae18();
    if (func_0202b7d8() == 0) {
        return;
    }
    if (func_0202c508(temp_r4) == 0) {
        M2C_FIELD(arg0, s8 *, 0x42E9) = 1;
    }
}
