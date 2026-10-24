#include <m2c.h>

s32 func_ov000_021820bc(M2C_UNK, M2C_UNK, M2C_UNK, s32 *);
s32 func_ov017_0218b5b0();
M2C_UNK func_ov017_02191aac(s32, M2C_UNK, s32, M2C_UNK);

s32 func_ov025_021e8084(s32 arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3) {
    s32 sp0[4];
    s32 temp_r4;

    temp_r4 = func_ov017_0218b5b0();
    if (func_ov000_021820bc(arg3, arg1, 7, sp0) != 0) {
        func_ov017_02191aac(temp_r4, 1, sp0[0], 4);
    }
    return 1;
}
