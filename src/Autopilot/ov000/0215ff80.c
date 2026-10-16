#include <m2c.h>


s16 func_ov000_0215ff80(s32 arg0, s32 arg1) {
    if (arg1 >= 3) {
        return -1;
    }
    if (arg1 < 0) {
        return -1;
    }
    return M2C_FIELD((arg0 + (arg1 * 2)), s16 *, 0xE);
}
