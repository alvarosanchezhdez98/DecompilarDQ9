#include <m2c.h>


s16 func_0206f7f4(void *arg0, s32 arg1) {
    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, s32 *, 4) <= arg1)) {
        return -1;
    }
    return M2C_FIELD((arg0 + (arg1 * 2)), s16 *, 8);
}
