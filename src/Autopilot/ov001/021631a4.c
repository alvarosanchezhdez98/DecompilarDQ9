#include <m2c.h>
#pragma optimization_level 4

void *func_ov017_0218b5b0();
s16 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_021631a4(M2C_UNK arg0) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(func_ov017_0218b5b0(), void **, 0x3734);
    M2C_FIELD(temp_r4, s16 *, 0x184) = func_ov017_021d60f4(arg0);
    return 1;
}
