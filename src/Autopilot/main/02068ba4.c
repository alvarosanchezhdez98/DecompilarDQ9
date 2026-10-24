#include <m2c.h>


s32 func_02068b94(s32 arg0, void *arg1) {
    s32 temp_r0;

    temp_r0 = M2C_FIELD(arg1, s32 *, 0x8B4);
    if ((temp_r0 != 0) && (temp_r0 != 1)) {
        return 1;
    }
    return 0;
}
