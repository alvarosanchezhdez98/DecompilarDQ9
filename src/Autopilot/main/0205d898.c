#include <m2c.h>


s32 func_0205d888(void *arg0) {
    s32 temp_r2;
    u8 temp_r0;

    if (M2C_FIELD(arg0, s32 *, 0x98) == 0) {
        return 0;
    }
    temp_r2 = M2C_FIELD(arg0, s32 *, 0x9C);
    if (temp_r2 == 0) {
        return 0;
    }
    temp_r0 = M2C_FIELD(arg0, u8 *, 0xB4);
    if (temp_r0 != 0) {
        return ((temp_r0 - 1) * 0xE0) + temp_r2;
    }
    return 0;
}
