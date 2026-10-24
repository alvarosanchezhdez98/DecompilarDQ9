#include <m2c.h>


s32 func_020de334(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 == ((u32) (M2C_FIELD(arg0, s32 *, 8) << 0x17) >> 0x1B)) {
        return 1;
    }
    return 0;
}
