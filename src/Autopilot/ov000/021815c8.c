#include <m2c.h>


s8 func_ov000_021815c8(void *arg0) {
    s8 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s8 *, 0x1D6B);
    if ((s32) temp_r1 < 0) {
        return -1;
    }
    return M2C_FIELD((arg0 + temp_r1), s8 *, 0x70);
}
