#include <m2c.h>

s32 func_02012444(M2C_UNK *, M2C_UNK);
M2C_UNK func_02012a84(M2C_UNK *, s32 *, s32 *);
s32 func_02080d54(s32, M2C_UNK, s16, s16);
extern M2C_UNK data_02114e30;
extern M2C_UNK data_02114e54;

s32 func_ov017_021ab1a4(void *arg0) {
    s32 sp4;
    s32 sp0;
    s32 var_r4;

    var_r4 = 0;
    if (func_02012444(&data_02114e30, 2) != 0) {
        var_r4 = 1;
    }
    if (M2C_FIELD(&data_02114e54, u8 *, 0x55) != 0) {
        func_02012a84(&data_02114e54, &sp4, &sp0);
        if ((func_02080d54(M2C_FIELD(arg0, s32 *, 0x18), 0, (s16) sp4, (s16) sp0) == 0) && (func_02080d54(M2C_FIELD(arg0, s32 *, 0x18), 1, (s16) sp4, (s16) sp0) == 0)) {
            var_r4 = 1;
        }
    }
    return var_r4;
}
