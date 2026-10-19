#include <m2c.h>


s32 func_0201e548(void *arg0, s32 arg1) {
    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, s32 *, 0x1C) <= arg1)) {
        return 0;
    }
    return (arg1 * 0x70) + M2C_FIELD(arg0, s32 *, 0x18);
}
