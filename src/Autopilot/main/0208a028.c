#include <m2c.h>


s32 func_0208a018(void *arg0, s32 arg1) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_r2 == 0) {
        return 0;
    }
    if ((s32) M2C_FIELD(arg0, s16 *, 4) <= arg1) {
        return 0;
    }
    return temp_r2 + (arg1 << 6);
}
