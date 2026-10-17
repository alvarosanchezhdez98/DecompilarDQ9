#include <m2c.h>

s32 func_ov031_0221042c(M2C_UNK);
s32 func_ov031_02210ef8();

s32 func_ov031_0221032c(M2C_UNK arg0) {
    s32 var_r4;

    var_r4 = -0x38;
    if (func_ov031_02210ef8() != 0) {
        var_r4 = func_ov031_0221042c(arg0);
    }
    return var_r4;
}
