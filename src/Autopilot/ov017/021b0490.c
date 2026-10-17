#include <m2c.h>
#pragma optimization_level 4


u8 func_ov017_021b0490(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 9) == 0) && (M2C_FIELD(arg0, s32 *, 0x30) != 0)) {
        M2C_FIELD(arg0, s8 *, 0x23) = 0;
        M2C_FIELD(arg0, s8 *, 0x24) = 0;
        return 9U;
    }
    return M2C_FIELD(arg0, u8 *, 0xA);
}
