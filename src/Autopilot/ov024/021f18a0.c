#include <m2c.h>

M2C_UNK __clear(M2C_UNK *, M2C_UNK);
s32 func_ov000_0215e9fc(s32, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK memcpy(s32, M2C_UNK *, M2C_UNK);

s32 func_ov024_021f18a0(s32 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
    M2C_UNK sp0[2];
    s32 temp_r0;

    __clear(sp0, 8);
    temp_r0 = func_ov000_0215e9fc(*arg0, sp0, 4, 1);
    if (temp_r0 <= 0) {
        return 0;
    }
    *arg3 = temp_r0;
    memcpy(arg4, sp0, 8);
    return 1;
}
