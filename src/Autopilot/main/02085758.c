#include <m2c.h>


u32 func_02085748(void *arg0) {
    if ((s32) M2C_FIELD(arg0, s16 *, 0x2AC) <= 0) {
        return 0U;
    }
    return (u32) (M2C_FIELD(arg0, s32 *, 0x2F4) << 6) >> 0x1D;
}
