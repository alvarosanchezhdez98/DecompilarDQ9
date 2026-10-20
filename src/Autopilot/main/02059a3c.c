#include <m2c.h>


s32 func_02059a2c(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0xC) != 0) {
        return 0;
    }
    if ((u32) M2C_FIELD(arg0, u32 *, 8) <= (u32) M2C_FIELD(arg0, u32 *, 4)) {
        return 1;
    }
    return 0;
}
