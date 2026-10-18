#include <m2c.h>


s32 func_0204af14(void *arg0, u32 arg1) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_r2 == 0) {
        return 0;
    }
    if ((u32) M2C_FIELD(arg0, u8 *, 0x1D) <= arg1) {
        return 0;
    }
    return temp_r2 + (arg1 * 0x10);
}
