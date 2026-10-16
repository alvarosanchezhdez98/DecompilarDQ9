#include <m2c.h>

s32 func_020882f8(s32);
s32 func_ov024_021de25c(void *);

s32 func_ov024_021f6d2c(void *arg0) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(arg0, void **, 4);
    if ((func_020882f8(M2C_FIELD(temp_r4, s32 *, 0x138)) != 0) || (func_ov024_021de25c(temp_r4) != 0)) {
        M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (2.0f * M2C_FIELD(arg0, f32 *, 0x14));
        M2C_FIELD(arg0, f32 *, 0x20) = (f32) (2.0f * M2C_FIELD(arg0, f32 *, 0x18));
    }
    return 1;
}
