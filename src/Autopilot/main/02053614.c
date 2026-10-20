#include <m2c.h>


s8 func_02053604(void *arg0) {
    s8 temp_r1;

    if (M2C_FIELD(arg0, s8 *, 0x17C) == 0) {
        return -1;
    }
    temp_r1 = M2C_FIELD(arg0, s8 *, 0x17D);
    if ((s32) temp_r1 >= 4) {
        return -1;
    }
    return M2C_FIELD((arg0 + temp_r1), s8 *, 0x178);
}
