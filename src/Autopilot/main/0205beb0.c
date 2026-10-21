#include <m2c.h>

M2C_UNK func_02012a84(M2C_UNK *, s32 *, s32 *);
s32 func_0205bd78(M2C_UNK, s32, s32);
extern M2C_UNK data_02114e54;

s32 func_0205bea0(M2C_UNK arg0) {
    s32 sp4;
    s32 sp0;
    s32 var_r0;

    if (M2C_FIELD(&data_02114e54, u8 *, 0x55) != 0) {
        func_02012a84(&data_02114e54, &sp4, &sp0);
        if (func_0205bd78(arg0, sp4, sp0) >= 0) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        return var_r0;
    }
    return 0;
}
