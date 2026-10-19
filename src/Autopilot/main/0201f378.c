#include <m2c.h>


s32 func_0201f368(void *arg0, s32 arg1) {
    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, u8 *, 0x38) <= arg1)) {
        return 0;
    }
    return M2C_FIELD((arg0 + (arg1 * 4)), s32 *, 0x18);
}
