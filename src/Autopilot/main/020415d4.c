#include <m2c.h>


s32 func_020415c4(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0xAC) & 2) {
        return M2C_FIELD(arg0, s32 *, 0xB0);
    }
    return M2C_FIELD(arg0, s32 *, 0x54);
}
