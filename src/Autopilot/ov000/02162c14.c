#include <m2c.h>

void *func_ov000_02161318(s32);
s8 func_ov000_021761c8(s32, s8);
s8 func_ov000_021761ec(s32, s8);

void func_ov000_02162c14(s32 arg0, s32 arg1, void *arg2) {
    void *temp_r0;

    temp_r0 = func_ov000_02161318(arg0 + 0x3760);
    if (temp_r0 == NULL) {
        return;
    }
    M2C_FIELD(arg2, s8 *, 0) = (s8) M2C_FIELD((temp_r0 + M2C_FIELD(temp_r0, s8 *, 0x18)), s8 *, 0x10);
    M2C_FIELD(arg2, s8 *, 1) = (s8) M2C_FIELD(temp_r0, s8 *, 0x1C);
    M2C_FIELD(arg2, s8 *, 2) = func_ov000_021761c8(arg0 + 0x3760, M2C_FIELD(temp_r0, s8 *, 0x1D));
    M2C_FIELD(arg2, s8 *, 3) = func_ov000_021761ec(arg0 + 0x3760, M2C_FIELD(temp_r0, s8 *, 0x1D));
    M2C_FIELD(arg2, s16 *, 6) = (s16) M2C_FIELD(temp_r0, s16 *, 0x2C);
    M2C_FIELD(arg2, s8 *, 4) = (s8) M2C_FIELD(temp_r0, s8 *, 0x2E);
    M2C_FIELD(arg2, u16 *, 8) = (u16) M2C_FIELD(temp_r0, u16 *, 0x26);
}
