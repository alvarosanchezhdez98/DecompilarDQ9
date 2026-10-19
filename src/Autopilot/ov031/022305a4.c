#include <m2c.h>

s32 FastIntDivide(u16, M2C_UNK);
extern M2C_UNK data_ov031_02290ca0;

s32 ov13_02234974(s32 arg0) {
    s32 var_r0;
    s32 var_r1;

    var_r0 = FastIntDivide(M2C_FIELD(&data_ov031_02290ca0, u16 *, 4), 0x1D);
    var_r1 = 0;
loop_1:
    if (var_r0 == arg0) {
        return var_r1;
    }
    var_r1 += 1;
    var_r0 += 1;
    if (var_r1 >= 4) {
        return -1;
    }
    goto loop_1;
}
