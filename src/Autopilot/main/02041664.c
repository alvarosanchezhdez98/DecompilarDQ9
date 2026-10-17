#include <m2c.h>
#pragma optimization_level 4


s32 func_02041654(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0x2D0) & 2) {
        return M2C_FIELD(arg0, s32 *, 0x2D4);
    }
    return M2C_FIELD(arg0, s32 *, 0x54);
}
