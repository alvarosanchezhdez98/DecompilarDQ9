#include <m2c.h>


s32 func_020ddb20(void *arg0) {
    if (((u32) (M2C_FIELD(arg0, s32 *, 8) << 0xC) >> 0x1F) != 0) {
        return 1;
    }
    return 0;
}
