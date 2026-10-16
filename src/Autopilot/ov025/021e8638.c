#include <m2c.h>

void *func_ov000_02160094(M2C_UNK, M2C_UNK);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_0219230c(s32, u16, s8);

s32 func_ov025_021e8638(void *arg0, M2C_UNK arg1) {
    s32 temp_r4;

    temp_r4 = func_ov017_0218b5b0();
    func_ov017_0219230c(temp_r4, M2C_FIELD(func_ov000_02160094(arg1, 0), u16 *, 0x20), M2C_FIELD(arg0, s8 *, 8));
    return 1;
}
