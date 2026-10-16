#include <m2c.h>


s32 func_ov024_021f71a8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (1.5f * M2C_FIELD(arg0, f32 *, 0x14));
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (1.5f * M2C_FIELD(arg0, f32 *, 0x18));
    return 1;
}
