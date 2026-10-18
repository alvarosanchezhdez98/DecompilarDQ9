#include <m2c.h>

void *func_ov017_0218b5b0();
s32 func_ov017_021d60f4();

s32 func_ov001_02160904(void) {
    s32 temp_r0;
    s32 temp_r4;
    s32 var_r0;
    void *temp_r1;

    temp_r4 = func_ov017_021d60f4();
    temp_r1 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x36D0);
    temp_r0 = M2C_FIELD(temp_r1, s32 *, 0x5A4);
    if (temp_r4 != 0) {
        var_r0 = temp_r0 & ~1;
    } else {
        var_r0 = temp_r0 | 1;
    }
    M2C_FIELD(temp_r1, s32 *, 0x5A4) = var_r0;
    return 1;
}
