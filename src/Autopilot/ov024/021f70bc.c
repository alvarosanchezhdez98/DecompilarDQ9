#include <m2c.h>

s32 func_0202053c(s32);

s32 func_ov024_021f70bc(void *arg0) {
    s32 temp_r4;

    temp_r4 = func_0202053c(M2C_FIELD(arg0, s32 *, 0)) * 2;
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (temp_r4 + 0x7D);
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (0.85f * (f32) (temp_r4 + 0x7D));
    return 1;
}
