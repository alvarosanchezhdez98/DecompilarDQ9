#include <m2c.h>

s32 func_ov000_02161318();
s32 func_ov000_02170c7c();

s32 func_ov000_02174e34(void) {
    if (func_ov000_02161318() == 0) {
        return -1;
    }
    return func_ov000_02170c7c();
}
