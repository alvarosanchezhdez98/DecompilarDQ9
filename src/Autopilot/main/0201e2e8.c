#include <m2c.h>


s32 func_0201e2d8(void *arg0, s32 arg1) {
    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, s32 *, 4) <= arg1)) {
        return 0;
    }
    return (arg1 * 0x58) + M2C_FIELD(arg0, s32 *, 0);
}
