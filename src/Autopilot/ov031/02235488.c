#include <m2c.h>

s32 FastIntDivide(M2C_UNK, s32);
M2C_UNK ov13_0223ABDC(s32);
M2C_UNK ov13_0223ABFC(s32, s32);
extern void *data_ov031_02290cf4;

void ov13_02239808(s32 arg0) {
    s32 var_r0;
    s32 var_r1;
    s32 var_r4;

    var_r4 = M2C_FIELD(data_ov031_02290cf4, u8 *, 0x1A) - arg0;
    if (var_r4 < 0) {
        var_r4 = 0 - var_r4;
    }
    if (var_r4 < 2) {
        var_r0 = 0;
    } else {
        var_r0 = 0x7F;
        if (var_r4 < 6) {
            var_r0 = FastIntDivide(0x7F, 6 - var_r4);
        }
    }
    ov13_0223ABDC(var_r0);
    if (var_r4 < 2) {
        var_r1 = -0x100;
    } else if (var_r4 >= 6) {
        var_r1 = 0x100;
    } else {
        var_r1 = FastIntDivide(0x200, 6 - var_r4) - 0x100;
    }
    ov13_0223ABFC(0xFFFF, var_r1);
}
