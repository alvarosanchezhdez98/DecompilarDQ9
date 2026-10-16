#include <m2c.h>

s32 func_02088514(s32);
s32 func_020885b4(s32);
s32 func_ov024_021da9b0(void *);

s32 func_ov024_021f6cc0(void *arg0) {
    void *temp_r4;

    temp_r4 = M2C_FIELD(arg0, void **, 4);
    if ((func_020885b4(M2C_FIELD(temp_r4, s32 *, 0x138)) != 0) || (func_02088514(M2C_FIELD(temp_r4, s32 *, 0x138)) != 0) || (func_ov024_021da9b0(temp_r4) != 0)) {
        M2C_FIELD(arg0, f32 *, 0x1C) = (f32) (1.5f * M2C_FIELD(arg0, f32 *, 0x14));
        M2C_FIELD(arg0, f32 *, 0x20) = (f32) (1.5f * M2C_FIELD(arg0, f32 *, 0x18));
    }
    return 1;
}
