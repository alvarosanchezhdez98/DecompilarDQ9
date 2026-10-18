#include <m2c.h>

void *func_ov017_0218b5b0();
s32 func_ov017_021d612c(M2C_UNK);
M2C_UNK sprintf(s32, M2C_UNK *, s32);
extern M2C_UNK data_ov001_02165745;

s32 func_ov001_021613d0(M2C_UNK arg0) {
    s32 temp_r4;

    temp_r4 = M2C_FIELD(func_ov017_0218b5b0(), s32 *, 0x3734);
    sprintf(temp_r4 + 0xD8, &data_ov001_02165745, func_ov017_021d612c(arg0));
    return 1;
}
