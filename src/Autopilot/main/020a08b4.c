#include <m2c.h>


u32 func_020a08a4(void *arg0) {
    u32 temp_r4;
    u32 var_r0;

    temp_r4 = (u32) (M2C_FIELD(arg0, s32 *, 0x14) << 0xE) >> 0x17;
    var_r0 = (u32) (temp_r4 * 0x64) / 232U;
    if (var_r0 != 0) {
        return var_r0;
    }
    if (temp_r4 != 0) {
        var_r0 = 1;
    }
    return var_r0;
}
