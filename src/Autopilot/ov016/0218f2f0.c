#include <m2c.h>


s32 func_ov016_0218f2f0(void *arg0) {
    s32 temp_r2_2;
    u32 temp_r2;

    temp_r2 = M2C_FIELD(arg0, u32 *, 0x9C);
    if (temp_r2 >= (u32) M2C_FIELD(arg0, u32 *, 0xA0)) {
        return 0;
    }
    M2C_FIELD(arg0, u32 *, 0x9C) = (u32) (temp_r2 + 1);
    temp_r2_2 = M2C_FIELD(arg0, s32 *, 0xC4) + 1;
    M2C_FIELD(arg0, s32 *, 0xC4) = temp_r2_2;
    if (temp_r2_2 == M2C_FIELD(arg0, s32 *, 0xA8)) {
        M2C_FIELD(arg0, s32 *, 0xC4) = 0;
    }
    return 1;
}
