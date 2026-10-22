#include <m2c.h>

s32 func_020bc0a4(s16);

s32 func_0209ca2c(void *arg0) {
    s16 temp_r1;

    temp_r1 = M2C_FIELD(arg0, s16 *, 0xCE);
    if ((s32) temp_r1 < 0) {
        return 0;
    }
    if (M2C_FIELD(arg0, u8 *, 0xC9) != 0) {
        return 1;
    }
    if (func_020bc0a4(temp_r1) > 0) {
        return 1;
    }
    return 0;
}
