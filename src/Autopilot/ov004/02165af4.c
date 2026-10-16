#include <m2c.h>

void *func_020421a0();

s32 func_ov004_02165af4(void) {
    void *temp_r0;

    temp_r0 = func_020421a0();
    M2C_FIELD(temp_r0, s8 *, 0x19B2) = 1;
    M2C_FIELD(temp_r0, s32 *, 0x99C) = 1;
    return 0;
}
