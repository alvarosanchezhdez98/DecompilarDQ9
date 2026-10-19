#include <m2c.h>


s32 func_020177a8(void *arg0, s32 arg1) {
    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, u8 *, 0x477) <= arg1)) {
        return 0;
    }
    return (arg1 * 0x24) + M2C_FIELD(arg0, s32 *, 0x47C);
}
