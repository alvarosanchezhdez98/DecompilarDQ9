#include <m2c.h>


s32 func_ov000_0217199c(s32 arg0, s32 arg1) {
    if ((arg1 < 0) || (arg1 >= 0x93)) {
        return 0;
    }
    return M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0x1A4);
}
