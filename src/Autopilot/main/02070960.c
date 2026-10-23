#include <m2c.h>


void func_02070950(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg2 < 0) {
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x10) = arg2;
    M2C_FIELD(arg0, s16 *, 2) = (s16) (M2C_FIELD(arg1, s32 *, 0) | (M2C_FIELD(arg1, s32 *, 4) << 5) | (M2C_FIELD(arg1, s32 *, 8) << 0xA));
    M2C_FIELD(arg0, s32 *, 8) = (s32) (16.667f * (f32) arg3);
    M2C_FIELD(arg0, s8 *, 4) = (s8) arg4;
    M2C_FIELD(arg0, s8 *, 0) = 1;
}
