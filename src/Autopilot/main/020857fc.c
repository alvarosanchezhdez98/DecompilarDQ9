#include <m2c.h>


s32 func_020857ec(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s16 *, 0x2AC) <= 0) {
        return 0;
    }
    if (((u32) (M2C_FIELD(arg0, s32 *, 0x2F8) << 0x1C) >> 0x1F) != 0) {
        return 1;
    }
    return 0;
}
