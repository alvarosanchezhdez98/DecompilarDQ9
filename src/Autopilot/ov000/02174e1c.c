#include <m2c.h>

s32 func_ov000_02161318();

s32 func_ov000_02174e1c(void) {
    s32 temp_r0;

    temp_r0 = func_ov000_02161318();
    if (temp_r0 != 0) {
        return temp_r0 + 0x68;
    }
    return 0;
}
