#include <m2c.h>


u8 func_0205d67c(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x98) == 0) {
        return 0U;
    }
    if (M2C_FIELD(arg0, s32 *, 0x9C) != 0) {
        return M2C_FIELD(arg0, u8 *, 0xB4);
    }
    return 0U;
}
