#include <m2c.h>


s32 func_ov000_0217f464(void *arg0) {
    if ((s32) M2C_FIELD((arg0 + M2C_FIELD(arg0, s8 *, 0x18)), s8 *, 0x10) < 0x64) {
        return 1;
    }
    return 0;
}
