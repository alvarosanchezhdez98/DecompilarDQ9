#include <m2c.h>


void func_02053c4c(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x150) = arg1;
    M2C_FIELD(arg0, s32 *, 0x134) = (s32) (arg1 + 0x3C);
    M2C_FIELD(arg0, s32 *, 0x130) = (s32) (arg1 + 0x18);
    M2C_FIELD(arg0, s32 *, 0x138) = (s32) (arg1 + 0x94);
}
