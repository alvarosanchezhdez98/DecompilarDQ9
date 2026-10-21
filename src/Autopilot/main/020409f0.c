#include <m2c.h>

s32 func_0203cdf8(s32);

s32 func_020409e0(void *arg0) {
    s32 temp_r1_2;
    void *temp_r0;
    void *temp_r1;

    temp_r1_2 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_r1_2 != 0) {
        return func_0203cdf8(temp_r1_2);
    }
    temp_r1 = M2C_FIELD(arg0, void **, 0x18);
    if (temp_r1 != NULL) {
        return M2C_FIELD(temp_r1, s32 *, 0xB0);
    }
    temp_r0 = M2C_FIELD(arg0, void **, 0x1C);
    if (temp_r0 != NULL) {
        return M2C_FIELD(temp_r0, s32 *, 0x2D4);
    }
    return 0;
}
