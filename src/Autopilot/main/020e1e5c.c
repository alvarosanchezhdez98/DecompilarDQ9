#include <m2c.h>

M2C_UNK func_02012a84(M2C_UNK *, s32 *, s32 *);
s32 func_020e1eb0(M2C_UNK, s16, s16);
extern M2C_UNK data_02114e54;

s32 func_020e1e4c(M2C_UNK arg0) {
    s32 sp4;
    s32 sp0;
    s32 var_r0;

    if (M2C_FIELD(&data_02114e54, u8 *, 0x55) != 0) {
        func_02012a84(&data_02114e54, &sp4, &sp0);
        var_r0 = func_020e1eb0(arg0, (s16) sp4, (s16) sp0);
        if (var_r0 < 0) {
            var_r0 = -2;
        }
        return var_r0;
    }
    return -1;
}
