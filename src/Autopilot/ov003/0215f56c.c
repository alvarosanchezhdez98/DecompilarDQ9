#include <m2c.h>


s32 func_ov003_0215f56c(void *arg0) {
    f32 temp_r0;
    s32 var_r4;

    var_r4 = 0xF;
    if ((arg0 != NULL) && ((s32) ((s32) (M2C_FIELD(arg0, s8 *, 0) << 0x1A) >> 0x1A) >= 0)) {
        temp_r0 = (f32) ((u32) (M2C_FIELD(arg0, s32 *, 0x154) << 0xC) >> 0x16) / (f32) ((u32) (M2C_FIELD(arg0, s32 *, 0x158) << 0x16) >> 0x16);
        if (temp_r0 <= 0.25f) {
            var_r4 = 0xD;
        }
        if (temp_r0 <= 0.08f) {
            var_r4 = 0xB;
        }
    }
    return var_r4;
}
