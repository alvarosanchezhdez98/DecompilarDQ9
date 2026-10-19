#include <m2c.h>


void func_020881ac(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~0x01000000);
    M2C_FIELD(arg0, s8 *, 0x24) = 0;
}
