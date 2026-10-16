#include <m2c.h>

s32 func_ov000_0215e9fc(s32, s16 *, M2C_UNK, M2C_UNK);
M2C_UNK func_ov024_021ed8c0(s32 *, M2C_UNK, M2C_UNK, s32 *, s16 *);

s32 func_ov024_021ee378(s32 *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 *arg3, s16 *arg4) {
    s32 temp_r0;

    temp_r0 = func_ov000_0215e9fc(*arg0, arg4, 4, 1);
    *arg3 = temp_r0;
    if (temp_r0 <= 0) {
        return 0;
    }
    func_ov024_021ed8c0(arg0, arg1, arg2, arg3, arg4);
    if ((s32) *arg4 >= 0) {
        return 1;
    }
    return 0;
}
