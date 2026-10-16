#include <m2c.h>


s16 func_ov000_0215ffa0(void *arg0) {
    s32 var_r1;
    u8 temp_r2;

    temp_r2 = M2C_FIELD(arg0, u8 *, 0x17);
    var_r1 = temp_r2 - 1;
    if ((u32) temp_r2 > 3U) {
        var_r1 = 2;
    }
    if (temp_r2 == 0) {
        var_r1 = 0;
    }
    return M2C_FIELD((arg0 + (var_r1 * 2)), s16 *, 0xE);
}
