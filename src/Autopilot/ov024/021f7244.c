#include <m2c.h>

M2C_UNK func_0202053c(s32);

s32 func_ov024_021f7244(void *arg0) {
    func_0202053c(M2C_FIELD(arg0, s32 *, 0));
    M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (5.0f + (M2C_FIELD(arg0, f32 *, 0x14) / 4.0f));
    M2C_FIELD(arg0, f32 *, 0x20) = (f32) (5.0f + (M2C_FIELD(arg0, f32 *, 0x18) / 4.0f));
    return 1;
}
