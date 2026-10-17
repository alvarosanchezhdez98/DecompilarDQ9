#include <m2c.h>


void func_ov003_021705d4(void *arg0, s16 *arg1, s16 *arg2) {
    s8 temp_r3;

    if (M2C_FIELD(arg0, s8 *, 1) == 5) {
        if (!(M2C_FIELD(arg0, u16 *, 0x20) & 4) || ((temp_r3 = M2C_FIELD(arg0, s8 *, 6), ((s32) temp_r3 >= 0)) && ((s32) temp_r3 <= 3))) {
            *arg1 = 4;
            *arg2 = (M2C_FIELD(arg0, s8 *, 6) * 0x10) + 0x2B;
            return;
        }
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    *arg1 = 0;
    *arg2 = 0;
}
