#include <m2c.h>
#pragma optimization_level 4


s32 func_02052e2c(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x150);
    if (temp_r0 != 0) {
        return temp_r0 + 0x488;
    }
    return 0;
}
