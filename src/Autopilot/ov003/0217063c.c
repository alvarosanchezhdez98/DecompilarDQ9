#include <m2c.h>


void func_ov003_0217063c(void *arg0, s16 *arg1, s16 *arg2) {
    u16 temp_r3;

    if ((M2C_FIELD(arg0, s8 *, 1) == 5) && ((temp_r3 = M2C_FIELD(arg0, u16 *, 0x20), ((temp_r3 & 0x10) != 0)) || (temp_r3 & 4))) {
        *arg1 = 0x2C;
        *arg2 = (M2C_FIELD(arg0, s8 *, 8) * 0x11) + 0x3A;
        return;
    }
    *arg1 = 0;
    *arg2 = 0;
}
