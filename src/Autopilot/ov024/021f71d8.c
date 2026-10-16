#include <m2c.h>


s32 func_ov024_021f71d8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) ((4.0f * M2C_FIELD(arg0, f32 *, 0x14)) / (f32) (M2C_FIELD(arg0, u16 *, 0xC) + 1));
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) ((4.0f * M2C_FIELD(arg0, f32 *, 0x18)) / (f32) (M2C_FIELD(arg0, u16 *, 0xC) + 1));
    return 1;
}
