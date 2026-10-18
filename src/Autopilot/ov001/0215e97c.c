#include <m2c.h>

void *func_020421a0();
s32 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_0215e97c(M2C_UNK arg0) {
    s8 var_r1;
    void *temp_r4;

    temp_r4 = func_020421a0();
    if (func_ov017_021d60f4(arg0) != 0) {
        var_r1 = 1;
    } else {
        var_r1 = 0;
    }
    M2C_FIELD(temp_r4, s8 *, 0x19CB) = var_r1;
    return 1;
}
