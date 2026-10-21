#include <m2c.h>


void func_020708c8(void *arg0, u32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = (s32) (16.667f * (f32) arg1);
    M2C_FIELD(arg0, s8 *, 4) = 1;
    M2C_FIELD(arg0, s8 *, 0) = 1;
}
