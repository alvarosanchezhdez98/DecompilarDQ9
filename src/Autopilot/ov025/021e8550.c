#include <m2c.h>

void *func_020421a0();

s32 func_ov025_021e8550(void *arg0) {
    s16 temp_r4;

    temp_r4 = M2C_FIELD(arg0, s16 *, 8);
    M2C_FIELD(func_020421a0(), s16 *, 0x19DA) = temp_r4;
    return 1;
}
