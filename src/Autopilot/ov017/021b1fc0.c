#include <m2c.h>


s32 func_ov017_021b1fc0(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_r0 != 0) {
        return temp_r0 + 0x50;
    }
    return 0;
}
