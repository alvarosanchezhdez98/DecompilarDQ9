#include <m2c.h>


s32 func_ov000_0215e9d8(void *arg0) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0x8E24);
    if (temp_r2 >= 0x48) {
        return 0;
    }
    return (temp_r2 * 0x28) + (s32) (arg0 + 0x821C);
}
