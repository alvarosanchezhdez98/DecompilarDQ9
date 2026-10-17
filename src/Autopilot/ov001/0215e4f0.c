#include <m2c.h>
#pragma optimization_level 4

void *func_020421a0();

s32 func_ov001_0215e4f0(void) {
    void *temp_r0;

    temp_r0 = func_020421a0();
    if (temp_r0 == NULL) {
        return 0;
    }
    M2C_FIELD(temp_r0, s8 *, 0x19B1) = 0;
    return 1;
}
