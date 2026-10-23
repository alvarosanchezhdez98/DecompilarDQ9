#include <m2c.h>


void func_02070900(void *arg0, void *arg1, u32 arg2) {
    M2C_FIELD(arg0, s16 *, 2) = (s16) (M2C_FIELD(arg1, s32 *, 0) | (M2C_FIELD(arg1, s32 *, 4) << 5) | (M2C_FIELD(arg1, s32 *, 8) << 0xA));
    M2C_FIELD(arg0, s32 *, 8) = (s32) (16.667f * (f32) arg2);
    M2C_FIELD(arg0, s8 *, 4) = 0x1F;
    M2C_FIELD(arg0, s8 *, 0) = 1;
}
