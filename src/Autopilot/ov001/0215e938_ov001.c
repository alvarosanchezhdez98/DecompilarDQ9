#include <m2c.h>

void *func_020421a0();
s8 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_0215e938(M2C_UNK arg0) {
    void *temp_r4;

    temp_r4 = func_020421a0();
    M2C_FIELD(temp_r4, s8 *, 0x19AE) = func_ov017_021d60f4(arg0);
    return 1;
}
