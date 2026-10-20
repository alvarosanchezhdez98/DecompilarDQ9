#include <m2c.h>


s32 func_020887d0(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x18) & 0x80) && (((u32) (M2C_FIELD(arg0, u16 *, 0x22) << 0x14) >> 0x1D) == 5)) {
        return 1;
    }
    return 0;
}
