#include <m2c.h>

void *func_ov017_0218b5b0();
s32 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_021630f4(M2C_UNK arg0) {
    s8 var_r0;
    void *temp_r4;

    temp_r4 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3734);
    if (func_ov017_021d60f4(arg0) != 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    M2C_FIELD(temp_r4, s8 *, 0xFE) = var_r0;
    return 1;
}
