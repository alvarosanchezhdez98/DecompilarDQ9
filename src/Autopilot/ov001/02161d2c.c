#include <m2c.h>

void *func_02012fe4();
s32 func_ov017_021d60f4(M2C_UNK);

s32 func_ov001_02161d2c(M2C_UNK arg0) {
    void *temp_r4;

    temp_r4 = func_02012fe4();
    M2C_FIELD(temp_r4, s32 *, 0x274C) = func_ov017_021d60f4(arg0);
    return 1;
}
