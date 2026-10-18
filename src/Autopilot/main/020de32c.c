#include <m2c.h>


s32 func_020de31c(void *arg0, s32 arg1) {
    if (arg1 == ((u32) (M2C_FIELD(arg0, s32 *, 8) << 0x1C) >> 0x1C)) {
        return 1;
    }
    return 0;
}
