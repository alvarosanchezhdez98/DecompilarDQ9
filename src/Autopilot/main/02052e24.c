#include <m2c.h>


s32 func_02052e14(void *arg0) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg0, s32 *, 0x150);
    if (temp_r0 != 0) {
        return temp_r0 + 0x488;
    }
    return 0;
}
