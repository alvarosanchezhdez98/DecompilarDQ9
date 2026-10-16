#include <m2c.h>


s32 func_ov025_021e8a64(void *arg0) {
    return M2C_FIELD((arg0 + (M2C_FIELD(arg0, u8 *, 0x30) * 4)), s32 *, 0x20);
}
