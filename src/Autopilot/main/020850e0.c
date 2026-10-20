#include <m2c.h>


s32 func_020850d0(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s16 *, 0x2AC) <= 0) {
        return 0;
    }
    if (((u32) (M2C_FIELD(arg0, s32 *, 0x2F4) << 0x1D) >> 0x1F) != 0) {
        return 1;
    }
    return 0;
}
