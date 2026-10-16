#include <m2c.h>


s32 func_ov024_021f6dd4(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (2.0f * M2C_FIELD(arg0, f32 *, 0x14));
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (2.0f * M2C_FIELD(arg0, f32 *, 0x18));
    return 1;
}
