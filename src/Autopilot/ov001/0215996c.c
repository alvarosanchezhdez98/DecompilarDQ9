#include <m2c.h>
#pragma optimization_level 4


s32 func_ov001_0215996c(void *arg0, void *arg1) {
    s32 temp_r2;

    temp_r2 = M2C_FIELD(arg1, s32 *, 0x60);
    if (temp_r2 >= (s32) M2C_FIELD(arg0, s32 *, 0x10)) {
        M2C_FIELD(arg1, s32 *, 0x60) = 0;
        return 0;
    }
    M2C_FIELD(arg1, s32 *, 0x60) = (s32) (temp_r2 + 1);
    return 1;
}
