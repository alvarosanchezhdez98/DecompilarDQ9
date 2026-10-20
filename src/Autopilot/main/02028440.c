#include <m2c.h>


s32 func_02028430(void *arg0, s32 arg1) {
    s32 temp_r0;

    if ((arg1 < 0) || ((s32) M2C_FIELD(arg0, u8 *, 2) <= arg1)) {
        return 0;
    }
    temp_r0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_r0 != 0) {
        return temp_r0 + (arg1 * 0x10);
    }
    return 0;
}
