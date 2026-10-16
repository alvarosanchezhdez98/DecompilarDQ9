#include <m2c.h>

extern s32 data_ov031_02290d10;

s32 func_ov031_02237eb0(void) {
    if (data_ov031_02290d10 != 0) {
        return 1;
    }
    return 0;
}
