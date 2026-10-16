#include <m2c.h>


#pragma thumb on
s32 func_ov031_0221e650(s8 *arg0) {
    s32 var_r2;

    var_r2 = 0;
    if (*arg0 != 0) {
        do {
            var_r2 += 1;
        } while (*(arg0 + var_r2) != 0);
    }
    return var_r2;
}
#pragma thumb off
