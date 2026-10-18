#include <m2c.h>


void func_0209ffe0(void *arg0, s16 arg1) {
    s16 temp_r3;

    temp_r3 = M2C_FIELD(arg0, s16 *, 0x68);
    if ((s32) temp_r3 < 0x32) {
        M2C_FIELD(arg0, s16 *, 0x68) = (s16) (temp_r3 + 1);
        M2C_FIELD((arg0 + (temp_r3 * 2)), s16 *, 0x6A) = arg1;
    }
}
