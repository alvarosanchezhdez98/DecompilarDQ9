#include <m2c.h>


s32 func_0207c5f8(s32 arg0, u32 arg1) {
    if (arg1 > 7U) {
        return 0;
    }
    return M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0xBD0);
}
