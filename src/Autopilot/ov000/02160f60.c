#include <m2c.h>
#pragma optimize_for_size off


s32 func_ov000_02160f60(void *arg0) {
    s32 temp_r0;
    s32 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s32 *, 0x55D8);
    if (temp_r1 == 0) {
        return 0;
    }
    temp_r0 = M2C_FIELD(arg0, s32 *, 0x29C);
    if (temp_r0 == 0) {
        return 0;
    }
    return ((temp_r1 - 1) * 0x28) + (temp_r0 + 0x821C);
}
