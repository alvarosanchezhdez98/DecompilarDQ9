#include <m2c.h>

s32 func_ov031_0221e4fc(u8 *, M2C_UNK, s32);
extern u8 data_ov031_0224f440;

#pragma thumb on
s32 func_ov031_0221d79c(s32 arg0, M2C_UNK arg1) {
    s32 var_r3;
    s32 var_r4;
    s32 var_r5;
    u8 *var_r6;

    var_r4 = 0;
    var_r6 = &data_ov031_0224f440;
    var_r5 = 0;
    var_r3 = 0;
loop_1:
    if (*var_r6 != 0) {
        var_r5 = 1;
    } else {
        var_r3 += 1;
        var_r6 += 1;
        if (var_r3 < 6) {
            goto loop_1;
        }
    }
    if (var_r5 != 0) {
        if (func_ov031_0221e4fc(&data_ov031_0224f440, arg1, 6) != 0) {
            var_r4 = 1;
        }
    } else if (arg0 != 0x1000) {
        var_r4 = 2;
    }
    return var_r4;
}
#pragma thumb off
