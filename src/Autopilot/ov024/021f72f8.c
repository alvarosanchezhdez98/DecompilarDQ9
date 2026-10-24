#include <m2c.h>

void *func_02053c6c(s32);

s32 func_ov024_021f72f8(void *arg0) {
    s32 temp_r5;

    temp_r5 = (u32) (M2C_FIELD(func_02053c6c(M2C_FIELD(arg0, s32 *, 0)), s32 *, 4) << 0x16) >> 0x16;
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) ((M2C_FIELD(arg0, f32 *, 0x14) / 2.0f) + (f32) temp_r5);
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) ((M2C_FIELD(arg0, f32 *, 0x18) / 2.0f) + (f32) temp_r5);
    return 1;
}
