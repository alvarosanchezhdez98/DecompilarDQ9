#include <m2c.h>


s32 func_020483f0(void *arg0, s32 arg1) {
    s32 *temp_r2;
    s32 temp_r0;

    temp_r2 = M2C_FIELD(arg0, s32 **, 0x130);
    temp_r0 = *temp_r2;
    if (arg1 & temp_r0) {
        return 0;
    }
    *temp_r2 = (s32) (u16) (temp_r0 | arg1);
    return 1;
}
