#include <m2c.h>


s32 func_ov024_021f6ed8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (0.3f * M2C_FIELD(arg0, f32 *, 0x14));
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (0.1f * M2C_FIELD(arg0, f32 *, 0x18));
    return 1;
}
