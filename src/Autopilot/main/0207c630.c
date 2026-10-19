#include <m2c.h>


s16 func_0207c620(s32 arg0, u32 arg1) {
    if (arg1 > 7U) {
        return -1;
    }
    return M2C_FIELD((arg0 + (arg1 * 2)), s16 *, 0xC10);
}
