#include <m2c.h>


void func_020444bc(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x9A0) = 5;
    M2C_FIELD(arg0, s32 *, 0x78) = (s32) (M2C_FIELD(arg0, s32 *, 0x78) + 1);
}
