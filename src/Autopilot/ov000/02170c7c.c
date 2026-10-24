#include <m2c.h>


s32 func_ov000_02170c7c(void *arg0) {
    f32 temp_r0;
    s32 var_r5;
    s16 temp_r6;

    temp_r6 = M2C_FIELD(arg0, s16 *, 8);
    var_r5 = 0;
    if (temp_r6 == 0) {
        return 6;
    }
    temp_r0 = (f32) M2C_FIELD(arg0, s16 *, 0xC) / (f32) temp_r6;
    if (temp_r0 <= 0.0f) {
        var_r5 = 6;
    } else if (temp_r0 <= 0.08f) {
        var_r5 = 5;
    } else if (temp_r0 <= 0.25f) {
        var_r5 = 4;
    }
    return var_r5;
}
