#include <m2c.h>

M2C_UNK func_ov031_02211138();
s32 func_ov031_022123d4();

s32 func_ov031_0221188c(void) {
    s32 temp_r0;

    temp_r0 = func_ov031_022123d4();
    if (temp_r0 == 0) {
        func_ov031_02211138();
    }
    return temp_r0;
}
